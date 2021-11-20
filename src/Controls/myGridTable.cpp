#include "myGridTable.h"
#include <wx/graphics.h>
#include "../Frames/Dialog_ListColumnSelect.h"
#include "../Utility/CustomEvents.h"


myGridTable::myGridTable(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize) 
	: wxGrid(parent,id,pos,size)
{
	this->initGridLabels();
	m_tableData = new myGridTableData(m_gridLabels);

	this->SetTable(m_tableData, true, wxGrid::wxGridSelectRows);

	SetActiveColumns();
	
	this->HideRowLabels();
	this->DisableDragGridSize();
	this->DisableDragRowSize();
	this->SetDefaultCellFitMode(wxGridFitMode::Ellipsize());
	this->SetDefaultCellFont(wxFontInfo(11).FaceName("Segoe UI"));
	this->SetLabelFont(wxFontInfo(10).FaceName("Segoe UI"));
	this->AutoSizeAllColLabelSize();


	this->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_BOTTOM);
	this->SetLabelTextColour(wxColour(40, 40, 40));
	this->SetLabelBackgroundColour(*wxWHITE);
	this->SetDefaultRowSize(30,true);


	this->SetColLabelSize(40);
	this->EnableGridLines(false);
	this->SetDefaultCellBackgroundColour(*wxWHITE);
	
	m_cellHighlightPenWidth = 0;
	m_cellHighlightROPenWidth = 0;
	EnableEditing(false);
	

	this->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &myGridTable::OnCellSelect, this);


	Bind(wxEVT_GRID_RANGE_SELECT, &myGridTable::DisableRangeHandler, this);
	Bind(wxEVT_GRID_SELECT_CELL, &myGridTable::DisableRangeSelectCellHandler, this);
	Bind(wxEVT_GRID_CELL_LEFT_CLICK, &myGridTable::DisableCtrlMaiusHandler, this);
	Bind(wxEVT_GRID_LABEL_RIGHT_CLICK, [&](wxGridEvent& evt)
		{
			Dialog_ListColumnSelect dlg(this,m_gridLabels,m_activeCol);

		});
	Bind(EVT_GRID_ACTIVE_COL_CHANGE, [&](wxCommandEvent& evt) {
			m_activeCol = evt.GetInt();
			SetActiveColumns();
			Settings::SaveGridActiveCol(m_activeCol);
			AutoSizeAllColLabelSize();
		});
	GetGridWindow()->Bind(wxEVT_MOTION, &myGridTable::DisableDraggingHandler, this);

}

myGridTable::~myGridTable()
{
}

void myGridTable::getSelectedRowData(addPageInfo &info)
{
	m_tableData->getRowData(info, m_selectedRowID);
}

std::map<Grid_label, wxString> myGridTable::getGridLabels()
{
	return m_gridLabels;
}

bool myGridTable::isRowSelected() 
{
	if (m_selectedRowID.empty())
		return false;
	return true;
}

void myGridTable::AutoSizeAllColLabelSize()
{
	int width{};
	uint_fast8_t count{};
	for (size_t i{ 0 }; i < static_cast<int>(Grid_label::grid_max_labels); ++i)
	{
		if (IsColShown(i))
		{
			if(i != static_cast<int>(Grid_label::grid_date))
				this->AutoSizeColLabelSize(i);
			else
				this->SetColSize(static_cast<int>(Grid_label::grid_date), 85);
			width += GetColWidth(i);
			count++;
		}
	}
	

	if (width < GetSize().GetWidth())
	{
		for (size_t i{ 0 }; i < static_cast<int>(Grid_label::grid_max_labels); ++i)
		{
			if (IsColShown(i))
				SetColSize(i, GetSize().GetWidth() / count);
		}
	}

}

void myGridTable::initGridLabels()
{
	m_gridLabels[Grid_label::grid_regnum] = "���. �";
	m_gridLabels[Grid_label::grid_date] = "����";
	m_gridLabels[Grid_label::grid_code] = "��� ������";
	m_gridLabels[Grid_label::grid_owner] = "��������� �� ���.";
	m_gridLabels[Grid_label::grid_receiver] = "���������� ���.";
	m_gridLabels[Grid_label::grid_transporter] = "���������� ���.";
	m_gridLabels[Grid_label::grid_amount_formed] = "������������";
	m_gridLabels[Grid_label::grid_amount_received_phys] = "��������� �� ���. ���";
	m_gridLabels[Grid_label::grid_amount_received_org] = "��������� �� ��. ���.";
	m_gridLabels[Grid_label::grid_amount_used] = "������������";
	m_gridLabels[Grid_label::grid_amount_defused] = "�����������";
	m_gridLabels[Grid_label::grid_amount_burial] = "����������";
	m_gridLabels[Grid_label::grid_amount_storage] = "���������� ��\n ��������";
	m_gridLabels[Grid_label::grid_amount_tUsed] = "�������� ��\n �������������";
	m_gridLabels[Grid_label::grid_amount_tDefused] = "�������� ��\n ��������������";
	m_gridLabels[Grid_label::grid_amount_tBurial] = "�������� ��\n �����������";
	m_gridLabels[Grid_label::grid_amount_tStorage] = "�������� ��\n ��������";
	m_gridLabels[Grid_label::grid_amount_storageFull] = "����� �� ��������";
	m_gridLabels[Grid_label::grid_struct_unitPOD9] = "����������� �������������\n ���9";
	m_gridLabels[Grid_label::grid_waste_norm] = "��������\n ����������� ������";
}

void myGridTable::SetActiveColumns()
{
	for (size_t i{ 0 }; i < static_cast<size_t>(Grid_label::grid_max_labels); ++i)
	{
		if (m_activeCol & (1ul << i) && !IsColShown(i))
			this->ShowCol(i);
		else if (!(m_activeCol & (1ul << i)) && IsColShown(i))
			this->HideCol(i);
	}

	this->Refresh();
}

void myGridTable::OnCellSelect(wxGridEvent& evt)
{
	SelectRow(evt.GetRow());
	m_selectedRowID = m_tableData->getSelectedRowID(evt.GetRow());
}

void myGridTable::DisableRangeHandler(wxGridRangeSelectEvent& evt)
{
	if (evt.Selecting() && (evt.GetTopRow() != evt.GetBottomRow())) {
		evt.StopPropagation();
		evt.Veto();
	}
}

void myGridTable::DisableRangeSelectCellHandler(wxGridEvent& evt)
{
	SelectRow(evt.GetRow());
}

void myGridTable::updateGrid()
{
	myGridTableData* tableNew = new myGridTableData(m_gridLabels);
	m_tableData = tableNew;
	this->SetTable(tableNew, true, wxGrid::wxGridSelectRows);
	this->AutoSizeAllColLabelSize();
	this->SetColSize(static_cast<int>(Grid_label::grid_date), 85);
}

void myGridTable::DisableCtrlMaiusHandler(wxGridEvent& evt)
{
	if (evt.ControlDown() || evt.ShiftDown()) {
		evt.Veto();
	}
	else {
		evt.Skip();
	}
}

void myGridTable::DisableDraggingHandler(wxMouseEvent& evt)
{
	if (evt.Dragging()) {
		evt.Skip(false);
	}
}
