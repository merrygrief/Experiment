#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
    char number[11];                    //学号最多10位
    char name[17];                      //名字最多占16个字节
    float English;
    float math;
    float physics;
    float C_language;
    float sum;
    float average;
    struct student *next;
    struct student *previous;
};
void get_record(struct student **head);         //用于输入信息
void put_record(struct student **head);         //用于输出原本输入的各项信息
int menu(void);
void modify_record(struct student **head);      //用于修改制修订学生的指定成绩
void count_record(struct student **head);       //用于统计总成绩与平均成绩
void final_output(struct student **head);       //需要先进行统计

int main()
{
    int choice;
    char then[10] = "";
    struct student *head;
    get_record(&head);
    do {
        choice = menu();
        switch(choice)
        {
            case 1: put_record(&head); break;
            case 2: modify_record(&head); break;
            case 3: count_record(&head); break;
            case 4: final_output(&head); break;
            default: break;
        }
        puts("Finish the procedure by entering the word \"over\" or continue.");
        scanf("%s", then);
    }while(strcmp(then, "over") != 0);
    return 0;
}

int menu(void)
{
    int choice;
    puts("What do you want to do?");
    puts("1.output the information of each student.");
    puts("2.modify specific data.");
    puts("3.count the average score of each student.");
    puts("4.output your student id, name, total score and average score of the four courses.");
    puts("5.exit.");
    scanf("%d", &choice);
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
        puts("enter your choice again.");
        scanf("%d", &choice);
    }
    return choice;
}

void get_record(struct student **head)                         //链表最后多余了一个结构体
{
    struct student *loc_head = NULL, *tail;
    puts("Enter the massage by following the order of");
    puts("\"number, name, score of English,score of math, score of physics, score of C_language\"");
    puts("Finish the input by entering the word \"over\"");
    loc_head = (struct student *) malloc(sizeof(struct student));
    loc_head->previous = NULL;                                  //双向链表头指针前一项为空
    tail = loc_head;
    scanf("%s", tail->number);
    while(strcmp(tail->number, "over") != 0) {
        scanf("%s%f%f%f%f", tail->name, &tail->English, &tail->math, &tail->physics, &tail->C_language);
        tail->next = (struct student *) malloc(sizeof(struct student));
        struct student *temp;                                   //双向链表
        temp = tail;
        tail = tail->next;
        tail->previous = temp;
        scanf("%s", tail->number);
    }
    tail->next = NULL;
    *head = loc_head;
}

void put_record(struct student **head)
{
    struct student *p = *head;
    puts("number         name             English   math      physics   C_language");
    while(strcmp(p->number, "over") != 0){
        printf("%-15s%-17s%-10.2f%-10.2f%-10.2f%-10.2f\n", p->number, p->name, p->English, p->math, p->physics, p->C_language);
        p = p->next;
    }
}

void modify_record(struct student **head)
{
    struct student *p = *head;
    char loc_number[11], loc_property[11];
    float loc_data;
    puts("enter the number of student, its property and property value to modify specific data.");
    puts("Finish the input by entering the word \"over\"");
    scanf("%s", loc_number);
    while(strcmp(loc_number, "over") != 0) {
        scanf("%s%f", loc_property, &loc_data);
        while(strcmp(loc_number, p->number) != 0 && strcmp(p->number, "over") != 0) p = p->next;
        if(strcmp(loc_number, p->number) == 0) {
            if(strcmp(loc_property, "English") == 0) p->English = loc_data;
            else if(strcmp(loc_property, "math") == 0) p->math = loc_data;
            else if(strcmp(loc_property, "physics") == 0) p->physics = loc_data;
            else if(strcmp(loc_property, "C_language") == 0) p->C_language = loc_data;
            else printf("There is no %s could to be modified.\n", loc_property);
        }
        else puts("There is no such number of student");
        scanf("%s", loc_number);
        p = *head;
    }
}

void count_record(struct student **head)
{
    struct student *p = *head;
    while(strcmp(p->number, "over") != 0) {
        p->sum = p->English + p->math + p->physics + p->C_language;
        p->average = p->sum / 4;
        p = p->next;
    }
    p = *head;
    puts("number         name             average_score");
    while(strcmp(p->number, "over") != 0){
        printf("%-15s%-17s%-10.2f\n", p->number, p->name, p->average);
        p = p->next;
    }
}

void final_output(struct student **head)
{
    struct student *p = *head;
    puts("number         name             sum       average_score");
    while(strcmp(p->number, "over") != 0){
        printf("%-15s%-17s%-10.2f%-10.2f\n", p->number, p->name, p->sum, p->average);
        p = p->next;
    }
}
/*      数据：
U202017182 zmx 78 89 97.7 87.6
U202017180 wbj 99 88.7 80.5 91.4
U202017191 yxw 89 87.5 89 94
over
*/ /*   选择2
U202017182 English 89
U202017182 math 88
over
*/