/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Factory
*/

#include "factory/Factory.hpp"
#include "components/Pin.hpp"
#include "components/basic/And.hpp"
#include "components/basic/Not.hpp"
#include "components/basic/Xor.hpp"
#include "../../include/components/special/True.hpp"
#include "../../include/components/special/False.hpp"
#include "../../include/components/special/Input.hpp"

nts::Factory::FactoryError::FactoryError(std::string message)
{
    _message = message;
}

nts::Factory::FactoryError::~FactoryError()
{
}

const char *nts::Factory::FactoryError::what() const throw()
{
    return _message.c_str();
}

nts::Factory::Factory()
{
    registerBasicComponents();
}

nts::Factory::~Factory()
{
}

void nts::Factory::registerBasicComponents()
{
    _map["input"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Input(name);
    };
    _map["output"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Input(name);
    };
    _map["and"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::And(name);
    };
    _map["not"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Not(name);
    };
    _map["xor"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Xor(name);
    };
}

void nts::Factory::registerComponent(const std::string &name,
    std::function<nts::IComponent*(const std::string&)> func)
{
    _map[name] = func;
}

std::unique_ptr<nts::IComponent> nts::Factory::createComponent(const
    std::string &comp, const std::string &name)
{
    if (_map.find(comp) == _map.end())
        throw FactoryError("Component type not found: " + comp);
    return std::unique_ptr<nts::IComponent>(_map[comp](name));
}
