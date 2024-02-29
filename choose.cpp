#include <string>
#include "choose.hpp"

void button(int x, int y, int w, int h, const string& text)
{
    setlinecolor(GRAY_BRUSH);//设置框边颜色
    setbkmode(TRANSPARENT);//设置字体背景透明
    setfillcolor(RGB(255, 255, 255));//设置填充颜色
    fillroundrect(x, y, x + w, y + h, 10, 10);//画一个按钮框

    settextcolor(BLACK);
    settextstyle(40, 0, "黑体");
    const char *text_= text.c_str();
    int tx = x + (w - textwidth(text_)) / 2;
    int ty = y + (h - textheight(text_)) / 2;
    outtextxy(tx, ty, text_);
}

int choose(int x, int y, bool flag){
    initgraph(400, 350);
    RECT rect{};
    GetWindowRect(GetHWnd(), &rect);
    const int width = rect.right - rect.left;
    const int height = rect.bottom - rect.top;
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    int ww = 400;
    int wh = 350;
    if (flag){
        x = (sw - ww) /2;
        y = (sh - wh) /2;
    }
    MoveWindow(GetHWnd(), x, y, width, height, false);
    button(50, 50, 300, 50, "9x9 10雷");
    button(50, 150, 300, 50, "16x16 40雷");
    button(50, 250, 300, 50, "16x30 99雷");
    MOUSEMSG msg{};
    while (true) {
        if (MouseHit())//有鼠标操作消息返回真
        {
            msg = GetMouseMsg();//获取鼠标信息
            if (msg.uMsg == WM_LBUTTONDOWN)//消息分发
            {
                if (msg.x >= 50 && msg.x <= 50 + 300 && msg.y >= 50 && msg.y <= 50 + 50){
                    closegraph();
                    return 1;
                }
                else if (msg.x >= 50 && msg.x <= 50 + 300 && msg.y >= 150 && msg.y <= 150 + 50) {
                    closegraph();
                    return 2;
                }
                else if (msg.x >= 50 && msg.x <= 50 + 300 && msg.y >= 250 && msg.y <= 250 + 50){
                    closegraph();
                    return 3;
                }
            }
        }
    }
}