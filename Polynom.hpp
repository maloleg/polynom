#ifndef LAB7_POLYNOM_HPP
#define LAB7_POLYNOM_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include "math.h"

template <typename T>
class Polynomial;

template <typename T>
std::ostream& operator << (std::ostream &out, const Polynomial<T> a){
    if (!a.Pol.empty()) {
        for (int i = a.Pol.size() - 1; i >= 0; i--) {
            if (a.Pol[i].first < 0) {
                if (i != a.Pol.size() - 1) out << " - ";
                else out << "-";
                if (abs(a.Pol[i].first) != 1 || a.Pol[i].second == 0) out << abs(a.Pol[i].first);
                if (a.Pol[i].second != 0 && a.Pol[i].second != 1) out << "x^" << a.Pol[i].second;
                else if (a.Pol[i].second != 0) out << "x";
            }
            else if (i != a.Pol.size() - 1) {
                out << " + ";
                if (abs(a.Pol[i].first) != 1 || abs(a.Pol[i].second) == 0) out << a.Pol[i].first;
                if (a.Pol[i].second != 0 && a.Pol[i].second != 1) out << "x^" << a.Pol[i].second;
                else if (a.Pol[i].second != 0) out << "x";
            }
            else if (abs(a.Pol[i].first) != 1) {
                out << a.Pol[i].first;
                if (a.Pol[i].second != 0 && a.Pol[i].second != 1) out << "x^" << a.Pol[i].second;
                else if (a.Pol[i].second != 0) out << "x";
            }
            else {
                if (a.Pol[i].second != 0 && a.Pol[i].second != 1) out << "x^" << a.Pol[i].second;
                else if (a.Pol[i].second != 0) out << "x";
            }
        }
    }
    else out << "0";
    //я хотел красиво и аккуратно всё написать, но разрослось. Зато работает правда-правда!
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
Polynomial<T> operator + (const Polynomial<T>& lhs, const Polynomial<T>& rhs){
    Polynomial<T> temp = lhs;
    temp += rhs;
    return temp;
}

template <typename T>
Polynomial<T> operator += (Polynomial<T>& lhs, const Polynomial<T>& rhs){
    for (int i = 0; i < rhs.Pol.size(); i++){
        lhs.Pol.push_back(rhs.Pol[i]);
    }
    lhs.normalize();

    return lhs;
}

template <typename T>
Polynomial<T> operator += (Polynomial<T>& lhs, const T& rhs){
    Polynomial<T> temp(rhs);
    temp += lhs;
    return lhs;
}

template <typename T>
Polynomial<T> operator - (const Polynomial<T>& lhs, const Polynomial<T>& rhs){
    Polynomial<T> temp = lhs;
    temp -= rhs;
    return temp;
}

template <typename T>
Polynomial<T> operator -= (Polynomial<T>& lhs, const Polynomial<T>& rhs){
    for (int i = 0; i < rhs.Pol.size(); i++){
        lhs.Pol.push_back(std::make_pair(-rhs.Pol[i].first, rhs.Pol[i].second));
    }
    lhs.normalize();

    return lhs;
}

template <typename T>
Polynomial<T> operator -=(Polynomial<T>& lhs, const T& rhs){
    Polynomial<T> temp(rhs);
    temp -= lhs;
    return temp;
}

template <typename T>
bool operator != (T lhs, const Polynomial<T> rhs){
    return (rhs.Pol.size() != 1 || rhs.Pol[0].first != lhs);
}

template <typename T>
bool operator != (const Polynomial<T> lhs, T rhs){
    return (lhs.Pol.size() != 1 || lhs.Pol[0].first != rhs);
}

template <typename T>
Polynomial<T> operator + (const Polynomial<T>& lhs, const T& rhs){
    Polynomial<T> temp(rhs);

    temp += lhs;

    return temp;
}

template <typename T>
Polynomial<T> operator +(const T& lhs, const Polynomial<T>& rhs){
    Polynomial<T> temp(lhs);

    temp += rhs;

    return temp;
}

template <typename T>
Polynomial<T> operator -(const T& lhs, const Polynomial<T>& rhs){
    Polynomial<T> temp(lhs);

    temp = rhs - temp;

    return temp;
}

template <typename T>
Polynomial<T> operator - (const Polynomial<T>& lhs, const T& rhs){
    Polynomial<T> temp(rhs);

    temp = lhs - temp;

    return temp;
}

template <typename T>
Polynomial<T> const operator *(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
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
const Polynomial<T> operator *(const T& lhs, const Polynomial<T>& rhs){
    Polynomial<T> temp(lhs);
    temp = temp * rhs;
    return temp;
}

template <typename T>
const Polynomial<T> operator *(const Polynomial<T>& lhs, const T& rhs){
    Polynomial<T> temp(rhs);
    temp = temp * lhs;
    return temp;
}

template <typename T>
Polynomial<T> operator *=(Polynomial<T>& lhs, const Polynomial<T>& rhs){
 lhs = lhs * rhs;
 return lhs;
}

template <typename T>
Polynomial<T> operator *=(Polynomial<T>& lhs, const T& rhs){
    lhs = lhs * rhs;
    return lhs;
}

template<typename T>
const Polynomial<T> pow2(Polynomial<T> lhs, int rhs){
    Polynomial<T> temp(1);

    for (int i = 0; i < rhs; i++){
        temp *= lhs;
    }
    temp.normalize();

    return temp;
}


template<typename T>
Polynomial<T> operator & (Polynomial<T> lhs, Polynomial<T> rhs){
    Polynomial<T> temp((std::vector<T>) {});

    for (int i = 0; i < lhs.Pol.size(); i++){
        temp += (pow2(rhs, lhs.Pol[i].second) * lhs.Pol[i].first);
    }
    temp.normalize();

    return temp;
}

template <typename T>
Polynomial<T> operator %(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
    Polynomial<T> q(lhs);
    Polynomial<T> p(std::vector<T> {0, 1});
    while (q.Degree() > rhs.Degree()){
        q -= ((q[q.Degree()])/(rhs[rhs.Degree()]))*(rhs * pow(p, (q.Degree() - rhs.Degree())));
    }
    return q;
}

template <typename T>
Polynomial<T> operator /(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
    Polynomial<T> temp(lhs);
    Polynomial<T> temp2(0);

    while (temp != 0){
        temp -= rhs*temp.Degree();
        temp2 += rhs*temp.Degree();
    }

    return temp2;
}

template <typename T>
Polynomial<T> operator ,(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
    Polynomial<T> temp1 = lhs;
    Polynomial<T> temp2 = rhs;

    while (temp1 != temp2){
        temp1 -= (temp2/temp1) * temp1;
        if (temp1 == temp2) break;
        temp2 -= (temp1/temp2) * temp2;
    }

    return temp1;
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
    friend Polynomial<T> operator -=<T> (Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial<T> operator +=<T> (Polynomial<T>& lhs, const Polynomial<T>& rhs);
    friend const Polynomial<T> operator *<T>(const Polynomial& lhs, const Polynomial& rhs);

    friend Polynomial<T> operator &<T>(Polynomial lhs, Polynomial rhs); //Я так понял что этот метод должен быть контанстным

    const Polynomial<T> pow2(Polynomial<T> lhs, int rhs);

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

    const int Degree(){
        this->normalize();
        if (!Pol.empty()) return Pol[Pol.size() - 1].second;
        else return -1;
    }

    const T operator [](int indx){
        T temp;
        bool check = false;

        this->normalize();
        if (indx > this->Degree()) return 0;
        else
            for (int i = 0; i < Pol.size(); i++){
             if (Pol[i].second == indx) {check = true; temp = Pol[i].first;}
            }
        if (check) return temp;
        else return 0;

    }

    const T operator ()(const T indx){
        T temp = 0;
        for (int i = 0; i < Pol.size(); i++){
            temp += (Pol[i].first * pow(indx, Pol[i].second));
        }
        return temp;
    }
};



#endif //LAB7_POLYNOM_HPP
