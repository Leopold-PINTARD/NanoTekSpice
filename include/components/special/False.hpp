/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** False
*/

#ifndef FALSE_HPP_
    #define FALSE_HPP_

    #include "components/special/ASpecial.hpp"

namespace nts {
    class False : public ASpecial {
        public:
            False(std::string name);
            ~False();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
    };
}

#endif /* !FALSE_HPP_ */
