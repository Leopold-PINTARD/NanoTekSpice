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
#include <unistd.h>

Test(parser_tests, constructor_test)
{
    nts::Parser parser("test_circuit.nts");
}

Test(parser_tests, parse_valid_file)
{
    nts::Parser parser("test_circuit.nts");
    std::vector<std::string> content = {
        ".chipsets:",
        "",
        "input\ta",
        "output s",
        "and gate",
        ".links:",
        "a:1 gate:1",
        "gate:3 s:1"
    };

    parser.setContent(content);
    auto chips = parser.getChips();
    cr_assert_eq(chips.size(), 3);
}

Test(parser_tests, handle_comments)
{
    nts::Parser parser("test_circuit.nts");
    std::vector<std::string> content = {
        ".chipsets:",
        "input a  # This is a comment",
        "output s # Another comment",
        ".links:",
        "a:1 s:1  # Connection"
    };

    parser.setContent(content);
    auto chips = parser.getChips();
    cr_assert_eq(chips.size(), 2);
}

Test(parser_tests, invalid_file_path)
{
    nts::Parser parser("nonexistent.nts");
    cr_assert_throw(parser.readContent(), nts::Parser::ParserError);
}

Test(parser_tests, missing_sections_link)
{
    nts::Parser parser("test_circuit.nts");
    std::vector<std::string> content = {
        ".chipsets:",
        "input a",
        "output s"
    };

    cr_assert_throw(parser.setContent(content), nts::Parser::ParserError);
}

Test(parser_tests, missing_sections_chipset)
{
    nts::Parser parser("test_circuit.nts");
    std::vector<std::string> content = {
        ".links:",
        "a:1 s:1"
    };

    cr_assert_throw(parser.setContent(content), nts::Parser::ParserError);
}

Test(parser_tests, section_not_known)
{
    nts::Parser parser("test_circuit.nts");
    std::vector<std::string> content = {
        ".chipsets:",
        "input a",
        "output s",
        ".unknown:",
        "a:1 s:1"
    };

    cr_assert_throw(parser.setContent(content), nts::Parser::ParserError);
}

Test(parser_tests, invalid_component)
{
    nts::Parser parser("test_circuit.nts");
    std::vector<std::string> content = {
        ".chipsets:",
        "input a",
        "output s",
        ".links:",
        "a:1 s:1",
        "invalid:1 s:1"
    };

    cr_assert_throw(parser.setContent(content), nts::Parser::ParserError);
}

Test(parser_tests, duplicate_component_names)
{
    nts::Parser parser("test_circuit.nts");
    std::vector<std::string> content = {
        ".chipsets:",
        "input a",
        "output a",
        ".links:",
        "a:1 a:1"
    };

    cr_assert_throw(parser.setContent(content), nts::Parser::ParserError);
}

Test(parser_tests, invalid_link_format)
{
    nts::Parser parser("test_circuit.nts");
    std::vector<std::string> content = {
        ".chipsets:",
        "input a",
        "output s",
        ".links:",
        "a:1 s1"
    };

    cr_assert_throw(parser.setContent(content), nts::Parser::ParserError);
}
