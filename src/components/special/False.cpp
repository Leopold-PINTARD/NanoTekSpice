/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** False
*/

#include "components/special/False.hpp"

nts::False::False(std::string name)
{
    this->compName = name;
}

nts::False::~False()
{
}

nts::Tristate nts::False::compute(size_t pin)
{
    (void)pin;
    return nts::Tristate::False;
}
