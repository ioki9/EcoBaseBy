# CMakeList.txt : CMake project for EcoBaseBy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("EcoBaseBy" VERSION 0.1)
include("${CMAKE_CURRENT_SOURCE_DIR}/resource/CMakeLists.txt")
include("${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt")
include("${CMAKE_CURRENT_SOURCE_DIR}/3rd/CMakeLists.txt")
#add_subdirectory(3rd)
set(DOCUMENTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/Documents)

file(MAKE_DIRECTORY ${DOCUMENTS_DIR})


add_executable (${PROJECT_NAME} WIN32 ${SRC_LIST})

target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/resource/EcoBaseBy.rc")
target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/3rd/wxpdfdoc/lib/fonts" PUBLIC ${PROJECT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${wxWidgets_LIBRARIES} wxPDFDocLib wxSQLite3Lib)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_NAME})
install(DIRECTORY ${DOCUMENTS_DIR} DESTINATION ${PROJECT_NAME})