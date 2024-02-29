#include "mine_map.hpp"
#include "choose.hpp"
#include <string>

void mine_map::show(int i, int j, IMAGE* img){
    putimage(i * IMGW + 50, j * IMGW + 100, img);
}

mine_map::mine_map(int r, int c, int n, int x, int y, bool flag, IMAGE* img)
                    :row(r), col(c), num(n), mines(r, c, n), img(img), set_mine(n), begin(false){
    int ww = row * IMGW + 100;
    int wh = col * IMGW + 150;
    if (flag){
        x = (sw - ww) /2;
        y = (sh - wh) /2;
    }
    initgraph(ww, wh);
    setbkcolor(LIGHTGRAY);
    cleardevice();
    RECT rect{};
    GetWindowRect(GetHWnd(), &rect);
    const int width = rect.right - rect.left;
    const int height = rect.bottom - rect.top;
    MoveWindow(GetHWnd(), x, y, width, height, false);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            show(i, j, img + 20);
        }
    }
    button(row * IMGW /2+75, 50, row * IMGW /2-25, 50, "00:00");
    button(row * IMGW /2+25, 50, 50, 50, ":)");
    flags();
}

void mine_map::flags() const {
    button(50, 50, row * IMGW /2-25, 50, to_string(set_mine) + '/' + to_string(num));
}

bool mine_map::finish() {
    bool flag = true;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (mines.if_block(i, j)){
                show(i, j, img + mines.get_mine(i, j));
                if (mines.if_mine(i, j)){
                    flag = false;
                    failure();
                    break;
                }
            }
        }
        if (!flag)
            break;
    }
    return flag;
}

void mine_map::failure() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (mines.if_flag(i, j)){
                if (!mines.if_mine(i, j)){
                    mines.set_mine(i ,j, true);
                }
                else{
                    continue;
                }
            }
            show(i, j, img + mines.get_mine(i, j));
        }
    }
    set_mine = -1;
}

void mine_map::set_mines(int i, int j) {
    for (int m = max(0, i - 1); m < min(row, i + 2); m++) {
        for (int n = max(0, j - 1); n < min(col, j + 2); n++) {
            if (!(m == i && n == j)){
                if (mines.if_block(m, n)){
                    mines.set_mine(m, n, false);
                    show(m, n, img + 21);
                    set_mine--;
                    flags();
                }
            }
        }
    }
}

void mine_map::twinkle(int i, int j) {
    for (int m = max(0, i - 1); m < min(row, i + 2); m++) {
        for (int n = max(0, j - 1); n < min(col, j + 2); n++) {
            if (!(m == i && n == j)){
                if (mines.if_block(m, n))
                    show(m, n, img + 22);
            }
        }
    }
    this_thread::sleep_for(chrono::milliseconds(150));
    for (int m = max(0, i - 1); m < min(row, i + 2); m++) {
        for (int n = max(0, j - 1); n < min(col, j + 2); n++) {
            if (!(m == i && n == j)){
                if (mines.if_block(m, n))
                    show(m, n, img + 20);
            }
        }
    }
}

bool mine_map::open(int i, int j) {
    for (int m = max(0, i - 1); m < min(row, i + 2); m++) {
        for (int n = max(0, j - 1); n < min(col, j + 2); n++) {
            if (!(m == i && n == j)){
                if (mines.if_block(m, n)){
                    mines.set_mine(m, n, true);
                    show(m, n, img + mines.get_mine(m, n));
                    if (mines.if_zero(m, n))
                        open(m, n);
                    else if (mines.if_mine(m, n))
                        return false;
                }
            }
        }
    }
    return true;
}

void mine_map::MouseEvent() {
    ExMessage msg{};
    if (peekmessage(&msg, EM_MOUSE)) {
        if (msg.y > 100 && msg.y < col * IMGW + 100 && msg.x > 50 && msg.x < row * IMGW + 50){
            int r = (msg.x-50) / IMGW;
            int c = (msg.y-100) / IMGW;
            if (msg.message == WM_LBUTTONDOWN) {
                if (!begin) {
                    begin = true;
                    t.begin();
                }
                if (mines.if_block(r, c)){
                    mines.set_mine(r, c, true);
                    show(r, c, img + mines.get_mine(r, c));
                    if (mines.if_mine(r, c)){
                        int ret = MessageBox(GetHWnd(), "°¡Å¶£¬Òªºó»ÚÂð£¿", "hit", MB_YESNO);
                        if (ret == IDNO){
                            failure();
                        }
                        else if (ret == IDYES){
                            mines.set_mine(r, c, false);
                            show(r, c, img + 20);
                        }
                    }
                    else if (mines.if_zero(r, c)){
                        open(r, c);
                    }
                }
                else if (mines.if_open(r, c)){
                    if (!mines.if_zero(r, c)){
                        int ct = mines.count(r, c, true);
                        if (ct == mines.get_mine(r, c)){
                            if (!open(r, c))
                                failure();
                        }
                        else {
                            twinkle(r, c);
                        }
                    }
                }
                if (mines.left() == set_mine){
                    finish();
                    set_mine = -3;
                }
            }
            if (msg.message == WM_RBUTTONDOWN) {
                if (!begin) {
                    begin = true;
                    t.begin();
                }
                if (mines.if_block(r, c)){
                    set_mine--;
                    flags();
                    show(r, c, img + 21);
                    mines.set_mine(r, c, false);
                }
                else if (mines.if_open(r, c)){
                    if (!mines.if_zero(r, c)){
                        int ct = mines.count(r, c, false) + mines.count(r, c, true);
                        if (ct == mines.get_mine(r, c)){
                            set_mines(r, c);
                        }
                        else {
                            twinkle(r, c);
                        }
                    }
                }
                else{
                    mines.set_mine(r, c, true);
                    show(r, c, img + 20);
                    set_mine++;
                    flags();
                }
                if (mines.left() == set_mine){
                    finish();
                    set_mine = -3;
                }
            }
        }
        else if (msg.message == WM_LBUTTONDOWN){
            if (msg.y > 50 && msg.y < 100 && msg.x > row * IMGW /2+25 && msg.x < row * IMGW /2+75){
                finish();
                set_mine = -2;
            }
        }
    }
    set_time();
}

void mine_map::set_time() {
    BeginBatchDraw();
    if (begin) button(row * IMGW /2+75, 50, row * IMGW /2-25, 50, t.get_time());
    EndBatchDraw();
}

string mine_map::get_time() {
    return t.get_time();
}

void mine_map::repent() {

}
