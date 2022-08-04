#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include <getch.h>
#include <unistd.h>
#include <string.h>
#include "mis.h"
#include "admin.h"
#include <malloc.h>
Teacher* tea;
Student* stu;
extern int teacher_count;
void msg_show(const char* msg, float sec)//短暂显示提示信息
{
	printf("%s",msg);
	fflush(stdout);
	usleep(sec*1000000);
}
void anykey_continue(void)//按任意键继续
{
	puts("按任意键继续...");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	getch();
}
char* hidden_input(void)//隐藏式输入密码，用法:strcpy(*dest,hidden_input())，输入密码到给定字符串里
{
  stdin->_IO_read_ptr = stdin->_IO_read_end;//清空缓冲区
  static char p[21]={};
  int  i=0;
    do
    {
        p[i]=getch();
        if(10==(int)p[i])//是回车
    {
      p[i]='\0';    
            break;
    }
        if((int)p[i]==127)//是退格
        {
            if(0==i)
            {
                printf("\a");
                continue;
            }
            i=i-1;
            printf("\b \b");
        }
        else
        {
            i=i+1;
            if(20!=i)
            {
            	printf("*");
            }
            else
            {
            	i=i-1;
            }
        }
    }while('\n'!=p[i] && i<20);
	printf("\n");

    if('\0'==p[0])
    {
    	printf("密码为空，已自动置为初始密码\n");
    	strcpy(p,"123456");
    	anykey_continue();
    }
  	return p;
}

//读文件teacher.txt
void tea_read(void)
{
	FILE* frp = fopen("teacher.txt","r");//以只读权限打开文件
	if(NULL == frp)//判断文件有没有
	{
		perror("frp: fopen");
		return ;
	}
	for(int j=0;j < teacher_count;j++)
	{
	     fscanf(frp,"%s %c %d %d %d %d %s\n",tea[j].name,&tea[j].sex,&tea[j].id,&tea[j].count,&tea[j].firstlogin,&tea[j].flag,tea[j].password);//在文件中读取数据到变量中
    	}
    fclose(frp);//关闭文件
    frp = NULL;
    encryption2(-8);
}

//读文件student.txt
void stu_read(void)
{	

	FILE* frp=fopen("student.txt","r");	
	if(NULL==frp)
	{
		printf("系统正在维护！");
		sleep(1);//anykey_continue();
		return;
	}
	char row[sizeof(Student)];
	int i=0;
	while(NULL!=fgets(row,sizeof(Student),frp))
	{
		sscanf(row,"%d %d %s %s %c %lf %lf %lf %d %d",
		&stu[i].firstlogin,&stu[i].id,stu[i].password,
		stu[i].name,&stu[i].sex,
		&stu[i].chinese,&stu[i].math,&stu[i].english,
		&stu[i].count,&stu[i].flag);
		i++;
	}
	fclose(frp);
	frp=NULL;
	encryption3(-8);
}

//保存文件student.txt
void stu_save(void)
{
	encryption3(8);
	FILE* fwp=fopen("student.txt","w");//写方式打开文件
	for(int i=0;i<MAX_STU;i++)
	{
		if('w'==stu[i].sex||'m'==stu[i].sex)//性别存在，写入
		{
			fprintf(fwp,"%d %d %s %s %c %lf %lf %lf %d %d\n",
			stu[i].firstlogin,stu[i].id,stu[i].password,
			stu[i].name,stu[i].sex,
			stu[i].chinese,stu[i].math,stu[i].english,
			stu[i].count,stu[i].flag);
		}	//更新文件数据
	}
	fclose(fwp);
	fwp=NULL;
}

//保存文件teacher.txt
void tea_save(void)
{
	encryption2(8);
	FILE* ftp = fopen("teacher.txt","w");//以只写权限打开文件,如果存在则清空打开，不存在则新建
	if(NULL == ftp)
	{
		perror("frp: fopen");
		return;
	}
	for(int j = 0;j<teacher_count;j++)	
	{
		if(tea[j].id)
		{
	    	fprintf(ftp,"%s %c %d %d %d %d %s\n",tea[j].name,tea[j].sex,tea[j].id,tea[j].count,tea[j].firstlogin,tea[j].flag,tea[j].password);//以文本形式输入数据到文件中
		}	
	}
    fclose(ftp);//关闭文件
    ftp = NULL;
}
//输入字符串并将末尾的\n变为\0
void my_fgets(char* str,int size)	
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	fgets(str,size,stdin); 
	str[strlen(str)-1]='\0';	//将\n置为\0 
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}
//加密解密
void encryption1(char key)
{
	for(int i=0;i<19;i++)
	{
		ad.password[i]+=key;
	}
	ad.password[19]='\0';
}
void encryption2(char key)
{	//教师密码加密
	for(int i=0; tea[i].flag ;i++)
	{
  		for(int j=0; j < strlen(tea[i].password) ;j++)
  		{
   			tea[i].password[j]+=key;
  		}
	}
}

void encryption3(char key)//学生密码加密
{  
	for(int i=0; stu[i].flag  ;i++)
	{
    	for(int j=0; j < strlen(stu[i].password) ;j++)
    	{
      		stu[i].password[j]+=key;
     	// printf("%c\n",stu[i].password[j]);
    	}
	}
}

int id_fgets(char*str,int size)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清空缓冲区
	fgets(str,size,stdin);
	str[strlen(str)-1]='\0';//将末尾\n置为\0
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	//printf("\n\n%s:%d\n\n",str,atoi(str)+10);
	return atoi(str);
}
