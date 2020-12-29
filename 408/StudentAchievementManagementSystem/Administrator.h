#include"Base.h"
#include"Teacher.h"
#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
class Administrator:public Base
{
private:
	Teacher* head;	// 存储老师信息的链表
public:
	Administrator();
	void Fileread();						// 文件读取
	void Filewrite(); 					// 文件输入
	void Display(int x = 1);		// 显示屏输出
	void Insert();
	void Delete();
	void Put();
	Teacher* Find();
	Teacher* teacher_pass(string number, string password);
};
#endif