/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** ADoor
*/

#include "ADoor.hpp"

nts::ADoor::ADoor()
{
    for (int i = 0; i < 2; i++)
        pins.emplace_back(Pin::Input);
    pins.emplace_back(Pin::Output);
}
