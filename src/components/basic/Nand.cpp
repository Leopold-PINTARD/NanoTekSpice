/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Nand
*/

#include "components/basic/Nand.hpp"
#include <iostream>

nts::Nand::Nand(std::string name) : and_gate("and"), not_gate("not")
{
    this->compName = name;
    this->setLink(0, this->and_gate, 0);
    this->setLink(1, this->and_gate, 1);
    this->and_gate.setLink(2, this->not_gate, 0);
    this->setLink(2, this->not_gate, 1);
}

nts::Nand::~Nand()
{
}

nts::Tristate nts::Nand::compute(size_t pin)
{
    nts::Tristate result;

    if (this->pins[pin].getType() != Pin::Output)
        return this->pins[pin].getStatus();
    currentTick++;
    for (size_t i = 0; i < 2; ++i) {
        if (this->pins[i].getStatus() == Undefined)
            this->pins[i].updatePinStatus(1);
    }
    result = this->not_gate.compute(1);
    this->pins[pin].setStatus(result);
    return result;
}
