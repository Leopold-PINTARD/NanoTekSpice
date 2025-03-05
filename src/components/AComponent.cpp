/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** AComponent
*/

#include "components/AComponent.hpp"

void nts::AComponent::simulate(size_t tick)
{
    for (size_t i = 0; i < pins.size(); i++) {
        while (pins[i].getType() == Pin::Input &&
            pins[i].getCurrentTick() < tick)
            compute(i);
    }
    for (size_t i = 0; i < pins.size(); i++) {
        if (pins[i].getType() == Pin::Output)
            compute(i);
    }
}

void nts::AComponent::setLink(size_t thisPin, IComponent &other, size_t otherPin)
{
    if (this->pins[thisPin].containsLinked(other, otherPin))
        return;
    this->pins[thisPin].addLinkedComp(other, otherPin);
    other.setLink(otherPin, *this, thisPin);
}

std::string nts::AComponent::getName() const
{
    return this->compName;
}
