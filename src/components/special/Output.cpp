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

nts::Tristate nts::Output::compute(size_t pin)
{
    (void)pin;
    this->pins[0].updatePinStatus(0);
    return this->pins[0].getStatus();
}
