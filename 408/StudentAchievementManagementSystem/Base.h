#ifndef BASE_H
#define BASE_H
class	Base {
public:
	virtual void Fileread()=0;	// 文件读取
	virtual void Filewrite()=0; // 文件输入
	virtual void Display(int x = 1)=0;		// 显示屏输出
};
#endif