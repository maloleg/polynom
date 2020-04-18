#include "Polynom.hpp"

int main(){
    std::vector<int> b = {4, 2, 0, 4, -5, 0, -7};
    Polynomial<int> a(b);
    Polynomial<int> c({4, 1, 2, 2, 1});
    Polynomial<int> f(-1);
    //a *= c;
    if (2 != a) std::cout << a << std::endl << c << std::endl  << (a&c) << std::endl << (a&c)(0) << std::endl;
    return 0;
}