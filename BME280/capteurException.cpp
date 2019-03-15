#include "capteurException.h"

CapteurException::CapteurException(int _codeErreur, std::string _message):
    code(_codeErreur),
    message(_message)
{

}

const char* CapteurException::what() const
{
    return message.c_str();
}

CapteurException::~CapteurException()
{
}
