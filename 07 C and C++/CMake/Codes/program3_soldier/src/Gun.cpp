#include "Gun.h"
#include <iostream>
using namespace std;

void Gun::addBullet (int bullet_num)
{
    this->_bullet_cout += bullet_num;
}

bool Gun::shoot ()
{
    if (this->_bullet_cout <= 0)
    {
        cout << "There is no bullet!" << endl;
        return 1;
    }
    else
    {
        this->_bullet_cout -= 1;
        cout << "Shoot successfully" << endl;
        return 0;
    }
}