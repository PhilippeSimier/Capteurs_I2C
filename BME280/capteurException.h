#ifndef CAPTEUREXCEPTION_H
#define CAPTEUREXCEPTION_H

#include <exception>
#include <string>

class CapteurException: public exception
{

private:
    int code;          // Numero de l'erreur
    std::string message;    // description de l'erreur


public:
    CapteurException(int _codeErreur, std::string _message);
    virtual const char* what() const;
    virtual ~CapteurException();
};

#endif // CAPTEUREXCEPTION_H
