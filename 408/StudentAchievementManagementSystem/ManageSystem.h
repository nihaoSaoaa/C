#include<string>
using namespace std;
#include"Teacher.h"

#ifndef MANAGESYSTEM_H
#define MANAGESYSTEM_H
class ManageSystem 
{
private:
	static const string Pass_word;
public:
	void Menu_studentpass();
	Teacher* Menu_teacherpass();
	void Menu_teacher(Teacher* p);
	void Menu_admin();
	void Welcome();
};
#endif