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
    size_t tick;

    if (this->pins[pin].getType() == Pin::Input)
        return this->pins[pin].updatePinStatus(1);
    tick = this->pins[2].getCurrentTick();
    this->not_gate.simulate(tick);
    return this->pins[2].getStatus();
}
