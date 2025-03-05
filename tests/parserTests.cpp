/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "fileHandling/Parser.hpp"
#include <fstream>

static void createTestFile(const std::string& content)
{
    std::ofstream file("test_circuit.nts");
    file << content;
    file.close();
}

static void cleanupTestFile()
{
    std::remove("test_circuit.nts");
}

Test(parser_tests, constructor_test)
{
    nts::Parser parser("test_circuit.nts");
}

Test(parser_tests, parse_valid_file)
{
    createTestFile(
        ".chipsets:\n\n"
        "input\ta\n"
        "output s\n"
        "and gate\n"
        ".links:\n"
        "a:1 gate:1\n"
        "gate:3 s:1\n"
    );

    nts::Parser parser("test_circuit.nts");
    parser.readContent();
    auto chips = parser.getChips();

    cr_assert_eq(chips.size(), 3);
    cleanupTestFile();
}

Test(parser_tests, handle_comments)
{
    createTestFile(
        ".chipsets:\n"
        "input a  # This is a comment\n"
        "output s # Another comment\n"
        ".links:\n"
        "a:1 s:1  # Connection\n"
    );

    nts::Parser parser("test_circuit.nts");
    parser.readContent();
    auto chips = parser.getChips();
    
    cr_assert_eq(chips.size(), 2);
    cleanupTestFile();
}

Test(parser_tests, invalid_file_path)
{
    nts::Parser parser("nonexistent.nts");
    cr_assert_throw(parser.readContent(), nts::Parser::ParserError);
}

Test(parser_tests, missing_sections_link)
{
    createTestFile(
        ".chipsets:\n"
        "input a\n"
        "output s\n"
    );

    nts::Parser parser("test_circuit.nts");
    cr_assert_throw(parser.readContent(), nts::Parser::ParserError);
    cleanupTestFile();
}

Test(parser_tests, missing_sections_chipset)
{
    createTestFile(
        ".links:\n"
        "a:1 s:1\n"
    );

    nts::Parser parser("test_circuit.nts");
    cr_assert_throw(parser.readContent(), nts::Parser::ParserError);
    cleanupTestFile();
}

Test(parser_tests, section_not_known)
{
    createTestFile(
        ".chipsets:\n"
        "input a\n"
        "output s\n"
        ".unknown:\n"
        "a:1 s:1\n"
    );

    nts::Parser parser("test_circuit.nts");
    cr_assert_throw(parser.readContent(), nts::Parser::ParserError);
    cleanupTestFile();
}

Test(parser_tests, invalid_component)
{
    createTestFile(
        ".chipsets:\n"
        "invalid a\n"
        ".links:\n"
        "a:1 s:1\n"
    );

    nts::Parser parser("test_circuit.nts");
    cr_assert_throw(parser.readContent(), nts::Parser::ParserError);
    cleanupTestFile();
}

Test(parser_tests, duplicate_component_names)
{
    createTestFile(
        ".chipsets:\n"
        "input a\n"
        "output a\n"
        ".links:\n"
        "a:1 a:1\n"
    );

    nts::Parser parser("test_circuit.nts");
    try {
        parser.readContent();
    } catch (const nts::Parser::ParserError& e) {
        cr_assert_str_eq(e.what(), "chipset not valid");
    }
    cleanupTestFile();
}

Test(parser_tests, invalid_link_format)
{
    createTestFile(
        ".chipsets:\n"
        "input a\n"
        "output s\n"
        ".links:\n"
        "a-1 s-1\n"
    );

    nts::Parser parser("test_circuit.nts");
    cr_assert_throw(parser.readContent(), nts::Parser::ParserError);
    cleanupTestFile();
}
