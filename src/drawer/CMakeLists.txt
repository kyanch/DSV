# include(qpdf)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

file(GLOB drawer_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/* )
file(GLOB drawer_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

message(${drawer_SOURCES})

qt_add_executable(drawer
    MANUAL_FINALIZATION
    ${drawer_SOURCES}
    ${drawer_HEADERS}
)

target_include_directories(drawer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(drawer PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

set_target_properties(drawer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    # WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(drawer)
