/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** CommandLine tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "commandLineHandling/CommandLineInput.hpp"
#include "components/special/Input.hpp"
#include "components/special/Output.hpp"
#include "components/special/Clock.hpp"
#include <sstream>

Test(commandLine_tests, constructor_test)
{
    nts::CommandLineInput cli(">");
    cr_assert_eq(cli.getIntroString(), ">");
}

Test(commandLine_tests, set_intro_string)
{
    nts::CommandLineInput cli;
    cli.setIntroString("test> ");
    cr_assert_eq(cli.getIntroString(), "test> ");
}

Test(commandLine_tests, handle_exit_command)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;

    cli.commandExit(chips);
    cr_assert_eq(cli.end, true);
}

Test(commandLine_tests, simulate_command)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;
    auto output = std::make_unique<nts::Output>("out1");
    chips.push_back(std::move(output));

    cli.commandSimulate(chips);
    cr_assert_eq(cli.tick, 1);
}

Test(commandLine_tests, change_pin_value)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;
    auto input = std::make_unique<nts::Input>("in1");
    chips.push_back(std::move(input));

    bool result = cli.commandChangePinValue("in1=1", chips);
    cr_assert_eq(result, true);
}

Test(commandLine_tests, invalid_pin_value)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;
    auto input = std::make_unique<nts::Input>("in1");
    chips.push_back(std::move(input));

    bool result = cli.commandChangePinValue("in1=2", chips);
    cr_assert_eq(result, false);
}

Test(commandLine_tests, display_command, .init=cr_redirect_stdout)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;
    auto input = std::make_unique<nts::Input>("in1");
    auto output = std::make_unique<nts::Output>("out1");

    input->changeState(nts::Tristate::True);
    chips.push_back(std::move(input));
    chips.push_back(std::move(output));

    cli.commandSimulate(chips);
    cli.commandDisplay(chips);
    cr_assert_stdout_eq_str("tick: 0\ninput(s):\n  in1: U\noutput(s):\n  out1: U\n");
}

Test(commandLine_tests, handle_invalid_command)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;

    cli.handleCommand("invalid", chips);
}
