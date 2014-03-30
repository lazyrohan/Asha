//ahmModelClass.h
//AHM model file load class

#ifndef _AHMMODELCLASS_H_
#define _AHMMODELCLASS_H_

//Model globle header includ
#include "hModelGloble.h"
using namespace modelA;

class ahmModelClass
{
public:
	ahmModelClass();
	~ahmModelClass();

public:	
	//Initialize
	bool Initialize(string fileName);
	//Load ahm model files
	bool loadModel(vector <VertexA>& m_vertices,vector <FaceIndexA>& m_faceIndex);
	void Release();
public:
	//Pulic numbers can be acced.
	unsigned long int g_elemIndex[3][2];

private:
	//Internal communication parameters	
	//File open stream
	ifstream ifoper;

};

#endif
