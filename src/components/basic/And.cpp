/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** And
*/

#include "And.hpp"

nts::And::And(std::string name)
{
    this->compName = name;
}

nts::And::~And()
{
}

static void updatePinStatus(nts::Pin &pin)
{
    pin.setStatus(pin.getLinkedComp(0)->compute(pin.getLinkedPin(0)));
}

nts::Tristate nts::And::compute(size_t pin)
{
    if (this->pins[pin].getType() == Pin::Output) {
        if (this->pins[0].getStatus() == Undefined)
            updatePinStatus(this->pins[0]);
        if (this->pins[1].getStatus() == Undefined)
            updatePinStatus(this->pins[1]);
        if (this->pins[0].getStatus() == True &&
            this->pins[1].getStatus() == True)
            return True;
        return False;
    }
    return this->pins[pin].getStatus();
}
