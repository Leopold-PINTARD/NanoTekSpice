/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** ADoor
*/

#ifndef ADOOR_HPP_
    #define ADOOR_HPP_

    #include "AComponent.hpp"

namespace nts {
    class ADoor : public AComponent {
        public:
            ADoor() {
                Pin input(Pin::Input);
                Pin output(Pin::Output);

                for (int i = 0; i < 2; i++)
                    pins.push_back(input);
                pins.push_back(output);
            }
    };
}

#endif /* !ADOOR_HPP_ */
