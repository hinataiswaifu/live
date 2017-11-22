#pragma once

#include "Item.h"

#define MAX_WEIGHT 40
#define MAX_ITEMS 6

class Inventory {
private:
    unsigned int m_current_weight;
    Item* m_items[MAX_ITEMS];
    Item* remove(int i);
    int reindex(int i);
public:
    Inventory();
    bool pickup(Item* i);
    bool use(int i, Player& p);
    Item** getItemSlot(int i);
    Item* drop(int i);
    bool isFull();
};
