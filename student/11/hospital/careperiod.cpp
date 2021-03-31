#include "careperiod.hh"
#include "utils.hh"
#include <iostream>
#include <string>
#include <algorithm>

CarePeriod::CarePeriod(const std::string &start, Person *patient) : patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person *patient) : patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::setEndDate()
{
    end_ = utils::today;
    endPeriodExist = true;
}

void CarePeriod::setStartDate()
{
    start_ = utils::today;
}

std::string CarePeriod::returnNameOfThePatient()
{
    return patient_->get_id();
}

void CarePeriod::addCareGiver(Person *careGiver)
{
    //adding only unique care giver person
    if (std::find(careGivers.begin(), careGivers.end(), careGiver) == careGivers.end())
    {
        careGivers.insert(careGivers.begin(), careGiver);
    }
}
void CarePeriod::printCareGivers()
{
    std::cout << "  - Staff:";
    if (!careGivers.size())
    {
        std::cout << " None";
    }
    else
    {
        for (auto staff : careGivers)
        {
            std::cout << " " << staff->get_id();
        }
    }
}

void CarePeriod::printCarePeriod()
{
    start_.print();
    std::cout << " - ";
    if (endPeriodExist)
    {
        end_.print();
    }
}

Person *CarePeriod::returnThePerson()
{
    return patient_;
}