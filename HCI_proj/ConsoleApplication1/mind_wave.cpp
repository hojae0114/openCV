#include "mindwave.h"


int MINDWAVE::MEDD_ATTD(void) {
	char *comPortName = NULL;            //활성화된 comport값으로 수정된 값을 가질 변수
	int connectionld = 0;            //연결된장치의 ID
	int packetsRead = 0;            //데이터를 읽어 들이는 변수
	int state = 0;               //연결된 상태 값을 받는 변수
	int ATTSt = 0;               //Attention value의 상태변수
	int MEDSt = 0;             //Meditation value의 상태변수
	int ATTD = 0;               //Attention 데이터 값을 받는 변수
	int MEDD = 0;               //Meditation 데이터 값을 받는 변수

	connectionld = TG_GetNewConnectionId();//connectionId 값에 연결될 기기에 관한 새로운 ID를 부여한다

	comPortName = "\\\\.\\COM3";

	state = TG_Connect(connectionld, comPortName, TG_BAUD_57600, TG_STREAM_PACKETS);
	//연결된기기의 ID, comport 이름 , baudrate값 ,data포맷타입으로 처리되며
	//return 값이 0 일 때 성공적인 연결상태가 되며
	//return 값이 -1 일 때 connectionId 에 제대로 된 입력 값을 받아오지 못한 경우
	//return 값이 -2 일 때 serialport 연결이 되지 않았거나 잘못된 COM(*)를 입력받은 경우
	//return 값이 -3 일 때 지정된 baudrate 값과 맞지 않은 입력 값을 받은 경우
	//return 값이 -4 일 때 serial data포맷이 적합하지 않은 경우입니다.
	printf("%d\n", state);

	

	while (1)
	{
		packetsRead = TG_ReadPackets(connectionld, 1);//연결된 기기에서 받은 데이터를 비트의 열로 변환하여 직렬로 전송합니다.



		ATTSt = TG_GetValueStatus(connectionld, TG_DATA_ATTENTION);//기본적으로 약 1초 간격으로 데이터처리가 되며, 1로 값이 나오게 되는 경우에만 처리된 데이터 값이 나옵니다.


		MEDSt = TG_GetValueStatus(connectionld, TG_DATA_MEDITATION); //기본적으로 약 1초 간격으로 데이터처리가 되며, 1로 값이 나오게 되는 경우에만 처리된 데이터 값이 나옵니다.


		if ((ATTSt != 0) && (MEDSt != 0))


		{
			ATTD = TG_GetValue(connectionld, TG_DATA_ATTENTION); //ATTD 값에 연결된 기기의 ID, 변환할 데이터형태로 구성된 값을 받습니다.



			MEDD = TG_GetValue(connectionld, TG_DATA_MEDITATION);//MEDD 값에 연결된 기기의 ID, 변환할 데이터형태로 구성된 값을 받습니다.

			printf("ATT =%3d\tMED =%3d\tMEDD-ATTD = %3d\n", ATTD, MEDD, MEDD - ATTD);
			printf("\n");
		}
		if (MEDD - ATTD > 20) {
			printf("집중하세요!");
		}
	}
}