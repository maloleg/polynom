#include "Polynom.hpp"

int main(){
    std::vector<int> b = {1, 2, 0, 4, -5, 0, -7};
    Polynomial<int> a(b);
    Polynomial<int> c({1, 1, 2, 2, 1});
    Polynomial<int> f(-1);
    a *= c;
    if (2 != a) std::cout << a << std::endl << c << std::endl << f << std::endl << c(2);
    return 0;
}