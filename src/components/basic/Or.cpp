/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Or
*/

#include "components/basic/Or.hpp"

nts::Or::Or(std::string name)
{
    this->compName = name;
}

nts::Or::~Or()
{
}

nts::Tristate nts::Or::compute(size_t pin)
{
    nts::Tristate result;

    if (this->pins[pin].getType() != Pin::Output)
        return this->pins[pin].getStatus();
    for (size_t i = 0; i < 2; ++i) {
        if (this->pins[i].getStatus() == Undefined)
            this->pins[i].updatePinStatus();
    }
    if (this->pins[0].getStatus() == True ||
        this->pins[1].getStatus() == True)
        result = True;
    else if (this->pins[0].getStatus() == Undefined ||
        this->pins[1].getStatus() == Undefined)
        result = Undefined;
    else
        result = False;
    this->pins[pin].setStatus(result);
    return result;
}
