//
// Created by E on 10/20/2019.
//

#ifndef LINKEDSTACK_PRECONDVIOLATEDEXCEPT_H
#define LINKEDSTACK_PRECONDVIOLATEDEXCEPT_H
#include <stdexcept>
#include <string>


class PrecondViolatedExcept : public std::logic_error{
public:
    explicit PrecondViolatedExcept(const std::string& message = "");
};
#endif //LINKEDSTACK_PRECONDVIOLATEDEXCEPT_H
