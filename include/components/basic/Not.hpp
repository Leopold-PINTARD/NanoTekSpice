/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Not
*/

#pragma once

#include "components/basic/ADoor.hpp"

namespace nts {
    // Input is pin[0], Output is pin[1]
    class Not : public ADoor {
        public:
            Not(std::string name);
            ~Not();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
    };
}
