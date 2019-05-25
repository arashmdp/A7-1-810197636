#ifndef ADMIN_H
#define ADMIN_H

class Admin {
public:
    Admin();
    int getMoney();

    void addMoney(int money);
private:
    int accountMoney = 0;
}; 

#endif