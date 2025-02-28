/*
** EPITECH PROJECT, 2025
** repo-c++
** File description:
** tests
*/

#include <iostream>
#include <fstream>
#include <string>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/Pin.hpp"
#include "components/special/True.hpp"
#include "components/special/False.hpp"
#include "components/basic/And.hpp"


// static void redirect_all_stdout(void)
// {
//     cr_redirect_stdout();
//     cr_redirect_stderr();
// }

Test(and_tests, true_test)
{
    nts::And and_gate("test");
    class nts::True true_gate("test2");
    true_gate.setLink(0, and_gate, 0);
    true_gate.setLink(0, and_gate, 1);
    auto result = and_gate.compute(2);
    cr_assert_eq(result, nts::True);
}

Test(and_tests, false_test)
{
    nts::And and_gate("test");
    class nts::True true_gate("vrai");
    class nts::False false_gate("faux");
    true_gate.setLink(0, and_gate, 0);
    false_gate.setLink(0, and_gate, 1);
    auto result = and_gate.compute(2);
    cr_assert_eq(result, nts::False);
}

Test(and_tests, undefined_test)
{
    nts::And and_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, and_gate, 0);
    auto result = and_gate.compute(2);
    cr_assert_eq(result, nts::Undefined);
}

Test(and_tests, undefined_false_test)
{
    nts::And and_gate("test");
    class nts::False false_gate("faux");
    false_gate.setLink(0, and_gate, 0);
    auto result = and_gate.compute(2);
    cr_assert_eq(result, nts::False);
}

Test(and_tests, compute_input_test)
{
    nts::And and_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, and_gate, 0);
    auto result = and_gate.compute(0);
    auto result2 = and_gate.compute(1);
    cr_assert_eq(result, nts::Undefined);
    cr_assert_eq(result2, nts::Undefined);
}

Test(and_tests, compute_input_after_compute_output_test)
{
    nts::And and_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, and_gate, 0);
    auto resultcomputer = and_gate.compute(2);
    auto result = and_gate.compute(0);
    auto result2 = and_gate.compute(1);
    cr_assert_eq(resultcomputer, nts::Undefined);
    cr_assert_eq(result, nts::True);
    cr_assert_eq(result2, nts::Undefined);
}
