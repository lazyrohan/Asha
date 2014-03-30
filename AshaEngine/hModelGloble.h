//hModelGloble.h
//Globe header files and basic data type for model class

#pragma once

#ifndef _HMODELGLOBLE_H_
#define _HMODELGLOBLE_H_

//Include standard cpp header files
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
using namespace std;

//Switch the log to file actions 
#define LOG_ON true
//Input data element flag
#define ELEMENT_VERTEX       0
#define ELEMENT_FACEINDEX    1

namespace modelA
{
//Globe data types
//3D model data structure
        struct VertexA
    {
        float pos[3]; //Vertex position 
        float vt[2];  //Vertex texture coordinates
        float vn[3];  //Vertex normal
    };

//Face index struct
        struct FaceIndexA
    {
        unsigned int ifp[3];//face point index
        unsigned int ift[3];//face texture index
        unsigned int ifn[3];//face normal
    };



//Globe functions

//Log to file function
void logToFile(string funcName,string funcInfo,bool logFlag);
//File string handling functions
bool scanStrFile(ifstream& ifoper,string& scanStr);
bool seekStrFromFile(ifstream& ifoper,string elemName);
//Modify file function
bool modifyContFile(ofstream mdfos,unsigned int startPos,unsigned int endPos,string newContent);
//A variable to string function
template <class T> string varToStr(T varName)
{stringstream ss;
    ss<<varName;
    return ss.str();};

    //A little timer
void tmsta(time_t& time);
void tmend(time_t& time,string infoLabel);

};


#endif