/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser
*/

#include "../../include/fileHandling/Parser.hpp"
#include "../../include/fileHandling/FileReader.hpp"
#include <sstream>

nts::Parser::ParserError::ParserError(std::string message)
{
    _message = message;
}

nts::Parser::ParserError::~ParserError()
{
}

const char *nts::Parser::ParserError::what() const throw()
{
    return _message.c_str();
}

// --------------------------------------------------------------------------

nts::Parser::Parser(std::string path)
{
    _path = path;
    readContent();
}

nts::Parser::~Parser()
{
}

void nts::Parser::readContent()
{
    FileReader reader(_path);

    try {
        _content = reader.read('\n');
        removeComments();
        removeTrallingSpaces();
        removeEmptyLines();
        replaceTabs();
        handleSection();
    } catch (const std::exception &e) {
        throw ParserError(e.what());
    }
}

void nts::Parser::removeComments()
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

void nts::Parser::removeTrallingSpaces()
{
    auto it = _content.begin();
    while (it != _content.end()) {
        while (!it->empty() && (*it)[it->size() - 1] == ' ') {
            *it = it->substr(0, it->size() - 1);
        }
        it++;
    }
}

void nts::Parser::removeEmptyLines()
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

void nts::Parser::replaceTabs()
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

void nts::Parser::handleSection()
{
    auto it = _content.begin();
    bool chipset = false;
    bool links = false;

    while (it != _content.end()) {
        if (*it == ".chipsets:") {
            chipset = true;
            try {
                it = handleDotChipset(++it);
            } catch (const std::exception &e) {
                throw ParserError(e.what());
            }
        } else if (*it == ".links:") {
            if (!chipset)
                throw ParserError(".links before .chipset");
            links = true;
            try {
                it = handleDotLinks(++it);
            } catch (const std::exception &e) {
                throw ParserError(e.what());
            }
        } else
            throw ParserError("Section not known");
    }
    if (!chipset || !links)
        throw ParserError("Missing section");
}

std::vector<std::string>::iterator
    nts::Parser::handleDotChipset(std::vector<std::string>::iterator it)
{
    std::string chip;
    std::string name;
    std::string trash;
    std::stringstream ss;

    while (it != _content.end() && !it->empty() && it->front() != '.') {
        ss.clear();
        ss.str(*it);
        ss >> chip >> name >> trash;
        if (!trash.empty() || chip.empty() || name.empty())
            throw ParserError("chipset not valid");
        try {
            chips.push_back(factory.createComponent(chip, name));
        } catch (const std::exception &e) {
            throw nts::Factory::FactoryError(e.what());
        }
        it++;
    }
    return it;
}

std::unique_ptr<nts::IComponent>& nts::Parser::getChip(std::string name)
{
    for (auto &chip : chips) {
        if (chip->getName() == name)
            return chip;
    }
    throw ParserError("Chip not found");
}

nts::Parser::linkSectionLine nts::Parser::getLinkSectionLine(std::string line)
{
    linkSectionLine link;
    std::string temp1, temp2;
    std::stringstream ss(line);
    std::getline(ss, temp1, ' ');
    std::getline(ss, temp2);
    size_t stop1 = temp1.find(':');
    size_t stop2 = temp2.find(':');

    if (stop1 == std::string::npos || stop2 == std::string::npos)
        throw ParserError("Invalid link format");
    link.chipSrc = temp1.substr(0, stop1);
    link.pinSrc = std::stoi(temp1.substr(stop1 + 1));
    link.chipDest = temp2.substr(0, stop2);
    link.pinDest = std::stoi(temp2.substr(stop2 + 1));
    return link;
}

std::vector<std::string>::iterator
    nts::Parser::handleDotLinks(std::vector<std::string>::iterator it)
{
    Parser::linkSectionLine line;
    std::unique_ptr<nts::IComponent> *chip1 = nullptr;
    std::unique_ptr<nts::IComponent> *chip2 = nullptr;

    while (it != _content.end() && !it->empty() && it->front() != '.') {
        try {
            line = getLinkSectionLine(*it);
            chip1 = &getChip(line.chipSrc);
            chip2 = &getChip(line.chipDest);
        } catch (const std::exception &e) {
            throw ParserError(e.what());
        }
        (*chip1)->setLink(line.pinSrc - 1, **chip2, line.pinDest - 1);
        it++;
    }
    return it;
}

std::vector<std::unique_ptr<nts::IComponent>> nts::Parser::getChips()
{
    return std::move(chips);
}
