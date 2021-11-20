# CMakeList.txt : CMake project for EcoBaseBy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("EcoBaseBy" VERSION 0.1)
include("${CMAKE_CURRENT_SOURCE_DIR}/resource/CMakeLists.txt")
include("${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt")

set(DOCUMENTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/Documents)
if(WIN32)
	set(wxWidgets_ROOT_DIR $ENV{WXWIN})
endif()
find_package(wxWidgets REQUIRED core base net xml html qa xrc gl aui propgrid ribbon scintilla richtext media stc webview)
include(${wxWidgets_USE_FILE})
set(wxWidgets_USE_UNICODE ON)
set(wxWidgets_CONFIGURATION mswu)
set(wxWidgets_USE_STATIC ON)
include_directories(PRIVATE ${wxWidgets_INCLUDE_DIRS} 
						${CMAKE_CURRENT_SOURCE_DIR}/libs/wxpdfdoc-1.0.1/include 
						${CMAKE_CURRENT_SOURCE_DIR}/libs/wxsqlite3-4.7.4/include)

foreach(LANG C CXX RC)
    set(CMAKE_${LANG}_STANDARD_INCLUDE_DIRECTORIES ${CUSTOM_INCLUDE_DIRECTORIES})
endforeach()

add_library(wxSQLite3Lib STATIC IMPORTED)
add_library(wxPDFDocLib STATIC IMPORTED)
if (WIN32)
	set_property(TARGET wxSQLite3Lib PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/wxsqlite3-4.7.4/lib/vc_lib/wxsqlite3.lib")
	set_property(TARGET wxPDFDocLib PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/wxpdfdoc-1.0.1/lib/vc_lib/wxpdfdoc.lib")
endif()

file(MAKE_DIRECTORY ${DOCUMENTS_DIR})


add_executable (${PROJECT_NAME} WIN32 ${SRC_LIST})

target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/resource/EcoBaseBy.rc")
target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/wxpdfdoc-1.0.1/lib/fonts" PUBLIC ${PROJECT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} wxPDFDocLib wxSQLite3Lib)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_NAME})
install(DIRECTORY ${DOCUMENTS_DIR} DESTINATION ${PROJECT_NAME})