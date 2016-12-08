#include <iostream>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/common_factor.hpp>

#include <algorithm>
#include <time.h>

using namespace boost::multiprecision;

namespace Generator{
    boost::mt19937 rng;
    boost::uniform_int<> one_to_six(0, 255);
    boost::variate_generator<boost::mt19937, boost::uniform_int<>> dice(rng, one_to_six);
    int next(){
        return std::rand() % 256;
    }

    uint256_t generate(int N){
        uint256_t n = 0;
        for (auto i=0;i < N;i+=8){
            std::srand(clock());
            uint256_t t = next();
            uint256_t temp = t << i;
            n = n | temp;
        }
        return n;
    }

}
namespace Utils {
//    int gcd(int number1, int number2) {
//        if (number2 == 0) {
//            return number1;
//        }
//        else {
//            return gcd(number2, number1 % number2);
//        }
//    }

//    int powm(int a, int t, int n) {
//        int b = 1;
//        while (t) {
//            if (t % 2 == 0) {
//                t /= 2;
//                a = (a*a) % n;
//            }
//            else {
//                t--;
//                b = (b*a) % n;
//            }
//        }
//        return b;
//    }

    uint256_t get_reverse_number_in_field(uint256_t a, uint256_t b) {// number , mod
        uint256_t x;
        uint256_t y;
        uint256_t mod = b;
        if (b == 0) {
            x = 1;
            y = 0;
            if (a == 1) {
                return x;
            }
        }
        else {
            uint256_t q;
            uint256_t r;
            uint256_t x1 = 0;
            uint256_t x2 = 1;
            uint256_t y1 = 1;
            uint256_t y2 = 0;
            while (b > 0) {
                q = a / b;
                r = a - (q*b);
                x = x2 - (q*x1);
                y = y2 - (q*y1);
                a = b;
                b = r;
                x2 = x1;
                x1 = x;
                y2 = y1;
                y1 = y;
                if (a == 1) {
                    uint256_t temp = x2%mod;
                    if (temp < 0) {
                        temp += mod;
                    }
                    return temp;
                }
            }
        }
        return -1;
    }

//    bool miller_ruben_test(uint256_t number) {
//        uint256_t k = 20;
//
//        uint256_t d = number-1;
//        uint256_t s = 0;
//        while (d%2 == 0) {
//            d /= 2;
//            s++;
//        }
//
//        uint256_t counter = 0;
//
//        while (counter++ < k) {
//            int x = std::rand() % (number - 1);
//            if (gcd(x,number) == 1) {
//                if ((powm(x, d, number) == 1)
//                    || (powm(x, d, number)==number-1)) {
//                    return true;
//                }
//                else {
//                    for (int r = 1; r < s; r++) {
//                        int xR = pow(x,d * pow(2,r)) % number;
//                        if (xR == number - 1) {
//                            return true;
//                        }
//                        else if (xR == 1) {
//                            return false;
//                        }
//                    }
//                }
//            }
//            else {
//                return false;
//            }
//        }
//        return true;
//    }

    bool try_test(uint256_t p){
        return ((p%3==0) && (p%5 == 0) && (p%7 == 0));
    }

    uint256_t get_prime_number(uint256_t n1,uint256_t n2){
        auto x = std::rand()%(n2-n1+1) + n1;
        if (x%2==0){
            x = x+1;
        }
        for (auto i = 0; i < ((n1-x)/2); i++){
            auto p = x+2*i;
            if (miller_rabin_test(p,30)){
                return p;
            }
        }
        return get_prime_number(n2,2*n2-2); // bertran
    }

    uint256_t get_prime_number(int length) {
        std::cout << "Generate prime number by bits count:" << std::endl;
        bool flag = true;
        uint256_t p;
        while (flag) {
            p = Generator::generate(length);
//            std::cout << p << std::endl;
            if (miller_rabin_test(p, 30)) {
                flag = false;
            }
        }
        std::cout << "Prime number generated" << std::endl;
        return p;
    }

}