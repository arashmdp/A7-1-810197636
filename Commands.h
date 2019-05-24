#ifndef COMMANDS_H
#define COMMANDS_H

#include "Network.h"
#include "Exceptions.h"

#include <vector>
#include <string>

#define POST "POST"
#define PUT "PUT"
#define GET "GET"
#define DELETE "DELETE"
#define SIGNUP "signup"
#define LOGIN "login"
#define FILMS "films"
#define MONEY "money"
#define REPLIES "replies"
#define FOLLOWERS "followers"
#define COMMENTS "comments"
#define BUY "buy"
#define RATE "rate"
#define PUBLISHED "published"
#define PURCHASED "purchased"
#define NOIFICATIONS "notifications"
#define LOGOUT "logout"
#define PUT_FILMS "put_films"

std::vector<std::string> separate(std::string line);
void detectCommands (std::string line, Network* network);

#endif