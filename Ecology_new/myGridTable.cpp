#include "myGridTable.h"

myGridTable::myGridTable(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize) 
	: wxGrid(parent,id,pos,size)
{
	this->initGridLabels();
	myGridTableData *tableData = new myGridTableData(m_gridLabels);
	this->SetTable(tableData, true, wxGrid::wxGridSelectRows);

	
	this->HideRowLabels();
	this->DisableDragGridSize();
	this->DisableDragRowSize();
	this->SetDefaultCellFitMode(wxGridFitMode::Ellipsize());
	this->SetDefaultCellFont(wxFontInfo(11).FaceName("Segoe UI"));
	this->SetLabelFont(wxFontInfo(10).FaceName("Segoe UI"));
	this->AutoSizeAllColLabelSize();
	
	this->SetColSize(static_cast<int>(Grid_label::grid_date),85);
	this->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_BOTTOM);
	this->SetLabelTextColour(wxColour(40, 40, 40));
	this->SetLabelBackgroundColour(*wxWHITE);
	this->SetDefaultRowSize(30);
	this->SetColLabelSize(40);
	this->EnableGridLines(false);
	this->SetDefaultCellBackgroundColour(*wxWHITE);

	
}

myGridTable::~myGridTable()
{
}



void myGridTable::AutoSizeAllColLabelSize()
{
	for (size_t i{ 0 }; i < static_cast<int>(Grid_label::grid_max_labels); ++i)
	{
		this->AutoSizeColLabelSize(i);
	}
	
}

void myGridTable::initGridLabels()
{
	m_gridLabels[Grid_label::grid_regnum] = "���. �";
	m_gridLabels[Grid_label::grid_date] = "����";
	m_gridLabels[Grid_label::grid_code] = "��� ������";
	m_gridLabels[Grid_label::grid_owner] = "��������� ���.";
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
	m_gridLabels[Grid_label::grid_struct_unitPOD10] = "����������� �������������\n ���10";
	m_gridLabels[Grid_label::grid_waste_norm] = "��������\n ����������� ������";
}
