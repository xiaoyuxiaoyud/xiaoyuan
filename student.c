#include"student.h"

int id=0;//当前学生所在位置
int stu_cnt=0;//学生个数
//登录主程序，成功则进入学生界面完成功能
void stu_login(void)//
{
	stu_read();
	for(int i=0;i<MAX_STU;i++)
	{
		if(0!=stu[i].flag)
		stu_cnt++;
	}
	char pw[20]={};
	int ac=0;
	printf("请输入帐号（学号）：");
	if(!scanf("%d",&ac))
	{
		printf("帐号不存在！\n");
		anykey_continue();
		return;
	}
	for(id=0;id<stu_cnt;id++)
	{
		if((ac==stu[id].id))	//帐号如果存在
		{
			if(-1==stu[id].flag)
			{
				msg_show("您的帐号已归档！",1.5);//是否退学
				anykey_continue();
				return;
			}
			else if(3==stu[id].count)			//是否上锁
			{
				msg_show("您的帐号已上锁，请找老师解锁",1.5);
				anykey_continue();
				return;
			}
			else 
			{
				break;
			}
		}
		if(id==stu_cnt-1)
		{
			printf("帐号不存在！\n");
			anykey_continue();
			return;
		}
	}
	

	//密码判断
	while(1)
	{
		printf("请输入密码：");
		strcpy(pw,hidden_input());
		if(!strcmp(pw,stu[id].password))//密码正确则退出循环进入下一步
		{
			stu[id].count=0;
			break;
		}
		else 
		{
			stu[id].count++;
		}
		if(1==stu[id].count)
		{
			printf("输入错误，还有两次机会！\n");
		}
		else if(2==stu[id].count)
		{
			printf("输入错误，还有一次机会！\n");
		}
		else if(3==stu[id].count)//输错三次，保存上锁信息，退出登录
		{
			printf("密码输入错误三次，帐号已锁定，解锁请找老师！\n");	
			anykey_continue();
			return;
		}
	}

	//是否初次登录
	if (0==stu[id].firstlogin)
	{
		printf("初次登录请修改密码！\n");
		stu[id].firstlogin=1;
		while(stu_changepassword());//强制修改密码
	}

	//进入学生界面循环
	for(;;)
	{
		switch(stu_menu())	
		{
			case '1':	
				stu_checkgrade();
			break;
			case '2':	
				stu_changepassword();
			break;
			case '3':	
				stu_showmessage();
			break;					
			case '0':	
				stu_save();
			return;
		}
	}
}

int stu_menu(void)//学生界面
{
	system("clear");
	printf("你好，%s同学！\n",stu[id].name);
	puts("***************");
	puts("  1、查询成绩");
	puts("  2、修改密码");
	puts("  3、个人信息");
	puts("  0、退出系统");
	puts("***************");
	printf("请输入指令：");	
	char cmd=getch();
	printf("%c\n",cmd);	//回显
	return cmd ;
}

void stu_checkgrade(void)//成绩查询
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	double grade[stu_cnt][4];//存放每个人成绩
	memset(grade,0,sizeof(grade));
	double stuchin=stu[id].chinese,stumath=stu[id].math,stuengl=stu[id].english,//将结构体数据传入数组
		stu_all=stu[id].chinese+stu[id].math+stu[id].english;	//计算个人成绩总分
	printf("你的成绩：\n语文：%.2lf\n数学：%.2lf\n英语：%.2lf\n\
总分：%.2lf\n",stuchin,stumath,stuengl,stu_all);
	for(int i=0;i<stu_cnt;i++)//成绩存入数组，每列分别存语文数学英语总分
	{
		grade[i][0]=stu[i].chinese;
		grade[i][1]=stu[i].math;
		grade[i][2]=stu[i].english;
		grade[i][3]=stu[i].chinese+stu[i].math+stu[i].english;
	}
	double plus[4]={},max[4]={},min[4]={},avg[4]={};int cnt=0,level[4]={1,1,1,1};//分别计入单科成绩的分数
	for(int i=0;i<stu_cnt;i++)//用flag  while
	{
		if(grade[i][3]>0)//成绩存在，计算最高分最低分
		{
			cnt++;	//	计入有成绩的学生人数
			if(stuchin<grade[i][0])level[0]++;//名次
			if(stumath<grade[i][1])level[1]++;
			if(stuengl<grade[i][2])level[2]++;
			if(stu_all<grade[i][3])level[3]++;
			for(int j=0;j<4;j++)
			{
				plus[j]+=grade[i][j];//成绩累加
				if(grade[i][j]>max[j])max[j]=grade[i][j];//最大值
				if(grade[i][j]<min[j])min[j]=grade[i][j];//最小值
			}	
		}
	}
	if(0==cnt)	//	防止除0出现的错误
	{
		cnt=1;
	}
	for(int i=0;i<4;i++)
	{
		avg[i]=plus[i]/cnt;//计算平均分
	}
	printf("语文最高分：%.2lf 语文最低分：%.2lf 语文平均分：%.2lf 你的名次：%d\n",
	max[0],min[0],avg[0],level[0]);
	printf("数学最高分：%.2lf 数学最低分：%.2lf 数学平均分：%.2lf 你的名次：%d\n",
	max[1],min[1],avg[1],level[1]);
	printf("英语最高分：%.2lf 英语最低分：%.2lf 英语平均分：%.2lf 你的名次：%d\n",
	max[2],min[2],avg[2],level[2]);
	printf("总分最高分：%.2lf 总分最低分：%.2lf 总分平均分：%.2lf 你的名次：%d\n",
	max[3],min[3],avg[3],level[3]);
	anykey_continue();
}

int stu_changepassword(void)//修改密码
{
	puts("请输入新密码：");
	char new1[20],new2[20];
	strcpy(new1,hidden_input());	//隐藏输入密码
	puts("请再次输入新密码：");
	strcpy(new2,hidden_input());	//隐藏再次输入密码
	if(!strcmp(new1,new2))			//判读两次密码输入是否相等
	{
		strcpy(stu[id].password,new1);//修改密码
		puts("修改成功！");
		anykey_continue();
		return 0;
	}
	else 
	{
		puts("修改失败！");
	}
	anykey_continue();
	return 1;
}

void stu_showmessage(void)//显示信息
{
	printf("姓名：%s\n性别：%s\n学号：%d\n状态：%s\n",stu[id].name,'w'==stu[id].sex?"女":"男",stu[id].id,stu[id].flag==1?"在校":"离校");
	anykey_continue();
}
