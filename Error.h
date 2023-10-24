
#ifndef M2_ERROR_H
#define M2_ERROR_H
#include <iostream>
#include <cstring>

namespace sdds{
    class Error {
        char * errorMsg;

    public:
        Error();
        Error(const char *msg);
        Error (const Error & er);
        Error& operator =(const Error & er);
        ~Error();
        operator bool () const;
        Error& clear();
        const char* errorQuery() const;

        std::ostream& display(std:: ostream& os);

    };
    std::ostream& operator << (std::ostream& os, Error& er);

}
#endif //M2_ERROR_