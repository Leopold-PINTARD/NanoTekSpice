/*
** EPITECH PROJECT, 2025
** Main file for the project to compile
** File description:
** Main
*/

#include <unistd.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    size_t sizewrite = write(1, "Hello, World!\n", 14);
    sizewrite += 1;
    return 0;
}
