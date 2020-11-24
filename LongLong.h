#ifndef LONGLONG_H
#define LONGLONG_H
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using uint = unsigned;
using namespace std;
class LongLong
{
    bool isNegative = false;
    string num;
    uint base = 10;
    LongLong() {}

    LongLong getZ(const LongLong& z);
    LongLong barretReduction(const LongLong& mod, LongLong z, LongLong base = 10);
    string dec2base(const string& baseDigits, unsigned int value);
    unsigned int base2dec(const string& baseDigits, const string& value);

public:
    LongLong(int number);
    LongLong(const string& s);

    std::string get_num() const {
        return num;
    }

    LongLong operator+(const LongLong& other) const;
    LongLong operator-(const LongLong& other) const;
    LongLong operator*(const LongLong& other) const;
    LongLong operator/(const LongLong& other) const;
    LongLong operator%(const LongLong& other) const;
    LongLong div2() const;
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
