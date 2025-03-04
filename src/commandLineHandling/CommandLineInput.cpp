/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** CommandLineInput
*/

#include "commandLineHandling/CommandLineInput.hpp"
#include "components/special/Input.hpp"
#include "components/special/Output.hpp"
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
    commands["exit"] = std::bind(&CommandLineInput::commandExit, this,
        std::placeholders::_1, std::placeholders::_2);
    commands["display"] = std::bind(&CommandLineInput::commandDisplay, this,
        std::placeholders::_1, std::placeholders::_2);
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

    if (end == true)
        return;
    handleCommand(input, chips);
}

void nts::CommandLineInput::commandExit(std::vector
    <std::unique_ptr<nts::IComponent>> &chips, std::vector<std::string> args)
{
    (void)chips;
    if (args.size() != 1)
        throw InputError("exit: invalid number of arguments");
    end = true;
}

std::string getStatusString(nts::Tristate state)
{
    if (state == nts::Tristate::True)
        return "1";
    if (state == nts::Tristate::False)
        return "0";
    return "U";
}

void nts::CommandLineInput::displayInOrder(std::vector
    <std::pair<std::string, std::string>> inputs, std::vector
    <std::pair<std::string, std::string>> outputs)
{
    std::sort(inputs.begin(), inputs.end(), [](const std::pair<std::string,
        std::string> &a, const std::pair<std::string, std::string> &b) {
        return a.first < b.first;
    });
    std::sort(outputs.begin(), outputs.end(), [](const std::pair<std::string,
        std::string> &a, const std::pair<std::string, std::string> &b) {
        return a.first < b.first;
    });
    std::cout << "input(s):" << std::endl;
    for (const auto &input : inputs) {
        std::cout << "\t" << input.first << ": " << input.second << std::endl;
    }
    std::cout << "output(s):" << std::endl;
    for (const auto &output : outputs) {
        std::cout << "\t" << output.first << ": " << output.second << std::endl;
    }
}

void nts::CommandLineInput::commandDisplay(std::vector
    <std::unique_ptr<nts::IComponent>> &chips, std::vector<std::string> args)
{
    std::vector<std::pair<std::string, std::string>> inputs;
    std::vector<std::pair<std::string, std::string>> outputs;
    Input *input;
    Output *output;

    if (args.size() != 1)
        throw InputError("display: invalid number of arguments");
    for (auto &chip : chips) {
        if (dynamic_cast<Input *>(chip.get()) != nullptr) {
            input = dynamic_cast<Input *>(chip.get());
            inputs.push_back(std::make_pair(input->getName(),
                getStatusString(input->getState())));
        } else if (dynamic_cast<Output *>(chip.get()) != nullptr) {
            output = dynamic_cast<Output *>(chip.get());
            outputs.push_back(std::make_pair(output->getName(),
                getStatusString(output->getState())));
        }
    }
    displayInOrder(inputs, outputs);
}
