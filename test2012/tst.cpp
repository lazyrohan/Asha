// tst.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <iomanip>
#include <string>
#include "directxmath.h"
using namespace std;
using namespace DirectX;
XMMATRIX mx;
XMMATRIX GetMx(void);
int main(void)
{
	cout<<"Size of xmmatrix:     "<<sizeof(XMMATRIX)<<endl;
	cout<<"Size of xmvector:     "<<sizeof(XMVECTOR)<<endl;
	cout<<"Size of float:        "<<sizeof(float)<<endl;
	cout<<"Size of double:       "<<sizeof(double)<<endl;
	cout<<"Size of long:         "<<sizeof(long)<<endl;
	cout<<"Size of int:          "<<sizeof(int)<<endl;
	cout<<setprecision(20)<<"Self defined PI: "<<XM_PI<<endl;

	cout<<"Rotation matrix function test:"<<endl;
	XMVECTOR rotaAix=XMVectorSet(0.8f,0.3f,0.1f,0.0f);
	XMMATRIX tstmx=XMMatrixIdentity();
	XMMATRIX mx1=XMMatrixIdentity();
	XMMATRIX mx2=XMMatrixIdentity();
	mx=tstmx*mx1*mx2;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout<<setw(16)<<setfill('\0')<<setprecision(10)<<(GetMx()).r[i].m128_f32[j]<<" ";
		}
		cout<<endl;
	}

	cout<<"Camera matrix function test: "<<endl;
	/*
	float camPos[4]={0.8f,0.7f,0.9f,1.0f};
	float objPos[4]={0.0f,0.0f,0.0f,1.0f};
	float upPos[4]={0.0f,1.0f,0.0f,1.0f,};
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout<<setw(16)<<setfill('\0')<<setprecision(10)<<getCameraMat(camPos,objPos,upPos).r[i].m128_f32[j]<<" ";
		}
		cout<<endl;
	}
	*/
	string str="\0";
	cin>>str;
	return 0;
}
XMMATRIX GetMx(void)
{
	return mx;
}


