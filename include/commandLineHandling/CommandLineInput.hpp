/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** CommandLineInput
*/

#pragma once

#include <iostream>

class CommandLineInput {
    public:
        CommandLineInput(std::string intro = "");
        ~CommandLineInput();
        std::string getInput();
        void setIntroString(std::string intro);
        std::string getIntroString();
    protected:
    private:
        std::string introString;
};
