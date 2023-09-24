#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>
#include <iostream>

class BaseException : public std::exception {
protected:
    std::string messagePrefix;
    std::string messageBody;
public:
    BaseException(char* prefix, char* errorMessage) : messagePrefix(std::string(prefix)), messageBody(std::string(errorMessage)) {
        std::cout << this->what() << std::endl;
    }
    BaseException(std::string prefix, std::string errorMessage) : messagePrefix(prefix), messageBody(errorMessage) {
        std::cout << this->what() << std::endl;
    }
    BaseException(QString prefix, QString errorMessage) : messagePrefix(prefix.toStdString()), messageBody(errorMessage.toStdString()) {
        std::cout << this->what() << std::endl;
    }
    BaseException(char* errorMessage) : messagePrefix(std::string()), messageBody(std::string(errorMessage)) {
        std::cout << this->what() << std::endl;
    }
    BaseException(std::string errorMessage) : messagePrefix(std::string()), messageBody(errorMessage) {
        std::cout << this->what() << std::endl;
    }
    const std::string what() { return this->messagePrefix + this->messageBody; };
    ~BaseException() { }
};



class OpenCLException : public BaseException {
public:
    OpenCLException(std::string errorMessage) : BaseException("OpenCL exception: ", errorMessage) { }
};


#endif // EXCEPTIONS_H
