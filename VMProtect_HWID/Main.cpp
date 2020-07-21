//=====================================================================================

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <VMProtectSDK.h>

using namespace std;

//=====================================================================================

#define DEFAULT_TXT "\\hwid.txt"

//=====================================================================================

string GetParent(const string& path)
{
	if (path.empty())
		return path;

	auto idx = path.rfind('\\');

	if (idx == path.npos)
		idx = path.rfind('/');

	if (idx != path.npos)
		return path.substr(0, idx);

	else
		return path;
}

//=====================================================================================

string GetExeDirectory()
{
	char imgName[MAX_PATH] = { NULL };
	DWORD len = ARRAYSIZE(imgName);

	QueryFullProcessImageName(GetCurrentProcess(), NULL, imgName, &len);

	return GetParent(imgName);
}

//=====================================================================================

string GetHwid()
{
	int nSize = VMProtectGetCurrentHWID(NULL, 0);
	char* pBuf = new char[nSize];
	VMProtectGetCurrentHWID(pBuf, nSize);
	string hwid(pBuf);
	delete[] pBuf;
	return hwid;
}

//=====================================================================================

int main()
{
	string szFilepath = GetExeDirectory() + DEFAULT_TXT;
	string szHwid = GetHwid();

	ofstream file(szFilepath, ios_base::out);
	file << szHwid << endl;

	cout << "Your hwid is: " << szHwid << endl;
	cout << "Saved to: " << szFilepath << endl;

	system("pause");

	return 0;
}

//=====================================================================================