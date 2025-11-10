#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <thread>
#include <sstream>
#include <string>

const std::string ANSI = "\001b",
RED = ANSI + "[31m",
GREEN = ANSI + "[32m",
RESET = ANSI + "[0m";

// Проект middle магазин

// 1) 10 видов товара. Айди, название, цена, кол-во 
// 2) Только строковый ввод
// 3) Чистота main() 
// 4) Учетные записи и их права. 3 шт
// 5) Сложности логинов и паролей 
// 6) Склад. Изменения цен, названия, списания товара, пополнение склада. 
// 7) Премии с продаж 
// 8) Нейминг 
// 9) Продажи + скидки + способы оплаты
// 10) Режим "сына маминой подруги"

void start();
bool login();
void storage();
void accounts();
void premium();
void sales();
void discounts();
void payment();
void momFriendSon();

std::vector<std::string> loginNames{ "admin","user" }, passwords{ "admin","user" },
userRights{ "Супер администратор","Администратор","Сотрудник" },
rights{ userRights[0],userRights[1],userRights[2] };
std::vector<std::size_t> id{ 1,2,3,4,5,6,7,8,9,10 }, count{ 4,6,5,2,1,8,9,10,3,7 };
std::vector<double> price{ 49.0,56.0,44.0,45.0,39.0,42.0,55.9,59.0,30.0,50.0 };
std::vector<std::string> productName{
    "The C++ programming language",
    "The C programming language",
    "The Java programming language",
    "MySQL database",
    "Kafka Book",
    "CMake For C++",
    "Bash line Linux",
    "Linux like kernel in computer system",
    "Grok algorithms",
    "The clean architecture"
};

bool login() {
    std::string loginName = "", password = ""; short exit = 0;
    std::cout << "Хотите Вы выйти из системы. Напишите 1 если да. Если нет то напишите любое число:\n";
    std::cin >> exit;
    if (exit == 1) {
        return false;
    }
    else {
        std::cout << std::right << std::setw(62) << "Авторизация\n";
        std::cout << "Введите своё имя пользователя:\n";
        std::cin >> loginName;
        std::cout << "Введите свой пароль:\n";
        std::cin >> password;
        if (loginName.size() < 5 || password.size() < 5) {
            std::cerr << RED << "Логин или пароль меньше указанных параметров.\n" << "Попробуйте еще раз" << RESET << std::endl;
            login();
        }
        else if (loginName == loginNames[0] && password == passwords[0]) {
            std::cout << "Пользователь: " << loginNames[0] << " успешно вошел в систему\n";
            std::cout << "Статус: " << userRights[0] << std::endl;
            return true;
        }
        else if (loginName != loginNames[0] && password != passwords[0]) {
            auto from_first_name_user = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
            auto find_loginName = std::find(loginNames.begin(), loginNames.end(), loginName);
            std::cout << GREEN + "Пользователь " << loginNames[std::distance(from_first_name_user, find_loginName)]
                << " успешно вошел в систему" << RESET << std::endl;
            std::cout << "Ваш статус: " << userRights[std::distance(from_first_name_user, find_loginName)] << "\n";
            return true;
        }
        else {
            std::cerr << "Некорректный ввод" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            system("cls");
        }
        return false;
    }
}

void accounts() {}

void premium() {};

void sales() {};

void discounts() {};

void payment() {
    std::string select_payment_operation = "", number_card = "", CVC = "", espiration_date = "";
    std::string numbers_from_espiration_date[2];
    std::size_t full_numbers = 0;
    std::string payments[]{"","Электронная карта (Мир Visa Mastercard)","Наличные"};
    for (std::size_t payment_way = 1; payment_way < 3; ++payment_way) {
        std::cout << payment_way << ") " << payments[payment_way] << std::endl;
    }
    std::cout << "Выберите способ оплаты товара:\n";
    std::cin >> select_payment_operation;
    if (std::stoi(select_payment_operation) == 1) {
        std::cout << "Введите номер своей карты: \n";
        std::cin >> number_card;
        std::cout << "Введите CVC карты:\n";
        std::cin >> CVC;
        std::cout << "Введите срок годности карты:\n";
        std::cin >> espiration_date;
        std::istringstream divide_espiration_date(espiration_date);
        std::string divide_string = "";
        while (divide_espiration_date >> divide_string) {
            numbers_from_espiration_date[full_numbers] = divide_string;
        }
        std::size_t count_spaces = std::count(number_card.begin(),number_card.end(),' ');
        if (number_card.size() < 19 || count_spaces != 3) {
            std::cerr << RED << "Номер карты должен быть 16-значным. Попробуйте еще раз" << RESET << std::endl;
            payment();
        } else if(CVC.size() < 3 || !std::isdigit(CVC.at(0))) {
            std::cerr << RED << "Код CVC для карты должен быть трехзначным. Попробуйте еще раз" << RESET << std::endl;
            payment();
        } else if (
            std::stoi(numbers_from_espiration_date[0]) < 1 || std::stoi(numbers_from_espiration_date[0]) > 12 && 
            std::stoi(numbers_from_espiration_date[1]) < 25) {
            std::cerr << RED << "Неверное указание срока годности карты. Попробуйте еще раз" << RESET << std::endl;
            payment();
        }
        else {

        }
    }
};

void momFriendSon() {};

void menu(short attempt) {
    if (attempt >= 10) {
        std::cerr << "Было использовано более 10 попыток при выборе опции. Попробуйте позже через 5 минут\n";
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::string option = "";
    std::cout << std::right << std::setw(62) << "Возрождение май\n";
    std::string menu_types[]{ "","Товары","Учетные записи","Премии с продаж","Продажи","Скидки","Способы оплаты","Склад","Сын маминой подруги" };
    for (std::size_t i = 1; i < 9; ++i) {
        std::cout << i << ") " << menu_types[i] << "\n";
    }
    std::cout << "Выберите опцию:\n";
    std::cin >> option;
    switch (std::stoi(option)) {
    case 1:
        start();
        break;
    case 2:
        accounts();
        break;
    case 3:
        premium();
        break;
    case 4:
        sales();
        break;
    case 5:
        discounts();
        break;
    case 6:
        payment();
        break;
    case 7:
        storage();
        break;
    case 8:
        momFriendSon();
        break;
    default:
        std::cerr << "Такой опции не существует. Повторите попытку:\n";
        attempt++;
        menu(attempt);
        break;
    }
}

void start() {
    if (login()) {
        std::cout << "Айди: ";
        for (std::size_t i = 0; i < 10; ++i) {
            std::cout << id[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Наименование товара: ";
        for (std::size_t i = 0; i < 10; ++i) {
            std::cout << productName[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Цена: ";
        for (std::size_t i = 0; i < 10; ++i) {
            std::cout << price[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Количество: ";
        for (std::size_t i = 0; i < 10; ++i) {
            std::cout << count[i] << " ";
        }
    } 
}

void storage() {
    std::string operation = "", _id = "", _price = "";
    std::string operations[]{ "","Изменение цен","Изменение названия товара","Списание товара","Пополнение склада","Выйти со склада"};
    for (auto i = 1; i < 6; ++i) {
        std::cout << i << ") " << operations[i] << std::endl;
    }
    std::cout << "Выберите операцию по работе с товарами: \n";
    std::cin >> operation;
    if (std::stoi(operation) == 1) {
        std::cout << "Напишите id товара для изменения цены: \n";
        std::cin >> _id;
        if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
            std::cerr << RED << "Ошибка. Товара с таким id не существует. Повторите еще раз" << RESET << std::endl;
            storage();
        }
        else {
            std::cout << "Напишите цены товара: \n";
            std::cin >> _price;
            auto find_necessary_price = std::find(price.begin(),price.end(),std::stoi(_price));
            auto find_from_first_element = std::find(price.begin(), price.end(), price.at(0));
            price[std::distance(find_from_first_element, find_necessary_price)] = std::stoi(_price);
            std::cout << GREEN << "Цена товара успешно изменена" << RESET << std::endl;
            storage();
        }
    } else if (std::stoi(operation) == 2) {
        std::cout << "Напишите id товара\n";
        std::cin >> _id;
        if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
            std::cerr << RED << "Ошибка. Товара с таким id не существует. Повторите еще раз" << RESET << std::endl;
            storage();
        }
        else {
            std::string newName = "";
            std::cout << "Напишите новое название товара:\n";
            std::cin >> newName;
            auto find_id = std::find(id.begin(),id.end(),std::stoi(_id));
            auto find_from_first_id = std::find(id.begin(), id.end(),id.at(0));
            productName[std::distance(find_from_first_id, find_id)] = newName;
            std::cout << GREEN << "Название товара было успешно изменено" << RESET << std::endl;
        }
    }
    else if (std::stoi(operation) == 3) {
        std::string select_type = "";
        std::cout << "Выберите тип списания товара:\n";
        std::cout << "1. Уменьшить количество товара\n";
        std::cout << "2. Сделать товар не доступным" << std::endl;
        std::cin >> select_type;
        if (std::stoi(select_type) < 1 || std::stoi(select_type) > 2) {
            std::cerr << "Выберите правильный тип списания товара" << std::endl;
            storage();
        }
        else if (std::stoi(select_type) == 1) {
            std::string newCount = "";
            std::cout << "Напишите id товара:\n";
            std::cin >> _id;
            if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
                std::cerr << RED << "Товар с таким id не существует. Попробуйте еще раз" << std::endl;
                storage();
            }
            else {
                auto find_id = std::find(id.begin(), id.end(), std::stoi(_id));
                auto find_from_first = std::find(id.begin(), id.end(), id.at(0));
                std::cout << "Напишите количество товара для уменьшения\n";
                std::cin >> newCount;
                if (std::stoi(newCount) > count[std::distance(find_from_first, find_id)]) {
                    std::cerr << RED << "Новое количество превышает текущее количество товара. Попробуйте еще раз" << RESET << std::endl;
                    storage();
                }
                else {
                    count[std::distance(find_from_first, find_id)] = std::stoi(newCount);
                    std::cout << GREEN << "Количество товара успешно уменьшено" << RESET << std::endl;
                    menu(1);
                }
            }
        }
        else {
            std::cout << "Напишите id товара:\n";
            std::cin >> _id;
            if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
                std::cerr << RED << "Товар с таким id не существует. Попробуйте еще раз" << RESET << std::endl;
                storage();
            }
            else {
                auto find_necessary_id = std::find(id.begin(),id.end(),std::stoi(_id));
                auto find_from_first_id = std::find(id.begin(), id.end(), id.at(0));
                auto find_necessary_product = std::find(
                    productName.begin(),
                    productName.end(),
                    productName[std::distance(find_from_first_id,find_necessary_id)]
                );
                productName.erase(find_necessary_product);
                auto find_necessary_price = std::find(
                    price.begin(),
                    price.end(),
                    price[std::distance(find_from_first_id,find_necessary_id)]
                );
                price.erase(find_necessary_price);
                auto find_necessary_count = std::find(
                    count.begin(),
                    count.end(),
                    count[std::distance(find_from_first_id,find_necessary_id)]);
                id.erase(find_necessary_id);
            }
        }
    }    
    else if (std::stoi(operation) == 4) {
        std::cout << "Напишите новое id товара: \n";
        std::cin >> _id;
        std::string newNameProduct = "", newCount = "", newPrice = "";
        std::cout << "Напишите новое название товара:\n";
        std::cin >> newNameProduct;
        if (std::isdigit(newNameProduct.at(0))) {
            std::cerr << RED << "Ошибка наименования товара. Попробуйте еще раз" << RESET << std::endl;
            storage();
        }
        std::cout << "Напишите количество нового товара:\n";
        std::cin >> newCount;
        if (std::isalpha(newCount.at(0))) {
            std::cerr << RED << "Ошибка указания количества товара. Попробуйте еще раз" << RESET << std::endl;
            storage();
        }
        std::cout << "Напишите цену нового товара:\n";
        std::cin >> newPrice;
        if (std::isalpha(newPrice.at(0))) {
            std::cerr << RED << "Ошибка указания цены товара. Попробуйте еще раз" << RESET << std::endl;
            storage();
        }
        id.emplace_back(_id);
        productName.emplace_back(newNameProduct);
        count.emplace_back(newCount);
        price.emplace_back(newPrice);
        std::cout << GREEN << "Товар успешно добавлен на склад магазина" << RESET << std::endl;
        menu(1);
    }
    else if (std::stoi(operation) == 5) {
        std::cout << "Выход со склада" << std::endl;
        menu(1);
    }
    else {
        std::cerr << "Такой операции не существует. Повторите еще раз\n";
        storage();
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    menu(1);

    return 0;
}
