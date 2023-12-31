#include "Gun.h"
#include "Solider.h"
#include <iostream>

using namespace std;

void test ()
{
    int num;

    Solider xusanduo ("xusanduo");
    xusanduo.addGun (new Gun ("AK47")); // new方法为目标分配动态内存地址
    cin >> num;
    xusanduo.addBulletToGun (num);
    xusanduo.fire ();
}

int main ()
{
    test ();
    return 0;
}