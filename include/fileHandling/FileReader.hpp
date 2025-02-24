/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** FileReader
*/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

class FileReader {
    public:
        class FileError : public std::exception {
            public:
                FileError(std::string message);
                ~FileError();
                const char *what() const throw();
            private:
                std::string _message;
        };

        FileReader(std::string path = "");
        ~FileReader();
        std::string read(std::string filename);
        std::string read();
        std::vector<std::string> read(std::string filename, char delim);
        std::vector<std::string> read(char delim);
        void setFilePath(std::string path);
        std::string getFilePath();
    protected:
    private:
        std::string filePath;
};
