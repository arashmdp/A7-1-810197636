#ifndef USER_H
#define USER_H

#include <map>
#include <vector>
#include <string>

#include "Film.h"

#define USERNAME "username"
#define PASSWORD "password"
#define EMAIL "email"
#define NAME "name"
#define DIRECTOR "director"
#define LENGTH "length"
#define YEAR "year"
#define SUMMARY "summary"
#define PRICE "price"

class User {
    public:
        User(std::map <std::string,std::string> _info, int _id, bool _isPublisher);

        virtual void newFilm(Film* film) {};
        virtual void editFilm(std::map<std::string,std::string> editMap) {};
        virtual void deleteFilm(int filmID) {};
        virtual void getFollowers() {};
        virtual void addFollower(User* follower) {};
        virtual void getPublished() {};
        virtual void getMoney(){};

        void follow(User* flwingPub);
        void addMoney(int amount);
        void showFilmDetail(Film* film);
        void buyFilm(Film* film);
        void rateFilm(Film* film, int rate);

        std::string getUsername() const;
        std::string getPassword() const;
        std::string getEmail() const;
        int getID() const;
        bool getStatus() const;

        void sendNotification(std::string content);
        
    
    protected:
        int id;
        std::map <std::string,std::string> info;
        bool isPublisher;
        std::vector<User*> following;
        std::vector<std::string> notifications;
        int moneyAmount;
        std::vector<Film*> purchasedFilms;


};

#endif