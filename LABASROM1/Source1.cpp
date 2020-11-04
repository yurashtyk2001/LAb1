#include "Header.h"
#include <iostream>

int main() 
{
    LongLong n1(1234);
    LongLong n2(3);
    LongLong mod(10);

    std::cout << "(" << n1 << "+" << n2 << ")"
        << "mod" << mod << "=" << n1.add_mod(n2, mod) << std::endl;
    std::cout << "(" << n1 << "-" << n2 << ")"
        << "mod" << mod << "=" << n1.red_mod(n2, mod) << std::endl;
    std::cout << "(" << n1 << "*" << n2 << ")"
        << "mod" << mod << "=" << n1.mul_mod(n2, mod) << std::endl;
    std::cout << "(" << n1 << "^" << n2 << ")"
        << "mod" << mod << "=" << n1.pow_mod(n2, mod) << std::endl;
    std::cout << "(" << n1 << "^2"
        << ")"
        << "mod" << mod << "=" << n1.pow2_mod(mod) << std::endl;

    return 0;
}
