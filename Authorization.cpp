#include "Authorization.h"
#include "GlobalObjectsAndVariables.h"
#include "EnterPoint.h"

void login(short attempt) {
    if (attempt >= 10) {
        std::cout << YELLOW << "Было использовано около 10 попыток захода в магазин. Попробуйте позже" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::string type_enter = "";
    std::cout << LIGHT_BLUE << "Выберите способ захода в магазин" << RESET << std::endl;
    std::string options[]{"","Регистрация","Авторизация","Войти как покупатель","Выход из магазина"};
    for (std::size_t select = 1; select < 5; ++select) {
        std::cout << "<" << select << "> " << options[select] << "\n";
    }
    std::cin >> type_enter;
    if (std::stoi(type_enter) == 1) {
        registry(1);
    }
    else if (std::stoi(type_enter) == 2) {
        std::string loginName = "", password = "";
        std::cout << LIGHT_BLUE << std::right << std::setw(62) << "Авторизация\n" << RESET;
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
void registry(short attempt) {
    if (attempt >= 10) {
        std::cout << YELLOW << "Было использовано около 10 попыток захода в магазин. Попробуйте позже" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::string select_user = "", name = "", password = "", result = "";
    std::string type_user[]{ "","Супер-администратор","Администратор","Сотрудник" };
    std::cout << LIGHT_BLUE << std::right << std::setw(62) << "Регистрация\n" << RESET;
    for (std::size_t show_all_types = 1; show_all_types < 4; ++show_all_types) {
        std::cout << "<" << show_all_types << "> " << type_user[show_all_types] << std::endl;
    }
    std::cout << "Выберите тип пользователя, от лица которого вы будете работать с магазином:\n";
    std::cin >> select_user;
    if (std::stoi(select_user) < 1 || std::stoi(select_user) > 3) {
        std::cerr << RED << "Такого типа пользователя не существует." << RESET << std::endl;
        menu(1);
    }
    else {
        std::size_t count_symbol_numbers = 0, find_special_symbols = 0;
        std::cout << "Напишите имя пользователя для типа " << type_user[std::stoi(select_user)] << "\n";
        std::cin >> name;
        auto find_dublicate_name = std::find(loginNames.begin(), loginNames.end(), name);
        if (find_dublicate_name != loginNames.end()) {
            std::cerr << RED << "Ошибка ввода. Попробуйте еще раз" << RESET << std::endl; \
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
        if (name.size() < 8 && password.size() < 8) {
            std::cerr << RED << "Логин или пароль меньше указанных параметров. Попробуйте еще раз." << RESET << std::endl;
            attempt++;
            registry(attempt);
        }
        if (count_symbol_numbers == 0 && find_special_symbols == 0) {
            std::cerr << RED << "Пароль должен содержать хотя бы 1 специальный символ и 4 числа" << RESET << std::endl;
            attempt++;
            registry(attempt);
        }
        else {
            loginNames.emplace_back(name);
            passwords.emplace_back(password);
            result = type_user[std::stoi(select_user)];
            rights.emplace_back(result);
            std::cout << GREEN << "Регистрация под типом пользователя '" << result <<
                "' прошла успешно" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("cls");
            login(1);
        }
    }
}
void accounts(short attempt) {
    if (attempt >= 10) {
        std::cerr << YELLOW << "Было использовано более 10 попыток внести изменения в аккаунт. Попробуйте позже" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
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
    auto find_password = std::find(passwords.begin(), passwords.end(), get_password);
    if (find_password == passwords.end()) {
        std::cerr << RED << "Ошибка ввода" << RESET << std::endl;
        attempt++;
        accounts(attempt);
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
        std::cout << "<1> Пароль\n";
        std::cout << "<2> Права\n";
        std::cout << "<3> Выйти в меню\n";
        std::cin >> operation;
        if (std::stoi(operation) == 1) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для смены его пароля:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            auto find_user_login_from_first = std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка" << RESET << std::endl;
                attempt++;
                accounts(attempt);
            }
            else if (rights[std::distance(find_user_login_from_first, find_user_login)] == "Супер-администратор") {
                std::cerr << RED << "Невозможно менять пароль человеку с тем же статусом. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
                }
                else if (count_symbol_numbers == 0 || count_special_symbols == 0) {
                    std::cerr << RED << "Пароль должен иметь хотя бы 1 специальный символ и 4 числа. Попробуйте еще раз" << RESET << std::endl;
                    attempt++;
                    accounts(attempt);
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
                attempt++;
                accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
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
        else if (std::stoi(operation) == 3) {
            menu(1);
        }
        else {
            std::cerr << "Такой опции нет. Попробуйте еще раз" << std::endl;
            attempt++;
            accounts(attempt);
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
        std::cout << "<1> Пароль\n";
        std::cout << "<2> Права\n";
        std::cout << "<3> Выйти в меню\n";
        std::cin >> operation;
        if (std::stoi(operation) == 1) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для смены его пароля:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            auto find_user_login_from_first = std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка" << RESET << std::endl;
                attempt++;
                accounts(attempt);
            }
            else if (rights[std::distance(find_user_login_from_first, find_user_login)] == "Супер-администратор") {
                std::cerr << RED << "Невозможно менять пароль человеку с тем же статусом. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
                }
                else if (count_symbol_numbers == 0 || count_special_symbols == 0) {
                    std::cerr << RED << "Пароль должен иметь хотя бы 1 специальный символ и 4 числа. Попробуйте еще раз" << RESET << std::endl;
                    attempt++;
                    accounts(attempt);
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
                attempt++;
                accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
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
        else if (std::stoi(operation) == 3) {
            menu(1);
        }
        else {
            std::cerr << RED << "Такой опции нет. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            accounts(attempt);
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
        std::cout << "<1> Пароль\n";
        std::cout << "<2> Права\n";
        std::cout << "<3> Выйти в меню\n";
        std::cin >> operation;
        if (std::stoi(operation) == 1) {
            std::string user_login = "";
            for (std::size_t i = 0; i < loginNames.size(); ++i) {
                std::cout << "> " << loginNames[i] << "\n";
            }
            std::cout << "Выберите пользователя для смены его пароля:\n";
            std::cin >> user_login;
            auto find_user_login = std::find(loginNames.begin(), loginNames.end(), user_login);
            auto find_user_login_from_first = std::find(loginNames.begin(), loginNames.end(), loginNames[0]);
            if (find_user_login == loginNames.end()) {
                std::cerr << RED << "Ошибка" << RESET << std::endl;
                attempt++;
                accounts(attempt);
            }
            else if (rights[std::distance(find_user_login_from_first, find_user_login)] == "Супер-администратор") {
                std::cerr << RED << "Невозможно менять пароль человеку с тем же статусом. Попробуйте еще раз" << RESET << std::endl;
                attempt++;
                accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
                }
                else if (count_symbol_numbers == 0 || count_special_symbols == 0) {
                    std::cerr << RED << "Пароль должен иметь хотя бы 1 специальный символ и 4 числа. Попробуйте еще раз" << RESET << std::endl;
                    attempt++;
                    accounts(attempt);
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
                attempt++;
                accounts(attempt);
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
                    attempt++;
                    accounts(attempt);
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
        else if (std::stoi(operation) == 3) {
            menu(1);
        }
        else {
            std::cerr << RED << "Такой опции нет. Попробуйте еще раз" << RESET << std::endl;
            attempt++;
            accounts(attempt);
        }
    }
}
