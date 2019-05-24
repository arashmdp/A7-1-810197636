#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "User.h"
#include "Film.h"


class Publisher : public User {
public:
    Publisher(std::map <std::string,std::string> _info, int _id, bool _isPublisher);
    void newFilm(Film* film);
    void editFilm(std::map <std::string,std::string> editInfo);
    void deleteFilm(int filmID);
    void getFollowers();
    void addFollower(User* follower);
    void getPublished();
    void getMoney();

    std::string getUsername() const;
    std::string getPassword() const;
    int getID() const;
    bool getStatus() const;

protected:
    int calculateMoney(Film* film);

private:
    std::vector<Film*> allFilms;
    std::vector<User*> followers;
    std::vector<Film*> purchasedFilms; 
    int money;
};

#endif