#include "Inventory.h"
#include <algorithm>
#include <iterator>

Inventory::Inventory() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        m_filled[i] = false;
    }
    m_current_weight = 0;
}

int Inventory::reindex(int i) { return (i + MAX_ITEMS - 1) % MAX_ITEMS; }

bool Inventory::remove(int i) {
    if (!m_filled[i]) return false;
    m_filled[i] = false;
    return true;
}

bool Inventory::pickup(Item* item) {
    // Test for validity
    int next_free =
        std::distance(m_filled, std::find(m_filled, m_filled + MAX_ITEMS, false));
    if (next_free >= MAX_ITEMS) return false;
    if (m_current_weight + item->get_weight() > MAX_WEIGHT) return false;

    // Add item
    item->setPosition(-1, -1);
    m_items[next_free] = item;
    m_filled[next_free] = true;
    return true;
}

bool Inventory::use(int i, Player& p) {
    i = reindex(i);
    if (!m_filled[i]) return false;
    if (m_items[i]->use(p)) {
        remove(i);
        // delete m_items[i];           // Must remove from scene first.
    }
    return true;
}

bool Inventory::drop(int i, float drop_x, float drop_y) {
    i = reindex(i);
    if (!remove(i)) return false;
    // TODO return ownership to MAP instance
    Item* to_drop = m_items[i];
    to_drop->setPosition(drop_x, drop_y);
    return true;
}