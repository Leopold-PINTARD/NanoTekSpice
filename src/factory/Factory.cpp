/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Factory
*/

#include "factory/Factory.hpp"
#include "components/Pin.hpp"
#include "components/basic/And.hpp"

nts::Factory::Factory()
{
}

nts::Factory::~Factory()
{
}

void nts::Factory::registerBasicComponents()
{
    _map["and"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::And(name);};
}

void nts::Factory::registerComponent(const std::string &name,
    std::function<nts::IComponent*(const std::string&)> func)
{
    _map[name] = func;
}

std::unique_ptr<nts::IComponent>
    nts::Factory::createComponent(const std::string &name)
{
    if (_map.find(name) == _map.end())
        throw std::invalid_argument("Component not found");
    return std::unique_ptr<nts::IComponent>(_map[name](name));
}
