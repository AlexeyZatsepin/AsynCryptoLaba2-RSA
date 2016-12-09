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

    struct Client {
        secret_keys sk;
        open_keys ok;
        string name;

        inline void set_open_keys(open_keys k) {
            ok = k;
        }

        inline void set_secret_keys(secret_keys k) {
            sk = k;
        }

        void generate_key() {
            cout << "Client " << name << endl;
            cout << "+++ key generator +++" << endl;
            int1024_t p = Utils::get_prime_number(256);
            cout << "p generated: " << hex << p << endl;
            int1024_t q = Utils::get_prime_number(256);
            cout << "q generated: " << hex << q << endl;
            cout << "n generated: " << hex << q * p << endl;
            int1024_t fi = (p - 1) * (q - 1);
            cout << "fi(n)    =   " << hex <<fi << endl;
            int1024_t e = (1 << 16) + 1;
            if (Utils::gcd(e, fi) == 1) {
                int1024_t d = Utils::get_reverse_number_in_field(e, fi);
                assert(e * d % fi == 1);
                cout << "d generated: " << hex << d << endl;
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
            cout << "+++ keys generated +++" << endl;
        }

        Client(string n) {
            name = n;
            generate_key();
        };

    };
    int1024_t encrypt(int1024_t message, open_keys ok) {
        int1024_t c = boost::multiprecision::powm(message, ok.e, ok.n);
        return message < (ok.n - 1) ? c : 0;
    }

    int1024_t decrypt(int1024_t cipher, secret_keys sk) {
        int1024_t m = boost::multiprecision::powm(cipher, sk.d, sk.p*sk.q);
        return m;
    }

    int1024_t sign(int1024_t message, secret_keys sk) {
        int1024_t s = boost::multiprecision::powm(message, sk.d, sk.p*sk.q);
        return s;
    }

    bool verify(int1024_t message, int1024_t sign, open_keys ok) {
        int1024_t m = boost::multiprecision::powm(sign, ok.e, ok.n);
        return message == m;
    }

    pair<int1024_t,int1024_t> send_key(int1024_t e1,int1024_t n1, secret_keys sk){
        int1024_t k = rand();
        cout << "generated K by first client: "<< hex << k << endl;
        int1024_t s = boost::multiprecision::powm(k, sk.d, sk.p*sk.q);
        int1024_t k1 = boost::multiprecision::powm(k, e1, n1);
        int1024_t s1 = boost::multiprecision::powm(s, e1, n1);
        return make_pair(k1,s1);
    }

    bool recieve_key(int1024_t e,int1024_t n,int1024_t k1,int1024_t s1, secret_keys sk1){
        int1024_t k = boost::multiprecision::powm(k1, sk1.d, sk1.q*sk1.p);
        int1024_t s = boost::multiprecision::powm(s1, sk1.d, sk1.q*sk1.p);
        cout <<"verified K by second client: "<< hex << k << endl;
        return k == boost::multiprecision::powm(s, e, n);
    }


}
