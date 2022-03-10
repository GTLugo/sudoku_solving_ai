#pragma once
//
// Created by Gabriel Lugo on 3/27/2021.
// Flugel Framework: https://github.com/GTLugo/flugel_framework
//

#include <chrono>
#include <iostream>

namespace flf {

  // duration types
  using NanoSeconds = std::chrono::duration<double, std::nano>;
  using MicroSeconds = std::chrono::duration<double, std::micro>;
  using MilliSeconds = std::chrono::duration<double, std::milli>;
  using Seconds = std::chrono::duration<double>;
  using Minutes = std::chrono::duration<double, std::ratio<60>>;
  using Hours = std::chrono::duration<double, std::ratio<3600>>;
  // clock types
  using ClockSystem = std::chrono::system_clock;
  using ClockSteady = std::chrono::steady_clock;
  using ClockAccurate = std::chrono::high_resolution_clock;
  // time point
  using TimePoint = ClockSteady::time_point;
  using TimePointAccurate = ClockAccurate::time_point;
  using TimePointSystem = ClockSystem::time_point;

  class Stopwatch {
  public:
    Stopwatch() {
      start();
    }

    explicit Stopwatch(TimePoint timePoint) {
      start(timePoint);
    }

    void start() { start(ClockSteady::now()); }

    void start(TimePoint timePoint) {
      start_ = timePoint;
    }

    template<class D>
    [[nodiscard]] double startTime() const {
      return D((start_).time_since_epoch()).count();
    }

    template<class D>
    [[nodiscard]] double getTimeElapsed() const {
      return D((ClockSteady::now() - start_)).count();
    }
  private:
    TimePoint start_{};
  };

  class Time {
  public:

    static void init(double tickRate = 128., uint32_t bailCount = 1024U) {
      // This is awful and messy, but it'll prevent anyone outside the App class
      // from reinitializing Time, which would cause the engine, the app, life,
      // the universe, and all catgirls to die.
      if (!virgin_) return;

      tickRate_ = tickRate;
      bailCount_ = bailCount;
      gameLast_ = TimePoint{ClockSteady::now()};
      gameCurrent_ = TimePoint{ClockSteady::now()};
      fixedTimeStep_ = Seconds{1. / tickRate_};
    }
//    explicit Time(double tickRate, uint32_t bailCount = 1024U)
//      : tickRate_{tickRate},
//        bailCount_{bailCount},
//        stopwatch_{ClockSteady::now()},
//        gameLast_{ClockSteady::now()},
//        gameCurrent_{ClockSteady::now()} {
//      fixedTimeStep_ = Seconds{1. / tickRate_};
//    }
//    ~Time() = default;

    [[nodiscard]] static double tickRate() {
      return tickRate_;
    }

    template<class Duration>
    [[nodiscard]] static double fixedStep() {
      return Duration::duration((fixedTimeStep_)).count();
    }

    template<class Duration>
    [[nodiscard]] static double start() {
      return stopwatch().startTime<Duration>();
    }

    template<class Duration>
    [[nodiscard]] static double sinceStart() {
      return stopwatch().getTimeElapsed<Duration>();
    }

    template<typename Duration>
    [[nodiscard]] static double now() {
      return Duration::duration(ClockSteady::now().time_since_epoch()).count();
    }

    template<class Duration>
    [[nodiscard]] static double delta() {
      return Duration::duration((delta_)).count();
    }

    template<class Duration>
    [[nodiscard]] static double lag() {
      return Duration::duration((lag_)).count();
    }

    static void update() {
      // FLUGEL_ENGINE_TRACE("Update!");
      gameCurrent_ = ClockSteady::now();
      // Seconds::duration()
      delta_ = std::chrono::duration_cast<Seconds>(gameCurrent_ - gameLast_);
      gameLast_ = gameCurrent_;
      lag_ += delta_;
      stepCount_ = 0U;
    }

    static void tick() {
      // FLUGEL_ENGINE_TRACE("Tick!");
      lag_ -= fixedTimeStep_;
      ++stepCount_;
    }

    [[nodiscard]] static bool shouldDoTick() {
      #ifndef NDEBUG
        if (stepCount_ >= bailCount_) {
          std::cerr << "Struggling to catch up with physics rate!\n";
        }
      #endif
      
      return lag_.count() >= fixedTimeStep_.count() && stepCount_ < bailCount_;
    }
  private:
    static inline bool virgin_{true};
    // fixed number of ticks per second. this will be used for physics and anything else in fixed update
    static inline double tickRate_{};
    static inline Seconds fixedTimeStep_{};
    // bail out of the fixed updates if iterations exceeds this amount to prevent lockups
    // on extremely slow systems where updateFixed may be longer than fixedTimeStep_
    static inline int bailCount_{};

    static inline TimePoint gameLast_{}; // when last frame started
    static inline TimePoint gameCurrent_{}; // when this frame started
    static inline Seconds delta_{Seconds{1. / 60.}}; // how much time last frame took
    static inline Seconds lag_{Seconds::zero()}; // how far behind the game is from real world
    static inline int stepCount_{0U};

    static const Stopwatch& stopwatch() {
      static const Stopwatch sw{ClockSteady::now()};
      return sw;
    };
  };
}