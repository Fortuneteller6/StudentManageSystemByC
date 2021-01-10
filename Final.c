#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h> 

#define MAXSIZE 100

void display();         // 主界面展示函数

void isert();           // 插入学生信息函数

void show();            // 学生信息显示示函数

void find();            // 主查询函数
void findById();        // 通过学号查询学生
void findByName();      // 通过姓名查询学生

void modify();          // 主修改函数(包括通过学号修改与删除函数)
void modifyById();      // 通过Id修改学生信息
void deleteById();      // 通过Id删除学生信息

void sort();            // 主排序函数
void sortByAvg();       // 平均分排序函数
void sortByScore1();    // 成绩1排序函数
void sortByScore2();    // 成绩2排序函数
void sortByScore3();    // 成绩3排序函数

void save();            // 文件保存函数
void load();            // 文件加载函数

void shutdown();        // 退出函数

// 学生信息结构体
struct student{
  	int id;                         //学号
  	char name[20];                  //姓名
  	char sex[4];                    //性别
  	double score1;                  //成绩1
  	double score2;                  //成绩2
  	double score3;                  //成绩3
  	double ave;                     //平均分         
};

// 定义队列的结构体
typedef struct Squeue {
	struct student data[MAXSIZE];
	int front;
	int rear;
}Squeue;

// 初始化队列
void InitQueue(Squeue* qu)
{
	qu->front = qu->rear = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        qu->data[i].id = 0;
        strcpy(qu->data[i].name, "NULL");
        strcpy(qu->data[i].sex, "NULL");   // 解决表达式必须是可修改的左值(字符串不能直接赋值)
        qu->data[i].score1 = 0.0;
        qu->data[i].score2 = 0.0;
        qu->data[i].score3 = 0.0;
        qu->data[i].ave = 0.0;
    }
}

// 判断队列是否为空
int isQueueEmpty(Squeue* qu)
{
	if (qu->front == qu->rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// 元素入队操作
int EnQueue(Squeue* qu, struct student s)
{
	//若队满则无法入队
	if ((qu->rear + 1) % MAXSIZE == qu->front)
	{
		return 0;
	}
	qu->data[qu->rear].id = s.id;
    strcpy(qu->data[qu->rear].name,  s.name);
    strcpy(qu->data[qu->rear].sex, s.sex);
    qu->data[qu->rear].score1 = s.score1;
    qu->data[qu->rear].score2 = s.score2;
    qu->data[qu->rear].score3 = s.score3;
    s.ave = (s.score1 + s.score2 + s.score3) / 3;
    qu->data[qu->rear].ave = s.ave;
    qu->rear = (qu->rear + 1) % MAXSIZE;
    return 1;
}

// 元素出队操作
int Dequeue(Squeue* qu)
{
	//若队空则无法出队
	if (qu->front == qu->rear)
	{
		return 0;
	}
	qu->front = (qu->front + 1) % MAXSIZE;
	return 1;
}

// 系统主函数入口
int main(){

    int flag = 1;
    int choice;

    Squeue *Q;
    Q = (Squeue*)calloc(20,sizeof(Squeue));
    InitQueue(Q);

    load(Q);    //完成数据的预读取

    while (flag) {

        display();

        printf("\t请在0-9之间做出选择：");

        fflush(stdin);          //清除输入设备的缓冲
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                 system("cls");
                 insert(Q);
                 break;

            case 2:
                 system("cls");
                 show(Q);
                 break;

            case 3:
                 system("cls");
                 sort(Q);
                 break;

            case 4:
                 system("cls");
                 modify(Q);
                 break;

            case 5:
                 system("cls");
                 find(Q);
                 break;     

            case 6:
                save(Q);
                shutdown();

            default:
                 system("cls");
                 continue;              
        }

    }
    return 0;
}

// 主页面展示函数
void display() {
    printf("\t************学 生 管 理 系 统**********\n");
    printf("\t1.录入学生信息\n");
	printf("\t2.显示学生信息\n");
	printf("\t3.学生成绩排序\n");
	printf("\t4.编辑学生信息\n");
	printf("\t5.查询学生成绩\n");
	printf("\t6.退出\n");
    printf("\t************学 生 管 理 系 统**********\n");
}

// 插入学生信息函数
void insert(Squeue *Q) {
    int i = 0;
    char ch;
    do
    {
         struct student s;
         printf("\n");
         printf("\t正在录入第%d个学生的信息", i + 1);

         printf("\n");
         printf("\t输入学生学号:");
         scanf("%d", &s.id);
         fflush(stdin);

         printf("\n");
         printf("\t输入学生姓名:");
         fflush(stdin);
         gets(s.name);

         printf("\n");
         printf("\t输入学生性别:");
         fflush(stdin);
         gets(s.sex);

         printf("\n");
         printf("\t输入学生成绩1:");
         scanf("%lf", &s.score1);
         fflush(stdin);

         printf("\n");
         printf("\t输入学生成绩2:");
         fflush(stdin);
         scanf("%lf", &s.score2);

         printf("\n");
         printf("\t输入学生成绩3:");
         fflush(stdin);
         scanf("%lf", &s.score3);

         printf("\n");

         EnQueue(Q,s);
         i++;

         printf("\t是否继续输入?(Y/N)");
         fflush(stdin);
         ch = getch();
         system("cls");

   }while(ch != 'n' && ch != 'N');
   system("cls");
}

// 学生信息显示示函数
void show(Squeue *Q) {
    int i;
  	char choice;
  	do{
        printf("\n");
        printf("\t班级学生信息列表\n");

      	printf("\t学号\t姓名\t性别\t成绩1\t成绩2\t成绩3\t平均值\n");
      	for(i = Q->front; i < Q->rear; i++){
            if(Q->data[i].id == 0) {  // 解决删除时候最后元素异常显示问题
                continue;
            }  
            printf("\t%d\t%s\t%s\t%.2lf\t%.2lf\t%.2lf\t%.2lf\n", Q->data[i].id, Q->data[i].name, Q->data[i].sex, Q->data[i].score1, Q->data[i].score2, Q->data[i].score3, Q->data[i].ave);
        }

      	printf("\t\t\t按任意键返回主菜单\a");
      	fflush(stdin);

      	choice = getch();

   	}while(!choice);
 	system("cls");
}

// 文件保存函数
void save(Squeue *Q) {
    FILE *fp;
    int i;

    if((fp = fopen("D://Student.txt", "w")) == NULL)
    {
        printf("\n保存失败!");
        shutdown();
    }
    
    for(i = Q->front; i < Q->rear; i++)
     {
        if(Q->data[i].id == 0) {  // 解决删除时候最后元素异常显示问题
            continue;
        }  
        fprintf(fp, "%d %s %s %lf %lf %lf %lf\t", Q->data[i].id, Q->data[i].name, Q->data[i].sex, Q->data[i].score1, Q->data[i].score2, Q->data[i].score3, Q->data[i].ave);
        //fwrite(&Q->data[i], sizeof(struct student), 1, fp);
     }

     fclose(fp);
     printf("学生信息已自动保存!\n");
}

// 文件加载函数
void load(Squeue *Q) {
    FILE *fp;
  	int i;
  	
  	if((fp = fopen("D://Student.txt", "r")) == NULL)        // 需要提前准备好文件
    {
       printf("找不到文件!\n");
       shutdown();
    }

    fseek(fp, 0, SEEK_SET);

    for(i = Q->front; i < MAXSIZE && !feof(fp); i++)
    {
        fscanf(fp, "%d %s %s %lf %lf %lf %lf\t", &Q->data[i].id, Q->data[i].name, Q->data[i].sex, &Q->data[i].score1, &Q->data[i].score2, &Q->data[i].score3, &Q->data[i].ave);
        //fread(&Q->data[i], sizeof(struct student), 1, fp);
        Q->rear++;          // 解决文件读取异常情况，指针未后移
    }

 	fclose(fp);
}

// 主查询函数
void find(Squeue *Q){
    int choice;
    int flag = 1;  // 设置标志位，结束循环
    do{
        printf("\n");
        printf("\t学生查询系统\n");  
        printf("\t1.按照学生学号查询\n");
        printf("\t2.按照学生姓名查询\n");
        printf("\t3.返回主菜单\n");
        printf("\t请输入要选择的功能:");
        fflush(stdin);
        scanf("%d", &choice);
        switch(choice)
            {
            case 1:
                system("cls");
                findById(Q);
                break;
            case 2:
                system("cls");
                findByName(Q);
                break;
            case 3:
                system("cls");
                flag = 0;
                break;
            default:
                system("cls");
                find(Q);
                break;
            }
        }while(flag);
        system("cls");
}

// 通过学号查询学生
void findById(Squeue *Q){
    int i;
    int choice;
    char as;
    do{
        printf("\n");
        printf("\t输入要查询的学生学号:\a");
        fflush(stdin);
        scanf("%d", &choice);

        for(i = Q->front; i < Q->rear; i++) {
            if(choice == Q->data[i].id)
            {
                printf("\t学号\t姓名\t性别\t成绩1\t成绩2\t成绩3\t平均值\n");
                printf("\t%d\t%s\t%s\t%.2lf\t%.2lf\t%.2lf\t%.2lf\n", Q->data[i].id, Q->data[i].name, Q->data[i].sex, Q->data[i].score1, Q->data[i].score2, Q->data[i].score3, Q->data[i].ave);
            }
        }

        printf("\t按任意键返回主菜单");
        fflush(stdin);
        as = getch();
     }while(!as);
    system("cls");
}

// 通过姓名查询学生
void findByName(Squeue *Q){
    int i;
    char str[20],as;
    do{
        printf("\n");
        printf("\t输入要查询的学生姓名:");
        fflush(stdin);
        gets(str);

        for(i = Q->front; i < Q->rear; i++) {
            if(!strcmp(Q->data[i].name,str))
            {
                printf("\t学号\t姓名\t性别\t成绩1\t成绩2\t成绩3\t平均值\n");
                printf("\t%d\t%s\t%s\t%.2lf\t%.2lf\t%.2lf\t%.2lf\n", Q->data[i].id, Q->data[i].name, Q->data[i].sex, Q->data[i].score1, Q->data[i].score2, Q->data[i].score3, Q->data[i].ave);
            }
        }

        printf("\t按任意键返回主菜单");
        fflush(stdin);
        as=getch();
     }while(!as);
    system("cls");
}

// 主修改函数(包括通过学号修改与删除函数)
void modify(Squeue *Q){
    int choice;
    int flag = 1;  // 设置标志位，结束循环
    do{
        printf("\n");
        printf("\t学生修改系统\n");  
        printf("\t1.按照学号修改学生\n");
        printf("\t2.按照学号删除学生\n");
        printf("\t3.返回主菜单\n");
        printf("\t请输入要选择的功能:");
        fflush(stdin);
        scanf("%d", &choice);
        switch(choice)
            {
            case 1:
                system("cls");
                modifyById(Q);
                break;
            case 2:
                system("cls");
                deleteById(Q);
                break;
            case 3:
                system("cls");
                flag = 0;
                break;
            default:
                system("cls");
                modify(Q);
                break;
            }
        }while(flag);
        system("cls");
}

// 通过Id修改学生信息
void modifyById(Squeue *Q){
    int i;
    int SearchId;

    printf("\t输入要修改的学生学号:");
  	fflush(stdin);
  	scanf("%d", &SearchId);

    for(i = Q->front; i < Q->rear; i++)
  	{
     	if(Q->data[i].id == SearchId){
            printf("\n");
            system("cls");
        	struct student stu;
        	printf("\t输入修改后学生信息\n");

        	Q->data[i].id = SearchId;

            printf("\t输入学生姓名:");
            fflush(stdin);
            gets(stu.name);
            strcpy(Q->data[i].name, stu.name);
            printf("\n");

        	printf("\t输入学生性别:");
        	fflush(stdin);
        	gets(stu.sex);
        	strcpy(Q->data[i].sex, stu.sex);
            printf("\n");

        	printf("\t输入学生成绩1:");
        	fflush(stdin);
        	scanf("%lf", &stu.score1);
        	Q->data[i].score1 = stu.score1;
            printf("\n");

        	printf("\t输入学生成绩2:");
        	fflush(stdin);
        	scanf("%lf", &stu.score2);
        	Q->data[i].score2 = stu.score2;
            printf("\n");

        	printf("\t输入学生成绩3:");
        	fflush(stdin);
        	scanf("%lf", &stu.score3);
        	Q->data[i].score3 = stu.score3;
            printf("\n");

			system("cls");
            printf("\t修改成功，系统自动跳转!\n");
            show(Q);
            break;
       	}
  	}
  	printf("\t删除失败!查无此人，系统自动跳转!");
    modify(Q);
}

// 通过Id删除学生信息
void deleteById(Squeue *Q){
    int num;
    printf("\t输入要删除学生的学号:");
    fflush(stdin);
    scanf("%u",&num);
    for(int i = Q->front; i < Q->rear; i++){
        if(Q->data[i].id == num){
            for (int j = i; j < Q->rear; j++)
            {
                Q->data[j] = Q->data[j + 1];
            }
            printf("\t删除成功!自动跳转查询全部学生页面!");
            show(Q);
            break;
        }
    }
    printf("\t删除失败!查无此人，系统自动跳转!");
    modify(Q);
}

// 主排序函数
void sort(Squeue *Q) {
    int choice;
    int flag = 1;  // 设置标志位，结束循环
    do{
        printf("\n");
        printf("\t学生排序系统\n");  
        printf("\t1.按照平均分排序\n");
        printf("\t2.按照成绩1排序\n");
        printf("\t3.按照成绩2排序\n");
        printf("\t4.按照成绩3排序\n");
        printf("\t5.返回主菜单\n");
        printf("\t请输入要选择的功能:");
        fflush(stdin);
        scanf("%d", &choice);
        switch(choice)
            {
            case 1:
                system("cls");
                sortByAvg(Q);
                break;
            case 2:
                system("cls");
                sortByScore1(Q);
                break;
            case 3:
                system("cls");
                sortByScore2(Q);
                break;
            case 4:
                system("cls");
                sortByScore3(Q);
                break;        
            case 5:
                system("cls");
                flag = 0;
                break;
            default:
                system("cls");
                sort(Q);
                break;
            }
        }while(flag);
        system("cls");
}

// 平均分排序函数
void sortByAvg(Squeue *Q) {
    struct student temp;   // 临时变量学生
    int i, j;
    for(i = Q->front; i < (Q->rear - 1); i++){
        for(j = Q->front; j < (Q->rear - i - 1); j++){
            if(Q->data[j].ave < Q->data[j + 1].ave){
                temp = Q->data[j];
                Q->data[j] = Q->data[j + 1];
                Q->data[j + 1] = temp;
            }
        }
    }
    show(Q);
}

// 成绩1排序函数
void sortByScore1(Squeue *Q) {
    struct student temp;   // 临时变量学生
    int i, j;
    for(i = Q->front; i < (Q->rear - 1); i++){
        for(j = Q->front; j < (Q->rear - i - 1); j++){
            if(Q->data[j].score1 < Q->data[j + 1].score1){
                temp = Q->data[j];
                Q->data[j] = Q->data[j + 1];
                Q->data[j + 1] = temp;
            }
        }
    }
    show(Q);
}

// 成绩2排序函数
void sortByScore2(Squeue *Q) {
    struct student temp;   // 临时变量学生
    int i, j;
    for(i = Q->front; i < (Q->rear - 1); i++){
        for(j = Q->front; j < (Q->rear - i - 1); j++){
            if(Q->data[j].score2 < Q->data[j + 1].score2){
                temp = Q->data[j];
                Q->data[j] = Q->data[j + 1];
                Q->data[j + 1] = temp;
            }
        }
    }
    show(Q);
}

// 成绩3排序函数
void sortByScore3(Squeue *Q) {
    struct student temp;   // 临时变量学生
    int i, j;
    for(i = Q->front; i < (Q->rear - 1); i++){
        for(j = Q->front; j < (Q->rear - i - 1); j++){
            if(Q->data[j].score3 < Q->data[j + 1].score3){
                temp = Q->data[j];
                Q->data[j] = Q->data[j + 1];
                Q->data[j + 1] = temp;
            }
        }
    }
    show(Q);
}

// 退出函数
void shutdown() {
    exit(0);
}