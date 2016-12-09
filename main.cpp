#include "rsa.h"

#define PRIME 999983


int main() {
//    int1024_t e = 65537;
//    int1024_t d ("378821569148597045159178426294595489046209714793964350359667504364887717525816254910225413531671050318560540853301123956462772271795582868830930193622473");
//    int1024_t p ("1749685328275600325280816425530535725608814939035401681676366845420633489669771");
//    int1024_t q ("11461151454240905547982277634878335828924195107903843486513544293895720915731827");
//    int1024_t n = q*p;
//    cout << (e*d) % ((p-1)*(q-1)) <<endl;
//    cout << Utils::get_reverse_number_in_field(d,n) <<endl;
//    cout << Utils::gcd(e, (p-1)*(q-1)) <<endl;
//    cout << Utils::get_reverse_number_in_field(1012,12312313227) <<endl;
    srand((unsigned)clock());
//    cout << boolalpha << Utils::miller_ruben_test(2124679,30) << endl;
//    cout << boolalpha << Utils::miller_ruben_test(953,30) << endl;
//    cout << boolalpha << boost::multiprecision::miller_rabin_test(65537,30) << endl;
//    cout << boolalpha << Utils::miller_ruben_test(47,30) << endl;
//    cout << Utils::get_reverse_number_in_field(3, 26) << endl;
//    cout << Utils::get_reverse_number_in_field_i(3, 26) << endl;
//    cout << Utils::get_reverse_number_in_field(2, 41) << endl;
//    cout << Utils::get_reverse_number_in_field_i(2, 41) << endl;
//    cout << Utils::get_reverse_number_in_field(4, 41) << endl;
//    cout << Utils::get_reverse_number_in_field_i(4, 41) << endl;

    RSA::Client A("A");

    RSA::Client B("B");

//    RSA::Client B("B");
//    RSA::generate_key(B);
//    B.info();

    int1024_t m;
    cout << "Write message: " << endl;
    cin >> m;
    int1024_t c = RSA::encrypt(m,A.ok);
    cout << "Chipred message: "<< dec << c << endl;
    cout << "Dechipred message: "<< RSA::decrypt(c,A.sk) << endl;

    cout << "Generete signutare: " << endl;
    int1024_t sign = RSA::sign(m,A.sk);
    cout << "Signature: " << sign << endl;

    cout <<"Verify: "<< boolalpha << RSA::verify(m,sign,A.ok) << endl;

    cout << "Send key" <<  endl;
    pair<int1024_t,int1024_t> verify_info = RSA::send_key(B.ok.e,B.ok.n,A.sk);
    cout << "Receive key" <<  endl;
    cout << "Authtorizated A&B connection: "<< boolalpha << RSA::recieve_key(A.ok.e,A.ok.n,verify_info.first,verify_info.second,B.sk) <<endl;

    cout << "------Work with RSA testing environment------" << endl;
    cout << "Please fill public keys (n,e)" << endl;
    int1024_t n,e;
    cin >> hex >> n;
    cin >> hex >> e;
//    open_keys test_ok;
//    test_ok.n=n;
//    test_ok.e=e;
    verify_info = RSA::send_key(e,n,A.sk);
    cout << "N: " << hex <<A.ok.n << endl;
    cout << "e: " << hex <<A.ok.e << endl;
    cout << "K1: " << hex <<verify_info.first << endl;
    cout << "S1: " << hex <<verify_info.second << endl;


    return 0;
}


