#ifndef PATIENT_IS_DEAD_EXCEPTION_H
#define PATIENT_IS_DEAD_EXCEPTION_H
#include <exception>
class PatientIsDeadException : public std::exception
{
public:
    const char* what() const throw();
};
#endif