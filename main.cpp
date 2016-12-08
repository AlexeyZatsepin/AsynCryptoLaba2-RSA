#include "rsa.h"

#define PRIME 999983


int main() {
    std::srand(clock());
//    std::cout << Utils::miller_ruben_test(2124679) << std::endl;
//    std::cout << Utils::miller_ruben_test(953) << std::endl;
//    std::cout << Utils::miller_ruben_test(65537) << std::endl;
//    std::cout << Utils::miller_ruben_test(47) << std::endl;
    std::cout << Utils::get_reverse_number_in_field(3, 26) << std::endl;
    std::cout << Utils::get_reverse_number_in_field(2, 41) << std::endl;
    std::cout << Utils::get_reverse_number_in_field(4, 41) << std::endl;

    RSA::Client A("A");
    RSA::generate_key(A);
    A.info();

    RSA::Client B("B");
    RSA::generate_key(B);
    B.info();

    return 0;
}


