#ifndef M1_POSAPP_H
#define M1_POSAPP_H

#include "Item.h"

namespace sdds{
    class PosApp: public Item{
        char fileName[128] ={0};
        Item *Iptr [MAX_NO_ITEMS+1]={};
        int nptr=0;
        void actionTitle(std::string name);

    public:
        PosApp();
        PosApp(const char *fileName);
        ~PosApp();

        void run();

        void menu();

        void addItem();

        void removeItem();

        void stockItem();

        void listItems();

        void POS();

        void saveRecs();

        void loadRecs();

        int selectItem();

        void sort();
    };
}
#endif //M1_POSAPP_H