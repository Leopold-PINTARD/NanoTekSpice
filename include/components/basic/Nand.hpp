/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Nand
*/

#ifndef NAND_HPP_
    #define NAND_HPP_

    #include "components/basic/ADoor.hpp"
    #include "components/basic/And.hpp"
    #include "components/basic/Not.hpp"

namespace nts {
    class Nand : public ADoor {
        public:
            Nand(std::string name);
            ~Nand();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
            nts::And and_gate;
            nts::Not not_gate;
    };
}

#endif /* !NAND_HPP_ */
