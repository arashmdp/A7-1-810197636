#include "Network.h"
#include "Exceptions.h"

#include <map>
#include <iterator>
#include <iostream>
#include <algorithm>

#define PUBLISHER "publisher"
#define TRUE "true"
#define FALSE "false"

using namespace std;

Network::Network(){
    filmCount = 1;
    userCount = 1;
    admin = new Admin();
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
        map<string,string> mapInfo = createMapInfo(information);
        for(int i=0 ; i<allUsersAndPublishers.size() ; i++){
            if(allUsersAndPublishers[i]->getUsername() == mapInfo.at("username")){
                if(allUsersAndPublishers[i]->getPassword() == mapInfo.at("password")){
                    currentUser = allUsersAndPublishers[i];
                    isPublisher = allUsersAndPublishers[i]->getStatus();
                    return;
                } else {
                    throw badRequest();
                    return;
                }
            }
        }
        throw badRequest();
}

void Network::logout(){
    if(currentUser != 0){
        currentUser = 0;
    } else {
        throw badRequest();
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

void Network::buyFilm(int filmID){
    Film* film = searchFilmByID(filmID);
    film->getUser()->buyFilm(admin,film);
    currentUser->buyFilm(admin,film);
    film->buy();
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

void Network::matriceFilmGraph(){
    int weight;
    for(int i=0 ; i<allFilms.size() ; i++){
        filmMatrix.push_back(vector<int>());
        for(int j=0 ; j<allFilms.size() ; j++){
            if(i==j){
                filmMatrix[i].push_back(0);
                continue;
            }
            weight = allFilms[i]->getNumberPurchased() + allFilms[j]->getNumberPurchased();
            filmMatrix[i].push_back(weight);
        }
    }
}

vector<pair<int,int>> Network::sortMatrixWithIndex() {
    vector<vector<pair<int,int>>> weightWithFilmIndex;
    matriceFilmGraph();
    for(int i=0 ; i<filmMatrix.size() ; i++){
        weightWithFilmIndex.push_back(vector<pair<int,int>>());
        for(int j=0 ; j<filmMatrix[i].size() ; j++){
            weightWithFilmIndex[i].push_back(make_pair(filmMatrix[i][j], i));
        }
    }
    vector<pair<int,int>> weights;
    for(int i=0 ; i<weightWithFilmIndex.size() ; i++){
        for(int j=0; j<weightWithFilmIndex[i].size() ; j++){
            weights.push_back(weightWithFilmIndex[i][j]);
        }
    }
    sort(weights.rbegin() , weights.rend());
    return weights;
}

void Network::printSuggestionFilms(vector<Film*> films){
    cout<<"Recommendation Film"<<endl;
    cout<<"#. Film Id | Film Name | Film Length | ";
    cout<<"Film Director"<<endl;
    for(int i=0 ; i<films.size() ; i++){
        map<string,string> info = films[i]->getMapInfo();
        cout<<i+1<<". "<<films[i]->getID()<<" | ";
        cout<<info.at(NAME)<<" | ";
        cout<<info.at(LENGTH)<<" | ";
        cout<<info.at(DIRECTOR)<<endl;
    }
}

void Network::suggestionFilms(){
    vector<pair<int,int>> sortedFilms = sortMatrixWithIndex();
    vector<Film*> bestFilms;
    for(int i=0 ; bestFilms.size()!=4 ; i++){
        Film* theFilm = allFilms[sortedFilms[i].second];
        if(!count(bestFilms.begin(),bestFilms.end(),theFilm)){
            bestFilms.push_back(theFilm);
        }
    }
    printSuggestionFilms(bestFilms);
}

void Network::showFilmDetail(int filmID){
    Film* film = searchFilmByID(filmID);
    currentUser->showFilmDetail(film);
    suggestionFilms();
}
