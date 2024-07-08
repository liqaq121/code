#pragma once
#define WND_WIDTH 520
#define WND_HEIGHT 640
#define IDT_TIMER1 1

#include<Windows.h>
#include<time.h>

//背景网格数组
int g_bkarr[20][10] = { 0 };
//俄罗斯方块数组
int g_tearr[2][4] = { 0 };
//方块预览数组
int g_prearr[2][4] = { 0 };
//分数
double g_score = 0;
//表面分数
float g_facescore = 0;
//是否游戏中
BOOL g_isplay = FALSE;
//是否结束
BOOL g_isover = TRUE;
//当前方块形状
int g_tetype = 0;
//预览方块形状
int g_pretype = 0;
//旋转支点
//预览方块支点
POINT g_tept = { 0 };
//当前方块支点
POINT g_prept = { 0 };
//3x3数组
//当前俄罗斯方块形状数组
int g_tert[3][3] = { 0 };
//预览图方块数组
int g_prert[3][3] = { 0 };



//窗口处理
LRESULT wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//绘图
void OnPaint(HDC hdc);
//画俄罗斯方块
void DrawBlock(HDC hdc);
//创建窗口
void OnCreate(HWND hwnd);
//创建方块
void CreateBlock();
//复制生成的方块到背景数组
void CopyToBK(HWND hwnd);
//回车键
void OnReturn(HWND hwnd);
//定时器处理函数
void OnTimer(HWND hwnd);
//下降
void BlockDown(HWND hwnd);
//判断是否到达最底端
BOOL IsBottom();
//调整方块状态，数组值
void AdjustBlockState(HWND hwnd);
//判断是否落到方块上面
BOOL IsBlockTop();
//判断游戏是否结束
BOOL IsGOver(HWND hwnd);
//左移
void OnLeft(HWND hwnd);
//右移
void OnRight(HWND hwnd);
//消除方块
void  ClearBlock(HWND hwnd);
//暂停/继续
void OnSpace(HWND hwnd);
//变形
void ChangeShape(HWND hwnd);
//长条
void StripChange(HWND hwnd);
//3x3变形
void NormalChange(HWND hwnd);