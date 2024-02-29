#ifndef MINE_MINE_HPP
#define MINE_MINE_HPP
#pragma once
#include <cstdlib>
#include <thread>
#include <graphics.h>
#include <easyx.h>
#define IMGW 40
using namespace std;


class mines{
private:
    int row;
    int col;
    int num;
    int** mine;
public:
    mines(int r, int c, int mines);
    int left();
    int count(int i, int j, bool flag);
    int get_mine(int i, int j){return mine[i][j];}
    bool if_block(int i, int j){return (mine[i][j] >= 10 && mine[i][j] < 20);}
    bool if_flag(int i, int j){return mine[i][j] >= 20;}
    bool if_open(int i, int j){return mine[i][j] < 10;}
    bool if_mine(int i, int j){return (mine[i][j] % 10 == 9);}
    bool if_zero(int i, int j){return mine[i][j] % 10 == 0;}
    void set_mine(int i, int j, bool flag);
    ~mines(){
        for (int i = 0; i < row; ++i) {
            delete[] mine[i];
        }
        delete[] mine;
    }
};

#endif //MINE_MINE_HPP
