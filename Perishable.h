
#ifndef M4_PERISHABLE_H
#define M4_PERISHABLE_H
#include "Item.h"
#include "Date.h"
#include "PosIO.h"

namespace sdds{
    class Perishable: public Item{
        Date date;
    public:

        Perishable();
        char itemType() const override;

        std::istream& read(std::istream& is) override;
        std::ostream& write(std::ostream& os)const override;
        std::ifstream& load(std::ifstream& ifs)override;
        std::ofstream& save(std::ofstream& of) const override;

    };
}

#endif //M4_PERISHABLE_H