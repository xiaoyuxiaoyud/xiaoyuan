#ifndef TEACHER_H
#define TEACHER_H

#include<stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <string.h>
#include "mis.h"

//教师登录
void tea_changepassword(void);	//首次登录修改密码
void tea_login(void);

//功能实现函数
void stu_add(void);				//1、添加学生
void stu_add_single(void);			//单个
void stu_add_batch(void);			//批量

void stu_del(void);				//2、删除学生

void stu_find(void);			//3、查找学生

void stu_mod(void);				//4、修改学生信息
void stu_modbase(void);
void stu_modscore(void);

void stu_score_input(void);		//5、录入学生成绩
void score_input_single(void);		//单个
void score_input_batch(void);		//批量

void stu_reset_password(void);	//6、重置学生密码
void stu_show(void);			//7、显示所有在校学生信息

void stu_show_quit(void);		//8、显示所有退学学生信息

//工具函数
int menu2(void);
FILE* file_read(void);
void stu_save1(void);
void tea_save(void);
void stu_unlock(void);

#endif//TEACHER_H
