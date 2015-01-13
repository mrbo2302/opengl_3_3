#include "FrameWork.h"
int main()
{
	//Initialize the FrameWork
	FrameWork* framework = new FrameWork();
	framework->Initialize();
	//update our framework
	framework->Run();

	delete framework;
	framework = NULL;

	return 0;
}