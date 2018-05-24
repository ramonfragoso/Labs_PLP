#ifndef PLP_RESTAURANT_H
#define PLP_RESTAURANT_H

#endif //PLP_RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include "item.h"

namespace rst {

    struct Restaurant {
        std::string name;
        std::string cnpj;
        std::string phone;
        std::string cuisine;
        // Ramon // adicionei a senha, o login sera o cnpj
        std::string password;
        std::vector<item::Item> menu;
        int opensAt[2];
        int closesAt[2];
    };

    Restaurant newRestaurant() {
        Restaurant rest;
        std::cin.get();
        std::cout << "Insira o nome do restaurante: ";
        getline(std::cin, rest.name);
        std::cout << "Insira o CNPJ(este sera o seu login): ";
        getline(std::cin, rest.cnpj);
        std::cout << "Insira o telefone: ";
        getline(std::cin, rest.phone);
        std::cout << "Qual o tipo de cozinha desse restaurante? ";
        getline(std::cin, rest.cuisine);
        std::cout << "Que horas o restaurante abre (hh:mm)? ";
        std::cin >> rest.opensAt[0] >> rest.opensAt[1];
        std::cout << "Que horas o restaurante fecha (hh:mm)? ";
        std::cin >> rest.closesAt[0] >> rest.closesAt[1];
        std::cout << "Pra finalizar, defina sua senha: ";
        std::cin.get();
        getline(std::cin, rest.password);

        return rest;
    }

    std::string toString(Restaurant &rest){
        std::ostringstream output;

        output << rest.name << " - " << rest.cuisine << " - " << rest.phone;

        return output.str();
    }

    std::string listaRestaurantes(std::vector<rst::Restaurant> rests){
        std::ostringstream output;
        int i = -1;
        for (auto it = rests.begin(); it != rests.end(); it++){
            i++;
            output << "( " << i << " ) " << rst::toString(*it) << "\n";
        }

        return output.str();
    }

    void addItem(Restaurant &rest) {
        item::Item item = item::newItem();
        rest.menu.push_back(item);
    }

    void removeItem(Restaurant &rest, int index) {
        rest.menu.erase(rest.menu.begin() + index);
    }

    std::string showMenu(Restaurant &rest){
        std::ostringstream output;

        for (auto it = rest.menu.begin(); it != rest.menu.end() - 1; it++) {
            output << item::toString(*it) << std::endl;
        }

        output << item::toString(rest.menu.back());
        return output.str();
    }



    bool isOpen(Restaurant &rest) {
        const std::time_t time = std::time(nullptr);
        std::tm cal = *std::localtime(&time);
        std::stringstream sstrMin, sstrHor;
        sstrMin << std::put_time(&cal, "%M");
        sstrHor << std::put_time(&cal, "%H");
        std::string minute = sstrHor.str();
        std::string hour = sstrMin.str();
        int fTime[] = {std::stoi(hour), std::stoi(minute)};

        bool open = false;
        if (rest.opensAt[0] < fTime[0] && fTime[0] < rest.closesAt[0]) {
            open = true;

        } else if (rest.opensAt[0] == fTime[0] && rest.opensAt[1] <= fTime[1]) {
            open = true;

        } else if (rest.closesAt[0] == fTime[0] && rest.closesAt[1] > fTime[1]) {
            open = true;
        }

        return open;
    };
}