#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<string>
#include<fstream>						//文件的输出输出流操作
#include<iomanip>						//对齐输出
#include <conio.h>
using namespace std;

#ifndef UTIL_H
#define UTIL_H
class Util {
public:
	static void	inputPassword(string &str, int size); 
};
#endif