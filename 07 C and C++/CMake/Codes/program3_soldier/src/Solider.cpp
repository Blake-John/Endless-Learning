#include "Gun.h"
#include "Solider.h"
using namespace std;

Solider::Solider (string name)
{
    this->_name = name;
    this->_ptr_gun = nullptr; // 初始化为空指针
}

void Solider::addGun (Gun *ptr_gun)
{
    this->_ptr_gun = ptr_gun;
}

void Solider::addBulletToGun (int bullet_num)
{
    this->_ptr_gun->addBullet (bullet_num);
}

bool Solider::fire ()
{
    return (this->_ptr_gun->shoot ());
}

Solider::~Solider ()
{
    if (this->_ptr_gun == nullptr)
    {
        return;
    }
    else
    {
        delete this->_ptr_gun;
        this->_ptr_gun = nullptr;
    }
}