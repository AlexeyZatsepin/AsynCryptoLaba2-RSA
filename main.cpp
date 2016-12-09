#include "rsa.h"

#define PRIME 999983




int main() {
    int1024_t e = 65537;
    int1024_t d ("378821569148597045159178426294595489046209714793964350359667504364887717525816254910225413531671050318560540853301123956462772271795582868830930193622473");
    int1024_t p ("1749685328275600325280816425530535725608814939035401681676366845420633489669771");
    int1024_t q ("11461151454240905547982277634878335828924195107903843486513544293895720915731827");
    int1024_t n = q*p;
    std::cout << (e*d) % ((p-1)*(q-1)) <<std::endl;
    std::cout << Utils::get_reverse_number_in_field(d,n) <<std::endl;
    std::cout << Utils::gcd(e, (p-1)*(q-1)) <<std::endl;
//    std::cout << Utils::get_reverse_number_in_field(1012,12312313227) <<std::endl;
    std::srand(clock());
//    std::cout << std::boolalpha << Utils::miller_ruben_test(2124679,30) << std::endl;
//    std::cout << std::boolalpha << Utils::miller_ruben_test(953,30) << std::endl;
//    std::cout << std::boolalpha << boost::multiprecision::miller_rabin_test(65537,30) << std::endl;
//    std::cout << std::boolalpha << Utils::miller_ruben_test(47,30) << std::endl;
//    std::cout << Utils::get_reverse_number_in_field(3, 26) << std::endl;
//    std::cout << Utils::get_reverse_number_in_field_i(3, 26) << std::endl;
//    std::cout << Utils::get_reverse_number_in_field(2, 41) << std::endl;
//    std::cout << Utils::get_reverse_number_in_field_i(2, 41) << std::endl;
//    std::cout << Utils::get_reverse_number_in_field(4, 41) << std::endl;
//    std::cout << Utils::get_reverse_number_in_field_i(4, 41) << std::endl;

    RSA::Client A("A");
    RSA::generate_key(A);
//    A.info();

//    RSA::Client B("B");
//    RSA::generate_key(B);
//    B.info();

    A.decrypt(A.encrypt(5));

    return 0;
}


