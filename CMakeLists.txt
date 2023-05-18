cmake_minimum_required(VERSION 3.5)

project(GunStore VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Charts)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/View)
include_directories(${PROJECT_SOURCE_DIR}/src/View/ViewElement)
include_directories(${PROJECT_SOURCE_DIR}/src/View/MenuAdmin)
include_directories(${PROJECT_SOURCE_DIR}/src/View/Delegates)
include_directories(${PROJECT_SOURCE_DIR}/src/View/Interface)
include_directories(${PROJECT_SOURCE_DIR}/src/ViewModel)
include_directories(${PROJECT_SOURCE_DIR}/src/Model)
include_directories(${PROJECT_SOURCE_DIR}/src/Model/base)
include_directories(${PROJECT_SOURCE_DIR}/src/Mediator)
include_directories(${PROJECT_SOURCE_DIR}/src/ViewModel/base)

file(GLOB RESOURCES "resources/*.qrc")
file(GLOB VIEW "src/View/*.cpp" "src/View/*.h" "src/View/MenuAdmin/*.cpp" "src/View/MenuAdmin/*.h" "src/View/ViewElement/*.cpp" "src/View/ViewElement/*.h" "src/View/Delegates/*.cpp" "src/View/Delegates/*.h" "src/View/Interface/*.h")
file(GLOB UI_HEADERS "src/View/*.ui" "src/View/MenuAdmin/*.ui" "src/View/ViewElement/*.ui")
file(GLOB VIEWMODEL "src/ViewModel/*.cpp" "src/ViewModel/*.h" "src/ViewModel/base/*.cpp" "src/ViewModel/base/*.h")
file(GLOB MODEL "src/Model/*.cpp" "src/Model/*.h" "src/Model/base/*.cpp" "src/Model/base/*.h")

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources/appicon.rc")

set(PROJECT_SOURCES
    src/main.cpp
    src/connectionhandler.h
    src/connectionhandler.cpp
    src/LayoutState.h
    src/printer.h
    src/printer.cpp
    src/filter.h
    src/filter.cpp
    ${RESOURCES}
    ${VIEW}
    ${VIEWMODEL}
    ${MODEL}
    ${UI_HEADERS}
    ${APP_ICON_RESOURCE_WINDOWS}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GunStore
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GunStore APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GunStore SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GunStore
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GunStore PRIVATE Qt6::Sql)
target_link_libraries(GunStore PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GunStore PRIVATE Qt6::PrintSupport)
target_link_libraries(GunStore PRIVATE Qt6::Gui)
target_link_libraries(GunStore PRIVATE Qt6::Charts)
target_link_libraries(GunStore PRIVATE ${PROJECT_SOURCE_DIR}/libmysql.dll)

set_target_properties(GunStore PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GunStore
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GunStore)
endif()
