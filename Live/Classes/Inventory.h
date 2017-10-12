#ifndef __INVENTORY__H__
#define __INVENTORY__H__

#include <vector>
#include "Item.h"

#define DEFAULT_MAX_WEIGHT 40
#define MAX_ITEMS 6

class Inventory {
private:
    unsigned int max_weight;
    unsigned int current_weight;
    unsigned int num_items;
    Item *items[MAX_ITEMS];
public:
    Inventory() {
        current_weight = 0;
        num_items = 0;
    }
    bool consume( Item *i );
    bool use( Item *i );
    bool pickup( Item *i );
    bool drop( Item *i );
};

#endif