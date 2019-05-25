#include "Publisher.h"

#include <iostream>

using namespace std;

Publisher::Publisher(map<string,string> _info, int _id, bool _isPublisher)
    :User(_info, _id, _isPublisher){}
        
void Publisher::newFilm(Film* film){
    allFilms.push_back(film);
}

void Publisher::editFilm(map<string,string> editInfo){
    int film_id = stoi(editInfo.at("film_id"));
    for (int i=0 ; i<allFilms.size() ; i++){
        if(film_id == allFilms[i]->getID()){
            allFilms[i]->edit(editInfo);
        }
    }
}

void Publisher::deleteFilm(int filmID){
    for(int i=0 ; i<allFilms.size() ; i++){
        if(filmID == allFilms[i]->getID()){
            allFilms.erase(allFilms.begin() + i);
            return;
        }
    }
}

void Publisher::getFollowers(){
    cout<<"List Of Followers"<<endl;
    cout<<"#. User Id | User Username | User Email"<<endl;
    for(int i=0 ; i<followers.size() ; i++){
        cout<<i+1<<". ";
        cout<<followers[i]->getID()<<" | ";
        cout<<followers[i]->getUsername()<<" | ";
        cout<<followers[i]->getEmail()<<endl;
    }
}

void Publisher::addFollower(User* follower){
    followers.push_back(follower);
}

void Publisher::getPublished(){
    cout<<"#. Film Id | Film Name | Film Length | Film Price";
    cout<<" | Rate | Production Year | Film Director"<<endl;
    for (int i=0 ; i<allFilms.size() ; i++){
        map<string,string> info = allFilms[i]->getMapInfo();
        cout<<i+1<<". ";
        cout<<allFilms[i]->getID()<<" | ";
        cout<<info.at(NAME)<<" | ";
        cout<<info.at(LENGTH)<<" | ";
        cout<<info.at(PRICE)<<" | ";
        cout<<allFilms[i]->getRate()<<" | ";
        cout<<info.at(YEAR)<<" | ";
        cout<<info.at(DIRECTOR)<<endl;

    }

}

int Publisher::calculateMoney(Film* film){
    int rate = film->getRate();
    int price = film->getPrice();

    if(rate<5){
        return (0.8 * price);
    } else if (5<=rate<8){
        return (0.9 * price);
    } else {
        return (0.95 * price);
    }
}

void Publisher::getMoney(){

}

void Publisher::buyFilm(Admin* admin, Film* film){
    int price = film->getPrice();
    int myPartMoney = calculateMoney(film);
    int toAccountMoney = price - myPartMoney;
    moneyFromFilms = myPartMoney;
    admin->addMoney(toAccountMoney);
    publisherNotifications.push_back("your film is bought");
}