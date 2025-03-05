/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Not
*/

#include "components/basic/Not.hpp"

nts::Not::Not(std::string name)
{
    this->compName = name;
    pins.clear();
    pins.emplace_back(Pin::Input);
    pins.emplace_back(Pin::Output);
}

nts::Not::~Not()
{
}

nts::Tristate nts::Not::compute(size_t pin)
{
    nts::Tristate result;

    if (this->pins[pin].getType() == Pin::Input)
        return this->pins[pin].updatePinStatus();
    if (this->pins[0].getStatus() == Undefined)
        result = Undefined;
    else
        result = this->pins[0].getStatus() == False ? True : False;
    this->pins[pin].setStatus(result);
    return result;
}
