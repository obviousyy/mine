#include <string>
#include "choose.hpp"

void button(int x, int y, int w, int h, const string& text)
{
    setlinecolor(GRAY_BRUSH);//���ÿ����ɫ
    setbkmode(TRANSPARENT);//�������屳��͸��
    setfillcolor(RGB(255, 255, 255));//���������ɫ
    fillroundrect(x, y, x + w, y + h, 10, 10);//��һ����ť��

    settextcolor(BLACK);
    settextstyle(40, 0, "����");
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
    button(50, 50, 300, 50, "9x9 10��");
    button(50, 150, 300, 50, "16x16 40��");
    button(50, 250, 300, 50, "16x30 99��");
    MOUSEMSG msg{};
    while (true) {
        if (MouseHit())//����������Ϣ������
        {
            msg = GetMouseMsg();//��ȡ�����Ϣ
            if (msg.uMsg == WM_LBUTTONDOWN)//��Ϣ�ַ�
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