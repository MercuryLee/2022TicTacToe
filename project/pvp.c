#include <stdio.h>
#include <windows.h>
#include "commonFunc.h"
#include "constants.h"
#pragma warning(disable:4996)

void pvpGamePlay(int* screenStatus, int(*board)[4]) {
    // ���� �Լ����� screenStatus�� 7�� ȭ��
    // 2���� �÷��̾�� �����ư��鼭 ������ �÷����� 
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
    // turn�� Ȧ���̸� P1(O)�� ����
    // turn�� ¦���̸� P2(X)�� ����
    gotoxy(x[xindex], y[yindex]); 
    while (loop) { // �����ϴ� �κ� 
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
            if (xindex != 3) gotoxy(x[++xindex], y[yindex]); // �� �ε����� �ƴϸ� ��������
            break;
        case SPACE:
        case ENTER: // ���ͳ� �����̽��� �ް�, �� ���尡 ����ִٸ�, �� �Ͽ� �´� O, X�� �������
            if (board[yindex][xindex] == 0) {
                if (turn % 2 == 1) {
                    board[yindex][xindex] = 1;
                    printf("O");
                } // P1 ����
                else {
                    board[yindex][xindex] = -1;
                    printf("X");
                } // P2 ����
                turn++;
            }
            break;
        }
        if (checkGameOver(board) != 0) { // ������ ��������, ���� ��� �������
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
            while (1) { // ������ ������, �Է��� ���������� ��ٷ���
                if (_kbhit()) {
                    _getch();
                    break;
                }
            }
            *screenStatus = 8; // pvp ���� ��� ǥ��â
        }
    }
}

void pvpGameResult(int* screenStatus, int(*board)[4]) {
    // ���� �Լ����� screenStatus�� 8�� ȭ��
    // ƽ���� 2P������ ���� ���, ������ ���(1P Win, 2P Win, Draw)�� �����ش�.
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
    FILE* fp = fopen("pvp.txt", "r"); // ���� ������� ���� ���� ����
    if (fp == NULL) { // ���� ������ ���ٸ�, ������ ���� �����
        fp = fopen("pvp.txt", "w");
        fprintf(fp, "P1: %d, P2: %d, Draw: %d", 0, 0, 0);
        fclose(fp);
        fp = fopen("pvp.txt", "r");
    }
    int p1Win, p2Win, draw;
    fscanf(fp, "P1: %d, P2: %d, Draw: %d", &p1Win, &p2Win, &draw); // ���Ͽ��� ���ݱ����� ������ �޾ƿ�
    switch (result) { // ���Ϲ��� ��츦 switch case ���� ����� ������ ��쿡 �����ϴ� ����� ����ϰ�, ��������� ���и� �����ϴ� ������ ���� ��ȭ������
    case 2: // ���ºΰ� ���� ��
        gotoxy(resultX[1], resultY);
        printf("Draw!");
        draw++;
        break;
    case 1: // P1�� �̰��� ��
        gotoxy(resultX[2], resultY);
        printf("P1 (O) Win !");
        p1Win++;
        break;
    case -1: // P2�� �̰��� ��
        gotoxy(resultX[2], resultY);
        printf("P2 (X) Win !");
        p2Win++;
        break;
    }
    gotoxy(MENU_MAX_X / 3 + 4, resultY - 1);
    printf("P1: %d, P2: %d, Draw: %d", p1Win, p2Win, draw); // ��������� ���� ������ (�� ���� �����ؼ�)
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
        case SPACE: // �����̽��� ���͸� ������ while�� ����
        case ENTER:
            loop = 0;
            break;
        }
    }
    fp = fopen("pvp.txt", "w");
    fprintf(fp, "P1: %d, P2: %d, Draw: %d", p1Win, p2Win, draw); // pvp ���Ͽ� ���� ���� �ۼ�����
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