
#include "PosIO.h"

using namespace std;

namespace sdds{

    std::ostream& operator<<(std::ostream& os, PosIO& rightHand){
        return rightHand.write(os);
    }
    std::ofstream& operator<<(std::ofstream& ofs, PosIO& rightHand){
        return rightHand.save(ofs);
    }

    std::istream& operator>>(std::istream& is, PosIO& rightHand){
        return rightHand.read(is);
    }

    std::ifstream& operator>>(std::ifstream& ifs, PosIO& rightHand){
        return rightHand.load(ifs);
    }
}