#include <iostream>
#include <random>
#include "LongLong.h"



int main() {
    LongLong n1(
        "149447688312848515258100433736237569226536104553607190385714200534665809680850193893154469046245315437213861571221904598002103944042544460864076638672456139498858521322800981173338456476678290683398437441053098102176912355036877066726513117830261910777017725496971994705120510022115094623833115317229509421019");

    LongLong n2(
        "41077207524471760561505389007664702164419173831209075152323809783771069542017713431957562039411596447990413079018865864401920197413810459722239238436640803044522290103733173716618617835438952917605528537529074643426815214656827633501732031853438134294104266177044483070110325599171617930049656394682510736871");
    LongLong mod("27116444766612544465217883254506908926923505304793807883685435181744506786223585664372377611605941645522748707567280220108971783927576372798087725031801531950178062036085167540648326725285253938711634728391804788087839526779826423288882935519018601470631365403330826612160941872633465809275880429520552684507");
    LongLong n3(
        "543447608312848515258100433736237569226536104553607190385714200534665809680850193893154469046245315437213861571221904598002103944042544460864076638672456139498858521322800981173338456476678290683398437441053098102176912355036877066726513117830261910777017725496971994705120510022115094623833115317229509421019");

    cout << "A=" << n1 << endl;
    cout << "B=" << n2 << endl;
    cout << "n3*(n1+n2)= "<<n3 * (n1 + n2) << endl;
   /* cout << "A+B" << " " << n1 + n2 << endl;
    cout << "A-B" << " " << n1 - n2 << endl;
    cout << "A*B" << " " << n1 * n2 << endl;
    cout << "A/B" << " " << n1 / n2 << endl;
    cout << "A%B" << " " << n1 % n2 << endl;
    cout << "A^2" << " " << n1.pow2() << endl;*/
   /* cout << n1 << "^" << n2 << "=" << " " << n1.pow(n2) << endl;*/

    /*cout << "( A+B )" << "mod=" << n1.add_mod(n2, mod) << endl;
    cout << "( A-B )" << "=" << "mod" << "=" << n1.red_mod(n2, mod) << endl;

    cout << "( A*B )" << "=" << "mod" << "=" << n1.mul_mod(n2, mod) << endl;*/
    /* cout << "( A^B )" << "=" << "mod" << "=" << n1.pow_mod(n2, mod) << endl;*/
   /* cout << "( A^2 )" << "=" << "mod" << "=" << n1.pow2_mod(mod) << endl;

    cout << "gcd:" << endl;
    cout << gcd(n1, n2) << endl;
    cout << "lcm:" << endl;
    cout  << lcm(n1, n2) << endl;

    cout << n1.toBinary() << endl;
    cout << n1.toHex() << endl;*/

    if (!((n1 + n2) * n3 == n3 * (n1 + n2) && n3 * (n1 + n2) == n1 * n3 + n2 * n3)) {
        cout << "(a+b)c != c(a+b) != ac + bc" << endl;
    }
    int n = 1000;
    LongLong extra = n1;
    for (int i = 0; i < n; i++) 
    {
        extra = extra + n1;
    }
    if (!(LongLong(1000) * n1 == extra))
    {
        cout << "1000a != a+a+a+...+a" << endl;
    }
    int k = n;
    int new_n = pow(3, k);
    int func = new_n - pow(3, k - 1);
    int func2 = 2 * pow(3, k - 1);
    LongLong extra2 = n1;
    LongLong extra3 = n1;
    for (int i = 1; i < func; i++) {
        extra2 = extra2 * n1;
    }
    for (int i = 1; i < func2; i++) {
        extra3 = extra3 * n1;
    }
    if (!(extra2 == extra3)) {
        cout << "a^(fi) != a^(2*3^(k-1))" << endl;
    }
    return 0;
}