#include "PremiumAndDiscounts.h"
#include "EnterPoint.h"
#include "StorageOperations.h"

void discounts(std::size_t id, double product_price, short attempt) {
    std::cout << "1.Черная пятница\n";
    std::cout << "2.Ноябрьская распродажа\n";
    std::string discount = "", type_discount = "";
    id--;
    std::cout << "Введите тип скидки:\n";
    if (std::stoi(type_discount) == 1) {
        std::cout << "Введите скидку на товар '" << productName[id] << "' от 50% до 80%\n";
        std::cin >> discount;
        if (std::stoi(discount) < 50 || std::stoi(discount) > 80) {
            std::cerr << RED << "Ошибка ввода скидки. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            discounts(id, product_price, attempt);
        }
        else if (!std::isdigit(discount.at(0)) || !std::isdigit(discount.at(discount.size() - 1))) {
            std::cerr << RED << "Ошибка ввода скидки. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            discounts(id, product_price, attempt);
        }
        else {
            double new_price = (product_price * std::stod(discount)) / 100.0;
            price[id] = new_price;
            discount_product = productName[id];
            procent_discount = discount;
            is_black_friday = 1;
            std::cout << "Скидка на товар '" << productName[id] << "' была успешно введена" << std::endl;
            menu(1);
        }
    }
    else if (std::stoi(type_discount) == 2) {
        std::cout << "Введите скидку на товар '" << productName[id] << "' от 20% до 30%\n";
        std::cin >> discount;
        if (std::stoi(discount) < 20 || std::stoi(discount) > 30) {
            std::cerr << RED << "Ошибка ввода скидки. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            discounts(id, product_price, attempt);
        }
        else if (!std::isdigit(discount.at(0)) || !std::isdigit(discount.at(discount.size() - 1))) {
            std::cerr << RED << "Ошибка ввода скидки. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            discounts(id, product_price, attempt);
        }
        else {
            double new_price = (product_price * std::stod(discount)) / 100.0;
            price[id] = new_price;
            discount_product = productName[id];
            procent_discount = discount;
            discount_sale = 1;
            std::cout << "Скидка на товар '" << productName[id] << "' была успешно введена" << std::endl;
            menu(1);
        }
    }
    else {
        std::cerr << "Неверный тип скидки. Попробуйте еще раз" << std::endl;
        attempt++;
        discounts(id, product_price, attempt);
    }
}

void premium(std::string login, std::string right) {
    std::string up = "";
    if (right == "Сотрудник") {
        std::cout << GREEN << login << " со статусом '" << right << "' получает вознаграждение в виде:\n" << RESET;
        std::cout << YELLOW << "<1> Возможность подняться до статуса Администратора\n" << RESET;
        std::cout << YELLOW << "<2> Возможность работать по графику 2/2 вместо 5/2\n" << RESET;
        std::cout << YELLOW << "-----------------------------------------------------\n" << RESET;
        std::cout << YELLOW << "Хотите подняться до уровня Администратора - напишите 1\n" << RESET;
        std::cout << YELLOW << "Хотите остаться на том же уровне, но с другим графиком работы - напишите другую цифру\n" << RESET;
        std::cin >> up;
        if (std::stoi(up) == 1) {
            auto find_login = std::find(loginNames.begin(), loginNames.end(), login);
            auto find = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
            rights[std::distance(find, find_login)] = "Администратор";
            std::cout << GREEN << "Сотрудник '" << login << "' был успешно поднят до статуса '" << rights[std::distance(find, find_login)] << "'.\nПоздравляем!" << RESET;
            storage(1);
        }
        else {
            std::cout << "Возвращение в работу" << std::endl;
            storage(1);
        }
    }
    else if (right == "Администратор") {
        std::cout << GREEN << login << " со статусом '" << right << "' получает вознаграждение в виде:\n" << RESET;
        std::cout << YELLOW << "<1>. Возможность подняться до Супер-администратора\n" << RESET;
        std::cout << YELLOW << "<2>. Возможность работать по графику 2/1 вместо 5/1\n" << RESET;
        std::cout << YELLOW << "-----------------------------------------------------\n" << RESET;
        std::cout << YELLOW << "Хотите подняться до уровня Супер-администратора - напишите 1\n" << RESET;
        std::cout << YELLOW << "Хотите остаться на том же уровне, но с другим графиком работы - напишите другую цифру\n" << RESET;
        std::cin >> up;
        if (std::stoi(up) == 1) {
            auto find_login = std::find(loginNames.begin(), loginNames.end(), login);
            auto find = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
            rights[std::distance(find, find_login)] = "Супер-администратор";
            std::cout << GREEN << "Сотрудник '" << login << "' был успешно поднят до статуса '" << rights[std::distance(find, find_login)] << "'.\nПоздравляем!" << RESET;
            storage(1);
        }
        else {
            std::cout << "Возвращение в работу" << std::endl;
            storage(1);
        }
    }
    else {
        std::cout << GREEN << login << " со статусом '" << right << "' получает вознаграждение в виде:\n" << RESET;
        std::cout << YELLOW << "Возможность стать директором магазина\n" << RESET;
        std::cout << YELLOW << "-----------------------------------------------------\n" << RESET;
        std::cout << YELLOW << "Хотите подняться до секретного уровня директора - напишите 1\n" << RESET;
        std::cout << YELLOW << "Хотите остаться на том же уровне, но с другим графиком работы - напишите другую цифру\n" << RESET;
        std::cin >> up;
        if (std::stoi(up) == 1) {
            auto find_login = std::find(loginNames.begin(), loginNames.end(), login);
            auto find = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
            rights[std::distance(find, find_login)] = "Директор";
            std::cout << GREEN << "Сотрудник '" << login << "' был успешно поднят до статуса '" << rights[std::distance(find, find_login)] << "'.\nПоздравляем!" << RESET;
            storage(1);
        }
        else {
            std::cout << "Возвращение в работу" << std::endl;
            storage(1);
        }
    }
}
