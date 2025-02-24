/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** FileReader
*/

#include "fileHandling/FileReader.hpp"

FileReader::FileError::FileError(std::string message)
{
    _message = message;
}

FileReader::FileError::~FileError()
{
}

const char *FileReader::FileError::what() const throw()
{
    return _message.c_str();
}

// ---------------------------- END CLASS THROW ----------------------------

FileReader::FileReader(std::string path)
{
    filePath = path;
}

FileReader::~FileReader()
{
}

std::string FileReader::read(std::string filename)
{
    std::ifstream file;
    std::string line;
    std::string content;

    file.open(filename);
    if (!file.is_open()) {
        throw FileError("File not found");
    }
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    return content;
}

std::string FileReader::read()
{
    return read(filePath);
}

std::vector<std::string> FileReader::read(std::string filename, char delim)
{
    std::ifstream file;
    std::string line;
    std::vector<std::string> content;

    file.open(filename);
    if (!file.is_open()) {
        throw FileError("File not found");
    }
    while (std::getline(file, line, delim)) {
        content.push_back(line);
    }
    file.close();
    return content;
}

std::vector<std::string> FileReader::read(char delim)
{
    return read(filePath, delim);
}

void FileReader::setFilePath(std::string path)
{
    filePath = path;
}

std::string FileReader::getFilePath()
{
    return filePath;
}
