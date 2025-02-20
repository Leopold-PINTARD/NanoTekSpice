/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser
*/

#include "Parser.hpp"
#include "FileReader.hpp"

Parser::Parser(std::string path)
{
    _path = path;
    readContent();
}

Parser::~Parser()
{
}

void Parser::readContent()
{
    FileReader reader(_path);

    _content = reader.read('\n');
    removeComments();
    removeTrallingSpaces();
    removeEmptyLines();
    replaceTabs();
}

void Parser::removeComments()
{
    auto it = _content.begin();
    while (it != _content.end()) {
        for (size_t i = 0; i < it->size(); i++) {
            if ((*it)[i] == '#') {
                *it = it->substr(0, i);
                break;
            }
        }
        it++;
    }
}

void Parser::removeTrallingSpaces()
{
    auto it = _content.begin();
    while (it != _content.end()) {
        while (!it->empty() && (*it)[it->size() - 1] == ' ') {
            *it = it->substr(0, it->size() - 1);
        }
        it++;
    }
}

void Parser::removeEmptyLines()
{
    auto it = _content.begin();
    while (it != _content.end()) {
        if (it->empty()) {
            it = _content.erase(it);
        } else {
            it++;
        }
    }
}

void Parser::replaceTabs()
{
    for (std::vector<std::string>::iterator
        it = _content.begin(); it != _content.end(); it++) {
        for (size_t i = 0; i < it->size(); i++) {
            if ((*it)[i] == '\t') {
                (*it)[i] = ' ';
            }
        }
    }
}
