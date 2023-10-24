
#include "NonPerishable.h"

using namespace std;

namespace sdds{

    char NonPerishable::itemType() const{
        return 'N';
    }

    ostream& NonPerishable::write(std::ostream& os)const {
        Item::write(os);
        if (errMsg.errorQuery() == nullptr) {
            if (displayFlag == POS_FORM) {
                os << "=============^";
                os<< endl;
            } else if (displayFlag == POS_LIST) {
                os << "     N / A   |";
            }
        }

        return os;
    }

}