#include <stdio.h>
#include "commonFunc.h"
#include "constants.h"
#pragma warning(disable:4996)

// �̴ϸƽ� �˰��� ���� ������ ����
// 
// �̴ϸƽ� �˰����� 3*3���� ���� ��� �̷��� ������ ���¸� ����ϴ� �˰����̴�.
// ���� ���, ó�� ƽ���信 ���� �δ� ����� ���� �� �ִ� ��Ҵ� 9���̸�, ������ 8���̴�.
// �̿� ���� ���� �� �� �ִ� ��Ҹ� ��� Ʈ�� ���·� �����Ѵ�.
// �׸��� ���࿡ �������� ���� ���忡�� ������ �����ٸ�, AI�� �̱�� ���� ������ +1,
// ���� ��쿡�� ������ -1, ���º��� ��쿣 ������ ��ȭ�� ���� �ʴ´�.
// �̿� ���� ������ �Ű����� ��, �� ������ �ش� ����� �θ� ��̿� ���Ѵ�.
// �׷��ٸ� 9���� ���忣 ������ ���忡 ������ ��, 
// ���� ������ ���� ���尡 AI ���忡�� �α� ���� ��Ұ� �ȴ�.
// 
// ��Ʈ��ŷ �˰����� Ȱ���� �� �̴ϸƽ� �˰����� �����ߴ�
// 
// ������ ���� (?) : https://towardsdatascience.com/lets-beat-games-using-a-bunch-of-code-part-1-tic-tac-toe-1543e981fec1

int minimax(int(*board)[4], int player) {
    int win = checkGameOver(board);
    if (win != 0 && win != 2) return win * player; // ������ �ºΰ� ���ٸ� 1, �Ǵ� -1 ��������
    int score = -2, notMoved = 1;
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (board[i][j] == 0) {
                board[i][j] = player; // �ش� ���忡 ���� ���Ƿ� ��
                int temp = -minimax(board, player * -1); // ���� �� minimax�Լ��� ���ϰ��� ������ ������ ���� ��, ���� - �ٿ���
                if (temp > score) {
                    score = temp;
                    notMoved = 0; 
                }
                board[i][j] = 0; // ���Ƿ� �� �� ���� (��Ʈ��ŷ)
            }
        }
    }
    if (notMoved) return 0;
    return score;
}
void computerMove(int(*board)[4]) {
    int x[4] = { // ƽ���� ������ x, y��ǥ ����
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
    int xx, yy; // ai�� �Ǵ��� ���� ȿ������ ���� i, j�� 
    int score = -2;
    for (int i = 1; i < 4; i++) { 
        for (int j = 1; j < 4; j++) {
            if (board[i][j] == 0) { 
                board[i][j] = -1; 
                int temp = -minimax(board, 1); // ���� �� minimax�Լ��� ���ϰ��� ������ ������ ���� ��, ���� - �ٿ���
                board[i][j] = 0; // ��Ʈ��ŷ �˰��� ���
                if (temp > score) { // ���� ���� ����ġ�� ������ �ִ� ������ i, j�� ����
                    score = temp;
                    xx = i;
                    yy = j;
                }
            }
        }
    }
    board[xx][yy] = -1; // �ش� ��ġ�� �̵��� ����Ʈ
    gotoxy(x[yy], y[xx]);
    printf("X");
}
void pveGamePlay(int* screenStatus, int(*board)[4]) {
    // ���� �Լ����� screenStatus�� 5�� ȭ��
    // �Ѹ��� �÷��̾ ������ �÷�����
    // gotoxy�� ���ؼ� �̸� �׷��� ���� ���� ���� ��ġ�� Ŀ���� �ű� ��, O, X�� �������
    system("cls");
    showCursor();
    int x[4] = { // ƽ���� ������ x, y��ǥ ����
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
    drawBoard(); //���� �ʱ�ȭ, ���� �׸���
    int turn = 1, xindex = 1, yindex = 1, loop = 1;
    // turn�� Ȧ���̸� Player(O)�� ����
    // turn�� ¦���̸� AI(X)�� ����
    gotoxy(x[xindex], y[yindex]); 
    while (loop) {  // �����ϴ� �κ� 
        if (checkGameOver(board) != 0) { // ������ ��������, ���� ��� �������
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
            while (1) {  // ������ ������, �Է��� ���������� ��ٷ���
                if (_kbhit()) {
                    _getch();
                    break;
                }
            }
            *screenStatus = 6; // pve ���� ��� ǥ��â
        }
        else if (turn % 2 == 0) { // X�� �����϶�, �̴ϸƽ� �˰������� X���� ��
            computerMove(board);
            turn++;
            gotoxy(x[xindex], y[yindex]);
        }
        else {
            int n = _getch();
            switch (n) { // �����ϴ� �κ� 
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
                if (xindex != 3) gotoxy(x[++xindex], y[yindex]);  // �� �ε����� �ƴϸ� ��������
                break;
            case SPACE:
            case ENTER:
                if (board[yindex][xindex] == 0) {
                    board[yindex][xindex] = 1;
                    printf("O");
                    turn++; // Player����
                }
                break;
            }
        }
    }
}
void pveGameResult(int* screenStatus, int(*board)[4]) {
    // ���� �Լ����� screenStatus�� 6�� ȭ��
    // ƽ���� 1P������ ���� ��, (Computer Win, You Win, Draw)�� �����ش�.
    reSizeConsole(MENU_MAX_X, MENU_MAX_Y);
    int result = checkGameOver(board); // ���� ��� ���Ϲޱ�
    int resultX[3] = { // ������ ����� ǥ���Ҷ�, "Draw!"�� "P1(P2) (O) Win !"���� ���ڿ� ���̰� �ٸ��⿡ ��� ������ �ϱ� ���ؼ� �̿� ���� ������
        0,
        MENU_MAX_X / 2 - 5,
        MENU_MAX_X / 2 - 7,
    };
    int resultY = MENU_MAX_Y / 4 - 2;
    int x[3] = { // ">"���ڸ� ǥ���� x, y ��ǥ, ��� �������� �ִ� �Լ����� �̿� ���� ������� ������
        0,
        MENU_MAX_X / 3 ,
        MENU_MAX_X / 3 - 3
    };
    int y[3] = {
        0,
        MENU_MAX_Y / 2,
        MENU_MAX_Y / 2 + 1
    };
    FILE* fp = fopen("pve.txt", "r"); // ���� ������� ���� ���� ����
    if (fp == NULL) { // ���� ������ ���ٸ�, ������ ���� �����
        fp = fopen("pve.txt", "w"); 
        fprintf(fp, "User: %d, Computer: %d, Draw: %d", 0, 0, 0);
        fclose(fp); 
        fp = fopen("pve.txt", "r");
    }
    int userWin, comWin, draw;
    fscanf(fp, "User: %d, Computer: %d, Draw: %d", &userWin, &comWin, &draw); // ���Ͽ��� ���ݱ����� ������ �޾ƿ�
    switch (result) {  // ���Ϲ��� ��츦 switch case ���� ����� ������ ��쿡 �����ϴ� ����� ����ϰ�, ��������� ���и� �����ϴ� ������ ���� ��ȭ������
    case 2: // ���ºΰ� ���� ��
        gotoxy(resultX[1], resultY);
        printf("Draw!");
        draw++;
        break;
    case 1: // �÷��̾ �̰��� ��
        gotoxy(resultX[2], resultY);
        printf("You Win !");
        userWin++;
        break;
    case -1: // ��ǻ�Ͱ� �̰��� ��
        gotoxy(resultX[2], resultY);
        printf("Computer Win !");
        comWin++;
        break;
    }
    gotoxy(MENU_MAX_X / 3, resultY - 1);
    printf("User: %d, Computer: %d, Draw: %d", userWin, comWin, draw);  // ��������� ���� ������ (�� ���� �����ؼ�)
    gotoxy(MENU_MAX_X / 3 - 4, y[1] - 3);  
    printf("Would you like to play tictactoe again ? ");
    int loop = 1, index = 1;
    gotoxy(x[1] - 2, y[1]); // ������ ���� �����°����� �� �ȼ� �ڿ� ">"�� ���ͼ� x[1] - 2�� ���� �����
    printf("> Yes, I want to play it again.");
    gotoxy(x[2], y[2]);
    printf("No, I don't want to play it again.");
    while (loop) { // �����ϴ� �κ�
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
        case ENTER: // �����̽��� ���͸� ������ while�� ����
            loop = 0;
            break;
        }
    }
    fp = fopen("pve.txt", "w");
    fprintf(fp, "User: %d, Computer: %d, Draw: %d", userWin, comWin, draw); // pve ���Ͽ� ���� ���� �ۼ�����
    fclose(fp);
    switch (index) { // �����̽��� ���͸� ������ ��, �ε��� ���� �������� ���� ȭ���� �����ִ� screenStatus������ ���� �ٲ�
    case 1:
        *screenStatus = 4; // �÷��̾� ���� â
        break;
    case 2:
        *screenStatus = 0; // ���� ������
        break;
    }
}