#include "mindwave.h"


int MINDWAVE::MEDD_ATTD(void) {
	char *comPortName = NULL;            //Ȱ��ȭ�� comport������ ������ ���� ���� ����
	int connectionld = 0;            //�������ġ�� ID
	int packetsRead = 0;            //�����͸� �о� ���̴� ����
	int state = 0;               //����� ���� ���� �޴� ����
	int ATTSt = 0;               //Attention value�� ���º���
	int MEDSt = 0;             //Meditation value�� ���º���
	int ATTD = 0;               //Attention ������ ���� �޴� ����
	int MEDD = 0;               //Meditation ������ ���� �޴� ����

	connectionld = TG_GetNewConnectionId();//connectionId ���� ����� ��⿡ ���� ���ο� ID�� �ο��Ѵ�

	comPortName = "\\\\.\\COM3";

	state = TG_Connect(connectionld, comPortName, TG_BAUD_57600, TG_STREAM_PACKETS);
	//����ȱ���� ID, comport �̸� , baudrate�� ,data����Ÿ������ ó���Ǹ�
	//return ���� 0 �� �� �������� ������°� �Ǹ�
	//return ���� -1 �� �� connectionId �� ����� �� �Է� ���� �޾ƿ��� ���� ���
	//return ���� -2 �� �� serialport ������ ���� �ʾҰų� �߸��� COM(*)�� �Է¹��� ���
	//return ���� -3 �� �� ������ baudrate ���� ���� ���� �Է� ���� ���� ���
	//return ���� -4 �� �� serial data������ �������� ���� ����Դϴ�.
	printf("%d\n", state);

	

	while (1)
	{
		packetsRead = TG_ReadPackets(connectionld, 1);//����� ��⿡�� ���� �����͸� ��Ʈ�� ���� ��ȯ�Ͽ� ���ķ� �����մϴ�.



		ATTSt = TG_GetValueStatus(connectionld, TG_DATA_ATTENTION);//�⺻������ �� 1�� �������� ������ó���� �Ǹ�, 1�� ���� ������ �Ǵ� ��쿡�� ó���� ������ ���� ���ɴϴ�.


		MEDSt = TG_GetValueStatus(connectionld, TG_DATA_MEDITATION); //�⺻������ �� 1�� �������� ������ó���� �Ǹ�, 1�� ���� ������ �Ǵ� ��쿡�� ó���� ������ ���� ���ɴϴ�.


		if ((ATTSt != 0) && (MEDSt != 0))


		{
			ATTD = TG_GetValue(connectionld, TG_DATA_ATTENTION); //ATTD ���� ����� ����� ID, ��ȯ�� ���������·� ������ ���� �޽��ϴ�.



			MEDD = TG_GetValue(connectionld, TG_DATA_MEDITATION);//MEDD ���� ����� ����� ID, ��ȯ�� ���������·� ������ ���� �޽��ϴ�.

			printf("ATT =%3d\tMED =%3d\tMEDD-ATTD = %3d\n", ATTD, MEDD, MEDD - ATTD);
			printf("\n");
		}
		if (MEDD - ATTD > 20) {
			printf("�����ϼ���!");
		}
	}
}