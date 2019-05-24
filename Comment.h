#ifndef COMMENT_H
#define COMMENT_H

#include <string>

class Comment{
public:
    Comment(std::string content);
    std::string getContent() const;
    std::string getReply() const;
    int getIDt() const;
private:
    std::string content;
    std::string reply;
    int id ;
};

#endif