/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Factory tests
*/

#include <criterion/criterion.h>
#include "factory/Factory.hpp"
#include "components/special/Input.hpp"
#include "components/special/Output.hpp"
#include "components/special/Clock.hpp"
#include "components/special/True.hpp"
#include "components/special/False.hpp"
#include "components/basic/And.hpp"
#include "components/basic/Or.hpp"
#include "components/basic/Not.hpp"
#include "components/basic/Xor.hpp"
#include "components/basic/Nand.hpp"

Test(factory_tests, create_input)
{
    nts::Factory factory;
    auto component = factory.createComponent("input", "test_input");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_input");
    cr_assert_not_null(dynamic_cast<nts::Input*>(component.get()));
}

Test(factory_tests, create_output)
{
    nts::Factory factory;
    auto component = factory.createComponent("output", "test_output");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_output");
    cr_assert_not_null(dynamic_cast<nts::Output*>(component.get()));
}

Test(factory_tests, create_clock)
{
    nts::Factory factory;
    auto component = factory.createComponent("clock", "test_clock");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_clock");
    cr_assert_not_null(dynamic_cast<nts::Clock*>(component.get()));
}

Test(factory_tests, create_true)
{
    nts::Factory factory;
    auto component = factory.createComponent("true", "test_true");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_true");
    cr_assert_not_null(dynamic_cast<class nts::True*>(component.get()));
}

Test(factory_tests, create_false)
{
    nts::Factory factory;
    auto component = factory.createComponent("false", "test_false");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_false");
    cr_assert_not_null(dynamic_cast<class nts::False*>(component.get()));
}

Test(factory_tests, create_and)
{
    nts::Factory factory;
    auto component = factory.createComponent("and", "test_and");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_and");
    cr_assert_not_null(dynamic_cast<nts::And*>(component.get()));
}

Test(factory_tests, create_or)
{
    nts::Factory factory;
    auto component = factory.createComponent("or", "test_or");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_or");
    cr_assert_not_null(dynamic_cast<nts::Or*>(component.get()));
}

Test(factory_tests, create_not)
{
    nts::Factory factory;
    auto component = factory.createComponent("not", "test_not");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_not");
    cr_assert_not_null(dynamic_cast<nts::Not*>(component.get()));
}

Test(factory_tests, create_xor)
{
    nts::Factory factory;
    auto component = factory.createComponent("xor", "test_xor");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_xor");
    cr_assert_not_null(dynamic_cast<nts::Xor*>(component.get()));
}

Test(factory_tests, create_nand)
{
    nts::Factory factory;
    auto component = factory.createComponent("nand", "test_nand");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_nand");
    cr_assert_not_null(dynamic_cast<nts::Nand*>(component.get()));
}

Test(factory_tests, invalid_component)
{
    nts::Factory factory;

    try {
        auto component = factory.createComponent("invalid", "test");
        cr_assert_fail("Expected FactoryError exception was not thrown");
    } catch (const nts::Factory::FactoryError& e) {
        cr_assert_str_eq(e.what(), "Component type not found: invalid");
    }
}

Test(factory_tests, register_component)
{
    nts::Factory factory;
    factory.registerComponent("test", [](const std::string &name)
        -> nts::IComponent* {
        return new nts::Input(name);
    });

    auto component = factory.createComponent("test", "test_input");

    cr_assert_not_null(component.get());
    cr_assert_eq(component->getName(), "test_input");
    cr_assert_not_null(dynamic_cast<nts::Input*>(component.get()));
}
