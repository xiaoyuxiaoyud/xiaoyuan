#include "admin.h"
#include <stdio.h>
#include <unistd.h>
#include "tools.h"
#include "process.h"
#include <string.h>
#include <getch.h>


Admin ad;
int teacher_count=0;	// 计算教师人数
void teacher_add(void) 	//添加教师
{	
	if(MAX_TEA <= teacher_count) //判断教师的最大人数是否达到最大值
	{
		puts("系统正在升级，请等待...");
		return ;
	}
	printf("请输入新教师的姓名:");
	for(;;)
	{
        my_fgets(tea[teacher_count].name,21);	
		printf("请选择性别w/m(女/男):\n");
		while(1)
		{
				stdin->_IO_read_ptr=stdin->_IO_read_end;
				int sex=getch();
				printf("%c\n",sex);
				switch(sex)	//为教师结构体的sex成员赋值
				{
					case 'm':
						tea[teacher_count].sex='m';
						break;
					case 'w':
						tea[teacher_count].sex='w';
						break;
					default:
						stdin->_IO_read_ptr=stdin->_IO_read_end;
						printf("请重新选择性别w/m:\n");//判读非法输入
						continue;	
				}
				break;	
			}
			break;	
	}
	tea[teacher_count].firstlogin = 0;          //默认教师第一次登录
	strcpy(tea[teacher_count].password,"123456");//设置默认密码
	tea[teacher_count].id = 100+teacher_count;//默认自动生成帐号
	tea[teacher_count].flag=1;
	teacher_count++;	//如果添加成功，则总教师人数加一	
	msg_show("添加教师成功!\n",1.5);
}

void teacher_reset(void)  //重置教师的密码
{
    int num;
		printf("请输入要重置密码老师的工号:");
	    scanf("%d",&num);			//输入重置密码的工号
	for(int j=0;j<teacher_count;j++)//通过for循环查找所输入的工号是否为有效工号
	{
		if(tea[j].id == num) 		//判断工号是否存在
		{
			strcpy(tea[j].password,"123456");	//将新密码替换旧的密码
			msg_show("重置成功！",1.5);
			return;
		}
	}
	msg_show("工号有误!\n",1.5);
}
void teacher_del(void) //删除教师
{
    int num ;
	printf("请输入要删除老师的工号:");
	scanf("%d",&num);
	for(int j=0;j<teacher_count;j++)//通过for循环查找老师工号判断输入工号是否为有效工号
	{
		if(tea[j].id == num)     //如果是有效工号
		{
	        tea[j].flag = -1;//将is_school改为1,则为离职教师 
			msg_show("删除成功!\n",1.5);
			return;
		}
     }
     msg_show("未查找到该工号!\n",1.5);
}

void teacher_display_in(void)  //在屏幕中显示在职教师
{
	printf("姓名     性别 工号\n");
	for(int j=0; j<teacher_count; j++)//通过for循环判断列表中教师的工号是否为正
	{
		if(1 == tea[j].flag)	
		{
			printf("%-9s %s  %-4d\n",
			tea[j].name,'w'==tea[j].sex?"女":"男",tea[j].id);	
		}
	}
	anykey_continue(); //按任意键继续
}

void teacher_display_out(void) //在屏幕中显示离职教师
{
	printf("姓名     性别 工号\n");
	for(int j=0; j<teacher_count; j++)//通过for循环判断列表中教师的工号是否为负
	{
		if(-1 == tea[j].flag)	
		{
			printf("%-9s %s  %-4d\n",
			tea[j].name,'w'==tea[j].sex?"女":"男",tea[j].id);	
		}	//输出离职教师
	}
	anykey_continue(); //按任意键继续
}


void teacher_unlock(void) //解锁教师帐号
{
    int num;
    printf("请输入要解锁的教师工号:");
    scanf("%d",&num);	//	输入要重置密码的帐号
        for(int j=0;j<teacher_count;j++)//通过for循环判断输入的工号是否有效
        {
            if(num == tea[j].id)	//判断帐号
            {
                tea[j].count = 0;	//将该教师输错密码次数清零
                msg_show("帐号已解锁!",1.5);
                return;
            }
        }
    msg_show("未找到该教师!",1.5);
}




void admin_reset_code(void) //重置校长密码
{
		    strcpy(ad.password,"123456");//将密码重置
		    msg_show("密码重置成功!\n",1.5);
		    return;
}


