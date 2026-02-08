#include "Contacts.h"
#include "EnterPoint.h"

void contacts() {
    std::cout << YELLOW << std::right << std::setw(62) << "Контакты:\n" << RESET;
    std::cout << "По вопросам энергетика ИМБА обращаться к 'Муллагалиев Фарит Газизянович':\n";
    std::cout << "1. @Black_Lotus00713 (Telegram)\n";
    std::cout << "2. @black_lotus_m (VK)\n";
    std::cout << YELLOW << std::right << std::setw(62) << "Местоположение:\n" << RESET;
    std::cout << "Город: Екатеринбург\n";
    std::cout << "Улица: Фурманова 57" << std::endl;
    menu(1);
}
