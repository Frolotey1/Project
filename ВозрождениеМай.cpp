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

std::vector<std::string> loginNames{ "admin","user" }, passwords{ "admin","user" },
userRights{ "Супер администратор","Администратор","Сотрудник" },
rights{ userRights[0],userRights[1],userRights[2] };

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

void start() {
    std::cout << std::right << std::setw(62) << "Возрождение май\n";


}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    start();
    return 0;
}
