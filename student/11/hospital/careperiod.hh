/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include "utils.hh"
#include <string>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods

    //sets the end date of the careperiod to the parameter
    void setEndDate(Date &date);
    //returns the string name of the patient whose careperiod it is
    std::string returnNameOfThePatient();
    //adds a caregiver to the patient 
    void addCareGiver(Person* careGiver);
    //prints all the caregiver in the careperiod
    void printCareGivers();
    //prints the careperiods timeline
    void printCarePeriod();
    //returns the pointer of Person class whose care period it is 
    Person* returnThePerson();

private:
    Person* patient_;
    Date start_;
    Date end_;

    // More attributes and methods
    //contains all the caregiver
    std::vector<Person*> careGivers;
    //checks for whether the care period has an end date or not
    bool endPeriodExist=false;
};

#endif // CAREPERIOD_HH
