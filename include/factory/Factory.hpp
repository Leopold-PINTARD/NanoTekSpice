/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Factory
*/

#pragma once

#include <map>
#include <functional>
#include <iostream>
#include <memory>
#include "../components/IComponent.hpp"

namespace nts {
    class Factory {
        public:
            Factory();
            ~Factory();
            class FactoryError : public std::exception {
                public:
                    FactoryError(std::string message);
                    ~FactoryError();
                    const char *what() const throw();
                private:
                    std::string _message;
            };
            std::unique_ptr<IComponent> createComponent(const std::string
                &comp, const std::string &name);
            void registerComponent(const std::string &name,
                std::function<nts::IComponent*(const std::string&)> func);
            void registerBasicComponents();
            void registerAdvancedComponents();
            void registerSpecialComponents();
        protected:
        private:
        std::unordered_map<std::string,
            std::function<nts::IComponent*(const std::string&)>> _map;
    };
}
