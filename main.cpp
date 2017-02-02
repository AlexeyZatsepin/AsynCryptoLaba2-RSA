#include "rsa.h"
#include "requests.h"

int main() {
    srand((unsigned)clock());
    cout << boolalpha << Utils::miller_ruben_test(7,30)<< endl;

    RSA::Client A("A");
    RSA::Client B("B");
    A.set_keys(RSA::generate_key());
    B.set_keys(RSA::generate_key());

    int1024_t m;
    cout << "Write message: " << endl;
    cin >> m;
    int1024_t c = RSA::encrypt(m,A.ok);
    cout << "Chipred message: "<< dec << c << endl;
    cout << "Dechipred message: "<< RSA::decrypt(c,A.sk) << endl;

    cout << "Generete signutare.. " << endl;
    int1024_t sign = RSA::sign(m,A.sk);
    cout << "Signature: " << sign << endl;

    cout <<"Verify: "<< boolalpha << RSA::verify(m,sign,A.ok) << endl;

    cout << "Send key" <<  endl;
    pair<int1024_t,int1024_t> verify_info = RSA::send_key(B.ok.e,B.ok.n,A.sk);
    cout << "Receive key" <<  endl;
    cout << "Authtorizated A&B connection: "<< boolalpha << RSA::recieve_key(A.ok.e,A.ok.n,verify_info.first,verify_info.second,B.sk) <<endl;

    cout << "------Work with RSA testing environment------" << endl;
    cout << "Please fill size of n (range 128-2048)" << endl;
    int size_n;
    cin >> size_n;
    int1024_t n,e;
    map<string,string> args = {{"keySize",to_string(size_n)}};
    ptree request = requests::get("http://asymcryptwebservice.appspot.com/rsa/serverKey",args);
//    cin >> hex >> n;
//    cin >> hex >> e;
    n = request.get<int1024_t>("modulus",0);
    e = request.get<int1024_t>("publicExponent",0);
//    e = request["publicExponent"];
    cout <<"Server modulus: "<< n << endl;
    cout <<"Server publicExponent: "<< e << endl;
    verify_info = RSA::send_key(e,n,A.sk);
    cout << "N: " << hex <<A.ok.n << endl;
    cout << "e: " << hex <<A.ok.e << endl;
    cout << "K1: " << hex <<verify_info.first << endl;
    cout << "S1: " << hex <<verify_info.second << endl;


//    cout << "Please fill (k,s)" << endl;
//    int1024_t k,s;
//    cin >> hex >> k;
//    cin >> hex >> s;
//    cout << "Authtorizated A & TEST connection: "<< boolalpha << RSA::recieve_key(e,n,k,s,A.sk);
    return 0;
}


