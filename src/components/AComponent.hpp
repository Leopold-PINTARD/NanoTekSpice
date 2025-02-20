/*
** EPITECH PROJECT, 2025
** ù
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
    #define ACOMPONENT_HPP_

    #include "IComponent.hpp"
    #include "Pin.hpp"

namespace nts
{
    class AComponent : public IComponent {
        public:
            //Nothing happens by default, the simulation must be implemented on a case by case basis
            virtual void simulate(size_t tick) override {}
            //If a link is set on an output pin, the link is outgoing, if it's set on an input pin, the link is incoming
            virtual void setLink(size_t thisPin, IComponent &other,
                size_t otherPin) override {
                if (this->pins[thisPin].containsLinked(std::shared_ptr<IComponent>(&other), otherPin))
                    return;
                this->pins[thisPin].addLinkedComp(other, otherPin);
                other.setLink(otherPin, *this, thisPin);
            };
            nts::Tristate getLink(std::size_t pin) const override {
                if (pins[pin].getType() == Pin::Input)
                    return pins[pin].getLinkedComp(0)->compute(pins[pin].getLinkedPin(0));
            };
            virtual const Pin &getPin(size_t pin) const override {return this->pins[pin];}
        protected:
            std::string compName;
            std::vector<Pin> pins;
    };
}

#endif /* !ACOMPONENT_HPP_ */
