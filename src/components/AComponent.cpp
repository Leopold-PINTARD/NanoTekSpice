/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** AComponent
*/

#include "components/AComponent.hpp"

void nts::AComponent::simulate(size_t tick)
{
    (void)tick;
}

void nts::AComponent::setLink(size_t thisPin, IComponent &other, size_t otherPin)
{
    if (this->pins[thisPin].containsLinked(other, otherPin))
        return;
    this->pins[thisPin].addLinkedComp(other, otherPin);
    other.setLink(otherPin, *this, thisPin);
}

nts::Tristate nts::AComponent::getLink(std::size_t pin) const
{
    if (pins[pin].getType() == Pin::Input)
        return pins[pin].getLinkedComp(0).compute(pins[pin].getLinkedPin(0));
    return pins[pin].getStatus();
};

std::string nts::AComponent::getName() const
{
    return this->compName;
}
