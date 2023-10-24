#ifndef M4_NONPERISHABLE_H
#define M4_NONPERISHABLE_H

#include <iostream>
#include "Item.h"
#include "Date.h"

namespace sdds{
    class NonPerishable: public Item{

    public:

        char itemType() const override;
        std::ostream& write(std::ostream& os)const override;

    };
}

#endif //M4_NONPERISHABLE_H
