#pragma once

#include "Item.h"

#define MAX_WEIGHT 40
#define MAX_ITEMS 10

class Inventory {
private:
    unsigned int m_current_weight;
    Item* m_items[MAX_ITEMS];
    bool m_filled[MAX_ITEMS];
    bool remove(int i);
    int reindex(int i);

public:
    Inventory();
    bool pickup(Item* i);
    bool use(int i, Player& p);
    bool drop(int i, float drop_x, float drop_y);
};