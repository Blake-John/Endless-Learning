#pragma once
#include <iostream>
#include <string>
#include "Gun.h"
using namespace std;

class Solider
{
    public:
        Solider (string name);
        ~Solider ();
        void addBulletToGun (int bullet_num);
        bool fire ();
        void addGun (Gun *_ptr_gun);

    private:
        string _name;
        Gun *_ptr_gun;
};