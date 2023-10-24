#ifndef M3_POSIO_H
#define M3_POSIO_H

#include <iostream>
#include <fstream>

namespace sdds{

    class PosIO{

    public:

        virtual std::ostream& write(std::ostream& os) const=0;
        virtual std::istream& read(std::istream& is)=0;
        virtual std::ofstream& save(std::ofstream& of) const =0;
        virtual std::ifstream& load(std::ifstream& ifs)=0;
    };

    std::ostream& operator<<(std::ostream& os, PosIO& rightHand);
    std::ofstream& operator<<(std::ofstream& ofs, PosIO& rightHand);
    std::istream& operator>>(std::istream& is, PosIO& rightHand);
    std::ifstream& operator>>(std::ifstream& ifs, PosIO& rightHand);
}

#endif //M3_POSIO_H
