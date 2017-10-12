#include "Inventory.h"

bool Inventory::pickup( Item *item ) {
    // TODO: Test for validity;
    item->setPosition(-1, -1);
    items[num_items] = item;
    num_items += 1;
    return true;
}