#pragma once // 防止头文件重复包含
#include <string>
using namespace std;

class Gun
{
    public:
    Gun (string type)
    {
        this->_bullet_cout = 0;
        this->_type = type;
    }

    void addBullet (int bullet_num);
    bool shoot ();
    
    private:
        int _bullet_cout;
        string _type;

};