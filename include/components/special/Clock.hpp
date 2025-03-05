/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_

    #include "components/special/Input.hpp"

namespace nts {
    class Clock : public Input {
        public:
            Clock(std::string name);
            ~Clock();
            enum Tristate compute(size_t pin) override;
            void simulate(size_t tick) override;
        protected:
        private:
    };
}

#endif /* !CLOCK_HPP_ */
