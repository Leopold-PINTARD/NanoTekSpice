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

    if (this->pins[pin].getType() != Pin::Output)
        return this->pins[pin].getStatus();
    for (size_t i = 0; i < 2; ++i) {
        if (this->pins[i].getStatus() == Undefined)
            this->pins[i].updatePinStatus(0);
        if (this->pins[i].getStatus() == Undefined)
            return Undefined;
    }
    result = this->pins[0].getStatus() != this->pins[1].getStatus()
        ? True : False;
    this->pins[pin].setStatus(result);
    return result;
}
