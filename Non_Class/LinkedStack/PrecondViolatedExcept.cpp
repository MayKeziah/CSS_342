//
// Created by E on 10/20/2019.
//

#include "PrecondViolatedExcept.h"
inline PrecondViolatedExcept::PrecondViolatedExcept(const std::string& message) :
std::logic_error("Precondition Violated Exception: " + message){}