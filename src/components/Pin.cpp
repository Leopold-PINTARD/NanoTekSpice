/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Pin
*/

#include "components/Pin.hpp"
#include <iostream>

nts::Pin::Pin(Pin::Type type) : status(Undefined), pinType(type),
    currentTick(0)
{
}

nts::Pin::~Pin()
{
}

nts::Tristate nts::Pin::getStatus() const
{
    return status;
}

size_t nts::Pin::getLinkedPin(size_t pin) const
{
    return linkedPins[pin];
}

nts::IComponent &nts::Pin::getLinkedComp(size_t comp) const
{
    return linkedComps[comp];
}

void nts::Pin::setStatus(enum nts::Tristate val)
{
    status = val;
}

void nts::Pin::addLinkedComp(IComponent &comp, size_t pin)
{
    linkedComps.push_back(comp);
    linkedPins.push_back(pin);
}

bool nts::Pin::containsLinked(nts::IComponent &searchedComp,
    size_t linkedPin)
{
    for (size_t i = 0; i != this->linkedPins.size(); i++) {
        if (this->linkedPins[i] == linkedPin &&
                this->linkedComps[i].get().getName() == searchedComp.getName())
            return true;
    }
    return false;
}

nts::Pin::Type nts::Pin::getType() const
{
    return pinType;
}

unsigned int nts::Pin::getCurrentTick() const
{
    return currentTick;
}

//This function is used to update the status of an input pin as it can only be
//linked to one output pin. It will compute the value of the linked output and
//set it as the new status of the input pin.
//
//If this function is used on an output pin or an unlinked pin, nothing will
//happen and the pin's current value will be returned.
//
//Return value: The (maybe new) status of the pin.
enum nts::Tristate nts::Pin::updatePinStatus(size_t input_comp)
{
    currentTick++;
    if (this->getType() == Pin::Input && this->linkedComps.size() > 0 &&
        input_comp < this->linkedComps.size()) {
        this->getLinkedComp(input_comp).simulate(currentTick);
        this->setStatus(this->getLinkedComp(input_comp).compute(
            this->getLinkedPin(input_comp)));
    }
    return this->getStatus();
}
