#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include "tools.h"
#include "admin.h"
#include <stdlib.h>
#include "process.h"
#include <string.h>
#include <getch.h>
#include "mis.h"
void init(void);//读取文件,初始化
void start(void);//开始功能
void save(void);//保存文件
void admin_main(void);
int menu1(void);
#endif//PROCESS_H
