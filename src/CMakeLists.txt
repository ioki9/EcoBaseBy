set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_LIST 
	${SOURCE_DIR}/Structs.h ${SOURCE_DIR}/Settings.cpp ${SOURCE_DIR}/Settings.h 
	${SOURCE_DIR}/GUI_parameters.h ${SOURCE_DIR}/Utility/CustomAutoComplete.cpp 
	${SOURCE_DIR}/Utility/CustomAutoComplete.h ${SOURCE_DIR}/Utility/CustomCodeValidator.cpp 
	${SOURCE_DIR}/Utility/CustomCodeValidator.h ${SOURCE_DIR}/Utility/CustomEvents.cpp 
	${SOURCE_DIR}/Utility/CustomEvents.h ${SOURCE_DIR}/Utility/Utility.cpp 
	${SOURCE_DIR}/Utility/Utility.h ${SOURCE_DIR}/PDF/PDF_Helper.cpp
	${SOURCE_DIR}/PDF/PDF_Helper.h ${SOURCE_DIR}/PDF/PDF_Journal.cpp 
	${SOURCE_DIR}/PDF/PDF_Journal.h ${SOURCE_DIR}/PDF/PDF_Main.cpp 
	${SOURCE_DIR}/PDF/PDF_Main.h ${SOURCE_DIR}/PDF/PDF_Pod9.cpp
	${SOURCE_DIR}/PDF/PDF_Pod9.h ${SOURCE_DIR}/PDF/PDF_Pod10.cpp 
	${SOURCE_DIR}/PDF/PDF_Pod10.h ${SOURCE_DIR}/Frames/Add_panel.h 
	${SOURCE_DIR}/Frames/Dialog_generic.cpp ${SOURCE_DIR}/Frames/Dialog_generic.h
	${SOURCE_DIR}/Frames/Add_panel.cpp ${SOURCE_DIR}/Frames/cApp.cpp 
	${SOURCE_DIR}/Frames/cApp.h ${SOURCE_DIR}/Frames/cMain.cpp 
	${SOURCE_DIR}/Frames/cMain.h ${SOURCE_DIR}/Frames/Dialog_ask.cpp 
	${SOURCE_DIR}/Frames/Dialog_ask.h ${SOURCE_DIR}/Frames/Dialog_cMainListEdit.cpp 
	${SOURCE_DIR}/Frames/Dialog_cMainListEdit.h ${SOURCE_DIR}/Frames/Dialog_ListColumnSelect.cpp 
	${SOURCE_DIR}/Frames/Dialog_ListColumnSelect.h ${SOURCE_DIR}/Frames/Dialog_OrgAddEdit.cpp  
	${SOURCE_DIR}/Frames/Dialog_OrgAddEdit.h ${SOURCE_DIR}/Frames/MyBusyInfo.cpp 
	${SOURCE_DIR}/Frames/MyBusyInfo.h ${SOURCE_DIR}/Frames/MyScrolledWindow.cpp 
	${SOURCE_DIR}/Frames/MyScrolledWindow.h ${SOURCE_DIR}/Frames/Settings_page.cpp 
	${SOURCE_DIR}/Frames/Settings_page.h ${SOURCE_DIR}/Database/DBMain.cpp 
	${SOURCE_DIR}/Database/DBMain.h ${SOURCE_DIR}/Database/DBColumnEnums.h 
	${SOURCE_DIR}/Controls/MainMenuTabButton.h ${SOURCE_DIR}/Controls/MainMenuTabButton.cpp 
	${SOURCE_DIR}/Controls/itemdata.h ${SOURCE_DIR}/Controls/CustomCheckBox.cpp 
	${SOURCE_DIR}/Controls/CustomCheckBox.h ${SOURCE_DIR}/Controls/MaterialButton.cpp 
	${SOURCE_DIR}/Controls/MaterialButton.h ${SOURCE_DIR}/Controls/myDirPicker.cpp 
	${SOURCE_DIR}/Controls/myDirPicker.h ${SOURCE_DIR}/Controls/myGridTable.cpp 
	${SOURCE_DIR}/Controls/myGridTable.h ${SOURCE_DIR}/Controls/myGridTableData.cpp 
	${SOURCE_DIR}/Controls/myGridTableData.h ${SOURCE_DIR}/Controls/VirtualCodeList.cpp 
	${SOURCE_DIR}/Controls/VirtualCodeList.h ${SOURCE_DIR}/Controls/VirtualListCtrl.cpp 
	${SOURCE_DIR}/Controls/VirtualListCtrl.h ${SOURCE_DIR}/Controls/VirtualOrgList.cpp 
	${SOURCE_DIR}/Controls/VirtualOrgList.h ${SOURCE_DIR}/Controls/VirtualStrgInitList.cpp 
	${SOURCE_DIR}/Controls/VirtualStrgInitList.h ${SOURCE_DIR}/Controls/myGridLabelsEnum.h
	${SOURCE_DIR}/Controls/VirtualEntryDateList.h ${SOURCE_DIR}/Controls/VirtualEntryDateList.cpp
	
)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}Config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}Config.h")

