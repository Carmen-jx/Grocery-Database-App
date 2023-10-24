
#include <string>
#include "Error.h"
using namespace std;

namespace sdds {


    Error::Error(){
        errorMsg= nullptr;
    }

    Error::Error(const char *msg){
        if (msg != nullptr){
            errorMsg= new char[strlen(msg)+1];
            strcpy(errorMsg,msg);
        }
    }

    Error:: Error (const Error & er){
        if (er.errorMsg != nullptr){
            errorMsg= new char[strlen(er.errorMsg)+1];
            strcpy(errorMsg,er.errorMsg);
        }else{
            errorMsg= nullptr;
        }
    }

    Error& Error::operator =(const Error & er){
        if(this!=&er){
            delete [] errorMsg;
            if(er.errorMsg!= nullptr){
                errorMsg= new char[strlen(er.errorMsg)+1];
                strcpy(errorMsg,er.errorMsg);
            }else{
                errorMsg= nullptr;
            }
        }
        return *this;
    }

    Error::~Error(){
        delete [] errorMsg;
        errorMsg= nullptr;
    }

    Error::operator bool () const{
        return (errorMsg != nullptr);
    }

    Error& Error::clear(){
        delete [] errorMsg;
        errorMsg= nullptr;
        return *this;
    }

    const char* Error::errorQuery() const{
        return errorMsg;
    }

    std::ostream& Error::display(std:: ostream& os){
        os<<errorMsg;
        return os;
    }

    std::ostream& operator << (std::ostream& os, Error& er){
        if(er){
            er.display(os);
        }
        return os;
    }


}
