#include "Date.h"
#include "Utils.h"
#include "POS.h"


using namespace std;

namespace sdds{

    Date::Date(){
        getSystemDate(year,month,day,hour,minute,date);
    }

    Date::Date(int yr, int mon, int dy){
        year=yr;
        month=mon;
        day=dy;
        date=true;

        valid_date(year,month,day,0,0);

    }

    Date::Date(int yr, int mon, int dy, int hr, int min){
        year=yr;
        month=mon;
        day=dy;
        hour=hr;
        minute=min;
        date= false;

        valid_date(year,month,day,hour,minute);
    }

    void Date::valid_date(int yr, int mon, int dy, int hr, int min){

        if(yr<MIN_YEAR || yr>MAX_YEAR){
            strcpy(errorOj,"Invalid Year");
        }else if((mon<0 || mon>12) && (yr>=MIN_YEAR && yr<=MAX_YEAR)){
            strcpy(errorOj,"Invalid Month");
        }else if((dy<0 || dy > daysOfMonth(yr,mon)) && (mon>0 && mon<13) &&(yr>=MIN_YEAR && yr<=MAX_YEAR)){
            strcpy(errorOj,"Invalid Day");
        }else if((hr<0 || hr>24) && (dy>0 && dy<=daysOfMonth(yr,mon) )&& (mon>0 && mon<13)&&(yr>=MIN_YEAR && yr<=MAX_YEAR)){
            strcpy(errorOj,"Invalid Hour");
        }else if((min<0 || min>=60) && (hr>=0 && hr<24) && (dy>0 && dy<=daysOfMonth(yr,mon) )&& (mon>0 && mon<13)&&(yr>=MIN_YEAR && yr<=MAX_YEAR)){
            strcpy(errorOj,"Invlid Minute");
        }


    }

    bool Date::operator==(Date& dt) const{
        bool same=false;

        if(uniqueDateValue(year,month,day,hour,minute)== uniqueDateValue(dt.year,dt.month,dt.day,hour,minute)){
            same= true;
        }
        return same;
    }

    bool Date::operator!=(Date& dt) const{
        bool same =false;

        if(uniqueDateValue(year,month,day,hour,minute)!= uniqueDateValue(dt.year,dt.month,dt.day,hour,minute)){
            same= true;
        }

        return same;
    }

    bool Date::operator<(Date& dt) const{
        bool less = false;

        if(uniqueDateValue(year,month,day,hour,minute) < uniqueDateValue(dt.year,dt.month,dt.day,hour,minute)){
            less= true;
        }

        return less;
    }

    bool Date::operator>(Date& dt) const{
        bool more=false;

        if(uniqueDateValue(year,month,day,hour,minute) > uniqueDateValue(dt.year,dt.month,dt.day,hour,minute)){
            more= true;
        }
        return more;
    }

    bool Date::operator<=(Date& dt) const{
        bool less =false;

        if(uniqueDateValue(year,month,day,hour,minute) <= uniqueDateValue(dt.year,dt.month,dt.day,hour,minute)){
            less= true;
        }

        return less;
    }

    bool Date::operator>=(Date& dt) const{
        bool more=false;

        if(uniqueDateValue(year,month,day,hour,minute) >= uniqueDateValue(dt.year,dt.month,dt.day,hour,minute)){
            more= true;
        }

        return more;
    }

    Date& Date::dateOnly(bool dateO){
        if(dateO){
            hour=0;
            minute=0;
        }
        date=dateO;

        return *this;
    }

    Date::operator bool() const{
        bool state =false;

        if(errorOj[0]=='\0'){
            state= true;
        }else if(errorOj[0]!='\0'){
            state= false;
        }

        return state;
    }

    const char *Date::error(){
        return errorOj;
    }

    ostream& Date::display(std::ostream& os){

        if(date){
            if(errorOj[0]!='\0'){
                os<<errorOj<<"("<<year<<"/"<< (month<10? "0" : "")<<month<<"/"<<(day<10? "0" : "")<<day<<")";
            }else{
                os<<year<<"/"<<(month<10? "0" : "")<<month<<"/"<<(day<10? "0" : "")<<day;
            }
        }else{
            if(errorOj[0]!='\0'){
                os<<errorOj<<"("<<year<<"/"<<(month<10? "0" : "")<<month<<"/"<<(day<10? "0" : "")<<day<<", "<< (hour<10 ?"0" : "" )<<hour<<":"<<(minute<10 || minute==0 ? "0" :"")<<minute<<")";
            }else {
                os << year << "/" <<(month<10? "0" : "")<< month << "/" << (day<10? "0" : "")<<day << ", " << (hour<10 ?"0" : "" )<<hour << ":" << (minute<10 || minute==0 ? "0" :"")<<minute;
            }
        }
        return os;
    }

    ostream& operator<<(ostream& os, Date& dt){
        dt.display(os);
        return os;
    }

    istream& Date::read(istream& is){
        errorOj[0]='\0';
        year=0;
        month=0;
        day=0;
        hour=0;
        minute=0;

        if(date){
            is>>year;
            is.ignore();
            is>>month;
            is.ignore();
            is>>day;
            if(is.fail()){
                if(year==0){
                    strcpy(errorOj,"Cannot read year entry");
                }else if(month==0){
                    strcpy(errorOj,"Cannot read month entry");
                }else if (day==0){
                    strcpy(errorOj,"Cannot read day entry");
                }
            }else{
                valid_date(year,month,day,0,0);
            }

        }else{
            is>>year;
            is.ignore();
            is>>month;
            is.ignore();
            is>>day;
            is.ignore();
            is>>hour;
            is.ignore();
            is>>minute;

            if(is.fail()){
                if(year==0){
                    strcpy(errorOj,"Cannot read year entry");
                }else if(month==0){
                    strcpy(errorOj,"Cannot read month entry");
                }else if (day==0){
                    strcpy(errorOj,"Cannot read day entry");
                }else if(hour==0){
                    strcpy(errorOj,"Cannot read hour entry");
                }else if( minute==0){
                    strcpy(errorOj,"Cannot read minute entry");
                }
            }else{
                valid_date(year,month,day,hour,minute);
            }
        }
        return is;

    }

    istream& operator>>(istream& is, Date& dt){
        return dt.read(is);
    }


}