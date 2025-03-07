/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Chip4001
*/

#include "components/advanced/Chip4001.hpp"
#include <iostream>

nts::Chip4001::Chip4001(std::string name)
{
    compName = name;
    pins.emplace_back(Pin::Input); // 1
    pins.emplace_back(Pin::Input); // 2
    pins.emplace_back(Pin::Output); // 3
    pins.emplace_back(Pin::Output); // 4
    pins.emplace_back(Pin::Input); // 5
    pins.emplace_back(Pin::Input); // 6
    pins.emplace_back(Pin::Ignore); // 7 -> ignored
    pins.emplace_back(Pin::Input); // 8
    pins.emplace_back(Pin::Input); // 9
    pins.emplace_back(Pin::Output); // 10
    pins.emplace_back(Pin::Output); // 11
    pins.emplace_back(Pin::Input); // 12
    pins.emplace_back(Pin::Input); // 13
    pins.emplace_back(Pin::Ignore); // 14 -> ignored
    linkChipsets();
}

nts::Chip4001::~Chip4001()
{
}

nts::Tristate nts::Chip4001::compute(size_t pin)
{
    if (this->pins[pin].getType() == Pin::Input) {
        this->pins[pin].updatePinStatus();
        this->input_gates[pin].changeState(this->pins[pin].getStatus());
        this->input_gates[pin].simulate(1);
        return this->input_gates[pin].compute(0);
    }
    this->output_gates[pin].simulate(this->pins[0].getCurrentTick());
    return this->output_gates[pin].compute(0);
}

void nts::Chip4001::linkChipsets()
{
    size_t input_pins[] = {0, 1, 4, 5, 7, 8, 11, 12};
    int output_pins[] = {2, 3, 9, 10};

    for (int i = 0; i < 4; i++) {
        input_gates.emplace_back("input_a_" + std::to_string(i));
        input_gates.emplace_back("input_b_" + std::to_string(i));
        nor_gates.emplace_back("nor_" + std::to_string(i));
        output_gates.emplace_back("output_" + std::to_string(i));
        input_gates[i].setLink(0, nor_gates[i], 0);
        input_gates[i + 1].setLink(0, nor_gates[i], 1);
        nor_gates[i].setLink(2, output_gates[i], 0);
    }
}
