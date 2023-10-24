#ifndef M2_DATE_H
#define M2_DATE_H

#include <iostream>
#include <cstring>

namespace sdds{
    class Date{
        int year=0;
        int month=0;
        int day=0;
        int hour=0;
        int minute=0;
        bool date=false;
        char errorOj[15]={0};

    public:
        Date();
        Date(int yr, int mon, int dy);
        Date(int yr, int mon, int dy, int hr, int min = 0);

        bool operator==(Date& dt) const;
        bool operator!=(Date& dt) const;
        bool operator<(Date& dt) const;
        bool operator>(Date& dt) const;
        bool operator<=(Date& dt) const;
        bool operator>=(Date& dt) const;

        void valid_date(int yr, int mon, int dy, int min, int sec);

        Date& dateOnly(bool dateO);

        operator bool() const;

        const char *error();

        std::ostream& display(std::ostream& os=std::cout);
        std::istream& read(std::istream& is=std::cin);

    };

    std::ostream& operator<<(std::ostream& os, Date& dt);
    std::istream& operator>>(std::istream& is, Date& dt);

}
#endif //M2_DATE_H