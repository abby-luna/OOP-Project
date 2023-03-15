#pragma once
#include <string>

using namespace std;
class CUser
{
private:
	string m_name;
	char m_userType;
	string m_password;

public:
	CUser();
	CUser(string uname, char type, string password);
	bool auth(string password);
	char getType();
	string getName();
	string getPass();
	void setPass(string newPass);




};

