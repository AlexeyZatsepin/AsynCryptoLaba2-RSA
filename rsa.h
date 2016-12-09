#include "utils.h"
#include <string.h>

namespace RSA{

    struct open_keys{
        int1024_t e;
        int1024_t n;
    };

    struct secret_keys{
        int1024_t p;
        int1024_t q;
        int1024_t d;
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
            int1024_t encrypt(int1024_t message){
                int1024_t c = boost::multiprecision::powm(message,ok.e,ok.n);
                std::cout<<"Cipher "<< c << std::endl;
                return message<(ok.n-1) ? c:0;
            }

            int1024_t decrypt(int1024_t cipher){
                int1024_t m = boost::multiprecision::powm(cipher,sk.d,ok.n);
                std::cout<<"Decrypted "<< m << std::endl;
                return m;
            }

    };

    int1024_t get_prime_number(){
        int1024_t p1 = Utils::get_prime_number(256);
        int i = 0;
        while (1){
            auto p = p1*2*i +1;
            if (boost::multiprecision::miller_rabin_test(p.convert_to<uint1024_t>(),30)){
                return p;
            }
            i++;
        }
    }

    void generate_key(Client &client){
        std::cout << "+++ key generator +++" << std::endl;
        int1024_t p = get_prime_number();
        std::cout << "p generated: "<< p << std::endl;
        int1024_t q = get_prime_number();
        std::cout << "q generated: " << q << std::endl;
        std::cout << "n generated: " << q*p << std::endl;
        int1024_t fi = (p-1)*(q-1);
        std::cout << "fi(n)    =   " << fi << std::endl;
        int1024_t e = (1<<16) + 1;
        if (Utils::gcd(e, fi)==1){
            int1024_t d = Utils::get_reverse_number_in_field(e,fi);
            assert(e*d%fi==1);
            std::cout << "d generated: "<< d << std::endl;
            open_keys ok;
            ok.e = e;
            ok.n = p*q;
            secret_keys sk;
            sk.d = d;
            sk.p = p;
            sk.q = q;
            client.set_open_keys(ok);
            client.set_secret_keys(sk);
        }else{
            generate_key(client);
        }
        std::cout << "+++ keys generated +++" << std::endl;
    }
}
