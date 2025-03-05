/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Input
*/

#ifndef INPUT_HPP_
    #define INPUT_HPP_

    #include "components/special/ASpecial.hpp"

namespace nts {
    class Input : public ASpecial {
        public:
            Input(std::string name);
            ~Input();
            enum Tristate compute(size_t pin) override;
            void changeState(Tristate new_state);
            virtual void simulate(size_t tick) override;
        protected:
        private:
            nts::Tristate nextState;
    };
}

#endif /* !INPUT_HPP_ */
