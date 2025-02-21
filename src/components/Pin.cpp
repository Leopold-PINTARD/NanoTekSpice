/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Pin
*/

#include "Pin.hpp"

nts::Pin::Pin(Pin::Type type) : status(Undefined), pinType(type)
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

std::shared_ptr<nts::IComponent> nts::Pin::getLinkedComp(size_t comp) const
{
    return linkedComps[comp];
}

void nts::Pin::setStatus(enum nts::Tristate val)
{
    status = val;
}

void nts::Pin::addLinkedComp(IComponent &comp, size_t pin)
{
    linkedComps.push_back(std::shared_ptr<IComponent>(&comp));
    linkedPins.push_back(pin);
}

bool nts::Pin::containsLinked(std::shared_ptr<IComponent> linkedComp,
    size_t linkedPin)
{
    for (size_t i = 0; i != this->linkedPins.size(); i++) {
        if (this->linkedPins[i] == linkedPin &&
                this->linkedComps[i] == linkedComp)
            return true;
    }
    return false;
}

nts::Pin::Type nts::Pin::getType() const
{
    return pinType;
}

//This function is used to update the status of an input pin as it can only be
//linked to one output pin. It will compute the value of the linked output and
//set it as the new status of the input pin.
//
//If this function is used on an output pin or an unlinked pin, nothing will
//happen and the pin's current value will be returned.
//
//Return value: The (maybe new) status of the pin.
enum nts::Tristate nts::Pin::updatePinStatus()
{
    if (this->getType() == Pin::Input && this->getLinkedComp(0) != nullptr)
        this->setStatus(this->getLinkedComp(0)->compute(this->getLinkedPin(0)));
    return this->getStatus();
}
