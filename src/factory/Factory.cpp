/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Factory
*/

#include "factory/Factory.hpp"
#include "components/Pin.hpp"
#include "components/basic/And.hpp"
#include "components/basic/Nand.hpp"
#include "components/basic/Not.hpp"
#include "components/basic/Xor.hpp"
#include "components/basic/Or.hpp"
#include "components/basic/Nor.hpp"
#include "../../include/components/special/True.hpp"
#include "../../include/components/special/False.hpp"
#include "../../include/components/special/Input.hpp"
#include "../../include/components/special/Output.hpp"
#include "../../include/components/special/Clock.hpp"
#include "components/advanced/Chip4001.hpp"

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
    registerSpecialComponents();
    registerAdvancedComponents();
}

nts::Factory::~Factory()
{
}

void nts::Factory::registerSpecialComponents()
{
    _map["input"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Input(name);
    };
    _map["output"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Output(name);
    };
    _map["clock"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Clock(name);
    };
    _map["true"] = [](const std::string &name) -> nts::IComponent* {
        return new class nts::True(name);
    };
    _map["false"] = [](const std::string &name) -> nts::IComponent* {
        return new class nts::False(name);
    };
}

void nts::Factory::registerBasicComponents()
{
    _map["and"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::And(name);
    };
    _map["not"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Not(name);
    };
    _map["xor"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Xor(name);
    };
    _map["or"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Or(name);
    };
    _map["nand"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Nand(name);
    };
    _map["nor"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Nor(name);
    };
}

void nts::Factory::registerAdvancedComponents()
{
    _map["4001"] = [](const std::string &name) -> nts::IComponent* {
        return new nts::Chip4001(name);
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
