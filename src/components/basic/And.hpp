/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** And
*/

#ifndef AND_HPP_
    #define AND_HPP_

    #include "ADoor.hpp"

namespace nts {
    class And : public ADoor {
        public:
            And();
            ~And();
            enum Tristate compute(size_t pin);
        protected:
        private:
    };
}

#endif /* !AND_HPP_ */
