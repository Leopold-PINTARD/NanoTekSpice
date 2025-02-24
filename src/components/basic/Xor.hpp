/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Xor
*/

#pragma once

    #include "ADoor.hpp"

namespace nts {
    class Xor : public ADoor {
        public:
            Xor(std::string name);
            ~Xor();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
    };
}
