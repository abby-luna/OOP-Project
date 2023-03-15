#include "CUser.h"

CUser::CUser()
{
	m_name = "";
	m_userType = 'N';
	m_password = "";
}
CUser::CUser(string uname, char type, string password)
{
	m_name = uname;
	m_userType = type;
	m_password = password;
}

bool CUser::auth(string password)
{
	return password == m_password;
}
char CUser::getType()
{
	return m_userType;
}

string CUser::getName()
{
	return m_name;
}

string CUser::getPass()
{
	return m_password;
}
void CUser::setPass(string newPass)
{
	m_password = newPass;
}