#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

//✨windows 접근 헤더, c 헤더, 표준 c 헤더

#pragma warning(disable:4996)
//✨scanf 오류 방지 코드

//----- console color -----
#define BLACK	0x0
#define BLUE	0x1
#define GREEN	0x2
#define CYAN	0x3
#define RED		0x4
#define MAGENTA	0x5
#define BROWN	0x6
#define WHITE	0x7

//✨8가지의 색이 정의되어있다. 0부터.. 7까지
//✨검정, 파랑, 초록, 하늘, 빨강, 분홍, 갈색, 흰색


//----- console color -----

int i2c_address_data_masterWrite(HWND hWind, HDC hDC, int origin_x, int origin_y, int addr, int data, char read_write_mode);
int i2c_address_data_masterRead(HWND hWind, HDC hDC, int origin_x, int origin_y, int addr, int data, char read_write_mode);

//✨ i2c주소 데이터 마스터... "쓰기", "읽기".
//✨ 함수 파라메터는 완전히 똑같은듯?

int windth_x = 80; //✨x = 80
int windth_y = 80; //✨y = 80
int windth_gap = 20; //✨차이 = 20;

int main(void)
{
	HWND hWind; //✨IDK
	HDC hDC; //✨IDK
	HANDLE hConsole; //✨IDK

	char chComm[16];
	int i2c_address = 0xaa; //✨i2c 주소는 0xaa
	int i2c_write_data = 0x55; //✨0x55를 쓸 것
	int i2c_read_data = 0xb6; //✨0xb6를 읽을 것... 근데 읽을 것을 지정할 수가 있나?

	hWind = GetForegroundWindow(); //✨윈도우를 얻어온다
	hDC = GetDC(hWind); //✨hWind를 getDC에 넘긴다
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //✨STD_OUTPUT_HANDLE을 GetStdHandle에 넘긴 반환값을 콘솔에 넣는다.

	do { //✨아래의 코드는 어떤 조건까지 무한 반복합니다. 아직은 모르겠네요
		printf("---command:"); //✨"커맨드:"를 출력

		scanf(" %s", chComm); //✨입력값을 chComm으로 넘김. chComm의 길이는 최대 16자 (오버플로우시 어떻게 될까?)
		switch (chComm[0]) { //✨chComm의 첫글자를 읽어와 switch문으로 넘긴다
		case 'a': // 콘솔 색상 변경(배경:밝은힌색, 전경:어두운검은색)
				//💬✨값이 a라면...
			system("color f0"); //✨cmd 명령어 color f0를 실행한다.
			break; //✨끝
		case 'b': // 콘솔창 크기 변경
				//💬✨값이 b라면
			system("mode con:cols=240 lines=50"); //✨cmd 명령어 mode con:cols=240 lines=50을 실행한다. ✨결과적으로 창이 커진다
			break; //✨끝
		case 'c': // 콘솔 지우기
				//💬✨값이 c라면
			system("cls"); //✨cmd 명령어 cls를 보낸다. ✨결과적으로 창의 값이 초기화된다
			break; //✨끝
		case 'd': // i2c : address[write mode](green color)-ack[low] : data(green color)-ack[low]
				//✨값이 d라면?...
			i2c_address_data_masterWrite(hWind, hDC, 50, 100, i2c_address, i2c_write_data, 'w');
			//✨마스터 쓰기📝를 실행한다.
			//✨아까 의문이였던 char read_write_mode는 'w'를 넣는다.

			//✨i2c_address는 바뀌지 않음... 값은 0x55;
			//✨i2c_write_data도 바뀌지 않음... 값은 0xaa;


			printf("i2c addres[write mode](green color)-ack[low]=0x%02x, data(green color)-ack[low]=0x%02x\n", i2c_address, i2c_write_data);
			//✨출력... i2c address[write mode](green color)-ack[low]0x%02x (16진수로 2자리), data(green color)-ack[low]=0x%02x ... 새 줄 생성

			//✨2자리의 16진수 값 두개는...
			//✨i2c_address와 i2c_write_data... 해당 값은 위에서 정의되었으며 실행 이후로 전혀 바뀌지 않았다.
			//✨ic2_address 0x55;
			//✨ic2_write_data 0xaa;


			break; //✨끝
		case 'e': // i2c : address[read mode](green color)-ack[low] : data(yellow color)-Nack[high]
				//✨값이 e라면...?

				//✨추론 : 해당 커맨드를 구분하는 글자는 어떤 약어가 아니라 그냥 abcde...순이다.



			i2c_address_data_masterRead(hWind, hDC, 50, 100, i2c_address, i2c_read_data, 'r');

			//✨masterRead로 데이터를 보낸다.

			//✨i2c_address는 여전히 0x55며
			//✨i2c_read_data 또한 여전히 0xb6이다

			//✨char read_write_mode는 'r'을 넣는다

			printf("i2c addres[read mode](green color)-ack[low]=0x%02x, data(yellow color)-Nack[high]=0x%02x\n", i2c_address, i2c_read_data);
			//✨출력... i2c address[read mode](green color)-ack[low]0x%02x (16진수로 2자리), data(green color)-Nack[high]=0x%02x ... 새 줄 생성
			break;
		default:
			//✨일반적인 경우
			break; //✨🎆탈출
		}
	} while ('x' != chComm[0]); //✨chComm의 첫번째 데이터 영역이 x일 때 까지 반복한다.

	//✨만약 x라면 위의 do... while문이 종료된다

	ReleaseDC(hWind, hDC); //✨DC릴리즈
	CloseHandle(hConsole); //✨콘솔 핸들러 닫기

	return(0);
}

int i2c_address_data_masterWrite(HWND hWind, HDC hDC, int origin_x, int origin_y, int addr, int data, char read_write_mode)
{
	int base_x, base_y; //✨시작 x, y 지정
	int i; //✨i 생성. for문에서 안 쓰려고 미리 지정하는 것일 수도 있음
	int m, d; //✨ m과 d 생성. 사용처는 후술
	int address; //✨주소
	int writedata; //✨쓸 데이터
	int chComp; //✨chComp... 원일 불명

	base_x = origin_x; base_y = origin_y;

	/*

		✨밖에서 origin으로 들어온 값은 그냥 base에 넣는다. 이유는 모르겠음. 아마 덧씌우는 용도일 가능성이 있음

	*/

	// idle(black)



	m = 0; //✨m은 0이다. (위에서 하지 않은 초기화 수행)

	//🎈 대기 비트
	for (i = 0; i < windth_x; i++) {	// SCL
		//✨i가 0부터... x 두께까지 반복한다
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(25, 25, 25));
		//✨픽셀 지정... 회색으로 추정

		//✨기존부터... 두께까지.
	}
	for (i = 0; i < windth_x; i++) {	// SDA
		//✨두께만큼 반복
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(25, 25, 25));
		//✨갭만큼 y를 띄워서 그린다.
	}
	// start(red)
	m = 1;

	//✨m이 1이 된다. (여기의 색코드는 235,0,0으로 거의 빨간색)



	//🎈 시작 비트
	for (i = 0; i < ((windth_x * 3) / 4); i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(235, 0, 0));

		//✨0부터 ((windth_x * 3) / 4)까지 반복 (💎SCL 작성)
	}
	for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(235, 0, 0));

		//✨((windth_x * 3 / 4))부터 windth_x까지 반복... (💎SCL 작성)
	}
	for (i = 0; i < ((windth_x * 2) / 4); i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(235, 0, 0));

		//✨0부터 ((windth_x * 2) / 4)까지 반복 (💎SDA 작성)
	}
	for (i = ((windth_x * 2) / 4); i < windth_x; i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(235, 0, 0));

		//✨((windth_x * 2) / 4)부터 windth_x까지 반복 (💎SDA 작성)
	}

	// address(green)

	//🎈주소 연산
	if ('w' == read_write_mode) {
		//✨쓰기 모드가 w라면
		address = (addr & 0xfe) + 0x00; //✨addr과 0xFE (0b1111 1110)의 bitwise AND에 0을 더한다. addr은 0x55
	}
	else { //✨그게 아니라면
		address = (addr & 0xfe) + 0x01; //✨addr과 0xFE의 AND후에 1을 더한다. 그게 이제 주소
	}
	chComp = 0x80; //✨chComp는 0x80... 0b1000 0000이다
	m = 2; //✨m은 2이다

	//🎈8개의 비트 전송... 주소를 보낸다
	for (d = 0; d < 8; d++) {
		//✨d는 0부터 8까지 반복한다
		if ((address & chComp) == chComp) {
			//주솟값과 비굣값의 AND 결과가 비굣값과 같다면... 그러니까 특정 위치의 비트가 맞다면
			for (i = 0; i < windth_x; i++) {	// SDA
				//✨SDA에 일정 길이만큼 그린다. 🥦초록
				SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(0, 235, 0));

				//🎈비트가 true라면... 일정 길이 만큼 한칸 내리기 + 차이만큼 내리기로 선을 그린다 (위쪽선)
			}
		}
		else {
			//✨데이터가 안맞는다면
			for (i = 0; i < windth_x; i++) {	// SDA
				//✨SDA에 쓴다... 아래로 가네
				//🎈비트가 false라면... 일정 길이만큼 두칸 내리기 + 차이만큼 내리기로 선을 그린다 (아랫쪽 선)
				SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(0, 235, 0));
			}
		}//✨비교문 종료


		//🎈아래의 세 for문은 CLK을 형상화한 것으로 보인다. 🥩의미 없음
		for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
			//✨원래 길이의 4분의 1만큼 그림 (초록 SCL)
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 235, 0));
		}
		for (i = ((windth_x * 1) / 4); i < ((windth_x * 3) / 4); i++) {	// SCL
			//✨원래 길이의 4분의 1만큼부터 3분의 4만큼 초록SCL 그림...
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(0, 235, 0));
		}
		for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
			//✨나머지를 그림
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 235, 0));
		}
		m += 1; //✨m의 값을 올림 --> m은 결과적으로 10이됨
		chComp >>= 1; //✨chComp를 오른쪽으로 옮겨서 비교함
	}

	// ack(blue)

	//🎈위쪽 SCL 부분에 클럭마냥 파란색으로 그린다 CLK과 동기화된 것처럼 보이며 실제로 의미를 가지지 않는다
	for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
		//✨0부터 4분의 1만큼 그림... SCL 파랑
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 0, 235));
	}
	for (i = ((windth_x * 1) / 4); i < ((windth_x * 3) / 4); i++) {	// SCL
		//✨4분의 1부터 4분의 3만큼 그림... SCL 파랑
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(0, 0, 235));
	}
	for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
		//✨4분의 3부터 끝까지 그림... SCL 파랑
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 0, 235));
	}
	// ack = OK
	//🎈SDA에 그린다. 반드시 내려가있다. 그 이유는 OK기 때문이다
	for (i = 0; i < windth_x; i++) {	// SDA
		//✨한줄을 그림
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(0, 0, 235));
	}

	// data[write](green)
	writedata = data; //✨writedata에 data를 집어넣음 0xaa가 들어왔다
	chComp = 0x80; //✨비교값 0x80...
	m += 1; //✨m에 1이 추가됨 (11이 됨)
	for (d = 0; d < 8; d++) {
		//✨8개 반복함
		// SDA
		if ((writedata & chComp) == chComp) {
			//-----코드추가-----...DONE!
				//주솟값과 비굣값의 AND 결과가 비굣값과 같다면... 그러니까 특정 위치의 비트가 맞다면
			for (i = 0; i < windth_x; i++) {	// SDA
				//✨SDA에 일정 길이만큼 그린다. 🥦초록
				SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(0, 235, 0));
			}
		}
		else {
			//✨데이터가 안맞는다면
			for (i = 0; i < windth_x; i++) {	// SDA
				//✨SDA에 쓴다... 아래로 가네
				SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(0, 235, 0));
			}
		}
		// SCL


		//🎈아래의 세 for문은 CLK을 형상화한 것으로 보인다. 🥩의미 없음
		for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
			//✨원래 길이의 4분의 1만큼 그림 (초록 SCL)
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 235, 0));
		}
		for (i = ((windth_x * 1) / 4); i < ((windth_x * 3) / 4); i++) {	// SCL
			//✨원래 길이의 4분의 1만큼부터 3분의 4만큼 초록SCL 그림...
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(0, 235, 0));
		}
		for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
			//✨나머지를 그림
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 235, 0));
		}
		//-----코드추가-----... DONE!

		m += 1; //✨친절하게도 누가 비트를 세주고 있다 (m은 19가된다)
		chComp >>= 1; //✨데이터 이동도 해주고있다
	}

	// ack(blue)

	//🎈SCL부분의 CLK 동작? 같은 응답을 나타내는 부분. 의미 없음 (거의 마지막)
	for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 0, 235));
	}
	for (i = ((windth_x * 1) / 4); i < ((windth_x * 3) / 4); i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(0, 0, 235));
	}
	for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 0, 235));
	}
	// ack = OK
	for (i = 0; i < windth_x; i++) {	// SDA

		//-----코드추가-----
		//✨한줄을 그림
		//🎈SDA의 ACK를 동작하는 부분. write는 반드시 OK이므로 내려가있어야 한다. windth_y에 2를 곱하면 내려가고, 1을 곱하면 올라온다
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(0, 0, 235));
	}

	// stop(red)
	m += 1;//🎈m을 1 올린다. m은 20이 된다 

	//✨빨간 비트를 내보낸다
	//🎈SCL (상단)에 내려갔다 올라갔다 하는 비트를 넣어준다
	for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(235, 0, 0)); //✨windth_y에 1을 곱하면 내려감
	}
	for (i = ((windth_x * 1) / 4); i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(235, 0, 0)); //✨windth_y에 0을 곱하면 올라감
	}

	//🎈SDA용 STOP BIT
	for (i = 0; i < ((windth_x * 2) / 4); i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(235, 0, 0));
	}
	for (i = ((windth_x * 2) / 4); i < windth_x; i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(235, 0, 0));
	}


	//✨IDLE을 내보낸다
	// idle(black)
	m += 1;
	for (i = 0; i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(25, 25, 25));
	}
	for (i = 0; i < windth_x; i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(25, 25, 25));
	}

	return(0);
}

int i2c_address_data_masterRead(HWND hWind, HDC hDC, int origin_x, int origin_y, int addr, int data, char read_write_mode)
{
	int base_x, base_y;
	int i;
	int m, d;
	int address;
	int readdata;
	int chComp;

	base_x = origin_x; base_y = origin_y;
	// idle(black)
	m = 0;
	for (i = 0; i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(25, 25, 25));
	}
	for (i = 0; i < windth_x; i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(25, 25, 25));
	}
	// start(red)

	//-----코드추가-----...DONE!


	m = 1;

	//✨m이 1이 된다. (여기의 색코드는 235,0,0으로 거의 빨간색)



	/*

		🐋 START BIT를 보내는 부분

	*/

	//🎈 시작 비트
	for (i = 0; i < ((windth_x * 3) / 4); i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(235, 0, 0));

		//✨0부터 ((windth_x * 3) / 4)까지 반복 (💎SCL 작성)
	}
	for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(235, 0, 0));

		//✨((windth_x * 3 / 4))부터 windth_x까지 반복... (💎SCL 작성)
	}
	for (i = 0; i < ((windth_x * 2) / 4); i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(235, 0, 0));

		//✨0부터 ((windth_x * 2) / 4)까지 반복 (💎SDA 작성)
	}
	for (i = ((windth_x * 2) / 4); i < windth_x; i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(235, 0, 0));

		//✨((windth_x * 2) / 4)부터 windth_x까지 반복 (💎SDA 작성)
	}

	/*

		🐋 START BIT 종료

	*/






	/*

		🐋🐋 주소값 전송 부분...

		몰랐던 게 있는데, address에 들어가는 addr 값을 왜 0xFE를 하는지 알았다.

		그 이유는 주소값은 7비트로 보내져야 하기 때문이다. 이는 설명서에 나와있었는데, 그냥 신경쓰지 않고 지나갔지만 역시 중요한 부분이었다.
		왜 주소비트를 8개 보낼까? 왜 read write 비트를 보내지 않을까?

		그 이유는 받아온 addr값에 0xFE를 bitwise AND 하여 마지막 비트를 손상시키고 write일 경우에는 0을 넣고
		read일 경우에는 1을 넣기 때문이다. 이런 작업을 하는 이유는 read를 하고 싶으면 read write 비트는 1이 되기 때문이었다.

	*/

	// address(green)
	if ('w' == read_write_mode) {
		address = (addr & 0xfe) + 0x00;
	}
	else {
		address = (addr & 0xfe) + 0x01;
	}
	chComp = 0x80;
	m = 2;

	//-----코드추가-----...DONE!
	//🎈8개의 비트 전송... 주소를 보낸다
	for (d = 0; d < 8; d++) {
		//✨d는 0부터 8까지 반복한다
		if ((address & chComp) == chComp) {
			//주솟값과 비굣값의 AND 결과가 비굣값과 같다면... 그러니까 특정 위치의 비트가 맞다면
			for (i = 0; i < windth_x; i++) {	// SDA
				//✨SDA에 일정 길이만큼 그린다. 🥦초록
				SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(0, 235, 0));

				//🎈비트가 true라면... 일정 길이 만큼 한칸 내리기 + 차이만큼 내리기로 선을 그린다 (위쪽선)
			}
		}
		else {
			//✨데이터가 안맞는다면
			for (i = 0; i < windth_x; i++) {	// SDA
				//✨SDA에 쓴다... 아래로 가네
				//🎈비트가 false라면... 일정 길이만큼 두칸 내리기 + 차이만큼 내리기로 선을 그린다 (아랫쪽 선)
				SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(0, 235, 0));
			}
		}//✨비교문 종료


		//🎈아래의 세 for문은 CLK을 형상화한 것으로 보인다. 🥩의미 없음
		for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
			//✨원래 길이의 4분의 1만큼 그림 (초록 SCL)
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 235, 0));
		}
		for (i = ((windth_x * 1) / 4); i < ((windth_x * 3) / 4); i++) {	// SCL
			//✨원래 길이의 4분의 1만큼부터 3분의 4만큼 초록SCL 그림...
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(0, 235, 0));
		}
		for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
			//✨나머지를 그림
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 235, 0));
		}
		m += 1; //✨m의 값을 올림 --> m은 결과적으로 10이됨
		chComp >>= 1; //✨chComp를 오른쪽으로 옮겨서 비교함
	}


	/*

		🐋🐋 주소 비트 전송 종료

	*/



	//🌿 DMZ. 아무 코드도 있어선 안된다


	/*

		🐋🐋🐋 응답 비트 전송...

	*/


	// ack(blue)

	//-----코드추가-----...DONE!



	//🎈위쪽 SCL 부분에 클럭마냥 파란색으로 그린다 CLK과 동기화된 것처럼 보이며 실제로 의미를 가지지 않는다
	for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
		//✨0부터 4분의 1만큼 그림... SCL 파랑
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 0, 235));
	}
	for (i = ((windth_x * 1) / 4); i < ((windth_x * 3) / 4); i++) {	// SCL
		//✨4분의 1부터 4분의 3만큼 그림... SCL 파랑
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(0, 0, 235));
	}
	for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
		//✨4분의 3부터 끝까지 그림... SCL 파랑
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 0, 235));
	}
	// ack = OK
	//🎈SDA에 그린다. 반드시 내려가있다. 그 이유는 OK기 때문이다. 다음 ACK에서는 반드시 올라와야 한다
	for (i = 0; i < windth_x; i++) {	// SDA
		//✨한줄을 그림
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(0, 0, 235));
	}




	/*

		🐋🐋🐋 응답 비트 종료

	*/








	//🌿 DMZ. 아무 코드도 있어선 안된다






	/*

		🐋🐋🐋🐋 데이터 읽기 비트 전송...

	*/


	// data[read](yellow)
	readdata = data;
	chComp = 0x80;
	m += 1;

	//-----코드추가-----...DONE!


	//🎈여기서 데이터는 쓰기의 경우 보내고, 읽기의 경우 받아와야 하지만,
	//해당 프로그램에서 데이터를 받을 수 없기 때문에 읽기를 상정하여 0xB6이 들어왔다는 가정 후
	//프로그램을 테스트 하는 것으로 보인다. 그렇기 때문에 코드는 write와 같고 readdata에
	//데이터를 넣어서 그래픽으로 표현한다.
	for (d = 0; d < 8; d++) {
		//✨8개 반복함
		// SDA
		if ((readdata & chComp) == chComp) {
			//-----코드추가-----...DONE!
				//주솟값과 비굣값의 AND 결과가 비굣값과 같다면... 그러니까 특정 위치의 비트가 맞다면
			for (i = 0; i < windth_x; i++) {	// SDA
				//✨SDA에 일정 길이만큼 그린다. 🧀이번엔 노랑을 보낸다
				SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(235, 235, 0));
			}
		}
		else {
			//✨데이터가 안맞는다면
			for (i = 0; i < windth_x; i++) {	// SDA
				//✨SDA에 쓴다... 아래로 가네
				SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(235, 235, 0));
			}
		}
		// SCL


		//🎈아래의 세 for문은 CLK을 형상화한 것으로 보인다. 🥩의미 없음
		for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
			//✨원래 길이의 4분의 1만큼 그림 (초록 SCL)
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 235, 0));
		}
		for (i = ((windth_x * 1) / 4); i < ((windth_x * 3) / 4); i++) {	// SCL
			//✨원래 길이의 4분의 1만큼부터 3분의 4만큼 초록SCL 그림...
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(0, 235, 0));
		}
		for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
			//✨나머지를 그림
			SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 235, 0));
		}
		//-----코드추가-----... DONE!

		m += 1; //✨친절하게도 누가 비트를 세주고 있다 (m은 19가된다)
		chComp >>= 1; //✨데이터 이동도 해주고있다
	}




	/*

		🐋🐋🐋🐋 데이터 읽기 비트 종료

	*/





	//🌿 DMZ. 아무 코드도 있어선 안된다




	/*

		🐋🐋🍜🐋🐋 응답 비트 전송...

	*/


	// Nack(blue)

	//-----코드추가-----...DONE!



	//🎈SCL부분의 CLK 동작? 같은 응답을 나타내는 부분. 의미 없음 (거의 마지막)


	//🎈해당 코드는 SCL(상단)의 왔다갔다 하는 코드
	for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 0, 235));
	}
	for (i = ((windth_x * 1) / 4); i < ((windth_x * 3) / 4); i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(0, 0, 235));
	}
	for (i = ((windth_x * 3) / 4); i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(0, 0, 235));
	}
	// NACK!
	//🎈이번엔 NACK이여야한다
	for (i = 0; i < windth_x; i++) {	// SDA

		//-----코드추가-----
		//✨한줄을 그림
		//🎈SDA의 ACK를 동작하는 부분. write는 반드시 OK이므로 내려가있어야 한다. windth_y에 2를 곱하면 내려가고, 1을 곱하면 올라온다
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(0, 0, 235));
	}



	/*

		🐋🐋🍜🐋🐋 응답 비트 종료

	*/



	//🌿 DMZ. 아무 코드도 있어선 안된다



	/*

		🐋🐋🍜🍜🐋🐋 STOP BIT 전송...

	*/

	// stop(red)
	m += 1;

	//-----코드추가-----...DONE!

	//🎈m을 1 올린다. m은 20이 된다 

	//✨빨간 비트를 내보낸다
	//🎈SCL (상단)에 내려갔다 올라갔다 하는 비트를 넣어준다
	for (i = 0; i < ((windth_x * 1) / 4); i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1)), RGB(235, 0, 0)); //✨windth_y에 1을 곱하면 내려감
	}
	for (i = ((windth_x * 1) / 4); i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(235, 0, 0)); //✨windth_y에 0을 곱하면 올라감
	}

	//🎈SDA용 STOP BIT
	for (i = 0; i < ((windth_x * 2) / 4); i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 2) + windth_gap), RGB(235, 0, 0));
	}
	for (i = ((windth_x * 2) / 4); i < windth_x; i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(235, 0, 0));
	}


	/*

		🐋🐋🍜🍜🐋🐋 STOP BIT 전송...

	*/


	// idle(black)
	m += 1;
	for (i = 0; i < windth_x; i++) {	// SCL
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 0)), RGB(25, 25, 25));
	}
	for (i = 0; i < windth_x; i++) {	// SDA
		SetPixel(hDC, (base_x + (m * windth_x) + i), (base_y + (windth_y * 1) + windth_gap), RGB(25, 25, 25));
	}

	return(0);
}

