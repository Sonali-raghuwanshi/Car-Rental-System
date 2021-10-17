//123//30
#include <stdio.h>
#include "conio2.h"
#include "car.h"
int main()
{
    int i;
    int ch,choice;
    int k;
    int done;
    int check_emp=0;
    int flag=0;
    addAdmin();
    User *usr;
    clrscr();
    gotoxy(47,13);
    textcolor(YELLOW);
    printf("WELCOME TO CAR RENTAL SYSTEM");
    gotoxy(42,16);
    textcolor(GREEN);
    printf("* RENT A CAR AND GO WHEREVER YOU NEED *");
    getch();

    while(1)
    {
        clrscr();
        textcolor(RED);
        gotoxy(54,2);
        printf("CAR RENTAL SYSTEM");
        textcolor(YELLOW);
        gotoxy(1,10);
           for(i=1;i<=120;i++)
             printf("*");
        gotoxy(1,20);
           for(i=1;i<=120;i++)
             printf("*");
        textcolor(YELLOW);
        gotoxy(54,12);
          printf("1. ADMIN");
        gotoxy(54,14);
          printf("2. EMPLOYEE");
        gotoxy(54,16);
          printf("3. QUIT");
        gotoxy(54,18);
        textcolor(WHITE);
        printf("SELECT YOUR ROLE: ");

        do{
            scanf("%d",&ch);


            if(ch==1)///ADMIN
            {
                do{

                     usr=getInput();
                     flag=0;
                     if(usr!=NULL)
                     {
                         k=checkUserExist(*usr,"admin");
                     }
                     else
                     {
                         flag=1;
                         break;
                     }
                  }while(k==0);
                  if(k==-1  || flag==1)
                  {
                      break;
                  }

                  if(k==1)//ADMIN MENU
                  {
                      while(1)
                      {
                          clrscr();
                          choice=adminMenu();
                          if(choice==7)
                            break;

                          switch(choice)
                          {
                            case 1:
                                clrscr();
                                addEmployee();
                                break;
                            case 2:
                                clrscr();
                                addCarDetails();
                                break;
                            case 3:
                                clrscr();
                                viewEmployee();
                                break;
                            case 4:
                                clrscr();
                                showCarDetails();
                                break;
                            case 5:
                                clrscr();
                                done=deleteEmp();
                                if(done==1)
                                {
                                    textcolor(LIGHTGREEN);
                                    gotoxy(40,17);
                                    printf("EMPLOYE RECORD DELETED, PRESS ANY KEY TO CONTINUE...");
                                }
                                else{
                                    textcolor(LIGHTRED);
                                    gotoxy(40,17);
                                    printf("NO SUCH EMPLOYEE PRESENT, PRESS ANY KEY TO CONTINUE...");
                                }
                                getch();
                                break;
                            case 6:
                                clrscr();
                                done=deleteCarModel();
                                if(done==1)
                                {
                                    textcolor(LIGHTGREEN);
                                    gotoxy(40,17);
                                    printf("CAR MODEL DELETED, PRESS ANY KEY TO CONTINUE...");
                                }
                                else{
                                    textcolor(LIGHTRED);
                                    gotoxy(40,17);
                                    printf("NO SUCH CAR ID PRESENT, PRESS ANY KEY TO CONTINUE...");
                                }
                                getch();
                                break;
                            default:
                                textcolor(RED);
                                gotoxy(54,20);
                                printf("INVALID CHOICE !");
                                getch();
                          }
                     }
                  }
            }
            else if(ch==2)///EMPLOYEE
            {
                do{
                     FILE *fp=fopen("emp.bin","rb");
                     check_emp=0;
                     if(fp==NULL)
                     {
                        gotoxy(54,22);
                        textcolor(RED);
                        printf("FIRST ADD EMPLOYEE'S FROM ADMIN's MENU !!");
                        getch();
                        check_emp=1;
                        break;
                     }

                     usr=getInput();
                     flag=0;
                     if(usr!=NULL)
                     {
                         k=checkUserExist(*usr,"emp");
                     }
                     else
                     {
                         flag=1;
                         break;
                     }
                  }while(k==0);

                  if(k==-1  || flag==1 || check_emp==1)
                  {
                      break;
                  }

                    while(1)
                        {
                            clrscr();
                            choice=empMenu();
                            if(choice==5)
                                break;

                            switch(choice)
                            {
                                case 1:
                                    clrscr();
                                    int res;
                                    res=rentCar();
                                    if(res==-2)
                                    {
                                        gotoxy(50,15);
                                        textcolor(LIGHTCYAN);
                                        printf("SORRY ALL CAR's ARE BOOKED");
                                        getch();
                                    }
                                    else if(res==0)
                                    {
                                        clrscr();
                                        gotoxy(46,15);
                                        textcolor(LIGHTRED);
                                        printf("# YOU DID NOT CHOOSE ANY CAR #");
                                        getch();
                                    }
                                    break;
                                case 2:
                                    clrscr();
                                    bookedCarDetails();
                                    break;
                                case 3:
                                    clrscr();
                                    availCarDetails();
                                    break;
                                case 4:
                                    clrscr();
                                    showCarDetails();
                                    break;
                                case 5:
                                    clrscr();
                                    getch();
                                    break;
                                default:
                                    textcolor(RED);
                                    gotoxy(54,20);
                                    printf("INVALID CHOICE !");
                                    getch();
                            }
                        }
            }
            else if(ch==3)///EXIT
            {
                clrscr();
                textcolor(GREEN);
                gotoxy(45,15);
                printf("THANK YOU FOR USING OUR APP !!");
                getch();
                return 0;
            }
            else///INVALID USER
            {
                gotoxy(54,22);
                textcolor(RED);
                printf("INVALID USER TYPE !!");
                getch();
                gotoxy(54,22);
                printf("\t\t\t\t");
                gotoxy(72,18);
                printf("\t\t");
                gotoxy(72,18);
            }


        if(choice==7 || choice==5)
            break;
        }while(1);

    }
    carReturn();
    getch();
    return 0;
}
