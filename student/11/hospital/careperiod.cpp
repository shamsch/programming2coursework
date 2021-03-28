#include "careperiod.hh"
#include "utils.hh"
#include <iostream>
#include <string>
#include <algorithm>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::setEndDate(){
    end_= utils::today;
}

void CarePeriod::setStartDate(){
    start_= utils::today;
}

std::string CarePeriod::returnNameOfThePatient(){
    return patient_->get_id();
}

void CarePeriod::addCareGiver(Person* careGiver){
    //adding only unique care giver person
    if(std::find(careGivers.begin(), careGivers.end(), careGiver) == careGivers.end()){
        careGivers.push_back(careGiver);
    }
}