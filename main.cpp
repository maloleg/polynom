#include "Polynom.hpp"

int main(){
    std::vector<int> b = {4, 2, 0, 4, -5, 0, -7};
    Polynomial<int> a(b);
    Polynomial<int> c({4, 1, 2, 2, 1});
    Polynomial<int> f(-1);
    Polynomial<int> g(1);

    Polynomial<double> d1((std::vector<double>){1, 3, 3, 1});
    Polynomial<double> d2((std::vector<double>){1, 1});
    Polynomial<double> d3((std::vector<double>){-2});
    //std::cout << g << std::endl;
    //a *= c;
    if (a != 2) std::cout << d1 << std::endl << d2 << std::endl  << (d2/d3) << std::endl << (d1,d2) << std::endl;
    return 0;
}
