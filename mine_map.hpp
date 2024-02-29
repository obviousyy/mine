#ifndef MINE_MINE_MAP_HPP
#define MINE_MINE_MAP_HPP
#include "mine.hpp"
#include "time.hpp"

#define sw GetSystemMetrics(SM_CXSCREEN)
#define sh GetSystemMetrics(SM_CYSCREEN)

class mine_map {
private:
    int row;
    int col;
    int num;
    mines mines;
    IMAGE* img;
    int set_mine;
    Time t;
    bool begin;
public:
    mine_map(int r, int c, int n, int x, int y, bool flag, IMAGE* img);
    bool open(int i, int j);
    void failure();
    void twinkle(int i, int j);
    void set_mines(int i, int j);
    void MouseEvent();
    bool finish();
    void flags() const;
    int get_mine() const{return set_mine;}
    void set_time();
    void show(int i, int j, IMAGE* im);
    void repent();
    string get_time();
    ~mine_map(){
        closegraph();
    }
};


#endif //MINE_MINE_MAP_HPP
