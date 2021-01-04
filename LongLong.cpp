#include "LongLong.h"
#include <algorithm>
#include <cmath>

LongLong LongLong::abs() const
{
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
        n *= -1;
    }
    return n;
}

string LongLong::toHex() const {
    string digits = "0123456789ABCDEF";
    long length = num.length();
    string result = "";
    vector<long> nibbles;
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

string LongLong::toBinary() const {
    LongLong res = *this;
    auto oddsToOne = [](const string& s) {
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
            add = oddsToOne(string{ ch }) * 5;
        }

        if (new_s != "0" && new_s.front() == '0') new_s.erase(0, 1);

        return new_s;
    };
    string stack;
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


LongLong gcd(LongLong n1, LongLong n2) {
    if (n2 == LongLong(0)) {
        return n1;
    }
    else {
        return gcd(n2, (n1 % n2));
    }
}


bool LongLong::operator==(const LongLong& other) const
{
    if (*this > other || *this < other)
    {
        return false;
    }
    return true;
}

bool LongLong::operator>(const LongLong& other) const { return other < *this; }

bool LongLong::operator>=(const LongLong& other) const
{
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

LongLong LongLong::barretReduction(const LongLong& mod, LongLong z,LongLong base)
{
    LongLong r(0);

    if (LongLong(2) * mod > this->abs() && base > 2)
    {
        return *this > LongLong(0) ? *this % mod : *this % mod + mod;
    }
    else {
        LongLong k = mod.num.length();
        LongLong q = (this->abs() / base.pow(k - LongLong(1)) * z) / base.pow(k + LongLong(1));
        LongLong r1 = this->abs() % base.pow(k + LongLong(1));
        LongLong r2 = (q * mod) % base.pow(k + LongLong(1));
        if (r1 >= r2) 
        {
            r = r1 - r2;
        }
        else {
            r = base.pow(k + LongLong(1)) + r1 - r2;
        }

        while (r >= mod)
        {
            r = r - mod;
        }
    }
    return *this == LongLong(0) ? mod - r : r;
}

string LongLong::dec2base(const string& baseDigits, unsigned int value)
{
    unsigned int numberBase = (unsigned int)baseDigits.length();
    string result;
    do {
        result.push_back(baseDigits[value % numberBase]);
        value /= numberBase;
    } while (value > 0);

    reverse(result.begin(), result.end());
    return result;
}

unsigned int LongLong::base2dec(const string& baseDigits, const string& value)
{
    unsigned int numberBase = (unsigned int)baseDigits.length();
    unsigned int result = 0;
    for (size_t i = 0; i < value.length(); ++i)
    {
        result *= numberBase;
        int c = baseDigits.find(value[i]);
        if (c == std::string::npos) throw std::runtime_error("Invalid character");

        result += (unsigned int)c;
    }

    return result;
}

LongLong::LongLong(int number) {
    if (number < 0) {
        isNegative = true;
    }
    num = std::to_string(std::abs(number));
}

LongLong::LongLong(const std::string& str)
{
    LongLong tmp(0);

    auto s = str;

    if (s.substr(0, 2) == "0x") {
        tmp.num.clear();
        this->base = 16;
        s.erase(0, 2);

        std::string targetBaseSet = "0123456789";
        std::string sourceBaseSet = "0123456789ABCDEF";

        auto targerBaseLength = targetBaseSet.length();
        std::string result;

        auto div = [this](const std::string& baseDigits, std::string& x,
            unsigned int y) {
                std::string quotient;

                size_t lenght = x.length();
                for (size_t i = 0; i < lenght; ++i) {
                    size_t j = i + 1 + x.length() - lenght;
                    if (x.length() < j) break;

                    unsigned int value = base2dec(baseDigits, x.substr(0, j));

                    quotient.push_back(baseDigits[value / y]);
                    x = dec2base(baseDigits, value % y) + x.substr(j);
                }

                unsigned int remainder = base2dec(baseDigits, x);

                size_t n = quotient.find_first_not_of(baseDigits[0]);
                if (n != std::string::npos) {
                    x = quotient.substr(n);
                }
                else {
                    x.clear();
                }

                return remainder;
        };

        do {
            unsigned int remainder = div(sourceBaseSet, s, targerBaseLength);
            tmp.num.push_back(targetBaseSet[remainder]);
        } while (!s.empty() && !(s.length() == 1 && s[0] == sourceBaseSet[0]));

        std::reverse(tmp.num.begin(), tmp.num.end());

        this->num = tmp.num;
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

LongLong LongLong::operator+(const LongLong& other) const
{
    LongLong res;
    LongLong a = *this;
    LongLong b = other;

    if (a.abs() < b.abs()) {
        std::swap(a, b);
    }

    reverse(a.num.begin(), a.num.end());
    reverse(b.num.begin(), b.num.end());

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

    while (res.num.size() > 1 && *(res.num.end() - 1) == '0')
    {
        res.num.pop_back();
    }
    reverse(res.num.begin(), res.num.end());

    return res;
}

LongLong LongLong::operator-(const LongLong& other) const
{
    LongLong a = *this;
    LongLong b = other;

    //    b.neg();
    if (b.isNegative)
    {
        b.flipSign();
    }
    else {
        b = b.neg();
    }

    return a + b;
}

LongLong LongLong::operator*(const LongLong& other) const
{
    LongLong a = *this;
    LongLong b = other;
    LongLong c;

    bool sign = false;
    if (a.isNegative != b.isNegative)
    {
        sign = true;
    }

    a = a.abs();
    b = b.abs();
    size_t size_a = a.num.size();
    size_t size_b = b.num.size();
    size_t length = size_a + size_b + 1;

    vector<int> v_a;
    vector<int> v_b;
    vector<int> v_c(length, 0);

    for (int digit : a.num)
        v_a.insert(v_a.begin(), digit - '0');

    for (int digit : b.num)
        v_b.insert(v_b.begin(), digit - '0');

    for (size_t i = 0; i < size_a; i++)
        for (size_t j = 0; j < size_b; j++)
            v_c[i + j] += v_a[i] * v_b[j];

    for (size_t i = 0; i < length - 1; i++)
    {
        v_c[i + 1] += v_c[i] / 10;
        v_c[i] %= 10;
    }

    while (v_c[length - 1] == 0)
        length--;

    c.isNegative = sign;

    std::string temp = "";
    for (int i = length - 1; i >= 0; i--)
        temp += (v_c[i] + '0');
    c.num = temp;

    return c;
}

LongLong LongLong::pow(LongLong p)
{

    LongLong a = *this;
    LongLong c(1);
    LongLong zero(0);
    LongLong one(1);
    LongLong two(2);

    bool sign;

    if (p == zero)
    {
        return one;
    }

    if (p < zero)
    {
        return zero;
    }

    if ((p.num[p.num.size() - 1] - '0') % 2 == 1)
    {
        sign = a.isNegative;
    }
    else {
        sign = false;
    }

    a = a.abs();

    if ((p.num[p.num.size() - 1] - '0') % 2 == 1) {
        auto result = this->pow(p - one) * a;
        return result;
    }
    else {
        LongLong b = this->pow(p.div2());
        auto result = b * b;
        return result;
    }
}

LongLong LongLong::div2() const {
    const int current_base = 10;
    std::vector<int> repr;

    auto char_to_digit = [](char c) {
        return static_cast<int>(c - '0');
    };

    for (const auto& digit : this->num) {
        repr.push_back(char_to_digit(digit));
    }
    std::reverse(repr.begin(), repr.end());
    int carry = 0;

    for (int i = static_cast<int>(repr.size()) - 1; i >= 0; --i) {
        int cur = repr[i] + carry * current_base;
        repr[i] = static_cast<int>(cur / 2);
        carry = static_cast<int>(cur % 2);
    }
    while (repr.size() > 1 && repr.back() == 0) {
        repr.pop_back();
    }

    std::string str_repr = "";
    for (const auto& digit : repr) {
        str_repr += std::to_string(digit);
    }
    std::reverse(str_repr.begin(), str_repr.end());

    return LongLong(str_repr);
}

LongLong LongLong::pow2() { return this->pow(LongLong(2)); }

LongLong LongLong::operator/(const LongLong& other) const {
    LongLong a = *this;
    LongLong b = other;
    if (other == LongLong(1)) {
        return *this;
    }

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


    LongLong left_bound = LongLong(1), right_bound = a;
    while (left_bound < right_bound) {
        auto middle = (left_bound + right_bound).div2();
        if (middle * b <= a) {
            left_bound = middle + 1;
        }
        else {
            right_bound = middle;
        }
    }

    LongLong c = left_bound - 1;
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

    auto result = a / b;
    a = a - result * b;

    a.isNegative = sign;
    return a;
}

LongLong::~LongLong() {}


LongLong lcm(LongLong n1, LongLong n2)
{
    return n1 * n2 / gcd(n1, n2);
}
