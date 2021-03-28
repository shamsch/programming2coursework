#include "careperiod.hh"
#include "utils.hh"
#include <iostream>
#include <string>

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