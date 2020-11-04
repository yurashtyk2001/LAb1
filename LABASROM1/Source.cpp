#include "Header.h"

#include <algorithm>
LongLong LongLong::abs() const {
    LongLong x = *this;
    x.isNegative = false;
    return x;
}

LongLong LongLong::neg() const {
    LongLong res = *this;
    res.isNegative = true;
    return res;
}

void LongLong::flipSign() { this->isNegative = !this->isNegative; }

int LongLong::toInt() const {
    auto n = std::stoi(num);
    if (isNegative) {
        n *= 1;
    }
    return n;
}

std::string LongLong::toHex() const {
    std::string digits = "0123456789ABCDEF";
    long length = num.length();
    std::string result = "";
    std::vector<long> nibbles;
    for (long i = 0; i < length; i++) {
        char d = num[i];
        nibbles.push_back((d >= '0' && d <= '9')
            ? d - '0'
            : (d >= 'a' && d <= 'f')
            ? d - 'a' + 10
            : (d >= 'A' && d <= 'F') ? d - 'A' + 10 : -1);
    }

    long newlen = 0;
    do {
        long value = 0;
        newlen = 0;
        for (long i = 0; i < length; i++) {
            value = (value * 10) + nibbles[i];
            if (value >= 16) {
                nibbles[newlen++] = value / 16;
                value %= 16;
            }
            else if (newlen > 0) {
                nibbles[newlen++] = 0;
            };
        };
        length = newlen;
        result = digits[value] + result;
    } while (newlen != 0);
    result.insert(0, "0x");

    return result;
}

std::string LongLong::toBinary() const {
    LongLong res = *this;
    auto oddsToOne = [](const std::string& s) {
        if (s.back() == '1' || s.back() == '3' || s.back() == '5' ||
            s.back() == '7' || s.back() == '9')
            return 1;
        return 0;
    };

    auto divByTwo = [&oddsToOne](const std::string& s) {
        std::string new_s{ "" };
        int add = 0;

        for (auto ch : s) {
            auto new_dgt = ((int)(ch)-(int)('0')) / 2 + add;
            new_s += std::to_string(new_dgt);
            add = oddsToOne(std::string{ ch }) * 5;
        }

        if (new_s != "0" && new_s.front() == '0') new_s.erase(0, 1);

        return new_s;
    };
    std::string stack;
    if (res.num == "0")
        stack = "0";
    else {
        stack = "";
        while (res.num != "0") {
            stack = std::to_string(oddsToOne(res.num)) + stack;
            res.num = divByTwo(res.num);
        }
    }

    stack.insert(0, "0b");
    return stack;
}

LongLong LongLong::add_mod(const LongLong& n1, const LongLong& mod) {
    LongLong sum = n1 + *this;

    return sum.barretReduction(mod, getZ(mod));
}

LongLong LongLong::red_mod(const LongLong& n1, const LongLong& mod) {
    LongLong red = n1 - *this;

    return red.barretReduction(mod, getZ(mod));
}

LongLong LongLong::mul_mod(const LongLong& n1, const LongLong& mod) {
    LongLong mul = n1 * (*this);
    return mul.barretReduction(mod, getZ(mod), 10);
}

LongLong LongLong::pow2_mod(const LongLong& mod) { return pow_mod(2, mod); }

LongLong LongLong::pow_mod(const LongLong& p, const LongLong& mod) {
    LongLong k = mod.num.length();
    LongLong base(10);
    LongLong z = (base.pow(LongLong(2) * (k))) / mod;

    LongLong b = *this;

    auto binaryP = p.toBinary();
    LongLong res(1);
    for (int i = binaryP.size() - 1; i > 1; --i) {
        if (binaryP[i] == '1') {
            res = (res * b).barretReduction(mod, z, 10);
        }
        b = (b * b).barretReduction(mod, z, 10);
    }
    return res.barretReduction(mod, z, 10);
}

LongLong gcd(const LongLong& n1, const LongLong& n2) {
    if (n1 % n2 == LongLong(0)) {
        return n2;
    }
    if (n2 % n1 == LongLong(0)) {
        return n1;
    }
    if (n1 > n2) {
        return gcd(n1 % n2, n2);
    }
    return gcd(n1, n2 % n1);
}

bool LongLong::operator==(const LongLong& other) const {
    if (*this > other || *this < other) {
        return false;
    }
    return true;
}

bool LongLong::operator>(const LongLong& other) const { return other < *this; }

bool LongLong::operator>=(const LongLong& other) const {
    return !(*this < other);
}

bool LongLong::operator<=(const LongLong& other) const {
    return !(*this > other);
}

LongLong LongLong::getZ(const LongLong& mod) {
    LongLong k = mod.num.length();
    LongLong base = this->base;
    LongLong z = base.pow(LongLong(2) * k) / mod;
    return z;
}

LongLong LongLong::barretReduction(const LongLong& mod, LongLong z,
    LongLong base) {
    LongLong r(0);

    if (LongLong(2) * mod > this->abs() && base > 2) {
        return *this > LongLong(0) ? *this % mod : *this % mod + mod;
    }
    else {
        LongLong k = mod.num.length();
        LongLong q = (this->abs() / base.pow(k - LongLong(1)) * z) /
            base.pow(k + LongLong(1));
        LongLong r1 = this->abs() % base.pow(k + LongLong(1));
        LongLong r2 = (q * mod) % base.pow(k + LongLong(1));
        if (r1 >= r2) {
            r = r1 - r2;
        }
        else {
            r = base.pow(k + LongLong(1)) + r1 - r2;
        }

        while (r >= mod) {
            r = r - mod;
        }
    }
    return *this == LongLong(0) ? mod - r : r;
}

LongLong::LongLong(int number) {
    if (number < 0) {
        isNegative = true;
    }
    num = std::to_string(std::abs(number));
}

LongLong::LongLong(const std::string& s) {
    LongLong tmp(0);
    if (s.substr(0, 2) == "0x") {
        int base = 1;
        this->base = 8;

        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] >= '0' && s[i] <= '9') {
                tmp = tmp + LongLong((s[i] - 48) * base);
                base = base * 16;
            }
            else if (s[i] >= 'A' && s[i] <= 'F') {
                tmp = tmp + LongLong((s[i] - 55) * base);
                base = base * 16;
            }
        }
        *this = tmp;
    }
    else if (s.substr(0, 2) == "0b") {
        this->base = 2;
        int base = 1;
        auto t = s.substr(2, s.size());

        while (t.size()) {
            int last_digit = static_cast<int>(*(std::prev(t.end())) - '0');

            t = t.substr(0, t.size() - 1);
            tmp = tmp + LongLong(last_digit) * LongLong(base);

            base = base * 2;
        }

        *this = tmp;
    }
    else {
        if (s[0] == '-') {
            isNegative = true;
            num = s.substr(1, s.size());
        }
        else {
            num = s;
        }
    }

    //  this->num = s;
}

bool LongLong::operator<(const LongLong& other) const {
    if (this->isNegative == false && other.isNegative == true) return false;

    if (this->isNegative == true && other.isNegative == false) return true;

    if (this->isNegative == false && other.isNegative == false) {
        if (this->num.size() < other.num.size()) return true;
        if (this->num.size() > other.num.size()) return false;

        for (uint i = 0; i < this->num.size(); ++i) {
            if (this->num[i] < other.num[i]) {
                return true;
            }
            else if (this->num[i] > other.num[i]) {
                return false;
            }
        }
    }

    if (this->isNegative == true && other.isNegative == true) {
        if (this->num.size() > other.num.size()) return true;
        if (this->num.size() < other.num.size()) return false;

        for (uint i = 0; i < this->num.size(); ++i) {
            if (this->num[i] > other.num[i]) {
                return true;
            }
            else if (this->num[i] < other.num[i]) {
                return false;
            }
        }
    }

    return false;
}

std::ostream& operator<<(std::ostream& out, const LongLong& n) {
    if (n.isNegative) {
        out << '-';
    }
    for (auto i : n.num) {
        std::cout << i;
    }

    return out;
}

LongLong LongLong::operator+(const LongLong& other) const {
    LongLong res;
    LongLong a = *this;
    LongLong b = other;

    if (a.abs() < b.abs()) {
        std::swap(a, b);
    }

    std::reverse(a.num.begin(), a.num.end());
    std::reverse(b.num.begin(), b.num.end());

    while (a.num.size() > b.num.size()) {
        b.num.push_back('0');
    }

    if (a.isNegative == b.isNegative) {
        res.isNegative = b.isNegative;

        char carry = 0;
        for (uint i = 0; i < b.num.size(); ++i) {
            int x = static_cast<int>(a.num[i] - '0') +
                static_cast<int>(b.num[i] - '0') + carry;
            carry = x / 10;
            x = x % 10;
            res.num.push_back(static_cast<char>(x + '0'));
        }

        if (carry) {
            res.num.push_back(static_cast<int>(carry + '0'));
        }

    }
    else {
        res.isNegative =
            (this->abs() < other.abs()) ? other.isNegative : this->isNegative;

        int carry = 0;
        for (uint i = 0; i < b.num.size(); ++i) {
            int x = static_cast<int>(a.num[i]) - '0';
            int y = static_cast<int>(b.num[i]) - '0';
            int p1 = 0;
            if (x < (y + carry)) {
                x += 10;
                p1 = 1;
            }

            int tmp = x - y - carry;
            res.num.push_back(static_cast<char>((tmp + '0')));
            carry = p1;
        }
    }

    while (res.num.size() > 1 && *(res.num.end() - 1) == '0') {
        res.num.pop_back();
    }
    std::reverse(res.num.begin(), res.num.end());

    return res;
}

LongLong LongLong::operator-(const LongLong& other) const {
    LongLong a = *this;
    LongLong b = other;

    //    b.neg();
    if (b.isNegative) {
        b.flipSign();
    }
    else {
        b = b.neg();
    }

    return a + b;
}

LongLong LongLong::operator*(const LongLong& other) const {
    LongLong a = *this;
    LongLong b = other;
    LongLong c;

    bool sign = false;
    if (a.isNegative != b.isNegative) {
        sign = true;
    }

    LongLong zero(0);
    LongLong one(1);

    a = a.abs();
    b = b.abs();

    while (b > zero) {
        c = c + a;
        b = b - one;
    }
    c.isNegative = sign;

    return c;
}

LongLong LongLong::pow(LongLong p) {
    LongLong a = *this;
    LongLong c(1);
    LongLong zero(0);
    LongLong one(1);

    bool sign;
    if (p == zero) {
        return one;
    }

    if (p < zero) {
        return zero;
    }

    if (a % LongLong(2) == one) {
        sign = a.isNegative;
    }
    else {
        sign = false;
    }

    a = a.abs();

    while (p > zero) {
        c = c * a;
        p = p - one;
    }
    c.isNegative = sign;

    return c;
}

LongLong LongLong::pow2() { return this->pow(LongLong(2)); }

LongLong LongLong::operator/(const LongLong& other) const {
    LongLong a = *this;
    LongLong b = other;

    bool sign = false;
    if (a.isNegative != b.isNegative) {
        sign = true;
    }

    LongLong zero(0);
    LongLong one(1);

    a = a.abs();
    b = b.abs();

    if (a < b) {
        return zero;
    }

    LongLong c(0);
    while (a >= b) {
        a = a - b;
        c = c + one;
    }

    c.isNegative = sign;
    return c;
}

LongLong LongLong::operator%(const LongLong& other) const {
    LongLong a = *this;
    LongLong b = other;

    bool sign = false;
    if (a.isNegative != b.isNegative) {
        sign = true;
    }
    LongLong zero(0);
    LongLong one(1);

    a = a.abs();
    b = b.abs();
    if (a < b) {
        return a;
    }

    while (a >= b) {
        a = a - b;
    }

    a.isNegative = sign;
    return a;
}

LongLong::~LongLong() {}

LongLong lcm(const LongLong& n1, const LongLong& n2) {
    return n1 * n2 / gcd(n1, n2);
}
