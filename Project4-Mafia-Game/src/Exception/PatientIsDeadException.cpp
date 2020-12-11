#include "PatientIsDeadException.hpp"

const char* PatientIsDeadException::what() const throw()
{
    return "Patient is dead\n";
}