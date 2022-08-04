#include "teacher.h"
#include "tools.h"
#include "admin.h"
int cnt=0;
int ret=0;
extern int teacher_count;
//教师端主菜单功能 1、添加学生
void stu_add(void) 
{
	printf("请选择添加学生的方式：\n");
	printf("1、单个添加学生信息\n");
	printf("2、批量导入学生信息\n");
	switch(getch())
	{
		case '1':stu_add_single();break; 	//按1进入单个添加功能
		case '2':stu_add_batch();break;		//按2进入批量导入功能
	}	
}

//添加学生二级菜单功能 1、单个添加
void stu_add_single(void)
{
	if(MAX_STU<=cnt)
	{
		puts("系统正在升级，请等待...");
		return;
	}
	int i=0;
	while(stu[i].flag)				//flag为真代表第i行有数据，跳转下一行
	{
		i++;
	}
	printf("请输入新学生的姓名:");
	for(;;)
	{
		my_fgets(stu[i].name,20);
		printf("请选择性别w/m(女/男):\n");
		while(1)
		{
			stdin->_IO_read_ptr=stdin->_IO_read_end;
			int sex=getch();
			printf("%c\n",sex);
			switch(sex)
			{
				case 'm':
					stu[i].sex='m';
					break;
				case 'w':
					stu[i].sex='w';
					break;
				default:
					stdin->_IO_read_ptr=stdin->_IO_read_end;
					printf("请重新选择性别w/m:\n");
					continue;	
			}
			break;	
		}
		break;
	}
	stu[i].firstlogin=0;		//新添加的学生未登录过教务系统
	stu[i].id=1000+i;			//学号由系统自动产生，为1000+行数
	strcpy(stu[i].password,"123456");		//学生初始密码为123456
	stu[i].count=0;		//学生登录次数置0
	stu[i].flag=1;		//flag置1,表示第i行已填入学生信息
	cnt++;				//对添加的学生计数
	msg_show("添加成功！\n",1.5);
}

//添加学生二级菜单功能 2、批量导入
void stu_add_batch(void)
{
	int ret1 = 1,i =cnt;
	char str[256] = {};						//定义256字节字符串
	FILE* frp=file_read();					//调用读文件函数
	if(NULL==frp)
	{
		perror("frp:fopen");
		return;
	}
	while(ret1)								//ret1表示读取文件是否成功，成功则继续循环
	{				
		stu[i].firstlogin=0;
		stu[i].id=1000+i;					//自动生成学生帐号
		strcpy(stu[i].password,"123456");				
		ret1=(int)fgets(str,50,frp);		//从文件中最多输入49个字符到str中
		sscanf(str,"%s %c\n",stu[i].name,&stu[i].sex);	//从str中解析读取数据到变量中
		stu[i].count=0;		//默认密码输入次数为0
		stu[i].flag=1;		//默认学生为在校生
		i++;		//指向结构体数组里的下一个元素
		cnt++;		//统计学生数量
		printf("cnt : %d\n",cnt);
	}
				
	printf("cnt : %d\n",cnt);
	stu[cnt-1].id = 0;
	stu[cnt-1].flag = 0;			//flag置0,表示下次输入数据时此处可用
	cnt--;				//多了一次循环 cnt=cnt-1
	fclose(frp);		//关闭文件
	frp=NULL;			//frp置空
}

//主菜单功能 2、删除学生
void stu_del(void)
{
	int id1=0,i=0;
	char str1[6]={};
	char str2[6]={};
	printf("请输入要删除学生的学号：");
	id1=id_fgets(str1,6);
	int id2=0;
	printf("请再次输入要删除学生的学号：");
	id2=id_fgets(str2,6);
	while(stu[i].flag)	//遍历结构体
	{
		if(id1==id2)
		{
			if(id2==stu[i].id)	//判断该行结构体有数据 并 帐号存在
			{
				stu[i].flag=-1;				//flag置-1,表示该学生休学
				FILE* fwp=fopen("stu_Drop_out.txt","a");
				if(NULL==fwp)
				{
					perror("frp: fopen");
					return;
				}
				fprintf(fwp,"%d %s %c\n",stu[i].id,stu[i].name,stu[i].sex);//将结构数据更新到文件中
				fclose(fwp);
				fwp=NULL;
				cnt--;
				msg_show("删除成功！\n",1.5);
				return;
			}
		}
		else 
		{
			msg_show("两次输入学号不一致，请重新进入删除功能\n",1.5);
			return;
		}	
		i++;
	}
	msg_show("查无此人，删除失败！\n",1.5);
}

//主菜单功能 3、查找学生 找到一个就return?
void stu_find(void)
{
	char key[20]={};
	printf("请输入要查找学生的姓名或学号：");
	my_fgets(key,20);		//输入查询关键字,限制从键盘读入19个字符
	char str[20]={};
	int i=0;
	while(stu[i].flag)
	{			
		sprintf(str,"%d",stu[i].id);	//将结构体中的id数据，以字符串方式存入str中
		if(strstr(stu[i].name,key)||(!strcmp(str,key)))	//判读姓名和学号
		{
			printf("%d %s %s\n",stu[i].id,stu[i].name,'w'==stu[i].sex?"女":"男");	
			sleep(1);
		}
		i++;
	}
	msg_show("无更多信息！\n",1.5);	
	return;
}

//主菜单功能 4、修改学生信息
void stu_mod(void)
{
	printf("请选择功能：\n");
	printf("1、修改学生基础信息\n");
	printf("2、修改学生成绩\n");
	switch(getch())
	{
		case '1':stu_modbase();break;
		case '2':stu_modscore();break;
	}	
}

//修改学生信息二级菜单功能 1、修改学生基础信息
void stu_modbase(void)
{
	int id=0,i=0;
	char str[6]={};
	printf("请输入要修改学生的学号：");
	id=id_fgets(str,6);
	while(stu[i].flag)	//遍历结构体
	{
		if(id==stu[i].id)		//判读关键字是否符合要求
		{
			printf("请输入学生的姓名:");
			for(;;)
			{
				my_fgets(stu[i].name,20);
				printf("请选择性别w/m(女/男):");
				while(1)
				{
					stdin->_IO_read_ptr=stdin->_IO_read_end;
					int sex=getch();
					printf("%c\n",sex);
					switch(sex)
					{
						case 'm':
							stu[i].sex='m';
							msg_show("修改成功！",1.5);
						return;
						case 'w':
							stu[i].sex='w';
							msg_show("修改成功！",1.5);
						return;
						default:	//判读非法字符
							stdin->_IO_read_ptr=stdin->_IO_read_end;
							printf("请重新选择性别w/m:");
							continue;	
					}
					break;	
				}
				break;
			}	
		}
		i++;
	}
	msg_show("查无此人！\n",1.5);
}
	

//修改学生信息二级菜单功能 2、修改学生成绩 改！
void stu_modscore(void)
{
	int id=0,i=0;
	char str[6]={};
	printf("请输入要修改学生的学号：");
	id=id_fgets(str,6);
	printf("%d",id);
	double score[3]={};
	while(stu[i].flag)			//遍历结构体
	{
		if(1==stu[i].flag&&id==stu[i].id)	//按学号修改成绩
		{
			printf("请重新输入学生的语文、数学、英语成绩：");
			for(int j=0;j<3;j++)
			{
				scanf("%lf",&score[j]);//改
			}
			if(score[0]>0&&score[0]<100&&
			score[1]>0&&score[1]<100&&
			score[2]>0&&score[2]<100)	//判断成绩合法
			{
				msg_show("修改成绩成功！",1.5);				
				stu[i].chinese=score[0];
				stu[i].math=score[1];
				stu[i].english=score[2];
				return;
			}
			else
			{
				msg_show("修改成绩失败！",1.5);
				return;
			}
		}
		i++;
	}
	msg_show("查无此人！\n",1.5);
}

//主菜单功能 5、录入学生成绩
void stu_score_input(void) 
{
	printf("请选择录入成绩的方式：\n");
	printf("1、单个录入\n");
	printf("2、批量导入\n");
	switch(getch())
	{
		case '1':score_input_single();break;
		case '2':score_input_batch();break;
	}	
}

//录入学生成绩二级菜单功能 1、单个录入
void score_input_single(void)
{
	int id=0;
	int i=0;
	char str[6]={};
	printf("请输入要录入成绩学生的学号：");
	id=id_fgets(str,6);
	double score[3]={};
	while(stu[i].flag)
	{	
		if(id==stu[i].id)
		{
			printf("请输入该学生的语文、数学、英语成绩：\n");
			for(int j=0;j<3;j++)
			{
				scanf("%lf",&score[j]);//改
			}
			if(score[0]>0&&score[0]<100&&
			score[1]>0&&score[1]<100&&
			score[2]>0&&score[2]<100)	//判断成绩合法
			{
				msg_show("成绩录入成功！",1.5);				
				stu[i].chinese=score[0];
				stu[i].math=score[1];
				stu[i].english=score[2];
				return;
			}
			else
			{
				msg_show("输入成绩失败！",1.5);
				return;
			}
		}
		i++;
	}
	msg_show("查无此人！",1.5);
}

//录入学生成绩二级菜单功能 2、批量导入
void score_input_batch(void)
{	
	typedef struct Score
	{
		int id;
		double	chinese;			
    	double	math;				
    	double	english;
	}Score;
	Score* sco;
	sco=calloc(sizeof(Score),50);
	int i=0,j=0;
	int ret=1;
	FILE* frp=file_read();
	if(NULL==frp)
	{
		perror("frp:fopen");
		return;
	}
	while(ret!=-1)
	{
		ret=fscanf(frp,"%d %lf %lf %lf\n",&sco[i].id,&sco[i].chinese,&sco[i].math,&sco[i].english);
		//memset(str,0,sizeof(str));
		i++;
	}
	fclose(frp);
	frp=NULL;
	int len = 0;
	while( stu[len].flag )
	{
	printf("hahajhahahhahh\n");
		for(int i = 0 ; stu[i].flag ; i ++ )
		{
		printf("--------------for---------------\n");
			if( stu[len].id == sco[i].id )
			{
				stu[len].chinese = sco[i].chinese;
				stu[len].math 	 = sco[i].math;
				stu[len].english = sco[i].english;
			}
		}
		len++;
	}
}

//主菜单功能 6、重置学生密码
void stu_reset_password(void)
{
	int id=0,i=0;
	char str[6]={};
	printf("请输入需要重置密码学生的学号：");
	id=id_fgets(str,6);
	while(stu[i].flag)
	{	
		if(1==stu[i].flag&&id==stu[i].id)
		{
			strcpy(stu[i].password,"123456");	//重置密码
			msg_show("重置成功！\n",1.5);
			return;
		}
		i++;
	}
	msg_show("查无此人！",1.5);
}

//主菜单功能 7、显示所有在校学生信息
void stu_show(void) 
{
	int i=0;
	while(stu[i].flag)
	{
		if(1==stu[i].flag)	//判读是否是在校生
		{
			printf("学号：%-5d姓名：%-10s	性别：%-4s语文：%-7.2lf数学：%-7.2lf英语：%-7.2lf\n",stu[i].id,stu[i].name,'w'==stu[i].sex?"女":"男",stu[i].chinese,stu[i].math,stu[i].english);
		}
		i++;
	}
	anykey_continue();
}

//主菜单功能 8、显示所有退学学生信息
void stu_show_quit(void)
{
	int i=0;
	while(stu[i].flag)
	{
		if(-1==stu[i].flag)	//判断是否是离校生
		{
			printf("学号：%-5d姓名：%-10s性别：%-4s\n",stu[i].id,stu[i].name,'w'==stu[i].sex?"女":"男");
		}
		i++;
	}
	anykey_continue();
}

//首次登录修改密码
void tea_changepassword(void)
{
	puts("请输入新密码：");
	char newpass[20];
	strcpy(newpass,hidden_input());
	strcpy(tea[ret].password,newpass);
	msg_show("修改成功！\n",1.5);
}

//登录教师端
void tea_login(void)
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
	stu_read();
	//使用帐号登录
	char pass[20]={};
	char str[4]={};
	int i=0;
	int id=0;
	printf("请输入帐号（工号）：");
	id=id_fgets(str,5);
	//printf("%d\n",id);
	while(i<MAX_TEA)
	{
		if(id==tea[i].id&&tea[i].sex)	//帐号如果存在
		{
			if(3==tea[i].count)	//是否上锁
			{
				msg_show("您的帐号已上锁，请找校长解锁\n",1.5);
				return;
			}
			else
			{
				break;
			}
		}
		if(i==MAX_TEA-1)
		{
			msg_show("帐号不存在！\n",1.5);
			return;
		}
		i++;
	}

	//密码判断
	while(1)//隐藏密码
	{
		printf("请输入密码：");
		strcpy(pass,hidden_input());
		//printf("密码：%s\n",pass);
		if(!strcmp(pass,tea[i].password))//密码正确则退出循环进入下一步
		{	
			ret=i;
			tea[i].count=0;
			msg_show("登录成功！\n",1.5);
			break;
		}
		else 
		{
			tea[i].count++;
		}
		if(1==tea[i].count)
		{
			printf("输入错误，还有两次机会！\n");
		}
		else if(2==tea[i].count)
		{
			printf("输入错误，还有一次机会！\n");
		}
		else if(3==tea[i].count)//输错三次，保存上锁信息，退出登录
		{
			msg_show("密码输入错误三次，帐号已锁定，解锁请校长解锁！\n",1.5);
			return;
		}
	}
	//是否初次登录
	if (0==tea[ret].firstlogin)
	{
		printf("初次登录请修改密码！\n");
		tea[ret].firstlogin=1;
		tea_changepassword();
	}		
	for(;;)
	{
		//显示主界面
		switch(menu2())
		{
			case '1': stu_add(); break;
			case '2': stu_del(); break;
			case '3': stu_find(); break;
			case '4': stu_mod(); break;
			case '5': stu_score_input(); break;
			case '6': stu_reset_password(); break;
			case '7': stu_show();break;
			case '8': stu_show_quit();break;
			case '9': stu_unlock();break;
			case '0': 
				tea_save();
				stu_save();
				return;
	
		}	
	}
}

// 教师端主菜单
int menu2(void)
{
	system("clear");
	puts("—————欢迎使用教务管理系统————");
	puts("      1.添加学生");
	puts("      2.删除学生");
	puts("      3.查找学生");
	puts("      4.修改学生信息");
	puts("      5.录入学生成绩");
	puts("      6.重置学生密码");
	puts("      7.显示所有在校学生信息");
	puts("      8.显示所有退学学生信息");
	puts("      9.解锁学生帐号");
	puts("      0.退出系统");
	puts("—————————————————————————————");
	printf("请输入指令：");
	char cmd=getch();
	printf("%c\n",cmd);
	return cmd;

}

FILE* file_read(void)
{
	FILE *frp;          	//定义文件指针 
	char filename[50];		//定义一个文件名数组保存文件名 
	char path[100]={};		//标明文件所在的路径 
	char path1[256]={};		//存储最终的文件读取路径
	printf("请输入路径名：\n");
	scanf("%s",path);
	printf("请输入要导入的文件的名字：/filename\n");
	scanf("%s",filename);
	stdin->_IO_read_ptr=stdin->_IO_read_end;
	sprintf(path1,"%s%s",path,filename);	//拼接path+filename，形成最终的文件路径 
	printf("待导入文件的路径为：%s\n",path1);
	frp=fopen(path1,"r");					//打开文件 
    if(NULL==frp)							//判断打开的文件是否为空，空则报错 
    {
        perror("frp: fopen");
        sleep(5);
		return NULL;						//返回空
    }
    return frp;								//返回文件指针frp
} 

void stu_unlock(void) //解锁学生帐号
{
    int id=0;
    int j=0;
    char str[6]={};
    printf("请输入要解锁的学生学号:");
    id=id_fgets(str,6);
    while(stu[j].flag)	//通过for循环判断输入的学号是否有效
    {
    	if(id == stu[j].id)
        {
        	stu[j].count = 0;	//将该学生输错密码次数清零
            msg_show("帐号已解锁!",1.5);
            return;
        }
        j++;
    }
    msg_show("未找到该学生!",1.5);
}
