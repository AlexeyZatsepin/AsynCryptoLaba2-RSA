#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

#define uint_t uint256_t

using namespace boost::multiprecision;

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
        return 1<<length; // TODO
    }

}