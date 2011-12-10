#include<stdio.h>
#include<string.h>
#include<memory.h>
#include<malloc.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

//定义了存放信息的数据结构
typedef struct STUDENT_INFO {
	char Student_ID[20];
	char Student_NAME[20];
	int Theory_SCORE;
	int Experiment_SCORE;
	int Total_SCORE;
}STU_INF;

//定义了存放数据的链表
typedef struct Student_Info_llist{
	STU_INF s_info;
	struct Student_Info_llist *prev;//prev指针指向上一个链表节点
	struct Student_Info_llist *next;//next指针指向下一个链表节点
}STU_INF_LL;

char line_1[100];//用于存放从文件中读取的每行数据

//以可读形式打开文件并返回文件指针
FILE *openfile(char *filename){
	FILE *stream;
	if( (stream = fopen("score.txt", "r" )) == NULL )
	printf( "The file score.txt was not opened\n" );
	else
	printf( "The file score.txt was opened\n" );
	return stream;
}

//在链表的末尾增加一个存放有一个学生信息的节点
void append_llist(STU_INF sti,STU_INF_LL *stil){
	STU_INF_LL *pNew;
	//找到最后一个节点的指针
	STU_INF_LL *pLast = stil;
	while(pLast->next != NULL)
		{
		pLast = pLast->next;
		}
	//创建新节点
	pNew = (STU_INF_LL *)malloc(sizeof(STU_INF_LL));
	pNew->prev = pLast;
	pNew->next = NULL;
	memcpy(&pNew->s_info, &sti,sizeof(STU_INF));
	//修改新节点的前驱节点-的下指针
	pLast->next  = pNew;
}

//根据定义好的数据结构格式化读取从文件中每行的数据
void read_format(FILE *stream,STU_INF_LL *stil){
	char line[100];
	STU_INF sti;
	int i = 0;
	while(1){
		if( stream != NULL )
		{
			if(i == 0){
				fgets(line_1,100,stream);
			}
			else if( fgets( line, 100, stream ) == NULL)
				break;
			else{
				//printf("Line%3d:",i);
				//printf("%s",line);
				sscanf(line, "%s %s %d %d %d",sti.Student_ID,sti.Student_NAME,
					&sti.Theory_SCORE,&sti.Experiment_SCORE,&sti.Total_SCORE);
				append_llist(sti,stil);
			}
			i++;
		}
	}
}

//在屏幕显示链表中存放的数据信息
void display(STU_INF_LL *stil){
	system("cls");
	STU_INF_LL *stu_m;
	stu_m = stil;
	int i = 0;
	do{
		printf("Line%3d:",i);
		if(i == 0)
			printf("  %s",line_1);
		else
			printf("%10s\t%s\t%d\t%d\t%d\n",stu_m->s_info.Student_ID,stu_m->s_info.Student_NAME,
				stu_m->s_info.Theory_SCORE,stu_m->s_info.Experiment_SCORE,stu_m->s_info.Total_SCORE);
		i++;
		stu_m = stu_m->next;
	}while(stu_m != NULL);
}

//在链表中插入一个节点
void insert_llist(STU_INF_LL *stil){
	int line_num = 0;
	int i = 0;
	STU_INF *sti;
	sti = (STU_INF *)malloc(sizeof(STU_INF));//为数据结构分配额内存空间
	STU_INF_LL *p1,*p2,*p3;
	p1 = stil;
	p3 = (STU_INF_LL *)malloc(sizeof(STU_INF_LL));//为链表节点分配内存空间
	printf("Enter the line_num you want to insert:");
	scanf("%d",&line_num);//输入插入节点的编号
	printf("Enter the (Student_ID, Student_NAME, Theory_SCORE, Experiment_SCORE, Total_SCORE) seperate with (Enter):");
	scanf("%s %s %d %d %d",sti->Student_ID, sti->Student_NAME,
		&sti->Theory_SCORE, &sti->Experiment_SCORE, &sti->Total_SCORE);
	memcpy(&p3->s_info,sti,sizeof(STU_INF));
	//在链表中寻找插入节点的位置
	while(i != line_num){
		i++;
		p1 = p1->next;
	}
	//插入节点操作
	p2 = p1->prev;
	p2->next = p3;
	p3->prev = p2;
	p3->next = p1;
	p1->prev = p3;
	system("cls");
	display(stil);
}

STU_INF_LL *init_linkl(){
	STU_INF_LL *Student_info_ll;
	Student_info_ll = (STU_INF_LL *)malloc(sizeof(STU_INF_LL));
	Student_info_ll->prev = NULL;
	Student_info_ll->next = NULL;
	return Student_info_ll;
}

void exchange(STU_INF_LL *p1, STU_INF_LL *p2){
	STU_INF *stu;
	STU_INF_LL *stil_m,*stil_n;
	stil_m = p1;
	stil_n = p2;
	int size_sti = sizeof(STU_INF);
	stu = (STU_INF *)malloc(size_sti);
	if((stil_m->next != NULL)&&(stil_m->prev != NULL)){
		memcpy(stu,&stil_m->s_info,size_sti);
		memcpy(&stil_m->s_info,&stil_n->s_info,size_sti);
		memcpy(&stil_n->s_info,stu,size_sti);
	}
}

void rank_score(STU_INF_LL *stil){
	int i=0;
	STU_INF_LL *stil_1,*stil_2;
	printf("[1]: rank the item as thoery score\n");
	printf("[2]: rank the item as experiment score\n");
	printf("[3]: rank the item as total score\n");
	//选择排序方式
	scanf("%d",&i);
	cin.get();
	system("cls");
	//按theory_score排序 
	if(i == 1){
		for(stil_1 = stil->next;stil_1->next != NULL;stil_1 = stil_1->next){
			for(stil_2 = stil_1->next;stil_2 != NULL;stil_2 = stil_2->next){
				if(stil_1->s_info.Theory_SCORE < stil_2->s_info.Theory_SCORE){
					exchange(stil_1,stil_2);
				}
			}
		}
		display(stil);
	}
	//按照experiment_score排序
	else if(i == 2){
		for(stil_1 = stil->next;stil_1->next != NULL;stil_1 = stil_1->next){
			for(stil_2 = stil_1->next;stil_2 != NULL;stil_2 = stil_2->next){
				if(stil_1->s_info.Experiment_SCORE < stil_2->s_info.Experiment_SCORE){
					exchange(stil_1,stil_2);
				}
			}
		}
		display(stil);
	}
	//按照total_score排序
	else if(i == 3){
		for(stil_1 = stil->next;stil_1->next != NULL;stil_1 = stil_1->next){
			for(stil_2 = stil_1->next;stil_2 != NULL;stil_2 = stil_2->next){
				if(stil_1->s_info.Total_SCORE < stil_2->s_info.Total_SCORE){
					exchange(stil_1,stil_2);
				}
			}
		}
		display(stil);
	}
}

//删除指定行的数据
void delete_item(STU_INF_LL *stil){
	int i, line_num;
	STU_INF_LL *stil_del,*p,*n;
	stil_del = stil;
	line_num = i = 0;
	printf("enter the line number you want to delete:");
	scanf("%d",&line_num);
	for(;i < line_num;i++){
		stil_del = stil_del->next;
	}
	p = stil_del->prev;
	n = stil_del->next;
	n->prev = stil_del->prev;
	p->next = stil_del->next;
	system("cls");
	display(stil);
}

//保存经过修改后的学生信息数据
void save_item(STU_INF_LL *stil,char *filename){
	FILE *stream;
	STU_INF_LL *p;
	p = stil->next;
	stream=fopen(filename,"w");
	fprintf(stream,"%s",line_1);
	do{
		fprintf(stream,"%s\t%s\t%d\t%d\t%d\n",p->s_info.Student_ID,p->s_info.Student_NAME,
			p->s_info.Theory_SCORE,p->s_info.Experiment_SCORE,p->s_info.Total_SCORE);
		p = p->next;
	}while(p != NULL);
	fclose(stream);
	system("cls");
	display(stil);
}

void main(){
	STU_INF_LL *stil;
	char cmd[20];
	stil = init_linkl();
	char *filename = "score.txt";
	FILE *stream_score;
	stream_score = openfile(filename);
	read_format(stream_score,stil);
	fclose(stream_score);
	while(1){
		//主菜单
		printf("[rank]: rank the items\n");
		printf("[display]: display a item\n");
		printf("[insert]: insert a item\n");
		printf("[delete]: delete a item\n");
		printf("[save]: save the item\n");
		printf("[quit]: quit\n");
		scanf("%s", cmd);
		//根据输入的选择信息，执行相应的操作
		if(!strcmp(cmd, "rank"))
			rank_score(stil);
		else if(!strcmp(cmd,"display"))
			display(stil);
		else if(!strcmp(cmd, "insert"))
			insert_llist(stil);
		else if(!strcmp(cmd, "delete"))
			delete_item(stil);
		else if(!strcmp(cmd, "save"))
			save_item(stil,filename);
		else if(!strcmp(cmd, "quit"))
			exit(0);
		//system("cls");
		//clrscr();
	}
}