#pragma once
#include <exception>
class SendMessageException: public std::exception
{
public:
    explicit SendMessageException(const std::string& message,const int status):
      msg_(message),status_(status)
      {}

    virtual const char* what() const throw (){
       return msg_.c_str();
    }

protected:
    /** Error message.
     */
    std::string msg_;
    int status_;
};