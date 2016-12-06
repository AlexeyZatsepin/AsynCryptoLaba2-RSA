#include "utils.h"
#include <string.h>

namespace RSA{

    struct open_keys{
        uint_t e;
        uint_t n;
    };

    struct secret_keys{
        uint_t p;
        uint_t q;
        uint_t d;
    };

    class Client{
        private:
            open_keys ok;
            secret_keys sk;
            std::string name;
        public:
            Client(std::string n){
                name = n;
            };
            void set_open_keys(open_keys k){
                ok = k;
            }
            void set_secret_keys(secret_keys k){
                sk = k;
            }

    };

    uint_t get_prime_number(){
        auto p1 = Utils::get_prime_number(256);
        int i = 0;
        while (1){
            auto p = p1*2*i +1;
            if (Utils::Miller_Rabin(p)){
                return p;
            }
        }
    }

    void generate_key(Client &client){
        uint_t p = get_prime_number();
        uint_t q = get_prime_number();
        uint_t fi = (p-1)*(q-1);
        uint_t e = (1<<16) + 1;
        if (boost::math::gcd(e, fi)==1){
            uint_t d = Utils::get_reverse_number_in_field(e,fi);
            open_keys ok;
            ok.e = e;
            ok.n = p*q;
            secret_keys sk;
            sk.d = d;
            sk.p = p;
            sk.q = q;
            client.set_open_keys(ok);
            client.set_secret_keys(sk);
        }
    }
}
