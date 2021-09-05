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
	m_gridLabels[Grid_label::grid_regnum] = "Рег. №";
	m_gridLabels[Grid_label::grid_date] = "Дата";
	m_gridLabels[Grid_label::grid_code] = "Код отхода";
	m_gridLabels[Grid_label::grid_owner] = "Поступило орг.";
	m_gridLabels[Grid_label::grid_receiver] = "Получатель орг.";
	m_gridLabels[Grid_label::grid_transporter] = "Перевозчик орг.";
	m_gridLabels[Grid_label::grid_amount_formed] = "Образовалось";
	m_gridLabels[Grid_label::grid_amount_received_phys] = "Поступило от физ. лиц";
	m_gridLabels[Grid_label::grid_amount_received_org] = "Поступило от др. орг.";
	m_gridLabels[Grid_label::grid_amount_used] = "Использовано";
	m_gridLabels[Grid_label::grid_amount_defused] = "Обезврежено";
	m_gridLabels[Grid_label::grid_amount_burial] = "Захоронено";
	m_gridLabels[Grid_label::grid_amount_storage] = "Направлено на\n хранение";
	m_gridLabels[Grid_label::grid_amount_tUsed] = "Передано на\n использование";
	m_gridLabels[Grid_label::grid_amount_tDefused] = "Передано на\n обезвреживание";
	m_gridLabels[Grid_label::grid_amount_tBurial] = "Передано на\n захоронение";
	m_gridLabels[Grid_label::grid_amount_tStorage] = "Передано на\n хранение";
	m_gridLabels[Grid_label::grid_amount_storageFull] = "Всего на хранении";
	m_gridLabels[Grid_label::grid_struct_unitPOD9] = "Структурное подразделение\n ПОД9";
	m_gridLabels[Grid_label::grid_struct_unitPOD10] = "Структурное подразделение\n ПОД10";
	m_gridLabels[Grid_label::grid_waste_norm] = "Норматив\n образования отхода";
}
