#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/math/common_factor.hpp>
#include <boost/math/special_functions/pow.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

#include <algorithm>
#include <time.h>

using uint1024_t = boost::multiprecision::uint1024_t;
using int1024_t = boost::multiprecision::int1024_t;

namespace Generator{
    int next(){
        return std::rand() % 256;
    }

    int1024_t generate(int N){
        int1024_t n = 0;
        for (auto i=0;i < N;i+=8){
            std::srand(clock());
            int1024_t t = next();
            int1024_t temp = t << i;
            n = n | temp;
        }
        return n;
    }

}
namespace Utils {
    int1024_t gcd(int1024_t number1, int1024_t number2) {
        if (number2 == 0) {
            return number1;
        } else {
            return gcd(number2, number1 % number2);
        }
    }

    int1024_t get_reverse_number_in_field(int1024_t n, int1024_t m) {// number , mod
        int1024_t x;
        int1024_t y;
        int1024_t mod = m;
        int1024_t b = mod;
        int1024_t a = n;
        if (b == 0) {
            x = 1;
            y = 0;
            if (a == 1) {
                return x;
            }
        }
        else {
            int1024_t q;
            int1024_t r;
            int1024_t x1 = 0;
            int1024_t x2 = 1;
            int1024_t y1 = 1;
            int1024_t y2 = 0;
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
                    int1024_t temp = x2%mod;
                    if (temp < 0) {
                        temp += mod;
                    }
                    return temp;
                }
            }
        }
        return -1;
    }

//    bool miller_ruben_test(uint1024_t number,unsigned int k) {
//        uint1024_t d = number-1;
//        uint1024_t s = 0;
//        while (d%2 == 0) {
//            d /= 2;
//            s++;
//        }
//
//        auto counter = 0;
//
//        while (counter++ < k) {
//            uint1024_t x = std::rand() % (number - 1);
//            if (gcd(x,number) == 1) {
//                if ((powm(x, d, number) == 1)
//                    || (powm(x, d, number)==number-1)) {
//                    return true;
//                }
//                else {
//                    for (int r = 1; r < s; r++) {
//                        uint1024_t t = d * (long long)pow(2,r);
//                        uint1024_t xR = pow(r,t) % number;
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

//    int1024_t get_prime_number(int1024_t n1,int1024_t n2){
//        int1024_t x = std::rand()%(n2-n1+1) + n1;
//        if (x%2==0){
//            x = x+1;
//        }
//        for (auto i = 0; i < ((n1-x)/2); i++){
//            int1024_t p = x+2*i;
//            if (boost::multiprecision::miller_rabin_test(p.convert_to<uint1024_t>(),30)){
//                return p;
//            }
//        }
//        return get_prime_number(n2,2*n2-2); // bertran
//    }

    int1024_t get_prime_number(int length) {
        std::cout << "Generate prime number by bits count:" << std::endl;
        bool flag = true;
        int1024_t p;
        while (flag) {
            p = Generator::generate(length);
//            std::cout << p << std::endl;
            if (boost::multiprecision::miller_rabin_test(p.convert_to<uint1024_t>(), 30)) {
                flag = false;
            }
        }
        std::cout << "Prime number generated" << std::endl;
        return p;
    }

    int1024_t get_prime_number() {
        int1024_t p1 = Utils::get_prime_number(256);
        int i = 0;
        while (1) {
            auto p = p1 * 2 * i + 1;
            if (boost::multiprecision::miller_rabin_test(p.convert_to<uint1024_t>(), 30)) {
                return p;
            }
            i++;
        }
    }

}