add_executable(ut number_multiplication_test.c)

target_link_libraries(ut PRIVATE
    cmocka::cmocka
    Number_Multiplication
    project_warnings
)
