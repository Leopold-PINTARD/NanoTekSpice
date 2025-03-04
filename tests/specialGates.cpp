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
#include "components/special/Input.hpp"
#include "components/special/Output.hpp"
#include "components/basic/And.hpp"
#include "components/basic/Nand.hpp"


// static void redirect_all_stdout(void)
// {
//     cr_redirect_stdout();
//     cr_redirect_stderr();
// }

Test(true_tests, true_test)
{
    class nts::True true_gate("test");
    cr_assert_eq(true_gate.compute(0), nts::True);
}

Test(false_tests, false_test)
{
    class nts::False false_gate("test");
    cr_assert_eq(false_gate.compute(0), nts::False);
}

Test(input_tests, undefined_test)
{
    class nts::Input input_gate("test");
    cr_assert_eq(input_gate.compute(0), nts::Undefined);
}

Test(input_tests, true_test)
{
    class nts::Input input_gate("test");
    input_gate.changeState(nts::True);
    cr_assert_eq(input_gate.compute(0), nts::True);
}

Test(input_tests, false_test)
{
    class nts::Input input_gate("test");
    input_gate.changeState(nts::False);
    cr_assert_eq(input_gate.compute(0), nts::False);
}

Test(output_tests, undefined_test)
{
    class nts::Output output_gate("test");
    cr_assert_eq(output_gate.compute(0), nts::Undefined);
}

Test(output_tests, true_test)
{
    class nts::Output output_gate("test");
    class nts::True true_gate("test2");
    output_gate.setLink(0, true_gate, 0);
    cr_assert_eq(output_gate.compute(0), nts::True);
}

Test(output_tests, false_test)
{
    class nts::Output output_gate("test");
    class nts::False false_gate("test2");
    output_gate.setLink(0, false_gate, 0);
    cr_assert_eq(output_gate.compute(0), nts::False);
}

Test(output_tests, advanced_true_test)
{
    class nts::Output output_gate("test");
    class nts::True true_gate("test2");
    nts::And and_gate("test3");
    true_gate.setLink(0, and_gate, 0);
    and_gate.setLink(1, true_gate, 0);
    output_gate.setLink(0, and_gate, 2);
    cr_assert_eq(output_gate.compute(0), nts::True);
}

Test(output_tests, advanced_false_test)
{
    class nts::Output output_gate("test");
    class nts::True true_gate("test2");
    nts::Nand nand_gate("test3");
    true_gate.setLink(0, nand_gate, 0);
    nand_gate.setLink(1, true_gate, 0);
    output_gate.setLink(0, nand_gate, 2);
    cr_assert_eq(output_gate.compute(0), nts::False);
}

Test(output_tests, advanced_undefined_test)
{
    class nts::Output output_gate("test");
    class nts::True true_gate("test2");
    nts::And and_gate("test3");
    and_gate.setLink(1, true_gate, 0);
    output_gate.setLink(0, and_gate, 2);
    cr_assert_eq(output_gate.compute(0), nts::Undefined);
}
