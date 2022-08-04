#include "mis.h"
#include "process.h"
#include "student.h"
#include "teacher.h"



int main(void)
{
	stu=calloc(sizeof(Student),MAX_STU);	//为学生结构体申请内存
	tea=calloc(sizeof(Teacher),MAX_TEA);	//申请内存过多 改*/
	do
	{
		system("clear");
		puts("*****教务管理系统*****\n");
		puts("1、校长端\n");
		puts("2、教师端\n");
		puts("3、学生端\n");
		puts("4、退出系统\n");
		puts("********************\n");
		puts("请选择功能：\n");
		switch(getch())
		{
			case '1':
				admin_main();	//校长系统
				break;
			case '2':
				tea_login();    //教师系统
				break;
			case '3':
				stu_login();    //学生系统
				break;
			case '4':
				free(tea);      //释放内存
				free(stu);
				return 0;

		}
	stdin->_IO_read_ptr=stdin->_IO_read_end;	
	}while(1);
}
