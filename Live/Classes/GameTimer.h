#pragma once

#include <chrono>
typedef std::chrono::system_clock Clock;

class GameTimer {
public:
  enum DayPhase { DAY, NIGHT };

  GameTimer();
  ~GameTimer();
  static GameTimer *getInstance();

  static int getTime();
  static int getDays();

  DayPhase getCurrentDayPhase();


private:
  static GameTimer *instance;
  static std::chrono::time_point<Clock> start_time;

};
