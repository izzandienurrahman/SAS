#include<stdio.h>
#include<stdlib.h>

/**
*@Author Izzan Dienurrahman
*@Since 3/7/2017
*@Version 1.0.0
*/

int i;
int parking[6]={1,2,3,4,5,6};

void successMsg(){
    printf("\nAccess granted. Use bike No : %d",findAvailableBike());
}

void tyMsg(){
    printf("\nAccess granted. Please return this bike to slot No: %d",findEmptyBike());
}

int findAvailableBike(){
    int i=0;
    while (parking[i]==0){
        i++;
    }
    return i;
}

int findEmptyBike(){
    int i=0;
    while (parking[i]!=0){
        i++;
    }
    return i;
}

int removeLocal(int x){
    parking[x]=0;
}

int addLocal(int x){
    parking[x]=x+1;
}

void borrowLocal(){
    i=findAvailableBike();
    removeLocal(i);
}

void returnLocal(){
    i=findEmptyBike();
    addLocal(i);
}

int main(){
    printf("\n\nList of available bike(s) : ");
    for(i=0;i<6;i++){
        printf("[%d] ",parking[i]);
    }

    printf("\nAvailable bike No: %d",findAvailableBike()+1);

borrowLocal();
successMsg();

    printf("\n\nList of available bike(s) : ");
    for(i=0;i<6;i++){
        printf("[%d] ",parking[i]);
    }
    printf("\nAvailable bike No: %d",findAvailableBike()+1);

borrowLocal();
successMsg();

    printf("\n\nList of available bike(s) : ");
    for(i=0;i<6;i++){
        printf("[%d] ",parking[i]);
    }
    printf("\nAvailable bike No: %d",findAvailableBike()+1);

    returnLocal();
    tyMsg();

    printf("\n\nList of available bike(s) : ");
    for(i=0;i<6;i++){
        printf("[%d] ",parking[i]);
    }
    printf("\nAvailable bike No: %d",findAvailableBike()+1);

}
