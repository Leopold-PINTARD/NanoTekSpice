/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** And
*/

#include "And.hpp"
#include <iostream>

nts::And::And(std::string name)
{
    this->compName = name;
}

nts::And::~And()
{
}

nts::Tristate nts::And::compute(size_t pin)
{
    nts::Tristate result;

    if (this->pins[pin].getType() != Pin::Output)
        return this->pins[pin].getStatus();
    for (size_t i = 0; i < 2; ++i) {
        if (this->pins[i].getStatus() == Undefined)
            this->pins[i].updatePinStatus();
        if (this->pins[i].getStatus() == Undefined)
            return Undefined;
    }
    result = this->pins[0].getStatus() == True &&
        this->pins[1].getStatus() == True ? True : False;
    this->pins[pin].setStatus(result);
    return result;
}
