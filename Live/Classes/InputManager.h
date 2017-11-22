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
    void enqueueFootstep(int id);
    static int footsteps_audio_queue_id;
    AudioComponent footsteps[6] = {
      AudioComponent( "Audio/Footsteps/footstep1.mp3", 1),
      AudioComponent( "Audio/Footsteps/footstep2.mp3", 1),
      AudioComponent( "Audio/Footsteps/footstep3.mp3", 1),
      AudioComponent( "Audio/Footsteps/footstep4.mp3", 1),
      AudioComponent( "Audio/Footsteps/footstep5.mp3", 1),
      AudioComponent( "Audio/Footsteps/footstep6.mp3", 1),
    };
};
