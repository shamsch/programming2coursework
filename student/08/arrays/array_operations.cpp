#include "array_operations.hh"
#include<iostream> 
#include<algorithm> 

int greatest_v1(int* itemptr, int size) {
    int max=*itemptr;
    int counter=0;
    while(counter<size){
        max=std::max(max, *itemptr);
        itemptr++;
        counter++;
    }
    return max;
}

int greatest_v2(int* itemptr, int* endptr) {
    int max=0;
    while(itemptr<endptr){
        max=std::max(max, *itemptr);
        itemptr++;
    }
    return max;
}

void copy(int* itemptr, int* endptr, int* targetptr) {
    while(itemptr<endptr){
        *targetptr=*itemptr;
        targetptr++;
        itemptr++;
    }
}

void reverse(int* leftptr, int* rightptr) {
    rightptr-=1;
    while(leftptr<rightptr){
        int leftVal=*leftptr;
        *leftptr=*rightptr;
        *rightptr=leftVal;
        ++leftptr;
        --rightptr;
    }
}