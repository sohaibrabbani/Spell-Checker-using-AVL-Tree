#include "Header.h"
void main(int argc,char** argv)
{
	ifstream inD,inC;
	ofstream outLog;
	string A;
	if (argc >= 4)
	{
		inD.open(argv[2]);
		if (inD.is_open())
		{
			inC.open(argv[1]);
			if (inC.is_open())
			{
				outLog.open(argv[3]);
				spellChecker obj;
				obj.inputFromFile(inD,outLog);
				obj.commandFile(outLog, inC);
				outLog.close();
				inC.close();
			}
			else
				cout << "Error: Command File is Missing.";
			inD.close();
		}
		cout <<  "Error: Command File is Missing.";
		
	}

}