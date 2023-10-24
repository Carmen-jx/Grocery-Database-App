#ifndef M3_POS_H
#define M3_POS_H
#define MAX_NAME_LEN 40


namespace sdds{

    const int POS_LIST=1;
    const int POS_FORM=2;
    const double TAX = 0.13;
    const int MAX_SKU_LEN = 7;
    const int MIN_YEAR = 2000;
    const int MAX_YEAR = 2023;
    const int MAX_STOCK_NUMBER = 99;
    const int MAX_NO_ITEMS = 200;


    const char ERROR_POS_SKU[]= "SKU too long";
    const char ERROR_POS_NAME[]="Item name too long";
    const char ERROR_POS_PRICE[]="Invalid price value";
    const char ERROR_POS_TAX[]="Invalid tax status";
    const char ERROR_POS_QTY[]="Invalid quantity value";
    const char ERROR_POS_STOCK[]="Item out of stock";
    const char ERROR_POS_EMPTY[]="Invalid Empty Item";




}


#endif //M3_POS_H