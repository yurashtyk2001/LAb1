#ifndef LONGLONG_H
#define LONGLONG_H
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using uint = unsigned;
class LongLong {
    bool isNegative = false;
    std::string num;
    uint base = 10;
    LongLong() {}

public:
    LongLong getZ(const LongLong& z);
    LongLong barretReduction(const LongLong& mod, LongLong z, LongLong base = 10);
    LongLong(int number);
    LongLong(const std::string& s);

    LongLong operator+(const LongLong& other) const;
    LongLong operator-(const LongLong& other) const;
    LongLong operator*(const LongLong& other) const;
    LongLong operator/(const LongLong& other) const;
    LongLong operator%(const LongLong& other) const;
    LongLong pow(LongLong p);
    LongLong pow2();

    bool operator<(const LongLong& other) const;
    bool operator>(const LongLong& other) const;
    bool operator<=(const LongLong& other) const;
    bool operator>=(const LongLong& other) const;
    bool operator==(const LongLong& other) const;

    LongLong abs() const;
    LongLong neg() const;
    void flipSign();
    int toInt() const;
    std::string toHex() const;
    std::string toBinary() const;

    LongLong add_mod(const LongLong& n1, const LongLong& n2);
    LongLong red_mod(const LongLong& n1, const LongLong& n2);
    LongLong mul_mod(const LongLong& n1, const LongLong& n2);
    LongLong pow2_mod(const LongLong& n2);
    LongLong pow_mod(const LongLong& n1, const LongLong& n2);

    friend std::ostream& operator<<(std::ostream& out, const LongLong& x);
    ~LongLong();
};
LongLong gcd(const LongLong& n1, const LongLong& n2);
LongLong lcm(const LongLong& n1, const LongLong& n2);

#endif  // LONGLONG_H

