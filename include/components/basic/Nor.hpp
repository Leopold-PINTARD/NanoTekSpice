/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Nor
*/

#ifndef NOR_HPP_
    #define NOR_HPP_

    #include "components/basic/ADoor.hpp"
    #include "components/basic/Or.hpp"
    #include "components/basic/Not.hpp"
    #include "components/special/Input.hpp"
    #include "components/special/Output.hpp"

namespace nts {
    class Nor : public ADoor {
        public:
            Nor(std::string name);
            ~Nor();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
            nts::Input in_1;
            nts::Input in_2;
            nts::Or or_gate;
            nts::Not not_gate;
            nts::Output out;
    };
}

#endif /* !NOR_HPP_ */
