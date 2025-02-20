/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser
*/

#pragma once

#include <iostream>
#include <vector>

class Parser {
    public:
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

    protected:
    private:
        std::string _path;
        
};
