/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Xor
*/

#include "Xor.hpp"

nts::Xor::Xor(std::string name)
{
    this->compName = name;
}

nts::Xor::~Xor()
{
}

static void updatePinStatus(nts::Pin &pin)
{
    pin.setStatus(pin.getLinkedComp(0)->compute(pin.getLinkedPin(0)));
}

nts::Tristate nts::Xor::compute(size_t pin)
{
    if (this->pins[pin].getType() == Pin::Output) {
        if (this->pins[0].getStatus() == Undefined)
            updatePinStatus(this->pins[0]);
        if (this->pins[1].getStatus() == Undefined)
            updatePinStatus(this->pins[1]);
        if (this->pins[0].getStatus() == Undefined ||
            this->pins[1].getStatus() == Undefined)
            return Undefined;
        if ((this->pins[0].getStatus() == True &&
            this->pins[1].getStatus() == False) ||
            (this->pins[0].getStatus() == False &&
            this->pins[1].getStatus() == True))
            return True;
        return False;
    }
    return this->pins[pin].getStatus();
}
