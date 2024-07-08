#include"Tetris.h"
#include"resource.h"
#include<math.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//��ƴ�����改
	wchar_t classname[50] = L"LZZGUIFoundation";
	wchar_t titlename[50] = L"�������˹����";
	WNDCLASS wc = { 0 };
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//ϵͳ����NULL
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wc.lpfnWndProc = wndproc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = classname;
	wc.hInstance = hInstance;

	//ע�ᴰ����
	RegisterClass(&wc);

	//��������
	HWND hwnd = CreateWindow(classname, titlename, WS_OVERLAPPEDWINDOW, 200, 100, WND_WIDTH, WND_HEIGHT, NULL, NULL, hInstance, NULL);
	
	//��ʾ���´���
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//�������ϢתΪ�ַ���Ϣ
		TranslateMessage(&msg);
		//�ַ���Ϣ
		DispatchMessage(&msg);
	}

	return 0;
}
LRESULT wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		mciSendString(L"open һ�����.mp3 alias bgm", NULL, 0, NULL);
		mciSendString(L"play bgm repeat", NULL, 0, NULL);
		OnCreate(hwnd);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT://�ͻ������û�ͼ
	{
		PAINTSTRUCT ps = { 0 };
		HDC hdc = BeginPaint(hwnd, &ps);
		OnPaint(hdc);
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			if (g_isover)
				OnReturn(hwnd);
			break;
		case VK_SPACE:
			if (!g_isover)
				OnSpace(hwnd);
			break;
		case VK_LEFT:
			if (g_isplay)
				OnLeft(hwnd);
			break;
		case VK_RIGHT:
			if (g_isplay)
				OnRight(hwnd);
			break;
		case VK_DOWN:
			if (g_isplay)
				OnTimer(hwnd);
			break;
		case VK_UP:
			if (g_isplay)
				ChangeShape(hwnd);
			break;
		}
		break;
	case WM_TIMER:
		if (!g_isover)
			OnTimer(hwnd);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void OnPaint(HDC hdc)
{
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP bmp = CreateCompatibleBitmap(hdc, WND_WIDTH, WND_HEIGHT);
	SelectObject(memdc, bmp);
	DrawBlock(memdc);
	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, memdc, 0, 0, SRCCOPY);
}
void DrawBlock(HDC hdc)
{
	RECT rect = { 0,0,WND_WIDTH, WND_HEIGHT };
	FillRect(hdc, &rect, HBRUSH(RGB(255, 255, 255)));
	MoveToEx(hdc, 0, 0, NULL);
	LineTo(hdc, WND_WIDTH, 0);
	MoveToEx(hdc, 300, 0, NULL);
	LineTo(hdc, 300, WND_HEIGHT);
	MoveToEx(hdc, 300, 150, NULL);
	LineTo(hdc, WND_WIDTH, 150);

	//������ˢ
	HBRUSH hbrush1 = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH hbrush2 = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hbrush3 = CreateSolidBrush(RGB(255, 0, 255));
	//���ƶ���˹����
	for(int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
		{
			if (g_bkarr[i][j] == 1)
			{
				SelectObject(hdc, hbrush1);
				Rectangle(hdc, j * 30 + 1, i * 30 + 1, (j + 1) * 30 - 1, (i + 1) * 30 - 1);
			}
			else if (g_bkarr[i][j] == 2)
			{
				SelectObject(hdc, hbrush2);
				Rectangle(hdc, j * 30 + 1, i * 30 + 1, (j + 1) * 30 - 1, (i + 1) * 30 - 1);
			}
		}
	//����Ԥ��ͼ
	SelectObject(hdc, hbrush3);
	for(int i=0;i<2;i++)
		for (int j = 0; j < 4; j++)
			if (g_prearr[i][j] == 1)
				Rectangle(hdc, j * 30 + 330 + 1, i * 30 + 50 + 1, (j + 1) * 30 + 330 - 1, i * 30 + 80 - 1);
	//����������Ϣ
	HFONT font = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("����"));
	SelectObject(hdc, font);
	wchar_t scorearr[10] = { 0 };
	wsprintf(scorearr, L"��ǰ����: %d", (int)g_facescore);
	SetBkMode(hdc, 0);
	TextOut(hdc, 350, 10, L"��һ��", wcslen(L"��һ��"));
	TextOut(hdc, 330, 120, scorearr, wcslen(scorearr));
	TextOut(hdc, 350, 190, L"��Ϸ˵��", wcslen(L"��Ϸ˵��"));
	TextOut(hdc, 330, 230, L"�س���: ��ʼ��Ϸ", wcslen(L"�س���: ��ʼ��Ϸ"));
	TextOut(hdc, 330, 270, L"�ո��: ��ͣ/����", wcslen(L"�ո��: ��ͣ/����"));
	TextOut(hdc, 330, 310, L"�����: ����", wcslen(L"�����: ����"));
	TextOut(hdc, 330, 350, L"���Ҽ�: ����", wcslen(L"���Ҽ�: ����"));
	TextOut(hdc, 330, 390, L"���¼�: ����", wcslen(L"���¼�: ����"));
	TextOut(hdc, 330, 430, L"���ϼ�: ����", wcslen(L"���ϼ�: ����"));
}
void OnCreate(HWND hwnd)
{
	memset(g_bkarr, 0, sizeof(g_bkarr));
	InvalidateRect(hwnd, NULL, FALSE);
	CreateBlock();//��������
	memcpy(g_tearr, g_prearr, sizeof(g_prearr));
}
void CreateBlock()
{
	memset(g_prert, 0, sizeof(g_prert));
	srand((unsigned int)time(NULL));
	//���������
	int index = rand() % 7;
	switch (index)
	{
	case 0:
		g_prearr[0][0] = 1, g_prearr[0][1] = 1, g_prearr[0][2] = 1, g_prearr[0][3] = 1;
		g_prearr[1][0] = 0, g_prearr[1][1] = 0, g_prearr[1][2] = 0, g_prearr[1][3] = 0;
		g_prept.x = 0, g_prept.y = 4;
		break;
	case 1:
		g_prearr[0][0] = 1, g_prearr[0][1] = 0, g_prearr[0][2] = 0, g_prearr[0][3] = 0;
		g_prearr[1][0] = 1, g_prearr[1][1] = 1, g_prearr[1][2] = 1, g_prearr[1][3] = 0;
		g_prept.x = 0, g_prept.y = 3;
		break;
	case 2:
		g_prearr[0][0] = 0, g_prearr[0][1] = 0, g_prearr[0][2] = 1, g_prearr[0][3] = 0;
		g_prearr[1][0] = 1, g_prearr[1][1] = 1, g_prearr[1][2] = 1, g_prearr[1][3] = 0;
		g_prept.x = 0, g_prept.y = 3;
		break;
	case 3:
		g_prearr[0][0] = 0, g_prearr[0][1] = 1, g_prearr[0][2] = 1, g_prearr[0][3] = 0;
		g_prearr[1][0] = 0, g_prearr[1][1] = 1, g_prearr[1][2] = 1, g_prearr[1][3] = 0;
		g_prept.x = 0, g_prept.y = 3;
		break;
	case 4:
		g_prearr[0][0] = 0, g_prearr[0][1] = 1, g_prearr[0][2] = 1, g_prearr[0][3] = 0;
		g_prearr[1][0] = 1, g_prearr[1][1] = 1, g_prearr[1][2] = 0, g_prearr[1][3] = 0;
		g_prept.x = 0, g_prept.y = 3;
		break;
	case 5:
		g_prearr[0][0] = 0, g_prearr[0][1] = 1, g_prearr[0][2] = 0, g_prearr[0][3] = 0;
		g_prearr[1][0] = 1, g_prearr[1][1] = 1, g_prearr[1][2] = 1, g_prearr[1][3] = 0;
		g_prept.x = 0, g_prept.y = 3;
		break;
	case 6:
		g_prearr[0][0] = 1, g_prearr[0][1] = 1, g_prearr[0][2] = 0, g_prearr[0][3] = 0;
		g_prearr[1][0] = 0, g_prearr[1][1] = 1, g_prearr[1][2] = 1, g_prearr[1][3] = 0;
		g_prept.x = 0, g_prept.y = 3;
		break;
	}
	g_pretype = index;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			g_prert[i][j] = g_prearr[i][j];
}
void CopyToBK(HWND hwnd)
{
	for(int i=0;i<2;i++)
		for (int j = 0; j < 4; j++)
			g_bkarr[i][j + 3] = g_tearr[i][j]; 
	g_tetype = g_pretype;
	g_tept = g_prept;
	memcpy(g_tert, g_prert, sizeof(g_prert));
	//������Ԥ��
	CreateBlock();
	InvalidateRect(hwnd, NULL, FALSE);
}
void OnReturn(HWND hwnd)
{
	CopyToBK(hwnd);//���Ƶ���������
	g_isover = FALSE;
	g_isplay = TRUE;
	SetTimer(hwnd, IDT_TIMER1, 500, NULL);
}
void OnTimer(HWND hwnd)
{
	if (FALSE == IsBottom() && FALSE == IsBlockTop())//������
		BlockDown(hwnd);
	else//ͣ��
	{
		AdjustBlockState(hwnd);//����״ֵ̬
		ClearBlock(hwnd);
		int res = IsGOver(hwnd);
		if (res == 1)//����
		{
			OnCreate(hwnd);
			return;
		}
		else if(res == 0)//�˳�
			exit(0);
		//����
		memcpy(g_tearr, g_prearr, sizeof(g_prearr));//��Ԥ��ͼ���Ƶ�����˹��������
		CopyToBK(hwnd);//������˹�������鸴�Ƶ���������
	}
}
void BlockDown(HWND hwnd)
{
	for (int i = 19; i >= 0; i--)
		for (int j = 0; j < 10; j++)
			if (g_bkarr[i][j] == 1)
			{
				g_bkarr[i + 1][j] = 1;
				g_bkarr[i][j] = 0;
			}
	g_tept.x++;
	InvalidateRect(hwnd, NULL, FALSE);
}
BOOL IsBottom()
{
	for (int i = 0; i < 10; i++)
		if (g_bkarr[19][i] == 1)
			return TRUE;
	return FALSE;
}
void AdjustBlockState(HWND hwnd)
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			if (g_bkarr[i][j] == 1)
				g_bkarr[i][j] = 2;
	InvalidateRect(hwnd, NULL, FALSE);
}
BOOL IsBlockTop()
{
	for (int i = 19; i >= 0; i--)
		for (int j = 0; j < 10; j++)
			if (g_bkarr[i][j] == 1 && g_bkarr[i + 1][j] == 2)
				return TRUE;
	return FALSE;
}
int IsGOver(HWND hwnd)
{
	for (int i = 0; i < 10; i++)
	{
		if (g_bkarr[0][i] == 2)
		{
			wchar_t str[50] = { 0 };
			wsprintf(str, L"��Ϸ����,�Ƿ�����?\n(���ķ���Ϊ:%d)", (int)g_facescore);
			if (IDYES == MessageBox(hwnd, str, L"��ʾ", MB_YESNO | MB_ICONQUESTION))
			{
				g_score = 0;
				g_facescore = 0;
				KillTimer(hwnd, IDT_TIMER1);
				g_isplay = FALSE;
				g_isover = TRUE;
				return 1;//����
			}
			else
			{
				return 0;//�˳�
			}
		}
	}
	return -1;//��Ϸ����
}
void OnLeft(HWND hwnd)
{
	//������߽�
	for (int i = 0; i < 20; i++)
		if (g_bkarr[i][0] == 1)
			return;
	//�ж�����Ƿ��з���
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			if (g_bkarr[i][j] == 1 && g_bkarr[i][j - 1] == 2)
				return;
	//����
	for(int i=0;i<20;i++)
		for (int j = 0; j < 10; j++)
			if (g_bkarr[i][j] == 1)
			{
				g_bkarr[i][j - 1] = 1;
				g_bkarr[i][j] = 0;
			}
	g_tept.y--;
	InvalidateRect(hwnd, NULL, FALSE);
}
void OnRight(HWND hwnd)
{
	//�����ұ߽�
	for (int i = 0; i < 20; i++)
		if (g_bkarr[i][9] == 1)
			return;
	//�ж��ұ��Ƿ��з���
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			if (g_bkarr[i][j] == 1 && g_bkarr[i][j + 1] == 2)
				return;
	//����
	for (int i = 0; i < 20; i++)
		for (int j = 9; j >= 0; j--)
			if (g_bkarr[i][j] == 1)
			{
				g_bkarr[i][j + 1] = 1;
				g_bkarr[i][j] = 0;
			}
	g_tept.y++;
	InvalidateRect(hwnd, NULL, FALSE);
}
void ClearBlock(HWND hwnd)
{
	srand((unsigned int)time(NULL));
	int clearlayer = 0;
	int lastlayer = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (g_bkarr[i][j] != 2)
				break;
			if (j == 9)
			{
				for (int k = 0; k < 10; k++)
					g_bkarr[i][k] = 0;
				clearlayer++;
				lastlayer = i;
			}
		}
	}
	if (clearlayer)
	{
		g_score = pow(-1, rand() % 10) * (fabs(g_score) + pow(2, clearlayer));
		g_facescore = fabs(g_score) * 10;
	}
	while (clearlayer--)
	{
		for (int i = lastlayer - 1; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{
				if (g_bkarr[i][j] == 2 && i != 19 && g_bkarr[i + 1][j] != 2)
				{
					g_bkarr[i + 1][j] = 2;
					g_bkarr[i][j] = 0;
				}
			}
		}
	}
	InvalidateRect(hwnd, NULL, FALSE);
}
void OnSpace(HWND hwnd)
{
	if (g_isplay)//��Ϸδ��ͣ
	{
		KillTimer(hwnd, IDT_TIMER1);
	}
	else//��Ϸ��ͣ
	{
		SetTimer(hwnd, IDT_TIMER1, 500, NULL);
	}
	g_isplay = !g_isplay;
}
void ChangeShape(HWND hwnd)
{
	switch (g_tetype)
	{
	case 0://����
		StripChange(hwnd);
		break;
	case 3://������
		break;
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
		NormalChange(hwnd);
		break;
	}
	InvalidateRect(hwnd, NULL, FALSE);
}
void StripChange(HWND hwnd)
{
	if (g_bkarr[g_tept.x][g_tept.y - 1] == 1)
	{				   
		if (g_tept.x - 1 >= 0 && g_tept.x + 2 <20 &&
			g_bkarr[g_tept.x - 1][g_tept.y] ==0 &&
			g_bkarr[g_tept.x + 1][g_tept.y] == 0 &&
			g_bkarr[g_tept.x + 2][g_tept.y] ==0)
		{
			g_bkarr[g_tept.x][g_tept.y - 1] = 0;
			g_bkarr[g_tept.x][g_tept.y] = 0;
			g_bkarr[g_tept.x][g_tept.y + 1] = 0;
			g_bkarr[g_tept.x][g_tept.y + 2] = 0;

			g_bkarr[g_tept.x - 1][g_tept.y] = 1;
			g_bkarr[g_tept.x][g_tept.y] = 1;
			g_bkarr[g_tept.x + 1][g_tept.y] = 1;
			g_bkarr[g_tept.x + 2][g_tept.y] = 1;
		}
	}
	else if(g_bkarr[g_tept.x - 1][g_tept.y] == 1)
	{
		if (g_tept.x >=0 && g_tept.y + 2 < 10 &&
			g_bkarr[g_tept.x][g_tept.y - 1] ==0 &&
			g_bkarr[g_tept.x][g_tept.y + 1] ==0 &&
			g_bkarr[g_tept.x][g_tept.y + 2] ==0)
		{
			g_bkarr[g_tept.x - 1][g_tept.y] = 0;
			g_bkarr[g_tept.x][g_tept.y] = 0;
			g_bkarr[g_tept.x + 1][g_tept.y] = 0;
			g_bkarr[g_tept.x + 2][g_tept.y] = 0;

			g_bkarr[g_tept.x][g_tept.y - 1] = 1;
			g_bkarr[g_tept.x][g_tept.y] = 1;
			g_bkarr[g_tept.x][g_tept.y + 1] = 1;
			g_bkarr[g_tept.x][g_tept.y + 2] = 1;
		}
	}
}
void NormalChange(HWND hwnd)
{
	////����һ����ʱ3x3����
	////ʵ��������ת-˳ʱ��
	int temp[3][3] = { 0 };
	for(int i=0;i<3;i++)
		for (int j = 0; j < 3; j++)
			temp[j][2-i] = g_tert[i][j];
	//���Ʊ���
	//��
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (temp[i][j] == 1 && (g_tept.x + i < 0 || g_bkarr[g_tept.x + i][g_tept.y + j] == 2))
				return;
	//��
	for (int i = 2; i >= 0; i--)
		for (int j = 0; j < 3; j++)
			if (temp[i][j] == 1 && (g_tept.x + i > 19 || g_bkarr[g_tept.x + i][g_tept.y + j] == 2))
				return;
	//��
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (temp[j][i] == 1 && (g_tept.y + i < 0 || g_bkarr[g_tept.x + j][g_tept.y + i] == 2))
				return;
	//��
	for (int i = 0; i < 3; i++)
		for (int j = 2; j >= 0; j--)
			if (temp[j][i] == 1 && (g_tept.y + i > 19 || g_bkarr[g_tept.x + j][g_tept.y + i] == 2))
				return;
	//���κ��λ���Ƿ���2
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (g_tert[i][j] == 1 && g_bkarr[g_tept.x + i][g_tept.y + j] == 2)
				return;

	memcpy(g_tert, temp, sizeof(temp));
	for(int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			g_bkarr[g_tept.x + i][g_tept.y + j] = g_tert[i][j];
	InvalidateRect(hwnd, NULL, FALSE);
}