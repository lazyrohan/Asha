//d3dut_globle.h
//Include globle files for D3D11 programe and simple usefull utinity functions

#pragma once

#ifndef _D3DUT_GLOBLE_H_
#define _D3DUT_GLOBLE_H_

//Include D3D11 libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"D3DCompiler.lib")

//Header files
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

//Standard c++ headers
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
using namespace std;

//Debug options
#ifndef _DEBUG_UT_ON
#define _DEBUG_UT_ON
#endif
#ifdef _DEBUG_UT_ON
#define UT_LOG_ON true
#define NV_DEBUG_ON true
#else
#define UT_LOG_ON flase
#define NV_DEBUG_ON false
#endif

//Setup NV PMAPI
//#define NV_INITGUID
//#include <NvPmApi.Manager.h>


//Some usefull functions
namespace utg
{
//Log to file function
void log2File(string funcName,string funcInfo,bool logFlag);

//A variable to string function
template <class T> string var2Str(T varName)	
{
	stringstream ss;
	ss<<varName;
	return ss.str();
};

//A litte timer
//Timer start
void tmstat(time_t& time);
//Timer end and return time cost by seconds
float tmendt(time_t starttime);
};

#endif
