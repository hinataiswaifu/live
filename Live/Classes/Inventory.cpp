#include "Inventory.h"
#include <algorithm>
#include <iterator>

Inventory::Inventory() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        m_items[i] = NULL;
    }
    m_current_weight = 0;
}

int Inventory::reindex(int i) { return (i + MAX_ITEMS - 1) % MAX_ITEMS; }

Item* Inventory::remove(int i) {
    Item* temp = m_items[i];
    m_items[i] = NULL;
    if (temp != NULL) m_current_weight -= temp->getWeight();
    return temp;
}

bool Inventory::pickup(Item* item) {
    // Test for validity
    int next_free = 0;
    for (; next_free < MAX_ITEMS; next_free++) {
        if (m_items[next_free] == NULL) break;
    }
    if (next_free >= MAX_ITEMS) return false;
    if (m_current_weight + item->getWeight() > MAX_WEIGHT) return false;

    // Add item
    m_current_weight += item->getWeight();
    m_items[next_free] = item;
    m_items[next_free]->getSprite()->removeFromParent();
    return true;
}

bool Inventory::use(int i, Player& p) {
    i = reindex(i);
    if (m_items[i] == NULL) return false;
    if (m_items[i]->use(p)) {
        delete m_items[i];
        remove(i);
    }
    return true;
}

Item** Inventory::getItemSlot(int i) { return &m_items[i]; }

Item* Inventory::drop(int i) {
    i = reindex(i);
    return remove(i);
}

bool Inventory::isFull() {
    int index = 0;
    for (; index < MAX_ITEMS; index++) {
        if (m_items[index] == NULL) break;
    }
    if (index >= MAX_ITEMS) {
        return true;
    } else {
        return false;
    }
}