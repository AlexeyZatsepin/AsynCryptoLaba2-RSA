#include <iostream>
#include "generator.h"

namespace Utils{
    uint_t pow_mod(uint_t a,uint_t t,uint_t n){
        uint_t b=1;
        while (t) {
             if (t%2==0) {
                t /= 2;
                a = (a*a)%n;
            }
            else {
                t--;
                b = (b*a)%n;
            }
        }
        return b;
    }
    bool try_test(uint_t p){
        return ((p%3==0) && (p%5 == 0) && (p%7 == 0));
    }

    bool Miller_Rabin(uint_t p){
        uint_t n = p-1;
        uint_t t = 0;
        uint_t s = 0;
        while (n%2==0){
            n = n>>1;
            s++;
        }
        t = n;

        for (auto k = 0; k < 30; k++){
            auto r = std::rand()%(n-2-2+1) + 2;
            auto x = pow_mod(r,t,p);
            if ((x==1)|(x==n)) break;
            if (s<1) break;
            for(uint_t i = 0;i < s-1;i++){
                x = x*x%n;
                if (x==1) return false;
                if (x==n-1) break;
            }
            return false;
        }
        return true;
    }

    uint_t get_prime_number(uint_t n1,uint_t n2){
        auto x = std::rand()%(n2-n1+1) + n1;
        if (x%2==0){
            x = x+1;
        }
        for (auto i = 0; i < ((n1-x)/2); i++){
            auto p = x+2*i;
            if (Miller_Rabin(p)){
                return p;
            }
        }
        return get_prime_number(n2,2*n2-2); // bertran
    }

    uint_t get_prime_number(int length){
        bool flag = true;
        uint_t p;
        while (flag){
            p = Generator::generate(length);
//            std::cout << p << std::endl;
            if (Miller_Rabin(p)){
                flag = false;
            }
        }
        return p;
    }

    uint_t euler(uint_t n) {
        uint_t result = n;
        for (uint_t i=2; i*i<=n; ++i)
            if (n % i == 0) {
                while (n % i == 0)
                    n /= i;
                result -= result / i;
            }
        if (n > 1)
            result -= result / n;
        return result;
    }

    uint_t get_reverse_number_in_field(uint_t a,uint_t n){
        return boost::multiprecision::powm(a,euler(n)-1,n);
    }


}