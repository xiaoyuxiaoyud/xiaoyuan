#include "process.h"
#include <malloc.h>
extern  int teacher_count;
void init(void)
{
    FILE* fap = fopen("bossID","r");//以只读权限打开文件
    if(NULL == fap)           		//判断文件有没有
	{
		perror("frp: fopen");
		return ;
	}
	fscanf(fap,"123456 %s %d %d\n",ad.password,&ad.firstlogin,&teacher_count);//在文件中读取数据到变量中
	fclose(fap);//关闭文件
	fap = NULL;
	tea_read();
	encryption1(-8);
}

void start(void)
{ 
    int ID;
	char code_old[20] = {};	//定义一个字符串用来存放第一次输入的密码
	char code[20] = {};
	char password1[20] = {};
	char password2[20] = {};
	for(;;)			//进入死循环
	{	
		if(0==ad.firstlogin)//如果是第一次登录系统则强制修改密码
		{
		    printf("请输入帐号:");
		    scanf("%d",&ID);
		    if(123456==ID)	//判断输入帐号是否正确
		    { 
		        printf("帐号输入正确!\n");
			    printf("请输入密码:");
			    strcpy(code_old,hidden_input());//输入初始密码
			    if(0==strcmp(code_old,"123"))	//初始密码为123,判断初始密码是否输入正确
			    {
				    printf("登录成功!\n");
				    printf("请修改密码:");
				    strcpy(password1,hidden_input());
				    printf("请再次输入密码:");
				    strcpy(password2,hidden_input());
				    if(0 == strcmp(password1,password2))
				    {
				    	printf("密码修改成功!");
				    	strcpy(ad.password,password1);
				    	ad.firstlogin = 1;//登录成功，则以后登录便不再强制修改密码
				    }
				    else
				    {
				    	printf("密码不一致！请重试！");
				    	continue;
				    }
			    }
			    else
			    {
				    printf("密码错误!\n");
				    continue;//初始密码错误，进入下次循环
			    }
			}
			else 
			    {   
			        msg_show("帐号错误!\n",1.5);//帐号输入错误，进入下次循环
			        return;
			    }
		}
	   else
	   {
			printf("请输入密码:");//不是第一次登录，直接输入密码即可
			strcpy(code,hidden_input());
			if(0==strcmp(code,ad.password))//如果密码正确，则进入主菜单
			{  
				for(;;)//进入死循环
				{
					   switch(menu1())
					   {
				            case '1': teacher_reset(); break;	   //重置教师密码
							case '2': teacher_add(); break;		   //添加教师
							case '3': teacher_del(); break;		   //删除教师
							case '4': teacher_display_in(); break; //显示在职教师
							case '5': teacher_display_out(); break;//显示离职教师
							case '6': teacher_unlock(); break;	   //解锁教师帐号
	                        case '7': admin_reset_code();break;  //重置校长密码
							case '0': return;					   //退出系统
					   }
				}
			}
			else 
			{
				printf("密码错误!\n");//密码错误，进入下次循环
				continue;
			}
	  }
	}
}
void save(void)//保存数据
{   
    encryption1(8);
    FILE* fwp = fopen("bossID","w");//以只写权限打开文件,如果存在则清空打开，不存在则新建
    if(NULL == fwp)
	{
		perror("frp: fopen");
		return ;
	}
	fprintf(fwp,"123456 %s %d %d",ad.password,ad.firstlogin,teacher_count);//以文本形式输入数据到文件中
	fclose(fwp);//关闭文件
	fwp = NULL;
	tea_save();
}

int menu1(void)//显示菜单
{
	system("clear");
	puts("****欢迎使用校长管理系统****");
	puts("1、重置教师密码");
	puts("2、添加教师");
	puts("3、删除教师");
	puts("4、显示所有在职教师");
	puts("5、显示所有离职教师");
	puts("6、解锁教师帐号");
	puts("7、重置密码");
	puts("0、退出系统");
	puts("******************************");
	printf("请输入指令:");
	char cmd = getch();
	printf("%c\n",cmd);
	return cmd;
}
	
void admin_main(void)
{
    init();
	start();
	save();
}

