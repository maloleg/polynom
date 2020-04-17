//
// Created by malol on 17.04.2020.
//

#ifndef LAB7_POLYNOM_H
#define LAB7_POLYNOM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iterator>

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

    T operator [](int indx){
        if (indx > this->Degree()) return 0;
        else return Pol[indx].first;
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

    int Degree(){
        this->normalize();
        if (!Pol.empty()) return Pol[Pol.size() - 1].second;
        else return -1;
    }
};


#endif //LAB7_POLYNOM_H
