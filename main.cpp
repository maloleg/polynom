#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

template <typename T>
class Polynomial;

template <typename T>
std::ostream& operator << (std::ostream &out, const Polynomial<T> a){
    for (int i = 0; i < a.size(); i++){
        out << a[i] << "^" << i << " ";
    }
    return out;
}

template <typename T>
class Polynomial {
public:
    std::vector<std::pair<T, int_fast8_t>> Pol;

    Polynomial(std::vector<T> a){
        Pol.clear();
        for (int i = 0; i < a.size(); i++){
            if (a[i] != 0){
                Pol.push_back({a[i], i});
            }
        }
    }

    Polynomial(T a){
        Pol.clear();
        Pol.push_back({a, 0});
    }

//    Polynomial(std::iterator First, std::iterator Last){
//        Pol.clear();
//        for (auto it; it != Last; it++){
//            Pol.push_back(*it, (int) it);
//        }
//    }

    friend std::ostream& operator << (std::ostream &out, const Polynomial<T> &a);

};





int main()
{
    Polynomial<int> a({1, 2, 0, 4, 5, 0, 7});
    std::cout << a;


    return 0;
}