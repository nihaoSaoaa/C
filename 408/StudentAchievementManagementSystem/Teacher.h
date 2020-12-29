#include<iostream>
#include<string>
using namespace std;
#include"Base.h"
#include"Student.h"

#ifndef TEACHER_H
#define TEACHER_H
class Teacher:public Base		//老师类，主要进行学生信息链表的操作，查找输出
{
private:
	string t_number;	// 工号
	string t_name;
	string password;	// 密码
	Student *head;		// 学生信息链表
	Teacher *link;		// 下一个老师结点
public:
	Teacher(string t_number="000", string t_name="空", string password="000");//学生链表的初始化，建立头结点,并从文件中读取信息建立链表				
	~Teacher();
	void Fileread();					//读取文件中的信息建立链表
	void Filewrite();				//通过文件的读写将链表中的内容写到文件中
	/**********************************     操作部分    ***********************************/
	void Putin(int n=1);			//输入,参数的含义是区别与是操作1的输入还是插入函数（默认是输入函数）
	void Display(int x=1);				//显示输出cout<<left<<setw(40)<<"靠左输出"<<left<<setw(35)<<"靠左输出"<<endl;
	void Insert();				//插入(添加)
	void Delete();				//删除
	void Find(int i=1);			//查找
	void Find_01name(int x=1);	//查找名字 参数 1.查找 2.删除 3.修改
	void Find_02number(int x=1);//学号查找
	void Find_03academy(int x=1);//学院查找
	void Modify();		//修改             界面里加上一些划线增加美观度
	void Modify_small(Student *p);
	void Sort();			//排序
	void Sort_small(int i=1);//排序函数分支，根据参数的不同进行不同选项的排序1.默认学号 2.单科成绩 3.总成绩  
	void Cal();			//计算各个学科总成绩和平均成绩   需要强大其功能
	void Cal_small(string na);
	float Grade_fail(string name ,int grade);		//计算成绩打败全校的百分比
	void student_pass(string na ,string num );		//学生登陆情况
	friend class Administrator;
	friend class ManageSystem;
};
#endif