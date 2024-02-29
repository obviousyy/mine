#include "time.hpp"

string Time::formatTime(int value) {
    return (value < 10) ? "0" + std::to_string(value) : std::to_string(value);
}

time_t Time::get_now(){
    chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return currentTime;
}

string Time::time_to_str(time_t time1){
    tm* localTime = localtime(&time1);
    string formattedTime = formatTime(localTime->tm_min) + ":" + formatTime(localTime->tm_sec);
    return formattedTime;
}

string Time::get_time() const {
    time_t now = get_now();
    return time_to_str(difftime(now, this->start));
}

void Time::begin() {
    start = Time::get_now();
}
