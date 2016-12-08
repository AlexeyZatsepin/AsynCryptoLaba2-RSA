#include "utils.h"
#include <string.h>

namespace RSA{

    struct open_keys{
        uint256_t e;
        uint256_t n;
    };

    struct secret_keys{
        uint256_t p;
        uint256_t q;
        uint256_t d;
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
            void info(){
                std::cout<<"Name "<< name << std::endl;
                std::cout<<"Open key: " << std::endl;
                std::cout<<"e "<< ok.e << std::endl;
                std::cout<<"n "<< ok.n << std::endl;
                std::cout<<"Secret key: " << std::endl;
                std::cout<<"p "<< sk.p << std::endl;
                std::cout<<"q "<< sk.q << std::endl;
                std::cout<<"d "<< sk.d << std::endl;
            }

    };

    uint256_t get_prime_number(){
        auto p1 = Utils::get_prime_number(256);
        int i = 0;
        while (1){
            auto p = p1*2*i +1;
            if (miller_rabin_test(p,30)){
                return p;
            }
            i++;
        }
    }

    void generate_key(Client &client){
        std::cout << "+++ key generator +++" << std::endl;
        uint256_t p = get_prime_number();
        std::cout << "p generated" << std::endl;
        uint256_t q = get_prime_number();
        std::cout << "q generated" << std::endl;
        uint256_t fi = (p-1)*(q-1);
        uint256_t e = (1<<16) + 1;
        if (boost::math::gcd(e, fi)==1){
            uint256_t d = Utils::get_reverse_number_in_field(e,fi);
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
        std::cout << "+++ keys generated +++" << std::endl;
    }
}
