
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
find_package(qpdf)

qt_add_executable(DSV
    MANUAL_FINALIZATION
    src/main.cpp
    inc/ui/LayersManager.hpp
    inc/ui/MainWindow.hpp
    inc/draw/Canvas.hpp

    ${_DRAW_SOURCES}
    ${_BASE_SOURCES}
    ${_UI_SOURCES}
    ${_IO_SOURCES}
    src/resource/icon.rc
)

target_link_libraries(DSV PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core qpdf::libqpdf)
target_compile_definitions(DSV PUBLIC POINTERHOLDER_TRANSITION=0)

set_target_properties(DSV PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(DSV)