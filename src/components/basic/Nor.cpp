/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Nor
*/

#include "components/basic/Nor.hpp"
#include <iostream>

nts::Nor::Nor(std::string name) : in_1("in_1"), in_2("in_2"),
    or_gate("or"), not_gate("not"), out("out")
{
    this->in_1.setLink(0, this->or_gate, 0);
    this->in_2.setLink(0, this->or_gate, 1);
    this->or_gate.setLink(2, this->not_gate, 0);
    this->not_gate.setLink(1, this->out, 0);
    this->compName = name;
}

nts::Nor::~Nor()
{
}

nts::Tristate nts::Nor::compute(size_t pin)
{
    if (this->pins[pin].getType() == Pin::Input) {
        this->pins[pin].updatePinStatus();
        if (pin == 0) {
            this->in_1.changeState(this->pins[pin].getStatus());
            this->in_1.simulate(1);
            return this->in_1.compute(0);
        } else {
            this->in_2.changeState(this->pins[pin].getStatus());
            this->in_2.simulate(1);
            return this->in_2.compute(0);
        }
    }
    this->out.simulate(this->pins[0].getCurrentTick());
    return this->out.compute(0);
}
