#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <time.h>
struct User{
    char userid[20];//for storing userid
    char pwd[20];//for storing password
    char name[20];//for storing name
};
struct Car{
    int car_id;//for storing car id
    char car_name[50];//for storing car name of size 50
    int capacity;//for storing capacity of car
    int car_count;//for storing no. Of cars
    int price;//for storing rental price
};
struct Customer_Car_Details{
    int car_id;//for storing car id
    char cust_name[30];//for storing car name of size 30
    char pick[30];//for storing car pickup location of size 30
    char drop[30];//for storing car drop location of size 30
    struct tm sd;//for storing starting date
    struct tm ed;//for storing ending date
};
typedef struct User User;
typedef struct Car Car;
typedef struct Customer_Car_Details Customer_Car_Details;

void addAdmin();
User* getInput();//For accepting || storing Userid and password
int checkUserExist(User,char *);//For validating userid and password which is inputted by user.
int adminMenu();//Serve the options for Admin to perform task(s)
void addEmployee();//Admin_s Option 1
void viewEmployee();//Admin_s Option 2
void addCarDetails();//Admin_s Option 3
void showCarDetails();//Admin_s Option 4
int deleteEmp();//Admin_s Option 5
int deleteCarModel();//Admin_s Option 6

int empMenu();//Serve the options for Emp to perform task(s)
int rentCar();
int selectCarModel();
int isValidDate(struct tm);
void updateCarCount(int);
void bookedCarDetails();
char* getCarName(int);
void availCarDetails();
void carReturn();

void updateCarCount2(int);
int deleteCust(Customer_Car_Details);
#endif // CAR_H_INCLUDED
