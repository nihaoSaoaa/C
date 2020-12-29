#include<iostream>
#include<string>
using namespace std;
#include "Lesson.h"

#ifndef STUDENT_H
#define STUDENT_H
class Student		//学生的信息类，存储学生的信息，并修改信息
{
private:
	string Name;		//姓名
	long Number;		//学号
	string Sex;			//性别
	string Academy;		//学院
	string Class;		//班级
	Lesson Less;        //课程
	Student *next;	// 指向下一个学生结点
public:
	Student(string na="空",long num=0,string sex="男",string aca="空",string cla="空");		//对成绩和姓名所以成员都进行初始化??需要优化?
	Student(Student &s); // 复制构造函数
	~Student();					//析构
	Student& operator=(const Student&s);	// 赋值重载
	void SetName(string name);		//设置名字
	void SetNumber(long num );		//设置学号
	void SetSex(string sex);			//设置性别
	void SetAcademy(string acad);	//设置学院
	void SetClass(string cla );		//设置班级
	void SetLesson();				//单人课程设置
	friend istream& operator>>(istream&is,Student &S);//输入数据
	friend ostream& operator<<(ostream&os,Student &S);//输出数据
	friend class Teacher;		//友元类设置
};
#endif