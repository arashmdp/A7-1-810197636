#include "Admin.h"

Admin::Admin(){}

void Admin::addMoney(int money){
    accountMoney+=money;
}

int Admin::getMoney(){
    return accountMoney;
}