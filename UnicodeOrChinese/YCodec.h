
#include <iostream>
using namespace std;

class YCodec
{
public:
	YCodec();
	~YCodec();
	// char to hex code
    int Char2Dec(char ch);
	// hex to char
    char Dec2Char(unsigned int n);
	// num^index
	long MIndex(int num, int index);
	// string to hex code
    long String2Dec(char* string, int strlen);
	// hex to char*
    int Dec2String(long hex, char* string, int* slen);
	// hex to wchar_t code
	wchar_t Hex2Wchart(long hex);
	// UNICODE十六进制字符串转成中英文
	// hex string to wchar_t*
	int HexStr2WChars(char* hexstr, int hexstrlen, int eachchar, wchar_t* wchs, int* wchslen);
	// wchar_t to hex code
    long Wchart2Dec(wchar_t wch);
	// 中英文转成UNICODE十六进制字符串
	// wchar_t* to char*(hex string)
	int Wchart2HexStr(wchar_t* wchs, int wchslen, int eachchar, char* hexstr, int* hexstrlen);

};
