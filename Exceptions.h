#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

#define NOT_FOUND "Not Found"
#define BAD_REQUEST "Bad Request"
#define PERMISSION_DENIED "Permission Denied"

class notFound : public std::exception {
    const char* what() const throw ();
};

class badRequest : public std::exception {
    const char* what() const throw ();
};

class permissionDenied : public std::exception {
    const char* what() const throw ();
};

#endif