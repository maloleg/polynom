#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

template <typename T>
class Polynomial;
template <typename T>
bool operator !=(const Polynomial<T> &lhs, const Polynomial<T> &rhs)
{
    return lhs.coefs != rhs.coefs;
}
template <typename T>
bool operator==(const Polynomial<T> &lhs, const Polynomial<T> &rhs)
{
    return lhs.coefs == rhs.coefs;
}
template <typename T>
bool operator !=(const Polynomial<T>& lhs, const T& rhs)
{
    Polynomial<T> s(rhs);
    return lhs != s;
}
template <typename T>
bool operator ==(const Polynomial<T> &lhs, const T& rhs)
{
    Polynomial<T> s(rhs);
    return lhs == s;
}

template <typename T>
Polynomial<T> operator + (Polynomial<T>& lhs, const Polynomial<T> rhs){
    lhs += rhs;
    return lhs;
}
template <typename T>
Polynomial<T> operator += (Polynomial<T>& lhs, Polynomial<T> rhs){
    for (int i = 0; i < rhs.coefs.size(); i++){
        lhs.coefs.push_back(rhs.coefs[i]);
    }
    lhs.normalize();
    return lhs;
}
template <typename T>
std::ostream& operator << (std::ostream &out, const Polynomial<T>& a){
    for (int i = a.coefs.size() - 1; i >= 0 ; i--)
    {
        if (a.coefs[i].second < 0) {
            out << " - ";
            if (abs(a.coefs[i].second) != 1)
            {
                out << abs(a.coefs[i].second);
            }
            if(a.coefs[i].first != 0)
            {
                out << "x^" << a.coefs[i].first;
            }
        }
        else
        {
            if (i != a.coefs.size() - 1)
            {
                out << " + ";
                if (abs(a.coefs[i].second) != 1)
                {
                    out << a.coefs[i].second;
                }
                if(a.coefs[i].first != 0)
                {
                    out << "x^" << a.coefs[i].first;
                }
            }
            else
            {
                if (abs(a.coefs[i].second) != 1)
                {
                    out << a.coefs[i].second;
                    if(a.coefs[i].first != 0)
                    {
                        out << "x^" << a.coefs[i].first;
                    }
                }
            }
        }
    }
    return out;
}

template <typename T>
class Polynomial
{
public:
    using container = typename std::vector< std::pair <int_fast64_t , T> >;
private:
    container coefs = {};
public:
    container& GetCoefs()
    {
        return coefs;
    }
    Polynomial(const std::vector <T> m)
    {
        for (T i = 0; i < m.size(); ++i)
        {
            if(m[i] != 0)
            {
                coefs.push_back(std::make_pair((int_fast64_t) i, m[i]));
            }
        }
    }
    Polynomial(const T& value)
    {
        coefs.push_back(std::make_pair(0, value));
    }
    template <typename F>
    Polynomial(F First, F Last)
    {
        for (F it; it != Last; it++){
            if (*it != 0) {
                coefs.push_back(std::make_pair((int)it, *it));
            }
        }
    }
    void normalize()
    {
        std::sort(coefs.begin(), coefs.end());
        for (int i = 0; i < coefs.size(); ++i)
        {
            int j = i + 1;
            while (j < coefs.size() && coefs[j].first == coefs[i].first)
            {
                coefs[i].second += coefs[j].second;
                coefs.erase(coefs.begin() + j);
            }
        }
        for (int i = 0; i < coefs.size(); ++i)
        {
            if (coefs[i].second == 0)
            {
                coefs.erase(coefs.begin() + i);
                --i;
            }
        }
    }
    friend bool operator ==<T>(const Polynomial& lhs, const Polynomial& rhs);
    friend bool operator !=<T>(const Polynomial& lhs, const Polynomial& rhs);
    friend bool operator !=<T>(const Polynomial& lhs, const T& rhs);
    friend bool operator ==<T>(const Polynomial& lhs, const T& rhs);
    friend Polynomial<T> operator +<T> (Polynomial& lhs, const Polynomial rhs);
    friend Polynomial<T> operator +=<T> (Polynomial& lhs, Polynomial rhs);

    friend std::ostream& operator << <T> (std::ostream& out, const Polynomial& a);
};


int main()
{
    std::vector <int> m(3);
    for (int i = 0; i < 3; ++i)
    {
        std::cin >> m[i];
    }
    Polynomial<int> t(6);
    for (int i = 0; i < 3; ++i)
    {
        std::cin >> m[i];
    }
    Polynomial<int> p(5);
    int s = 9;
    std::cout << (p != t) << std::endl;
    std::cout << (p == t) << std::endl;
    std::cout << (p != s) << std::endl;
    p += t;
    std::cout << p << std::endl;
}