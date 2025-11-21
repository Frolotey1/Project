#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <sstream>
#include <locale>
#include <string>

const std::string RED = "\033[31m";
const std::string LIGHT_BLUE = "\033[36m";
const std::string YELLOW = "\033[33m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

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

void start(short attempt);
void login(short attempt);
void storage();
void accounts();
void premium(std::string login, std::string right);
void sales();
void discounts(std::size_t id, double product_price);
void payment(std::string product, double product_price, std::size_t count);
void momFriendSon();
void menu(short attempt);
void registry(short attempt);
void new_storage();
void fines_for_employees();

bool is_employee = 0, is_mom_friend_son = 0, existed_fine = 0;

size_t count_sales = 0, count_changed_storage_times = 0; double earned_money = 0.0;
std::string client;
std::vector<std::string> loginNames,
    passwords,
    userRights{ "Супер-администратор","Администратор","Сотрудник" },
    rights;
std::vector<std::size_t> id{ 1,2,3,4,5,6,7,8,9,10 }, count{ 4,6,5,2,1,8,9,10,3,7 };
std::vector<double> price{ 49.0,56.0,44.0,45.0,39.0,42.0,55.9,59.0,30.0,50.0 };
std::vector<std::string> productName{
    "The C++ Book",
    "The C Book",
    "The Java Book",
    "MySQL database",
    "Kafka Book",
    "CMake For C++",
    "Bash-line Linux",
    "Linux kernel",
    "Grok algorithms",
    "The clean code"
};

std::vector<std::string> saled_products; std::vector<double> result_saled_products;
std::vector<std::size_t> result_count_products;
std::vector<std::string> set_product; std::vector<std::size_t> set_count, set_id;
std::vector<double> set_price;
std::vector<std::size_t> fines;
void fines_for_employees() {
    fines.resize(productName.size());
    std::fill(fines.begin(), fines.end(), 0);
}
void registry(short attempt) {
    if (attempt >= 10) {
        std::cout << YELLOW << "Было использовано около 10 попыток захода в магазин. Попробуйте позже" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::string select_user = "", name = "", password = "", result = "";
    std::string type_user[]{ "","Супер-администратор","Администратор","Сотрудник" };
    std::cout << LIGHT_BLUE << std::right << std::setw(62) << "Регистрация\n" << RESET;
    for (std::size_t show_all_types = 1; show_all_types < 4; ++show_all_types) {
        std::cout << show_all_types << ") " << type_user[show_all_types] << std::endl;
    }
    std::cout << "Выберите тип пользователя, от лица которого вы будете работать с магазином:\n";
    std::cin >> select_user;
    if (std::stoi(select_user) < 1 || std::stoi(select_user) > 3) {
        std::cerr << RED << "Такого типа пользователя не существует." << RESET << std::endl;
        menu(1);
    }
    else {
        if (type_user[std::stoi(select_user)] == "Сотрудник") {
            is_employee = 1;
        }
        std::size_t count_symbol_numbers = 0, find_special_symbols = 0;
        std::cout << "Напишите имя пользователя для типа " << type_user[std::stoi(select_user)] << "\n";
        std::cin >> name;
        auto find_dublicate_name = std::find(loginNames.begin(), loginNames.end(), name);
        if (find_dublicate_name != loginNames.end()) {
            std::cerr << RED << "Такой пользователь уже зарегистрирован в системе. Введите новый логин" << RESET << std::endl; \
                attempt++;
            registry(attempt);
        }
        std::cout << "Напишите пароль для пользователя типа " << type_user[std::stoi(select_user)] << "\n";
        std::cin >> password;
        for (auto& digit : password) {
            if (std::isdigit(digit, std::locale(""))) {
                count_symbol_numbers++;
            }
            else if (!std::isalnum(digit, std::locale(""))) {
                find_special_symbols++;
            }
        }
        if (name.size() < 8 || password.size() < 8) {
            std::cerr << RED << "Логин или пароль меньше указанных параметров. Попробуйте еще раз." << RESET << std::endl;
            attempt++;
            registry(attempt);
        }
        if (count_symbol_numbers == 0 || find_special_symbols == 0) {
            std::cerr << RED << "Пароль должен содержать хотя бы 1 специальный символ и 4 числа" << RESET << std::endl;
            attempt++;
            registry(attempt);
        }
        else {
            loginNames.emplace_back(name);
            passwords.emplace_back(password);
            result = type_user[std::stoi(select_user)];
            rights.emplace_back(result);
            std::cout << GREEN << "Регистрация под типом пользователя '" << type_user[std::stoi(select_user)] <<
                "' прошла успешно" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("cls");
            login(1);
        }
    }
}

void login(short attempt) {
    if (attempt >= 10) {
        std::cout << YELLOW << "Было использовано около 10 попыток захода в магазин. Попробуйте позже" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::string type_enter = "";
    std::cout << LIGHT_BLUE << "Выберите способ захода в магазин" << RESET << std::endl;
    std::cout << "1. Регистрация\n";
    std::cout << "2. Авторизация\n";
    std::cout << "3. Войти как покупатель\n";
    std::cout << "4. Выход из магазина\n";
    std::cin >> type_enter;
    if (std::stoi(type_enter) == 1) {
        registry(1);
    }
    else if (std::stoi(type_enter) == 2) {
        std::string loginName = "", password = "";
        std::cout << LIGHT_BLUE <<  std::right << std::setw(62) << "Авторизация\n" << RESET;
        std::cout << "Введите своё имя пользователя:\n";
        std::cin >> loginName;
        std::cout << "Введите свой пароль:\n";
        std::cin >> password;
        if (loginName.size() < 8 && password.size() < 8) {
            std::cerr << RED << "Логин или пароль меньше указанных параметров. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            login(attempt);
        }
        auto from_first_name_user = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
        auto find_loginName = std::find(loginNames.begin(), loginNames.end(), loginName);
        auto find_password = std::find(passwords.begin(), passwords.end(), password);
        if (find_loginName != loginNames.end() || find_password != passwords.end()) {
            std::cout << GREEN << "Пользователь " << loginNames[std::distance(from_first_name_user, find_loginName)]
                      << " успешно вошел в систему" << RESET << std::endl;
            std::cout << GREEN << "Ваш статус: " << rights[std::distance(from_first_name_user, find_loginName)] << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("cls");
            menu(1);
        }
        else {
            std::cerr << RED << "Ошибка авторизации в магазине. Повторите попытку" << RESET << std::endl;
            attempt++;
            login(attempt);
        }
    }
    else if (std::stoi(type_enter) == 3) {
        client = "Покупатель";
        menu(1);
    }
    else if (std::stoi(type_enter) == 4) {
        std::cout << LIGHT_BLUE << "Завершение программы" << RESET << std::endl;
        exit(0);
    }
    else {
        std::cerr << RED << "Такого способа нет. Попробуйте еще раз" << RESET << std::endl;
        attempt++;
        login(attempt);
    }
}

void accounts() {
    std::string get_login = "", get_password = "";
    std::cout << "Напишите свой логин: " << std::endl;
    std::cin >> get_login;
    auto find_login = std::find(loginNames.begin(), loginNames.end(), get_login);
    if (find_login == loginNames.end()) {
        std::cerr << RED << "Ошибка ввода" << RESET << std::endl;
        menu(1);
    }
    std::cout << "Напишите свой текущий пароль:\n";
    std::cin >> get_password;
    auto find_password = std::find(passwords.begin(),passwords.end(),get_password);
    if (find_password == passwords.end()) {
        std::cerr << RED << "Ошибка ввода" << RESET << std::endl;
        accounts();
    }
    auto find_right = std::find(loginNames.begin(), loginNames.end(), get_login);
    auto find_from_first = std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
    if (rights[std::distance(find_from_first, find_right)] == "Супер-администратор") {
        for (std::size_t i = 0; i < loginNames.size(); ++i) {
            std::cout << "Логин: " << loginNames[i] << " | " << "Пароль: " << passwords[i]
                      << " | " << "Права: " << rights[i] << std::endl;
        }
        std::string operation = "";
        std::cout << "Что хотите изменить:\n";
        std::cout << "1. Пароль\n";
        std::cout << "2. Права\n";
        std::cin >> operation;
        if (std::stoi(operation) == 1) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для смены его пароля:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            auto find_user_login_from_first = std::find(loginNames.begin(),loginNames.end(),loginNames[0]);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка" << RESET << std::endl;
                accounts();
            } else if(rights[std::distance(find_user_login_from_first,find_user_login)] == "Супер-администратор") {
                std::cerr << RED << "Невозможно менять пароль человеку с тем же статусом. Попробуйте еще раз" << RESET << std::endl;
                accounts();
            }
            else {
                auto find_user_login_from_first =
                    std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
                std::cout << "Напишите новый пароль для пользователя:\n";
                std::string new_password = "";
                std::cin >> new_password;
                auto find_existed_password = std::find(passwords.begin(), passwords.end(), new_password);
                if (find_existed_password != passwords.end()) {
                    std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                std::size_t count_symbol_numbers = 0, count_special_symbols = 0;
                for (auto& digit : new_password) {
                    if (std::isdigit(digit, std::locale(""))) {
                        count_symbol_numbers++;
                    }
                    else if (!std::isalnum(digit, std::locale(""))) {
                        count_special_symbols++;
                    }
                }
                if (new_password.size() < 8) {
                    std::cerr << RED << "Пароль должен быть не менее 8 символов" << RESET << std::endl;
                    accounts();
                }
                else if (count_symbol_numbers == 0 || count_special_symbols == 0) {
                    std::cerr << RED << "Пароль должен иметь хотя бы 1 специальный символ и 4 числа. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                else {
                    passwords[std::distance(find_user_login_from_first, find_user_login)] = new_password;
                    std::cout << GREEN << "Пароль для пользователя '" << loginNames[std::distance(find_user_login_from_first, find_user_login)] << "' успешно изменен" << RESET << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    system("cls");
                    menu(1);
                }
            }
        }
        else if (std::stoi(operation) == 2) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для изменения его права:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl;
                accounts();
            }
            else {
                auto find_user_login_from_first =
                    std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
                std::cout << "Напишите новое право для пользователя:\n";
                std::string new_right = "";
                std::cin >> new_right;
                auto exist_right = std::find(rights.begin(), rights.end(), new_right);
                if (new_right.size() < 5 || exist_right == rights.end()) {
                    std::cerr << RED << "Ошибка ввода права для пользователя. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                else {
                    rights[std::distance(find_user_login_from_first, find_user_login)] = new_right;
                    std::cout << GREEN << "Право для пользователя '" << loginNames[std::distance(find_user_login_from_first, find_user_login)] << "' успешно изменено" << RESET << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    system("cls");
                    menu(1);
                }
            }
        }
    }
    else if (rights[std::distance(find_from_first, find_right)] == "Администратор") {
        for (std::size_t i = 0; i < loginNames.size(); ++i) {
            if (rights[i] != "Супер-администратор") {
                std::cout << "Логин: " << loginNames[i] << " | " << "Пароль: " << passwords[i]
                          << " | " << "Права: " << rights[i] << std::endl;
            }
        }
        std::string operation = "";
        std::cout << "Что хотите изменить:\n";
        std::cout << "1. Пароль\n";
        std::cout << "2. Права\n";
        std::cin >> operation;
        if (std::stoi(operation) == 1) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для смены его пароля:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            auto find_user_login_from_first = std::find(loginNames.begin(),loginNames.end(),loginNames[0]);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка" << RESET << std::endl;
                accounts();
            } else if(rights[std::distance(find_user_login_from_first,find_user_login)] == "Супер-администратор") {
                std::cerr << RED << "Невозможно менять пароль человеку с тем же статусом. Попробуйте еще раз" << RESET << std::endl;
                accounts();
            }
            else {
                auto find_user_login_from_first =
                    std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
                std::cout << "Напишите новый пароль для пользователя:\n";
                std::string new_password = "";
                std::cin >> new_password;
                auto find_existed_password = std::find(passwords.begin(), passwords.end(), new_password);
                if (find_existed_password != passwords.end()) {
                    std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                std::size_t count_symbol_numbers = 0, count_special_symbols = 0;
                for (auto& digit : new_password) {
                    if (std::isdigit(digit, std::locale(""))) {
                        count_symbol_numbers++;
                    }
                    else if (!std::isalnum(digit, std::locale(""))) {
                        count_special_symbols++;
                    }
                }
                if (new_password.size() < 8) {
                    std::cerr << RED << "Пароль должен быть не менее 8 символов" << RESET << std::endl;
                    accounts();
                }
                else if (count_symbol_numbers == 0 || count_special_symbols == 0) {
                    std::cerr << RED << "Пароль должен иметь хотя бы 1 специальный символ и 4 числа. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                else {
                    passwords[std::distance(find_user_login_from_first, find_user_login)] = new_password;
                    std::cout << GREEN << "Пароль для пользователя '" << loginNames[std::distance(find_user_login_from_first, find_user_login)] << "' успешно изменен" << RESET << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    system("cls");
                    menu(1);
                }
            }
        }
        else if (std::stoi(operation) == 2) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для изменения его права:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl;
                accounts();
            }
            else {
                auto find_user_login_from_first =
                    std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
                std::cout << "Напишите новое право для пользователя:\n";
                std::string new_right = "";
                std::cin >> new_right;
                auto exist_right = std::find(rights.begin(), rights.end(), new_right);
                if (new_right.size() < 5 || exist_right == rights.end()) {
                    std::cerr << RED << "Ошибка ввода права для пользователя. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                else {
                    rights[std::distance(find_user_login_from_first, find_user_login)] = new_right;
                    std::cout << GREEN << "Право для пользователя '" << loginNames[std::distance(find_user_login_from_first, find_user_login)] << "' успешно изменено" << RESET << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    system("cls");
                    menu(1);
                }
            }
        }
    }
    else if (rights[std::distance(find_from_first, find_right)] == "Сотрудник") {
        for (std::size_t i = 0; i < loginNames.size(); ++i) {
            if (rights[i] == "Сотрудник") {
                std::cout << "Логин: " << loginNames[i] << " | " << "Пароль: " << passwords[i]
                          << " | " << "Права: " << rights[i] << std::endl;
            }
        }
        std::string operation = "";
        std::cout << "Что хотите изменить:\n";
        std::cout << "1. Пароль\n";
        std::cout << "2. Права\n";
        std::cin >> operation;
        if (std::stoi(operation) == 1) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для смены его пароля:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            auto find_user_login_from_first = std::find(loginNames.begin(),loginNames.end(),loginNames[0]);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка" << RESET << std::endl;
                accounts();
            } else if(rights[std::distance(find_user_login_from_first,find_user_login)] == "Супер-администратор") {
                std::cerr << RED << "Невозможно менять пароль человеку с тем же статусом. Попробуйте еще раз" << RESET << std::endl;
                accounts();
            }
            else {
                auto find_user_login_from_first =
                    std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
                std::cout << "Напишите новый пароль для пользователя:\n";
                std::string new_password = "";
                std::cin >> new_password;
                auto find_existed_password = std::find(passwords.begin(), passwords.end(), new_password);
                if (find_existed_password != passwords.end()) {
                    std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                std::size_t count_symbol_numbers = 0, count_special_symbols = 0;
                for (auto& digit : new_password) {
                    if (std::isdigit(digit, std::locale(""))) {
                        count_symbol_numbers++;
                    }
                    else if (!std::isalnum(digit, std::locale(""))) {
                        count_special_symbols++;
                    }
                }
                if (new_password.size() < 8) {
                    std::cerr << RED << "Пароль должен быть не менее 8 символов" << RESET << std::endl;
                    accounts();
                }
                else if (count_symbol_numbers == 0 || count_special_symbols == 0) {
                    std::cerr << RED << "Пароль должен иметь хотя бы 1 специальный символ и 4 числа. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                else {
                    passwords[std::distance(find_user_login_from_first, find_user_login)] = new_password;
                    std::cout << GREEN << "Пароль для пользователя '" << loginNames[std::distance(find_user_login_from_first, find_user_login)] << "' успешно изменен" << RESET << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    system("cls");
                    menu(1);
                }
            }
        }
        else if (std::stoi(operation) == 2) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для изменения его права:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl;
                accounts();
            }
            else {
                auto find_user_login_from_first =
                    std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
                std::cout << "Напишите новое право для пользователя:\n";
                std::string new_right = "";
                std::cin >> new_right;
                auto exist_right = std::find(rights.begin(), rights.end(), new_right);
                if (new_right.size() < 5 || exist_right == rights.end()) {
                    std::cerr << RED << "Ошибка ввода права для пользователя. Попробуйте еще раз" << RESET << std::endl;
                    accounts();
                }
                else {
                    rights[std::distance(find_user_login_from_first, find_user_login)] = new_right;
                    std::cout << GREEN << "Право для пользователя '" << loginNames[std::distance(find_user_login_from_first, find_user_login)] << "' успешно изменено" << RESET << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    system("cls");
                    menu(1);
                }
            }
        }
    }
}

void premium(std::string login, std::string right) {
    std::string up = "";
    if (right == "Сотрудник") {
        std::cout << GREEN << login << " со статусом '" << right << "' получает вознаграждение в виде:\n" << RESET;
        std::cout << YELLOW << "1. Возможность подняться до статуса Администратора\n" << RESET;
        std::cout << YELLOW << "2. Возможность работать по графику 2/2 вместо 5/2\n" << RESET;
        std::cout << YELLOW << "-----------------------------------------------------\n" << RESET;
        std::cout << YELLOW << "Хотите подняться до уровня Администратора - напишите 1\n" << RESET;
        std::cout << YELLOW << "Хотите остаться на том же уровне, но с другим графиком работы - напишите другую цифру\n" << RESET;
        std::cin >> up;
        if (std::stoi(up) == 1) {
            auto find_login = std::find(loginNames.begin(), loginNames.end(), login);
            auto find = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
            rights[std::distance(find, find_login)] = "Администратор";
            std::cout << GREEN << "Сотрудник '" << login << "' был успешно поднят до статуса '" << rights[std::distance(find, find_login)] << "'.\nПоздравляем!" << RESET;
            storage();
        }
        else {
            std::cout << "Возвращение в работу" << std::endl;
            storage();
        }
    }
    else if (right == "Администратор") {
        std::cout << GREEN << login << " со статусом '" << right << "' получает вознаграждение в виде:\n" << RESET;
        std::cout << YELLOW << "1. Возможность подняться до Супер-администратора\n" << RESET;
        std::cout << YELLOW << "2. Возможность работать по графику 2/1 вместо 5/1\n" << RESET;
        std::cout << YELLOW << "-----------------------------------------------------\n" << RESET;
        std::cout << YELLOW << "Хотите подняться до уровня Супер-администратора - напишите 1\n" << RESET;
        std::cout << YELLOW << "Хотите остаться на том же уровне, но с другим графиком работы - напишите другую цифру\n" << RESET;
        std::cin >> up;
        if (std::stoi(up) == 1) {
            auto find_login = std::find(loginNames.begin(), loginNames.end(), login);
            auto find = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
            rights[std::distance(find, find_login)] = "Супер-администратор";
            std::cout << GREEN << "Сотрудник '" << login << "' был успешно поднят до статуса '" << rights[std::distance(find, find_login)] << "'.\nПоздравляем!" << RESET;
            storage();
        }
        else {
            std::cout << "Возвращение в работу" << std::endl;
            storage();
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
            storage();
        }
        else {
            std::cout << "Возвращение в работу" << std::endl;
            storage();
        }
    }
}

void sales() {
    if (client == "Покупатель") {
        std::cerr << RED << "У вас недостаточно прав на просмотр отчета продаж" << RESET << std::endl;
        menu(1);
    }
    std::string name_employee[1];
    if (is_employee == 1) {
        std::string get_login = "";
        std::cout << "Введите свой логин:\n";
        std::cin >> get_login;
        auto find_login = std::find(loginNames.begin(), loginNames.end(), get_login);
        auto find_from_first_login = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
        if (find_login == loginNames.end()) {
            std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl;
            sales();
        }
        name_employee[0] = loginNames[std::distance(find_from_first_login, find_login)];
        std::cout << YELLOW << std::right << std::setw(62) << "Итоги продаж за день\n" << RESET;
        double sum_saled_product = 0.0;
        std::cout << "Наименование товара" << "\t" << "Количество" << "\t" << "Сумма" << "\n";
        for (std::size_t i = 0; i < saled_products.size(); ++i) {
            std::cout << saled_products[i] << "\t\t" << result_count_products[i] << "\t\t" << result_saled_products[i] << "\n";
            sum_saled_product += result_saled_products[i];
        }
        std::cout << YELLOW << "Итоговая сумма с проданных товаров: " << sum_saled_product << " рублей" << RESET << std::endl;
    }
    else {
        std::cout << YELLOW << std::right << std::setw(62) << "Итоги продаж за день\n" << RESET;
        double sum_saled_product = 0.0;
        std::cout << "Наименование товара" << "\t" << "Количество" << "\t" << "Сумма" << "\n";
        for (std::size_t i = 0; i < saled_products.size(); ++i) {
            std::cout << saled_products[i] << "\t\t" << result_count_products[i] << "\t\t" << result_saled_products[i] << "\n";
            sum_saled_product += result_saled_products[i];
        }
        if (sum_saled_product < 500.0) {
            std::string give_fine = "";
            std::cout << YELLOW << "Сотрудник '" << name_employee[0] << "' продал товары на сумму меньше 500 рублей. Напишите 1 чтобы им выдать штраф, другую цифру если пощадить: \n" << RESET;
            std::cin >> give_fine;
            if (std::stoi(give_fine) == 1) {
                existed_fine = 1;
                count_sales = 1;
                fines_for_employees();
                auto find_employee = std::find(loginNames.begin(), loginNames.end(), name_employee[0]);
                auto find = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
                rights[std::distance(find, find_employee)] = "Сотрудник";
                fines[std::distance(find, find_employee)] = 1;
                std::cout << GREEN << "Штраф сотруднику '" << name_employee[0] << "' был успешно выдан" << RESET << std::endl;
            }
        }
        else {
            std::cout << GREEN << "Товаров было продано на сумму больше или равной 500 рублям" << RESET << std::endl;
            menu(1);
        }
    }
}

void discounts(std::size_t id, double product_price) {
    std::string discount = "";
    id--;
    std::cout << LIGHT_BLUE << "Введите скидку на товар " << productName[id] << RESET << ":\n";
    std::cin >> discount;
    if (discount.at(0) == '-') {
        std::cerr << RED << "Скидка не может быть отрицательной. Попробуйте еще раз" << RESET << std::endl;
        discounts(id, product_price);
    }
    else {
        auto erase_procent = std::find(discount.begin(), discount.end(), '%');
        discount.erase(erase_procent);
        double new_price = (product_price * std::stod(discount)) / 100.0;
        price[id] = new_price;
        std::cout << GREEN << "Скидка на товар '" << productName[id] << " была успешно введена" << RESET << std::endl;
        menu(1);
    }
}

void payment(std::string product, double product_price, std::size_t count) {
    saled_products.emplace_back(product);
    if (is_mom_friend_son == 1) {
        result_saled_products.emplace_back(0.0);
    }
    else {
        result_saled_products.emplace_back(product_price * (double)count);
    }
    result_count_products.emplace_back(count);
    std::string select_payment_operation = "", number_card = "", CVC = "", espiration_date = "", count_cash = "", get_check = "";
    std::size_t get_cash = 0;
    std::string numbers_from_espiration_date[2];
    std::size_t full_numbers = 0;
    double sum_for_paying = product_price * (double)count;
    std::string payments[]{ "","Электронная карта (Мир Visa Mastercard)","Наличные" };
    for (std::size_t payment_way = 1; payment_way < 3; ++payment_way) {
        std::cout << payment_way << ") " << payments[payment_way] << std::endl;
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
                get_cash = std::stod(count_cash);
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
                    std::cout << std::right << std::setw(62) << "Кассовый чек\n";
                    std::cout << "Покупка №1488 Смена 666\n";
                    std::cout << "Товар: " << product << "\n";
                    std::cout << "Итог: " << get_cash << " рублей\n";
                    std::cout << "Сдача: " << get_cash - sum_for_paying << " рублей\n";
                    std::cout << "-------------------------------------------\n";
                    std::cout << "666666 г. Екатеринбург ул. Фурманова 57\n";
                    auto date = std::chrono::system_clock::now();
                    count_sales++; earned_money += get_cash - sum_for_paying;
                    menu(1);
                }
                else {
                    std::cout << GREEN << "Товар успешно приобретен" << RESET << std::endl;
                    count_sales++;
                    menu(1);
                }
            }
            else {
                std::cerr << RED << "Недостаточно средств на счету" << RESET << std::endl;
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
                std::cout << YELLOW << std::right << std::setw(62) << "Кассовый чек\n" << RESET;
                std::cout << "Покупка №1488 Смена 666\n";
                std::cout << "Товар: " << product << "\n";
                std::cout << "Итог: " << get_cash << " рублей\n";
                std::cout << "Сдача: " << get_cash - sum_for_paying << " рублей\n";
                std::cout << "-------------------------------------------\n";
                std::cout << "666666 г. Екатеринбург ул. Фурманова 57\n";
                auto date = std::chrono::system_clock::now();
                count_sales++; earned_money += get_cash - sum_for_paying;
                menu(1);
            }
            else {
                std::cout << GREEN << "Товар успешно приобретен" << RESET << std::endl;
                count_sales++;
                menu(1);
            }
        }
        else {
            std::cerr << RED << "Недостаточно средств на счету" << RESET << std::endl;
            menu(1);
        }
    }
}

void momFriendSon() {
    is_mom_friend_son = 1;
    std::cout << GREEN << "Режим '" << "Сын маминой подруги" << "' активирован" << RESET << std::endl;
    menu(1);
}

void menu(short attempt) {
    if (attempt >= 10) {
        std::cout << YELLOW << "Было использовано более 10 попыток при выборе опции. Попробуйте позже через 5 минут\n" << RESET;
        std::this_thread::sleep_for(std::chrono::seconds(300));
        attempt = 1;
    }
    std::string option = "";
    std::cout << std::right << std::setw(62) << "Возрождение май\n";
    std::string menu_types[]{ "","Товары","Учетные записи","Продажи","Склад","Сын маминой подруги","Итоги продаж", "Выйти со своего аккаунта" };
    for (std::size_t i = 1; i < 8; ++i) {
        std::cout << i << ") " << menu_types[i] << "\n";
    }
    std::cout << LIGHT_BLUE << "Выберите опцию:\n" << RESET;
    std::cin >> option;
    switch (std::stoi(option)) {
    case 1:
        start(1);
        break;
    case 2:
        accounts();
        break;
    case 3:
        sales();
        break;
    case 4:
        storage();
        break;
    case 5:
        momFriendSon();
        break;
    case 6:
        sales();
        break;
    case 7:
        if (client == "Покупатель") {
            client.clear();
        }
        login(1);
        break;
    default:
        std::cerr << RED << "Такой опции не существует. Повторите попытку:\n" << RESET;
        attempt++;
        menu(attempt);
        break;
    }
}

void start(short attempt) {
    if (attempt >= 10) {
        std::cout << YELLOW << "Превышено количество попыток для выбора товара. Попробуйте позже" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
    for (std::size_t i = 0; i < 10; ++i) {
        std::cout << id[i] << "\t" << productName[i] << "\t" << price[i] << "\t" << count[i] << std::endl;
    }
    std::string select_id_product = "", count_product = "";
    std::cout << "Напишите id продукта для покупки:\n";
    std::cin >> select_id_product;
    if (!std::isdigit(select_id_product.at(0), std::locale(""))) {
        std::cerr << RED << "Ошибка ввода айди товара. Попробуйте еще раз" << RESET << std::endl;
        start(1);
    }
    std::cout << "Напишите количество продукта:\n";
    std::cin >> count_product;
    if (!std::isdigit(count_product.at(0), std::locale(""))) {
        std::cerr << RED << "Ошибка ввода количества товара. Попробуйте еще раз" << RESET << std::endl;
        start(1);
    }
    auto find_id_product = std::find(id.begin(), id.end(), std::stoi(select_id_product));
    auto find_from_first = std::find(id.begin(), id.end(), id.at(0));
    if (find_id_product == id.end()) {
        std::cerr << RED << "Такого товара с таким айди. Попробуйте еще раз" << RESET << std::endl;
        attempt++;
        start(attempt);
    }
    if (std::stoi(count_product) > count[std::distance(find_from_first, find_id_product)] ||
        std::stoi(count_product) < 0) {
        std::cerr << RED << "Количество товара должно быть меньше указанного максимума в списке товаров и больше 0\n" << RESET;
        std::cerr << RED << "Попробуйте еще раз" << RESET << std::endl;
        attempt++;
        start(attempt);
    }
    else {
        std::string return_product = "";
        std::cout << "Хотите ли Вы отказаться от товара.\n";
        std::cout << "Если да, то напишите 1. Если нет, то другую цифру:\n";
        std::cin >> return_product;
        if (std::stoi(return_product) == 1) {
            select_id_product.clear();
            count_product.clear();
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

void new_storage() {
    std::string create_product_name = "", set_size = "", create_count = "", create_price = "", create_id = ""; std::size_t create = 0;
    std::cout << LIGHT_BLUE << "Введите размер для нового склада: \n" << RESET;
    std::cin >> set_size;
    if (std::stoi(set_size) <= 0) {
        std::cerr << RED << "Размер склада не может быть нулевым или отрицательным. Попробуйте еще раз" << RESET << std::endl;
        new_storage();
    }
    std::size_t get_size = std::stoi(set_size);
    while (create < get_size) {
        std::cout << "Напишите id для нового товара:\n";
        std::cin >> create_id;
        std::cout << "Напишите название для нового товара:\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, create_product_name);
        std::cout << "Напишите количество для нового товара:\n";
        std::cin >> create_count;
        std::cout << "Напишите цену для нового товара:\n";
        std::cin >> create_price;
        if (std::stoi(create_id) <= 0 || std::stoi(create_count) <= 0 || std::stod(create_price) <= 0.0) {
            std::cerr << RED << "Введены некорректные данные для нового товара. Попробуйте еще раз" << RESET << std::endl;
            new_storage();
        }
        else {
            set_id.emplace_back(std::stoi(create_id));
            set_product.emplace_back(create_product_name);
            set_count.emplace_back(std::stoi(create_count));
            set_price.emplace_back(std::stod(create_price));
            create++;
        }
    }
    std::cout << std::right << std::setw(62) << "Новый склад\n";
    std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
    for (std::size_t i = 0; i < get_size; ++i) {
        std::cout << set_id[i] << "\t" << set_product[i] << "\t" << set_price[i] << "\t" << set_count[i] << std::endl;
    }
    menu(1);
}

void storage() {
    std::string get_login = "";
    std::cout << LIGHT_BLUE << "Напишите свой логин: " << RESET << std::endl;
    std::cin >> get_login;
    auto find_login = std::find(loginNames.begin(), loginNames.end(), get_login);
    auto find_from_first_login = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
    if (find_login == loginNames.end()) {
        std::cerr << RED << "Ошибка ввода" << RESET << std::endl;
        menu(1);
    }
    if (fines[std::distance(find_from_first_login, find_login)] == 1) {
        std::cout << YELLOW << "Уважаемый '" << get_login << "' вы продали очень мало товаров на сумму менее 500 рублей\n" << RESET;
        std::cout << YELLOW << "Поэтому к сожалению вас пришлось понизить до статуса 'Сотрудник'. Вам прилетел штраф" << RESET << std::endl;
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
        std::cout << "1. Работать с готовым складом\n";
        std::cout << "2. Создать новый склад\n";
        std::cout << "3. Выйти в меню" << std::endl;
        std::cin >> select_storage;
        if (std::stoi(select_storage) == 1) {
            std::cout << LIGHT_BLUE << "Выберите операцию по работе с товарами: \n" << RESET;
        }
        else if (std::stoi(select_storage) == 2) {
            new_storage();
        }
        else if (std::stoi(select_storage) == 3) {
            menu(1);
        }
        else {
            std::cerr << RED << "Неверный тип склада. Попробуйте еще раз" << RESET << std::endl;
            storage();
        }
        std::string _id = "", _price = "", operation = "";
        std::cout << "1. Изменение цены\n";
        std::cout << "2. Изменение названия товара\n";
        std::cout << "3. Списание товара\n";
        std::cout << "4. Добавить новый товар\n";
        std::cout << "5. Изменение id товара\n";
        std::cout << "6. Выход со склада\n";
        std::cin >> operation;
        if (std::stoi(operation) == 1) {
            std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << id[i] << "\t" << productName[i] << "\t" << price[i] << "\t" << count[i] << std::endl;
            }
            std::cout << "Напишите айди товара для изменения цены: \n";
            std::cin >> _id;
            if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
                std::cerr << RED << "Ошибка. Товара с таким id нет. Повторите еще раз" << RESET << std::endl;
                storage();
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
                std::cerr << RED << "Ошибка. Товара с таким id нет. Повторите еще раз" << RESET << std::endl;
                storage();
            }
            else if (!std::isdigit(_id.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка написания айди товара. Попробуйте еще раз" << RESET << std::endl;
                storage();
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
            std::cout << "1. Уменьшить количество товара\n";
            std::cout << "2. Сделать товар не доступным" << std::endl;
            std::cin >> select_type;
            if (std::stoi(select_type) < 1 || std::stoi(select_type) > 2) {
                std::cerr << RED << "Выберите правильный тип списания товара" << RESET << std::endl;
                storage();
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
                    std::cerr << RED << "Товар с таким айди нет. Попробуйте еще раз" << RESET << std::endl;
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
                    std::cerr << RED << "Товар с таким id нет. Попробуйте еще раз" << RESET << std::endl;
                    storage();
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
                storage();
            }
            std::string newNameProduct = "", newCount = "", newPrice = "";
            std::cout << "Напишите новое название товара:\n";
            std::cin >> newNameProduct;
            if (!std::isalpha(newNameProduct.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка наименования товара. Попробуйте еще раз" << RESET << std::endl;
                storage();
            }
            std::cout << "Напишите количество нового товара:\n";
            std::cin >> newCount;
            if (std::isalpha(newCount.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания количества товара. Попробуйте еще раз" << RESET << std::endl;
                storage();
            }
            std::cout << "Напишите цену нового товара:\n";
            std::cin >> newPrice;
            if (std::isalpha(newPrice.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания цены товара. Попробуйте еще раз" << RESET << std::endl;
                storage();
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
            std::cout << "Напишите id для товара:\n";
            std::cin >> _id;
            auto find_id = std::find(id.begin(), id.end(), std::stoi(_id));
            if (find_id == id.end()) {
                std::cerr << RED << "Товар с таким айди не найден. Попробуйте еще раз" << RESET << std::endl;
                storage();
            }
            else {
                std::string new_id = "";
                std::cout << "Напишите новое id товара:\n";
                std::cin >> new_id;
                auto find_from_first_id = std::find(id.begin(), id.end(), id.at(0));
                id[std::distance(find_from_first_id, find_id)] = std::stoi(new_id);
                std::cout << GREEN << "Айди " << _id << " для товара '" << productName[std::distance(find_from_first_id, find_id)] << "' был успешно изменен на " << new_id << RESET << std::endl;
                count_changed_storage_times++;
                menu(1);
            }
        }
        else if (std::stoi(operation) == 6) {
            std::cout << "Выход со склада" << std::endl;
            menu(1);
        }
        else {
            std::cerr << RED << "Такой операции не существует. Повторите еще раз" << RESET << std::endl;
            storage();
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
        std::cout << "1. Отчёт продаж\n";
        std::cout << "2. Изменение товара\n";
        std::cout << "3. Выход со склада" << std::endl;
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
                storage();
            }
            std::cout << "Введите новое название для товара:\n";
            std::cin >> new_name;
            if (std::isdigit(new_name.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка наименования товара. Повторите попытку" << RESET << std::endl;
                storage();
            }
            std::cout << "Напишите новое айди товара:\n";
            std::cin >> new_id;
            if (!std::isdigit(new_id.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания нового айди для товара. Повторите попытку" << RESET << std::endl;
                storage();
            }
            std::cout << "Напишите количество нового товара\n";
            std::cin >> new_count;
            if (!std::isdigit(new_count.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания количества нового товара. Повторите попытку" << RESET << std::endl;
                storage();
            }
            std::cout << "Введите новую цену для товара:\n";
            std::cin >> new_price;
            if (!std::isdigit(new_price.at(0), std::locale(""))) {
                std::cerr << RED << "Ошибка указания цены для нового товара" << RESET << std::endl;
                storage();
            }
            productName[std::distance(find_id_from_first, find_id)] = new_name;
            id[std::distance(find_id_from_first, find_id)] = std::stoi(new_id);
            count[std::distance(find_id_from_first, find_id)] = std::stoi(new_count);
            price[std::distance(find_id_from_first, find_id)] = std::stod(new_price);
            std::cout << GREEN << "Товар был успешно изменен" << RESET << std::endl;
            count_changed_storage_times++;
            storage();
        }
        else if (std::stoi(option) == 3) {
            menu(1);
        }
        else {
            std::cerr << RED << "Такой опции нет. Попробуйте еще раз" << RESET << std::endl;
            storage();
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
        std::cout << "1. Сделать скидку на товар\n";
        std::cout << "2. Возврат товара\n";
        std::string option = "";
        std::cin >> option;
        if (std::stoi(option) < 1 || std::stoi(option) > 2) {
            std::cerr << RED << "Такой опции нет. Попробуйте еще раз" << RESET << std::endl;
            storage();
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
                std::cerr << RED << "Товар с таким айди нет. Попробуйте еще раз" << RESET << std::endl;
                storage();
            }
            else {
                auto find_id_from_first = std::find(id.begin(), id.end(), id.at(0));
                discounts(id[std::distance(find_id_from_first, find_id)],
                          price[std::distance(find_id_from_first, find_id)]);
            }
        }
        else {
            std::string id_product_for_returning = "";
            std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << id[i] << "\t" << productName[i] << "\t\t" << price[i] << "\t" << count[i] << std::endl;
            }
            std::cout << "Напишите товар, который вы хотите вернуть обратно на склад:\n";
            std::cin >> id_product_for_returning;
            auto find = std::find(id.begin(), id.end(), std::stoi(id_product_for_returning));
            if (find == id.end()) {
                std::cerr << RED << "Продукта с таким айди нет. Попробуйте еще раз" << RESET << std::endl;
                storage();
            }
            std::cout << GREEN << "Товар успешно возвращен на склад" << RESET << std::endl;
        }
    }
    else {
        std::cerr << RED << "У вас недостаточно прав на работу на складе" << RESET << std::endl;
        menu(1);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    login(1);
    return 0;
}
