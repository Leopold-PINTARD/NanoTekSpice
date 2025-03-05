/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Clock tests
*/

#include <criterion/criterion.h>
#include "components/special/Clock.hpp"

Test(clock_tests, initial_state)
{
    nts::Clock clock("test_clock");
    cr_assert_eq(clock.compute(0), nts::Undefined);
}

Test(clock_tests, set_state_true)
{
    nts::Clock clock("test_clock");
    clock.changeState(nts::True);
    clock.simulate(1);
    cr_assert_eq(clock.compute(0), nts::True);
}

Test(clock_tests, set_state_false)
{
    nts::Clock clock("test_clock");
    clock.changeState(nts::False);
    clock.simulate(1);
    cr_assert_eq(clock.compute(0), nts::False);
}

Test(clock_tests, state_toggle)
{
    nts::Clock clock("test_clock");
    clock.changeState(nts::True);
    clock.simulate(1);
    cr_assert_eq(clock.compute(0), nts::True);

    clock.simulate(1);
    cr_assert_eq(clock.compute(0), nts::False);

    clock.simulate(1);
    cr_assert_eq(clock.compute(0), nts::True);
}
