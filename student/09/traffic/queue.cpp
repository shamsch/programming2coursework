#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle) : cycle_(cycle)
{
}

Queue::~Queue()
{
    while (first_ != nullptr)
    {
        Vehicle *item_to_be_released = first_;
        first_ = first_->next;

        delete item_to_be_released;
    }
}

void Queue::enqueue(string reg)
{
    Vehicle *newCard = new Vehicle{reg, nullptr};

    if (first_ == nullptr)
    {
        first_ = newCard;
        last_ = newCard;
    }
    else
    {
        last_->next = newCard;
        last_ = newCard;
    }

    if(is_green_){
        dequeue(1);
    }
}

void Queue::switch_light()
{
    if(is_green_){
        is_green_=false;
        dequeue(cycle_);
    }
    else{
        is_green_=true;
        dequeue(cycle_);
    }
    
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_=cycle;
}

void Queue::print()
{
    if(first_==nullptr){
        std::cout<<lightStatus()<<": No vehicles waiting in traffic lights"<<std::endl;
    }
    else{
        std::cout<<lightStatus()<<": Vehicle(s) "<< listVehicle() <<" waiting in traffic lights"<<std::endl;
    }
    
}

void Queue::dequeue(int numberOfTimes)
{
    int counter=numberOfTimes;
    string removedCars="";
    while (counter)
    {
        if(first_==nullptr){
            break;
        }
        removedCars+=first_->reg_num+" ";
        first_=first_->next;    
        counter--;
    
    }

    if(removedCars==""){
        std::cout<<lightStatus()<<": No vehicles waiting in traffic lights"<<std::endl;
    }
    else{
        std::cout<<lightStatus()<<": Vehicle(s) "<<removedCars<<"can go on"<<std::endl;
        is_green_=false;
    }
}

std::string Queue::listVehicle(){
    int count=0;
    std::string rtrn="";

    Vehicle* top_=first_;
    while (top_!=nullptr)
    {
        if(count>0){
            rtrn+=" "+top_->reg_num;
        }
        else{
            rtrn=top_->reg_num;
        }
        count++;
        top_=top_->next;
    }
    return rtrn;
}

std::string Queue::lightStatus(){
    if(is_green_){
        return "GREEN";
    }
    else{
        return "RED";
    }
}