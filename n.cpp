#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


template <typename T>
class Polynomial;
template <typename T>
const bool operator !=(const Polynomial<T> &lhs, const Polynomial<T> &rhs);
template <typename T>
const bool operator !=(const T& lhs, const Polynomial<T>& rhs);
template <typename T>
const bool operator !=(const Polynomial<T>& lhs, const T& rhs);
template <typename T>
const bool operator==(const Polynomial<T> &lhs, const Polynomial<T> &rhs);
template <typename T>
const bool operator ==(const Polynomial<T> &lhs, const T& rhs);
template <typename T>
const bool operator==(const T& lhs, const Polynomial<T> &rhs);
template <typename T>
Polynomial<T> operator +=(Polynomial<T>& lhs, const Polynomial<T>& rhs);
template <typename T>
Polynomial<T> operator +=(Polynomial<T> &lhs, const T& rhs);
template <typename T>
const Polynomial<T> operator +(const Polynomial<T>& lhs, const Polynomial<T>& rhs);
template <typename T>
const Polynomial<T> operator +(const Polynomial<T> &lhs, const T& rhs);
template <typename T>
const Polynomial<T> operator +(const T& lhs, const Polynomial<T> &rhs);
template <typename T>
Polynomial<T> operator -=(Polynomial<T>& lhs, const Polynomial<T>& rhs);
template <typename T>
Polynomial<T> operator -=(Polynomial<T>& lhs, const T& rhs);
template <typename T>
const Polynomial<T> operator -(const Polynomial<T>& lhs, const Polynomial<T>& rhs);
template <typename T>
const Polynomial<T> operator -(const Polynomial<T> &lhs, const T& rhs);
template <typename T>
const Polynomial<T> operator -(const T& lhs, const Polynomial<T> &rhs);
template <typename T>
const Polynomial<T> operator *(const Polynomial<T>& lhs, const Polynomial<T>& rhs);
template <typename T>
const Polynomial<T> operator *(const Polynomial<T>& lhs, const T& rhs);
template <typename T>
const Polynomial<T> operator *(const T& lhs, const Polynomial<T>& rhs);
template <typename T>
Polynomial<T> operator *=(Polynomial<T>& lhs, const Polynomial<T>& rhs);
template <typename T>
Polynomial<T> operator *=(Polynomial<T>& lhs, const T& rhs);
template <typename T>
const Polynomial<T> operator &(const Polynomial<T>& lhs, const Polynomial<T>& rhs);
template <typename T>
std::ostream& operator << (std::ostream &out, const Polynomial<T>& a);

template <typename T>
class Polynomial
{
private:
    std::vector < std::pair<int_fast64_t , T> > coefs = {};
public:
    Polynomial(const std::vector <T> m)
    {
        for (T i = 0; i < m.size(); ++i)
        {
            if(m[i] != 0)
            {
                coefs.push_back(std::make_pair(i, m[i]));
            }
        }
    }
    Polynomial(const T& value)
    {
        coefs.push_back(std::make_pair(0, value));
    }
    Polynomial(T First, T Last)
    {
        for (T it = First; it != Last; ++it){
            if (*it != 0) {
                coefs.push_back(std::make_pair((int)it, *it));
            }
        }
    }
    void normalize();
    const int_fast64_t Degree();
    friend const bool operator ==<T>(const Polynomial<T>& lhs, const Polynomial<T>& rhs);
    friend const bool operator !=<T>(const Polynomial<T>& lhs, const Polynomial<T>& rhs);
    friend Polynomial<T> operator +=<T>(Polynomial<T>& lhs, const Polynomial<T>& rhs);
    friend Polynomial<T> operator -=<T>(Polynomial<T>& lhs, const Polynomial<T>& rhs);
    friend const Polynomial<T> operator *<T>(const Polynomial<T>& lhs, const Polynomial<T>& rhs);
    const T operator ()(const T& p);
    const T operator [](const int_fast64_t& a);
    friend const Polynomial<T> operator &<T>(const Polynomial<T>& lhs, const Polynomial<T>& rhs);
    friend std::ostream& operator << <T> (std::ostream& out, const Polynomial<T>& a);
};
template <typename T>
Polynomial<T> pow(const Polynomial<T>& a, const int k)
{
    Polynomial<T> y(1);
    for (int i = 0; i < k; ++i)
    {
        y *= a;
    }
    return y;
}
template <typename T>
const int_fast64_t Polynomial<T>::Degree()
{
    return coefs[coefs.size() - 1].first;
}
template <typename T>
void Polynomial<T>::normalize()
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
template <typename T>
const bool operator !=(const Polynomial<T> &lhs, const Polynomial<T> &rhs)
{
    return lhs.coefs != rhs.coefs;
}
template <typename T>
const bool operator !=(const T& lhs, const Polynomial<T>& rhs)
{
    return rhs != lhs;
}
template <typename T>
const bool operator !=(const Polynomial<T>& lhs, const T& rhs)
{
    Polynomial<T> s(rhs);
    return lhs != s;
}
template <typename T>
const bool operator==(const Polynomial<T> &lhs, const Polynomial<T> &rhs)
{
    return lhs.coefs == rhs.coefs;
}
template <typename T>
const bool operator ==(const Polynomial<T> &lhs, const T& rhs)
{
    Polynomial<T> s(rhs);
    return lhs == s;
}
template <typename T>
const bool operator==(const T& lhs, const Polynomial<T> &rhs)
{
    return rhs == lhs;
}
template <typename T>
Polynomial<T> operator +=(Polynomial<T>& lhs, const Polynomial<T>& rhs)
{
    for (int i = 0; i < rhs.coefs.size(); ++i)
    {
        lhs.coefs.push_back(rhs.coefs[i]);
    }
    lhs.normalize();
    return lhs;
}
template <typename T>
Polynomial<T> operator +=(Polynomial<T> &lhs, const T& rhs)
{
    Polynomial<T> y(rhs);
    lhs += y;
    return lhs;
}
template <typename T>
const Polynomial<T> operator +(const Polynomial<T>& lhs, const Polynomial<T>& rhs)
{
    Polynomial<T> y({});
    y = lhs;
    y += rhs;
    return y;
}
template <typename T>
const Polynomial<T> operator +(const Polynomial<T> &lhs, const T& rhs)
{
    Polynomial<T> y(rhs);
    y += lhs;
    return y;
}
template <typename T>
const Polynomial<T> operator +(const T& lhs, const Polynomial<T> &rhs)
{
    Polynomial<T> y(lhs);
    y += rhs;
    return y;
}
template <typename T>
Polynomial<T> operator -=(Polynomial<T>& lhs, const Polynomial<T>& rhs)
{
    for (int i = 0; i < rhs.coefs.size(); ++i)
    {
        lhs.coefs.push_back(std::make_pair(rhs.coefs[i].first, -rhs.coefs[i].second));
    }
    lhs.normalize();
    return lhs;
}
template <typename T>
Polynomial<T> operator -=(Polynomial<T>& lhs, const T& rhs)
{
    Polynomial<T> y(rhs);
    lhs -= y;
    return lhs;
}
template <typename T>
const Polynomial<T> operator -(const Polynomial<T>& lhs, const Polynomial<T>& rhs)
{
    Polynomial<T> y({});
    y = lhs;
    y -= rhs;
    return y;
}
template <typename T>
const Polynomial<T> operator -(const Polynomial<T> &lhs, const T& rhs)
{
    Polynomial<T> y(rhs);
    y = lhs - y;
    return y;
}
template <typename T>
const Polynomial<T> operator -(const T& lhs, const Polynomial<T> &rhs)
{
    Polynomial<T> y(lhs);
    y = y - rhs;
    return y;
}
template <typename T>
const Polynomial<T> operator *(const Polynomial<T>& lhs, const Polynomial<T>& rhs)
{
    Polynomial<T> y(std::vector<T> {});
    for (int i = 0; i < lhs.coefs.size(); ++i)
    {
        for (int j = 0; j < rhs.coefs.size(); ++j)
        {
            y.coefs.push_back(std::make_pair((lhs.coefs[i].first + rhs.coefs[j].first), (lhs.coefs[i].second * rhs.coefs[j].second)));
        }
    }
    y.normalize();
    return y;
}
template <typename T>
const Polynomial<T> operator *(const Polynomial<T>& lhs, const T& rhs)
{
    Polynomial<T> y(rhs);
    y *= lhs;
    return y;
}
template <typename T>
const Polynomial<T> operator *(const T& lhs, const Polynomial<T>& rhs)
{
    Polynomial<T> y(lhs);
    y *= rhs;
    return y;
}
template <typename T>
Polynomial<T> operator *=(Polynomial<T>& lhs, const Polynomial<T>& rhs)
{
    lhs = lhs * rhs;
    return lhs;
}
template <typename T>
Polynomial<T> operator *=(Polynomial<T>& lhs, const T& rhs)
{
    Polynomial<T> y(rhs);
    lhs *= y;
    return lhs;
}
template <typename T>
std::ostream& operator << (std::ostream &out, const Polynomial<T>& a){
    for (int i = a.coefs.size() - 1; i >= 0 ; --i)
    {
        if (a.coefs[i].second < 0) {
            if (i == a.coefs.size() - 1)
            {
                out << "-";
            }
            else
            {
                out << " - ";
            }
            if (abs(a.coefs[i].second) != 1 || a.coefs[i].first == 0)
            {
                out << abs(a.coefs[i].second);
            }
            if(a.coefs[i].first != 0)
            {
                if (a.coefs[i].first == 1)
                {
                    out << "x";
                }
                else
                {
                    out << "x^" << a.coefs[i].first;
                }
            }
        }
        else
        {
            if (i != a.coefs.size() - 1)
            {
                out << " + ";
                if (abs(a.coefs[i].second) != 1 || a.coefs[i].first == 0)
                {
                    out << a.coefs[i].second;
                }
                if(a.coefs[i].first != 0)
                {
                    if (a.coefs[i].first == 1)
                    {
                        out << "x";
                    }
                    else
                    {
                        out << "x^" << a.coefs[i].first;
                    }
                }
            }
            else
            {
                if (abs(a.coefs[i].second) != 1 || a.coefs[i].first == 0)
                {
                    out << a.coefs[i].second;
                }
                if(a.coefs[i].first != 0)
                {
                    if (a.coefs[i].first == 1)
                    {
                        out << "x";
                    }
                    else
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
const T Polynomial<T>::operator [](const int_fast64_t& a)
{
    int i = 0;
    while (i < coefs.size() && a > coefs[i].first)
    {
        ++i;
    }
    if (i == coefs.size() || coefs[i].first != a)
    {
        return 0;
    }
    else
    {
        return coefs[i].second;
    }
}
template <typename T>
const T Polynomial<T>::operator ()(const T& p)
{
    T sum = 0;
    int j = coefs.size() - 1;
    for (int i = coefs[coefs.size() - 1].first; i >= 0; --i)
    {
        sum *= p;
        if (i == coefs[j].first)
        {
            sum += coefs[j].second;
        }
    }
    return sum;
}
template <typename T>
const Polynomial<T> operator &(const Polynomial<T>& lhs, const Polynomial<T>& rhs)
{
    Polynomial sum(std::vector<T> {});
    for (int i = 0; i < lhs.coefs.size(); ++i)
    {
        sum += (lhs.coefs[i].second * pow(rhs, lhs.coefs[i].first));
    }
    return sum;
}
template <typename T>
Polynomial<T> operator %(Polynomial<T>& lhs, Polynomial<T>& rhs)
{
    Polynomial<T> q(lhs);
    Polynomial<T> p(std::vector<T> {0, 1});
    while (q.Degree() > rhs.Degree())
    {
        q -= ((q[q.Degree()])/(rhs[rhs.Degree()]))*(rhs * pow(p, (q.Degree() - rhs.Degree())));
    }
    return q;
}

int main()
{
    Polynomial<double > a({4, 2, 0, 4, -5, 0, -7});
    Polynomial<double> b(std::vector<double > {4, 1, 2, 2, 10});

    std::cout << a << std::endl << b << std::endl;
    //std::cout << b[3] <<  std::endl;
    std::cout << (a&b) << std::endl;
}