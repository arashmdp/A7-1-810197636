#include "Network.h"
#include "Exceptions.h"

#include <map>
#include <iterator>
#include <iostream>

#define PUBLISHER "publisher"
#define TRUE "true"
#define FALSE "false"

using namespace std;

Network::Network(){
    filmCount = 1;
    userCount = 1;
};

bool checkPublisher(vector<string> info){
    for(int i=0; i<info.size() ; i++){
        if(info[i] == PUBLISHER){
            if(info[i+1] == TRUE){
                return true;
            } else {
                return false; 
            }
        }
    }
    return false; 
}

int search(vector<string> info){
    for(int i=0 ; i<info.size() ; i++){
        if(info[i] == "?"){
            return i+1;
        }
    }
}

map<string,string> createMapInfo(vector<string> info){
    map<string, string> mapInfo;
    int index = search(info);
    for(int i=index; i<info.size()-1 ; i+=2){
        if(info[i] != PUBLISHER){
            mapInfo.insert( pair<string,string> (info[i],info[i+1]) );
        }
    }
    return mapInfo;
}

bool Network::getStatus() const {
    return isPublisher;
}

bool Network::noSameName(string name){
    try {
        if(allUsersAndPublishers.size() != 0){
            for(int i=0 ; i<allUsersAndPublishers.size() ; i++){
            if(name == allUsersAndPublishers[i]->getUsername()){
                 throw badRequest();
                return false;
            }
            }
        }
        return true;
        }
    catch (std::exception &exp){
            cerr<<exp.what()<<endl;
    }
}

void Network::signup (vector<string> information){
    map<string,string> mapInfo = createMapInfo(information);
    if(noSameName(mapInfo.at("username"))){
        isPublisher = checkPublisher(information);
        if(isPublisher){
            User* newUser = new Publisher(mapInfo, userCount, true);
            allUsersAndPublishers.push_back(newUser);
            currentlyUser = newUser;
        } else {
            User* newUser = new User(mapInfo, userCount, false);
            allUsersAndPublishers.push_back(newUser);
            currentlyUser = newUser;
        }
        userCount++;
    }
}

void Network::login (vector<string> information){
    map<string,string> mapInfo = createMapInfo(information);
    for(int i=0 ; i<allUsersAndPublishers.size() ; i++){
        if(allUsersAndPublishers[i]->getUsername() == mapInfo.at("username")){
            if(allUsersAndPublishers[i]->getPassword() == mapInfo.at("password")){
                currentlyUser = allUsersAndPublishers[i];
                isPublisher = allUsersAndPublishers[i]->getStatus();
                return;
            } else {
                //sends error   
                //should return
            }
        }
    }
    //sends error
}

void Network::addFilm(vector<string> info){
    map<string,string> mapInfo = createMapInfo(info);
    Film* film = new Film(mapInfo,currentlyUser,filmCount);
    filmCount++;
    allFilms.push_back(film);
    currentlyUser->newFilm(film);
}

void Network::editFilm(vector<string> info){
    map<string,string> mapInfo = createMapInfo(info);
    currentlyUser->editFilm(mapInfo);
}

void Network::deleteFilm(int filmID){
    for(int i=0 ; i<allFilms.size() ; i++){
        if(filmID == allFilms[i]->getID()){
            if(currentlyUser == allFilms[i]->getUser()){
                currentlyUser->deleteFilm(filmID);
                allFilms.erase(allFilms.begin()+i);
            } else {
                // throw error "Permission Denied"
            }
            return;
        }
    }
    //throw error "Not Found"
}

void Network::getFollowers(){
    currentlyUser->getFollowers();
}

void Network::follow(int userID){
    for (int i=0 ; i<allUsersAndPublishers.size() ; i++){
        if(userID == allUsersAndPublishers[i]->getID()){
            allUsersAndPublishers[i]->addFollower(currentlyUser);
            currentlyUser->follow(allUsersAndPublishers[i]);
            break;
        }
    }
}

void Network::addMoney(int amount){
    currentlyUser->addMoney(amount);
}

void Network::showFilmDetail(int filmID){
    for(int i=0 ; i<allFilms.size() ; i++){
        if(filmID == allFilms[i]->getID()){
            currentlyUser->showFilmDetail(allFilms[i]);
        }
    }
}

void Network::buyFilm(int filmID){
    for(int i=0 ; i<allFilms.size() ; i++){
        if(filmID == allFilms[i]->getID()){
            currentlyUser->buyFilm(allFilms[i]);
        }
    }
}

void Network::getPublished(){
    currentlyUser->getPublished();
}
bool Network::search(vector<string>& filters, Film* film, int i){
    map<string,string> filmInfo = film->getMapInfo();
    if(filters.size() - i == 2){
        if(filmInfo.at(filters[i]) == filters[i+1]){
            return true;
        } else 
            return false;
    }
    if(search(filters, film, i+2) && filmInfo.at(filters[i]) == filters[i+1]){
        return true;
    } else {
        return false;
    }
}

void Network::searchFilm(vector<string> filters){
    vector<Film*> show;
    for(int i=0 ; i<allFilms.size() ; i++){
        if(search(filters, allFilms[i] , 3)){
            show.push_back(allFilms[i]);
        }
    }
}

void showSearch(std::vector<Film*> films){
  cout<<"#. Film Id | Film Name | Film Length | Film Price | ";
  cout<<"Rate | Production Year | Film Director";
    
}

void Network::getMoney(){
    currentlyUser->getMoney();
}

void Network::giveRate(vector<string> information){
    map<string,string> info = createMapInfo(information);
    int filmID = stoi(info.at("film_id"));
    int rate = stoi(info.at("score"));
    for(int i=0 ; i<allFilms.size() ; i++){
        if(allFilms[i]->getID() == filmID){
            currentlyUser->rateFilm(allFilms[i],rate);
        }
    }
}
