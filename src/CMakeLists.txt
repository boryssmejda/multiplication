add_library(Number_Multiplication
    number_multiplication.c
    number_multiplication.h
)

target_include_directories(Number_Multiplication
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

target_link_libraries(Number_Multiplication PUBLIC project_warnings)
