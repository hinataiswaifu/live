#pragma once

#include "Direction.h"
#include "GameObject.h"

#define EXPIRE_LIMIT 500
#define SPEED 10

class Arrow : public GameObject {
public:
    Arrow(float pos_x, float pos_y, Direction dir);
    virtual void update();
    bool isExpired();
private:
	Direction m_orientation;
	float m_distance_travelled;
	bool m_expired;
	void move(float x, float y);
};
