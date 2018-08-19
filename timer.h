#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <chrono>

class Timer
{
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
private:
    unsigned int hours,
                 minutes,
                 seconds,
                 milliseconds;
    TimePoint    startPoint;
public:
    Timer();
    explicit Timer(std::string timeString);

    std::string toString() const;
    std::string stop();
    void        convertToLarger();
};

#endif // TIMER_H
