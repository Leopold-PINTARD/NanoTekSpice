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
    #include <vector>

namespace nts {
    class AComponent : public IComponent {
        public:
            //Nothing happens by default, the simulation must be implemented on
            //a case by case basis.
            virtual void simulate(size_t tick) override;
            //If a link is set on an output pin, the link is outgoing, if it's
            //set on an input pin, the link is incoming.
            virtual void setLink(size_t thisPin, IComponent &other,
                size_t otherPin) override;
            nts::Tristate getLink(std::size_t pin) const override;
            virtual const Pin &getPin(size_t pin) const override;
            std::string getName() const;
        protected:
            //The name of the component. It is used to identify it in the circuit.
            std::string compName;
            //When appending a pin to a component, use pins.emplace_back(Pin::Type).
            //Type can be either Input or Output.
            std::vector<Pin> pins;
    };
}

#endif /* !ACOMPONENT_HPP_ */
