/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Chip4001
*/

#pragma once

#include "components/AComponent.hpp"
#include <vector>
#include "components/basic/Not.hpp"
#include "components/basic/Or.hpp"

namespace nts {
    class Chip4001 : public AComponent {
        public:
            Chip4001(std::string name);
            ~Chip4001();
            enum Tristate compute(size_t pin) override;
            void linkChipsets();
        protected:
        private:
            std::vector<std::unique_ptr<nts::Not>> not_gates;
            std::vector<std::unique_ptr<nts::Or>> or_gates;
    };
}
