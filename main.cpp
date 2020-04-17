<<<<<<< HEAD
#include "Polynom.hpp"

int main(){
    std::vector<int> b = {1, 2, 0, 4, -5, 0, 7};
    Polynomial<int> a(b);
    Polynomial<int> c({1, 1, 2, 2, 1});
    Polynomial<int> f({0, 0, 0});
    f = a * c;
    std::cout << a << std::endl << c << std::endl << f << std::endl << f[3];
    return 0;
=======
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
bool operator != (const Polynomial<T> lhs, const Polynomial<T> rhs){
    if (lhs.Pol == rhs.Pol) return 0;
    else return 1;
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
Polynomial<T> operator + (Polynomial<T> lhs, const Polynomial<T> rhs){
    lhs += rhs;
    return lhs;
}

template <typename T>
Polynomial<T> operator += (Polynomial<T>& lhs, Polynomial<T> rhs){
    for (int i = 0; i < rhs.Pol.size(); i++){
        lhs.Pol.push_back(rhs.Pol[i]);
    }
    lhs.normalize();

    return lhs;
}

template <typename T>
Polynomial<T> operator += (Polynomial<T>& lhs, T rhs){
    lhs.Pol[0].first += rhs;
}

template <typename T>
Polynomial<T> operator - (Polynomial<T>& lhs, Polynomial<T> rhs){
    lhs += rhs;
    return lhs;
}

template <typename T>
Polynomial<T> operator -= (Polynomial<T>& lhs, Polynomial<T> rhs){
    for (int i = 0; i < rhs.Pol.size(); i++){
        lhs.Pol.push_back(-rhs.Pol[i]);
    }
    lhs.normalize();

    return lhs;
}

template <typename T>
Polynomial<T> operator -=(Polynomial<T>& lhs, T rhs){
    lhs.Pol[0].first -= rhs;
}

template <typename T>
bool operator != (T lhs, const Polynomial<T> rhs){
    return (rhs.pol.size() != 1 || rhs.pol[0].first != lhs);
}

template <typename T>
bool operator != (const Polynomial<T> lhs, T rhs){
    return (lhs.pol.size() != 1 || lhs.pol[0].first != rhs);
}

template <typename T>
Polynomial<T> operator + (Polynomial<T> lhs, T rhs){
    lhs[0].first += rhs;

    return lhs;

}

template <typename T>
Polynomial<T> operator +(T lhs, Polynomial<T> rhs){
    rhs[0].first += lhs;

    return rhs;
}

template <typename T>
Polynomial<T> operator -(T lhs, Polynomial<T>& rhs){
    rhs[0].first -= lhs;

    return rhs;
}

template <typename T>
Polynomial<T> operator - (Polynomial<T>& lhs, T rhs){
    lhs[0].first -= rhs;

    return lhs;
}

template <typename T>
Polynomial<T> operator *(Polynomial<T>& lhs, const Polynomial<T> rhs){
    Polynomial<T> temp(0);
    temp.Pol.clear();

    for (int i = 0; i < lhs.Pol.size(); i++){
        for (int j = 0; j < rhs.Pol.size(); j++){
            temp.Pol.push_back(std::make_pair(lhs.Pol[i].first*rhs.Pol[j].first, lhs.Pol[i].second+rhs.Pol[j].second));
        }
    }
    temp.normalize();

    return temp;
}

template <typename T>
Polynomial<T> operator *(T lhs, Polynomial<T>& rhs){
    for (int i = 0; i < rhs.Pol.size(); i++){
        rhs.Pol[i].first *= lhs;
    }
    return rhs;
}

template <typename T>
Polynomial<T> operator *(Polynomial<T>& lhs, T rhs){
    for (int i = 0; i < lhs.Pol.size(); i++){
        lhs.Pol[i].first *= rhs;
    }
    return lhs;
}

template <typename T>
Polynomial<T> operator *=(Polynomial<T>& lhs, Polynomial<T> rhs){

}

template <typename T>
Polynomial<T> operator *=(Polynomial<T>& lhs, T rhs){
    for (int i = 0; i < lhs.Pol.size(); i++){
        lhs.Pol[i].first *= rhs;
    }
    return lhs;
}


template <typename T>
class Polynomial {
private:
    std::vector<std::pair<T, int>> Pol;

public:
    friend std::ostream& operator <<<T> (std::ostream &out, const Polynomial a);
    friend bool operator ==<T> (const Polynomial lhs, const Polynomial rhs);
    friend bool operator !=<T> (const Polynomial lhs, const Polynomial rhs);
    friend bool operator !=<T> (T lhs, const Polynomial rhs);
    friend bool operator !=<T> (const Polynomial lhs, T rhs);
    friend bool operator ==<T> (const Polynomial lhs, T rhs);
    friend bool operator ==<T> (T lhs, const Polynomial rhs);
    friend bool operator ==<T> (T lhs, const Polynomial rhs);
    friend Polynomial<T> operator +<T> (const Polynomial lhs, T rhs);
    friend Polynomial<T> operator +<T> (T lhs, const Polynomial rhs);
    friend Polynomial<T> operator +<T> (Polynomial lhs, const Polynomial rhs);
    friend Polynomial<T> operator +=<T> (Polynomial& lhs, Polynomial rhs);
    friend Polynomial<T> operator +=<T> (Polynomial& lhs, T rhs);
    friend Polynomial<T> operator -<T> (Polynomial& lhs, Polynomial rhs);
    friend Polynomial<T> operator -<T> (T lhs, Polynomial& rhs);
    friend Polynomial<T> operator -<T> (Polynomial& lhs, T rhs);
    friend Polynomial<T> operator -=<T> (Polynomial& lhs, Polynomial rhs);
    friend Polynomial<T> operator -=<T> (Polynomial& lhs, T rhs);
    friend Polynomial<T> operator *<T>( Polynomial& lhs, const Polynomial rhs);
    friend Polynomial<T> operator *<T>(T lhs, Polynomial& rhs);
    friend Polynomial<T> operator *<T>(Polynomial& lhs, T rhs);
    friend Polynomial<T> operator *=<T>(Polynomial& lhs, Polynomial rhs);
    friend Polynomial<T> operator *=<T>(Polynomial& lhs, T rhs);

    void normalize(){
        std::sort(Pol.begin(), Pol.end(), [](const std::pair<int,int> &a, const std::pair<int,int> &b){return (a.second < b.second);});
        for (int i = 0; i < Pol.size(); ++i){
            int j = i + 1;

            while (j < Pol.size() && Pol[j].second == Pol[i].second){
                Pol[i].first += Pol[j].first;
                Pol.erase(Pol.begin() + j);
            }
        }
        for (int i = 0; i < Pol.size(); ++i){
            if (Pol[i].first == 0){
                Pol.erase(Pol.begin() + i);
                --i;
            }
        }
    }

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

    template <typename Forw>
    Polynomial(Forw First, Forw Last){
        Pol.clear();
        for (Forw it; it != Last; it++){
            if (*it != 0) {
                Pol.push_back(std::make_pair(*it, (int) it));
            }
        }
    }
};

int main(){
    std::vector<int> b = {1, 2, 0, 4, -5, 0, 7};
    Polynomial<int> a(b);
    Polynomial<int> c({1, 1, 2, 2, 1});
    //a = a * c;
    std::cout << a << std::endl << c << std::endl << a * c;
    return 0;
>>>>>>> 406412490b4995ad274645763692a53be8fdc59f
}