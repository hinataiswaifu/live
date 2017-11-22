#pragma once

#include <map>
#include <chrono>
#include "cocos2d.h"
#include "AudioComponent.h"

#define MOVE_STEP 50

class MainScene;
class InputManager {
public:
    static cocos2d::EventListenerKeyboard* initializeInputManager(MainScene* scene);
    static void update(float delta);
private:
    static bool isKeyPressed(cocos2d::EventKeyboard::KeyCode code);
    static double keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);

    // Disallow contructor:
    InputManager();
    static std::map<cocos2d::EventKeyboard::KeyCode,
                    std::chrono::high_resolution_clock::time_point> keys;

    /** Stores a pointer to the scene the input manager is attached to */
    static MainScene* m_scene;
    // used to track release state of C key, until more sophisticated input impl
    static bool m_key_c_released;
    // used to track gameover state, currently used to reject keyboard input
    static bool m_game_over;

    // used to queue up footsteps
    static void enqueueFootstep(int id);
    static int m_footsteps_audio_queue_id;
    static AudioComponent m_footsteps[6];
    static AudioManager* m_audio_mgr;
};
