#include "Exceptions.h"

const char* notFound::what() const throw() {
    return NOT_FOUND;
}

const char* badRequest::what() const throw() {
    return BAD_REQUEST;
}

const char* permissionDenied::what() const throw() {
    return PERMISSION_DENIED;
}