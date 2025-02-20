/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
    #define ICOMPONENT_HPP_

    #include <string>

namespace nts
{
    enum Tristate {
        Undefined = (-true),
        True = true,
        False = false
    };
    class Pin;
    class IComponent
    {
        public:
        virtual ~IComponent() = default;
        virtual void simulate(std::size_t tick) = 0;
        virtual nts::Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, nts::IComponent &other,
            std::size_t otherPin) = 0;
        virtual const Pin &getPin(size_t pin) const = 0;
        virtual enum Tristate getLink(std::size_t pin) const = 0;
    };
}

#endif /* !ICOMPONENT_HPP_ */
