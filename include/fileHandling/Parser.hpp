/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "../components/IComponent.hpp"
#include "../factory/Factory.hpp"

namespace nts {
    class Parser {
        public:
            struct linkSectionLine {
                std::string chipSrc;
                std::size_t pinSrc;
                std::string chipDest;
                std::size_t pinDest;
            };
            class ParserError : public std::exception {
                public:
                    ParserError(std::string message);
                    ~ParserError();
                    const char *what() const throw();
                private:
                    std::string _message;
            };

            Parser(std::string path);
            ~Parser();
            void readContent();
            void removeComments();
            void removeEmptyLines();
            void replaceTabs();
            void removeTrallingSpaces();
            void setChipsets();
            void setLinks();
            std::vector<std::string> _content;
            void handleSection();
            std::vector<std::string>::iterator
                handleDotChipset(std::vector<std::string>::iterator it);
            std::vector<std::string>::iterator
                handleDotLinks(std::vector<std::string>::iterator it);
            std::unique_ptr<nts::IComponent>& getChip(std::string name);
            linkSectionLine getLinkSectionLine(std::string line);
            std::vector<std::unique_ptr<nts::IComponent>> getChips();
        protected:
        private:
            std::string _path;
            std::vector<std::unique_ptr<nts::IComponent>> chips;
            nts::Factory factory;

    };
}
