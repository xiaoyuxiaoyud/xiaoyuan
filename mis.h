//	mis		信息管理系统
//	mis.h
#ifndef MIS_H
#define MIS_H

#define MAX_TEA 50 //不要用MAX遍历
#define MAX_STU 500



typedef struct Student
{
	int firstlogin;	//	是否是第一次登入
	int id;				//	学号
    char password[20];	//	密码
    char name[20];		//	姓名
    char sex;			
    double	chinese;			//	语文成绩
    double	math;				//	数学成绩
    double	english;			//	英语成绩
    int count;		//	计算密码输入次数
    int flag;	//	状态：1，在校。-1，离校。0，该条记录无数据，或未使用
}Student;

typedef struct Teacher//声明教师的结构体，用来存放教师的基本信息
{
	char name[20];     //教师的名字
	char sex;          //教师的性别
	int id;            //教师登陆系统的工号Student* stu;
	char password[20]; //教师登陆系统的密码
    int count;         //教师登录系统输错密码的次数
    int firstlogin;    //判断是否第一次登录
    int flag;          //判断是否在校
}Teacher;

typedef struct admin{
	int firstlogin;	//	是否是第一次登入
    char password[20];	//	密码

}Admin;

extern Teacher* tea;
extern Student* stu;
#endif //MIS_H
