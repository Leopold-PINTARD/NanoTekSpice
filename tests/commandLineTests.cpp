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
#include <thread>
#include <chrono>
#include <csignal>

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

Test(commandLine_tests, handle_input_with_eof, .init=cr_redirect_stdout)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;

    std::cin.clear(std::ios::eofbit);
    cli.handleInput(chips);
    cr_assert_eq(cli.end, true);
    std::cin.clear();
}

Test(commandLine_tests, loop_command_with_interrupt, .init=cr_redirect_stdout)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;
    auto output = std::make_unique<nts::Output>("out1");
    chips.push_back(std::move(output));

    std::thread([]{
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        raise(SIGINT);
    }).detach();

    cli.commandLoop(chips);
    cr_assert(true);
}

Test(commandLine_tests, change_pin_value_invalid_format)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;
    auto input = std::make_unique<nts::Input>("in1");
    chips.push_back(std::move(input));

    cr_assert_eq(cli.commandChangePinValue("in1", chips), false);
    cr_assert_eq(cli.commandChangePinValue("in1=", chips), false);
    cr_assert_eq(cli.commandChangePinValue("=1", chips), false);
}

Test(commandLine_tests, change_pin_nonexistent_component)
{
    nts::CommandLineInput cli;
    std::vector<std::unique_ptr<nts::IComponent>> chips;

    bool result = cli.commandChangePinValue("nonexistent=1", chips);
    cr_assert_eq(result, false);
}
