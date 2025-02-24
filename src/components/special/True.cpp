/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** True
*/

#include "components/special/True.hpp"

nts::True::True(std::string name)
{
    this->compName = name;
    pins.emplace_back(Pin::Output);
}

nts::True::~True()
{
}

nts::Tristate nts::True::compute(size_t pin)
{
    (void)pin;
    return nts::Tristate::True;
}
