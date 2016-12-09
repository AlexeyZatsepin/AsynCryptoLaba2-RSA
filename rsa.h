#include "utils.h"
#include <string.h>

namespace RSA {

    struct open_keys {
        int1024_t e;
        int1024_t n;
    };

    struct secret_keys {
        int1024_t p;
        int1024_t q;
        int1024_t d;
    };

    class Client {
    private:
        open_keys ok;
        secret_keys sk;
        std::string name;

        void set_open_keys(open_keys k) {
            ok = k;
        }

        void set_secret_keys(secret_keys k) {
            sk = k;
        }

        void generate_key() {
            std::cout << "Client " << name << std::endl;
            std::cout << "+++ key generator +++" << std::endl;
            int1024_t p = Utils::get_prime_number();
            std::cout << "p generated: " << p << std::endl;
            int1024_t q = Utils::get_prime_number();
            std::cout << "q generated: " << q << std::endl;
            std::cout << "n generated: " << q * p << std::endl;
            int1024_t fi = (p - 1) * (q - 1);
            std::cout << "fi(n)    =   " << fi << std::endl;
            int1024_t e = (1 << 16) + 1;
            if (Utils::gcd(e, fi) == 1) {
                int1024_t d = Utils::get_reverse_number_in_field(e, fi);
                assert(e * d % fi == 1);
                std::cout << "d generated: " << d << std::endl;
                open_keys ok;
                ok.e = e;
                ok.n = p * q;
                secret_keys sk;
                sk.d = d;
                sk.p = p;
                sk.q = q;
                set_open_keys(ok);
                set_secret_keys(sk);
            } else {
                generate_key();
            }
            std::cout << "+++ keys generated +++" << std::endl;
        }

    public:
        Client(std::string n) {
            name = n;
            generate_key();
        };

        void info() {
            std::cout << "Name " << name << std::endl;
            std::cout << "Open key: " << std::endl;
            std::cout << "e " << ok.e << std::endl;
            std::cout << "n " << ok.n << std::endl;
            std::cout << "Secret key: " << std::endl;
            std::cout << "p " << sk.p << std::endl;
            std::cout << "q " << sk.q << std::endl;
            std::cout << "d " << sk.d << std::endl;
        }

        int1024_t encrypt(int1024_t message) {
            int1024_t c = boost::multiprecision::powm(message, ok.e, ok.n);
            std::cout << "Cipher " << c << std::endl;
            return message < (ok.n - 1) ? c : 0;
        }

        int1024_t decrypt(int1024_t cipher) {
            int1024_t m = boost::multiprecision::powm(cipher, sk.d, ok.n);
            std::cout << "Decrypted " << m << std::endl;
            return m;
        }

        int1024_t sign(int1024_t message) {
            int1024_t s = boost::multiprecision::powm(message, sk.d, ok.n);
            return s;
        }

        bool verify(int1024_t message, int1024_t sign) {
            int1024_t m = boost::multiprecision::powm(sign, ok.e, ok.n);
            return message == m;
        }

        std::pair<int1024_t,int1024_t> send_key(int1024_t e1,int1024_t n1){
//            while (ok.n<n1){
//                generate_key();
//            }
            int1024_t k = rand();
            int1024_t s = boost::multiprecision::powm(k, sk.d, ok.n);
            int1024_t k1 = boost::multiprecision::powm(s, e1, n1);
            int1024_t s1 = boost::multiprecision::powm(k, e1, n1);
            return std::make_pair(k1,s1);
        }
        //send key, receive key

        bool recieve_key(int1024_t e,int1024_t n,int1024_t k1,int1024_t s1){
            int1024_t k = boost::multiprecision::powm(k1, sk.d, ok.n);
            int1024_t s = boost::multiprecision::powm(s1, sk.d, ok.n);
            return k == boost::multiprecision::powm(s, e, n);
        }


    };


}
