add_executable(ut number_multiplication_test.c)
target_link_libraries(ut PRIVATE
    cmocka::cmocka
    Number_Multiplication
    project_warnings
)

add_executable(fuzz_test number_multiplication_fuzz_test.c)
target_link_libraries(fuzz_test PRIVATE
    Number_Multiplication
    project_warnings
)

target_compile_options(fuzz_test
    PRIVATE
    -fsanitize=fuzzer
)

target_link_options(fuzz_test PRIVATE -fsanitize=fuzzer)
