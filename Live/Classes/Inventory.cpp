#include "Inventory.h"

Inventory::Inventory() {
    m_current_weight = 0;
    m_num_items = 0;
}

bool Inventory::pickup( Item *item ) {
    // TODO: Test for validity;
    item->setPosition(-1, -1);
    m_items[m_num_items] = item;
    m_num_items += 1;
    return true;
}