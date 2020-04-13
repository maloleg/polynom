#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iterator>

template <typename T>
class Polynomial;

template <typename T>
std::ostream& operator << (std::ostream &out, const Polynomial<T> a){
    for (int i = a.Pol.size() - 1; i >= 0 ; i--){
        if (a.Pol[i].first < 0) {out << " - "; if (abs(a.Pol[i].first) != 1)  out << abs(a.Pol[i].first); out << "x^" << a.Pol[i].second;}
        else
            if (i != a.Pol.size() - 1) {out << " + "; if (abs(a.Pol[i].first) != 1) out << a.Pol[i].first; out << "x^" << a.Pol[i].second;}
            else if (abs(a.Pol[i].first) != 1) {out << a.Pol[i].first; out << "x^" << a.Pol[i].second;}
    }
    return out;
}

template <typename T>
bool operator == (const Polynomial<T> lhs, const Polynomial<T> rhs){
    if (lhs.Pol == rhs.Pol) return 1;
    else return 0;
}

template <typename T>
bool operator == (const Polynomial<T> lhs, T rhs){
    if (lhs.Pol.size() == 1 && lhs.Pol[0].second == 0 && lhs.Pol[0].first == rhs) return 1;
    else return 0;
}

template <typename T>
bool operator == (T lhs, const Polynomial<T> rhs){
    if (rhs.Pol.size() == 1 && rhs.Pol[0].second == 0 && rhs.Pol[0].first == lhs) return 1;
    else return 0;
}

template <typename T>
Polynomial<T> operator + (const Polynomial<T> lhs, const Polynomial<T> rhs){
    std::vector<T> temp;
    int MDegree = 0;

    for (int i = 0; i < lhs.Pol.size(); i++){
        if (lhs.Pol[i].second > MDegree) MDegree = lhs.Pol[i].second;
    }
    for (int i = 0; i < rhs.Pol.size(); i++){
        if (rhs.Pol[i].second > MDegree) MDegree = rhs.Pol[i].second;
    }
    // наверное можно было и проще(

    temp.resize(MDegree + 1);

    for (int i = 0; i < lhs.Pol.size(); i++){
        temp[lhs.Pol[i].second] += lhs.Pol[i].first;
    }
    for (int i = 0; i < rhs.Pol.size(); i++){
        temp[rhs.Pol[i].second] += rhs.Pol[i].first;
    }

    Polynomial<T> a(temp);

    temp.clear();

    return a;
}

template <typename T>
class Polynomial {
public:
    std::vector<std::pair<T, int>> Pol;

    Polynomial(std::vector<T> b){
        Pol.clear();
        for (int i = 0; i < b.size(); i++){
            if (b[i] != 0){
                Pol.push_back(std::make_pair(b[i], i));
            }
        }
    }

    Polynomial(T a){
        Pol.clear();
        Pol.push_back(std::make_pair(a, (int) 0));
    }

//    Polynomial(std::iterator First, std::iterator Last){
//        Pol.clear();
//        for (auto it; it != Last; it++){
//            if (*it != 0) {
//                Pol.push_back(std::make_pair(*it, (int) it));
//            }
//        }
//    }



    //friend std::ostream& operator <<<T> (std::ostream &out, const Polynomial &a);

};





int main()
{
    std::vector<int> b = {1, 2, 0, 4, -5, 0, 7};
    Polynomial<int> a(b);
    Polynomial<int> c({1, 1, 2, 2, 1});
    a = a + c;
    std::cout << a;


    return 0;
}