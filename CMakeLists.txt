# CMakeList.txt : CMake project for EcoBaseBy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.2)

set(CXX_)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("EcoBaseBy" VERSION 0.1.1)


include("${CMAKE_CURRENT_SOURCE_DIR}/3rd/CMakeLists.txt")
include("${CMAKE_CURRENT_SOURCE_DIR}/resource/CMakeLists.txt")
include("${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt")

set(DOCUMENTS_DIR "${CMAKE_CURRENT_BINARY_DIR}/Documents")

file(MAKE_DIRECTORY ${DOCUMENTS_DIR})


add_executable (${PROJECT_NAME} WIN32 ${SRC_LIST})
if(WIN32)
target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/resource/EcoBaseBy.rc")
    foreach(LANG C CXX RC)
        set(CMAKE_${LANG}_STANDARD_INCLUDE_DIRECTORIES ${CUSTOM_INCLUDE_DIRECTORIES})
    endforeach()
    target_link_libraries(${PROJECT_NAME} PRIVATE wxWidgets wxSQLite3Lib wxPDFDocLib)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE wxWidgets "/usr/local/lib/lib${wxSQLiteLibName}.a" "/usr/local/lib/lib${wxPDFLibName}.a")
endif()
target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/3rd/wxpdfdoc/lib/fonts" PRIVATE ${PROJECT_BINARY_DIR})


install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(DIRECTORY ${DOCUMENTS_DIR} DESTINATION .)
if(UNIX)
    set(CPACK_GENERATOR TGZ)
else()
    set(CPACK_GENERATOR ZIP)
endif()
set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_ARCHIVE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")
include(CPack)
