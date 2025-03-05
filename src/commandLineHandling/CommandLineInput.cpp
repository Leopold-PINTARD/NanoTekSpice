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
#include <algorithm>

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
    tick = 0;
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
    commands.emplace("exit", [this](std::vector<std::unique_ptr
        <nts::IComponent>> &chips) {
        this->commandExit(chips);
    });

    commands.emplace("display", [this](std::vector<std::unique_ptr
        <nts::IComponent>> &chips) {
        this->commandDisplay(chips);
    });
    commands.emplace("simulate", [this](std::vector<std::unique_ptr
        <nts::IComponent>> &chips) {
        this->commandSimulate(chips);
    });
}

void nts::CommandLineInput::handleCommand(std::string input,
    std::vector<std::unique_ptr<nts::IComponent>> &chips)
{
    std::istringstream iss(input);
    std::string command;
    std::string arg;

    iss >> command;
    if (commandChangePinValue(command, chips))
        return;
    if (commands.find(command) == commands.end()) {
        std::cerr << "Invalid Command" << std::endl;
        return;
    }
    commands[command](chips);
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
    <std::unique_ptr<nts::IComponent>> &chips)
{
    (void)chips;
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

void nts::CommandLineInput::commandDisplay(std::vector<std::unique_ptr
    <nts::IComponent>> &chips)
{
    std::vector<std::pair<std::string, std::string>> inputs;
    std::vector<std::pair<std::string, std::string>> outputs;
    Input *input;
    Output *output;

    std::cout << "tick: " << tick << std::endl;
    for (auto &chip : chips) {
        if (dynamic_cast<Input *>(chip.get()) != nullptr) {
            input = dynamic_cast<Input *>(chip.get());
            inputs.push_back(std::make_pair(input->getName(),
                getStatusString(input->compute(0))));
        } else if (dynamic_cast<Output *>(chip.get()) != nullptr) {
            output = dynamic_cast<Output *>(chip.get());
            outputs.push_back(std::make_pair(output->getName(),
                getStatusString(output->compute(0))));
        }
    }
    displayInOrder(inputs, outputs);
}

bool nts::CommandLineInput::tryChangePinValue(std::string value,
    std::string chipType, std::vector<std::unique_ptr<nts::IComponent>> &chips)
{
    IComponent *chipFound;
    Input *input;
    bool found = false;

    for (auto &chip : chips) {
        if (chip->getName() == chipType) {
            found = true;
            chipFound = chip.get();
            break;
        }
    }
    if (!found)
        return false;
    if (dynamic_cast<Input *>(chipFound) != nullptr) {
        input = dynamic_cast<Input *>(chipFound);
        input->changeState(static_cast<nts::Tristate>(value[0] - '0'));
        return true;
    }
    return false;
}

bool nts::CommandLineInput::commandChangePinValue(std::string input,
    std::vector<std::unique_ptr<nts::IComponent>> &chips)
{
    std::size_t pos = input.find('=');
    std::string chip;
    std::string value;

    if (pos == std::string::npos)
        return false;
    chip = input.substr(0, pos);
    value = input.substr(pos + 1);
    if (value != "0" && value != "1" && value != "U")
        return false;
    return tryChangePinValue(value, chip, chips);
}

void nts::CommandLineInput::commandSimulate(std::vector<std::unique_ptr
    <nts::IComponent>> &chips)
{
    tick++;
    for (auto &chip : chips) {
        if (dynamic_cast<Output *>(chip.get()) != nullptr)
            chip->simulate(tick);
    }
}
