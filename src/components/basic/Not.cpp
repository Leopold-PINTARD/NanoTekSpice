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

    if (this->pins[pin].getType() != Pin::Output)
        return this->pins[pin].getStatus();
    currentTick++;
    for (size_t i = 0; i < 1; ++i) {
        if (this->pins[i].getStatus() == Undefined)
            this->pins[i].updatePinStatus(0);
        if (this->pins[i].getStatus() == Undefined)
            return Undefined;
    }
    //If the pin is false, return true, else it means the pin is true
    //then we return false
    result = this->pins[0].getStatus() == False ? True : False;
    this->pins[pin].setStatus(result);
    return result;
}
