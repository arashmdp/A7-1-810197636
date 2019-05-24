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
    vector<string> info;
    try {
        if (command[0] == POST){
            if(command[1] == SIGNUP){
                network->signup(command);
                cout<<"OK"<<endl;
            }
            else if (command[1] == LOGIN){
                network->login(command);
                cout<<"OK"<<endl;
            }
            else if (command[1] == FILMS){
                if(network->getStatus()){
                    network->addFilm(command);
                    cout<<"OK"<<endl;
                } else {
                    throw permissionDenied();
                }
            }
            else if(command[1] == MONEY){
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
            else if(command[1] == REPLIES){

            }
            else if(command[1] == FOLLOWERS){
                int userID = stoi(command[4]);
                network->follow(userID);
            }
            else if(command[1] == BUY){
                network->buyFilm(stoi(command[4]));
            }
            else if(command[1] == RATE){
                network->giveRate(command);
            }
            else if(command[1] == COMMENTS){
                network->addComment(command);
            }
            else if(command[1] == PUT_FILMS){
                if(network->getStatus()){
                    network->editFilm(command);
                    cout<<"OK"<<endl;
                } else {
                    throw permissionDenied();
                }
            }
            else {
                throw notFound();
            }
        }
        else if (command[0] == DELETE){
            if (command [1] == FILMS){
                if(network->getStatus()){
                    int filmID = stoi(command[4]);
                    network->deleteFilm(filmID);
                    cout<<"OK"<<endl;
                } else {
                    throw permissionDenied();
                }
            }
            else if(command[1] == COMMENTS){

            }
            else {
                throw notFound();
            }
        }
        else if (command[0] == GET){
            if (command[1] == FOLLOWERS){
                if(network->getStatus()){
                    network->getFollowers();
                } else {
                    throw permissionDenied();
                }
            }
            else if(command[1] == PUBLISHED){
                if(network->getStatus()){
                    network->getPublished();
                } else {
                
                }
            }
            else if(command[1] == FILMS){
                if(command[3]=="film_id"){
                    network->showFilmDetail(stoi(command[4]));
                } else {
                
                }
            }
            else if(command[1] == PURCHASED){

            }
            else if(command[1] == NOIFICATIONS){

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