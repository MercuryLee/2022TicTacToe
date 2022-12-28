#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "constants.h"
#pragma warning (disable:4996)
#pragma comment(lib, "winmm.lib")

void gotoxy(int x, int y) {
    // 매개변수로 받은 X, Y로 커서를 이동하는 함수
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void changeIndex(int* x, int* y, int* index, int changeIndex) { 
    // 무언가를 선택하는 화면을 구성하는 함수가 있을때, 겹치는 부분이 너무 많아 편의상 만든 함수 
    // 해당 화면의 x배열과, y배열들을 포인터 변수로 받아내고, 해당 함수의 index를 포인터 변수로 받고, 현재 index에서 바꿀 index인 changeIndex값을 매개변수로 받아준다.
    // x, y 배열, 변수 index값을 사용해 원래 ">"가 있던 곳으로 가서 ">"를 없애주고, index를 changeIndex의 값으로 바꿔준다. 그리고 changeIndex의 x, y좌표로 움직여 ">"를 출력해준다. 
    gotoxy(x[*index] - 2, y[*index]);
    printf(" ");
    *index = changeIndex;
    gotoxy(x[*index] - 2, y[*index]);
    printf(">");
}
void reSizeConsole(int width, int height){
    // 매개변수로 받은 width, height의 값으로 콘솔의 값을 변화시키는 함수
    char chTemp[50];
    sprintf(chTemp, "mode con cols=%d lines=%d| title TicTacToe", width, height);
    system(chTemp);
}
void clearCursor() {
    // 콘솔에 보이는 커서를 없애는 함수
    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1;
    c.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}
void showCursor() {
    // 콘솔에서 없앴던 커서를 다시 보여주는 함수
    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1;
    c.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}
void drawStart(int *screenStatus) { 
    // 메인 함수에서 screenStatus가 1인 페이지
    // 처음 프로젝트를 시작했을 때, TICTACTOE 글씨가 깜박거리며, 디미고 교가를 틀어준다
    reSizeConsole(MENU_MAX_X, MENU_MAX_Y); 
    PlaySound(TEXT("Music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
    while (1) {
        if (_kbhit()) {
            // 만약 입력을 받으면 포인터를 사용해 screenStatus의 값을 바꾸어 main의 switch case에서 다음 화면으로 넘어갈 수 있게 한다.
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
    // 틱택토 플레이시 그려지는 판을 출력해주는 함수
    reSizeConsole(GAME_MAX_X, GAME_MAX_Y); // 게임을 플레이 할때의 콘솔의 X, Y값과 메뉴에서의 X, Y 값이 다르기에 크기를 바꾸어준다 
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
    // 메인 함수에서 screenStatus가 2인 화면
    // 틱택토의 룰이나, 설명을 모르는 유저들을 위해 만들어진 화면을 보여주는 함수
    system("cls");
    int x[3] = { // ">"문자를 표시할 x, y 좌표, 모든 선택지가 있는 함수에서 이와 같은 방식으로 구성됨
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
    printf("종이 위에 가로줄 2줄 세로줄 2줄을 그린다.");
    gotoxy(MENU_MAX_X / 5, MENU_MAX_Y / 6 + 7);
    printf("이렇게 생긴 9칸 위에 1P는 O, 2P는 X를 번갈아가며 그린다.");
    gotoxy(MENU_MAX_X / 5 + 2, MENU_MAX_Y / 6 + 8);
    printf("먼저 O나 X를 3개가 직선으로 이어지게 만들면 승리한다.");
    gotoxy(x[1] - 2, y[1]); // 원래는 글이 나오는곳에서 두 픽셀 뒤에 ">"가 나와서 x[1] - 2로 가서 출력함
    printf("> Go to menu");
    gotoxy(x[2], y[2]);
    printf("Quit the game");
    int index = 1, loop = 1;
    while (loop) { // 선택하는 부분
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
        case ENTER: // 스페이스나 엔터를 누르면 while문 나감
            loop = 0;
            break;
        }
    }
    switch (index) { // 스페이스나 엔터를 눌렀을 때, 인덱스 값을 기준으로 다음 화면을 보여주는 screenStatus변수의 값을 바꿈
    case 1:
        *screenStatus = 3; // 메뉴화면 
        break;
    case 2:
        *screenStatus = 0; // 나가기
        break;
    }
}
void drawMenu(int *screenStatus) {
    // 메인 함수에서 screenStatus가 3인 화면
    // 게임을 시작할지, 게임의 설명을 볼지, 게임을 나갈지 보여주는 화면을 구성하는 함수
    system("cls");
    int x[4] = { // ">"문자를 표시할 x, y 좌표, 모든 선택지가 있는 함수에서 이와 같은 방식으로 구성됨
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
    gotoxy(x[1] - 2, y[1]); // 원래는 글이 나오는곳에서 두 픽셀 뒤에 ">"가 나와서 x[1] - 2로 가서 출력함
    printf("> Game Start");
    gotoxy(x[2], y[2]);
    printf("What is Tictactoe ?");
    gotoxy(x[3], y[3]);
    printf("Exit");
    int index = 1, loop = 1;
    while (loop) { // 선택하는 부분
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
        case ENTER: // 스페이스나 엔터를 누르면 while문 나감
        case SPACE:
            loop = 0;
            break;
        }
    }   
    switch (index) { // 스페이스나 엔터를 눌렀을 때, 인덱스 값을 기준으로 다음 화면을 보여주는 screenStatus변수의 값을 바꿈
    case 1:
        *screenStatus = 4; // 플레이어 수 정하는 화면
        break;
    case 2:
        *screenStatus = 2; // 틱택토 설명하는 화면
        break;
    case 3:
        *screenStatus = 0; // 게임 나가기
        break;
    }
}
void drawPlayerChoose(int* screenStatus) {    
    // 메인 함수에서 screenStatus가 4인 화면
    // 게임을 1P로 진행할지, 2P로 진행할지 고르는 화면을 구성하는 함수
    system("cls");
    int x[3] = { // ">"문자를 표시할 x, y 좌표, 모든 선택지가 있는 함수에서 이와 같은 방식으로 구성됨
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
    gotoxy(x[1] - 2, y[1]); // 원래는 글이 나오는곳에서 두 픽셀 뒤에 ">"가 나와서 x[1] - 2로 가서 출력함
    printf("> 1P (Person VS Envrionment)");
    gotoxy(x[2], y[2]);
    printf("2P (Person VS Person)");
    int index = 1, loop = 1;
    while (loop) { // 선택하는 부분
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
        case ENTER: // 스페이스나 엔터를 누르면 while문 나감
        case SPACE:
            loop = 0;
            break;
        }
    }
    switch (index) { // 스페이스나 엔터를 눌렀을 때, 인덱스 값을 기준으로 다음 화면을 보여주는 screenStatus변수의 값을 바꿈
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
    // 틱택토를 두는 board함수 (2차원 배열) 초기화해줌
    // 4*4로 선언한 이유는 편의상 [0][0]보단 [1][1]이 더 좋은것 같아서 이와 같이 선언했음
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
}
int checkGameOver(int (*board)[4]) { 
    // 틱택토의 기본 룰을 구성하는 함수
    // 한줄이 같은 돌로 찼다면, 그 돌의 수를 반환함 (O의 경우 1, X의 경우 -1을 반환함)
    for (int i = 1; i < 4; i++) {
        if (board[1][i] == board[2][i] && board[1][i] == board[3][i] && board[1][i] != 0) return board[1][i]; // 세로줄 확인하기
        if (board[i][1] == board[i][2] && board[i][1] == board[i][3] && board[i][1] != 0) return board[i][1]; // 가로줄 확인하기
    }
    if (board[1][1] == board[2][2] && board[1][1] == board[3][3] && board[2][2] != 0) return board[2][2];
    if (board[1][3] == board[2][2] && board[2][2] == board[3][1] && board[2][2] != 0) return board[2][2]; // 대각선 체크하기
    
    int isFull = 1;
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (board[i][j] == 0) isFull = 0;
        }
    }
    if (isFull) return 2;
    // 만약 꽉 찼다면 2 반환
    return 0;
    // 아직 게임이 끝날 조건이 아니라면 0 반환
}