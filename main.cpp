#include <iostream>
#include "LongLong.h"

//#define KEK

int main() {
    LongLong n1(
        "0x3A7EF2554E8940FA9B93B2A5E822CC7BB262F4A14159E4318CAE3ABF5AEB1022EC6D01DEFAB48B528868679D649B445A753684C13F6C3ADBAB059D635A2882090FC166EA9F0AAACD16A062149E4A0952F7FAAB14A0E9D3CB0BE9200DBD3B0342496421826919148E617AF1DB66978B1FCD28F8408506B79979CCBCC7F7E5FDE7");

    LongLong n2(
        "0x3A7EF2554E8940FA9B93B2A5E822CC7BB262F4A14159E4318CAE3ABF5AEB1022EC6D01DEFAB48B528868679D649B445A753684C13F6C3ADBAB059D635A2882090FC166EA9F0AAACD16A062149E4A0952F7FAAB14A0E9D3CB0BE9200DBD3B0342496421826919148E617AF1DB66978B1FCD28F8408506B79979CCBCC7F7E5FDE7");
    LongLong mod(10);



    cout << n1 << "+" << n2 << "=" << " " << n1 + n2 << endl;
    cout << n1 << "-" << n2 << "=" << " " << n1 - n2 << endl;
    cout << n1 << "*" << n2 << "=" << " " << n1 * n2 << endl;
    cout << n1 << "/" << n2 << "=" << " " << n1 / n2 << endl;
    cout << n1 << "%" << n2 << "=" << " " << n1 % n2 << endl;
    cout << n1 << "^2" << "=" << " " << n1.pow2() << endl;
    //    cout << n1 << "^" << n2 << "="<< " " << n1.pow(n2) <<endl;
    cout << "(" << n1 << "+" << n2 << ")" << "mod" << mod << "=" << n1.add_mod(n2, mod) << endl;
    cout << "(" << n1 << "-" << n2 << ")" << "mod" << mod << "=" << n1.red_mod(n2, mod) << endl;

    cout << "(" << n1 << "*" << n2 << ")" << "mod" << mod << "=" << n1.mul_mod(n2, mod) << endl;
    cout << "(" << n1 << "^" << n2 << ")" << "mod" << mod << "=" << n1.pow_mod(n2, mod) << endl;
    cout << "(" << n1 << "^2" << ")" << "mod" << mod << "=" << n1.pow2_mod(mod) << endl;

    cout << n1.toBinary() << endl;
    cout << n1.toHex() << endl;

    return 0;
}