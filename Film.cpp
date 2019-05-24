#include "Film.h"

using namespace std;

Film::Film(map <string,string> _info, User* _thePublisher, int _filmID){
            info = _info;
            thePublisher = _thePublisher;
            id = _filmID;
            aveRate = 0;
        }

void Film::edit(map<string,string> editMap){
    swap(info, editMap);
    info.insert(editMap.begin(), editMap.end());
}

int Film::getID() const {
    return id;
}

int Film::getRate() const {
    return aveRate;
}

User* Film::getUser() const{
    return thePublisher;
}

map<string,string> Film::getMapInfo() const{
    return info;
}

int Film::getPrice() const{
    return stoi(info.at("price"));
}

void Film::setRate(int _rate){
    int mid;
    rates.push_back(_rate);
    for(int i=0 ; i<rates.size() ; i++){
        mid += rates[i];
    }
    mid/=rates.size();
    aveRate = mid;
}

void Film::setComment(Comment* comment){
    comments.push_back(comment);
}