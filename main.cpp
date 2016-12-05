#include "utils.h"

#define SIMPLE 999983

int main() {
    auto res = Utils::Miller_Rabin(SIMPLE);
//    auto res = test::pow_mod(11,2,100);

    if (res){
        std::cout << "true" << std::endl;
    }else {
        std::cout << "false" << std::endl;
    }

    std::cout << Utils::get_prime_number(999980,999984) << std::endl;
    std::cout << Utils::get_prime_number(999980,999984);
    return 0;
}
