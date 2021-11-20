

if(WIN32)
	set(wxWidgets_ROOT_DIR $ENV{WXWIN})
endif()
find_package(wxWidgets REQUIRED core base net xml html qa xrc gl aui propgrid ribbon scintilla richtext media stc webview)
include(${wxWidgets_USE_FILE})
set(wxWidgets_USE_UNICODE ON)
set(wxWidgets_CONFIGURATION mswud)
set(wxWidgets_USE_STATIC ON)
include_directories(PRIVATE ${wxWidgets_INCLUDE_DIRS} 
						${CMAKE_CURRENT_SOURCE_DIR}/3rd/wxpdfdoc/include 
						${CMAKE_CURRENT_SOURCE_DIR}/3rd/wxsqlite3/include)
foreach(LANG C CXX RC)
    set(CMAKE_${LANG}_STANDARD_INCLUDE_DIRECTORIES ${CUSTOM_INCLUDE_DIRECTORIES})
endforeach()

add_library(wxSQLite3Lib STATIC IMPORTED)
add_library(wxPDFDocLib STATIC IMPORTED)
if (WIN32)
	set_property(TARGET wxSQLite3Lib PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/3rd/wxsqlite3/lib/vc_lib/wxsqlite3d.lib")
	set_property(TARGET wxPDFDocLib PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/3rd/wxpdfdoc/lib/vc_lib/wxpdfdocd.lib")
endif()