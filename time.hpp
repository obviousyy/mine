#ifndef MINE_TIME_HPP
#define MINE_TIME_HPP
#include <string>
#include <chrono>
#include <ctime>
using namespace std;

class Time {
private:
    time_t start;
    static time_t get_now();
    static string time_to_str(time_t time1);
    static string formatTime(int value);
public:
    string get_time() const;
    void begin();
};

#endif //MINE_TIME_HPP
