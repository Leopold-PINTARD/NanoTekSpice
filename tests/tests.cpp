/*
** EPITECH PROJECT, 2025
** repo-c++
** File description:
** tests
*/

#include <iostream>
#include <fstream>
#include <string>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

std::string format_output(const std::string& expected, const std::string& actual) {
    std::string separator = "\033[1;34m--------------------\033[0m\n";
    std::string formatted_output = separator +
        "\033[1;32mExpected:\033[0m\n" + expected + "\n" +
        separator +
        "\033[1;31mActual:\033[0m\n" + actual + "\n" +
        separator;
    return formatted_output;
}

Test(sample_test_suite, sample_test_case)
{
    int a = 5;
    int b = 10;
    int result = a + b;

    std::string formatted_output = format_output("15", std::to_string(result));
    cr_assert_eq(result, 15, "%s", formatted_output.c_str());
}

Test(output_test_suite, hello_world_test, .init = redirect_all_stdout)
{
    std::cout << "Hello, World!" << std::endl;
    std::string formatted_output = format_output("Hello, World!\n", "Hello, World!");
    cr_assert_stdout_eq_str("Hello, World!\n", "%s", formatted_output.c_str());
}

// Test(file_output_test_suite, file_content_test, .init = redirect_all_stdout)
// {
//     std::ifstream file("test_file.txt");
//     std::string file_content((std::istreambuf_iterator<char>(file)),
//         std::istreambuf_iterator<char>());
//     std::string expected_content = "File content to compare\n";

//     std::string formatted_output = format_output(expected_content, file_content);
//     cr_assert_eq(file_content, expected_content, "%s", formatted_output.c_str());
// }
