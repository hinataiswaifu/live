#include "GameTimer.h"

GameTimer::GameTimer() {
    start_time = Clock::now();
}

GameTimer::~GameTimer() {}

int GameTimer::getTime() {
    return std::chrono::duration_cast<std::chrono::seconds>(Clock::now()-start_time).count();
}

int GameTimer::getDaysElapsed() {
    return getTime()/10;
}

GameTimer::DayPhase GameTimer::getCurrentDayPhase() {
    if(getTime()/5 % 2 == 0) {
        return DayPhase::DAY;
    }
    return DayPhase::NIGHT;
}

GameTimer* GameTimer::getInstance() {
    if (!GameTimer::instance)
        GameTimer::instance = new GameTimer();
    return GameTimer::instance;
}

GameTimer* GameTimer::instance = nullptr;
std::chrono::time_point<Clock> GameTimer::start_time = Clock::now();
