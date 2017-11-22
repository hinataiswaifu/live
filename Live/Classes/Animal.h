#pragma once

#include "ResourceObstacle.h"
#include "Direction.h"
#include "Animate.h"

#define ANIMAL_MAX_HEALTH   100
#define ANIMAL_FRAME_COUNT  3
#define NUM_ANIMALS         4

class Animal : public ResourceObstacle, public Live::Animate {
public:
    Animal(const std::string& sprite_frame_file,
            float pos_x, float pos_y, unsigned int index, float speed);

    void update(float delta);

private:
    float m_health;

protected:
    float m_speed;
    virtual void animateMove();
    virtual void stopMove();
};
