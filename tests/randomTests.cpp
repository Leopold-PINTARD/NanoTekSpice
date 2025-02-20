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
#include "../src/components/Pin.hpp"
#include "../src/components/basic/And.hpp"


void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(sample_test_suite, sample_test_case)
{
    nts::And test;
}
