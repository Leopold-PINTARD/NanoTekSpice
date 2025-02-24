/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** True
*/

#ifndef TRUE_HPP_
    #define TRUE_HPP_

    #include "components/AComponent.hpp"

namespace nts {
    class True : public AComponent {
        public:
            True(std::string name);
            ~True();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
    };
}

#endif /* !TRUE_HPP_ */
