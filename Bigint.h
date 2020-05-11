/*
Author: Vismantas Stonkus, PS 4gr
*/
#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

class Bigint
    {
    private:
        const static int base = 1000000000;
        const static int baseDigits = 9;

        void trim();
        // possible exception: std::invalid_argument "Bigint contains not a number or symbols: +, -"
        void convertFromString(const string &s);

    public:
        int sign;
        vector<long> v;
        Bigint();
        Bigint(const string &s);

        #pragma region Assign
        void operator=(const string &s);
        void operator=(long long a);
        void operator=(const Bigint &bigint);
        #pragma endregion

        #pragma region Operations
        void operator+=(const Bigint &subtract);
        Bigint operator+(const Bigint &summand) const;
        void operator-=(const Bigint &subtract);
        Bigint operator-(const Bigint &subtract) const;
        Bigint operator++();
        Bigint operator--();
        void operator*=(int m);
        Bigint operator*(int m) const;
        void operator*=(const Bigint &m);
        Bigint operator*(const Bigint &m) const;
        // possible exception: std::invalid_argument "Division by zero"
        void operator/=(int d);
        // possible exception: std::invalid_argument "Division by zero"
        Bigint operator/(int d) const;
        // Note: slow when dividing by small numbers
        // possible exception: std::invalid_argument "Division by zero"
        void operator/=(const Bigint &d);
        // Note: slow when dividing by small numbers
        // possible exception: std::invalid_argument "Division by zero"
        Bigint operator/(const Bigint &d) const;
        // possible exception: std::invalid_argument "Division by zero"
        Bigint operator%(const Bigint &d) const;
        #pragma endregion

        #pragma region Compare
        bool operator<(const Bigint &right) const;
        bool operator>(const Bigint &right) const;
        bool operator>=(const Bigint &right) const;
        bool operator<=(const Bigint &right) const;
        bool operator==(const Bigint &right) const;
        bool operator!=(const Bigint &right) const;
        #pragma endregion

        #pragma region Stream
        friend ostream& operator<<(ostream &stream, const Bigint &bigint);
        friend istream& operator>>(istream &stream, Bigint &bigint);
        #pragma endregion

        Bigint operator-() const;
        Bigint abs() const;
    };