#include "StorageOperations.h"
#include "PremiumAndDiscounts.h"
#include "PaymentOperations.h"
#include "EnterPoint.h"

void start(short attempt) {
    if (attempt >= 10) {
        std::cout << YELLOW << "Превышено количество попыток для выбора товара. Попробуйте позже" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
    for (std::size_t i = 0; i < 10; ++i) {
        std::cout << id[i] << "\t" << productName[i] << "\t\t" << price[i] << "\t" << count[i] << std::endl;
    }
    std::string exit = "0";
    std::cout << "Хотите ли Вы выйти в меню. Если да, то напишите 1: " << std::endl;
    std::cin >> exit;
    if (std::stoi(exit) == 1) {
        menu(1);
    }
    std::string select_id_product = "0", count_product = "0";
    std::cout << "Напишите айди продукта для покупки:\n";
    std::cin >> select_id_product;
    if (!std::isdigit(select_id_product.at(0), std::locale(""))) {
        std::cerr << RED << "Ошибка ввода айди товара. Попробуйте еще раз" << RESET << std::endl;
        attempt++;
        start(attempt);
    }
    std::cout << "Напишите количество продукта:\n";
    std::cin >> count_product;
    if (!std::isdigit(count_product.at(0), std::locale(""))) {
        std::cerr << RED << "Ошибка ввода количества товара. Попробуйте еще раз" << RESET << std::endl;
        attempt++;
        start(attempt);
    }
    auto find_id_product = std::find(id.begin(), id.end(), std::stoi(select_id_product));
    auto find_from_first = std::find(id.begin(), id.end(), id.at(0));
    if (find_id_product == id.end()) {
        std::cerr << RED << "Такого товара с таким айди нет\nПопробуйте еще раз" << RESET << std::endl;
        attempt++;
        start(attempt);
    }
    if (std::stoi(count_product) > count[std::distance(find_from_first, find_id_product)]) {
        std::cerr << RED << "Ошибка ввода.\nПопробуйте еще раз" << RESET << std::endl;
        attempt++;
        start(attempt);
    }
    else {
        std::string return_product = "0";
        std::cout << "Хотите ли Вы вернуть товар. Если да, то напишите 1:\n";
        std::cin >> return_product;
        if (std::stoi(return_product) == 1) {
            select_id_product = "0";
            count_product = "0";
            std::cout << GREEN << "Товар успешно возврашен." << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            system("cls");
            start(1);
        }
        else {
            count[std::distance(find_from_first, find_id_product)] -= std::stoi(count_product);
            auto find_id_from_first = std::find(id.begin(), id.end(), id.at(0));
            payment(productName[std::distance(find_id_from_first, find_id_product)],
                    price[std::distance(find_id_from_first, find_id_product)], std::stoi(count_product));
        }
    }
}
void storage(short attempt) {
    std::string get_login = "";
    std::cout << LIGHT_BLUE << "Напишите свой логин: " << RESET << std::endl;
    std::cin >> get_login;
    auto find_login = std::find(loginNames.begin(), loginNames.end(), get_login);
    auto find_from_first_login = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
    if (find_login == loginNames.end()) {
        std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl;
        menu(1);
    }
    if (rights[std::distance(find_from_first_login, find_login)] == "Супер-администратор") {
        if (count_changed_storage_times >= 100) {
            std::string check_premium = "";
            std::cout << YELLOW << "Уважаемый '" << get_login << "' со статусом '" << rights[std::distance(find_from_first_login, find_login)] << "' " <<
                "!\nВам пришло уведомление, связанное с достижением определенного количества изменений на складу для получения премии.\nНапишите 1 для просмотра премиума, любую другую цифру для отказа просмотра\n" << RESET;
            std::cin >> check_premium;
            if (std::stoi(check_premium) == 1) {
                premium(get_login, rights[std::distance(find_from_first_login, find_login)]);
            }
        }
        std::string select_storage = "";
        std::cout << LIGHT_BLUE << "Выберите тип работы со складом:\n" << RESET;
        std::cout << "<1> Работать с готовым складом\n";
        std::cout << "<2> Выход со склада" << std::endl;
        std::cin >> select_storage;
        if (std::stoi(select_storage) == 1) {
            std::cout << LIGHT_BLUE << "Выберите операцию по работе с товарами: \n" << RESET;
        }
        else if (std::stoi(select_storage) == 2) {
            menu(1);
        }
        else {
            std::cerr << RED << "Неверный тип склада. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            storage(attempt);
        }
        std::string _id = "", _price = "", operation = "";
        std::cout << "<1> Изменение цены\n";
        std::cout << "<2> Изменение названия товара\n";
        std::cout << "<3> Списание товара\n";
        std::cout << "<4> Добавить новый товар\n";
        std::cout << "<5> Изменение id товара\n";
        std::cout << "<6> Выход со склада\n";
        std::cin >> operation;
        if (std::stoi(operation) == 1) {
            std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << id[i] << "\t" << productName[i] << "\t" << price[i] << "\t" << count[i] << std::endl;
            }
            std::cout << "Напишите айди товара для изменения цены: \n";
            std::cin >> _id;
            if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
                std::cerr << RED << "Ошибка. Товара с таким айди нет. Повторите еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            else {
                std::cout << "Напишите цену товара: \n";
                std::cin >> _price;
                auto find_necessary_price = std::find(price.begin(), price.end(), std::stoi(_price));
                auto find_from_first_element = std::find(price.begin(), price.end(), price.at(0));
                price[std::distance(find_from_first_element, find_necessary_price)] = std::stoi(_price);
                std::cout << GREEN << "Цена товара успешно изменена" << RESET << std::endl;
                count_changed_storage_times++;
                menu(1);
            }
        }
        else if (std::stoi(operation) == 2) {
            std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << id[i] << "\t" << productName[i] << "\t" << price[i] << "\t" << count[i] << std::endl;
            }
            std::cout << "Напишите id товара\n";
            std::cin >> _id;
            if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
                std::cerr << RED << "Ошибка. Товара с таким айди нет. Повторите еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            else if (!std::isdigit(_id.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка написания айди товара. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            else {
                std::string newName = "";
                std::cout << "Напишите новое название товара:\n";
                std::cin >> newName;
                auto find_id = std::find(id.begin(), id.end(), std::stoi(_id));
                auto find_from_first_id = std::find(id.begin(), id.end(), id.at(0));
                productName[std::distance(find_from_first_id, find_id)] = newName;
                std::cout << GREEN << "Название товара было успешно изменено" << RESET << std::endl;
                count_changed_storage_times++;
                menu(1);
            }
        }
        else if (std::stoi(operation) == 3) {
            std::string select_type = "";
            std::cout << LIGHT_BLUE << "Выберите тип списания товара:\n" << RESET;
            std::cout << "<1> Уменьшить количество товара\n";
            std::cout << "<2> Сделать товар не доступным" << std::endl;
            std::cin >> select_type;
            if (std::stoi(select_type) < 1 || std::stoi(select_type) > 2) {
                std::cerr << RED << "Выберите правильный тип списания товара" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            else if (std::stoi(select_type) == 1) {
                std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
                for (std::size_t i = 0; i < 10; ++i) {
                    std::cout << id[i] << "\t" << productName[i] << "\t\t" << price[i] << "\t" << count[i] << std::endl;
                }
                std::string newCount = "";
                std::cout << "Напишите id товара:\n";
                std::cin >> _id;
                if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
                    std::cerr << RED << "Товара с таким айди нет. Попробуйте еще раз" << RESET << std::endl;
                    attempt++;
                    storage(attempt);
                }
                else {
                    auto find_id = std::find(id.begin(), id.end(), std::stoi(_id));
                    auto find_from_first = std::find(id.begin(), id.end(), id.at(0));
                    std::cout << "Напишите количество товара для уменьшения\n";
                    std::cin >> newCount;
                    if (std::stoi(newCount) > count[std::distance(find_from_first, find_id)]) {
                        std::cerr << RED << "Новое количество превышает текущее количество товара. Попробуйте еще раз" << RESET << std::endl;
                        attempt++;
                        storage(attempt);
                    }
                    else {
                        count[std::distance(find_from_first, find_id)] = std::stoi(newCount);
                        std::cout << GREEN << "Количество товара успешно уменьшено" << RESET << std::endl;
                        count_changed_storage_times++;
                        menu(1);
                    }
                }
            }
            else {
                std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
                for (std::size_t i = 0; i < 10; ++i) {
                    std::cout << id[i] << "\t" << productName[i] << "\t" << price[i] << "\t" << count[i] << std::endl;
                }
                std::cout << "Напишите айди товара:\n";
                std::cin >> _id;
                if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
                    std::cerr << RED << "Товар с таким айди нет. Попробуйте еще раз" << RESET << std::endl;
                    attempt++;
                    storage(attempt);
                }
                else {
                    auto find_necessary_id = std::find(id.begin(), id.end(), std::stoi(_id));
                    auto find_from_first_id = std::find(id.begin(), id.end(), id.at(0));
                    auto find_necessary_product = std::find(
                        productName.begin(),
                        productName.end(),
                        productName[std::distance(find_from_first_id, find_necessary_id)]
                        );
                    productName.erase(find_necessary_product);
                    auto find_necessary_price = std::find(
                        price.begin(),
                        price.end(),
                        price[std::distance(find_from_first_id, find_necessary_id)]
                        );
                    price.erase(find_necessary_price);
                    auto find_necessary_count = std::find(
                        count.begin(),
                        count.end(),
                        count[std::distance(find_from_first_id, find_necessary_id)]);
                    count.erase(find_necessary_count);
                    id.erase(find_necessary_id);
                    std::cout << GREEN << "Списание товара прошло успешно" << RESET << std::endl;
                    count_changed_storage_times++;
                    menu(1);
                }
            }
        }
        else if (std::stoi(operation) == 4) {
            std::cout << "Напишите новое айди товара: \n";
            std::cin >> _id;
            auto check_existed_id = std::find(id.begin(), id.end(), std::stoi(_id));
            if (check_existed_id != id.end()) {
                std::cerr << RED << "Такой айди уже существует. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            std::string newNameProduct = "", newCount = "", newPrice = "";
            std::cout << "Напишите новое название товара:\n";
            std::cin >> newNameProduct;
            if (!std::isalpha(newNameProduct.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка наименования товара. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            std::cout << "Напишите количество нового товара:\n";
            std::cin >> newCount;
            if (std::isalpha(newCount.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания количества товара. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            std::cout << "Напишите цену нового товара:\n";
            std::cin >> newPrice;
            if (std::isalpha(newPrice.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания цены товара. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            id.emplace_back(std::stoi(_id));
            productName.emplace_back(newNameProduct);
            count.emplace_back(std::stoi(newCount));
            price.emplace_back(std::stod(newPrice));
            std::cout << GREEN << "Товар успешно добавлен на склад магазина" << RESET << std::endl;
            count_changed_storage_times++;
            menu(1);
        }
        else if (std::stoi(operation) == 5) {
            std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << id[i] << "\t" << productName[i] << "\t" << price[i] << "\t" << count[i] << std::endl;
            }
            std::cout << "Напишите айди для товара:\n";
            std::cin >> _id;
            auto find_id = std::find(id.begin(), id.end(), std::stoi(_id));
            if (find_id == id.end()) {
                std::cerr << RED << "Товар с таким айди не найден. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            else {
                std::string new_id = "";
                std::cout << "Напишите новое айди товара:\n";
                std::cin >> new_id;
                auto find_from_first_id = std::find(id.begin(), id.end(), id.at(0));
                id[std::distance(find_from_first_id, find_id)] = std::stoi(new_id);
                std::cout << GREEN << "Айди " << _id << " для товара '" << productName[std::distance(find_from_first_id, find_id)] << "' был успешно изменен на " << new_id << RESET << std::endl;
                count_changed_storage_times++;
                menu(1);
            }
        }
        else if (std::stoi(operation) == 6) {
            std::cout << LIGHT_BLUE << "Выход со склада" << RESET << std::endl;
            menu(1);
        }
        else {
            std::cerr << RED << "Такой операции не существует. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            storage(attempt);
        }
    }
    else if (rights[std::distance(find_from_first_login, find_login)] == "Администратор") {
        if (count_changed_storage_times >= 100) {
            std::string check_premium = "";
            std::cout << YELLOW << "Уважаемый '" << get_login << "' со статусом '" << rights[std::distance(find_from_first_login, find_login)] << "' " <<
                "!\nВам пришло уведомление, связанное с достижением определенного количества изменений на складу для получения премии.\nНапишите 1 для просмотра премиума, любую другую цифру для отказа просмотра\n" << RESET;
            std::cin >> check_premium;
            if (std::stoi(check_premium) == 1) {
                premium(get_login, rights[std::distance(find_from_first_login, find_login)]);
            }
        }
        std::cout << LIGHT_BLUE << "Выберите опцию по работе с товарами\n" << RESET;
        std::cout << "<1> Отчёт продаж\n";
        std::cout << "<2> Изменение товара\n";
        std::cout << "<3> Выход со склада" << std::endl;
        std::string option = "";
        std::cin >> option;
        if (std::stoi(option) == 1) {
            sales();
        }
        else if (std::stoi(option) == 2) {
            std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << id[i] << "\t" << productName[i] << "\t\t" << price[i] << "\t" << count[i] << std::endl;
            }
            std::string check_id = "", new_id = "", new_count = "", new_price = "", new_name = "";
            std::cout << "Напишите товар для его изменения по айди:\n";
            std::cin >> check_id;
            auto find_id = std::find(id.begin(), id.end(), std::stoi(check_id));
            auto find_id_from_first = std::find(id.begin(), id.end(), id.at(0));
            if (find_id == id.end()) {
                std::cerr << RED << "Товара с таким айди нет. Повторите попытку" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            std::cout << "Введите новое название для товара:\n";
            std::cin >> new_name;
            if (std::isdigit(new_name.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка наименования товара. Повторите попытку" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            std::cout << "Напишите новое айди товара:\n";
            std::cin >> new_id;
            if (!std::isdigit(new_id.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания нового айди для товара. Повторите попытку" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            std::cout << "Напишите количество нового товара\n";
            std::cin >> new_count;
            if (!std::isdigit(new_count.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания количества нового товара. Повторите попытку" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            std::cout << "Введите новую цену для товара:\n";
            std::cin >> new_price;
            if (!std::isdigit(new_price.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания цены для нового товара" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            productName[std::distance(find_id_from_first, find_id)] = new_name;
            id[std::distance(find_id_from_first, find_id)] = std::stoi(new_id);
            count[std::distance(find_id_from_first, find_id)] = std::stoi(new_count);
            price[std::distance(find_id_from_first, find_id)] = std::stod(new_price);
            std::cout << GREEN << "Товар был успешно изменен" << RESET << std::endl;
            count_changed_storage_times++;
            attempt++;
            storage(attempt);
        }
        else if (std::stoi(option) == 3) {
            std::cout << LIGHT_BLUE << "Выход со склада" << RESET << std::endl;
            menu(1);
        }
        else {
            std::cerr << RED << "Такой опции нет. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            storage(attempt);
        }
    }
    else if (rights[std::distance(find_from_first_login, find_login)] == "Сотрудник") {
        if (count_sales >= 10) {
            std::string check_premium = "";
            std::cout << YELLOW << "Уважаемый '" << get_login << "' со статусом '" << rights[std::distance(find_from_first_login, find_login)] << "' " <<
                "!\nВам пришло уведомление, связанное с достижением определенного количества продажей товаров для получения премии.\nНапишите 1 для просмотра премиума, любую другую цифру для отказа просмотра\n" << RESET;
            std::cin >> check_premium;
            if (std::stoi(check_premium) == 1) {
                premium(get_login, rights[std::distance(find_from_first_login, find_login)]);
            }
        }
        std::cout << LIGHT_BLUE << "Выберите опцию для работы с товарами\n" << RESET;
        std::cout << "<1> Сделать скидку на товар\n";
        std::cout << "<2> Возврат товара\n";
        std::cout << "<3> Выход со склада\n";
        std::string option = "";
        std::cin >> option;
        if (std::stoi(option) < 1 || std::stoi(option) > 3) {
            std::cerr << RED << "Такой опции нет. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            storage(attempt);
        }
        else if (std::stoi(option) == 1) {
            std::string select_id = "";
            std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
            for (std::size_t i = 0; i < productName.size(); ++i) {
                std::cout << id[i] << "\t" << productName[i] << "\t\t" << price[i] << "\t" << count[i] << std::endl;
            }
            std::cout << "Выберите товар по айди для реализации скидки:\n";
            std::cin >> select_id;
            auto find_id = std::find(id.begin(), id.end(), std::stoi(select_id));
            if (find_id == id.end()) {
                std::cerr << RED << "Товара с таким айди нет. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            else {
                auto find_id_from_first = std::find(id.begin(), id.end(), id.at(0));
                discounts(id[std::distance(find_id_from_first, find_id)],
                          price[std::distance(find_id_from_first, find_id)], 1);
            }
        }
        else if (std::stoi(option) == 2) {
            std::string id_product_for_returning = "";
            std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << id[i] << "\t" << productName[i] << "\t\t" << price[i] << "\t" << count[i] << std::endl;
            }
            std::cout << "Напишите товар, который вы хотите вернуть обратно на склад:\n";
            std::cin >> id_product_for_returning;
            auto find = std::find(id.begin(), id.end(), std::stoi(id_product_for_returning));
            if (find == id.end()) {
                std::cerr << RED << "Товара с таким айди нет. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                storage(attempt);
            }
            std::cout << GREEN << "Товар успешно возвращен на склад" << RESET << std::endl;
        }
        else {
            std::cout << LIGHT_BLUE << "Выход со склада" << RESET << std::endl;
            menu(1);
        }
    }
    else {
        std::cerr << RED << "У вас недостаточно прав на работу на складе" << RESET << std::endl;
        menu(1);
    }
}
