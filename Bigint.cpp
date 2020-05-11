#include "Bigint.h"
using namespace std;

void Bigint::trim()
    {
    while (!v.empty() && !v.back())
        v.pop_back();
    if (v.empty())
        sign = 1;
    }

void Bigint::convertFromString(const string &s)
    {
    for (int i = 0; i < s.size(); i++)
        {
        if ((s[i] < '0' || s[i] > '9') && s[i] != '+' && s[i] != '-')
            throw std::invalid_argument("Bigint contains not a number or symbols: +, -");
        }
    sign = 1;
    v.clear();
    int vStart = 0;
    while (vStart < s.size() && (s[vStart] == '+' || s[vStart] == '-'))
        {
        if (s[vStart] == '-')
            sign = -sign;
        vStart++;
        }
    for (int i = s.size() - 1; i >= vStart; i -= baseDigits)
        {
        int a = 0;
        for (int j = max(vStart, i - baseDigits + 1); j <= i; j++)
            a = 10 * a + s[j] - '0';
        v.push_back(a);
        }
    trim();
    }

Bigint::Bigint()
    {
    sign = 1;
    }

Bigint::Bigint(const string &s)
    {
    convertFromString(s);
    }

#pragma region Assign
void Bigint::operator=(const string &s)
    {
    convertFromString(s);
    }

void Bigint::operator=(long long a)
    {
    sign = 1;
    if (a < 0)
        sign = -1, a = -a;
    for (; a > 0; a /= base)
        v.push_back(a % base);
    }

void Bigint::operator=(const Bigint &bigint)
    {
    sign = bigint.sign;
    v = bigint.v;
    }
#pragma endregion

#pragma region Operations
void Bigint::operator+=(const Bigint &summand)
    {
    *this = *this + summand;
    }

Bigint Bigint::operator+(const Bigint &summand) const
    {
    if (sign == summand.sign)
        {
        if (v.size() < summand.v.size())
            return summand + *this;
        Bigint result = *this;
        for (int i = 0, carry = 0; i < summand.v.size() || carry; i++)
            {
            if (i == result.v.size())
                result.v.push_back(0);
            result.v[i] += carry + (i < summand.v.size() ? summand.v[i] : 0);
            carry = result.v[i] >= base;
            if (carry)
                result.v[i] -= base;
            }
        return result;
        }
    return *this - (-summand);
    }

void Bigint::operator-=(const Bigint &subtract)
    {
    *this = *this - subtract;
    }

Bigint Bigint::operator-(const Bigint &subtract) const
    {
    if (sign == subtract.sign)
        {
        if (abs() < subtract.abs())
            return -(subtract - *this);
        Bigint result = *this;
        for (int i = 0, carry = 0; i < subtract.v.size() || carry; i++)
            {
            result.v[i] -= carry + (i < subtract.v.size() ? subtract.v[i] : 0);
            carry = result.v[i] < 0;
            if (carry)
                result.v[i] += base;
            }
        result.trim();
        return result;
        }
    return *this + (-subtract);
    }

Bigint Bigint::operator++()
    {
    *this += (Bigint)"1";
    return *this;
    }

Bigint Bigint::operator--()
    {
    *this -= (Bigint)"1";
    return *this;
    }

void Bigint::operator*=(int m)
    {
    if (m < 0)
        sign = -sign, m = -m;
    for (int i = 0, carry = 0; i < v.size() || carry; i++)
        {
        if (i == v.size())
            v.push_back(0);
        long long curr = carry + (long long)v[i] * (long long)m;
        carry = curr / base;
        v[i] = curr % base;
        }
    trim();
    }

Bigint Bigint::operator*(int m) const
    {
    Bigint result = *this;
    result *= m;
    return result;
    }

void Bigint::operator*=(const Bigint &m)
    {
    *this = *this * m;
    }

Bigint Bigint::operator*(const Bigint &m) const
    {
    Bigint result;
    for (int i = m.v.size() - 1; i >= 0; i--)
        {
        result *= base;
        result += *this * m.v[i];
        }
    result.sign = m.sign > 0 ? sign : -sign;
    return result;
    }

void Bigint::operator/=(int d)
    {
    if (d == 0)
        throw std::invalid_argument("Division by zero");

    if (d < 0)
        sign = -sign, d = -d;
    for (int i = v.size() - 1, rem = 0; i >= 0; i--)
        {
        long long curr = rem * (long long)base + v[i];
        v[i] = curr / d;
        rem = curr % d;
        }
    trim();
    }

Bigint Bigint::operator/(int d) const
    {
    Bigint result = *this;
    result /= d;
    return result;
    }

void Bigint::operator/=(const Bigint &d)
    {
    *this = *this / d;
    }

Bigint Bigint::operator/(const Bigint &d) const
    {
    if (d == (Bigint)"0")
        throw std::invalid_argument("Division by zero");
    
    Bigint remainder = abs();
    Bigint divider = d.abs();
    Bigint result;
    for (; remainder >= divider; ++result)
        remainder -= divider;
    result.sign = sign * d.sign;
    if (result.sign < 0 && remainder != (Bigint)"0")
        --result;
    return result;
    }

Bigint Bigint::operator%(const Bigint &d) const
    {
    if (d == (Bigint)"0")
        throw std::invalid_argument("Division by zero");

    Bigint remainder = abs();
    Bigint divider = d.abs();
    while (remainder >= divider)
        remainder -= divider;
    if (sign * d.sign < 0 && remainder != (Bigint)"0")
        remainder -= divider;
    return remainder;
    }
#pragma endregion

#pragma region Compare
bool Bigint::operator<(const Bigint &right) const
    {
    if (sign != right.sign)
        return sign < right.sign;
    if (v.size() != right.v.size())
        return v.size() * sign < right.v.size() * sign;
    for (int i = v.size() - 1; i >= 0; i--)
        if (v[i] != right.v[i])
            return v[i] * sign < right.v[i] * sign;
    return false;
    }

bool Bigint::operator>(const Bigint &right) const
    {
    return right < *this;
    }

bool Bigint::operator>=(const Bigint &right) const
    {
    return !(*this < right);
    }

bool Bigint::operator<=(const Bigint &right) const
    {
    return !(right < *this);
    }

bool Bigint::operator==(const Bigint &right) const
    {
    return !(right < *this) && !(*this < right);
    }

bool Bigint::operator!=(const Bigint &right) const
    {
    return right < *this || *this < right;
    }
#pragma endregion

#pragma region Stream
ostream& operator<<(ostream &stream, const Bigint &bigint)
    {
    if (bigint.sign == -1)
        stream << '-';
    stream << (bigint.v.empty() ? 0 : bigint.v.back());
    for (int i = bigint.v.size() - 2; i >= 0; i--)
        stream << setw(Bigint::baseDigits) << setfill('0') << bigint.v[i];
    return stream;
    }

istream& operator>>(istream &stream, Bigint &bigint)
    {
    string s;
    stream >> s;
    bigint.convertFromString(s);
    return stream;
    }
#pragma endregion

Bigint Bigint::operator-() const
    {
    Bigint result = *this;
    result.sign = -sign;
    return result;
    }

Bigint Bigint::abs() const
    {
    Bigint result = *this;
    result.sign = 1;
    return result;
    }