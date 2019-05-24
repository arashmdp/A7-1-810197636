#ifndef NETWORK_H
#define NETWORK_H

#include <vector>

#include "User.h"
#include "Publisher.h"
#include "Comment.h"

class Network {
    public:
        Network();
        void signup(std::vector<std::string> informations);
        void login(std::vector<std::string> informations);
        
        void addFilm(std::vector<std::string> information);
        void editFilm(std::vector<std::string> newInfo);
        void deleteFilm(int filmID);
        void getFollowers();
        void getPublished();
        void getMoney();

        void follow(int userID);
        void searchFilm(std::vector<std::string> filters);
        void showSearch(std::vector<Film*> films);
        void addMoney(int amount);
        void showFilmDetail(int filmID);
        void buyFilm(int filmID);
        void giveRate(std::vector<std::string> info);
        void addComment(std::vector<std::string> info);

        bool getStatus() const;

    protected:
        bool noSameName(std::string name);
        bool search(std::vector<std::string>& filters, Film* film, int i);
        Film* searchFilmByID(int filmID);

    private:
        
        std::vector <User*> allUsersAndPublishers;
        std::vector <Film*> allFilms;
        int filmCount, userCount;

        int commentID =0;
        User* currentUser;
        bool isPublisher;
};

#endif