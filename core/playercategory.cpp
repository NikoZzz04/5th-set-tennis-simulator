#include "playercategory.h"

#include <stdexcept>

PlayerCategory playerCategoryFromIndex(int index)
{
    switch(index) {
    case 0:
        return PlayerCategory::Atp;
    case 1:
        return PlayerCategory::Wta;
    default:
        throw std::out_of_range("Nieprawidłowy index dla PlayerCategory");
    }
}
