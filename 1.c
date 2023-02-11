#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define leapYear(y)  ((y%4==0)&&(y%100!=0)||(y%400==0))    //宏定义,判断是否是闰年

struct date
{
    int years;
    int months;
    int days;
};

typedef struct book
{
    char book_num[10];				//书号
    char book_name[20];				//书名
    char book_at_name[30];			//作者名
    char book_cp_name[30];			//出版社
    float book_price;				//价格
    int book_rest;					//库存
    int book_time;                  //图书被借阅次数
    struct book *next;				//下本书
} Book;

/*存储学生的信息*/
typedef struct Student
{
    char student_num[20];           //学生学号
    char student_psw[20];           //学生密码
    char student_id[30];            //学生身份证
    char student_name[20];          //学生姓名
    char student_sex[10];           //学生性别
    char student_bsd[20];           //学生生日
    char student_phone[20];         //学生手机号
    char student_borrow[10][20];    //学生借的书的编号
    char student_last[10][25];      //最晚还书日期
    struct Student *next;             //下一个学生
} Student;

typedef struct manager
{
    char man_name[15];				//管理员姓名
    char man_acc[20];				//管理员账号
    char man_passw[15];				//管理员密码
    struct manager *next;			//下个管理员
} Manager;

Book *Book_head;
Student *Student_head;
Manager *Manager_head;

void show_main(void);
//主界面
void show_stu(void);
//学生端
void show_stu_enter(void);
//学生页
void show_manager(void);
//管理员端
void show_manager_enter(void);
//管理员页
Book *Book_load(void);
//将书籍文件中的信息加载至书籍链表
Student *Student_load(void);
//将学生文件中的信息加载至学生链表
Manager *Manager_load(void);
//将管理员文件的信息加载至管理员链表
void Student_Port(void);
//学生端口
void Manager_Port(void);
//管理员端口
void Student_Login(void);
//学生端登录
void Student_Register(void);
//学生注册账号
void Find_Password(void);
//学生找回密码
void Password_Input(char *Password);
//输入密码函数
int Password_Text(char *Password_temp);
//检测密码
Student *Find_Num(char *Stu_num);
//按学号查找学生
int Password_Text_Find(char *Password);
//找回密码身份验证密码验证
void Stu_Borrow(Student *Stu_num);
//学生借书
void Stu_Back(Student *Stu_num);
//学生还书
void Find_Book(void);
//按照书名或者图书编号查找书
void Find_Theborrow(Student *Stu_num);
//学生查看所借书
void Change_Stupassword(Student *Stu_num);
//学生修改密码
Book *Find_BookofName(char *Book_num);
//按书号查找书
void Print_Book(void);
//打印书单
Book *Book_exit(char *Book_num);
//寻找该书是否存在
int Ifborrow(Student *Stu_num,char *Book_num);
//查询学生是否借过此书
void Print_Borbook(Student *Stu_num);
//打印所借书街
void Bake_Book(Student *Stu_num,char *Book_num);
//还书具体操作
void Manager_Login(void);
//管理员登录
Manager *Manager_check(char *Manager_num);
//核对管理员账号
void Manager_Add_Book(void);
//管理员上架书籍
void Manager_Down_Book(void);
//管理员下架书籍
void Manager_Look_Book(void);
//管理员浏览书架
void book_deadline(void);
//管理员输出还有一周到期的图书信息
void Manager_Manager_Stu(void);
//管理员管理学生
void Manager_Change_Password(Manager *Man_num);
//管理员修改密码
void Lookofnum(void);
//编号升序查看书架
void Lookofrest(void);
//库存升序查看书架
void Lookstayenum(void);
//类别查看书架
void Lookoftime(void);
//借阅次数升序查看书架
void Lookofprice(void);
//价格升序查看
void Manager_Print_Book(void);
//管理员打印书架
void Manager_Add_Book1(void);
//增加库存
void Manager_Add_Book2(void);
//上架新书
void Save_Book(void);
//保存书籍链表至文件
void Save_Student(void);
//保存学生链表至文件
void Save_Manger(void);
//保存管理员链表至文件
void Massage_Save(void);
//所有信息保存至文件
void Manager_Look_Stu(void);
//管理员查看学生名单
void Manager_LookBook_Stu(void);
//管理员查看学生的借书情况
void Manager_Return_Stu(void);
// 管理员强制学生还书
void Manager_Del_Stu(void);
// 删除学生号码并归还所有书籍
Student *Find_Stu(char *Stu_Stuty);
//按学号查学生

int main(void)
{
//    system("color DE");
    Book_head=(Book *)malloc(sizeof(Book));//初始化Book_head，并分配Book结构体大小的内存
    Student_head=(Student *)malloc(sizeof(Student));//初始化Student_head，并分配Student结构体大小的内存
    Manager_head=(Manager *)malloc(sizeof(Manager));//初始化Manager_head，并分配Manager结构体大小的内存

    Book_head->next=Book_load();//用函数从存储图书的文本文件中读取数据到Book_head链表中
    Student_head->next=Student_load();//用函数从存储学生数据的文本文件中读取数据到Student_head链表中
    Manager_head->next=Manager_load();//用函数从存储管理员数据的文本文件中读取数据到Manager_head链表中

    char ma='1';

    while(ma!='3')
    {
        show_main();
        printf("\t\t\t\t");
        scanf("%c",&ma);
        while(getchar()!='\n');
        switch(ma)
        {
        case '1':
            Student_Port();
            break;
        case '2':
            Manager_Port();
            break;
        case '3':
            Massage_Save();
            break;
        default:
            printf("\t\t\t\t输入错误，请重新输入\n");
            break;
        }
    }
    system("PAUSE");
    return 0;
}

void show_main(void)
{
    printf(
        "          ]@@@@@@@@OOOOO@@@@@@@@@OOOOO=@OO@OOOO*@@                   @@@@@@@@@@   \n"
        "        @@@`@OOOOOOOOOOOOOOOOO@@@@@OOO^@@OOOOOO^O@              ,@@@@@       @@@    \n"
        "       @@^=OOOOOOOOOOOOOOOOOOOOO@@@@O@O=@@@@OOO O@          ,@@@@O`          @@    \n"
        "     @@@`@OOOO@@@@@@@@@@@@@@@@OOO@@@@O^=@@@OOO^=@^       ,@@@O`       ***   @@ @@@@@@@@O    \n"
        "    @@@,OOO@@@OOOOOOOOOOOOO@@@@@@@@@@O@@@@OOo@@@@      ,@@@`      ***      @@@@@@`    @@@      \n"
        "   @@^@OO@OOOOOOOOOOO@@@@@@@@@@@@@@@@@@@@@@@@@`      ,@@@      ,@oOOOo`   @@@@`    *  ,@@^      \n"
        "  @@^OO@OOOOOOOOOO@@@@O@O@@@@@@@@@@@@@@@@O@@@@     ,@@O*    @Ooooooooo^ @@@O`   ***    =@@      \n"
        " =@@=OOOOOOOOOOO@@@OO@@@@@@@@@@@@@@@@@@@@@@@O@@@  @@O`   *@oooooooooo@,@@@`   *** ***   @@^     \n"
        " @@ @OOOOOOOOO@@@OO@@@@@@@@@@@@@@@@@@@@@@@@@@OO@@@@@    ,@OOOOOOoooo@,@@@  =oooooO^     @@@     \n"
        " @@ OOOOOOOOO@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,@@@@@@@@@@@@@@@@@@@@@@@@ *ooooooooo`    =@@     \n"
        " @@`=OOOOOO@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@`             *@@@@@@Ooooooooo^    =@@     \n"
        " ,@@`,@OO@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,@@@O`                      [@@@Ooooooo@     @@^     \n"
        "   ,@@@]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@^                             @@@O@ooo^   , @@`     \n"
        "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@                                 @@@[@O^    =@@      \n"
        "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`@@@     xxxx                             @@@O^   =@@^     \n"
        "      @@@@@,@@@@@@@@@@@@@@@@@@@@@@@@`@@@@    xxxxxxx                              @`   @@@       \n"
        "      @@@@@@@@@@@@@@@@@@@@@@@@@@@@O O@O       xxxx                                @@^ @@@       \n"
        "       @@@@*@@@@@@@@@@@@@@@@@@@@@@^ @@                $$$       xxxx               @@O@@          @@            @@                 @@@@@@ \n"
        "        @@@@@@@@@@@@@@@@@@@@@@@@@@O @@@                |      xxxxxxx              @@@@           @@       @@@@@@@@@@@@@@@@@     @@   @@`\n"
        "        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@               |       xxxxx               @@@`      @@@  @@ @@@       @@   @@        @@@@@@@@@@@@@  \n"
        "         @@@@@@@@@@@@@@@@@@@@@@@@@@@@`@@@@`        ^^^ | ^^^                      @@        @@@   @@  @@@     @@@@` @@  @@@   @@   @@    @@    \n"
        "          @@@@@@@@@@@@@@@@@@@@@@@@@@@*O@@@@@@@@@`    ^^^^^                       @@^       @@@    @@   @@@    @@ @@`@@@@@`    @@@@@@@@@@@@@    \n"
        "          @@@@@@@@@@@@@@@@@@@@@@@@@@O,O`    @@@@@@@                             @@        @@@     @@    @@@  @@    @@@@`          @@@@      @    \n"
        "          @@@=@@@@@@@@@@@@@@@@@@@@@@^ ]          @@@@@                         @@`                @@        @@   @@@  @@@       @@@ @@  @@  @    \n"
        "           @@=@@@@@@@@@@@@@@@@@@@@@@@=@@@            @@@@                      @@`             @@@@@       @@ @@@        @@@  @@@    @@@@@@@@` \n"
        "           =@^O@@@@@@@@@@@@@@@@@@@@@@@,@@@`            @@@@                    @@              \n"
        "           =@@=@@@@@@@@@@@@@@@@@@@@@@@@`@@@@@            @@@@                  @@              \n"
        "            @@=@@@@@@@@@@@@@@@@@@@@@@@@@,@O@@@@@           @@@@                @@              \n"
        "            =@@O@@@@@@@@@@@@@@@@@@@@@@@^ `    @@@@          @@@@                @@           @@@@@@@@@@@@@@@       @@@  @@       @@      @@\n"
        "            ,@@=@@@@@@@@@@@@@@@@@@@@@@@O,@@*                 @@@@                @@          @@   @@      @@  @@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@   \n"
        "             @@^@@@@@@@@@@@@@@@@@@@@@@@^=@O                                       @@         @@ @@@@@@@@@ @@       @@@   @@   @@@ @@ @@@@@@@@@ @   \n"
        "             =@O=@@@@@@@@@@@@@@@@@@@@@O O@^                                        @@`       @@@` @@@@@   @@       @@@   @@   @@@@@` @@     @@  \n"
        "              @@@O@@@@@@@@@@@@@@@@@@@@@ O@^                                         @@@      @@@@@@`  @@@@@@ @@@@@@@@@@@@@@@@   @@   @@@@@@@@@  \n"
        "              =@@=@@@@@@@@@@@@@@@@@@@@^ O@^                 请选择                   @@@     @@    @@@@@  @@       @@@     @@   @@   @@@@@@@@@  \n"
        "               @@^O@@@@@@@@@@@@@@@@@@@^ O@^                                           @@@    @@ @@@@@@@@@ @@       @@@ @@@@@@   @@@@ @@     @@ \n"
        "               =@@=@@@@@@@@@@@@@@@@@@@^ =@^         ★-·-·-·-·-·-·★             @@    @@@@@@@@@@@@@@@       @@@   @@@    @@@  @@@@@@@@@  \n"
        "                @@@O@@@@@@@@@@@@@@@@@@@  @@         |     1、学生端      |              @@     \n"
        "                ,@@o@@@@@@@@@@@@@@@@@@@` O@^        |     2、管理员端    |              @@@@@   \n"
        "                 =@OO@@@@@@@@@@@@@@@@@@@ ,OO        |     3、退出        |              @@@*[@@   \n"
        "                  @@o@@@@@@@@@@@@@@@@@@@^ =@@       ★-·-·-·-·-·-·★              @@^    @@ \n"
        "                  ,@@O@@@@@@@@@@@@@@@@@@O ,@@^                                          @@`    @@ \n"
        "                   @@OO@@@@@@@@@@@@@@@@@@@ ,@@@                                        @@@     @@`\n"
        "                    @@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@^                                  O@O     @@@ \n"
        "                    =@@O@@@@@@@@@@@@@@@@@@@@@O`                                      @@O    @@@  \n"
        "                     @@@@@@@@@@@@@@@@@@^@@@`                                     ,@@@   @@@@@@    \n"
        "                      @@@O@@@@@@@@@@@@@ O^                                 ]]@@@@@@`              \n"
        "                       @@`O@@@@@@@@@@@@`[@^@O@]]]]]]]]]]OO@@O ,O`    @@@@@@@O[[                   \n");
//    printf("\n\n\n\t\t\t\t\t\t小灰兔图书馆");
//    printf("\n\t\t\t\t**********************************************\n\n");
//    printf("\t\t\t\t\t\t1、学生端\n");
//    printf("\t\t\t\t\t\t2、管理员端\n");
//    printf("\t\t\t\t\t\t3、退出\n");
//    printf("\n\t\t\t\t**********************************************\n\n");
}
void show_stu(void)
{
    system("CLS");
    printf("\n\n\n\t\t\t\t\t\t学生界面");
    printf("\n\t\t\t\t**********************************************\n\n");
    printf("\t\t\t\t\t\t1、登录\n");
    printf("\t\t\t\t\t\t2、注册\n");
    printf("\t\t\t\t\t\t3、找回密码\n");
    printf("\t\t\t\t\t\t4、返回\n");
    printf("\n\t\t\t\t**********************************************\n\n");
}
void show_stu_enter(void)
{
    system("CLS");
    printf("\n\n\n\t\t\t\t\t    学生页面\n");
    printf("\t\t\t****************************************************\n");
    printf("\n\t\t\t\t\t1、借书\n");
    printf("\t\t\t\t\t2、还书\n");
    printf("\t\t\t\t\t3、查询图书\n");
    printf("\t\t\t\t\t4、查看自己的借书情况\n");
    printf("\t\t\t\t\t5、修改密码\n");
    printf("\t\t\t\t\t6、返回\n");
    printf("\n\t\t\t****************************************************\n");
}
void show_manager(void)
{
    system("CLS");
    printf("\n\n\n\t\t\t\t\t\t管理员界面");
    printf("\n\t\t\t\t**********************************************\n\n");
    printf("\t\t\t\t\t\t1、登录\n");
    printf("\t\t\t\t\t\t2、返回\n");
    printf("\n\t\t\t\t**********************************************\n\n");
}
void show_manager_enter(void)
{
    system("CLS");
    printf("\n\n\n\t\t\t\t\t    管理员页\n");
    printf("\t\t\t****************************************************\n");
    printf("\n\t\t\t\t\t1、上架书籍\n");
    printf("\t\t\t\t\t2、下架书籍\n");
    printf("\t\t\t\t\t3、浏览书架\n");
    printf("\t\t\t\t\t4、管理学生账号\n");
    printf("\t\t\t\t\t5、修改密码\n");
    printf("\t\t\t\t\t6、退出\n");
    printf("\n\t\t\t****************************************************\n");
}

/*管理员端*/
void Manager_Port(void)
{
    char mp='1';

    while(mp!='2')
    {
        show_manager();
        printf("\t\t\t\t");
        scanf("%c",&mp);
        while(getchar()!='\n');
        switch(mp)
        {
        case '1':
            Manager_Login();
            break;
        case '2':
            system("CLS");
            break;
        default:
            printf("\t\t\t\t输入错误，请重新输入\n");
            Sleep(3000);
            break;
        }
    }
}
/*管理员登录*/
void Manager_Login(void)
{
    char Manager_num[20];
    char ml='1';
    Manager *t;
    printf("\n\t\t\t\t账号：");
    gets(Manager_num);
    t=Manager_check(Manager_num);
    if(!t)
    {
        printf("\t\t\t\t抱歉，账号不存在\n");
        printf("\t\t\t\t按任意键退出");
        getchar();
        return;
    }
    printf("\t\t\t\t密码：");
    if(Password_Text_Find(t->man_passw)==0)
    {
        printf("\n\t\t\t\t已经错误输入密码三次，将退出登录系统···\n");
        Sleep(5000);
        return;
    }
    Sleep(500);
    printf("\n\t\t\t\t登录中···\n");
    Sleep(500);
    printf("\t\t\t\t登录成功···\n");
    Sleep(500);
    printf("\t\t\t\t正在加载···\n");
    Sleep(1000);


    while(ml!='6')
    {
        show_manager_enter();
        printf("\t\t\t");
        scanf("%c",&ml);
        while(getchar()!='\n');
        switch(ml)
        {
        case '1':
            Manager_Add_Book();
            break;
        case '2':
            Manager_Down_Book();
            break;
        case '3':
            Manager_Look_Book();
            break;
        case '4':
            Manager_Manager_Stu();
            break;
        case '5':
            Manager_Change_Password(t);
            break;
        case '6':
            break;
        default:
            printf("\t\t\t\t输入错误，请重新输入\n");
            Sleep(3000);
            break;
        }
    }



}
/*核对管理员账号*/
Manager *Manager_check(char *Manager_num)
{

    Manager *t=Manager_head->next;
    while(t)
    {
        if(strcmp(Manager_num,t->man_acc)==0)
            break;
        t=t->next;
    }
    return t;
}
/*管理员查看书架*/
void Manager_Look_Book(void)
{
    char ml;
    system("CLS");
    printf("\n\n\n\n\t\t\t\t****************************************************\n");
    printf("\t\t\t\t\t\t请选择浏览的方式\n");
    printf("\t\t\t\t****************************************************\n");
    printf("\t\t\t\t1、按编号升序浏览书架\n");
    printf("\t\t\t\t2、按库存升序浏览书架\n");
    printf("\t\t\t\t3、按价格升序浏览书架\n");
    printf("\t\t\t\t4、按借阅次数降序浏览书架\n");
    printf("\t\t\t\t5、按借类别浏览书架\n");
    printf("\t\t\t\t6、输出借出到期或1周内将到期的图书信息\n\n");

    printf("\t\t\t\t");
    scanf("%c",&ml);
    while(getchar()!='\n');
    switch(ml)
    {
    case '1':
        Lookofnum();
        break;
    case '2':
        Lookofrest();
        break;
    case '3':
        Lookofprice();
        break;
    case '4':
        Lookoftime();
        break;
    case '5':
        Lookstayenum();
        break;
    case '6':
        book_deadline();
        break;
    default:
        printf("\t\t\t输入错误\n");
        break;
    }
    printf("\t\t\t按任意键退出");
    getch();
    return;
}
//编号升序查看书架
void Lookofnum(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t暂无书籍\n");
        return;
    }
    if(Book_head->next->next==NULL)
    {
        return;
    }
    Book *p1,*p2,*p3,*end,*tem;
    Book *head=Book_head;
    end=NULL;
    while(head->next!=end)
    {
        for(p1=head,p2=p1->next,p3=p2->next; p3!=end; p1=p1->next,p2=p2->next,p3=p3->next)
        {
            if((strcmp(p2->book_num,p3->book_num))>0)
            {
                p1->next=p2->next;
                p2->next=p3->next;
                p3->next=p2;
                tem=p2;
                p2=p3;
                p3=tem;
            }

        }
        end=p2;
    }
    Manager_Print_Book();
}
//库存升序查看书架
void Lookofrest(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t暂无书籍\n");
        return;
    }
    if(Book_head->next->next==NULL)
    {
        return;
    }
    Book *p1,*p2,*p3,*end,*tem;
    Book *head=Book_head;
    end=NULL;
    while(head->next!=end)
    {
        for(p1=head,p2=p1->next,p3=p2->next; p3!=end; p1=p1->next,p2=p2->next,p3=p3->next)
        {
            if(p2->book_rest > p3->book_rest)
            {
                p1->next=p2->next;
                p2->next=p3->next;
                p3->next=p2;
                tem=p2;
                p2=p3;
                p3=tem;
            }

        }
        end=p2;
    }
    Manager_Print_Book();
}
//借阅次数降序查看书架
void Lookoftime(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t暂无书籍\n");
        return;
    }
    if(Book_head->next->next==NULL)
    {
        return;
    }
    Book *p1,*p2,*p3,*end,*tem;
    Book *head=Book_head;
    end=NULL;
    while(head->next!=end)
    {
        for(p1=head,p2=p1->next,p3=p2->next; p3!=end; p1=p1->next,p2=p2->next,p3=p3->next)
        {
            if(p2->book_time < p3->book_time)
            {
                p1->next=p2->next;
                p2->next=p3->next;
                p3->next=p2;
                tem=p2;
                p2=p3;
                p3=tem;
            }

        }
        end=p2;
    }
    Manager_Print_Book();
}
//价格升序查看书架
void Lookofprice(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t暂无书籍\n");
        return;
    }
    if(Book_head->next->next==NULL)
    {
        return;
    }
    Book *p1,*p2,*p3,*end,*tem;
    Book *head=Book_head;
    end=NULL;
    while(head->next!=end)
    {
        for(p1=head,p2=p1->next,p3=p2->next; p3!=end; p1=p1->next,p2=p2->next,p3=p3->next)
        {
            if(p2->book_price > p3->book_price)
            {
                p1->next=p2->next;
                p2->next=p3->next;
                p3->next=p2;
                tem=p2;
                p2=p3;
                p3=tem;
            }

        }
        end=p2;
    }
    Manager_Print_Book();
}

//类别查看书架
void Lookstayenum(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t暂无书籍\n");
        return;
    }
    if(Book_head->next==NULL)
    {
        return;
    }
    Book *p;
    Book *head=Book_head;
    printf("\n\t\t\t\t\t\t教材类\n");                                          //输出教材类
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    for(p=head; p!=NULL; p=p->next)
    {

        if(atoi(p->book_num)/1000==1)
        {
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   p->book_num,p->book_name,p->book_at_name,
                   p->book_cp_name,p->book_price,p->book_rest,p->book_time);
        }

    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");

    printf("\n\t\t\t\t\t\t文学类\n");                                          //输出文学类
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    for(p=head; p!=NULL; p=p->next)
    {

        if(atoi(p->book_num)/1000==2)
        {
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   p->book_num,p->book_name,p->book_at_name,
                   p->book_cp_name,p->book_price,p->book_rest,p->book_time);
        }

    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");

    printf("\n\t\t\t\t\t\t政治类\n");                                          //输出政治类
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    for(p=head; p!=NULL; p=p->next)
    {

        if(atoi(p->book_num)/1000==3)
        {
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   p->book_num,p->book_name,p->book_at_name,
                   p->book_cp_name,p->book_price,p->book_rest,p->book_time);
        }

    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");

    printf("\n\t\t\t\t\t\t法律类\n");                                          //输出法律类
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    for(p=head; p!=NULL; p=p->next)
    {

        if(atoi(p->book_num)/1000==4)
        {
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   p->book_num,p->book_name,p->book_at_name,
                   p->book_cp_name,p->book_price,p->book_rest,p->book_time);
        }

    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");

    printf("\n\t\t\t\t\t\t经济类\n");                                          //输出经济类
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    for(p=head; p!=NULL; p=p->next)
    {

        if(atoi(p->book_num)/1000==5)
        {
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   p->book_num,p->book_name,p->book_at_name,
                   p->book_cp_name,p->book_price,p->book_rest,p->book_time);
        }

    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");

    printf("\n\t\t\t\t\t\t历史类\n");                                          //输出历史类
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    for(p=head; p!=NULL; p=p->next)
    {

        if(atoi(p->book_num)/1000==6)
        {
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   p->book_num,p->book_name,p->book_at_name,
                   p->book_cp_name,p->book_price,p->book_rest,p->book_time);
        }

    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");

    printf("\n\t\t\t\t\t\t医学类\n");                                          //输出医学类
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    for(p=head; p!=NULL; p=p->next)
    {

        if(atoi(p->book_num)/1000==7)
        {
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   p->book_num,p->book_name,p->book_at_name,
                   p->book_cp_name,p->book_price,p->book_rest,p->book_time);
        }

    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");

     printf("\n\t\t\t\t\t\t地理类\n");                                          //输出地理类
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    for(p=head; p!=NULL; p=p->next)
    {

        if(atoi(p->book_num)/1000==8)
        {
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   p->book_num,p->book_name,p->book_at_name,
                   p->book_cp_name,p->book_price,p->book_rest,p->book_time);
        }

    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");
}

void Manager_Print_Book(void)
{
    Book *t=Book_head->next;
    if(t==NULL)
    {
        printf("\t\t没有任何书籍信息\n");
        return;
    }
    printf("\n\n\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    while(t)
    {
        printf("\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
               t->book_num,t->book_name,t->book_at_name,
               t->book_cp_name,t->book_price,t->book_rest,t->book_time);
        t=t->next;
    }
    printf("\n\t*************************************************");
    printf("********************************************************\n\n\n");
}

//管理员输出还有一周到期的图书信息
int days_date(struct date s)				//以2022-00-00时为基准，计算过去了多少天
{
    int days_on_month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; //分别对应1到12月的天数，a[0]空着
    int i,sum=0;								//统计天数
    for (int i = 2022; i < s.years; i++)      //年份
    {
        if (leapYear(i))				//判断是否是闰年
            sum += 366;
        else sum += 365;
    }

    if (leapYear(i))
        days_on_month[2]=29;                //闰年二月为29天
    else
        days_on_month[2]=28;                 //这步不可以省略
    for (int k = 1; k < s.months; k++)		 //月份
        sum += days_on_month[k];

    return sum+s.days;						 //加上天数 返回
}

int diff(struct date s1, struct date s2)      //计算两个时间段，天数差函数
{
    return days_date(s1)-days_date(s2);
}

int countdays(char ch[])
{
    char a[3][5]= {0};
    int i,j=0,k=0;
    for(i=0; i<15; i++)
    {
        if(ch[i]=='-')
        {
            k++;
            j=0;
        }
        if('0'<=ch[i]&&ch[i]<='9'&&k==0)
        {
            a[0][j]=ch[i];
            j++;
        }
        else if('0'<=ch[i]&&ch[i]<='9'&&k==1)
        {
            a[1][j]=ch[i];
            j++;
        }
        else if('0'<=ch[i]&&ch[i]<='9'&&k==2)
        {
            a[2][j]=ch[i];
            j++;
        }
    }

    struct date s1,s2;
    s1.years=atoi(a[0]);
    s1.months=atoi(a[1]);
    s1.days=atoi(a[2]);
    time_t timep;//记录当前时间
    time(&timep);
    struct tm *p;
    p=localtime(&timep);
    s2.years=p->tm_year+1900;
    s2.months=p->tm_mon+1;
    s2.days=p->tm_mday;
    return diff(s1,s2);
}

void book_deadline(void)
{
    Student *t=Student_head->next;
    printf("\t\t\t\t正在查找借出到期或1周内将到期的图书信息···\n");
    Sleep(1000);
    if(!t)
    {
        printf("\n\t\t\t\t抱歉，暂无学生借阅图书\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    int tem=0;
    while(t)
    {
        Book *a;
        for(int i=0; i<10; i++)
        {
            if(strcmp(t->student_borrow[i],"0")!=0)
            {
                if(countdays(t->student_last[i])<=7)
                {
                    tem=1;
                    break;
                }
            }
        }
        t=t->next;
    }
    if(tem==0)
        {
            printf("\n\n\t\t\t\t暂无到期或1周内将到期的图书\n\n");
            return;
        }
    t=Student_head->next;
    printf("\n\t*********************************************");
    printf("*********************************************************\n");
    printf("\t %-10s%-20s%-20s%-10s%-20s%-10s\n\n",
           "编号","书名","借书学生","价格","最晚还书时间","超时天数");
    while(t)
    {
        Book *a;
        for(int i=0; i<10; i++)
        {
            if(strcmp(t->student_borrow[i],"0")!=0)
            {
                if(countdays(t->student_last[i])<=7)
                {
                    a=Find_BookofName(t->student_borrow[i]);
                    printf("\t %-10s%-20s%-20s%-10.2f%-20s%-10d\n",
                           a->book_num,a->book_name,t->student_name,
                           a->book_price,t->student_last[i],(0-countdays(t->student_last[i])));
                }
            }
        }
        t=t->next;
    }
    printf("\t*********************************************");
    printf("*********************************************************\n");
    return;
}

/*管理员修改密码*/
void Manager_Change_Password(Manager *Man_num)
{
    char password_tem[20];
    printf("\t\t加载中···\n");
    Sleep(500);
    printf("\t\t请输入原密码：");
    if(Password_Text_Find(Man_num->man_passw)==0)
    {
        printf("\n\t\t已经错误输入密码三次，将退出修改密码系统···\n");
        Sleep(1500);
        return;
    }
    printf("\n\t\t验证中···\n");
    Sleep(1000);
    printf("\t\t验证成功！\n");
    Sleep(500);
    printf("\t\t请输入新密码(6~10位)：");
    Password_Input(password_tem);
    printf("\n\t\t请再次输入新密码：");
    if(Password_Text(password_tem)==0)
    {
        printf("\t\t已经错误输入密码三次，将退出修改密码系统···\n");
        Sleep(1500);
        return;
    }
    Man_num->man_passw[0]='\0';
    strcat(Man_num->man_passw,password_tem);
    Sleep(500);
    printf("\n\t\t请稍等，正在修改···\n");
    Sleep(1000);
    printf("\t\t···\n");
    Sleep(1000);
    printf("\t\t···\n");
    Sleep(1000);
    printf("\t\t恭喜！修改成功！\n");
    printf("\t\t按任意键退出");
    getch();
}
/*上架书籍*/
void Manager_Add_Book(void)
{


    char mab='1';

    while(mab!='3')
    {
        system("CLS");
        printf("\n\n\n\n\t\t\t\t\t\t请选择上架的种类\n");
        printf("\t\t\t\t****************************************************\n");
        printf("\n\t\t\t\t1、增加库存\n");
        printf("\t\t\t\t2、上架新书\n");
        printf("\t\t\t\t3、退出\n");
        printf("\n\t\t\t\t****************************************************\n");
        printf("\n\t\t\t\t");
        scanf("%c",&mab);
        while(getchar()!='\n');
        switch(mab)
        {
        case '1':
            system("CLS");
            Manager_Add_Book1();
            break;
        case '2':
            Manager_Add_Book2();
            break;
        case '3':
            break;
        default:
            printf("\t\t\t输入错误，请重新输入\n");
            Sleep(3000);
            break;
        }
    }
}
void Manager_Add_Book1(void)
{
    Book *t;
    int n;
    char ch[20];
    Lookofnum();
    if(!Book_head->next)
    {
        printf("\t\t\t\t无法增加库存\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\t\t\t\t输入新增书的编号:");
    gets(ch);
    t=Find_BookofName(ch);
    if(!t)
    {
        printf("\t\t\t\t抱歉，无此书\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\t\t\t\t输入新增的数量：");
    scanf("%d",&n);
    getchar();
    t->book_rest+=n;
    Sleep(500);
    printf("\t\t\t\t正在增加···\n");
    Sleep(500);
    printf("\t\t\t\t成功增加%d本书籍\n",n);
    printf("\t\t\t\t按任意键退出");
    getch();
}
void Manager_Add_Book2(void)
{

    printf("\t\t\t\t请输入以下信息：\n");
    Book *new=(Book *)malloc(sizeof(Book));
    new->next=NULL;
    Book *t=Book_head;
    printf("\t\t\t\t★-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·★\n");
    printf("\t\t\t\t|                注意：编号为4位数    开头数字代表图书类别                 |\n");
    printf("\t\t\t\t|                       录入信息时不能加空格！                             |\n");
    printf("\t\t\t\t|      1【教材类】     2【文学类】     3【政治类】     4【法律类】         |\n");
    printf("\t\t\t\t|      5【经济类】     6【历史类】     7【医学类】     8【地理类】         |\n");
    printf("\t\t\t\t★-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·★\n");
    printf("\t\t\t\t书籍编号：");
    gets(new->book_num);
    if(Find_BookofName(new->book_num))
    {
        free(new);
        printf("\t\t\t\t该书已上架过，请选择增加库存\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\t\t\t\t书名：");
    gets(new->book_name);
    printf("\t\t\t\t作者：");
    gets(new->book_at_name);
    printf("\t\t\t\t出版社：");
    gets(new->book_cp_name);
    printf("\t\t\t\t价格：");
    scanf("%f",&new->book_price);
    getchar();
    printf("\t\t\t\t库存：");
    scanf("%d",&new->book_rest);
    new->book_time=0;
    getchar();
    Sleep(500);
    printf("\t\t\t\t正在上架···\n");
    Sleep(500);
    printf("\t\t\t\t···\n");
    Sleep(500);
    printf("\t\t\t\t···\n");
    Sleep(500);
    printf("\t\t\t\t上架成功！\n");
    while(t->next)
    {
        t=t->next;
    }
    t->next=new;
    printf("\t\t\t\t按任意键退出");
    getch();
}
/*管理员下架书籍*/
void Manager_Down_Book(void)
{
    char book_num[20];
    Book *t=Book_head->next;
    Lookofnum();
    if(!t)
    {
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\t\t\t\t请输入需下架的书籍编号：");
    gets(book_num);
    t=Find_BookofName(book_num);
    if(!t)
    {
        printf("\t\t\t\t抱歉，无此书籍\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    t->book_rest=0;
    Sleep(500);
    printf("\t\t\t\t正在下架···\n");
    Sleep(500);
    printf("\t\t\t\t下架成功！\n");
    printf("\t\t\t\t按任意键退出");
    getch();

}

/*管理员管理学生*/
void Manager_Manager_Stu(void)
{

    char mms='1';

    while(mms!='5')
    {
        system("CLS");
        printf("\n\n\n\n\t\t\t\t****************************************************\n");
        printf("\t\t\t\t\t\t学生管理界面\n");
        printf("\t\t\t\t****************************************************\n");
        printf("\t\t\t\t\t1、查看学生名单\n");
        printf("\t\t\t\t\t2、强制学生还书\n");
        printf("\t\t\t\t\t3、删除学生账号并归还所有书籍\n");
        printf("\t\t\t\t\t4、查看学生具体的借书情况\n");
        printf("\t\t\t\t\t5、返回\n");
        printf("\n\t\t\t\t");
        scanf("%c",&mms);
        while(getchar()!='\n');
        switch(mms)
        {
        case '1':
            Manager_Look_Stu();
            break;
        case '2':
            Manager_Return_Stu();
            break;
        case '3':
            Manager_Del_Stu();
            break;
        case '4':
            Manager_LookBook_Stu();
            break;
        case '5':
            break;
        default:
            printf("\t\t\t\t输入错误，请重新输入\n");
            Sleep(3000);
            break;
        }
    }
}

/*管理员查看学生的借书情况*/
void Manager_LookBook_Stu(void)
{
    system("CLS");
    Student *t=Student_head->next;
    printf("\t\t\t\t正在打印学生借书情况···\n");
    Sleep(1000);
    if(!t)
    {
        printf("\n\t\t\t\t抱歉，暂无学生\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    while(t)
    {
        printf("\t姓名：%s\t学号：%s\t手机号：%s",t->student_name,t->student_num,t->student_phone);
        int tem=0;
        Book *a;
        for(int i=0; i<10; i++)
        {
            if(strcmp(t->student_borrow[i],"0")!=0)
            {
                tem=1;
                break;
            }
        }
        if(tem==0)
        {
            printf("\n\t*********************************************");
        printf("*********************************************************");
            printf("\n\t\t\t暂无借书记录\n");
            printf("\t*********************************************");
        printf("*********************************************************\n\n");
        }
        else{
        printf("\n\t*********************************************");
        printf("*********************************************************\n");
        printf("\t %-10s%-20s%-20s%-25s%-10s%-20s\n\n",
               "编号","书名","作者","出版社","价格","最晚还书时间");
        for(int i=0; i<10; i++)
        {
            if(strcmp(t->student_borrow[i],"0")!=0)
            {
                a=Find_BookofName(t->student_borrow[i]);
                printf("\t %-10s%-20s%-20s%-25s%-10.2f%-20s\n",
                       a->book_num,a->book_name,a->book_at_name,
                       a->book_cp_name,a->book_price,t->student_last[i]                                                 );
            }
        }
        printf("\t*********************************************");
        printf("*********************************************************\n\n");
        }
        t=t->next;
    }
    printf("\n\t\t\t\t按任意键退出");
    getch();
}


/*管理员查看学生名单*/
void Manager_Look_Stu(void)
{
    Student *t=Student_head->next;
    printf("\t\t\t\t正在打印学生名单···\n");
    Sleep(1000);
    if(!t)
    {
        printf("\n\t\t\t\t抱歉，暂无学生\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\n\n     *****************************************************");
    printf("*********************************************************\n\n");
    printf("      %-15s%-20s%-20s%-15s%-24s%-10s\n\n",
           "姓名","学号","电话","生日","身份证号","借书数量");
    while(t)
    {
        int n=0;
        for(int i=0; i<10; i++)
        {
            if(strcmp(t->student_borrow[i],"0")!=0)
                n++;
        }
        printf("      %-15s%-20s%-20s%-15s%-24s%-10d\n",
               t->student_name,t->student_num,t->student_phone,
               t->student_bsd,t->student_id,n);
        t=t->next;
    }
    printf("\n     ****************************************************");
    printf("**********************************************************\n\n\n");
    printf("\t\t\t\t按任意键退出");
    getch();

}
/*强制还书*/
void Manager_Return_Stu(void)
{
    char ch[20];
    Book *a;
    Student *t=Student_head->next;

    if(!t)
    {
        printf("\n\t\t\t\t抱歉，暂无学生\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\n\n     *************************************");
    printf("************************************\n\n");
    printf("\t %-10s%-20s%-24s%-10s\n\n",
           "姓名","学号","身份证号","借书数量");
    while(t)
    {
        int n=0;
        for(int i=0; i<10; i++)
        {
            if(strcmp(t->student_borrow[i],"0")!=0)
                n++;
        }
        printf("\t %-10s%-20s%-24s%-10d\n",
               t->student_name,t->student_num,t->student_id,n);
        t=t->next;
    }
    printf("\n\n     *************************************");
    printf("************************************\n\n");
    printf("\t\t\t\t请输入你想强制还书的学号：");
    gets(ch);
    t=Find_Stu(ch);
    if(!t)
    {
        printf("\t\t\t\t抱歉，无该学生\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    int n=0;
    for(int i=0; i<10; i++)
    {
        if(strcmp(t->student_borrow[i],"0")!=0)
            n++;
    }
    if(!n)
    {
        printf("\t\t\t\t抱歉，该学生借书数量为0，无法强制还书\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    for(int i=0; i<10; i++)
    {
        if(strcmp(t->student_borrow[i],"0")!=0)
        {
            a=Find_BookofName(t->student_borrow[i]);
            a->book_rest+=1;
            t->student_borrow[i][0]='0';
            t->student_borrow[i][1]='\0';
        }
    }
    printf("\t\t\t\t增在强制还书···\n");
    Sleep(500);
    printf("\t\t\t\t···\n");
    Sleep(500);
    printf("\t\t\t\t强制还书成功！\n");
    printf("\t\t\t\t按任意键退出");
    getch();
    return;
}

Student *Find_Stu(char *Stu_Stuty)
{
    Student *t=Student_head->next;
    while(t)
    {
        if(strcmp(t->student_num,Stu_Stuty)==0)
            break;
        t=t->next;
    }
    return t;
}
void Manager_Del_Stu(void)
{
    char bh[20];
    Book *a;
    Student *head=Student_head;
    Student *t=Student_head->next;
    printf("\t\t\t\t正在打印学生名单···\n");
    Sleep(1000);
    if(!t)
    {
        printf("\n\t\t\t\t抱歉，暂无学生\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\n\n\t\t     *************************************");
    printf("*********************************************\n\n");
    printf("\t\t      %-10s%-20s%-20s%-20s%-10s\n\n",
           "姓名","学号","电话","密码","借书数量");
    while(t)
    {
        int n=0;
        for(int i=0; i<10; i++)
        {
            if(strcmp(t->student_borrow[i],"0")!=0)
                n++;
        }
        printf("\t\t      %-10s%-20s%-20s%-20s%-10d\n",
               t->student_name,t->student_num,t->student_phone,
               t->student_psw,n);
        t=t->next;
    }
    printf("\n\t\t     *****************************************");
    printf("*****************************************\n\n\n");

    printf("\t\t\t\t请输入你想删除学生的账号：");
    gets(bh);
    t=Find_Stu(bh);
    if(!t)
    {
        printf("\t\t\t\t抱歉，无该学生\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }
    Sleep(500);
    printf("\t\t\t\t正在删除···\n");
    Sleep(500);
    printf("\t\t\t\t删除成功！\n");
    for(int i=0; i<10; i++)
    {
        if(strcmp(t->student_borrow[i],"0")!=0)
        {
            a=Find_BookofName(t->student_borrow[i]);
            a->book_rest+=1;
        }
    }
    t=Student_head->next;
    while(t)
    {
        if(strcmp(bh,t->student_num)==0)
        {
            head->next=t->next;

            free(t);
            break;
        }
        head=t;
        t=t->next;
    }
    printf("\t\t\t\t按任意键退出\n");
    getch();
    return;
}

/*密码的输入*/
void Password_Input(char *Password)
{
    char ch;
    int i;
    int len=4;
    while(len<6 || len>10)
    {
        for(i=0; i<20; i++)
        {
            ch=getch();
            if(ch==8)
            {
                if((i-1)>=0)
                {
                    i-=2;
                    printf("\b \b");
                }
                else
                    i--;
                continue;
            }
            if(ch=='\r')
                break;
            Password[i]=ch;
            printf("*");
        }
        Password[i]='\0';
        len=strlen(Password);
        if(len<6 || len>10)
            printf("\n\t\t\t\t输入错误，请输入正确长度的密码:");
    }
}
/*检测密码*/
int Password_Text(char *Password)
{
    char password_tem[20];
    int tem=0;
    int n=0;    //检测输入次数
    while(n!=3)
    {
        Password_Input(password_tem);
        if(strcmp(password_tem,Password)==0)
        {
            tem=1;
            break;
        }
        else
        {
            n++;
            if(n!=3)
            {
                printf("\n\t\t\t\t两次输入密码不一致，请重新输入,您还有%d次输入机会：",3-n);
            }
            else if(n==3)
                printf("\n\t\t\t\t输入错误\n");
        }
    }
    return tem;
}
/*密码验证*/
int Password_Text_Find(char *Password)
{
    char password_tem[30];
    int tem=0;
    int n=0;    //检测输入次数
    while(n!=3)
    {
        Password_Input(password_tem);
        if(strcmp(password_tem,Password)==0)
        {
            tem=1;
            break;
        }
        else
        {
            n++;
            printf("\n\t\t\t\t输入错误，请重新输入，你还有%d次机会：",3-n);
        }
    }
    return tem;
}

Book *Book_load()
{
    FILE *fp;
    Book *h=NULL,*t=h,*p;
    if((fp=fopen("Booknode.txt","r"))==NULL)
    {
        printf("\t\t\t\t打开失败\n");
        exit(1);
    }
    getc(fp);
    if(feof(fp))
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    while(!feof(fp))
    {
        p=(Book *)malloc(sizeof(Book));
        p->next=NULL;
        fscanf(fp,"%s",p->book_num);
        fscanf(fp,"%s",p->book_name);
        fscanf(fp,"%s",p->book_at_name);
        fscanf(fp,"%s",p->book_cp_name);
        fscanf(fp,"%f",&p->book_price);
        fscanf(fp,"%d",&p->book_rest);
        fscanf(fp,"%d",&p->book_time);
        if(h==NULL)
            h=p;
        else
            t->next=p;
        t=p;
    }
    fclose(fp);
    return h;
}
/*将学生文件中的信息加载至学生链表*/
Student *Student_load(void)
{
    FILE *fp;
    Student *h=NULL,*t=h,*p;
    if((fp=fopen("Studentnode.txt","r"))==NULL)
    {
        printf("\t\t\t\t打开失败\n");
        exit(1);
    }
    getc(fp);
    if(feof(fp))
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    while(!feof(fp))
    {
        p=(Student *)malloc(sizeof(Student));
        p->next=NULL;
        fscanf(fp,"%s ",p->student_num);
        fscanf(fp,"%s ",p->student_psw);
        fscanf(fp,"%s ",p->student_id);
        fscanf(fp,"%s ",p->student_name);
        fscanf(fp,"%s ",p->student_sex);
        fscanf(fp,"%s ",p->student_bsd);
        fscanf(fp,"%s ",p->student_phone);
        for(int i=0; i<10; i++)
        {
            fscanf(fp,"%s ",p->student_borrow[i]);
            fscanf(fp,"%s ",p->student_last[i]);
        }
        int len=strlen(p->student_psw);			//密码解密
        for(int i=0; i<len; i++)
        {
            p->student_psw[i]=p->student_psw[i]-(i%4+1);
        }
        if(h==NULL)
            h=p;
        else
            t->next=p;
        t=p;
    }
    fclose(fp);
    return h;
}
Manager *Manager_load(void)
{
    FILE *fp;
    Manager *h=NULL,*t=h,*p;
    if((fp=fopen("Managernode.txt","r"))==NULL)
    {
        printf("\t\t\t\t打开失败\n");
        exit(1);
    }
    getc(fp);
    if(feof(fp))
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    while(!feof(fp))
    {
        p=(Manager *)malloc(sizeof(Manager));
        p->next=NULL;
        fscanf(fp,"%s",p->man_name);
        fscanf(fp,"%s",p->man_acc);
        fscanf(fp,"%s",p->man_passw);
        int len=strlen(p->man_passw);			//密码解密
        for(int i=0; i<len; i++)
        {
            p->man_passw[i]=p->man_passw[i]-(i%4+1);

        }
        if(h==NULL)
            h=p;
        else
            t->next=p;
        t=p;
    }
    fclose(fp);
    return h;
}
/*保存书籍链表至文件*/
void Save_Book(void)
{
    FILE *fp;
    Book *t=Book_head->next;
    if(!t)
        return;
    if((fp=fopen("Booknode.txt","w+"))==NULL)
    {
        printf("\t\t\t\t打开失败\n");
        exit(1);
    }
    while(t->next)
    {
        fprintf(fp,"%s ",t->book_num);
        fprintf(fp,"%s ",t->book_name);
        fprintf(fp,"%s ",t->book_at_name);
        fprintf(fp,"%s ",t->book_cp_name);
        fprintf(fp,"%.2f ",t->book_price);
        fprintf(fp,"%d ",t->book_rest);
        fprintf(fp,"%d\n",t->book_time);
        t=t->next;
    }
    fprintf(fp,"%s ",t->book_num);
    fprintf(fp,"%s ",t->book_name);
    fprintf(fp,"%s ",t->book_at_name);
    fprintf(fp,"%s ",t->book_cp_name);
    fprintf(fp,"%.2f ",t->book_price);
    fprintf(fp,"%d ",t->book_rest);
    fprintf(fp,"%d",t->book_time);
    fclose(fp);
}
/*保存学生链表至文件*/
void Save_Student(void)
{
    FILE *fp;
    Student *t=Student_head->next;
    if(!t)
        return;
    if((fp=fopen("Studentnode.txt","w+"))==NULL)
    {
        printf("\t\t\t\t打开失败\n");
        exit(1);
    }
    while(t->next)
    {
        int len=strlen(t->student_psw);			//密码加密
        for(int i=0; i<len; i++)
        {
            t->student_psw[i]=t->student_psw[i]+(i%4+1);
        }
        fprintf(fp,"%s ",t->student_num);
        fprintf(fp,"%s ",t->student_psw);
        fprintf(fp,"%s ",t->student_id);
        fprintf(fp,"%s ",t->student_name);
        fprintf(fp,"%s ",t->student_sex);
        fprintf(fp,"%s ",t->student_bsd);
        fprintf(fp,"%s ",t->student_phone);
        for(int i=0; i<9; i++)
        {
            fprintf(fp,"%s ",t->student_borrow[i]);
            fprintf(fp,"%s ",t->student_last[i]);
        }
        fprintf(fp,"%s ",t->student_borrow[9]);
        fprintf(fp,"%s\n",t->student_last[9]);
        t=t->next;
    }

    int len=strlen(t->student_psw);			//密码加密
    for(int i=0; i<len; i++)
    {
        t->student_psw[i]=t->student_psw[i]+(i%4+1);
    }
    fprintf(fp,"%s ",t->student_num);
    fprintf(fp,"%s ",t->student_psw);
    fprintf(fp,"%s ",t->student_id);
    fprintf(fp,"%s ",t->student_name);
    fprintf(fp,"%s ",t->student_sex);
    fprintf(fp,"%s ",t->student_bsd);
    fprintf(fp,"%s ",t->student_phone);
    for(int i=0; i<9; i++)
    {
        fprintf(fp,"%s ",t->student_borrow[i]);
        fprintf(fp,"%s ",t->student_last[i]);
    }
    fprintf(fp,"%s ",t->student_borrow[9]);
    fprintf(fp,"%s ",t->student_last[9]);
    fclose(fp);
}
/*保存管理员链表至文件*/
void Save_Manger(void)
{
    FILE *fp;
    Manager *t=Manager_head->next;
    if(!t)
        return;
    if((fp=fopen("Managernode.txt","w+"))==NULL)
    {
        printf("\t\t\t\t打开失败\n");
        exit(1);
    }
    while(t->next)
    {
        int len=strlen(t->man_passw);			//密码加密
        for(int i=0; i<len; i++)
        {
            t->man_passw[i]=t->man_passw[i]+(i%4+1);
        }
        fprintf(fp,"%s ",t->man_name);
        fprintf(fp,"%s ",t->man_acc);
        fprintf(fp,"%s\n",t->man_passw);
        t=t->next;
    }
    int len=strlen(t->man_passw);			//密码加密
    for(int i=0; i<len; i++)
    {
        t->man_passw[i]=t->man_passw[i]+(i%4+1);
    }
    fprintf(fp,"%s ",t->man_name);
    fprintf(fp,"%s ",t->man_acc);
    fprintf(fp,"%s",t->man_passw);
    fclose(fp);
}
/*所有信息保存至文件*/
void Massage_Save(void)
{
    Save_Book();
    Save_Student();
    Save_Manger();
}

/*学生端口*/
void Student_Port(void)
{
    char sp='1';

    while(sp!='4')
    {
        show_stu();
        printf("\t\t\t\t");

        scanf("%c",&sp);
        while(getchar()!='\n');
        switch(sp)
        {
        case '1':
            Student_Login();
            break;
        case '2':
            Student_Register();
            break;
        case '3':
            Find_Password();
            break;
        case '4':
            system("CLS");
            break;
        default:
            printf("\t\t\t\t输入错误，请重新输入：\n");
            Sleep(1500);
            break;
        }
    }
}
/*学生注册账号*/
void Student_Register(void)
{
    char password[20];
    Student *t;
    Student *new=(Student *)malloc(sizeof(Student));
    new->next=NULL;
    for(int i=0; i<10; i++)
    {
        new->student_borrow[i][0]='0';
        new->student_borrow[i][1]='\0';
        new->student_last[i][0]='0';
        new->student_last[i][1]='\0';
    }
    system("CLS");
    printf("\n\n\n\t\t\t****************************************************\n");
    printf("\t\t\t\t\t欢迎来到注册界面\n");
    printf("\t\t\t****************************************************\n");
    Sleep(1);
    printf("\t\t\t请输入以下信息\n\n");
    printf("\t\t\t姓名：\n");
    scanf("%s",new->student_name);
    printf("\t\t\t性别：\n");
    scanf("%s",new->student_sex);
    printf("\t\t\t学号：\n");
    scanf("%s",new->student_num);
    printf("\t\t\t身份证号：\n");
    scanf("%s",new->student_id);
    printf("\t\t\t手机号：\n");
    scanf("%s",new->student_phone);
    printf("\t\t\t生日：（格式样例：2022.05.04）\n");
    scanf("%s",new->student_bsd);
    printf("\t\t\t密码：（密码长度不超过20）\n");
    Password_Input(new->student_psw);
    printf("\n\t\t\t再次输入密码：\n");
    if(Password_Text(new->student_psw)==0)
    {
        printf("\n\t\t\t您已连续输错3次，将退出注册系统···");
        Sleep(5000);
        free(new);
        return;
    }
    Sleep(500);
    printf("\n\t\t\t\t正在注册\n\t\t\t\t···\n");
    Sleep(1000);
    printf("\t\t\t\t···\n");
    Sleep(1000);
    printf("\t\t\t\t···\n");
    Sleep(1000);
    printf("\t\t\t\t注册成功！\n");
    while(getchar()!='\n');
    t=Student_head;
    while(t->next)
    {
        t=t->next;
    }
    t->next=new;
    printf("\t\t\t\t按任意键退出");
    getch();
}
void Find_Password(void)
{
    Student *find_tem;
    char student_num[50];
    char password_find[20];
    printf("\t\t\t欢迎来到找回密码系统\n");
    Sleep(500);
    printf("\t\t\t···\n");
    Sleep(500);
    int l=1;
    while(l!=12)
    {
        printf("\t\t\t请输入学号：");
        gets(student_num);
        l=strlen(student_num);
        if(l!=12)
            printf("\t\t\t账号有误，请输入正确长度的账号\n");
    }
    student_num[12]='\0';
    find_tem=Find_Num(student_num);
    printf("\t\t\t您输入的账号：");
    puts(student_num);
    Sleep(500);
    printf("\t\t\t正在为您查找\n");
    Sleep(500);
    printf("\t\t\t···\n");
    Sleep(500);
    if(find_tem==NULL)
    {
        printf("\t\t\t抱歉，无此账号，即将退出找回密码模块\n");
        Sleep(1000);
        printf("\t\t\t···\n");
        Sleep(3000);
        return;
    }
    printf("\t\t\t%s，您好！\n",find_tem->student_name);
    Sleep(300);
    printf("\t\t\t你的生日是： ");
    Sleep(300);
    if(Password_Text_Find(find_tem->student_bsd)==0)
    {
        printf("\n\t\t\t您已连续输错3次，将退出找回密码系统···\n");
        Sleep(1500);
        return;
    }
    Sleep(500);
    printf("\n\t\t\t正在查找\n");
    Sleep(500);
    printf("\t\t\t···\n");
    Sleep(500);
    printf("\t\t\t···\n");
    Sleep(500);
    printf("\t\t\t%s 您好，您的密码是 ：%s",find_tem->student_name,find_tem->student_psw);
    printf("\n\t\t\t请牢记您的密码\n");
    printf("\t\t\t按任意键退出");
    getch();


}
Student *Find_Num(char *Stu_num)
{
    Student *t=Student_head->next;
    while(t)
    {
        if(strcmp(t->student_num,Stu_num)==0)
            break;
        t=t->next;
    }
    return t;
}
/*学生端登录*/
void Student_Login(void)
{
    char sl='1';
    char enter_num[50];
    char enter_passw[20];
    int l=1;
    Student *enter_stu;
    while(l!=12)
    {
        printf("\n\t\t\t\t请输入你的账号：");
        gets(enter_num);
        l=strlen(enter_num);
        if(l!=12)
            printf("\t\t\t\t账号有误，请输入正确长度的账号\n");
    }
    enter_num[12]='\0';
    enter_stu=Find_Num(enter_num);
    if(enter_stu==NULL)
    {
        printf("\n\t\t\t\t抱歉，无此账号");
        Sleep(500);
        printf("\n\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\t\t\t\t请输入密码：");
    if(Password_Text_Find(enter_stu->student_psw)==0)
    {
        printf("\n\t\t\t\t您已连续输错3次，将退出登录系统···");
        Sleep(2000);
        return;
    }
    Sleep(500);
    printf("\n\t\t\t\t正在登录中，请稍后···");
    Sleep(500);
    printf("\n\t\t\t\t······\n");
    Sleep(500);
    printf("\n\t\t\t\t登录成功！\n");
    Sleep(1000);


    while(sl!='6')
    {
        show_stu_enter();
        printf("\t\t\t");
        scanf("%c",&sl);
        while(getchar()!='\n');
        switch(sl)
        {
        case '1':
            Stu_Borrow(enter_stu);
            break;
        case '2':
            Stu_Back(enter_stu);
            break;
        case '3':
            Find_Book();
            break;
        case '4':
            Find_Theborrow(enter_stu);
            break;
        case '5':
            Change_Stupassword(enter_stu);
            break;
        case '6':
            break;
        default:
            printf("\t\t\t输入错误，请重新输入\n");
            Sleep(3000);
            break;
        }
    }
}

void Find_Book(void)
{
    Book *t=Book_head->next;
    char book_n[20];
    if(t==NULL)
    {
        printf("\t\t\t抱歉，暂无书籍\n");
        printf("\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\t\t\t请输入你需要查找的书名或者书的编号：");
    gets(book_n);
    while(t)
    {
        if(strcmp(book_n,t->book_name)==0||strcmp(book_n,t->book_num)==0)
            break;
        t=t->next;
    }
    if(t==NULL)
    {
        printf("\t\t\t抱歉，无此书籍\n");
        printf("\t\t\t按任意键退出");
        getch();
        return;
    }
    t=Book_head->next;
    printf("\n\n\t\t*********************************************");
    printf("*************************************************\n\n");
    printf("\t\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    while(t)
    {
        if(strcmp(book_n,t->book_name)==0||strcmp(book_n,t->book_num)==0)
            printf("\t\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
                   t->book_num,t->book_name,t->book_at_name,
                   t->book_cp_name,t->book_price,t->book_rest,t->book_time);
        t=t->next;
    }
    printf("\n\t\t*************************************************");
    printf("*********************************************\n\n\n");
    printf("\n\t\t\t按任意键退出");
    getch();
}

Book *Find_BookofName(char *Book_num)
{
    Book *t=Book_head->next;
    while(t)
    {
        if(strcmp(Book_num,t->book_num)==0)
            return t;
        t=t->next;
    }
}
void Change_Stupassword(Student *Stu_num)
{
    char password_tem[20];
    printf("\t\t\t加载中···\n");
    Sleep(500);
    printf("\t\t\t请输入原密码：");
    if(Password_Text_Find(Stu_num->student_psw)==0)
    {
        printf("\n\t\t\t已经错误输入密码三次，将退出修改密码系统···\n");
        Sleep(1500);
        return;
    }
    printf("\n\t\t\t验证中···\n");
    Sleep(1000);
    printf("\t\t\t验证成功！\n");
    Sleep(500);
    printf("\t\t\t请输入新密码(6~20位)：");
    Password_Input(password_tem);
    printf("\n\t\t\t请再次输入新密码：");
    if(Password_Text(password_tem)==0)
    {
        printf("\t\t\t已经错误输入密码三次，将退出修改密码系统···\n");
        Sleep(3000);
        return;
    }
    Stu_num->student_psw[0]='\0';
    strcat(Stu_num->student_psw,password_tem);
    Sleep(500);
    printf("\n\t\t\t请稍等，正在修改···\n");
    Sleep(1000);
    printf("\t\t\t···\n");
    Sleep(1000);
    printf("\t\t\t···\n");
    Sleep(1000);
    printf("\t\t\t恭喜！修改成功！\n");
    printf("\t\t\t按任意键退出");
    getch();
}
void Find_Theborrow(Student *Stu_num)
{
    int tem=0;
    Book *t;
    printf("\t\t\t查找中···\n");
    Sleep(1000);
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],"0")!=0)
        {
            tem=1;
            break;
        }
    }
    if(tem==0)
    {
        printf("\t\t\t暂无借书记录\n");
        printf("\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\n\n\t*********************************************");
    printf("*********************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-20s\n\n",
           "编号","书名","作者","出版社","价格","最晚还书时间");
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],"0")!=0)
        {
            t=Find_BookofName(Stu_num->student_borrow[i]);
            printf("\t %-10s%-20s%-20s%-25s%-10.2f%-20s\n",
                   t->book_num,t->book_name,t->book_at_name,
                   t->book_cp_name,t->book_price,Stu_num->student_last[i]                                                 );
        }
    }
    printf("\n\n\t*********************************************");
    printf("*********************************************************\n\n");
    printf("\n\t\t\t\t按任意键退出");
    getch();
}

void Stu_Borrow(Student *Stu_num)
{
    system("CLS");
    int n=0;
    Book *t;
    char numb[10];
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],"0")!=0)
            n++;
    }
    printf("\n\t\t\t\t*****************************");
    printf("****************************\n");
    printf("\t\t\t\t\t\t\t借书系统\n");
    printf("\t\t\t\t*****************************");
    printf("****************************\n");
    if(n==10)
    {
        printf("\t\t\t\t\t\t您好，您已借书10本，已到最大借书限额，");
        printf("\t\t\t\t\t\t请先归还已借书籍\n\n");
        printf("\t\t\t\t\t\t按任意键退出");
        getch();
        return;
    }
    printf("\n\t\t\t\t\t您已借书籍%d本，还可借%d本\n",n,10-n);
    Sleep(500);
    printf("\n\n\t\t\t\t\t\t\t书单如下\n");
    Sleep(500);
    Print_Book();
    printf("\n\t\t\t请选择你想借书的编号：");
    gets(numb);
    t=Book_exit(numb);
    printf("\t\t\t正在办理···\n");
    Sleep(1000);
    if(!t)
    {
        printf("\t\t\t抱歉，无此书，借书失败\n");
        printf("\t\t\t按任意键退出");
        getch();
        return;
    }
    if(t->book_rest==0)
    {
        printf("\t\t\t抱歉，库存不足，借书失败\n");
        printf("\t\t\t按任意键退出");
        getch();
        return;
    }
    if(Ifborrow(Stu_num,numb))
    {
        printf("\t\t\t抱歉，您已借过此书，请勿重复借书\n");
        printf("\t\t\t按任意键退出");
        getch();
        return;
    }
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],"0")==0)
        {
            Stu_num->student_borrow[i][0]='\0';
            strcat(Stu_num->student_borrow[i],numb);
            t->book_rest--;
            t->book_time++;
            time_t timep;//记录借书时间
            time(&timep);
            struct tm *p;
            p=localtime(&timep);
            char ch[5];
            Stu_num->student_last[i][0]='\0';
            if((p->tm_mon+2)<=12)
            {
                int num=p->tm_year+1900;
                itoa(num,ch,10);
                strcat(Stu_num->student_last[i],ch);
                strcat(Stu_num->student_last[i],"-");
                num=p->tm_mon+2;
                itoa(num,ch,10);
                strcat(Stu_num->student_last[i],ch);
                strcat(Stu_num->student_last[i],"-");
                num=p->tm_mday;
                itoa(num,ch,10);
                strcat(Stu_num->student_last[i],ch);
            }
            else
            {
                int num=p->tm_year+1901;
                itoa(num,ch,10);
                strcat(Stu_num->student_last[i],ch);
                strcat(Stu_num->student_last[i],"-");
                num=p->tm_mon-10;
                itoa(num,ch,10);
                strcat(Stu_num->student_last[i],ch);
                strcat(Stu_num->student_last[i],"-");
                num=p->tm_mday;
                itoa(num,ch,10);
                strcat(Stu_num->student_last[i],ch);
            }
            break;
        }
    }
    printf("\t\t\t···\n");
    printf("\t\t\t恭喜您办理成功！\n");
    printf("\t\t\t按任意键退出");
    getch();
    return;
}

/*打印书单*/
void Print_Book(void)
{
    Book *t=Book_head->next;
    if(t==NULL)
    {
        printf("\t\t\t抱歉，暂无上架书籍\n");
        Sleep(2000);
        return;
    }
    printf("\n\n\t\t*********************************************");
    printf("***********************************************************\n\n");
    printf("\t\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "编号","书名","作者","出版社","价格","库存","借阅次数");
    while(t)
    {
        printf("\t\t %-10s%-20s%-20s%-25s%-10.2f%-10d%-10d\n",
               t->book_num,t->book_name,t->book_at_name,
               t->book_cp_name,t->book_price,t->book_rest,t->book_time);
        t=t->next;
    }
    printf("\n\t\t*************************************************");
    printf("*******************************************************\n\n\n");
}
/*寻找该书是否存在*/
Book *Book_exit(char *Book_num)
{

    Book *t=Book_head->next;
    while(t)
    {
        if(strcmp(t->book_num,Book_num)==0)
            break;
        t=t->next;
    }
    return t;
}
/*查询学生是否借过此书*/
int Ifborrow(Student *Stu_num,char *Book_num)
{
    int tem=0;
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],Book_num)==0)
        {
            tem=1;
            break;
        }
    }
    return tem;
}
/*学生还书*/
void Stu_Back(Student *Stu_num)
{
    system("CLS");
    char book_num[15];
    int tem=0;
    printf("\n\t\t\t\t*****************************");
    printf("****************************\n");
    printf("\t\t\t\t\t\t\t还书系统\n");
    printf("\t\t\t\t*****************************");
    printf("****************************\n");
    printf("\n\n\t\t\t正在查找已借书籍···\n");
    Sleep(500);
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],"0")!=0)
        {
            tem=1;
            break;
        }
    }
    if(tem==0)
    {
        printf("\n\t\t\t暂无借书记录\n");
        printf("\n\t\t\t按任意键退出");
        getch();
        return;
    }
    Print_Borbook(Stu_num);
    printf("\n\t\t\t\t请输入书的编号进行归还：");
    gets(book_num);
    tem=0;
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],book_num)==0)
        {
            tem=1;
            break;
        }
    }
    if(!tem)
    {
        printf("\t\t\t\t输入错误，您未借过此书\n");
        printf("\t\t\t\t按任意键退出");
        getch();
        return;
    }

    Sleep(500);
    printf("\t\t\t正在归还···\n");
    Sleep(500);
    Bake_Book(Stu_num,book_num);
    printf("\t\t\t归还成功！\n");
    printf("\t\t\t按任意键退出");
    getch();
}
/*打印所借书籍*/
void Print_Borbook(Student *Stu_num)
{
    int tem=0;
    Book *t;
    printf("\n\n\t\t*********************************************");
    printf("********************************************************\n\n");
    printf("\t\t %-10s%-20s%-20s%-25s%-10s%-20s\n\n",
           "编号","书名","作者","出版社","价格","最晚还书日期");
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],"0")!=0)
        {
            t=Find_BookofName(Stu_num->student_borrow[i]);
            printf("\t\t %-10s%-20s%-20s%-25s%-10.2f%-20s\n",
                   t->book_num,t->book_name,t->book_at_name,
                   t->book_cp_name,t->book_price,Stu_num->student_last[i]
                  );
        }
    }
    printf("\n\n\t\t*********************************************");
    printf("********************************************************\n\n");
}
/*还书具体操作*/
void Bake_Book(Student *Stu_num,char *Book_num)
{
    Book *t;
    for(int i=0; i<10; i++)
    {
        if(strcmp(Stu_num->student_borrow[i],Book_num)==0)
        {
            Stu_num->student_borrow[i][0]='0';
            Stu_num->student_borrow[i][1]='\0';
            break;
        }
        if(strcmp(Stu_num->student_borrow[i],Book_num)==0)
        {
            Stu_num->student_last[i][0]='0';
            Stu_num->student_last[i][1]='\0';
            break;
        }
    }
    t=Find_BookofName(Book_num);
    t->book_rest++;
}
