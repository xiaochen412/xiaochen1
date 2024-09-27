#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Book {
    char id[50];        
    char title[100];    
    char author[100];   
    char publisher[100];
    int year;
    struct Book* next;  
} book;

book* creates(FILE* f);//创建链表
void append(book* p);//增加数据
void print(book* p);//打印表格
void delete(book*p,char id[50]);//删除数据
void modify(book* p,char id[50]);//修改数据
void inquire(book* p);//查询最新出版数据
void release(book* p);//释放数据并保存修改

//创建链表
book* creates(FILE* f){
	char a[50];
	book* head = (book*)malloc(sizeof(book));
	head->next = NULL;
	book* j = head;
	book*q;
	const char *s=",";
		while(fgets(a,sizeof(a), f)){//fgets返回指针
			book* q = (book*)malloc(sizeof(book));
			strcpy(q->id,strtok(a,s));
			strcpy(q->title,strtok(NULL,s));
			strcpy(q->author,strtok(NULL,s));
			strcpy(q->publisher,strtok(NULL,s));
			q->year = atoi(strtok(NULL,s));
			j->next = q;
			j = q;	
			j ->next =NULL;
	}
	return head;
}
//打印表格
void print(book* p){
	 book *d,*j;
    d = p;//传输
    j = d->next;//取数据
	while(j!=NULL){
        printf("id:%-15s",j->id);
		printf("title:%-20s",j->title);
		printf("author:%-10s",j->author);
		printf("publisher:%-20s",j->publisher);
		printf("year:%-10d\n",j->year);
        d = j;
        j = d->next;}
	return ;
}
//增加数据
void append(book* p){
	book* q = p;//找结尾
	book* j;//接上
	while(q->next !=NULL){//找到最后一个结构体
		q = q->next;
	}
	j = (book*)malloc(sizeof(book));
	j->next =NULL;
	printf("id:");
		scanf("%s",&(j->id));
	printf("title:");
		scanf("%s",&(j->title));
	printf("author:");
		scanf("%s",&(j->author));
	printf("publisher:");
		scanf("%s",&(j->publisher));
	printf("year:");
		scanf("%d",&(j->year));
	q->next = j;//连接数据
	printf("数据增加成功\n");
	return;
}
//删除数据
void delete(book*p,char id[50]){
	book* q;
	book* d;
	q=p;
	d=q->next;
	while(strcmp(d->id,id)!=0 && d->next!=NULL)
	{
		q=d;
		d=q->next;
	}
	printf("%s",d->id);
	if (strcmp(d->id,id)!=0)
		{printf("未查询到您要删除的程序\n");
		return;}
	q->next = d->next;
	free(d);//释放删除项所占空间
	printf("删除完毕\n");
	return;
}
//修改数据
void modify(book* p,char id[50]){
	book* q = p->next;//找到要修改的数据
	char choice[20];
	while(q->next!=NULL&&strcmp(q->id,id)!=0){
		q = q->next;
	}
	if (strcmp(q->id,id)!=0)
		printf("未查询到您想要修改的数据\n");
	printf("请输入你想要修改的数据项名，如果不需要更改，请输入0退出\n");
	while(1){
	printf("您想要修改的数据项是:");
	scanf("%s",choice);//更改具体选项
	if (strcmp(choice,"id")==0)
	{printf("id:");
		scanf("%s",&(q->id));}
	else if(strcmp(choice,"title")==0)
	{printf("title:");
		scanf("%s",&(q->title));}
	else if(strcmp(choice,"author")==0)
	{printf("author:");
		scanf("%s",&(q->author));}
	else if(strcmp(choice,"publish")==0)
	{printf("publisher:");
		scanf("%s",&(q->publisher));}
	else if(strcmp(choice,"year")==0 )
		{printf("year:");
		scanf("%d",&(q->year));}
	else if (strcmp(choice,"0")==0)
		{break;}
	else{
		printf("没有找到你想修改的数据项，请重新输入\n");
	}
	}
	printf("修改完毕\n");
	return;
}
//查询最新出版数据
void inquire(book* p){
	book *d = p->next;//用于遍历
	int bigyear;//最新年份
	bigyear = d->year;
	while(d->next!=NULL){
        d = d->next;//遍历
		if (d->year>=bigyear){
			bigyear = d->year;
		}
	}
	d = p;
	while(d->next!=NULL){
        d = d->next;
		if(d->year == bigyear){
			printf("id:%-15s",d->id);
			printf("title:%-20s",d->title);
			printf("author:%-10s",d->author);
			printf("publisher:%-20s",d->publisher);
			printf("year:%-10d\n",d->year);
		}
	}
	return;
}
//释放数据并保存至副本
void release(book* p){
	FILE* pf = fopen("save.csv","w");
	book* d = (book*)malloc(sizeof(book));
	d = p;
	p = d->next;
	free(d);//释放头节点
	while(p!=NULL){
		book* q = (book*)malloc(sizeof(book));
		q = p;
		fprintf(pf,"%s,%s,%s,%s,%d\n",q->id,q->title,q->author,q->publisher,q->year);
		p = q->next;
		free(q);
	}
	printf("已清除所有数据\n");
	return;
}
int main()
{
	FILE *f = fopen("book.csv","r");//读取文本位置
	book* p = creates(f);
	int num;//储存选项信息
	char a[50];//储存编号信息
	print(p);
	printf("请选择下列要执行的操作\n");
	printf("输入1,新增书目及其基本信息\n");
	printf("输入2,删除给定编号的书目及其信息\n");
	printf("输入3,修改给定编号的书目信息\n");
	printf("输入4,输出最新出版的书目及其信息\n");
	printf("输入0,保存并退出程序\n");
	while(1){//无限循环执行操作
    printf("请输入:");
	scanf("%d",&num);
	switch (num)
	{
	case 0://保存并退出
		release(p);
		break;
	case 1://新增书目
		append(p);
		print(p);
		break;
	case 2://删除数据
		printf("您要删除的书目编号为:");
		scanf("%s",&a);
		delete(p,a);
		print(p);
		break;
	case 3://修改数据
		printf("您要修改的书目编号为:");
		scanf("%s",&a);
		modify(p,a);
		print(p);
		break;
	case 4://输出最新出版时间的书目信息
		inquire(p);
        break;
	default:
		printf("输入内容错误，请重新输入\n");
		break;
	}
	if (num ==0){
		break;
	}
	}
    printf("感谢您的使用");//结束语
	return 0; 
    }
