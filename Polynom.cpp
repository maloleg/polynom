//#pragma once

#include "Polynom.h"

template <typename T>
class Polynomial;

template <typename T>
std::ostream& operator << (std::ostream &out, const Polynomial<T> a){
    if (!a.Pol.empty()) {
        for (int i = a.Pol.size() - 1; i >= 0; i--) {
            if (a.Pol[i].first < 0) {
                out << " - ";
                if (abs(a.Pol[i].first) != 1) out << abs(a.Pol[i].first);
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
    else out << "this vector is empty";
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


