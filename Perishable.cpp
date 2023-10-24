#include "Perishable.h"
#include "POS.h"

using namespace std;

namespace sdds{

    Perishable::Perishable(){
        date.dateOnly(true);
    }
    char Perishable::itemType() const{
        return 'P';
    }

    std::istream& Perishable:: read(std::istream& is){
        Item::read(is);
        if(errMsg.errorQuery()== nullptr && !is.fail()) {
            cout << "Expiry date (YYYY/MM/DD)" << endl;
            cout << "> ";
            is >> (Date &) date;
            if(is.fail()){
                errMsg=date.error();
            }
        }
        return is;
    }

    std::ostream& Perishable:: write(std::ostream& os)const {
        Item::write(os);
        if(errMsg.errorQuery() == nullptr){
            if(displayFlag==POS_LIST){
                os<<"  "<<(Date&)date<<" |";
            }else if(displayFlag==POS_FORM){
                os<<"Expiry date: "<<(Date&)date<<endl;
                os<<"=============^"<<endl;
            }
        }
        return os;
    }

    std::ifstream& Perishable::load(std::ifstream& ifs){
        char delim;

        Item::load(ifs);
        if(errMsg.errorQuery() == nullptr && !ifs.fail()){
            date.dateOnly(true);
            ifs>>delim>>(Date&)date;
            if(ifs.fail()){
                errMsg=date.error();
            }
        }

        return ifs;
    }

    std::ofstream& Perishable::save(std::ofstream& of) const {
        Item::save(of);
        if(!of.fail()){
            of<<","<< (Date&)date;
        }
        return of;
    }
}