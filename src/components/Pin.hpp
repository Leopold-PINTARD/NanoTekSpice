/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Pin
*/

#ifndef PIN_HPP_
    #define PIN_HPP_

    #include "IComponent.hpp"
    #include <vector>
    #include <memory>

namespace nts
{
    class Pin {
        public:
            enum Type {
                Input = 0,
                Output = 1
            };
            Pin(Pin::Type type);
            ~Pin();
            enum nts::Tristate getStatus() const;
            enum nts::Tristate updatePinStatus();
            size_t getLinkedPin(size_t pin) const;
            std::shared_ptr<IComponent> getLinkedComp(size_t comp) const;
            void setStatus(enum nts::Tristate val);
            void addLinkedComp(IComponent &comp, size_t pin);
            bool containsLinked(std::shared_ptr<IComponent> linkedComp,
                size_t linkedPin);
            Type getType() const;
        private:
            std::vector<std::shared_ptr<IComponent>> linkedComps;
            std::vector<size_t> linkedPins;
            enum nts::Tristate status;
            Type pinType;
    };
}

#endif /* !PIN_HPP_ */
