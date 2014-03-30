//d3dut_globle.cpp
#include "d3dut_globle.h"

//Log to file function
void utg::log2File(string funcName,string funcInfo,bool logFlag)
{
	if(logFlag)
	{ofstream ofoper;
	ofoper.open("log.txt",ios_base::out|ios_base::app);

	//CPP time function to get time
	tm *loctime=new tm;
	//Get calender time
	time_t nowtime=time(NULL);
	//Get local time
	localtime_s(loctime,&nowtime);

	//Output hh:mm:ss YY/MM/DD header
	ofoper<<setfill('0')<<setw(2)<<loctime->tm_hour<<':'<<setw(2)<<loctime->tm_min<<':'<<setw(2)<<loctime->tm_sec<<"  "    //hh:mm:ss
		<<(loctime->tm_year+1900)<<'-'<<setw(2)<<(loctime->tm_mon+1)<<'-'<<setw(2)<<loctime->tm_mday<<"      "             //yyyy-mm-dd
		<<"<"<<funcName<<">:"<<"  "<<flush;                                                                                //info lable
	//Output function running info
	ofoper<<funcInfo<<"\n"<<flush;

	//Exit log process
	ofoper.clear();
	ofoper.close();
	}
	else
		return;
};

//A little timer
//Timer start
void utg::tmstat(time_t& time)
{
	time=clock();		
};
//Timer end and return time cost by seconds
float utg::tmendt(time_t starttime)
{
	return ((clock()-starttime)/float(CLOCKS_PER_SEC));
};