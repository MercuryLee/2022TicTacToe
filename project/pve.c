#include <stdio.h>
#include "commonFunc.h"
#include "constants.h"
#pragma warning(disable:4996)

// 미니맥스 알고리즘에 관한 간단한 설명
// 
// 미니맥스 알고리즘은 3*3보드 내의 모든 미래에 가능한 상태를 고려하는 알고리즘이다.
// 예를 들어, 처음 틱택토에 돌을 두는 사람이 놓을 수 있는 장소는 9개이며, 다음은 8개이다.
// 이와 같이 돌을 둘 수 있는 장소를 계속 트리 형태로 구성한다.
// 그리고 만약에 가상으로 만든 보드에서 게임이 끝난다면, AI가 이기는 경우는 점수를 +1,
// 지는 경우에는 점수를 -1, 무승부의 경우엔 점수의 변화를 주지 않는다.
// 이와 같이 점수가 매겨졌을 때, 그 점수를 해당 노드의 부모 어미에 더한다.
// 그렇다면 9개에 보드엔 각각의 보드에 놓았을 때, 
// 가장 점수가 높은 보드가 AI 입장에서 두기 좋은 장소가 된다.
// 
// 백트래킹 알고리즘을 활용해 이 미니맥스 알고리즘을 구성했다
// 
// 참고한 서적 (?) : https://towardsdatascience.com/lets-beat-games-using-a-bunch-of-code-part-1-tic-tac-toe-1543e981fec1

int minimax(int(*board)[4], int player) {
    int win = checkGameOver(board);
    if (win != 0 && win != 2) return win * player; // 게임이 승부가 난다면 1, 또는 -1 리턴해줌
    int score = -2, notMoved = 1;
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (board[i][j] == 0) {
                board[i][j] = player; // 해당 보드에 돌을 임의로 둠
                int temp = -minimax(board, player * -1); // 상대방 의 minimax함수의 리턴값이 적으면 나에겐 좋은 수, 따라서 - 붙여줌
                if (temp > score) {
                    score = temp;
                    notMoved = 0; 
                }
                board[i][j] = 0; // 임의로 둔 돌 빼기 (백트래킹)
            }
        }
    }
    if (notMoved) return 0;
    return score;
}
void computerMove(int(*board)[4]) {
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
    int xx, yy; // ai가 판단한 가장 효율적인 수의 i, j값 
    int score = -2;
    for (int i = 1; i < 4; i++) { 
        for (int j = 1; j < 4; j++) {
            if (board[i][j] == 0) { 
                board[i][j] = -1; 
                int temp = -minimax(board, 1); // 상대방 의 minimax함수의 리턴값이 적으면 나에겐 좋은 수, 따라서 - 붙여줌
                board[i][j] = 0; // 백트래킹 알고리즘 사용
                if (temp > score) { // 가장 높은 가중치를 가지고 있는 보드의 i, j값 저장
                    score = temp;
                    xx = i;
                    yy = j;
                }
            }
        }
    }
    board[xx][yy] = -1; // 해당 위치로 이동후 프린트
    gotoxy(x[yy], y[xx]);
    printf("X");
}
void pveGamePlay(int* screenStatus, int(*board)[4]) {
    // 메인 함수에서 screenStatus가 5인 화면
    // 한명의 플레이어만 게임을 플레이함
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
    // turn이 홀수이면 Player(O)의 차례
    // turn이 짝수이면 AI(X)의 차례
    gotoxy(x[xindex], y[yindex]); 
    while (loop) {  // 선택하는 부분 
        if (checkGameOver(board) != 0) { // 게임이 끝났으면, 게임 결과 출력해줌
            loop = 0;
            switch (checkGameOver(board)) {
            case 1:
                gotoxy(GAME_MAX_X / 2 - 4, GAME_MAX_Y - 1);
                printf("You Win !");
                break;
            case -1:
                gotoxy(GAME_MAX_X / 2 - 7, GAME_MAX_Y - 2);
                printf("Computer Win !");
                break;
            case 2:
                gotoxy(GAME_MAX_X / 2 - 3, GAME_MAX_Y - 2);
                printf("Draw !");
                break;
            }
            gotoxy(GAME_MAX_X / 2 - 10, GAME_MAX_Y - 1);
            printf("Press key to continue");
            clearCursor();
            while (1) {  // 게임이 끝나고, 입력을 받을때까지 기다려줌
                if (_kbhit()) {
                    _getch();
                    break;
                }
            }
            *screenStatus = 6; // pve 게임 결과 표시창
        }
        else if (turn % 2 == 0) { // X의 차례일때, 미니맥스 알고리즘으로 X돌을 둠
            computerMove(board);
            turn++;
            gotoxy(x[xindex], y[yindex]);
        }
        else {
            int n = _getch();
            switch (n) { // 선택하는 부분 
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
                if (xindex != 3) gotoxy(x[++xindex], y[yindex]);  // 끝 인덱스가 아니면 움직여줌
                break;
            case SPACE:
            case ENTER:
                if (board[yindex][xindex] == 0) {
                    board[yindex][xindex] = 1;
                    printf("O");
                    turn++; // Player차례
                }
                break;
            }
        }
    }
}
void pveGameResult(int* screenStatus, int(*board)[4]) {
    // 메인 함수에서 screenStatus가 6인 화면
    // 틱택토 1P게임이 끝난 후, (Computer Win, You Win, Draw)를 보여준다.
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
    FILE* fp = fopen("pve.txt", "r"); // 파일 입출력을 위한 변수 선언
    if (fp == NULL) { // 만약 파일이 없다면, 파일을 새로 만든다
        fp = fopen("pve.txt", "w"); 
        fprintf(fp, "User: %d, Computer: %d, Draw: %d", 0, 0, 0);
        fclose(fp); 
        fp = fopen("pve.txt", "r");
    }
    int userWin, comWin, draw;
    fscanf(fp, "User: %d, Computer: %d, Draw: %d", &userWin, &comWin, &draw); // 파일에서 지금까지의 전적을 받아옴
    switch (result) {  // 리턴받은 경우를 switch case 문을 사용해 각각의 경우에 대응하는 결과를 출력하고, 현재까지의 승패를 저장하는 변수에 값을 변화시켜줌
    case 2: // 무승부가 났을 때
        gotoxy(resultX[1], resultY);
        printf("Draw!");
        draw++;
        break;
    case 1: // 플레이어가 이겼을 때
        gotoxy(resultX[2], resultY);
        printf("You Win !");
        userWin++;
        break;
    case -1: // 컴퓨터가 이겼을 때
        gotoxy(resultX[2], resultY);
        printf("Computer Win !");
        comWin++;
        break;
    }
    gotoxy(MENU_MAX_X / 3, resultY - 1);
    printf("User: %d, Computer: %d, Draw: %d", userWin, comWin, draw);  // 현재까지의 전적 보여줌 (전 게임 포함해서)
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
        case SPACE: 
        case ENTER: // 스페이스나 엔터를 누르면 while문 나감
            loop = 0;
            break;
        }
    }
    fp = fopen("pve.txt", "w");
    fprintf(fp, "User: %d, Computer: %d, Draw: %d", userWin, comWin, draw); // pve 파일에 현재 전적 작성해줌
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