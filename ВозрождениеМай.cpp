#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <thread>
#include <sstream>
#include <string>

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
void login(short attempt);
void storage();
void accounts();
void premium();
void sales();
void discounts();
void payment();
void momFriendSon();
void menu(short attempt);
void registry();

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

void registry(short attempt) {
    if(attempt >= 10) {
        std::cout << "Было использовано около 10 попыток захода в магазин. Попробуйте позже" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::string select_user = "", name = "", password = "", result = "";
    std::string type_user[]{"","Супер-администратор","Администратор","Сотрудник"};
    std::cout << std::right << std::setw(62) << "Регистрация\n";
    for(std::size_t show_all_types = 1; show_all_types < 4; ++show_all_types) {
        std::cout << show_all_types << ") " << type_user[show_all_types] << std::endl;
    }
    std::cout << "Выберите тип пользователя, от лица которого вы будете работать с магазином\n";
    std::cin >> select_user;
    if(std::stoi(select_user) < 1 || std::stoi(select_user) > 3) {
        std::cerr << "Такого типа пользователя не существует." << std::endl;
        menu(1);
    } else {
        std::cout << "Напишите имя пользователя для типа '" << type_user[std::stoi(select_user)] << "'\n";
        std::cin >> name;
        std::cout << "Напишите пароль для пользователя типа'" << type_user[std::stoi(select_user)] << "'\n";
        std::cin >> password;
        if(name.size() < 5 && password.size() < 5) {
            std::cerr << "Логин или пароль меньше указанных параметров.\nПопробуйте еще раз.";
            attempt++;
            registry(1);
        }
        loginNames.emplace_back(name);
        passwords.emplace_back(password);
        result = type_user[std::stoi(select_user)];
        rights.emplace_back(result);
        std::cout << "Регистрация под типом пользователя '" << type_user[std::stoi(select_user)] <<
            " прошла успешно" << std::endl;
        login(1);
    }
}

void login(short attempt) {
    if(attempt >= 10) {
        std::cout << "Было использовано около 10 попыток захода в магазин. Попробуйте позже" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::string type_enter = "";
    std::cout << "Выберите способ захода в магазин\n";
    std::cout << "1. Регистрация\n";
    std::cout << "2. Авторизация\n";
    std::cout << "3. Войти как покупатель\n";
    std::cout << "3. Выход из магазина\n";
    std::cin >> type_enter;
    if(std::stoi(type_enter) == 1) {
        registry(1);
    } else if(std::stoi(type_enter) == 2) {
        std::string loginName = "", password = "";
        std::cout << std::right << std::setw(62) << "Авторизация\n";
        std::cout << "Введите своё имя пользователя:\n";
        std::cin >> loginName;
        std::cout << "Введите свой пароль:\n";
        std::cin >> password;
        if (loginName.size() < 5 || password.size() < 5) {
            std::cerr << "Логин или пароль меньше указанных параметров.\n" << "Попробуйте еще раз" << std::endl;
            attempt++;
            login(attempt);
        }
        auto from_first_name_user = std::find(loginNames.begin(), loginNames.end(), loginNames.at(0));
        auto find_loginName = std::find(loginNames.begin(), loginNames.end(), loginName);
        auto find_password = std::find(passwords.begin(),passwords.end(),password);
        if(find_loginName != loginNames.end() || find_password != passwords.end()) {
            std::cout << "Пользователь " << loginNames[std::distance(from_first_name_user, find_loginName)]
                      << " успешно вошел в систему" << std::endl;
            std::cout << "Ваш статус: " << rights[std::distance(from_first_name_user, find_loginName)] << "\n";
            menu(1);
        } else {
            std::cout << "Ошибка авторизации в магазине. Повторите попытку" << std::endl;
            attempt++;
            login(attempt);
        }
    } else if(std::stoi(type_enter) == 3) {
        menu(1);
    }else if(std::stoi(type_enter) == 4) {
        std::cout << "Завершение программы" << std::endl;
        system("cls");
        exit(0);
    } else {
        std::cerr << "Такого способа не существует. Попробуйте еще раз" << std::endl;
        attempt++;
        login(attempt);
    }
}

void accounts() {
    std::string get_login = "";
    std::cout << "Напишите свой логин: " << std::endl;
    std::cin >> get_login;
    auto find_login = std::find(loginNames.begin(),loginNames.end(),get_login);
    if(find_login == loginNames.end()) {
        std::cerr << "Такого пользователя с таким логином не существует" << std::endl;
        menu(1);
    }
    auto find_right = std::find(loginNames.begin(),loginNames.end(),get_login);
    auto find_from_first = std::find(loginNames.begin(),loginNames.end(),loginNames.at(0));
    if(rights[std::distance(find_from_first,find_right)] == "Супер-администратор") {
        for(std::size_t i = 0; i < loginNames.size(); ++i) {
            std::cout << "Логин: " << loginNames[i] << " | " << "Пароль: " << passwords[i]
                      << " | " << "Права: " << rights[i] << std::endl;
        }
    } else if(rights[std::distance(find_from_first,find_right)] == "Администратор") {
        for(std::size_t i = 0; i < loginNames.size(); ++i) {
            if(rights[i] != "Супер-администратор") {
                std::cout << "Логин: " << loginNames[i] << " | " << "Пароль: " << passwords[i]
                          << " | " << "Права: " << rights[i] << std::endl;
            }
        }
    } else if(rights[std::distance(find_from_first,find_right)] == "Сотрудник") {
        for(std::size_t i = 0; i < loginNames.size(); ++i) {
            if(rights[i] == "Сотрудник") {
                std::cout << "Логин: " << loginNames[i] << " | " << "Пароль: " << passwords[i]
                          << " | " << "Права: " << rights[i] << std::endl;
            }
        }
    }
}

void premium() {}

void sales() {}

void discounts() {}

void payment() {
    std::string select_payment_operation = "", number_card = "", CVC = "", espiration_date = "",
        count_cash = "";
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
            std::cerr << "Номер карты должен быть 16-значным. Попробуйте еще раз" << std::endl;
            payment();
        } else if(CVC.size() < 3 || !std::isdigit(CVC.at(0),std::locale(""))) {
            std::cerr << "Код CVC для карты должен быть трехзначным. Попробуйте еще раз" << std::endl;
            payment();
        } else if (
            std::stoi(numbers_from_espiration_date[0]) < 1 || std::stoi(numbers_from_espiration_date[0]) > 12 &&
                                                                  std::stoi(numbers_from_espiration_date[1]) < 25) {
            std::cerr << "Неверное указание срока годности карты. Попробуйте еще раз" << std::endl;
            payment();
        }
        else {

        }
    } else if(std::stoi(select_payment_operation) == 2) {
        std::cout << "Введите сумму своих денежных средств на счету: \n";
        std::cin >> count_cash;
    }
}

void momFriendSon() {}

void menu(short attempt) {
    if (attempt >= 10) {
        std::cerr << "Было использовано более 10 попыток при выборе опции. Попробуйте позже через 5 минут\n";
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    std::string option = "";
    std::cout << std::right << std::setw(62) << "Возрождение май\n";
    std::string menu_types[]{ "","Товары","Учетные записи","Премии с продаж","Продажи","Скидки","Способы оплаты","Склад","Сын маминой подруги", "Выйти со своего аккаунта" };
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
    case 9:
        login(1);
        break;
    default:
        std::cerr << "Такой опции не существует. Повторите попытку:\n";
        attempt++;
        menu(attempt);
        break;
    }
}

void start() {
    std::cout << "Айди" << "\t" << "Наименование товара" << "\t" << "Цена" << "\t" << "Количество" << std::endl;
    for(std::size_t i = 0; i < 10; ++i) {
        std::cout << id[i] << "\t" << productName[i] << "\t\t" << price[i] << "\t" << count[i] << std::endl;
    }
}

void storage() {
    std::string get_login = "";
    std::cout << "Напишите свой логин: " << std::endl;
    std::cin >> get_login;
    auto find_login = std::find(loginNames.begin(),loginNames.end(),get_login);
    if(find_login == loginNames.end()) {
        std::cerr << "Такого пользователя с таким логином не существует" << std::endl;
        menu(1);
    }
    std::string _id = "", _price = "", operation = "";
    std::cout << "Выберите операцию по работе с товарами: \n";
    std::cin >> operation;
    if (std::stoi(operation) == 1) {
        std::cout << "Напишите id товара для изменения цены: \n";
        std::cin >> _id;
        if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
            std::cerr << "Ошибка. Товара с таким id не существует. Повторите еще раз" << std::endl;
            storage();
        }
        else {
            std::cout << "Напишите цены товара: \n";
            std::cin >> _price;
            auto find_necessary_price = std::find(price.begin(),price.end(),std::stoi(_price));
            auto find_from_first_element = std::find(price.begin(), price.end(), price.at(0));
            price[std::distance(find_from_first_element, find_necessary_price)] = std::stoi(_price);
            std::cout << "Цена товара успешно изменена" << std::endl;
            storage();
        }
    } else if (std::stoi(operation) == 2) {
        std::cout << "Напишите id товара\n";
        std::cin >> _id;
        if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
            std::cerr << "Ошибка. Товара с таким id не существует. Повторите еще раз" << std::endl;
            storage();
        }
        else {
            std::string newName = "";
            std::cout << "Напишите новое название товара:\n";
            std::cin >> newName;
            auto find_id = std::find(id.begin(),id.end(),std::stoi(_id));
            auto find_from_first_id = std::find(id.begin(), id.end(),id.at(0));
            productName[std::distance(find_from_first_id, find_id)] = newName;
            std::cout << "Название товара было успешно изменено" << std::endl;
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
                std::cerr << "Товар с таким id не существует. Попробуйте еще раз" << std::endl;
                storage();
            }
            else {
                auto find_id = std::find(id.begin(), id.end(), std::stoi(_id));
                auto find_from_first = std::find(id.begin(), id.end(), id.at(0));
                std::cout << "Напишите количество товара для уменьшения\n";
                std::cin >> newCount;
                if (std::stoi(newCount) > count[std::distance(find_from_first, find_id)]) {
                    std::cerr << "Новое количество превышает текущее количество товара. Попробуйте еще раз" << std::endl;
                    storage();
                }
                else {
                    count[std::distance(find_from_first, find_id)] = std::stoi(newCount);
                    std::cout << "Количество товара успешно уменьшено" << std::endl;
                    menu(1);
                }
            }
        }
        else {
            std::cout << "Напишите id товара:\n";
            std::cin >> _id;
            if (std::stoi(_id) < 1 || std::stoi(_id) > id.size()) {
                std::cerr << "Товар с таким id не существует. Попробуйте еще раз" << std::endl;
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
        if (std::isalpha(newNameProduct.at(0),std::locale(""))) {
            std::cerr << "Ошибка наименования товара. Попробуйте еще раз" << std::endl;
            storage();
        }
        std::cout << "Напишите количество нового товара:\n";
        std::cin >> newCount;
        if (std::isalpha(newCount.at(0),std::locale(""))) {
            std::cerr << "Ошибка указания количества товара. Попробуйте еще раз" << std::endl;
            storage();
        }
        std::cout << "Напишите цену нового товара:\n";
        std::cin >> newPrice;
        if (std::isalpha(newPrice.at(0),std::locale(""))) {
            std::cerr << "Ошибка указания цены товара. Попробуйте еще раз" << std::endl;
            storage();
        }
        id.emplace_back(std::stoi(_id));
        productName.emplace_back(newNameProduct);
        count.emplace_back(std::stoi(newCount));
        price.emplace_back(std::stod(newPrice));
        std::cout << "Товар успешно добавлен на склад магазина" << std::endl;
        menu(1);
    }
    else if (std::stoi(operation) == 5) {
        std::cout << "Выход со склада" << std::endl;
        menu(1);
    }
    else {
        std::cerr << "Такой операции не существует. Повторите еще раз" << std::endl;
        storage();
    }
}

int main() {
    setlocale(LC_ALL,"Rus");
    srand(time(NULL));
    login(1);
    return 0;
}
