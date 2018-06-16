#include "mindwave.h"
#include "eyedecting.h"
#include "thread"

void main() {
	int temp;
	VIDEO video;
	MINDWAVE mw;
	thread t1(&mw.MEDD_ATTD);
	
	video.videoPlay();
	t1.join();

	system("pause");
}