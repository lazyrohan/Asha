//App main program

#include "AppSysClass.h"
#include "AshaGraphClass.h"


#pragma warning(suppress: 28251)
int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPWSTR lpCmdLine,int nCmdShow)
{
	//Shutdown unused parameter compiler warning
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	//New AppSysClass
	AppSysClass* AppSys;
	AppSys = new AppSysClass;
	if(!AppSys)
	{
		return false;
	}

	LPCSTR   AppName="Asha:Practice";
	HCURSOR  hAppCursor=NULL;
	HICON    hAppIcon=NULL;
	RECT     Apprc={0,0,800,600};

	AppSys->Initialize(hInstance,nCmdShow,AppName,hAppCursor,hAppIcon,Apprc);
	//Run process
	AppSys->Run();
	//Exit windows process
	int exitmsg=0;
	exitmsg=AppSys->Exit();	
	delete AppSys;
	AppSys=NULL;

	return exitmsg;
}
