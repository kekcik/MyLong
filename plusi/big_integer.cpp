#include "big_integer.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <string>
#define ull unsigned long long
#define ll long long
#define ui unsigned int
unsigned long long p = 1 << 30;
unsigned long long mod = 4 * p;

bool boolAt (int pos)
{
    return true;
}

std::string to_string(big_integer const& a)
{
    std::string res = "";
    big_integer aa (a);
    big_integer bb (0);
    big_integer cc (0);
    big_integer dd (0);
    if (a.flag == 1) {
        aa.flag = false;
    }
    if (a == big_integer(0)) return "0";
    while ((aa) > big_integer(0))
    {
        bb = aa / big_integer(1000000000);
        cc = bb * big_integer(1000000000);
        dd = aa - cc;
        aa = bb;
        for (int i = 0; i < 9; i++)
        {
            res += dd.data[0] % 10 + 48;
            dd.data[0] /= 10;
        }
    }
    while (res[res.size() - 1] == '0') res.pop_back();
    if (a.flag == 1) {
        res+='-';
    }
    for (int  i = 0; i < res.size()/2; ++i)
    {
        std::swap(res[i], res[res.size()-1-i]);
    }
    return res;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a)
{
    return s << to_string(a);
}


big_integer::big_integer()
{
    this->data.clear();
    this->data.push_back(0);
    this->flag = false;
}

big_integer::big_integer(std::string str)
{
    if (str[0] == '-') flag = true; else flag = false;
    for (int i = 0; i < str.size(); ++i)
    {
        *this *= big_integer(10);
        *this += big_integer(str[i] - 48);
    }
}

big_integer::big_integer(big_integer const& other)
{
    this -> flag = other.flag;
    this -> data = other.data;
}

big_integer::big_integer(int a)
{
    this -> flag = a < 0 ? 1 : 0;
    data.push_back(a < 0 ? -a : a);
}

//delete it!

big_integer& big_integer::operator=(big_integer const& other)
{
    this -> data = other.data;
    this -> flag = other.flag;
    return *this;
}

bool operator==(big_integer const& a, big_integer const& b)
{
    if (a.flag == b.flag and a.data.size() == b.data.size()) {
        for (int i = 0; i < (int)a.data.size(); i++) {
            if (a.data[i] != b.data[i]) return false;
        }
        return true;
    }
    return false;
}

bool operator!=(big_integer const& a, big_integer const& b)
{
    return !operator==(a, b);
}

//?
bool operator<(big_integer const& a, big_integer const& b)
{
    
    if (a.flag != b.flag) return a.flag;
    if (a.data.size() != b.data.size())
    {
        return ((a.data.size() < b.data.size()) ^ a.flag);
    }
    int i;
    for (i = (int) a.data.size() - 1; i >= 0 and a.data[i] == b.data[i]; --i);
    if (i < 0)
    {
        return false;
    }
    return (a.data[i] < b.data[i] and !a.flag);
}

bool operator>(big_integer const& a, big_integer const& b)
{
    return !operator<=(a, b);
}

bool operator<=(big_integer const& a, big_integer const& b)
{
    return operator<(a, b) || operator==(a, b);
}

bool operator>=(big_integer const& a, big_integer const& b)
{
    return !operator<(a, b);
}

//?

big_integer& big_integer::operator+=(big_integer const& b)
{
    
    big_integer _result(0);
    _result.data.pop_back();
    ll _balance = 0;
    bool _inv = false;
    unsigned int _length =
    (this->data.size() > b.data.size() ? (int) this->data.size() : (int) b.data.size());
    
    if (this->flag == b.flag)
    {
        _result.flag = b.flag;
    }
    else
    {
        _inv = true;
        if ((*this < -b and b.flag) or (-*this > b and b.flag == 0))
        {
            _result.flag = true;
        }
    }
    
    for (int i = 0; i < (int)_length; ++i)
    {
        ll aa = i < (ll)data.size() ? data[i] : 0;
        if (_result.flag ^ flag and _inv) aa = -aa;
        
        ll bb = i < (ll)b.data.size() ? b.data[i] : 0;
        if (_result.flag ^ b.flag and _inv) bb = -bb;
        
        _result.data.push_back((ui)((ll)mod + aa + bb + _balance) % mod);
        
        if (aa + bb + _balance < 0)
        {
            _balance = -1;
        }
        else if ((ui)((aa + bb + _balance) / mod))
        {
            _balance = 1;
        }
        else
        {
            _balance = 0;
        }
    }
    _result.data.push_back((ui)_balance);
    while (!_result.data[_result.data.size() - 1] and _result.data.size() != 1) _result.data.pop_back();
    *this = _result;
    return *this;
}


big_integer& big_integer::operator-=(big_integer const& b)
{
    return *this += -b;
}

big_integer operator+(big_integer a, big_integer const& b)
{
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b)
{
    return a -= b;
}

big_integer& big_integer::operator--()
{
    this->operator-=(1);
    return *this;
}

big_integer big_integer::operator--(int)
{
    big_integer t = *this;
    --(*this);
    return t;
}

big_integer& big_integer::operator++()
{
    this->operator+=(1);
    return *this;
}

big_integer big_integer::operator++(int)
{
    big_integer t = *this;
    ++(*this);
    return t;
}

big_integer big_integer::operator-() const
{
    big_integer r = *this;
    r.flag = (r.flag ? 0 : 1);
    return r;
}

big_integer& big_integer::operator*=(big_integer const& b)
{
    big_integer _result;
    _result.data.resize((int)data.size() + (int)b.data.size());
    _result.flag = flag != b.flag ? 1 : 0;
    for (int i = 0; i < (int)data.size(); ++i)
    {
        for (int j = 0; j < (int)b.data.size(); ++j)
        {
            ull mul = (ull)data[i] * (ull)b.data[j];
            
            ull mU = mul / mod;
            ull mD = mul % mod;
            int  k = 0;
            while (mD + mU > 0)
            {
                mU += ((ull)_result.data[i+j+k] + mD) / mod;
                _result.data[i+j+k] += (ui)mD;
                _result.data[i+j+k] %= mod;
                mD = mU;
                mU = 0;
                k++;
            }
        }
    }
    while (!_result.data[_result.data.size() - 1] and _result.data.size() != 1) _result.data.pop_back();
    *this = _result;
    return *this;
}


big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}

big_integer div2(big_integer a)
{
    ull b, c = 0;
    for (int i = (int)a.data.size() - 1; i >= 0; --i)
    {
        b = a.data[i] % 2;
        a.data[i] >>= 1;
        a.data[i] += (2*p) * c;
        c = b;
    }
    return a;
}

big_integer& big_integer::operator/=(big_integer const& rhs)
{
    if (*this < rhs)
    {
        *this = big_integer(0);
        return *this;
    }
    big_integer m(1);
    big_integer a(-1), b(*this + 1);
    while (b - a > big_integer(1))
    {
        m = div2(b + a + big_integer(1));
        big_integer bb = m * rhs;
        if (bb > *this) {
            b = m;
        }
        else
        {
            a = m;
        }
    }
    
    if (a * rhs <= *this) {
        *this = a;
    } else {
        *this = b;
    }
    while (!data[data.size() - 1] and data.size() != 1) data.pop_back();
    return *this;
}

big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
}


big_integer& big_integer::operator%=(big_integer const& rhs)
{

    big_integer res = *this - rhs * (*this / rhs);
    *this = res;
    return *this;
}

big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}

/*
 big_integer::big_integer(std::string const& str)
 {
 if (mpz_init_set_str(mpz, str.c_str(), 10))
 {
 mpz_clear(mpz);
 throw std::runtime_error("invalid string");
 }
 }
 

 
 big_integer& big_integer::operator%=(big_integer const& rhs)
 {
 mpz_tdiv_r(mpz, mpz, rhs.mpz);
 return *this;
 }
 
 big_integer& big_integer::operator&=(big_integer const& rhs)
 {
 mpz_and(mpz, mpz, rhs.mpz);
 return *this;
 }
 
 big_integer& big_integer::operator|=(big_integer const& rhs)
 {
 mpz_ior(mpz, mpz, rhs.mpz);
 return *this;
 }
 
 big_integer& big_integer::operator^=(big_integer const& rhs)
 {
 mpz_xor(mpz, mpz, rhs.mpz);
 return *this;
 }
 
 big_integer& big_integer::operator<<=(int rhs)
 {
 mpz_mul_2exp(mpz, mpz, rhs);
 return *this;
 }
 
 big_integer& big_integer::operator>>=(int rhs)
 {
 mpz_div_2exp(mpz, mpz, rhs);
 return *this;
 }
 
 big_integer big_integer::operator~() const
 {
 big_integer r;
 mpz_com(r.mpz, mpz);
 return r;
 }
 
 big_integer& big_integer::operator++()
 {
 mpz_add_ui(mpz, mpz, 1);
 return *this;
 }
 
 big_integer big_integer::operator++(int)
 {
 big_integer r = *this;
 ++*this;
 return r;
 }
 
 big_integer& big_integer::operator--()
 {
 mpz_sub_ui(mpz, mpz, 1);
 return *this;
 }
 
 big_integer big_integer::operator--(int)
 {
 big_integer r = *this;
 --*this;
 return r;
 }
 
 big_integer operator+(big_integer a, big_integer const& b)
 {
 return a += b;
 }
 
 big_integer operator-(big_integer a, big_integer const& b)
 {
 return a -= b;
 }
 

 

 
 big_integer operator%(big_integer a, big_integer const& b)
 {
 return a %= b;
 }
 
 big_integer operator&(big_integer a, big_integer const& b)
 {
 return a &= b;
 }
 
 big_integer operator|(big_integer a, big_integer const& b)
 {
 return a |= b;
 }
 
 big_integer operator^(big_integer a, big_integer const& b)
 {
 return a ^= b;
 }
 
 big_integer operator<<(big_integer a, int b)
 {
 return a <<= b;
 }
 
 big_integer operator>>(big_integer a, int b)
 {
 return a >>= b;
 }
 */
