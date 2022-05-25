#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "Card.hpp"

namespace helpers
{

static inline auto sortDescending = [](const Card& first, const Card& second){
    return first.getValue() < second.getValue();
};

} // helpers

#endif