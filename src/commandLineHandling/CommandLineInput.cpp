/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** CommandLineInput
*/

#include "commandLineHandling/CommandLineInput.hpp"
#include <iostream>
#include <sstream>

nts::CommandLineInput::InputError::InputError(std::string const &message)
{
    _message = message;
}

nts::CommandLineInput::InputError::~InputError()
{
}

const char *nts::CommandLineInput::InputError::what() const noexcept
{
    return _message.c_str();
}

// ----------------------------------------------------------------------------

nts::CommandLineInput::CommandLineInput(std::string intro)
{
    introString = intro;
    end = false;
    registerCommand();
}

nts::CommandLineInput::~CommandLineInput()
{
}

std::string nts::CommandLineInput::getInputNotParsed()
{
    std::string input;

    std::cout << introString;
    std::getline(std::cin, input);
    if (std::cin.eof())
        end = true;
    return input;
}

void nts::CommandLineInput::setIntroString(std::string intro)
{
    introString = intro;
}

std::string nts::CommandLineInput::getIntroString()
{
    return introString;
}

void nts::CommandLineInput::registerCommand()
{
}

void nts::CommandLineInput::handleCommand(std::string input,
    std::vector<std::unique_ptr<nts::IComponent>> &chips)
{
    std::vector<std::string> args;
    std::istringstream iss(input);
    std::string word;

    while (iss >> word) {
        args.push_back(word);
    }
    if (args.size() == 0) {
        std::cerr << "No command entered" << std::endl;
        return;
    }
    if (commands.find(args[0]) == commands.end()) {
        std::cerr << "Command not found" << std::endl;
        return;
    }
    try {
        commands[args[0]](chips, args);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void nts::CommandLineInput::handleInput(std::vector
    <std::unique_ptr<nts::IComponent>> &chips)
{
    std::string input = getInputNotParsed();

    if (input.starts_with("exit")) {
        end = true;
        return;
    }
    if (end == true)
        return;
    handleCommand(input, chips);
}