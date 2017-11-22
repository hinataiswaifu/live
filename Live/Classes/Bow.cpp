#include "Bow.h"
#include "Equipment/BowEquip.h"
#include "Player.h"

bool Bow::use(Player& p) {
	p.equip(new BowEquip(p, p.getOrientation()));
	return true;
};
