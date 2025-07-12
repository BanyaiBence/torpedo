add_library(Table
        Table.c
        Table.h
)


target_include_directories(Table
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Table PRIVATE SDL3::SDL3)
target_link_libraries(Table PRIVATE Graphics)


set_target_properties(Table PROPERTIES
        VERSION 1.0.0
        SOVERSION 1
)
