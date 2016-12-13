#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/math/common_factor.hpp>
#include <boost/math/special_functions/pow.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

#include <algorithm>
#include <time.h>

using namespace boost::multiprecision;
using namespace std;

namespace Generator{
    int next(){
        return rand() % 256;
    }

    int1024_t generate(int N){
        int1024_t n = 0;
        for (auto i=0;i < N;i+=8){
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
        int1024_t b = m;
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
                    int1024_t temp = x2%m;
                    if (temp < 0) {
                        temp += m;
                    }
                    return temp;
                }
            }
        }
        return -1;
    }

    bool miller_ruben_test(int1024_t number,unsigned int k) {
        int1024_t d = number-1;
        int1024_t s = 0;
        while (d%2 == 0) {
            d /= 2;
            s++;
        }
        auto counter = 0;

        while (counter++ < k) {
            int1024_t x = rand() % (number - 1);
            if (gcd(x,number) == 1) {
                if ((powm(x, d, number) == 1)
                    || (powm(x, d, number)==number-1)) {
                    return true;
                }
                else {
                    for (int1024_t r = 1; r < s; r++) {
                        int1024_t two = 2;
                        int1024_t t = powm(two, r, number);
                        t *= d;
                        int1024_t temp = powm(r, t, number);
                        int1024_t xR = temp % number;
                        if (xR == number - 1) {
                            return true;
                        }
                        else if (xR == 1) {
                            return false;
                        }
                    }
                }
            }
            else {
                return false;
            }
        }
        return true;
    }

    int1024_t get_prime_number(int lenght) {
        bool flag = true;
        int1024_t temp;
        while (flag) {
            temp = Generator::generate(lenght);
            if (miller_rabin_test(temp.convert_to<uint1024_t>(), 30)) {
                flag = false;
            }
        }
        int i = 0;
        while (1) {
            auto p = temp * 2 * i + 1;
            if (miller_rabin_test(p.convert_to<uint1024_t>(), 30)) {
                return p;
            }
            i++;
        }
    }

}