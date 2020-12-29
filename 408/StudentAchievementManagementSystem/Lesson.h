#include<iostream>
#include<string>
using namespace std;
#include"Base.h"

#ifndef LESSON_H
#define LESSON_H
const int MAX=10;							//最多课程数量
struct Lesson_Node							//课程的结构体设置
{
	string L_name;							//课程名称
	int grade;								//课程成绩
};

class Lesson:public Base								//课程设置类
{
private:
	Lesson_Node lesson[MAX];				//课程具体信息，最多10项
	int n;									//当前的课程数量
	int Mount_s;							//成绩总和
	int Average_s;							//平均成绩
public:
	Lesson();							//课程初始化，读取文件中公共课程的信息设置,如果没有文件就建立一个文件
	~Lesson();							//析构
	Lesson(const Lesson&rhs);				//复制构造函数
	Lesson& operator=(const Lesson&L);		// 重载赋值函数
	int ReturnMount_s();						//返回总分
	int ReturnAverage_s();					//返回平均分
	void Display(int x=1);					//输出当前的课程的信息
	void Add(int i=1);					//增加课程 参数1是公共课程的添加 2是私人课程的添加
	void Dell(int i=1);					//删除课程
	void SetA_M();							//计算平均分和总分
	/*******************************************     个人选修课程设置     *********************************************/
	void SetPersonLesson();
	/*******************************************     公共课程设置部分     **********************************************/
	void Filewrite();				//向文件中输入公共课程的设置
	void Fileread();				//从文件中读取公共课程设置信息，建立课程
	void SetPublicLesson();				//设置当前的公共课程的信息
	/*******************************************      输入输出友元函数     **********************************************/
	friend istream& operator>>(istream& is,Lesson &rhs);//输入成绩
	friend ostream& operator<<(ostream& os,Lesson &rhs);//输出成绩
	friend class Student;
	friend class Teacher;
};
#endif