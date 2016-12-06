#include "rsa.h"

#define PRIME 999983

void print_bool(bool res){
    if (res){
        std::cout << "true" << std::endl;
    }else {
        std::cout << "false" << std::endl;
    }
}

int main() {
    uint_t big("115792089237316195423570985008687907853269984665640564039457584007911697984170");
    print_bool(Utils::Miller_Rabin(big));

//    std::cout << Utils::get_prime_number(999980,999984) << std::endl;
    std::cout << Utils::get_prime_number(256) << std::endl;
    for (int j = 0; j < 10; ++j) {
        std::cout << Generator::generate(256) << std::endl;
    }


    return 0;
}


