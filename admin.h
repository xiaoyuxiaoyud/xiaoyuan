#ifndef ADMIN_H
#define ADMIN_H
#include "mis.h"
extern Admin ad;		//声明Admin结构体
void teacher_reset(void);	//重置教师密码
void teacher_add(void);		//添加教师
void admin_reset_code(void);		//修改校长密码
void teacher_del(void);		//删除教师
void teacher_display_in(void);		//显示在职教师
void teacher_display_out(void);		//显示离职教师
void teacher_unlock(void);		//解锁教师帐号
#endif//ADMIN_H
