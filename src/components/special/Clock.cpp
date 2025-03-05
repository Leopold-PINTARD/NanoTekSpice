/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Clock
*/

#include "components/special/Clock.hpp"

nts::Clock::Clock(std::string name) : Input(name)
{
    this->compName = name;
}

nts::Clock::~Clock()
{
}

nts::Tristate nts::Clock::compute(size_t pin)
{
    (void)pin;
    return this->pins[0].getStatus();
}

void nts::Clock::simulate(size_t tick)
{
    (void)tick;
    if (toChange) {
        this->pins[0].setStatus(nextState);
        toChange = false;
        return;
    }
    if (this->pins[0].getStatus() == nts::Tristate::True)
        this->pins[0].setStatus(nts::Tristate::False);
    else if (this->pins[0].getStatus() == nts::Tristate::False)
        this->pins[0].setStatus(nts::Tristate::True);
    else
        this->pins[0].setStatus(nts::Tristate::Undefined);
}
