#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "constants.h"
#pragma warning (disable:4996)
#pragma comment(lib, "winmm.lib")

void gotoxy(int x, int y) {
    // �Ű������� ���� X, Y�� Ŀ���� �̵��ϴ� �Լ�
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void changeIndex(int* x, int* y, int* index, int changeIndex) { 
    // ���𰡸� �����ϴ� ȭ���� �����ϴ� �Լ��� ������, ��ġ�� �κ��� �ʹ� ���� ���ǻ� ���� �Լ� 
    // �ش� ȭ���� x�迭��, y�迭���� ������ ������ �޾Ƴ���, �ش� �Լ��� index�� ������ ������ �ް�, ���� index���� �ٲ� index�� changeIndex���� �Ű������� �޾��ش�.
    // x, y �迭, ���� index���� ����� ���� ">"�� �ִ� ������ ���� ">"�� �����ְ�, index�� changeIndex�� ������ �ٲ��ش�. �׸��� changeIndex�� x, y��ǥ�� ������ ">"�� ������ش�. 
    gotoxy(x[*index] - 2, y[*index]);
    printf(" ");
    *index = changeIndex;
    gotoxy(x[*index] - 2, y[*index]);
    printf(">");
}
void reSizeConsole(int width, int height){
    // �Ű������� ���� width, height�� ������ �ܼ��� ���� ��ȭ��Ű�� �Լ�
    char chTemp[50];
    sprintf(chTemp, "mode con cols=%d lines=%d| title TicTacToe", width, height);
    system(chTemp);
}
void clearCursor() {
    // �ֿܼ� ���̴� Ŀ���� ���ִ� �Լ�
    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1;
    c.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}
void showCursor() {
    // �ֿܼ��� ���ݴ� Ŀ���� �ٽ� �����ִ� �Լ�
    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1;
    c.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}
void drawStart(int *screenStatus) { 
    // ���� �Լ����� screenStatus�� 1�� ������
    // ó�� ������Ʈ�� �������� ��, TICTACTOE �۾��� ���ڰŸ���, ��̰� ������ Ʋ���ش�
    reSizeConsole(MENU_MAX_X, MENU_MAX_Y); 
    PlaySound(TEXT("Music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
    while (1) {
        if (_kbhit()) {
            // ���� �Է��� ������ �����͸� ����� screenStatus�� ���� �ٲپ� main�� switch case���� ���� ȭ������ �Ѿ �� �ְ� �Ѵ�.
            _getch();
            *screenStatus = 3;
            break;
        }
        gotoxy(MENU_MAX_X / 12, MENU_MAX_Y / 3);
        printf("TTTTT    IIIII    CCCCC    TTTTT      A      CCCCC    TTTTT    OOOOO    EEEEE");
        gotoxy(MENU_MAX_X / 12, MENU_MAX_Y / 3 + 1);
        printf("  T        I      C          T       A A     C          T      O   O    E");
        gotoxy(MENU_MAX_X / 12, MENU_MAX_Y / 3 + 2);
        printf("  T        I      C          T      AAAAA    C          T      O   O    EEEEE");
        gotoxy(MENU_MAX_X / 12, MENU_MAX_Y / 3 + 3);
        printf("  T        I      C          T      A   A    C          T      O   O    E");
        gotoxy(MENU_MAX_X / 12, MENU_MAX_Y / 3 + 4);
        printf("  T      IIIII    CCCCC      T      A   A    CCCCC      T      OOOOO    EEEEE");
        gotoxy(MENU_MAX_X / 3 + 5, MENU_MAX_Y / 3 + 8);
        printf("Press Any Key to start");
        Sleep(1000);
        system("cls");
        Sleep(500);
    }
    PlaySound(NULL, NULL, NULL);
}
void drawBoard() { 
    // ƽ���� �÷��̽� �׷����� ���� ������ִ� �Լ�
    reSizeConsole(GAME_MAX_X, GAME_MAX_Y); // ������ �÷��� �Ҷ��� �ܼ��� X, Y���� �޴������� X, Y ���� �ٸ��⿡ ũ�⸦ �ٲپ��ش� 
    printf("\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("        |       |       \n");
        }
        printf(" -------+-------+-------\n");
    }
    for (int j = 0; j < 3; j++) {
        printf("        |       |       \n");
    }
} 
void drawDescription(int *screenStatus) {
    // ���� �Լ����� screenStatus�� 2�� ȭ��
    // ƽ������ ���̳�, ������ �𸣴� �������� ���� ������� ȭ���� �����ִ� �Լ�
    system("cls");
    int x[3] = { // ">"���ڸ� ǥ���� x, y ��ǥ, ��� �������� �ִ� �Լ����� �̿� ���� ������� ������
        0,
        MENU_MAX_X / 3 + 8,
        MENU_MAX_X / 3 + 6
    };
    int y[3] = {
        0,
        MENU_MAX_Y / 6 + 11,
        MENU_MAX_Y / 6 + 12
    };
    gotoxy(MENU_MAX_X / 5, MENU_MAX_Y / 6);
    printf("Tic-tac-toe is a paper-and-pencil game for two players who");
    gotoxy(MENU_MAX_X / 5 - 4, MENU_MAX_Y / 6 + 1);
    printf("take turns marking the spaces in a three-by-three grid with O or X");
    gotoxy(MENU_MAX_X / 5 + 2, MENU_MAX_Y / 6 + 2);
    printf("The player who succeeds in placing three of their marks");
    gotoxy(MENU_MAX_X / 5 + 1, MENU_MAX_Y / 6 + 3);
    printf("in a horizontal, vertical, or diagonal row is the winner.");
    gotoxy(MENU_MAX_X / 5 + 6, MENU_MAX_Y / 6 + 6);
    printf("���� ���� ������ 2�� ������ 2���� �׸���.");
    gotoxy(MENU_MAX_X / 5, MENU_MAX_Y / 6 + 7);
    printf("�̷��� ���� 9ĭ ���� 1P�� O, 2P�� X�� �����ư��� �׸���.");
    gotoxy(MENU_MAX_X / 5 + 2, MENU_MAX_Y / 6 + 8);
    printf("���� O�� X�� 3���� �������� �̾����� ����� �¸��Ѵ�.");
    gotoxy(x[1] - 2, y[1]); // ������ ���� �����°����� �� �ȼ� �ڿ� ">"�� ���ͼ� x[1] - 2�� ���� �����
    printf("> Go to menu");
    gotoxy(x[2], y[2]);
    printf("Quit the game");
    int index = 1, loop = 1;
    while (loop) { // �����ϴ� �κ�
        int n = _getch();
        switch (n) {
        case UP:
        case W:
        case w:
            if (index == 2) changeIndex(x, y, &index, 1);
            break;
        case DOWN:
        case S:
        case s:
            if (index == 1) changeIndex(x, y, &index, 2);
            break;
        case SPACE:
        case ENTER: // �����̽��� ���͸� ������ while�� ����
            loop = 0;
            break;
        }
    }
    switch (index) { // �����̽��� ���͸� ������ ��, �ε��� ���� �������� ���� ȭ���� �����ִ� screenStatus������ ���� �ٲ�
    case 1:
        *screenStatus = 3; // �޴�ȭ�� 
        break;
    case 2:
        *screenStatus = 0; // ������
        break;
    }
}
void drawMenu(int *screenStatus) {
    // ���� �Լ����� screenStatus�� 3�� ȭ��
    // ������ ��������, ������ ������ ����, ������ ������ �����ִ� ȭ���� �����ϴ� �Լ�
    system("cls");
    int x[4] = { // ">"���ڸ� ǥ���� x, y ��ǥ, ��� �������� �ִ� �Լ����� �̿� ���� ������� ������
        0,
        MENU_MAX_X / 3 + 9,
        MENU_MAX_X / 3 + 6,
        MENU_MAX_X / 2 - 4
    };
    int y[4] = {
        0,
        MENU_MAX_Y / 3 + 5,
        MENU_MAX_Y / 3 + 6,
        MENU_MAX_Y / 3 + 7
    };
    gotoxy(MENU_MAX_X / 4 - 6, MENU_MAX_Y / 3);
    printf("PRESS WASD OR ARROW TO MOVE, PRESS SPACE OR ENTER TO SELECT");
    gotoxy(x[1] - 2, y[1]); // ������ ���� �����°����� �� �ȼ� �ڿ� ">"�� ���ͼ� x[1] - 2�� ���� �����
    printf("> Game Start");
    gotoxy(x[2], y[2]);
    printf("What is Tictactoe ?");
    gotoxy(x[3], y[3]);
    printf("Exit");
    int index = 1, loop = 1;
    while (loop) { // �����ϴ� �κ�
        int n = _getch();
        switch (n) {
        case UP:
        case W:
        case w:
            if (index == 2) changeIndex(x, y, &index, 1);
            else if (index == 3) changeIndex(x, y, &index, 2);
            break;
        case DOWN:
        case S:
        case s:
            if (index == 1) changeIndex(x, y, &index, 2);
            else if (index == 2) changeIndex(x, y, &index, 3);
            break;
        case ENTER: // �����̽��� ���͸� ������ while�� ����
        case SPACE:
            loop = 0;
            break;
        }
    }   
    switch (index) { // �����̽��� ���͸� ������ ��, �ε��� ���� �������� ���� ȭ���� �����ִ� screenStatus������ ���� �ٲ�
    case 1:
        *screenStatus = 4; // �÷��̾� �� ���ϴ� ȭ��
        break;
    case 2:
        *screenStatus = 2; // ƽ���� �����ϴ� ȭ��
        break;
    case 3:
        *screenStatus = 0; // ���� ������
        break;
    }
}
void drawPlayerChoose(int* screenStatus) {    
    // ���� �Լ����� screenStatus�� 4�� ȭ��
    // ������ 1P�� ��������, 2P�� �������� ���� ȭ���� �����ϴ� �Լ�
    system("cls");
    int x[3] = { // ">"���ڸ� ǥ���� x, y ��ǥ, ��� �������� �ִ� �Լ����� �̿� ���� ������� ������
        0,
        MENU_MAX_X / 3 + 2,
        MENU_MAX_X / 3 + 5,
    };
    int y[3] = {
        0,
        MENU_MAX_Y / 3 + 4,
        MENU_MAX_Y / 3 + 6
    };
    gotoxy(MENU_MAX_X / 4 - 6, MENU_MAX_Y / 3);
    printf("PRESS WASD OR ARROW TO MOVE, PRESS SPACE OR ENTER TO SELECT");
    gotoxy(x[1] - 2, y[1]); // ������ ���� �����°����� �� �ȼ� �ڿ� ">"�� ���ͼ� x[1] - 2�� ���� �����
    printf("> 1P (Person VS Envrionment)");
    gotoxy(x[2], y[2]);
    printf("2P (Person VS Person)");
    int index = 1, loop = 1;
    while (loop) { // �����ϴ� �κ�
        int n = _getch();
        switch (n) {
        case UP:
        case W:
        case w:
            if (index == 2) changeIndex(x, y, &index, 1);
            break;
        case DOWN:
        case S:
        case s:
            if (index == 1) changeIndex(x, y, &index, 2);
            break;
        case ENTER: // �����̽��� ���͸� ������ while�� ����
        case SPACE:
            loop = 0;
            break;
        }
    }
    switch (index) { // �����̽��� ���͸� ������ ��, �ε��� ���� �������� ���� ȭ���� �����ִ� screenStatus������ ���� �ٲ�
    case SPACE:
    case 1:
        *screenStatus = 5; // 1P ( PVE )
        break;
    case 2:
        *screenStatus = 7; // 2P ( PVP )
        break;
    }
}
void initializeBoard(int(*board)[4]) { 
    // ƽ���並 �δ� board�Լ� (2���� �迭) �ʱ�ȭ����
    // 4*4�� ������ ������ ���ǻ� [0][0]���� [1][1]�� �� ������ ���Ƽ� �̿� ���� ��������
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
}
int checkGameOver(int (*board)[4]) { 
    // ƽ������ �⺻ ���� �����ϴ� �Լ�
    // ������ ���� ���� á�ٸ�, �� ���� ���� ��ȯ�� (O�� ��� 1, X�� ��� -1�� ��ȯ��)
    for (int i = 1; i < 4; i++) {
        if (board[1][i] == board[2][i] && board[1][i] == board[3][i] && board[1][i] != 0) return board[1][i]; // ������ Ȯ���ϱ�
        if (board[i][1] == board[i][2] && board[i][1] == board[i][3] && board[i][1] != 0) return board[i][1]; // ������ Ȯ���ϱ�
    }
    if (board[1][1] == board[2][2] && board[1][1] == board[3][3] && board[2][2] != 0) return board[2][2];
    if (board[1][3] == board[2][2] && board[2][2] == board[3][1] && board[2][2] != 0) return board[2][2]; // �밢�� üũ�ϱ�
    
    int isFull = 1;
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (board[i][j] == 0) isFull = 0;
        }
    }
    if (isFull) return 2;
    // ���� �� á�ٸ� 2 ��ȯ
    return 0;
    // ���� ������ ���� ������ �ƴ϶�� 0 ��ȯ
}