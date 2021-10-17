#include<stdio.h>
#include<string.h>
#include "conio2.h"
#include "car.h"
#include <time.h>

void addAdmin()
{
    FILE* fp;
    fp=fopen("Admin.bin","r");
    if(fp==NULL)
    {
        fp=fopen("Admin.bin","wb");
        User ad[2]={{"admin","test","Dhanveer"},{"Tester","dummy@123","Rohit"}};
        fwrite(ad,sizeof(ad),1,fp);
     }

    fclose(fp);
}

User* getInput()
{
     clrscr();
     int i;
     static User usr;
     textcolor(YELLOW);
     gotoxy(54,1);
     printf("CAR RENTAL SYSTEM");
     textcolor(YELLOW);
     gotoxy(1,2);
        for(i=1;i<=120;i++)
           printf("%c",247);
     gotoxy(54,5);
     printf("* LOGIN PANEL *");
     textcolor(LIGHTBLUE);
     gotoxy(1,7);
        for(int i=1;i<=120;i++)
            printf("%c",247);
     textcolor(LIGHTBLUE);
     gotoxy(1,17);
        for(i=1;i<=120;i++)
            printf("%c",247);
     textcolor(WHITE);
     gotoxy(100,8);
     printf("Press 0 to Exit");
     textcolor(LIGHTBLUE);
     gotoxy(54,11);

     printf("Enter User ID:");
     textcolor(WHITE);
     fflush(stdin);
     fgets(usr.userid,20,stdin);
     char *pos;
     pos=strchr(usr.userid,'\n');
     if(pos!=NULL)
        *pos='\0';

     if(strcmp(usr.userid,"0")==0)
     {
        textcolor(LIGHTRED);
        gotoxy(54,19);
        printf("Login Cancelled!");
        getch();
        return NULL;
     }
     textcolor(LIGHTBLUE);
     gotoxy(54,13);
     printf("Enter Password:");
     textcolor(WHITE);
     fflush(stdin);
     for(i=0;;i++)
     {
         usr.pwd[i]=getch();
         if(usr.pwd[i]==13)
            break;

         if(usr.pwd[i]==8)
         {
             printf("\b \b");
             i--;
             usr.pwd[i]=getch();
             printf("*");
         }
         else
            printf("*");
     }
     usr.pwd[i]='\0';
     if(strcmp(usr.pwd,"0")==0)
     {
        textcolor(LIGHTRED);
        gotoxy(54,19);
        printf("Login Cancelled!");
        getch();
        return NULL;
     }
     return &usr;
     getch();
 }

int checkUserExist(User usr,char *name)
{
    int found=0;
    if(strcmp(usr.userid,"")==0 || strcmp(usr.pwd,"")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(54,19);
        printf("Both Fields Are Mandatory.Try again");
        getch();
        gotoxy(54,19);

        printf("\t\t\t\t\t\t");
        return 0;
    }

    FILE *fp;
    if(strcmp(name,"admin")==0)
    {
       fp=fopen("admin.bin","rb");
    }
    else
    {
       fp=fopen("emp.bin","rb");
    }


    if(fp==NULL)
    {
        gotoxy(54,19);
        textcolor(RED);
        printf("Sorry ! can't open the File.");
        getch();
        gotoxy(54,19);
        printf("\t\t\t\t\t\t");
        return -1;
    }

    User u;
    while(fread(&u,sizeof(u),1,fp)==1)
    {
    if(strcmp(u.userid,usr.userid)==0 && strcmp(u.pwd,usr.pwd)==0)
        {
            found=1;
            break;
        }
    }
    if(found==0)
    {
        gotoxy(54,19);
        textcolor(LIGHTRED);
        printf("INVALID USERID OR PASSWORD.");
        getch();
        printf("\t\t\t\t\t\t");
    }
    else
    {
        gotoxy(54,19);
        textcolor(LIGHTGREEN);
        printf("LOGIN SUCCESSFULL !");
        getch();
        printf("\t\t\t\t\t\t");
    }
    fclose(fp);
    return found;
 }

int adminMenu()
{
    int i;
    textcolor(LIGHTRED);
    gotoxy(54,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(56,6);
    printf("ADMIN MENU\n");
    for(i=1;i<=120;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(54,8);
    printf("1. Add Employee");
    gotoxy(54,9);
    printf("2. Add Car Details");
    gotoxy(54,10);
    printf("3. Show Employee");
    gotoxy(54,11);
    printf("4. Show Car Details");
    gotoxy(54,12);
    printf("5. Delete Employee");
    gotoxy(54,13);
    printf("6. Delete Car Details");
    gotoxy(54,14);
    printf("7. Exit");
    gotoxy(54,16);
    printf("Enter Choice: ");
    scanf("%d",&i);

    return i;
}

void addEmployee()
{
    FILE* fp;
    User usr;
    int i;
    int no;
    char choice;
    char id[20];
    fp=fopen("emp.bin","ab+");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("SORRY, FILE CANT'T BE OPEN...");
        getch();
    }
    fseek(fp,0,SEEK_END);
    no=ftell(fp)/60;
    if(no!=0)
    {
        char *pos;
        fseek(fp,(signed int)-(sizeof(usr)),SEEK_END);
        fread(id,sizeof(id),1,fp);
        pos=strchr(id,'_');
        pos++;
        sscanf(pos,"%d",&no);
        //no=atoi(pos); Both Have Done same work
    }
    no++;
    fseek(fp,0,SEEK_END);
        do{
                clrscr();
            textcolor(LIGHTRED);
            gotoxy(54,2);
            printf("CAR RENTAL SYSTEM\n");
            textcolor(LIGHTGREEN);
            for(i=1;i<=120;i++)
                printf("~");
            textcolor(WHITE);
            gotoxy(49,5);
            printf("*** ADD EMPLOYEE DETAILS ***");

            textcolor(YELLOW);
            gotoxy(1,8);
            printf("Enter Employee Name: ");
            textcolor(WHITE);
            fflush(stdin);
            fgets(usr.name,20,stdin);
            char *pos;

            pos=strchr(usr.name,'\n');
            if(pos!=NULL)
            *pos='\0';
            textcolor(YELLOW);
            gotoxy(1,9);
            printf("Enter Employee PassWord: ");
            textcolor(WHITE);
            fgets(usr.pwd,20,stdin);

            pos=strchr(usr.pwd,'\n');
            if(pos!=NULL)
            *pos='\0';

            sprintf(usr.userid,"Emp_%d",no);
            i=fwrite(&usr,sizeof(usr),1,fp);

            if(i==1)
            {
                textcolor(LIGHTGREEN);
                gotoxy(54,18);
                printf("Employee Added Successfully");
                textcolor(YELLOW);
                gotoxy(1,10);
                printf("Employee ID is:");
                textcolor(LIGHTGREEN);
                printf("%s",usr.userid);
            }
            else
            {
                textcolor(RED);
                gotoxy(54,12);
                printf("Employee Can't be Added.");
            }
            gotoxy(1,21);
            textcolor(RED);
            printf("\nDO YOU WANT TO ADD MORE EMPLOYEE(Y/N): ");
            textcolor(WHITE);
            scanf(" %c",&choice);
            no++;
    }while(choice=='Y' || choice=='y');
    fclose(fp);
}

void addCarDetails()
{
    FILE *fp;
    Car car;
    int i;
    int id,no;
    char choice;
    fp=fopen("car.bin","ab+");
    fseek(fp,(signed int)-(sizeof(car)),SEEK_END);
    no=fread(&id,sizeof(id),1,fp);
    if(no!=1)
    {
        id=1;
    }
    else
    {
        id++;
    }
    fseek(fp,0,SEEK_END);
    car.car_id=id;
    do{
        clrscr();
        textcolor(LIGHTRED);
        gotoxy(54,2);
        printf("CAR RENTAL SYSTEM\n");
        textcolor(LIGHTGREEN);
        for(i=1;i<=120;i++)
            printf("~");
        textcolor(WHITE);
        gotoxy(49,5);
        printf("*** ADD CAR DETAILS ***");
        textcolor(YELLOW);
        gotoxy(1,8);
        printf("Enter Car Model: ");
        textcolor(WHITE);
        fflush(stdin);
        fgets(car.car_name,50,stdin);
        char *pos;
        pos=strchr(car.car_name,'\n');
        if(pos!=NULL)
            *pos='\0';

        textcolor(YELLOW);
        printf("Enter Car Capacity: ");
        textcolor(WHITE);
        scanf("%d",&car.capacity);
        textcolor(YELLOW);
        printf("Enter Car Count: ");
        textcolor(WHITE);
        scanf("%d",&car.car_count);
        textcolor(YELLOW);
        printf("Enter Car Rent Per Day: ");
        textcolor(WHITE);
        scanf("%d",&car.price);
        textcolor(YELLOW);
        printf("CAR ID IS: ");
        textcolor(LIGHTGREEN);
        printf("%d",car.car_id);
        no=fwrite(&car,sizeof(car),1,fp);
        if(no==1)
        {
            gotoxy(54,18);
            printf("CAR ADDED SUCCESSFULLY\n\n");
            textcolor(LIGHTRED);
            printf("DO YOU WANT TO ADD MORE CAR(Y/N): ");
            textcolor(WHITE);
            scanf(" %c",&choice);
        }
        else{
            textcolor(LIGHTRED);
            gotoxy(54,18);
            printf("CAR CAN'T BE ADDED");
            getch();
        }
        car.car_id++;
    }while(choice=='Y' || choice=='y');
     fclose(fp);
}

void viewEmployee()
{
    int i;
    User usr;
    FILE *fp;
    fp=fopen("emp.bin","rb");
    if(fp==NULL)
    {
        printf("NO EMPLOYEE AVAILABLE !!!!");
        getch();
        return;
    }
    textcolor(YELLOW);
    gotoxy(54,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(53,5);
    printf("* EMPLOYEE DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    printf(" Employee ID");
    gotoxy(54,8);
    printf("Name");
    gotoxy(105,8);
    printf("PassWord\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    i=10;
    while(fread(&usr,sizeof(usr),1,fp)==1)
    {
        textcolor(YELLOW);
        printf(" %s",usr.userid);
        gotoxy(54,i);
        printf("%s",usr.name);
        gotoxy(105,i);
        printf("%s\n",usr.pwd);
        i++;
    }
    getch();
    fclose(fp);
}

void showCarDetails()
{
    int i;
    Car car;;
    FILE *fp;
    fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("NO CAR AVAILABLE !!!!");
        getch();
        return;
    }
    textcolor(YELLOW);
    gotoxy(54,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(54,5);
    printf("* CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    printf(" Car ID");
    gotoxy(10,8);
    printf("Car Name");
    gotoxy(48,8);
    printf("Capacity");
    gotoxy(72,8);
    printf("Count");
    gotoxy(96,8);
    printf("Rent Per day\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    i=10;
    while(fread(&car,sizeof(car),1,fp)==1)
    {
        printf(" %d",car.car_id);
        gotoxy(10,i);
        printf("%s",car.car_name);
        gotoxy(48,i);
        printf("%d",car.capacity);
        gotoxy(72,i);
        printf("%d",car.car_count);
        gotoxy(96,i);
        printf("%d\n",car.price);
        i++;
    }
    getch();
    fclose(fp);
}

int deleteEmp()
{
    int i;
    int found=0;
    char id[20];
    FILE *fp,*fp2;
    User usr;
    textcolor(YELLOW);
    gotoxy(54,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(49,5);
    printf("* DELETE EMPLOYEE RECORD(s) *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(1,13);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    fp=fopen("emp.bin","rb+");
    gotoxy(44,10);
    if(fp==NULL)
    {
        textcolor(RED);
        gotoxy(50,10);
        printf("NO EMPLOYEES AVAILABLE !!!");
        getch();
        return 0;
    }
    printf("Enter Employee ID to Delete Record:");
    textcolor(WHITE);
    fflush(stdin);
    fgets(id,20,stdin);
    char *pos;
        pos=strchr(id,'\n');
        if(pos!=NULL)
            *pos='\0';

    fp2=fopen("temp.bin","wb+");
    if(fp2==NULL)
    {
        textcolor(LIGHTRED);
        gotoxy(40,16);
        printf("EMPLOYEES CANT't BE DELETED, PLEASE TRY AGAIN LATER!!!");
        getch();
        return 0;
    }
    while(fread(&usr,sizeof(usr),1,fp)==1)
    {
        if(strcmp(id,usr.userid)==0)
        {
            found=1;
            continue;
        }
        fwrite(&usr,sizeof(usr),1,fp2);
    }
    fclose(fp);
    fclose(fp2);

    i=remove("emp.bin");
    if(i!=0)
    {
        perror("Remove:");
    }
    i=rename("temp.bin","emp.bin");
    if(i!=0)
    {
        perror("ReName:");
    }
    return found;
}

int deleteCarModel()
{
    int i;
    int found=0;
    int id;
    FILE *fp,*fp2;
    Car car;
    textcolor(YELLOW);
    gotoxy(54,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(49,5);
    printf("* DELETE CAR MODEL(s) *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(1,13);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    fp=fopen("car.bin","rb+");
    gotoxy(44,10);
    if(fp==NULL)
    {
        textcolor(RED);
        gotoxy(50,10);
        printf("NO CARs AVAILABLE !!!");
        getch();
        return 0;
    }
    printf("Enter Car ID to Delete Record:");
    textcolor(WHITE);
    scanf("%d",&id);
    fp2=fopen("temp.bin","wb+");
    if(fp2==NULL)
    {
        textcolor(LIGHTRED);
        gotoxy(40,16);
        printf("CAR MODEL CANT't BE DELETED, PLEASE TRY AGAIN LATER!!!");
        getch();
        return 0;
    }
    while(fread(&car,sizeof(car),1,fp)==1)
    {
        if(id==car.car_id)
        {
            found=1;
            continue;
        }
        fwrite(&car,sizeof(car),1,fp2);
    }

    fclose(fp);
    fclose(fp2);

    i=remove("car.bin");
    if(i!=0)
    {
        perror("Remove:");
    }
    i=rename("temp.bin","car.bin");
    if(i!=0)
    {
        perror("ReName:");
    }

    return found;
}

int empMenu()
{
    int i;
    textcolor(LIGHTRED);
    gotoxy(54,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(56,6);
    printf("EMPLOYEE MENU\n");
    for(i=1;i<=120;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(54,8);
    printf("1. RENT A CAR");
    gotoxy(54,9);
    printf("2. BOOKING DETAILs");
    gotoxy(54,10);
    printf("3. AVAILABLE CAR DETAILs");
    gotoxy(54,11);
    printf("4. SHOW ALL CAR DETAILs");
    gotoxy(54,12);
    printf("5. Exit");
    gotoxy(54,15);
    printf("Enter Choice: ");
    textcolor(WHITE);
    scanf("%d",&i);

    return i;
}

int rentCar()
{
    int i;
    int res;
    FILE *fp;
    Customer_Car_Details cust;
    res=selectCarModel();
    clrscr();
    if(res==-1 || res==-2 || res==0)
        return res;
    cust.car_id=res;

    textcolor(YELLOW);
    gotoxy(54,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    textcolor(LIGHTGREEN);
    gotoxy(50,5);
    printf("ENTER CUSTOMER CAR DETAIL's\n\n\n");
    for(i=1;i<=120;i++)
    {
        printf("*");
    }
        gotoxy(1,18);
    for(i=1;i<=120;i++)
        printf("*");
    char *pos;

        textcolor(YELLOW);
        gotoxy(50,9);
        printf("ENTER CUSTOMER NAME: ");
        textcolor(WHITE);
        fflush(stdin);
        fgets(cust.cust_name,30,stdin);
        pos=strchr(cust.cust_name,'\n');
        if(pos!=NULL)
            *pos='\0';

        textcolor(YELLOW);
        gotoxy(50,10);
        printf("ENTER PICK-UP POINT: ");
        textcolor(WHITE);
        fflush(stdin);
        fgets(cust.pick,30,stdin);
        pos=strchr(cust.pick,'\n');
        if(pos!=NULL)
            *pos='\0';

        textcolor(YELLOW);
        gotoxy(50,11);
        printf("ENTER DROP POINT: ");
        textcolor(WHITE);
        fflush(stdin);
        fgets(cust.drop,30,stdin);
        pos=strchr(cust.drop,'\n');
        if(pos!=NULL)
            *pos='\0';

        while(1)
        {
            textcolor(YELLOW);
            gotoxy(50,12);
            printf("ENTER START DATE (dd/mm/yyyy): ");
            textcolor(WHITE);
            scanf("%d/%d/%d",&cust.sd.tm_mday,&cust.sd.tm_mon,&cust.sd.tm_year);
            res=isValidDate(cust.sd);
            if(res!=1)
            {
                gotoxy(50,20);
                textcolor(RED);
                printf("WRONG or INVALID Date !!!");
                getch();
                gotoxy(49,20);
                printf("\t\t\t\t\t\t");
                gotoxy(81,12);
                printf("\t\t\t");
            }
            else
                break;
        }
        while(1)
        {
                textcolor(YELLOW);
                gotoxy(50,13);
                printf("ENTER END DATE (dd/mm/yyyy): ");
                textcolor(WHITE);
                scanf("%d/%d/%d",&cust.ed.tm_mday,&cust.ed.tm_mon,&cust.ed.tm_year);
                res=isValidDate(cust.ed);
                if(cust.sd.tm_year < cust.ed.tm_year);
                else
                {
                    if( cust.sd.tm_mon < cust.ed.tm_mon );
                    else
                    {
                        if( cust.sd.tm_mday <= cust.ed.tm_mday );
                        else
                            res=0;
                    }
                }

                if(res!=1)
                {
                    gotoxy(50,20);
                    textcolor(RED);
                    printf("WRONG or INVALID Date !!!");
                    getch();
                    gotoxy(50,20);
                    printf("\t\t\t\t\t\t");
                    gotoxy(79,13);
                    printf("\t\t\t");
                    continue;
                }
                else
                    break;
        }
        ///Write Info In file
        fp=fopen("customer.bin","ab+");
        if(fp==NULL)
        {
            gotoxy(50,20);
            textcolor(RED);
            printf("Sorry! File cannot be opened...");
            getch();
            return -1;
        }
        if(fwrite(&cust,sizeof(cust),1,fp) ==1)
        {

            printf("BOOKING DONE for : %d\n",cust.car_id);
            printf("Press Any Key To Continue....");
            getch();
            fclose(fp);
            updateCarCount(cust.car_id);
            bookedCarDetails();
            return 1;
        }
        else
        {
            gotoxy(50,20);
            textcolor(RED);
            printf("Data Cannot be write !!");
            getch();
            return -1;
        }
}

int selectCarModel()
{
    int i;
    int choice;
    int flag=0;
    Car C;
    FILE *fp;
    textcolor(YELLOW);
    gotoxy(54,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
        printf("%c",247);

    gotoxy(47,5);
    printf("SELECT THE CAR YOU WANT TO BOOK\n\n");
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(1,9);
    for(i=1;i<=120;i++)
        printf("%c",247);

    gotoxy(45,8);
    printf("CAR ID's");
    gotoxy(67,8);
    printf("CAR MODEL's");
    textcolor(YELLOW);
    fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        textcolor(RED);
        gotoxy(52,13);
        printf("SORRY! FILE CANOT BE OPEN..");
        getch();
        return -1;
    }
    textcolor(YELLOW);
    int row_no=10;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_count>0)
        {
                gotoxy(45,row_no);
                flag++;
                printf("%d",C.car_id);
                gotoxy(67,row_no);
                printf("%s",C.car_name);
                row_no++;
        }
    }
    if(flag==0)
    {
        fclose(fp);
        return -2;
    }
    gotoxy(45,row_no+3);
    printf("ENTER YOUR CHOICE AS CAR ID(0 to exit): ");
    while(1)
    {
        textcolor(WHITE);
        scanf("%d",&choice);
        if(choice==0)
        {
            fclose(fp);
            return choice;
        }
        rewind(fp);
        flag=0;
        while(fread(&C,sizeof(C),1,fp)==1)
        {
            if(C.car_id==choice && C.car_count>0)
            {
                    flag=1;
                    fclose(fp);
                    return choice;
            }
        }
        if(flag==0)
        {
            gotoxy(54,row_no+6);
            textcolor(RED);
            printf("INVALID CHOICE!!");
            getch();
            gotoxy(52,row_no+6);
            printf("\t\t\t\t\t");
            gotoxy(85,row_no+3);
            printf("\t");
            gotoxy(85,row_no+3);
        }
    }
    fclose(fp);
    getch();
}

int isValidDate(struct tm cust)
{

    int dd,mm,yy;
    struct tm dt;
    time(&dt);
    struct tm *now=localtime(&dt);

    now->tm_mon=now->tm_mon+1;
    now->tm_year=now->tm_year+1900;

    dd=cust.tm_mday;
    mm=cust.tm_mon;
    yy=cust.tm_year;
///Checking date Syntactically

//Checking For year
if(yy>=now->tm_year && yy<=now->tm_year+1)
{
    //Checking For Month
    if(mm>=1 && mm<=12)
    {
        //Checking For Days
        if(dd>0 && dd<=31)
        {
            if( (mm==4 || mm==6 || mm==9 || mm==11) && dd>30)
            {
                return 0;
            }
            else if(mm==2)
            {
                if( yy%4!=0  && dd>28 )
                      return 0;
            }
        }
        else
            return 0;
    }
    else
        return 0;
}
else
{
    return 0;
}

///Checking date Logically

    if(yy > now->tm_year)
        return 1;
    else
    {
        if( mm > now->tm_mon)
            return 1;
        else if( mm == now->tm_mon && dd >= now->tm_mday)
            return 1;
    }

    return 0;
}

void updateCarCount(int id)
{
    FILE *fp;
    Car C;
    fp=fopen("car.bin","rb+");
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id == id)
        {
            fseek(fp,(signed int)-(sizeof(C)),SEEK_CUR);
            C.car_count--;
            fwrite(&C,sizeof(C),1,fp);
            break;
        }
    }
    fclose(fp);
}

void bookedCarDetails(int C_id)
{
    int i;
    clrscr();
    Customer_Car_Details cust;
    FILE *fp;
    fp=fopen("customer.bin","rb");
    if(fp==NULL)
    {
        textcolor(YELLOW);
        printf("NO BOOKED CAR !!");
        getch();
        return;
    }
    textcolor(YELLOW);
    gotoxy(54,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(52,5);
    printf("* BOOKED CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    printf(" Model");
    gotoxy(20,8);
    printf("Cust Name");
    gotoxy(40,8);
    printf("Pick From");
    gotoxy(65,8);
    printf("Drop point");
    gotoxy(90,8);
    printf("S_date");
    gotoxy(106,8);
    printf("E_Date\n");

    for(i=1;i<=120;i++)
        printf("%c",247);
    i=10;
    textcolor(YELLOW);
    while(fread(&cust,sizeof(cust),1,fp)==1)
    {
            printf(" %s",getCarName(cust.car_id));
            gotoxy(20,i);
            printf("%s",cust.cust_name);
            gotoxy(40,i);
            printf("%s",cust.pick);
            gotoxy(65,i);
            printf("%s",cust.drop);
            gotoxy(90,i);
            printf("%d/%d/%d",cust.sd.tm_mday,cust.sd.tm_mon,cust.sd.tm_year);
            gotoxy(106,i);
            printf("%d/%d/%d\n",cust.ed.tm_mday,cust.ed.tm_mon,cust.ed.tm_year);
            i++;
    }
    getch();
    fclose(fp);
}

char* getCarName(int id)
{
    FILE *fp;
    static Car C;
    fp=fopen("car.bin","rb");
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id == id)
        {
            fclose(fp);
            return C.car_name;
        }
    }
    printf("EHILW ENd");
    getch();
    fclose(fp);
    return NULL;
}

void availCarDetails()
{
    int i;
    Car car;;
    FILE *fp;
    fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("NO CAR AVAILABLE !!!!");
        getch();
        return;
    }
    textcolor(YELLOW);
    gotoxy(54,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(54,5);
    printf("* CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
        printf("%c",247);
    printf(" Car ID");
    gotoxy(10,8);
    printf("Car Name");
    gotoxy(48,8);
    printf("Capacity");
    gotoxy(72,8);
    printf("Count");
    gotoxy(96,8);
    printf("Rent Per day\n");
    for(i=1;i<=120;i++)
        printf("%c",247);
    i=10;
    while(fread(&car,sizeof(car),1,fp)==1)
    {
        if(car.car_count>0)
        {
            printf(" %d",car.car_id);
            gotoxy(10,i);
            printf("%s",car.car_name);
            gotoxy(48,i);
            printf("%d",car.capacity);
            gotoxy(72,i);
            printf("%d",car.car_count);
            gotoxy(96,i);
            printf("%d\n",car.price);
            i++;
        }
    }
    getch();
    fclose(fp);
}

void carReturn()
{
    FILE *fp;
    int res;
    Customer_Car_Details cust;
    fp=fopen("customer.bin","rb");
    if(fp==NULL)
    {
        return;
    }

    struct tm dt,*now;
    time(&dt);

    now=localtime(&dt);
    now->tm_mon=now->tm_mon+1;
    now->tm_year=now->tm_year+1900;

    while(fread(&cust,sizeof(cust),1,fp)==1)
    {
        if(cust.ed.tm_mday==now->tm_mday && cust.ed.tm_mon==now->tm_mon && cust.ed.tm_year==now->tm_year)
        {
            res=deleteCust(cust);
            if(res==1)
                updateCarCount2(cust.car_id);
        }
    }
    fclose(fp);
}

void updateCarCount2(int id)
{
    FILE *fp;
    Car C;
    fp=fopen("car.bin","rb+");
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id == id)
        {
            fseek(fp,(signed int)-(sizeof(C)),SEEK_CUR);
            C.car_count++;
            fwrite(&C,sizeof(C),1,fp);
            break;
        }
    }
    fclose(fp);
}

int deleteCust(Customer_Car_Details cust)
{
    int flag=0;
    Customer_Car_Details cust2;
    FILE *fp=fopen("customer.bin","rb+");
    if(fp==NULL)
        return 0;
    FILE *fp2=fopen("temp.bin","wb+");
    if(fp==NULL)
        return 0;

    while(fread(&cust2,sizeof(cust2),1,fp)==1)
    {
        if(strcmp(cust.cust_name,cust2.cust_name)==0 && strcmp(cust.pick,cust2.pick)==0 && strcmp(cust.drop,cust2.drop)==0 && cust.car_id==cust2.car_id && cust.sd.tm_mday==cust2.sd.tm_mday && cust.sd.tm_mon==cust2.sd.tm_mon && cust.sd.tm_year==cust2.sd.tm_year && cust.ed.tm_mday==cust2.ed.tm_mday && cust.ed.tm_mon==cust2.ed.tm_mon && cust.ed.tm_year==cust2.ed.tm_year)
        {
            flag=1;
            continue;
        }
        else
        {
            fwrite(&cust2,sizeof(cust2),1,fp2);
        }
    }
    fclose(fp);
    fclose(fp2);

    if(flag==0)
    {
        return 0;
    }
    fp=fopen("customer.bin","wb+");
    fp2=fopen("temp.bin","rb");
    while(fread(&cust2,sizeof(cust2),1,fp2)==1)
    {
        fwrite(&cust2,sizeof(cust2),1,fp);
    }
    return 1;
    fclose(fp);
    fclose(fp2);
}





