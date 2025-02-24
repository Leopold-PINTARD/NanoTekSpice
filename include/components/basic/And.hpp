/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** And
*/

#ifndef AND_HPP_
    #define AND_HPP_

    #include "components/basic/ADoor.hpp"

namespace nts {
    class And : public ADoor {
        public:
            And(std::string name);
            ~And();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
    };
}

#endif /* !AND_HPP_ */
