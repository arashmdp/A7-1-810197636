#include "Commands.h"

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<string> separate(string line){
    stringstream str;
    str<<line;
    string word;
    vector<string> words;
    while(!str.eof()){
        str>>word;
        words.push_back(word); 
    }
    return words;
}

vector<string> subVector(vector<string> theVec, int begin){
    vector<string> subVec;
    for(int i= begin ; theVec.size() ; i++){
        subVec.push_back(theVec[i]);
    }
    return subVec;
}

void detectCommands(string line, Network* network){
    vector<string> command = separate(line);
    string key = command[0];
    string method = command[1];
    try {
        if (key == POST){
            if(method == SIGNUP){
                network->signup(command);
                cout<<"OK"<<endl;
            }
            else if (method == LOGIN){
                network->login(command);
                cout<<"OK"<<endl;
            }
            else if (method == FILMS){
                if(network->getStatus()){
                    network->addFilm(command);
                    cout<<"OK"<<endl;
                } else {
                    throw permissionDenied();
                }
            }
            else if(method == MONEY){
                if (command.size()>3){
                    int amount = stoi(command[4]);
                    network->addMoney(amount);
                }else{
                    if(network->getStatus()){
                        network->getMoney();
                    } else {
                        throw permissionDenied();
                    }
                }
            }
            else if(method == REPLIES){

            }
            else if(method == FOLLOWERS){
                int userID = stoi(command[4]);
                network->follow(userID);
            }
            else if(method == BUY){
                network->buyFilm(stoi(command[4]));
            }
            else if(method == RATE){
                network->giveRate(command);
            }
            else if(method == COMMENTS){
                network->addComment(command);
            }
            else if(method == PUT_FILMS){
                if(network->getStatus()){
                    network->editFilm(command);
                    cout<<"OK"<<endl;
                } else {
                    throw permissionDenied();
                }
            }
            else if(method == DELETE_FILMS){
                if(network->getStatus()){
                    int filmID = stoi(command[4]);
                    network->deleteFilm(filmID);
                    cout<<"OK"<<endl;
                } else {
                    throw permissionDenied();
                }
            }
            else if(method == DELETE_COMMENTS){

            }
            else {
                throw notFound();
            }
        }
        else if (key == GET){
            if (method == FOLLOWERS){
                if(network->getStatus()){
                    network->getFollowers();
                } else {
                    throw permissionDenied();
                }
            }
            else if(method == PUBLISHED){
                if(network->getStatus()){
                    network->getPublished();
                } else {
                
                }
            }
            else if(method == FILMS){
                if(command[3]=="film_id"){
                    network->showFilmDetail(stoi(command[4]));
                } else {
                
                }
            }
            else if(method == PURCHASED){

            }
            else if(method == NOIFICATIONS){

            }
            else {
                throw notFound();
            }
        }
        else{
            throw badRequest();
        }
    }
    catch(std::exception &exp){
        std::cerr<<exp.what()<<endl;
    }
} 