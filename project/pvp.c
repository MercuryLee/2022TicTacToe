#include <stdio.h>
#include <windows.h>
#include "commonFunc.h"
#include "constants.h"
#pragma warning(disable:4996)

void pvpGamePlay(int* screenStatus, int(*board)[4]) {
    // 메인 함수에서 screenStatus가 7인 화면
    // 2명의 플레이어끼리 번갈아가면서 게임을 플레이함 
    // gotoxy를 통해서 미리 그려진 보드 위에 일정 위치로 커서를 옮긴 후, O, X를 출력해줌
    system("cls");
    showCursor();
    int x[4] = { // 틱택토 보드의 x, y좌표 값들
        0,
        4,
        12,
        20
    };
    int y[4] = {
        0,
        2,
        6,
        10
    };
    initializeBoard(board);
    drawBoard(); //보드 초기화, 보드 그리기
    int turn = 1, xindex = 1, yindex = 1, loop = 1;
    // turn이 홀수이면 P1(O)의 차례
    // turn이 짝수이면 P2(X)의 차례
    gotoxy(x[xindex], y[yindex]); 
    while (loop) { // 선택하는 부분 
        int n = _getch();
        switch (n) {
        case w:
        case W:
        case UP:
            if (yindex != 1) gotoxy(x[xindex], y[--yindex]);
            break;
        case s:
        case S:
        case DOWN:
            if (yindex != 3) gotoxy(x[xindex], y[++yindex]);
            break;
        case a:
        case A:
        case LEFT:
            if (xindex != 1) gotoxy(x[--xindex], y[yindex]);
            break;
        case d:
        case D:
        case RIGHT:
            if (xindex != 3) gotoxy(x[++xindex], y[yindex]); // 끝 인덱스가 아니면 움직여줌
            break;
        case SPACE:
        case ENTER: // 엔터나 스페이스를 받고, 그 보드가 비어있다면, 그 턴에 맞는 O, X를 출력해줌
            if (board[yindex][xindex] == 0) {
                if (turn % 2 == 1) {
                    board[yindex][xindex] = 1;
                    printf("O");
                } // P1 차례
                else {
                    board[yindex][xindex] = -1;
                    printf("X");
                } // P2 차례
                turn++;
            }
            break;
        }
        if (checkGameOver(board) != 0) { // 게임이 끝났으면, 게임 결과 출력해줌
            loop = 0;
            switch (checkGameOver(board)) {
            case 1:
                gotoxy(GAME_MAX_X / 2 - 6, GAME_MAX_Y - 2);
                printf("P1 (0) Win !");
                break;
            case -1:
                gotoxy(GAME_MAX_X / 2 - 6, GAME_MAX_Y - 2);
                printf("P2 (X) Win !");
                break;
            case 2:
                gotoxy(GAME_MAX_X / 2 - 3, GAME_MAX_Y - 2);
                printf("Draw !");
                break;
            }
            gotoxy(GAME_MAX_X / 2 - 10, GAME_MAX_Y - 1);
            printf("Press key to continue"); 
            clearCursor();
            while (1) { // 게임이 끝나고, 입력을 받을때까지 기다려줌
                if (_kbhit()) {
                    _getch();
                    break;
                }
            }
            *screenStatus = 8; // pvp 게임 결과 표시창
        }
    }
}

void pvpGameResult(int* screenStatus, int(*board)[4]) {
    // 메인 함수에서 screenStatus가 8인 화면
    // 틱택토 2P게임이 끝난 경우, 게임의 결과(1P Win, 2P Win, Draw)를 보여준다.
    reSizeConsole(MENU_MAX_X, MENU_MAX_Y);
    int result = checkGameOver(board); // 게임 결과 리턴받기
    int resultX[3] = { // 게임의 결과를 표시할때, "Draw!"와 "P1(P2) (O) Win !"과의 문자열 길이가 다르기에 가운데 정렬을 하기 위해서 이와 같이 구성함
        0,
        MENU_MAX_X / 2 - 5,
        MENU_MAX_X / 2 - 7,
    };
    int resultY = MENU_MAX_Y / 4 - 2;
    int x[3] = { // ">"문자를 표시할 x, y 좌표, 모든 선택지가 있는 함수에서 이와 같은 방식으로 구성됨
        0,
        MENU_MAX_X / 3 ,
        MENU_MAX_X / 3 - 3
    };
    int y[3] = {
        0,
        MENU_MAX_Y / 2,
        MENU_MAX_Y / 2 + 1
    };
    FILE* fp = fopen("pvp.txt", "r"); // 파일 입출력을 위한 변수 선언
    if (fp == NULL) { // 만약 파일이 없다면, 파일을 새로 만든다
        fp = fopen("pvp.txt", "w");
        fprintf(fp, "P1: %d, P2: %d, Draw: %d", 0, 0, 0);
        fclose(fp);
        fp = fopen("pvp.txt", "r");
    }
    int p1Win, p2Win, draw;
    fscanf(fp, "P1: %d, P2: %d, Draw: %d", &p1Win, &p2Win, &draw); // 파일에서 지금까지의 전적을 받아옴
    switch (result) { // 리턴받은 경우를 switch case 문을 사용해 각각의 경우에 대응하는 결과를 출력하고, 현재까지의 승패를 저장하는 변수에 값을 변화시켜줌
    case 2: // 무승부가 났을 때
        gotoxy(resultX[1], resultY);
        printf("Draw!");
        draw++;
        break;
    case 1: // P1이 이겼을 때
        gotoxy(resultX[2], resultY);
        printf("P1 (O) Win !");
        p1Win++;
        break;
    case -1: // P2가 이겼을 때
        gotoxy(resultX[2], resultY);
        printf("P2 (X) Win !");
        p2Win++;
        break;
    }
    gotoxy(MENU_MAX_X / 3 + 4, resultY - 1);
    printf("P1: %d, P2: %d, Draw: %d", p1Win, p2Win, draw); // 현재까지의 전적 보여줌 (전 게임 포함해서)
    gotoxy(MENU_MAX_X / 3 - 4, y[1] - 3);
    printf("Would you like to play tictactoe again ? ");
    int loop = 1, index = 1;
    gotoxy(x[1] - 2, y[1]); // 원래는 글이 나오는곳에서 두 픽셀 뒤에 ">"가 나와서 x[1] - 2로 가서 출력함
    printf("> Yes, I want to play it again.");
    gotoxy(x[2], y[2]);
    printf("No, I don't want to play it again.");
    while (loop) { // 선택하는 부분
        int n = _getch();
        switch (n) {
        case W:
        case w:
        case UP:
            if (index == 2) changeIndex(x, y, &index, 1);
            break;
        case S:
        case s:
        case DOWN:
            if (index == 1) changeIndex(x, y, &index, 2);
            break;
        case SPACE: // 스페이스나 엔터를 누르면 while문 나감
        case ENTER:
            loop = 0;
            break;
        }
    }
    fp = fopen("pvp.txt", "w");
    fprintf(fp, "P1: %d, P2: %d, Draw: %d", p1Win, p2Win, draw); // pvp 파일에 현재 전적 작성해줌
    fclose(fp);
    switch (index) { // 스페이스나 엔터를 눌렀을 때, 인덱스 값을 기준으로 다음 화면을 보여주는 screenStatus변수의 값을 바꿈
    case 1:
        *screenStatus = 4; // 플레이어 선택 창
        break;
    case 2:
        *screenStatus = 0; // 게임 나가기
        break;
    }
}