#include <random>
#include "mine.hpp"

using namespace std;


mines::mines(int r, int c, int mines): row(r), col(c), num(mines) {
    mine = new int*[r];
    for (int i = 0; i < r; i++){
        mine[i] = new int[c];
        for (int j = 0; j < c; j++)
            mine[i][j] = 10;
    }
    for (int i = 0; i < num;){
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 generator(seed);
        uniform_int_distribution<int> distribution(0, row-1);
        int x = distribution(generator);
        generator.discard(10);
        uniform_int_distribution<int> distribution2(0, col-1);
        int y = distribution2(generator);
        if (mine[x][y] != 19 && !(x == 0 && y == col-1) && !(x == 0 && y == 0) && !(x == row-1 && y == 0) &&!(x == row-1 && y == col-1))
        {
            mine[x][y] = 19;
            i++;
            for (int m = max(0, x - 1); m < min(row, x + 2); m++) {
                for (int n = max(0, y - 1); n < min(col, y + 2); n++) {
                    if (!(m == x && n == y)) {
                        if (mine[m][n] != 19)
                            mine[m][n]++;
                    }
                }
            }
        }
    }
}


int mines::count(int i, int j, bool flag){
    int count = 0;
    for (int m = max(0, i - 1); m < min(row, i + 2); m++) {
        for (int n = max(0, j - 1); n < min(col, j + 2); n++) {
            if (!(m == i && n == j)){
                if (flag){
                    if (if_flag(m, n))
                        count++;
                }
                else{
                    if (if_block(m, n))
                        count++;
                }
            }
        }
    }
    return count;
}

int mines::left(){
    int count = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (if_block(i, j)){
                count++;
            }
        }
    }
    return count;
}

void mines::set_mine(int i, int j, bool flag) {
    if (flag)
        mine[i][j] -= 10;
    else
        mine[i][j] += 10;
}
