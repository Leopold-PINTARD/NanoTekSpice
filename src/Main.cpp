/*
** EPITECH PROJECT, 2025
** Main file for the project to compile
** File description:
** Main
*/

#include <unistd.h>
#include "../include/fileHandling/Parser.hpp"
#include "../include/commandLineHandling/CommandLineInput.hpp"
#include <iostream>

void printUsage()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./nanotekspice [file.nts]" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tfile.nts\tfile describing the circuit" << std::endl;
}

int startCommandLine(std::vector<std::unique_ptr<nts::IComponent>> chips)
{
    nts::CommandLineInput input("> ");

    while (input.end == false) {
        try {
            input.handleInput(chips);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 84;
        }
    }
    return 0;
}

int startProgram(std::string path)
{
    nts::Parser parser(path);

    try {
        parser.readContent();
        auto chips = parser.getChips();
        return startCommandLine(std::move(chips));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printUsage();
        return 84;
    }
    return startProgram(argv[1]);
}
