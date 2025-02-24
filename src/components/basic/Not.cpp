/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Not
*/

#include "Not.hpp"

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

static void updatePinStatus(nts::Pin &pin)
{
    pin.setStatus(pin.getLinkedComp(0)->compute(pin.getLinkedPin(0)));
}

nts::Tristate nts::Not::compute(size_t pin)
{
    if (this->pins[pin].getType() == Pin::Output) {
        if (this->pins[0].getStatus() == Undefined)
            updatePinStatus(this->pins[0]);
        if (this->pins[0].getStatus() == True)
            return False;
        else if (this->pins[0].getStatus() == False)
            return True;
        return Undefined;
    }
    return this->pins[pin].getStatus();
}
