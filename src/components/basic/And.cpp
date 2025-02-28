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
    nts::Tristate status0;
    nts::Tristate status1;

    if (this->pins[pin].getType() != Pin::Output)
        return this->pins[pin].getStatus();
    for (size_t i = 0; i < 2; ++i) {
        if (this->pins[i].getStatus() == Undefined)
            this->pins[i].updatePinStatus();
    }
    status0 = this->pins[0].getStatus();
    status1 = this->pins[1].getStatus();
    if (status0 == False || status1 == False)
        result = False;
    else if (status0 == Undefined || status1 == Undefined)
        result = Undefined;
    else
        result = True;
    this->pins[pin].setStatus(result);
    return result;
}
