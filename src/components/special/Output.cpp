/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Output
*/

#include "components/special/Output.hpp"

nts::Output::Output(std::string name)
{
    this->compName = name;
    pins.emplace_back(Pin::Input);
}

nts::Output::~Output()
{
}

void nts::Output::simulate(size_t tick)
{
    while (pins[0].getCurrentTick() < tick)
        this->pins[0].updatePinStatus();
}

nts::Tristate nts::Output::compute(size_t pin)
{
    (void)pin;
    return this->pins[0].getStatus();
}
