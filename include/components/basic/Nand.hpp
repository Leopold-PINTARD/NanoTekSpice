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
    #include "components/special/Input.hpp"
    #include "components/special/Output.hpp"

namespace nts {
    class Nand : public ADoor {
        public:
            Nand(std::string name);
            ~Nand();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
            nts::Input in_1;
            nts::Input in_2;
            nts::And and_gate;
            nts::Not not_gate;
            nts::Output out;
    };
}

#endif /* !NAND_HPP_ */
