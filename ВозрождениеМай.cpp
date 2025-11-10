#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <thread>
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
        std::cout << "Авторизация\n";
        std::cout << "Введите своё имя пользователя:\n";
        std::getline(std::cin, loginName);
        std::cout << "Введите свой пароль:\n";
        std::getline(std::cin, password);
        if (loginName.size() < 5 || password.size() < 8) {
            std::cerr << "Логин или пароль меньше указанных параметров.\n" << "Попробуйте еще раз" << std::endl;
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
            std::cout << "Пользователь " << loginNames[std::distance(from_first_name_user, find_loginName)] << " успешно вошел в систему\n";
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

void payment() {};

void momFriendSon() {};

void menu(short attempt) {
    if (attempt >= 10) {
        std::cerr << "Было использовано более 10 попыток при выборе опции. Попробуйте позже через 5 минут\n";
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    short option = 0;
    std::cout << std::right << std::setw(62) << "Возрождение май\n";
    std::string menu_types[]{"","Товары","Учетные записи","Премии с продаж","Продажи","Скидки","Способы оплаты","Склад","Сын маминой подруги"};
    for (std::size_t i = 1; i < 9; ++i) {
        std::cout << i << ") " << menu_types[i] << "\n";
    }
    std::cout << "Выберите опцию:\n";
    std::cin >> option;
    switch (option) {
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
    for (std::size_t i = 0; i < 10; ++i) {

    }
}

void storage() {
    short operation = 0;
    std::string operations[]{"","Изменение цен","Изменение названия","Списание товара","Пополнение склада"};
    for (auto i = 1; i < 5; ++i) {
        std::cout << i << ") " << operations[i] << std::endl;
    }
    std::cout << "Выберите операцию по работе с товарами: \n";
    std::cin >> operation;
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    menu(1);

    return 0;
}
