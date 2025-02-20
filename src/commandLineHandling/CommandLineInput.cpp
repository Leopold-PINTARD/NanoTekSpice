/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** CommandLineInput
*/

#include "CommandLineInput.hpp"

CommandLineInput::CommandLineInput(std::string intro)
{
    introString = intro;
}

CommandLineInput::~CommandLineInput()
{
}

std::string CommandLineInput::getInput()
{
    std::string input;

    std::cout << introString;
    std::getline(std::cin, input);
    return input;
}

void CommandLineInput::setIntroString(std::string intro)
{
    introString = intro;
}

std::string CommandLineInput::getIntroString()
{
    return introString;
}
