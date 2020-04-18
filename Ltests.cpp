#include "Polynom.hpp"
using namespace std;

int main() {

    //cout << Polynomial<int>(0).Degree() << endl;
    [[maybe_unused]] double a = 1, b = 2, c = 3;
    Polynomial<double> A(a);
    cout << (A == a) << (a == A) << (A == Polynomial<double>(a))
         << (A == b) << (b == A) << (A == Polynomial<double>(b)) << endl; //111000
    cout << (A != a) << (a != A) << (A != Polynomial<double>(a))
         << (A != b) << (b != A) << (A != Polynomial<double>(b)) << endl; //000111
    cout << (A += a) << " " << (A -= a) << " " << (A *= b) << " "
    //     << (A /= b) << " " << (A += Polynomial<double>(c)) << " "
    //     << (A /= Polynomial<double>(b)) << " "
         << (A += Polynomial<double>(a) - Polynomial<double>(b))
         << endl; //2.000000 1.000000 2.000000 1.000000 4.000000 2.000000 1.000000
    cout << A.Degree() << endl; //0
    cout << Polynomial<int>(0).Degree() << endl; //-1
    cout << A[0] << " " << A[1] << endl; //1 0
    Polynomial<double> B(vector<double>{a, b});
    cout << B(2) << endl; //5
    Polynomial<int> C(vector<int>{(int)a, (int)b, (int)c});
    Polynomial<double> C2(vector<double>{a, b, c});
    cout << C << endl; //3x^2 + 2x + 1
    cout << C2 << endl; //3.000000x^2 + 2.000000x + 1.000000
    for (auto i = C.begin(); i != C.end(); ++i){
        cout << (*i).first << " "; //1 2 3
    }
    cout << endl;
    for (auto i : B){
        cout << i.first << " "; //1 2
    }
    cout << endl;
    cout << (C & C) << endl; //27x^4 + 36x^3 + 36x^2 + 16x + 6
    cout << (C2 / A) << endl; //3.000000x^2 + 2.000000x + 1.000000
    cout << (C2 % A) << endl; //0.000000
    Polynomial<double> C2_buff(C2);
    //cout << (C2 /= A) << endl; //3.000000x^2 + 2.000000x + 1.000000
    //cout << (C2_buff %= A) << endl; //0.000000
    cout << ((C2 & C2 & C2) % B) << endl; //61.980469
    return 0;
}