#ifndef M2_UTILS_H
#define M2_UTILS_H
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>

namespace sdds{
    void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
    int uniqueDateValue(int year, int mon, int day, int hour, int min);
    int daysOfMonth(int year, int month);
}
#endif //M2_UTILS_H
