//hModelGloble.cpp
//Define model globle functions
#include "hModelGloble.h"

//Log fucnton
void modelA::logToFile(string funcName,string funcInfo,bool logFlag)
{
	ofstream ofoper;
	ofoper.open("log.txt",ios_base::out|ios_base::app);

	//CPP time function to get time
	tm *loctime=new tm;
	//Get calender time
	time_t nowtime=time(NULL);
	//Get local time
	localtime_s(loctime,&nowtime);

	//Output hh:mm:ss YY/MM/DD header
	ofoper<<setfill('0')<<setw(2)<<loctime->tm_hour<<':'<<setw(2)<<loctime->tm_min<<':'<<setw(2)<<loctime->tm_sec<<"  "    //hh:mm:ss
		<<(loctime->tm_year+1900)<<'-'<<setw(2)<<(loctime->tm_mon+1)<<'-'<<setw(2)<<loctime->tm_mday<<"      "           //yyyy-mm-dd
		<<"<"<<funcName<<">:"<<"  "<<flush;                                                                         //info lable
	//Output function running info
	ofoper<<funcInfo<<"\n"<<flush;

	//Exit log process
	ofoper.clear();
	ofoper.close();
}

//Character scan to string
bool modelA::scanStrFile(ifstream& ifoper,string& scanStr)
{
	int i=0;
	  char inchar[256]="\0";
	  char charBuff='\0';
	  while((charBuff!=char(32))&&(charBuff!='\n')&&(!ifoper.eof()))
	  {
           charBuff=ifoper.get();
		  if((charBuff!=char(32))&&(charBuff!='\n'))
		   {
			   inchar[i]=charBuff;
		       ++i;
		   }		   
	  }

	  //Get last read char
	  scanStr=inchar;

	  if(!ifoper.eof())
		  return true;
	  else
	  {
		  ifoper.clear();
		  ifoper.seekg(0,ios_base::beg);
		  return false;
	  }
}

//String seeker
bool modelA::seekStrFromFile(ifstream& ifoper,string elemName)
{
	string endStr="\0";
	//Seeking strings.
	while((endStr!=elemName)&&(!(ifoper.eof())))
	{
	  //String reader
	  scanStrFile(ifoper,endStr);
	}

	if(!ifoper.eof())
	  return true;
	else
	{
		ifoper.clear();
		ifoper.seekg(0,ios_base::beg);
		return false;
	}
}

//Modify file content function
bool modelA::modifyContFile(ofstream mdfos,unsigned int startPos,unsigned int endPos,string newContent)
{
	if(endPos<startPos)
		return false;
	else
	{
		//Move ofstream pointer to end position 
		mdfos.seekp(endPos,ios_base::beg);
		//Delete old content
		for(int i=0;i<int(endPos-startPos);i++)
			mdfos.put(char(8));
		//Write new content
		mdfos<<newContent<<flush;
		//Exit and go to begin
		mdfos.clear();
		mdfos.seekp(0,ios_base::beg);
	}

	return true;
}
void modelA::tmsta(time_t& time)
{
	time=clock();
		
}
void modelA::tmend(time_t& time,string infoLabel)
{
	time_t timend=clock()-time;
	cout<<infoLabel<<" time cost: "<<(timend/float(CLOCKS_PER_SEC))<<" seconds!\n";
}