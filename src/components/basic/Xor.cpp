/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Xor
*/

#include "components/basic/Xor.hpp"

nts::Xor::Xor(std::string name)
{
    this->compName = name;
}

nts::Xor::~Xor()
{
}

nts::Tristate nts::Xor::compute(size_t pin)
{
    nts::Tristate result;

    if (this->pins[pin].getType() == Pin::Input)
        return this->pins[pin].updatePinStatus();
    if (this->pins[0].getStatus() == Undefined ||
        this->pins[1].getStatus() == Undefined)
        result = Undefined;
    else 
        result = this->pins[0].getStatus() != this->pins[1].getStatus()
        ? True : False;
    this->pins[pin].setStatus(result);
    return result;
}
