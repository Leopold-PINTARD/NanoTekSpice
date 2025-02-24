/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Not
*/

#pragma once

#include "ADoor.hpp"

namespace nts {
    class Not : public ADoor {
        public:
            Not(std::string name);
            ~Not();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
    };
}
