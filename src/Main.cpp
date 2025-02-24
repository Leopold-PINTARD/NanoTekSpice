/*
** EPITECH PROJECT, 2025
** Main file for the project to compile
** File description:
** Main
*/

#include <unistd.h>
#include "components/basic/And.hpp"
#include "components/special/True.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    nts::And and_gate("test");
    class nts::True true_gate("test2");
    true_gate.setLink(0, and_gate, 0);
    // true_gate.setLink(0, and_gate, 1);
    auto result = and_gate.compute(2);
    if (result == nts::Tristate::Undefined) {
        std::cout << "Result of compute: Undefined" << std::endl;
    } else if (result == nts::Tristate::True) {
        std::cout << "Result of compute: True" << std::endl;
    } else if (result == nts::Tristate::False) {
        std::cout << "Result of compute: False" << std::endl;
    }
    return 0;
}
