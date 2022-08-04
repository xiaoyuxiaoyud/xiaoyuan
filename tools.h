#ifndef TOOLS_H
#define TOOLS_H

void msg_show(const char* msg,float sec);//短暂显示提示信息
void anykey_continue(void);//按任意键继续
char* hidden_input(void);//隐藏式输入密码，用法:strcpy(*dest,hidden_input())，输入密码到给定字符串里
void tea_read(void);
void stu_read(void);
void tea_save(void);
void stu_save(void);
void my_fgets(char* str,int size);
void encryption1(char key);
void encryption2(char key);
void encryption3(char key);
int id_fgets(char*str,int size);
#endif//TOOLS_H
