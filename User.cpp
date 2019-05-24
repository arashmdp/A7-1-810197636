#include "User.h"

#include <iostream>

using namespace std;

User::User(map<string,string> _info, int _id, bool _isPublisher){
    info = _info;
    id = _id;
    isPublisher = _isPublisher;
    moneyAmount = 0;
}

string User::getUsername() const {
    return info.at(USERNAME);
}

string User::getPassword() const {
    return info.at(PASSWORD);
}

string User::getEmail() const {
    return info.at(EMAIL);
}

int User::getID() const {
    return id;
}

bool User::getStatus() const {
    return isPublisher;
}

void User::follow(User* flwingPub) {
    following.push_back(flwingPub);
}

void User::addMoney(int amount){
        moneyAmount+=amount;
    }

void User::showFilmDetail(Film* film){
    map<string,string> info = film->getMapInfo();
    cout<<"Details of Film "<<info.at(NAME)<<endl;
    cout<<"Id = "<<film->getID()<<endl;
    cout<<"Director = "<<info.at(DIRECTOR)<<endl;
    cout<<"Length = "<<info.at(LENGTH)<<endl;
    cout<<"year = "<<info.at(YEAR)<<endl;
    cout<<"summary = "<<info.at(SUMMARY)<<endl;
    cout<<"rate = "<<film->getRate()<<endl;
    cout<<"price = "<<info.at(PRICE)<<endl<<endl;
    cout<<"Comments"<<endl;
}

void User::sendNotification(string content){
    notifications.push_back(content);
}

void User::buyFilm(Film* film){
    int price = film->getPrice();
    if(price>=moneyAmount){
        moneyAmount-=price;
        (film->getUser())->sendNotification("Your film is purchased!");
        purchasedFilms.push_back(film);
    }
}

void User::rateFilm(Film* film, int rate){
    film->setRate(rate);
}