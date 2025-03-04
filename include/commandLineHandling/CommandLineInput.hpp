/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** CommandLineInput
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include "../components/IComponent.hpp"

namespace nts {
    class CommandLineInput {
        public:
            class InputError : public std::exception {
                public:
                    InputError(std::string const &message);
                    ~InputError();
                    const char *what() const noexcept override;
                private:
                    std::string _message;
            };
            CommandLineInput(std::string intro = "");
            ~CommandLineInput();
            bool end;
            std::string getInputNotParsed();
            void setIntroString(std::string intro);
            std::string getIntroString();
            void handleInput(std::vector<std::unique_ptr<nts::IComponent>>
                &chips);
            void handleCommand(std::string input,
                std::vector<std::unique_ptr<nts::IComponent>> &chips);
            void registerCommand();
            void commandExit(std::vector<std::unique_ptr<nts::IComponent>>
                &chips, std::vector<std::string> args);
            void commandDisplay(std::vector<std::unique_ptr<nts::IComponent>>
                &chips, std::vector<std::string> args);
            void displayInOrder(std::vector<std::pair<std::string,
                std::string>> inputs, std::vector<std::pair<std::string,
                std::string>> outputs);
        protected:
        private:
            std::string introString;
            std::unordered_map<std::string,
                std::function<void(std::vector<std::unique_ptr<nts::
                IComponent>> &chips, std::vector<std::string>)>> commands;
    };
}
