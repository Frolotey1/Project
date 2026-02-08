#include "EnterPoint.h"
#include "Authorization.h"
#include "Contacts.h"
#include "StorageOperations.h"
#include "PremiumAndDiscounts.h"
#include "MomFriendSon.h"
#include "PaymentOperations.h"

void menu(short attempt) {
    if (attempt >= 10) {
        std::cout << YELLOW << "Было использовано более 10 попыток при выборе опции. Попробуйте позже через 5 минут\n" << RESET;
        std::this_thread::sleep_for(std::chrono::seconds(300));
        attempt = 1;
    }
    std::string option = "";
    std::cout << std::right << std::setw(62) << "Возрождение май\n";
    std::string menu_types[]{ "","Товары","Учетные записи","Продажи","Склад","Сын маминой подруги","Контакты","Выйти со своего аккаунта" };
    for (std::size_t i = 1; i < 8; ++i) {
        std::cout << "[" << i << "] " << menu_types[i] << "\n";
    }
    std::cout << LIGHT_BLUE << "Выберите опцию:\n" << RESET;
    std::cin >> option;
    switch (std::stoi(option)) {
    case 1:
        start(1);
        break;
    case 2:
        accounts(1);
        break;
    case 3:
        sales();
        break;
    case 4:
        storage(1);
        break;
    case 5:
        momFriendSon();
        break;
    case 6:
        contacts();
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
