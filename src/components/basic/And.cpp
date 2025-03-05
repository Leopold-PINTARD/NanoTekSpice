/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** And
*/

#include "components/basic/And.hpp"
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
    currentTick++;
    for (size_t i = 0; i < 2; ++i) {
        if (this->pins[i].getStatus() == Undefined)
            this->pins[i].updatePinStatus(0);
    }
    if (this->pins[0].getStatus() == False ||
        this->pins[1].getStatus() == False)
        result = False;
    else if (this->pins[0].getStatus() == Undefined ||
        this->pins[1].getStatus() == Undefined)
        result = Undefined;
    else
        result = True;
    this->pins[pin].setStatus(result);
    return result;
}
