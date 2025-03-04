/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Output
*/

#ifndef OUTPUT_HPP_
    #define OUTPUT_HPP_

    #include "components/AComponent.hpp"

namespace nts {
    class Output : public AComponent {
        public:
            Output(std::string name);
            ~Output();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
    };
}

#endif /* !OUTPUT_HPP_ */
