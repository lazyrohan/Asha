//ahmModelClass.cpp
#include "ahmModelClass.h"

ahmModelClass::ahmModelClass()
{

}

ahmModelClass::~ahmModelClass()
{

}

//Initialize open ahm file and read data

bool ahmModelClass::Initialize(string fileName)
{
	logToFile("ahmModelClass","------------------------------------------------------------------",LOG_ON);
	//Open model files
	ifoper.open(fileName,ios_base::in|ios_base::binary);
	if(!ifoper.is_open())
	{
		logToFile("Initialize","Invalid file to read!",LOG_ON);
		return false;
	}
	else
		logToFile("Initialize",("Load ahm model file: "+fileName+" succed."),LOG_ON);
	
	//Load element index info form file
	string elemName[3]={"vertex","face","shape"};
	for(int i=0;i<3;i++)
	{
		//Loop read index info
	      if(seekStrFromFile(ifoper,elemName[i]))
		  {
			  ifoper>>g_elemIndex[i][0];//First element number.
			  if(g_elemIndex[i][0]<=0)
			  {
				  logToFile("Initialize",("No validate element number found."),LOG_ON);
				  return false;
			  }

		      ifoper>>g_elemIndex[i][1];//than element data step from begin.
			  if(g_elemIndex[i][1]<=0)
			  {
				  logToFile("Initialize",("No validate element step data found."),LOG_ON);
					  return false;
			  }
		  }
		  logToFile("Initialize",(elemName[i]+" number read from index: "+modelA::varToStr(g_elemIndex[i][0])+",data step from begin: "+modelA::varToStr(g_elemIndex[i][1])),LOG_ON);
	}

	ifoper.clear();
	return true;
}

//Load vertex elements
bool ahmModelClass::loadModel(vector <VertexA>& m_vertices,vector <FaceIndexA>& m_faceIndex)
{
	//Load vertex data
	if(!ifoper.is_open())
	{
		logToFile("loadModel","Model file closed!",LOG_ON);
		return false;
	}
	ifoper.seekg((g_elemIndex[0][1]),ios_base::beg);

	for(vector <VertexA>::iterator itv=m_vertices.begin();itv<m_vertices.end();itv++)
	{
		for(int i=0;i<2;i++)
		{
			ifoper>>itv->pos[i];
			ifoper>>itv->vt[i];
			ifoper>>itv->vn[i];
		}
		ifoper>>itv->pos[2];
		ifoper>>itv->vn[2];

	}
	ifoper.clear();
	logToFile("loadModel","Vertex data loading completed.",LOG_ON);
	//Load face index data

	ifoper.seekg((g_elemIndex[1][1]),ios_base::beg);

		for(vector <FaceIndexA>::iterator itf=m_faceIndex.begin();itf<m_faceIndex.end();itf++)
	{

		for(int i=0;i<3;i++)
		{
			ifoper>>itf->ifp[i];
			ifoper>>itf->ift[i];
			ifoper>>itf->ifn[i];
		}

	}
		logToFile("loadModel","Face index data loading completed.",LOG_ON);
		//Close data loading stream
		ifoper.clear();
		ifoper.close();
		return true;
}

void ahmModelClass::Release()
{
	//delete[] g_elemIndex;
}

	


