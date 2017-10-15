#pragma once

#include "Item.h"

#define DEFAULT_MAX_WEIGHT 40
#define MAX_ITEMS 6

class Inventory {
private:
    unsigned int m_max_weight = DEFAULT_MAX_WEIGHT;
    unsigned int m_current_weight;
    unsigned int m_num_items;
    Item* m_items[MAX_ITEMS];

public:
    Inventory();
    bool consume(Item* i);
    bool use(Item* i);
    bool pickup(Item* i);
    bool drop(Item* i);
};