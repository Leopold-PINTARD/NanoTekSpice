/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Pin
*/

#ifndef PIN_HPP_
    #define PIN_HPP_

    #include "AComponent.hpp"
    #include <vector>
    #include <memory>

namespace nts {
    class Pin {
        public:
            enum Type {
                Input = 0,
                Output = 1
            };
            Pin(Pin::Type type);
            ~Pin();
            enum nts::Tristate getStatus() const;
            enum nts::Tristate updatePinStatus(size_t input_comp);
            size_t getLinkedPin(size_t pin) const;
            IComponent &getLinkedComp(size_t comp) const;
            void setStatus(enum nts::Tristate val);
            void addLinkedComp(IComponent &comp, size_t pin);
            bool containsLinked(IComponent &linkedComp, size_t linkedPin);
            Type getType() const;
            unsigned int getCurrentTick() const;
        private:
            std::vector<std::reference_wrapper<IComponent>>linkedComps;
            std::vector<size_t> linkedPins;
            enum nts::Tristate status;
            Type pinType;
            unsigned int currentTick;
    };
}

#endif /* !PIN_HPP_ */
