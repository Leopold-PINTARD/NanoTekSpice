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
#include "components/basic/And.hpp"


// static void redirect_all_stdout(void)
// {
//     cr_redirect_stdout();
//     cr_redirect_stderr();
// }

Test(and_tests, test)
{
    nts::And and_gate("test");
    class nts::True true_gate("test2");
    true_gate.setLink(0, and_gate, 0);
    true_gate.setLink(0, and_gate, 1);
    auto result = and_gate.compute(2);
    cr_assert_eq(result, nts::True);
}
