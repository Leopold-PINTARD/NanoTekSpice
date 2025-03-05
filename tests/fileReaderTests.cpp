/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** FileReader tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "fileHandling/FileReader.hpp"
#include <fstream>

Test(fileReader_tests, constructor_test)
{
    FileReader reader("test.txt");
    cr_assert_eq(reader.getFilePath(), "test.txt");
}

Test(fileReader_tests, set_file_path)
{
    FileReader reader;
    reader.setFilePath("test.txt");
    cr_assert_eq(reader.getFilePath(), "test.txt");
}

Test(fileReader_tests, read_existing_file)
{
    std::ofstream testFile("temp_test.txt");
    testFile << "Test content\nSecond line";
    testFile.close();

    FileReader reader("temp_test.txt");
    std::string content = reader.read();
    cr_assert_eq(content, "Test content\nSecond line\n");
    std::remove("temp_test.txt");
}

Test(fileReader_tests, read_with_delimiter)
{
    std::ofstream testFile("temp_test.txt");
    testFile << "First,Second,Third";
    testFile.close();

    FileReader reader("temp_test.txt");
    std::vector<std::string> content = reader.read(',');
    cr_assert_eq(content.size(), 3);
    cr_assert_eq(content[0], "First");
    cr_assert_eq(content[1], "Second");
    cr_assert_eq(content[2], "Third");

    std::remove("temp_test.txt");
}

Test(fileReader_tests, read_nonexistent_file)
{
    FileReader reader("nonexistent.txt");
    try {
        reader.read();
        cr_assert_fail("Expected FileError exception was not thrown");
    } catch (const FileReader::FileError& e) {
        cr_assert_str_eq(e.what(), "File not found");
    }
}

Test(fileReader_tests, read_empty_file)
{
    std::ofstream testFile("empty_test.txt");
    testFile.close();

    FileReader reader("empty_test.txt");
    std::string content = reader.read();
    cr_assert_eq(content, "");

    std::remove("empty_test.txt");
}

Test(fileReader_tests, read_with_alternate_filepath)
{
    std::ofstream testFile("alt_test.txt");
    testFile << "Alternative content";
    testFile.close();

    FileReader reader;
    std::string content = reader.read("alt_test.txt");
    cr_assert_eq(content, "Alternative content\n");

    std::remove("alt_test.txt");
}