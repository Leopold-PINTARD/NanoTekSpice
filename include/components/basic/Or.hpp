/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Or
*/

#pragma once

    #include "components/basic/ADoor.hpp"

namespace nts {
    class Or : public ADoor {
        public:
            Or(std::string name);
            ~Or();
            enum Tristate compute(size_t pin) override;
        protected:
        private:
    };
}
