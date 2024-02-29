#include <easyx.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "mine.hpp"
#include "choose.hpp"
#include "time.hpp"
#include "mine_map.hpp"

using namespace std;

int victory(const string& now_time, int mode){
    ifstream infile;
    infile.open("D:/others/project/mine/best_time.txt", ios::in);
    string best_time[3];
    for (auto & i : best_time) {
        getline(infile, i);
    }
    infile.close();
    if (now_time < best_time[mode]){
        best_time[mode] = now_time;
        ofstream outfile;
        outfile.open("D:/others/project/mine/best_time.txt", ios::out);
        for (const auto & i : best_time)
            outfile << i << endl;
        outfile.close();
    }
    string when_win = string("你赢了！耗时: ") + now_time + " , 最佳耗时为: " + best_time[mode] + " , 是否继续该模式重开？";
    return MessageBox(GetHWnd(), when_win.c_str(), "hit", MB_YESNOCANCEL);
}

int CALLBACK WinMain(
        _In_ HINSTANCE hInstance,
        _In_ HINSTANCE hPrevInstance,
        _In_ LPSTR lpCmdLine,
        _In_ int nCmdShow
) {
    bool flag = true;
    IMAGE img[23];
    for (int i = 0; i < 23; i++)
    {
        char filename[50];
        sprintf_s(filename, "D:/others/project/mine/images/%d.jpg", i);
        loadimage(img + i, filename, IMGW, IMGW);
    }
    int row, col, mines, mode;
    bool retry = false;
    bool xy = true;
    int x = 0;
    int y = 0;
    while(flag){
        if (!retry){
            mode = choose(x, y, xy);
            switch (mode) {
                case 1:
                    row = 9;
                    col = 9;
                    mines = 10;
                    break;
                case 2:
                    row = 16;
                    col = 16;
                    mines = 40;
                    break;
                case 3:
                    row = 30;
                    col = 16;
                    mines = 99;
                    break;
                default:
                    continue;
            }
        }
        else retry = false;
        mine_map win(row, col, mines, x, y, xy, img);
        while (true){
            win.MouseEvent();
            int mine = win.get_mine();
            if (mine <= 0){
                int ret;
                switch (mine) {
                    case -1:
                        ret = MessageBox(GetHWnd(), "你输了！是否继续该模式重开？", "hit", MB_YESNOCANCEL);
                        break;
                    case 0:
                        if (win.finish()){
                            ret = victory(win.get_time(), mode-1);
                        }
                        else{
                            ret = MessageBox(GetHWnd(), "你输了！是否继续该模式重开？", "hit", MB_YESNOCANCEL);
                        }
                        break;
                    case -2:
                        ret = MessageBox(GetHWnd(), "全知视角，展开！是否继续该模式重开？", "hit", MB_YESNOCANCEL);
                        break;
                    case -3:
                        ret = victory(win.get_time(), mode-1);
                        break;
                }
                if (ret == IDCANCEL){
                    flag = false;
                }
                else if (ret == IDYES){
                    retry = true;
                }
                break;
            }
        }
        RECT rect{};
        GetWindowRect(GetHWnd(), &rect);
        x = rect.left;
        y = rect.top;
        xy = false;
    }
    return 0;
}