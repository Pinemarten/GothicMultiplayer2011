
/*
MIT License

Copyright (c) 2022 Gothic Multiplayer Team.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "gothic_clock.h"

#include <chrono>
#include <spdlog/spdlog.h>

namespace
{
constexpr std::chrono::seconds kClockUpdateInterval(4);
}

GothicClock::GothicClock(Time initial_time) : time_(initial_time)
{
  thread_ = std::thread(&GothicClock::RunClockLoop, this);
}

GothicClock::~GothicClock()
{
  run_clock_thread_ = false;
  thread_.join();
}

void GothicClock::RunClockLoop()
{
  while (run_clock_thread_)
  {
    std::this_thread::sleep_for(kClockUpdateInterval);
    std::lock_guard<std::mutex> lock(time_mutex_);
    if (++time_.min_ > 59)
    {
      time_.min_ = 0;
      if (++time_.hour_ > 23)
      {
        time_.hour_ = 0;
        time_.day_++;
      }
    }
    SPDLOG_TRACE("Gothic clock interval update: {}", time_);
  }
}

void GothicClock::UpdateTime(GothicClock::Time new_time)
{
  std::lock_guard<std::mutex> lock(time_mutex_);
  time_ = new_time;
  SPDLOG_DEBUG("Gothic clock updated to {}", time_);
}

GothicClock::Time GothicClock::GetTime() const
{
  Time current_time;
  std::lock_guard<std::mutex> lock(time_mutex_);
  current_time = time_;
  return current_time;
}

void GothicClock::Time::from_toml(const toml::value& v)
{
  day_ = toml::find<std::uint16_t>(v, "day");
  hour_ = toml::find<std::uint8_t>(v, "hour");
  min_ = toml::find<std::uint8_t>(v, "min");
}

std::ostream& operator<<(std::ostream& os, const GothicClock::Time& d)
{
  return os << d.day_ << '-' << static_cast<std::int32_t>(d.hour_) << ':'
            << static_cast<std::int32_t>(d.min_);
}