/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Input
*/

#include "components/special/Input.hpp"

nts::Input::Input(std::string name)
{
    this->compName = name;
}

nts::Input::~Input()
{
}

nts::Tristate nts::Input::compute(size_t pin)
{
    (void)pin;
    return this->pins[0].getStatus();
}

void nts::Input::changeState(Tristate new_state)
{
    this->pins[0].setStatus(new_state);
}
