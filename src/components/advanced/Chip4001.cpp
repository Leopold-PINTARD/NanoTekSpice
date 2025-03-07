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
    Tristate result = Tristate::Undefined;
    size_t not_gate_index;

    if (pins[pin].getType() == Pin::Ignore)
        return Tristate::Undefined;
    if (pins[pin].getType() == Pin::Input) {
        std::cout << "pin: " << pin << std::endl;
        std::cout << "pin lié: " << pins[pin].getLinkedComp(0).getName() << std::endl;
        std::cout << "pin lié: " << pins[pin].getLinkedPin(1) << std::endl;
        pins[pin].updatePinStatus(); // recursion infinie ici
        return pins[pin].getStatus();
    }
    if (pin == 2)
        not_gate_index = 0;
    else if (pin == 3)
        not_gate_index = 1;
    else if (pin == 9)
        not_gate_index = 2;
    else if (pin == 10)
        not_gate_index = 3;
    else
        return Tristate::Undefined;
    result = not_gates[not_gate_index]->compute(1);
    pins[pin].setStatus(result);
    return result;
}

void nts::Chip4001::linkChipsets()
{
    const int inputs[4][2] = {{0, 1}, {4, 5}, {7, 8}, {11, 12}};
    const int outputs[4] = {2, 3, 9, 10};

    for (int i = 0; i < 4; i++) {
        not_gates.push_back(std::make_unique<nts::Not>("not" + std::to_string(i)));
        or_gates.push_back(std::make_unique<nts::Or>("or" + std::to_string(i)));
        or_gates[i]->setLink(2, *not_gates[i], 0);
    }
    for (int i = 0; i < 4; i++) {
        this->setLink(inputs[i][0], *or_gates[i], 0);
        this->setLink(inputs[i][1], *or_gates[i], 1);
        not_gates[i]->setLink(1, *this, outputs[i]);
    }
}
