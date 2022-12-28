// 
// 3 * 3�� ������ ��������� ƽ���並 �÷����� �� �ִ� ���α׷�
// 

#include "pve.h"
#include "pvp.h"
#include "constants.h"
#include "commonFunc.h"

int main() {
	int screenStatus = 1, loop = 1;
	int board[4][4];
	reSizeConsole(MENU_MAX_X, MENU_MAX_Y);
	clearCursor(); 

	//
	// �����Լ� �۵� ���
	// 
	// screenStatus��� ������ �����ؼ� ��� ȭ�鿡 �� ������ �ּҰ��� �Ű������� ����
	// �Լ� ������ �����͸� ���� ���ϴ� ȭ���� screenStatus������ screenStatus�� ���� ��ȭ��Ŵ
	// ������ ���� ���κ������� switch case ���� ���� �ν��ϰ�, �ش� ȭ������ �Ѱ���
	// 

	while (loop) {
		switch (screenStatus) {
		case 0:
			loop = 0; // ���α׷� ������
			break;
		case 1:
			drawStart(&screenStatus); // ���� ȭ�� ( ƽ���� �۾� ������ �� ) 
			break;
		case 2:
			drawDescription(&screenStatus); // ƽ���� ���� �����ִ� ȭ��
			break;
		case 3:
			drawMenu(&screenStatus); // ���� ���������� �ѹ� Ŭ���ϸ� ������ �޴� ȭ�� ( 3���� ������ )
			break;
		case 4:
			drawPlayerChoose(&screenStatus); // 1P, 2P�� ���� �����ϴ� ȭ��
			break;
		case 5:
			pveGamePlay(&screenStatus, board); // 1P ���� �÷��� �ϴ� ȭ�� ( ������ AI �ڵ� ���ư� )
			break;
		case 6:
			pveGameResult(&screenStatus, board); // 1P ���� ��� 
			break;
		case 7:
			pvpGamePlay(&screenStatus, board); // 2P ���� �÷��� �ϴ� ȭ��
			break;
		case 8:
			pvpGameResult(&screenStatus, board); // 2P ���� ���
			break;
		}
	}
	return 0;
}