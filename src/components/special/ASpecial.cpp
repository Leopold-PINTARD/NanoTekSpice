/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** ASpecial
*/

#include "components/special/ASpecial.hpp"

nts::ASpecial::ASpecial()
{
    pins.emplace_back(Pin::Output);
}
