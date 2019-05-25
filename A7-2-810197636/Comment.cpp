#include "Comment.h"

using namespace std;

Comment::Comment(string _content, int _id){
    content = _content;
    id = _id;
}

string Comment::getContent() const {
    return content;
}

string Comment::getReply() const {
    return reply;
}

int Comment::getID() const {
    return id;
}