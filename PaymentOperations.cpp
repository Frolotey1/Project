#include "PaymentOperations.h"
#include "StorageOperations.h"
#include "EnterPoint.h"

void payment(std::string product, double product_price, std::size_t count) {
    saled_products.emplace_back(product);
    if (is_mom_friend_son == 1) {
        result_saled_products.emplace_back(0.0);
    }
    else {
        result_saled_products.emplace_back(product_price * (double)count);
    }
    result_count_products.emplace_back(count);
    std::string select_payment_operation = "0", number_card = "", CVC = "", espiration_date = "", count_cash = "", get_check = "";
    double get_cash = 0;
    std::string numbers_from_espiration_date[2];
    if (product == discount_product) {
        if (is_black_friday == 1) {
            std::cout << "Акция: 'Черная пятница'." << "На товар '" << product << "' действует скидка на " << procent_discount << "% на сумму " << product_price << " рублей" << RESET << std::endl;
        }
        else if (discount_sale == 1) {
            std::cout << "Акция: 'Ноябрьская распродажа'." << "На товар '" << product << "' действует скидка на " << procent_discount << "% на сумму " << product_price << " рублей" << RESET << std::endl;
        }
    }
    std::size_t full_numbers = 0;
    double sum_for_paying = product_price * (double)count;
    std::string payments[]{ "","Электронная карта (Мир Visa Mastercard)","Наличные" };
    for (std::size_t payment_way = 1; payment_way < 3; ++payment_way) {
        std::cout << "<" << payment_way << "> " << payments[payment_way] << std::endl;
    }
    std::cout << LIGHT_BLUE << "Выберите способ оплаты товара:\n" << RESET;
    std::cin >> select_payment_operation;
    if (std::stoi(select_payment_operation) == 1) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите номер своей карты: \n";
        std::getline(std::cin, number_card);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите CVC карты:\n";
        std::getline(std::cin, CVC);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите срок годности карты:\n";
        std::getline(std::cin, espiration_date);
        std::istringstream divide_espiration_date(espiration_date);
        std::string divide_string = "";
        while (divide_espiration_date >> divide_string) {
            numbers_from_espiration_date[full_numbers] = divide_string;
        }
        std::size_t count_spaces = std::count(number_card.begin(), number_card.end(), ' ');
        if (number_card.size() < 19 && count_spaces != 3) {
            std::cerr << RED << "Номер карты должен быть 16-значным. Попробуйте еще раз" << RESET << std::endl;
            payment(product, product_price, count);
        }
        else if (CVC.size() < 3 || !std::isdigit(CVC.at(0), std::locale(""))) {
            std::cerr << RED << "Код CVC для карты должен быть трехзначным. Попробуйте еще раз" << RESET << std::endl;
            payment(product, product_price, count);
        }
        else if (
            std::stoi(numbers_from_espiration_date[0]) < 1 || std::stoi(numbers_from_espiration_date[0]) > 12 &&
                                                                  std::stoi(numbers_from_espiration_date[1]) < 25) {
            std::cerr << RED << "Неверное указание срока годности карты. Попробуйте еще раз" << RESET << std::endl;
            payment(product, product_price, count);
        }
        else {
            if (is_mom_friend_son == 1) {
                sum_for_paying = 0.0;
            }
            std::cout << "Стоимость товара '" << product << "'" << " с учетом количеством в " << count << ": " << sum_for_paying << " рублей\n";
            std::cout << "Введите стоимость товара для его приобретения:\n";
            std::cin >> count_cash;
            if (is_mom_friend_son == 1) {
                get_cash = 0;
            }
            else {
                get_cash = std::stod(count_cash);
            }
            if (get_cash >= sum_for_paying) {
                std::cout << GREEN << "Оплата успешно проведена на сумму " << get_cash << " рублей\n" << RESET;
                std::cout << "Хотите получить чек? Если да, то напишите 1. Если нет то 0:\n";
                std::cin >> get_check;
                if (std::stoi(get_check) == 1) {
                    std::cout << "Подождите";
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    std::cout << ".";
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    std::cout << ".";
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    std::cout << ".";
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    std::cout << std::right << std::setw(62) << "Кассовый чек\n";
                    std::cout << "Покупка №1488 Смена 666\n";
                    std::cout << "Товар: " << product << "\n";
                    std::cout << "Итог: " << get_cash << " рублей\n";
                    std::cout << "Сдача: " << get_cash - sum_for_paying << " рублей\n";
                    std::cout << "-------------------------------------------\n";
                    std::cout << "666666 г. Екатеринбург ул. Фурманова 57\n";
                    auto date = std::chrono::system_clock::now();
                    std::cout << std::format("Дата оформления чека: {}", date) << std::endl;
                    count_sales++; earned_money += get_cash - sum_for_paying;
                    std::cout << "Для продолжения покупки товаров напишите 1. другая цифра - выйти в меню" << std::endl;
                    std::string continue_shopping = "";
                    std::cin >> continue_shopping;
                    if (std::stoi(continue_shopping) == 1) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        system("cls");
                        start(1);
                    }
                    else {
                        menu(1);
                    }
                }
                else {
                    std::cout << GREEN << "Товар успешно приобретен" << RESET << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    count_sales++;
                    menu(1);
                }
            }
            else {
                std::cerr << RED << "Недостаточно средств на счету" << RESET << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                system("cls");
                menu(1);
            }
        }
    }
    else if (std::stoi(select_payment_operation) == 2) {
        if (is_mom_friend_son == 1) {
            sum_for_paying = 0.0;
        }
        std::cout << "Для приобретения товара '" << product << "' вам нужно оплатить " << sum_for_paying << " рублей\n" << RESET;
        std::cin >> count_cash;
        if (is_mom_friend_son == 1) {
            get_cash = std::stod(count_cash);
            get_cash = 0;
        }
        else {
            get_cash = std::stod(count_cash);
        }
        if (std::stod(count_cash) >= sum_for_paying) {
            std::cout << GREEN << "Оплата товара '" << product << "' прошла успешно\n" << RESET;
            std::cout << "Хотите получить чек? Напишите 1 если да, если нет то 0:\n";
            std::cin >> get_check;
            if (std::stoi(get_check) == 1) {
                std::cout << "Подождите";
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                std::cout << ".";
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                std::cout << ".";
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                std::cout << ".";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << YELLOW << std::right << std::setw(62) << "Кассовый чек\n" << RESET;
                std::cout << "Покупка №1488 Смена 666\n";
                std::cout << "Товар: " << product << "\n";
                std::cout << "Итог: " << get_cash << " рублей\n";
                std::cout << "Сдача: " << get_cash - sum_for_paying << " рублей\n";
                std::cout << "-------------------------------------------\n";
                std::cout << "666666 г. Екатеринбург ул. Фурманова 57\n";
                auto date = std::chrono::system_clock::now();
                std::cout << std::format("Дата оформления чека: {}",date) << std::endl;
                count_sales++; earned_money += get_cash - sum_for_paying;
                std::cout << "Для продолжения покупки товаров напишите 1. 0 - выйти в меню" << std::endl;
                std::string continue_shopping = "";
                std::cin >> continue_shopping;
                if (std::stoi(continue_shopping) == 1) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    system("cls");
                    start(1);
                }
                else {
                    menu(1);
                }
            }
            else {
                std::cout << GREEN << "Товар успешно приобретен" << RESET << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                count_sales++;
                menu(1);
            }
        }
        else {
            std::cerr << RED << "Недостаточно средств на счету" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("cls");
            menu(1);
        }
    }
}

void sales() {
    if (client == "Покупатель") {
        std::cerr << RED << "У вас недостаточно прав на просмотр отчета продаж" << RESET << std::endl;
        menu(1);
    }
    std::cout << YELLOW << std::right << std::setw(62) << "Итоги продаж за день\n" << RESET;
    double sum_saled_product = 0.0;
    std::cout << "Наименование товара" << "\t" << "Количество" << "\t" << "Сумма" << "\n";
    for (std::size_t i = 0; i < saled_products.size(); ++i) {
        std::cout << saled_products[i] << "\t\t" << result_count_products[i] << "\t\t" << result_saled_products[i] << "\n";
        sum_saled_product += result_saled_products[i];
    }
    std::cout << YELLOW << "Итоговая сумма с проданных товаров: " << sum_saled_product << " рублей" << RESET << std::endl;
    menu(1);
}
