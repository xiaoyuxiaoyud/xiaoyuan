#ifndef STUDENT_H
#define STUDENT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getch.h>
#include"mis.h"
#include "tools.h"
void stu_login(void);		//学生登入界面

int stu_menu(void);		//学生界面菜单

void stu_checkgrade(void);	//查询学生成绩

int stu_changepassword(void);	//修改学生密码

void stu_showmessage(void);	//显示学生信息

void stu_save(void);		//将学生信息写入文件

char* hidden_input(void);	//隐藏输入函数

#endif
