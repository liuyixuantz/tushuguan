#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define leapYear(y)  ((y%4==0)&&(y%100!=0)||(y%400==0))    //�궨��,�ж��Ƿ�������

struct date
{
    int years;
    int months;
    int days;
};

typedef struct book
{
    char book_num[10];				//���
    char book_name[20];				//����
    char book_at_name[30];			//������
    char book_cp_name[30];			//������
    float book_price;				//�۸�
    int book_rest;					//���
    int book_time;                  //ͼ�鱻���Ĵ���
    struct book *next;				//�±���
} Book;

/*�洢ѧ������Ϣ*/
typedef struct Student
{
    char student_num[20];           //ѧ��ѧ��
    char student_psw[20];           //ѧ������
    char student_id[30];            //ѧ�����֤
    char student_name[20];          //ѧ������
    char student_sex[10];           //ѧ���Ա�
    char student_bsd[20];           //ѧ������
    char student_phone[20];         //ѧ���ֻ���
    char student_borrow[10][20];    //ѧ�������ı��
    char student_last[10][25];      //����������
    struct Student *next;             //��һ��ѧ��
} Student;

typedef struct manager
{
    char man_name[15];				//����Ա����
    char man_acc[20];				//����Ա�˺�
    char man_passw[15];				//����Ա����
    struct manager *next;			//�¸�����Ա
} Manager;

Book *Book_head;
Student *Student_head;
Manager *Manager_head;

void show_main(void);
//������
void show_stu(void);
//ѧ����
void show_stu_enter(void);
//ѧ��ҳ
void show_manager(void);
//����Ա��
void show_manager_enter(void);
//����Աҳ
Book *Book_load(void);
//���鼮�ļ��е���Ϣ�������鼮����
Student *Student_load(void);
//��ѧ���ļ��е���Ϣ������ѧ������
Manager *Manager_load(void);
//������Ա�ļ�����Ϣ����������Ա����
void Student_Port(void);
//ѧ���˿�
void Manager_Port(void);
//����Ա�˿�
void Student_Login(void);
//ѧ���˵�¼
void Student_Register(void);
//ѧ��ע���˺�
void Find_Password(void);
//ѧ���һ�����
void Password_Input(char *Password);
//�������뺯��
int Password_Text(char *Password_temp);
//�������
Student *Find_Num(char *Stu_num);
//��ѧ�Ų���ѧ��
int Password_Text_Find(char *Password);
//�һ����������֤������֤
void Stu_Borrow(Student *Stu_num);
//ѧ������
void Stu_Back(Student *Stu_num);
//ѧ������
void Find_Book(void);
//������������ͼ���Ų�����
void Find_Theborrow(Student *Stu_num);
//ѧ���鿴������
void Change_Stupassword(Student *Stu_num);
//ѧ���޸�����
Book *Find_BookofName(char *Book_num);
//����Ų�����
void Print_Book(void);
//��ӡ�鵥
Book *Book_exit(char *Book_num);
//Ѱ�Ҹ����Ƿ����
int Ifborrow(Student *Stu_num,char *Book_num);
//��ѯѧ���Ƿ�������
void Print_Borbook(Student *Stu_num);
//��ӡ�������
void Bake_Book(Student *Stu_num,char *Book_num);
//����������
void Manager_Login(void);
//����Ա��¼
Manager *Manager_check(char *Manager_num);
//�˶Թ���Ա�˺�
void Manager_Add_Book(void);
//����Ա�ϼ��鼮
void Manager_Down_Book(void);
//����Ա�¼��鼮
void Manager_Look_Book(void);
//����Ա������
void book_deadline(void);
//����Ա�������һ�ܵ��ڵ�ͼ����Ϣ
void Manager_Manager_Stu(void);
//����Ա����ѧ��
void Manager_Change_Password(Manager *Man_num);
//����Ա�޸�����
void Lookofnum(void);
//�������鿴���
void Lookofrest(void);
//�������鿴���
void Lookstayenum(void);
//���鿴���
void Lookoftime(void);
//���Ĵ�������鿴���
void Lookofprice(void);
//�۸�����鿴
void Manager_Print_Book(void);
//����Ա��ӡ���
void Manager_Add_Book1(void);
//���ӿ��
void Manager_Add_Book2(void);
//�ϼ�����
void Save_Book(void);
//�����鼮�������ļ�
void Save_Student(void);
//����ѧ���������ļ�
void Save_Manger(void);
//�������Ա�������ļ�
void Massage_Save(void);
//������Ϣ�������ļ�
void Manager_Look_Stu(void);
//����Ա�鿴ѧ������
void Manager_LookBook_Stu(void);
//����Ա�鿴ѧ���Ľ������
void Manager_Return_Stu(void);
// ����Աǿ��ѧ������
void Manager_Del_Stu(void);
// ɾ��ѧ�����벢�黹�����鼮
Student *Find_Stu(char *Stu_Stuty);
//��ѧ�Ų�ѧ��

int main(void)
{
//    system("color DE");
    Book_head=(Book *)malloc(sizeof(Book));//��ʼ��Book_head��������Book�ṹ���С���ڴ�
    Student_head=(Student *)malloc(sizeof(Student));//��ʼ��Student_head��������Student�ṹ���С���ڴ�
    Manager_head=(Manager *)malloc(sizeof(Manager));//��ʼ��Manager_head��������Manager�ṹ���С���ڴ�

    Book_head->next=Book_load();//�ú����Ӵ洢ͼ����ı��ļ��ж�ȡ���ݵ�Book_head������
    Student_head->next=Student_load();//�ú����Ӵ洢ѧ�����ݵ��ı��ļ��ж�ȡ���ݵ�Student_head������
    Manager_head->next=Manager_load();//�ú����Ӵ洢����Ա���ݵ��ı��ļ��ж�ȡ���ݵ�Manager_head������

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
            printf("\t\t\t\t�����������������\n");
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
        "              =@@=@@@@@@@@@@@@@@@@@@@@^ O@^                 ��ѡ��                   @@@     @@    @@@@@  @@       @@@     @@   @@   @@@@@@@@@  \n"
        "               @@^O@@@@@@@@@@@@@@@@@@@^ O@^                                           @@@    @@ @@@@@@@@@ @@       @@@ @@@@@@   @@@@ @@     @@ \n"
        "               =@@=@@@@@@@@@@@@@@@@@@@^ =@^         ��-��-��-��-��-��-����             @@    @@@@@@@@@@@@@@@       @@@   @@@    @@@  @@@@@@@@@  \n"
        "                @@@O@@@@@@@@@@@@@@@@@@@  @@         |     1��ѧ����      |              @@     \n"
        "                ,@@o@@@@@@@@@@@@@@@@@@@` O@^        |     2������Ա��    |              @@@@@   \n"
        "                 =@OO@@@@@@@@@@@@@@@@@@@ ,OO        |     3���˳�        |              @@@*[@@   \n"
        "                  @@o@@@@@@@@@@@@@@@@@@@^ =@@       ��-��-��-��-��-��-����              @@^    @@ \n"
        "                  ,@@O@@@@@@@@@@@@@@@@@@O ,@@^                                          @@`    @@ \n"
        "                   @@OO@@@@@@@@@@@@@@@@@@@ ,@@@                                        @@@     @@`\n"
        "                    @@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@^                                  O@O     @@@ \n"
        "                    =@@O@@@@@@@@@@@@@@@@@@@@@O`                                      @@O    @@@  \n"
        "                     @@@@@@@@@@@@@@@@@@^@@@`                                     ,@@@   @@@@@@    \n"
        "                      @@@O@@@@@@@@@@@@@ O^                                 ]]@@@@@@`              \n"
        "                       @@`O@@@@@@@@@@@@`[@^@O@]]]]]]]]]]OO@@O ,O`    @@@@@@@O[[                   \n");
//    printf("\n\n\n\t\t\t\t\t\tС����ͼ���");
//    printf("\n\t\t\t\t**********************************************\n\n");
//    printf("\t\t\t\t\t\t1��ѧ����\n");
//    printf("\t\t\t\t\t\t2������Ա��\n");
//    printf("\t\t\t\t\t\t3���˳�\n");
//    printf("\n\t\t\t\t**********************************************\n\n");
}
void show_stu(void)
{
    system("CLS");
    printf("\n\n\n\t\t\t\t\t\tѧ������");
    printf("\n\t\t\t\t**********************************************\n\n");
    printf("\t\t\t\t\t\t1����¼\n");
    printf("\t\t\t\t\t\t2��ע��\n");
    printf("\t\t\t\t\t\t3���һ�����\n");
    printf("\t\t\t\t\t\t4������\n");
    printf("\n\t\t\t\t**********************************************\n\n");
}
void show_stu_enter(void)
{
    system("CLS");
    printf("\n\n\n\t\t\t\t\t    ѧ��ҳ��\n");
    printf("\t\t\t****************************************************\n");
    printf("\n\t\t\t\t\t1������\n");
    printf("\t\t\t\t\t2������\n");
    printf("\t\t\t\t\t3����ѯͼ��\n");
    printf("\t\t\t\t\t4���鿴�Լ��Ľ������\n");
    printf("\t\t\t\t\t5���޸�����\n");
    printf("\t\t\t\t\t6������\n");
    printf("\n\t\t\t****************************************************\n");
}
void show_manager(void)
{
    system("CLS");
    printf("\n\n\n\t\t\t\t\t\t����Ա����");
    printf("\n\t\t\t\t**********************************************\n\n");
    printf("\t\t\t\t\t\t1����¼\n");
    printf("\t\t\t\t\t\t2������\n");
    printf("\n\t\t\t\t**********************************************\n\n");
}
void show_manager_enter(void)
{
    system("CLS");
    printf("\n\n\n\t\t\t\t\t    ����Աҳ\n");
    printf("\t\t\t****************************************************\n");
    printf("\n\t\t\t\t\t1���ϼ��鼮\n");
    printf("\t\t\t\t\t2���¼��鼮\n");
    printf("\t\t\t\t\t3��������\n");
    printf("\t\t\t\t\t4������ѧ���˺�\n");
    printf("\t\t\t\t\t5���޸�����\n");
    printf("\t\t\t\t\t6���˳�\n");
    printf("\n\t\t\t****************************************************\n");
}

/*����Ա��*/
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
            printf("\t\t\t\t�����������������\n");
            Sleep(3000);
            break;
        }
    }
}
/*����Ա��¼*/
void Manager_Login(void)
{
    char Manager_num[20];
    char ml='1';
    Manager *t;
    printf("\n\t\t\t\t�˺ţ�");
    gets(Manager_num);
    t=Manager_check(Manager_num);
    if(!t)
    {
        printf("\t\t\t\t��Ǹ���˺Ų�����\n");
        printf("\t\t\t\t��������˳�");
        getchar();
        return;
    }
    printf("\t\t\t\t���룺");
    if(Password_Text_Find(t->man_passw)==0)
    {
        printf("\n\t\t\t\t�Ѿ����������������Σ����˳���¼ϵͳ������\n");
        Sleep(5000);
        return;
    }
    Sleep(500);
    printf("\n\t\t\t\t��¼�С�����\n");
    Sleep(500);
    printf("\t\t\t\t��¼�ɹ�������\n");
    Sleep(500);
    printf("\t\t\t\t���ڼ��ء�����\n");
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
            printf("\t\t\t\t�����������������\n");
            Sleep(3000);
            break;
        }
    }



}
/*�˶Թ���Ա�˺�*/
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
/*����Ա�鿴���*/
void Manager_Look_Book(void)
{
    char ml;
    system("CLS");
    printf("\n\n\n\n\t\t\t\t****************************************************\n");
    printf("\t\t\t\t\t\t��ѡ������ķ�ʽ\n");
    printf("\t\t\t\t****************************************************\n");
    printf("\t\t\t\t1�����������������\n");
    printf("\t\t\t\t2�����������������\n");
    printf("\t\t\t\t3�����۸�����������\n");
    printf("\t\t\t\t4�������Ĵ�������������\n");
    printf("\t\t\t\t5���������������\n");
    printf("\t\t\t\t6�����������ڻ�1���ڽ����ڵ�ͼ����Ϣ\n\n");

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
        printf("\t\t\t�������\n");
        break;
    }
    printf("\t\t\t��������˳�");
    getch();
    return;
}
//�������鿴���
void Lookofnum(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t�����鼮\n");
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
//�������鿴���
void Lookofrest(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t�����鼮\n");
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
//���Ĵ�������鿴���
void Lookoftime(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t�����鼮\n");
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
//�۸�����鿴���
void Lookofprice(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t�����鼮\n");
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

//���鿴���
void Lookstayenum(void)
{
    if(Book_head->next==NULL)
    {
        printf("\t\t�����鼮\n");
        return;
    }
    if(Book_head->next==NULL)
    {
        return;
    }
    Book *p;
    Book *head=Book_head;
    printf("\n\t\t\t\t\t\t�̲���\n");                                          //����̲���
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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

    printf("\n\t\t\t\t\t\t��ѧ��\n");                                          //�����ѧ��
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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

    printf("\n\t\t\t\t\t\t������\n");                                          //���������
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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

    printf("\n\t\t\t\t\t\t������\n");                                          //���������
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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

    printf("\n\t\t\t\t\t\t������\n");                                          //���������
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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

    printf("\n\t\t\t\t\t\t��ʷ��\n");                                          //�����ʷ��
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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

    printf("\n\t\t\t\t\t\tҽѧ��\n");                                          //���ҽѧ��
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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

     printf("\n\t\t\t\t\t\t������\n");                                          //���������
    printf("\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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
        printf("\t\tû���κ��鼮��Ϣ\n");
        return;
    }
    printf("\n\n\t*********************************************");
    printf("************************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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

//����Ա�������һ�ܵ��ڵ�ͼ����Ϣ
int days_date(struct date s)				//��2022-00-00ʱΪ��׼�������ȥ�˶�����
{
    int days_on_month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; //�ֱ��Ӧ1��12�µ�������a[0]����
    int i,sum=0;								//ͳ������
    for (int i = 2022; i < s.years; i++)      //���
    {
        if (leapYear(i))				//�ж��Ƿ�������
            sum += 366;
        else sum += 365;
    }

    if (leapYear(i))
        days_on_month[2]=29;                //�������Ϊ29��
    else
        days_on_month[2]=28;                 //�ⲽ������ʡ��
    for (int k = 1; k < s.months; k++)		 //�·�
        sum += days_on_month[k];

    return sum+s.days;						 //�������� ����
}

int diff(struct date s1, struct date s2)      //��������ʱ��Σ��������
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
    time_t timep;//��¼��ǰʱ��
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
    printf("\t\t\t\t���ڲ��ҽ�����ڻ�1���ڽ����ڵ�ͼ����Ϣ������\n");
    Sleep(1000);
    if(!t)
    {
        printf("\n\t\t\t\t��Ǹ������ѧ������ͼ��\n");
        printf("\t\t\t\t��������˳�");
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
            printf("\n\n\t\t\t\t���޵��ڻ�1���ڽ����ڵ�ͼ��\n\n");
            return;
        }
    t=Student_head->next;
    printf("\n\t*********************************************");
    printf("*********************************************************\n");
    printf("\t %-10s%-20s%-20s%-10s%-20s%-10s\n\n",
           "���","����","����ѧ��","�۸�","������ʱ��","��ʱ����");
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

/*����Ա�޸�����*/
void Manager_Change_Password(Manager *Man_num)
{
    char password_tem[20];
    printf("\t\t�����С�����\n");
    Sleep(500);
    printf("\t\t������ԭ���룺");
    if(Password_Text_Find(Man_num->man_passw)==0)
    {
        printf("\n\t\t�Ѿ����������������Σ����˳��޸�����ϵͳ������\n");
        Sleep(1500);
        return;
    }
    printf("\n\t\t��֤�С�����\n");
    Sleep(1000);
    printf("\t\t��֤�ɹ���\n");
    Sleep(500);
    printf("\t\t������������(6~10λ)��");
    Password_Input(password_tem);
    printf("\n\t\t���ٴ����������룺");
    if(Password_Text(password_tem)==0)
    {
        printf("\t\t�Ѿ����������������Σ����˳��޸�����ϵͳ������\n");
        Sleep(1500);
        return;
    }
    Man_num->man_passw[0]='\0';
    strcat(Man_num->man_passw,password_tem);
    Sleep(500);
    printf("\n\t\t���Եȣ������޸ġ�����\n");
    Sleep(1000);
    printf("\t\t������\n");
    Sleep(1000);
    printf("\t\t������\n");
    Sleep(1000);
    printf("\t\t��ϲ���޸ĳɹ���\n");
    printf("\t\t��������˳�");
    getch();
}
/*�ϼ��鼮*/
void Manager_Add_Book(void)
{


    char mab='1';

    while(mab!='3')
    {
        system("CLS");
        printf("\n\n\n\n\t\t\t\t\t\t��ѡ���ϼܵ�����\n");
        printf("\t\t\t\t****************************************************\n");
        printf("\n\t\t\t\t1�����ӿ��\n");
        printf("\t\t\t\t2���ϼ�����\n");
        printf("\t\t\t\t3���˳�\n");
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
            printf("\t\t\t�����������������\n");
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
        printf("\t\t\t\t�޷����ӿ��\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\t\t\t\t����������ı��:");
    gets(ch);
    t=Find_BookofName(ch);
    if(!t)
    {
        printf("\t\t\t\t��Ǹ���޴���\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\t\t\t\t����������������");
    scanf("%d",&n);
    getchar();
    t->book_rest+=n;
    Sleep(500);
    printf("\t\t\t\t�������ӡ�����\n");
    Sleep(500);
    printf("\t\t\t\t�ɹ�����%d���鼮\n",n);
    printf("\t\t\t\t��������˳�");
    getch();
}
void Manager_Add_Book2(void)
{

    printf("\t\t\t\t������������Ϣ��\n");
    Book *new=(Book *)malloc(sizeof(Book));
    new->next=NULL;
    Book *t=Book_head;
    printf("\t\t\t\t��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-����\n");
    printf("\t\t\t\t|                ע�⣺���Ϊ4λ��    ��ͷ���ִ���ͼ�����                 |\n");
    printf("\t\t\t\t|                       ¼����Ϣʱ���ܼӿո�                             |\n");
    printf("\t\t\t\t|      1���̲��ࡿ     2����ѧ�ࡿ     3�������ࡿ     4�������ࡿ         |\n");
    printf("\t\t\t\t|      5�������ࡿ     6����ʷ�ࡿ     7��ҽѧ�ࡿ     8�������ࡿ         |\n");
    printf("\t\t\t\t��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-����\n");
    printf("\t\t\t\t�鼮��ţ�");
    gets(new->book_num);
    if(Find_BookofName(new->book_num))
    {
        free(new);
        printf("\t\t\t\t�������ϼܹ�����ѡ�����ӿ��\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\t\t\t\t������");
    gets(new->book_name);
    printf("\t\t\t\t���ߣ�");
    gets(new->book_at_name);
    printf("\t\t\t\t�����磺");
    gets(new->book_cp_name);
    printf("\t\t\t\t�۸�");
    scanf("%f",&new->book_price);
    getchar();
    printf("\t\t\t\t��棺");
    scanf("%d",&new->book_rest);
    new->book_time=0;
    getchar();
    Sleep(500);
    printf("\t\t\t\t�����ϼܡ�����\n");
    Sleep(500);
    printf("\t\t\t\t������\n");
    Sleep(500);
    printf("\t\t\t\t������\n");
    Sleep(500);
    printf("\t\t\t\t�ϼܳɹ���\n");
    while(t->next)
    {
        t=t->next;
    }
    t->next=new;
    printf("\t\t\t\t��������˳�");
    getch();
}
/*����Ա�¼��鼮*/
void Manager_Down_Book(void)
{
    char book_num[20];
    Book *t=Book_head->next;
    Lookofnum();
    if(!t)
    {
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\t\t\t\t���������¼ܵ��鼮��ţ�");
    gets(book_num);
    t=Find_BookofName(book_num);
    if(!t)
    {
        printf("\t\t\t\t��Ǹ���޴��鼮\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    t->book_rest=0;
    Sleep(500);
    printf("\t\t\t\t�����¼ܡ�����\n");
    Sleep(500);
    printf("\t\t\t\t�¼ܳɹ���\n");
    printf("\t\t\t\t��������˳�");
    getch();

}

/*����Ա����ѧ��*/
void Manager_Manager_Stu(void)
{

    char mms='1';

    while(mms!='5')
    {
        system("CLS");
        printf("\n\n\n\n\t\t\t\t****************************************************\n");
        printf("\t\t\t\t\t\tѧ���������\n");
        printf("\t\t\t\t****************************************************\n");
        printf("\t\t\t\t\t1���鿴ѧ������\n");
        printf("\t\t\t\t\t2��ǿ��ѧ������\n");
        printf("\t\t\t\t\t3��ɾ��ѧ���˺Ų��黹�����鼮\n");
        printf("\t\t\t\t\t4���鿴ѧ������Ľ������\n");
        printf("\t\t\t\t\t5������\n");
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
            printf("\t\t\t\t�����������������\n");
            Sleep(3000);
            break;
        }
    }
}

/*����Ա�鿴ѧ���Ľ������*/
void Manager_LookBook_Stu(void)
{
    system("CLS");
    Student *t=Student_head->next;
    printf("\t\t\t\t���ڴ�ӡѧ���������������\n");
    Sleep(1000);
    if(!t)
    {
        printf("\n\t\t\t\t��Ǹ������ѧ��\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    while(t)
    {
        printf("\t������%s\tѧ�ţ�%s\t�ֻ��ţ�%s",t->student_name,t->student_num,t->student_phone);
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
            printf("\n\t\t\t���޽����¼\n");
            printf("\t*********************************************");
        printf("*********************************************************\n\n");
        }
        else{
        printf("\n\t*********************************************");
        printf("*********************************************************\n");
        printf("\t %-10s%-20s%-20s%-25s%-10s%-20s\n\n",
               "���","����","����","������","�۸�","������ʱ��");
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
    printf("\n\t\t\t\t��������˳�");
    getch();
}


/*����Ա�鿴ѧ������*/
void Manager_Look_Stu(void)
{
    Student *t=Student_head->next;
    printf("\t\t\t\t���ڴ�ӡѧ������������\n");
    Sleep(1000);
    if(!t)
    {
        printf("\n\t\t\t\t��Ǹ������ѧ��\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\n\n     *****************************************************");
    printf("*********************************************************\n\n");
    printf("      %-15s%-20s%-20s%-15s%-24s%-10s\n\n",
           "����","ѧ��","�绰","����","���֤��","��������");
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
    printf("\t\t\t\t��������˳�");
    getch();

}
/*ǿ�ƻ���*/
void Manager_Return_Stu(void)
{
    char ch[20];
    Book *a;
    Student *t=Student_head->next;

    if(!t)
    {
        printf("\n\t\t\t\t��Ǹ������ѧ��\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\n\n     *************************************");
    printf("************************************\n\n");
    printf("\t %-10s%-20s%-24s%-10s\n\n",
           "����","ѧ��","���֤��","��������");
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
    printf("\t\t\t\t����������ǿ�ƻ����ѧ�ţ�");
    gets(ch);
    t=Find_Stu(ch);
    if(!t)
    {
        printf("\t\t\t\t��Ǹ���޸�ѧ��\n");
        printf("\t\t\t\t��������˳�");
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
        printf("\t\t\t\t��Ǹ����ѧ����������Ϊ0���޷�ǿ�ƻ���\n");
        printf("\t\t\t\t��������˳�");
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
    printf("\t\t\t\t����ǿ�ƻ��顤����\n");
    Sleep(500);
    printf("\t\t\t\t������\n");
    Sleep(500);
    printf("\t\t\t\tǿ�ƻ���ɹ���\n");
    printf("\t\t\t\t��������˳�");
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
    printf("\t\t\t\t���ڴ�ӡѧ������������\n");
    Sleep(1000);
    if(!t)
    {
        printf("\n\t\t\t\t��Ǹ������ѧ��\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\n\n\t\t     *************************************");
    printf("*********************************************\n\n");
    printf("\t\t      %-10s%-20s%-20s%-20s%-10s\n\n",
           "����","ѧ��","�绰","����","��������");
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

    printf("\t\t\t\t����������ɾ��ѧ�����˺ţ�");
    gets(bh);
    t=Find_Stu(bh);
    if(!t)
    {
        printf("\t\t\t\t��Ǹ���޸�ѧ��\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }
    Sleep(500);
    printf("\t\t\t\t����ɾ��������\n");
    Sleep(500);
    printf("\t\t\t\tɾ���ɹ���\n");
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
    printf("\t\t\t\t��������˳�\n");
    getch();
    return;
}

/*���������*/
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
            printf("\n\t\t\t\t���������������ȷ���ȵ�����:");
    }
}
/*�������*/
int Password_Text(char *Password)
{
    char password_tem[20];
    int tem=0;
    int n=0;    //����������
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
                printf("\n\t\t\t\t�����������벻һ�£�����������,������%d��������᣺",3-n);
            }
            else if(n==3)
                printf("\n\t\t\t\t�������\n");
        }
    }
    return tem;
}
/*������֤*/
int Password_Text_Find(char *Password)
{
    char password_tem[30];
    int tem=0;
    int n=0;    //����������
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
            printf("\n\t\t\t\t����������������룬�㻹��%d�λ��᣺",3-n);
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
        printf("\t\t\t\t��ʧ��\n");
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
/*��ѧ���ļ��е���Ϣ������ѧ������*/
Student *Student_load(void)
{
    FILE *fp;
    Student *h=NULL,*t=h,*p;
    if((fp=fopen("Studentnode.txt","r"))==NULL)
    {
        printf("\t\t\t\t��ʧ��\n");
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
        int len=strlen(p->student_psw);			//�������
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
        printf("\t\t\t\t��ʧ��\n");
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
        int len=strlen(p->man_passw);			//�������
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
/*�����鼮�������ļ�*/
void Save_Book(void)
{
    FILE *fp;
    Book *t=Book_head->next;
    if(!t)
        return;
    if((fp=fopen("Booknode.txt","w+"))==NULL)
    {
        printf("\t\t\t\t��ʧ��\n");
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
/*����ѧ���������ļ�*/
void Save_Student(void)
{
    FILE *fp;
    Student *t=Student_head->next;
    if(!t)
        return;
    if((fp=fopen("Studentnode.txt","w+"))==NULL)
    {
        printf("\t\t\t\t��ʧ��\n");
        exit(1);
    }
    while(t->next)
    {
        int len=strlen(t->student_psw);			//�������
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

    int len=strlen(t->student_psw);			//�������
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
/*�������Ա�������ļ�*/
void Save_Manger(void)
{
    FILE *fp;
    Manager *t=Manager_head->next;
    if(!t)
        return;
    if((fp=fopen("Managernode.txt","w+"))==NULL)
    {
        printf("\t\t\t\t��ʧ��\n");
        exit(1);
    }
    while(t->next)
    {
        int len=strlen(t->man_passw);			//�������
        for(int i=0; i<len; i++)
        {
            t->man_passw[i]=t->man_passw[i]+(i%4+1);
        }
        fprintf(fp,"%s ",t->man_name);
        fprintf(fp,"%s ",t->man_acc);
        fprintf(fp,"%s\n",t->man_passw);
        t=t->next;
    }
    int len=strlen(t->man_passw);			//�������
    for(int i=0; i<len; i++)
    {
        t->man_passw[i]=t->man_passw[i]+(i%4+1);
    }
    fprintf(fp,"%s ",t->man_name);
    fprintf(fp,"%s ",t->man_acc);
    fprintf(fp,"%s",t->man_passw);
    fclose(fp);
}
/*������Ϣ�������ļ�*/
void Massage_Save(void)
{
    Save_Book();
    Save_Student();
    Save_Manger();
}

/*ѧ���˿�*/
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
            printf("\t\t\t\t����������������룺\n");
            Sleep(1500);
            break;
        }
    }
}
/*ѧ��ע���˺�*/
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
    printf("\t\t\t\t\t��ӭ����ע�����\n");
    printf("\t\t\t****************************************************\n");
    Sleep(1);
    printf("\t\t\t������������Ϣ\n\n");
    printf("\t\t\t������\n");
    scanf("%s",new->student_name);
    printf("\t\t\t�Ա�\n");
    scanf("%s",new->student_sex);
    printf("\t\t\tѧ�ţ�\n");
    scanf("%s",new->student_num);
    printf("\t\t\t���֤�ţ�\n");
    scanf("%s",new->student_id);
    printf("\t\t\t�ֻ��ţ�\n");
    scanf("%s",new->student_phone);
    printf("\t\t\t���գ�����ʽ������2022.05.04��\n");
    scanf("%s",new->student_bsd);
    printf("\t\t\t���룺�����볤�Ȳ�����20��\n");
    Password_Input(new->student_psw);
    printf("\n\t\t\t�ٴ��������룺\n");
    if(Password_Text(new->student_psw)==0)
    {
        printf("\n\t\t\t�����������3�Σ����˳�ע��ϵͳ������");
        Sleep(5000);
        free(new);
        return;
    }
    Sleep(500);
    printf("\n\t\t\t\t����ע��\n\t\t\t\t������\n");
    Sleep(1000);
    printf("\t\t\t\t������\n");
    Sleep(1000);
    printf("\t\t\t\t������\n");
    Sleep(1000);
    printf("\t\t\t\tע��ɹ���\n");
    while(getchar()!='\n');
    t=Student_head;
    while(t->next)
    {
        t=t->next;
    }
    t->next=new;
    printf("\t\t\t\t��������˳�");
    getch();
}
void Find_Password(void)
{
    Student *find_tem;
    char student_num[50];
    char password_find[20];
    printf("\t\t\t��ӭ�����һ�����ϵͳ\n");
    Sleep(500);
    printf("\t\t\t������\n");
    Sleep(500);
    int l=1;
    while(l!=12)
    {
        printf("\t\t\t������ѧ�ţ�");
        gets(student_num);
        l=strlen(student_num);
        if(l!=12)
            printf("\t\t\t�˺�������������ȷ���ȵ��˺�\n");
    }
    student_num[12]='\0';
    find_tem=Find_Num(student_num);
    printf("\t\t\t��������˺ţ�");
    puts(student_num);
    Sleep(500);
    printf("\t\t\t����Ϊ������\n");
    Sleep(500);
    printf("\t\t\t������\n");
    Sleep(500);
    if(find_tem==NULL)
    {
        printf("\t\t\t��Ǹ���޴��˺ţ������˳��һ�����ģ��\n");
        Sleep(1000);
        printf("\t\t\t������\n");
        Sleep(3000);
        return;
    }
    printf("\t\t\t%s�����ã�\n",find_tem->student_name);
    Sleep(300);
    printf("\t\t\t��������ǣ� ");
    Sleep(300);
    if(Password_Text_Find(find_tem->student_bsd)==0)
    {
        printf("\n\t\t\t�����������3�Σ����˳��һ�����ϵͳ������\n");
        Sleep(1500);
        return;
    }
    Sleep(500);
    printf("\n\t\t\t���ڲ���\n");
    Sleep(500);
    printf("\t\t\t������\n");
    Sleep(500);
    printf("\t\t\t������\n");
    Sleep(500);
    printf("\t\t\t%s ���ã����������� ��%s",find_tem->student_name,find_tem->student_psw);
    printf("\n\t\t\t���μ���������\n");
    printf("\t\t\t��������˳�");
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
/*ѧ���˵�¼*/
void Student_Login(void)
{
    char sl='1';
    char enter_num[50];
    char enter_passw[20];
    int l=1;
    Student *enter_stu;
    while(l!=12)
    {
        printf("\n\t\t\t\t����������˺ţ�");
        gets(enter_num);
        l=strlen(enter_num);
        if(l!=12)
            printf("\t\t\t\t�˺�������������ȷ���ȵ��˺�\n");
    }
    enter_num[12]='\0';
    enter_stu=Find_Num(enter_num);
    if(enter_stu==NULL)
    {
        printf("\n\t\t\t\t��Ǹ���޴��˺�");
        Sleep(500);
        printf("\n\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\t\t\t\t���������룺");
    if(Password_Text_Find(enter_stu->student_psw)==0)
    {
        printf("\n\t\t\t\t�����������3�Σ����˳���¼ϵͳ������");
        Sleep(2000);
        return;
    }
    Sleep(500);
    printf("\n\t\t\t\t���ڵ�¼�У����Ժ󡤡���");
    Sleep(500);
    printf("\n\t\t\t\t������������\n");
    Sleep(500);
    printf("\n\t\t\t\t��¼�ɹ���\n");
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
            printf("\t\t\t�����������������\n");
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
        printf("\t\t\t��Ǹ�������鼮\n");
        printf("\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\t\t\t����������Ҫ���ҵ�����������ı�ţ�");
    gets(book_n);
    while(t)
    {
        if(strcmp(book_n,t->book_name)==0||strcmp(book_n,t->book_num)==0)
            break;
        t=t->next;
    }
    if(t==NULL)
    {
        printf("\t\t\t��Ǹ���޴��鼮\n");
        printf("\t\t\t��������˳�");
        getch();
        return;
    }
    t=Book_head->next;
    printf("\n\n\t\t*********************************************");
    printf("*************************************************\n\n");
    printf("\t\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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
    printf("\n\t\t\t��������˳�");
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
    printf("\t\t\t�����С�����\n");
    Sleep(500);
    printf("\t\t\t������ԭ���룺");
    if(Password_Text_Find(Stu_num->student_psw)==0)
    {
        printf("\n\t\t\t�Ѿ����������������Σ����˳��޸�����ϵͳ������\n");
        Sleep(1500);
        return;
    }
    printf("\n\t\t\t��֤�С�����\n");
    Sleep(1000);
    printf("\t\t\t��֤�ɹ���\n");
    Sleep(500);
    printf("\t\t\t������������(6~20λ)��");
    Password_Input(password_tem);
    printf("\n\t\t\t���ٴ����������룺");
    if(Password_Text(password_tem)==0)
    {
        printf("\t\t\t�Ѿ����������������Σ����˳��޸�����ϵͳ������\n");
        Sleep(3000);
        return;
    }
    Stu_num->student_psw[0]='\0';
    strcat(Stu_num->student_psw,password_tem);
    Sleep(500);
    printf("\n\t\t\t���Եȣ������޸ġ�����\n");
    Sleep(1000);
    printf("\t\t\t������\n");
    Sleep(1000);
    printf("\t\t\t������\n");
    Sleep(1000);
    printf("\t\t\t��ϲ���޸ĳɹ���\n");
    printf("\t\t\t��������˳�");
    getch();
}
void Find_Theborrow(Student *Stu_num)
{
    int tem=0;
    Book *t;
    printf("\t\t\t�����С�����\n");
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
        printf("\t\t\t���޽����¼\n");
        printf("\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\n\n\t*********************************************");
    printf("*********************************************************\n\n");
    printf("\t %-10s%-20s%-20s%-25s%-10s%-20s\n\n",
           "���","����","����","������","�۸�","������ʱ��");
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
    printf("\n\t\t\t\t��������˳�");
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
    printf("\t\t\t\t\t\t\t����ϵͳ\n");
    printf("\t\t\t\t*****************************");
    printf("****************************\n");
    if(n==10)
    {
        printf("\t\t\t\t\t\t���ã����ѽ���10�����ѵ��������޶");
        printf("\t\t\t\t\t\t���ȹ黹�ѽ��鼮\n\n");
        printf("\t\t\t\t\t\t��������˳�");
        getch();
        return;
    }
    printf("\n\t\t\t\t\t���ѽ��鼮%d�������ɽ�%d��\n",n,10-n);
    Sleep(500);
    printf("\n\n\t\t\t\t\t\t\t�鵥����\n");
    Sleep(500);
    Print_Book();
    printf("\n\t\t\t��ѡ���������ı�ţ�");
    gets(numb);
    t=Book_exit(numb);
    printf("\t\t\t���ڰ�������\n");
    Sleep(1000);
    if(!t)
    {
        printf("\t\t\t��Ǹ���޴��飬����ʧ��\n");
        printf("\t\t\t��������˳�");
        getch();
        return;
    }
    if(t->book_rest==0)
    {
        printf("\t\t\t��Ǹ����治�㣬����ʧ��\n");
        printf("\t\t\t��������˳�");
        getch();
        return;
    }
    if(Ifborrow(Stu_num,numb))
    {
        printf("\t\t\t��Ǹ�����ѽ�����飬�����ظ�����\n");
        printf("\t\t\t��������˳�");
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
            time_t timep;//��¼����ʱ��
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
    printf("\t\t\t������\n");
    printf("\t\t\t��ϲ������ɹ���\n");
    printf("\t\t\t��������˳�");
    getch();
    return;
}

/*��ӡ�鵥*/
void Print_Book(void)
{
    Book *t=Book_head->next;
    if(t==NULL)
    {
        printf("\t\t\t��Ǹ�������ϼ��鼮\n");
        Sleep(2000);
        return;
    }
    printf("\n\n\t\t*********************************************");
    printf("***********************************************************\n\n");
    printf("\t\t %-10s%-20s%-20s%-25s%-10s%-10s%-10s\n\n",
           "���","����","����","������","�۸�","���","���Ĵ���");
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
/*Ѱ�Ҹ����Ƿ����*/
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
/*��ѯѧ���Ƿ�������*/
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
/*ѧ������*/
void Stu_Back(Student *Stu_num)
{
    system("CLS");
    char book_num[15];
    int tem=0;
    printf("\n\t\t\t\t*****************************");
    printf("****************************\n");
    printf("\t\t\t\t\t\t\t����ϵͳ\n");
    printf("\t\t\t\t*****************************");
    printf("****************************\n");
    printf("\n\n\t\t\t���ڲ����ѽ��鼮������\n");
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
        printf("\n\t\t\t���޽����¼\n");
        printf("\n\t\t\t��������˳�");
        getch();
        return;
    }
    Print_Borbook(Stu_num);
    printf("\n\t\t\t\t��������ı�Ž��й黹��");
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
        printf("\t\t\t\t���������δ�������\n");
        printf("\t\t\t\t��������˳�");
        getch();
        return;
    }

    Sleep(500);
    printf("\t\t\t���ڹ黹������\n");
    Sleep(500);
    Bake_Book(Stu_num,book_num);
    printf("\t\t\t�黹�ɹ���\n");
    printf("\t\t\t��������˳�");
    getch();
}
/*��ӡ�����鼮*/
void Print_Borbook(Student *Stu_num)
{
    int tem=0;
    Book *t;
    printf("\n\n\t\t*********************************************");
    printf("********************************************************\n\n");
    printf("\t\t %-10s%-20s%-20s%-25s%-10s%-20s\n\n",
           "���","����","����","������","�۸�","����������");
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
/*����������*/
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
