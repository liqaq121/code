#pragma once
#define WND_WIDTH 520
#define WND_HEIGHT 640
#define IDT_TIMER1 1

#include<Windows.h>
#include<time.h>

//������������
int g_bkarr[20][10] = { 0 };
//����˹��������
int g_tearr[2][4] = { 0 };
//����Ԥ������
int g_prearr[2][4] = { 0 };
//����
double g_score = 0;
//�������
float g_facescore = 0;
//�Ƿ���Ϸ��
BOOL g_isplay = FALSE;
//�Ƿ����
BOOL g_isover = TRUE;
//��ǰ������״
int g_tetype = 0;
//Ԥ��������״
int g_pretype = 0;
//��ת֧��
//Ԥ������֧��
POINT g_tept = { 0 };
//��ǰ����֧��
POINT g_prept = { 0 };
//3x3����
//��ǰ����˹������״����
int g_tert[3][3] = { 0 };
//Ԥ��ͼ��������
int g_prert[3][3] = { 0 };



//���ڴ���
LRESULT wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//��ͼ
void OnPaint(HDC hdc);
//������˹����
void DrawBlock(HDC hdc);
//��������
void OnCreate(HWND hwnd);
//��������
void CreateBlock();
//�������ɵķ��鵽��������
void CopyToBK(HWND hwnd);
//�س���
void OnReturn(HWND hwnd);
//��ʱ��������
void OnTimer(HWND hwnd);
//�½�
void BlockDown(HWND hwnd);
//�ж��Ƿ񵽴���׶�
BOOL IsBottom();
//��������״̬������ֵ
void AdjustBlockState(HWND hwnd);
//�ж��Ƿ��䵽��������
BOOL IsBlockTop();
//�ж���Ϸ�Ƿ����
BOOL IsGOver(HWND hwnd);
//����
void OnLeft(HWND hwnd);
//����
void OnRight(HWND hwnd);
//��������
void  ClearBlock(HWND hwnd);
//��ͣ/����
void OnSpace(HWND hwnd);
//����
void ChangeShape(HWND hwnd);
//����
void StripChange(HWND hwnd);
//3x3����
void NormalChange(HWND hwnd);