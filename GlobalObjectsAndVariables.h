#ifndef GLOBALOBJECTSANDVARIABLES_H
#define GLOBALOBJECTSANDVARIABLES_H
#include "ConstantStrings.h"
#include "Libraries.h"

bool is_mom_friend_son = 0, is_new_storage = 0, is_black_friday = 0, discount_sale = 0;

size_t count_sales = 0, count_changed_storage_times = 0, use_mom_friend_son = 0; double earned_money = 0.0;
std::string client = "", discount_product = "", procent_discount = "";
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
std::vector<std::string> favourite_product;
std::vector<std::size_t> favourite_count, favourite_id;
std::vector<double> favourite_price;
#endif // GLOBALOBJECTSANDVARIABLES_H
