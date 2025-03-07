/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Chip4001
*/

#pragma once

#include "components/AComponent.hpp"
#include <vector>
#include "components/basic/Nor.hpp"
#include <unordered_map>

namespace nts {
    class Chip4001 : public AComponent {
        public:
            Chip4001(std::string name);
            ~Chip4001();
            enum Tristate compute(size_t pin) override;
            void linkChipsets();
        protected:
        private:
            std::vector<nts::Input> input_gates;
            std::vector<nts::Nor> nor_gates;
            std::vector<nts::Output> output_gates;
    };
}
