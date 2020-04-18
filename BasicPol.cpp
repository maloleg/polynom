// Polynomial.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>


template <typename T>
class Polynomial {
public:
    using i64 = std::int64_t;
    using Container = typename std::vector<T>;
    using ConstIterator = typename Container::const_iterator;

    static const T valueTypeZero{ static_cast<T>(0) };


private:
    Container coefficients_;

    void _normalize() {
        while (!coefficients_.empty() && coefficients_.back() == valueTypeZero) {
            coefficients_.pop_back();
        }
    }

    Container& GetCoeffs() {
        return coefficients_;
    }

public:


    Polynomial(const Container& coefficients)
            : coefficients_{ coefficients } {
        _normalize();
    }

    Polynomial(const T& value = {}) {
        if (value != valueTypeZero) {
            coefficients_.push_back(value);
        }
    }

    template<typename ForwardIt>
    Polynomial(ForwardIt first, ForwardIt last)
            : coefficients_{ first, last } {
        _normalize();
    }

    const Container& GetCoeffs() const {
        return coefficients_;
    }
    friend bool operator==(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return lhs.GetCoeffs() == rhs.GetCoeffs();
    }

    friend bool operator!=(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return !(lhs == rhs);
    }
    Polynomial<T>& operator+=(const Polynomial<T>& other) {
        if (other.Degree() > Degree()) {
            GetCoeffs().resize(other.Degree() + 1);
        }

        for (i64 i = 0; i <= Degree() && i <= other.Degree(); ++i) {
            GetCoeffs()[i] += other.GetCoeffs()[i];
        }
        _normalize();
        return *this;
    }

    Polynomial<T>& operator-=(const Polynomial<T>& other) {
        if (other.Degree() > Degree()) {
            GetCoeffs().resize(other.Degree() + 1);
        }

        for (i64 i = 0; i <= Degree() && i <= other.Degree(); ++i) {
            GetCoeffs()[i] -= other.GetCoeffs()[i];
        }
        _normalize();
        return *this;
    }

    Polynomial<T>& operator*=(const Polynomial<T>& other) {
        if (Degree() == -1 || other.Degree() == -1) {
            GetCoeffs().resize(0);
            return *this;
        }

        std::vector<T> tmp(Degree() + other.Degree() + 1);
        for (i64 i = 0; i <= Degree(); ++i) {
            for (i64 j = 0; j <= other.Degree(); ++j) {
                tmp[i + j] += GetCoeffs()[i] * other.GetCoeffs()[j];
            }
        }
        GetCoeffs() = std::move(tmp);
        _normalize();
        return *this;
    }
    friend Polynomial<T> operator+(Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs += rhs;
    }

    friend Polynomial<T> operator-(Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs -= rhs;
    }

    friend Polynomial<T> operator*(Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs *= rhs;
    }
    i64 Degree() const {
        return static_cast<i64>(GetCoeffs().size()) - 1;
    }

    const T& operator[](size_t power) const {
        return static_cast<i64>(power) > Degree() ? valueTypeZero : GetCoeffs()[power];
    }
    T operator()(const T& givenValue) const {
        T result = valueTypeZero;

        for (auto i = Degree(); i >= 0; --i) {
            result *= givenValue;
            result += GetCoeffs()[i];
        }

        return result;
    }
    ConstIterator begin() const {
        return GetCoeffs().cbegin();
    }

    ConstIterator end() const {
        return GetCoeffs().cend();
    }
    friend Polynomial<T> operator&(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        Polynomial<T> result;  // = 0 as default;

        for (auto i = lhs.Degree(); i >= 0; --i) {
            result *= rhs;
            result += lhs[i];
        }

        return result;
    }
    friend Polynomial<T> operator/(Polynomial<T> lhs, const Polynomial<T>& rhs) {
        if (lhs.Degree() < rhs.Degree() || lhs.Degree() == -1) {
            return {};
        }

        const auto quotient = lhs[lhs.Degree()] / rhs[rhs.Degree()];
        if (lhs.Degree() == rhs.Degree()) {
            return { quotient };
        }

        Container answer(lhs.Degree() - rhs.Degree() + 1);
        answer.back() = quotient;

        for (auto i = lhs.Degree(); i >= lhs.Degree() - rhs.Degree(); --i) {
            lhs.GetCoeffs()[i] = lhs[i] - rhs[rhs.Degree() - lhs.Degree() + i] * quotient;
        }
        lhs._normalize();
        return answer + lhs / rhs;
    }
    friend Polynomial<T> operator%(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return lhs - (lhs / rhs) * rhs;
    }

    friend Polynomial<T> operator,(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        if (lhs == lhs.valueTypeZero) {
            if (rhs.Degree() != -1) {
                return rhs / rhs[rhs.Degree()];
            }
            return rhs;
        }
        return (rhs % lhs, lhs);
    }
};
template<typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& polynomial) {
    const T zero = static_cast<T>(0), one = static_cast<T>(1),
            minusOne = static_cast<T>(-1);
    if (polynomial.Degree() == -1) {
        return out << zero;
    }

    bool firstWriten = false;
    for (auto degree = polynomial.Degree(); degree >= 0; --degree) {
        const auto& coefficient = polynomial[degree];
        if (coefficient == zero) {
            continue;
        }

        if (coefficient > zero && firstWriten) {
            out << '+';
        }
        else if (degree > 0 && coefficient == minusOne) {
            out << '-';
        }

        if (!degree || (coefficient != one && coefficient != minusOne)) {
            out << coefficient;
            if (degree > 0) {
                out << '*';
            }
        }

        if (degree > 0) {
            out << 'x';
            if (degree > 1) {
                out << '^' << degree;
            }
        }
        firstWriten = true;
    }
    return out;
}


int main()
{
    const Polynomial<int> x((std::vector<int>) {1, 1});
    const Polynomial<int> x2((std::vector<int>) {-2});

    std::cout << x/x2;


    return 0;
}