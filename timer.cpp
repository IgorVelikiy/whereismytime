#include "timer.h"

Timer::Timer()
    : hours(0),
      minutes(0),
      seconds(0),
      milliseconds(0),
      startPoint(Clock::now())
{

}

Timer::Timer(std::string timeString)
    : startPoint(Clock::now())
{
    hours = stoul(timeString.substr(0, timeString.find(':')));
    timeString = timeString.substr(timeString.find(':') + 1);
    minutes = stoul(timeString.substr(0, timeString.find(':')));
    timeString = timeString.substr(timeString.find(':') + 1);
    seconds = stoul(timeString.substr(0, timeString.find('.')));
    milliseconds = stoul(timeString.substr(timeString.find('.') + 1));
}

std::string Timer::toString() const
{
    return std::to_string(hours)+":"
            +std::to_string(minutes)+":"
            +std::to_string(seconds)+"."
            +std::to_string(milliseconds);
}

std::string Timer::stop()
{
    auto time = Clock::now() - startPoint;
    auto hh = std::chrono::duration_cast<std::chrono::hours>(time);
    time -= hh;
    auto mm = std::chrono::duration_cast<std::chrono::minutes>(time);
    time -= mm;
    auto ss = std::chrono::duration_cast<std::chrono::seconds>(time);
    time -= ss;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);
    hours += hh.count();
    minutes += mm.count();
    seconds += ss.count();
    milliseconds += ms.count();
    return this->toString();
}
