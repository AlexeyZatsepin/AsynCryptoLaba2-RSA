#include <iostream>

namespace test{
    long long pow_mod(long long a,long long t,long long n){
        long b=1;

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

    bool millera_rabena(long long p){
        long long n = p-1;
        long long t = 0;
        long long s = 0;
        while (n%2==0){
            n = n>>1;
            s++;
        }
        t = n;
        for (auto k = 0; k < 30; ++k){
            auto r = std::rand()%(n-2-2+1) + 2;
            auto x = pow_mod(r,t,p);
            if ((x==1)|(x==n)) continue;
            for(auto i = 0;i< s-1;i++){
                x = x*x%n;
                if (x==1) return false;
                if (x==n-1) break;
            }
            return false;
        }
        return true;
    }
}