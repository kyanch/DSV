include(glm)

file(GLOB GEOMETRY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
add_library(geometry ${GEOMETRY_SOURCES})
target_link_libraries(geometry PRIVATE glm)
target_include_directories(geometry 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

