#ifndef M3_ITEM_H
#define M3_ITEM_H
#include"POS.h"
#include"PosIO.h"
#include "Error.h"


namespace sdds{
    class Item : public PosIO{
        char SKU [MAX_SKU_LEN + 1];
        char* Name = {0};
        double Price;
        bool Taxed;
        int qty;

    protected:
        int displayFlag;
        Error errMsg;

    public:
        Item();
        Item(const Item& copy);
        Item& operator=(const Item& copy);
        virtual ~Item();

        bool operator==(const char* rightHand) const;
        bool operator>(const Item& r) const;
        int operator+=(int rightHand);
        int operator-=(int rightHand);
        operator bool () const;

        virtual char itemType() const;
        Item& displayType(int type);
        int quantity () const;
        double cost() const;
        char* nameQuery() const;


        std::ostream& bprint(std::ostream& os) const;

        //IO
        std::ostream& write(std::ostream& os)const override;
        std::istream& read(std::istream& is) override;
        std::ofstream& save(std::ofstream& of) const override;
        std::ifstream& load(std::ifstream& ifs) override;

    };
    double operator+=(double& left, const Item& right);

}


#endif //M3_ITEM_H
