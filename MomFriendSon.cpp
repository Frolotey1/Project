#include "MomFriendSon.h"
#include "EnterPoint.h"

void momFriendSon() {
    if (use_mom_friend_son == 1) {
        if (is_mom_friend_son == 0) {
            std::cout << RED << "Режим '" << "Сын маминой подруги" << "' был отключен\n" << RESET;
            std::cout << RED << "Вы больше не сможете его включить" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            system("cls");
            menu(1);
        }
        std::cerr << YELLOW << "Режим 'Сын маминой подруги' уже активирован\n" << RESET;
        std::string delete_mom_friend_son = "";
        std::cout << "Для отключения режима напишите 1. Если не хотите отключать, напишите 0:\n";
        std::cin >> delete_mom_friend_son;
        if (std::stoi(delete_mom_friend_son) == 1) {
            is_mom_friend_son = 0;
            std::cout << GREEN << "Режим '" << "Сын маминой подруги" << "' успешно отключен" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("cls");
            menu(1);
        }
        else {
            menu(1);
        }
    }
    is_mom_friend_son = 1;
    std::cout << GREEN << "Режим '" << "Сын маминой подруги" << "' активирован" << RESET << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    use_mom_friend_son++;
    system("cls");
    menu(1);
}
