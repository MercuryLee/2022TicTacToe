// 
// 3 * 3의 간단한 보드게임인 틱택토를 플레이할 수 있는 프로그램
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
	// 메인함수 작동 방식
	// 
	// screenStatus라는 변수를 선언해서 모든 화면에 이 변수의 주소값을 매개변수로 보냄
	// 함수 내에서 포인터를 통해 원하는 화면의 screenStatus값으로 screenStatus의 값을 변화시킴
	// 변수의 값을 메인변수에서 switch case 문을 통해 인식하고, 해당 화면으로 넘겨줌
	// 

	while (loop) {
		switch (screenStatus) {
		case 0:
			loop = 0; // 프로그램 끝내기
			break;
		case 1:
			drawStart(&screenStatus); // 시작 화면 ( 틱택토 글씨 나오는 곳 ) 
			break;
		case 2:
			drawDescription(&screenStatus); // 틱택토 설명 보여주는 화면
			break;
		case 3:
			drawMenu(&screenStatus); // 시작 페이지에서 한번 클릭하면 나오는 메뉴 화면 ( 3개의 선택지 )
			break;
		case 4:
			drawPlayerChoose(&screenStatus); // 1P, 2P로 할지 선택하는 화면
			break;
		case 5:
			pveGamePlay(&screenStatus, board); // 1P 게임 플레이 하는 화면 ( 내에서 AI 코드 돌아감 )
			break;
		case 6:
			pveGameResult(&screenStatus, board); // 1P 게임 결과 
			break;
		case 7:
			pvpGamePlay(&screenStatus, board); // 2P 게임 플레이 하는 화면
			break;
		case 8:
			pvpGameResult(&screenStatus, board); // 2P 게임 결과
			break;
		}
	}
	return 0;
}