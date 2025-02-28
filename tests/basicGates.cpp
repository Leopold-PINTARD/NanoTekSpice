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
#include "components/basic/Xor.hpp"
#include "components/basic/Not.hpp"


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

Test(xor_tests, true_test)
{
    nts::Xor xor_gate("test");
    class nts::True true_gate("test2");
    true_gate.setLink(0, xor_gate, 0);
    true_gate.setLink(0, xor_gate, 1);
    auto result = xor_gate.compute(2);
    cr_assert_eq(result, nts::False);
}

Test(xor_tests, false_test)
{
    nts::Xor xor_gate("test");
    class nts::True true_gate("vrai");
    class nts::False false_gate("faux");
    true_gate.setLink(0, xor_gate, 0);
    false_gate.setLink(0, xor_gate, 1);
    auto result = xor_gate.compute(2);
    cr_assert_eq(result, nts::True);
}

Test(xor_tests, undefined_test)
{
    nts::Xor xor_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, xor_gate, 0);
    auto result = xor_gate.compute(2);
    cr_assert_eq(result, nts::Undefined);
}

Test(xor_tests, compute_input_test)
{
    nts::Xor xor_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, xor_gate, 0);
    auto result = xor_gate.compute(0);
    auto result2 = xor_gate.compute(1);
    cr_assert_eq(result, nts::Undefined);
    cr_assert_eq(result2, nts::Undefined);
}

Test(xor_tests, compute_input_after_compute_output_test)
{
    nts::Xor xor_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, xor_gate, 0);
    auto resultcomputer = xor_gate.compute(2);
    auto result = xor_gate.compute(0);
    auto result2 = xor_gate.compute(1);
    cr_assert_eq(resultcomputer, nts::Undefined);
    cr_assert_eq(result, nts::True);
    cr_assert_eq(result2, nts::Undefined);
}

Test(not_tests, true_test)
{
    nts::Not not_gate("test");
    class nts::False false_gate("faux");
    false_gate.setLink(0, not_gate, 0);
    auto result = not_gate.compute(1);
    cr_assert_eq(result, nts::True);
}

Test(not_tests, false_test)
{
    nts::Not not_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, not_gate, 0);
    auto result = not_gate.compute(1);
    cr_assert_eq(result, nts::False);
}

Test(not_tests, undefined_test)
{
    nts::Not not_gate("test");
    auto result = not_gate.compute(1);
    cr_assert_eq(result, nts::Undefined);
}

Test(not_tests, compute_input_test)
{
    nts::Not not_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, not_gate, 0);
    auto result = not_gate.compute(0);
    cr_assert_eq(result, nts::Undefined);
}

Test(not_tests, compute_input_after_compute_output_test)
{
    nts::Not not_gate("test");
    class nts::True true_gate("vrai");
    true_gate.setLink(0, not_gate, 0);
    auto resultcomputer = not_gate.compute(1);
    auto result = not_gate.compute(0);
    cr_assert_eq(resultcomputer, nts::False);
    cr_assert_eq(result, nts::True);
}
