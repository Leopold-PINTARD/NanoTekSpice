/*
** EPITECH PROJECT, 2025
** Main file for the project to compile
** File description:
** Main
*/

#include <unistd.h>
#include "components/basic/Nand.hpp"
#include "components/special/True.hpp"
#include "components/special/False.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    nts::Nand nand_gate("test");
    class nts::False gate("test2");
    gate.setLink(0, nand_gate, 0);
    auto result = nand_gate.compute(2);
    if (result == nts::Tristate::Undefined) {
        std::cout << "Result of compute: Undefined" << std::endl;
    } else if (result == nts::Tristate::True) {
        std::cout << "Result of compute: True" << std::endl;
    } else if (result == nts::Tristate::False) {
        std::cout << "Result of compute: False" << std::endl;
    }
    return 0;
}
