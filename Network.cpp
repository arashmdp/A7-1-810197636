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

int questionMarkPlace(vector<string> info){
    for(int i=0 ; i<info.size() ; i++){
        if(info[i] == "?"){
            return i+1;
        }
    }
}

Film* Network::searchFilmByID(int filmID){
    for (int i=0 ; i<allFilms.size() ; i++){
        if(allFilms[i]->getID() == filmID){
            return allFilms[i];
        }
    }
}

map<string,string> createMapInfo(vector<string> info){
    map<string, string> mapInfo;
    int index = questionMarkPlace(info);
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
            currentUser = newUser;
        } else {
            User* newUser = new User(mapInfo, userCount, false);
            allUsersAndPublishers.push_back(newUser);
            currentUser = newUser;
        }
        userCount++;
    }
}

void Network::login (vector<string> information){
    try{
        map<string,string> mapInfo = createMapInfo(information);
        for(int i=0 ; i<allUsersAndPublishers.size() ; i++){
            if(allUsersAndPublishers[i]->getUsername() == mapInfo.at("username")){
                if(allUsersAndPublishers[i]->getPassword() == mapInfo.at("password")){
                    currentUser = allUsersAndPublishers[i];
                    isPublisher = allUsersAndPublishers[i]->getStatus();
                    return;
                } else {
                    throw badRequest();
                }
            }
        }
        throw badRequest();
    } catch(std::exception &exp) {
        cerr<<exp.what()<<endl;
    }
}

void Network::addFilm(vector<string> info){
    map<string,string> mapInfo = createMapInfo(info);
    Film* film = new Film(mapInfo,currentUser,filmCount);
    filmCount++;
    allFilms.push_back(film);
    currentUser->newFilm(film);
}

void Network::editFilm(vector<string> info){
    map<string,string> mapInfo = createMapInfo(info);
    currentUser->editFilm(mapInfo);
}

void Network::deleteFilm(int filmID){
    try{
        for(int i=0 ; i<allFilms.size() ; i++){
            if(filmID == allFilms[i]->getID()){
                if(currentUser == allFilms[i]->getUser()){
                    currentUser->deleteFilm(filmID);
                    allFilms.erase(allFilms.begin()+i);
                } else {
                    throw permissionDenied();
                }
                return;
            }
        }   
        throw notFound();
    } catch(std::exception &exp){
        cerr<<exp.what()<<endl;
    }
}

void Network::getFollowers(){
    currentUser->getFollowers();
}

void Network::follow(int userID){
    for (int i=0 ; i<allUsersAndPublishers.size() ; i++){
        if(userID == allUsersAndPublishers[i]->getID()){
            allUsersAndPublishers[i]->addFollower(currentUser);
            currentUser->follow(allUsersAndPublishers[i]);
            break;
        }
    }
}

void Network::addMoney(int amount){
    currentUser->addMoney(amount);
}

void Network::showFilmDetail(int filmID){
    for(int i=0 ; i<allFilms.size() ; i++){
        if(filmID == allFilms[i]->getID()){
            currentUser->showFilmDetail(allFilms[i]);
        }
    }
}

void Network::buyFilm(int filmID){
    for(int i=0 ; i<allFilms.size() ; i++){
        if(filmID == allFilms[i]->getID()){
            currentUser->buyFilm(allFilms[i]);
        }
    }
}

void Network::getPublished(){
    currentUser->getPublished();
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

void Network::showSearch(std::vector<Film*> films){
  cout<<"#. Film Id | Film Name | Film Length | Film Price | ";
  cout<<"Rate | Production Year | Film Director";
    
}

void Network::getMoney(){
    currentUser->getMoney();
}

void Network::giveRate(vector<string> information){
    map<string,string> info = createMapInfo(information);
    int filmID = stoi(info.at("film_id"));
    int rate = stoi(info.at("score"));
    Film* theFilm = searchFilmByID(filmID);
    currentUser->rateFilm(theFilm,rate);
}

void Network::addComment(vector<string> information){
    map<string,string> info = createMapInfo(information);
    int filmID = stoi(info.at("film_id"));
    string content = info.at("content");
    Film* film = searchFilmByID(filmID);
    commentID++;
    Comment* comment = new Comment(content,commentID);
    film->setComment(comment);
}
