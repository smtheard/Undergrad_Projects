#include <string>

using namespace std;

class ScriptParser
{

	public: struct cmdLine
	  {
	   string operation;
	   string listID;
	   string value1;
	   string value2;
	  };
    public:  cmdLine cmd;
	public: ScriptParser();
	public: int operationCode();
	public: void ParseLine(string stringtobeparsed);
	public:  string match(string str1, string strtemplate);
}
;