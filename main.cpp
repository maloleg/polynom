#include "Polynom.hpp"

int main(){
    std::vector<int> b = {1, 2, 0, 4, -5, 0, 7};
    Polynomial<int> a(b);
    Polynomial<int> c({1, 1, 2, 2, 1});
    Polynomial<int> f({0, 0, 0});
    f = a * c;
    std::cout << a << std::endl << c << std::endl << f << std::endl << f[3];
    return 0;
}