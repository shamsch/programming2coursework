#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <map>
#include <algorithm>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for (std::map<std::string, Person *>::iterator
             iter = staff_.begin();
         iter != staff_.end();
         ++iter)
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for(auto patient: all_patients_){
        delete patient.second;
    }

    for(auto carePeriods: carePeriods_){
        delete carePeriods;
    }
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if (staff_.find(specialist_id) != staff_.end())
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person *new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    std::string nameOfthePatient = params.at(0);
    //situation where the patient is already in the hospital
    if (current_patients_.find(nameOfthePatient) != current_patients_.end())
    {
        std::cout << ALREADY_EXISTS << nameOfthePatient << std::endl;
        return;
    }
    //declaring new Person and CarePeriod
    Person *new_patient = new Person(nameOfthePatient);
    CarePeriod *carePeriod = new CarePeriod(utils::today, new_patient);
    carePeriods_.push_back(carePeriod);
    current_patients_.insert({nameOfthePatient, new_patient});
    all_patients_.insert({nameOfthePatient, new_patient});
    std::cout << PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
{
    //check if it is in current_patient_
    //remove from there
    //given an end date to the patient
    std::string nameOfthePatient = params.at(0);
    if (current_patients_.find(nameOfthePatient) != current_patients_.end())
    {
        current_patients_.erase(nameOfthePatient);
        for (auto element : carePeriods_)
        {
            if (nameOfthePatient == element->returnNameOfThePatient())
            {
                element->setEndDate();
            }
        }
        std::cout << PATIENT_LEFT << std::endl;
    }
    //if not found give error
    else
    {
        std::cout << CANT_FIND << nameOfthePatient << std::endl;
    }
}

void Hospital::assign_staff(Params params)
{
    //check if the caregiver and patient are in their respective list
    std::string careGiver = params.at(0);
    std::string patient = params.at(1);
    if (staff_.find(careGiver) != staff_.end())
    {
        if (current_patients_.find(patient) != current_patients_.end())
        {
            for (auto element : carePeriods_)
            {
                if (patient == element->returnNameOfThePatient())
                {
                    //assign the caregiver
                    element->addCareGiver(staff_[careGiver]);
                    std::cout << STAFF_ASSIGNED << patient << std::endl;
                    //also adding the patient in staff/caregivers map
                    if (staffAssignments.find(staff_[careGiver]) != staffAssignments.end())
                    {
                        staffAssignments[staff_[careGiver]].push_back(element);
                    }
                    else
                    {
                        std::vector<CarePeriod *> temp;
                        temp.push_back(element);
                        staffAssignments.insert({staff_[careGiver], temp});
                    }
                }
            }
        }
        else
        {
            std::cout << CANT_FIND << patient << std::endl;
        }
    }
    else
    {
        std::cout << CANT_FIND << careGiver << std::endl;
    }
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if (not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true))
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person *>::const_iterator
        patient_iter = current_patients_.find(patient);
    if (patient_iter == current_patients_.end())
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
    //adding the medicine in list of medicine and recording the user of that particular drug
    if (medcinesInUse.find(medicine) != medcinesInUse.end())
    {
        medcinesInUse[medicine].push_back(patient);
    }
    else
    {
        std::vector<std::string> temp;
        temp.push_back(patient);
        medcinesInUse.insert({medicine, temp});
    }
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person *>::const_iterator
        patient_iter = current_patients_.find(patient);
    if (patient_iter == current_patients_.end())
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
    //removing the patient from the medcine use
    int index = 0;
    for (auto element : medcinesInUse[medicine])
    {
        if (patient == element)
        {
            medcinesInUse[medicine].erase(medcinesInUse[medicine].begin() + index);
        }
        index++;
    }
    //when no one is using that medicine anymore
    if (medcinesInUse[medicine].size() < 1)
    {
        medcinesInUse.erase(medicine);
    }
}

void Hospital::print_patient_info(Params params)
{
    std::string patient = params.at(0);
    //print the careperiod
    if (current_patients_.find(patient) != current_patients_.end())
    {
        for (auto element : carePeriods_)
        {
            if (patient == element->returnNameOfThePatient())
            {
                std::cout << "* Care period: ";
                element->printCarePeriod();
                std::cout << std::endl;
                //print care givers
                element->printCareGivers();
                std::cout << std::endl;
            }
        }
        //print drugs
        std::cout << "* Medicines:";
        all_patients_[patient]->print_medicines("  - ");
    }
    else
    {
        std::cout << CANT_FIND << patient << std::endl;
    }
}

void Hospital::print_care_periods_per_staff(Params params)
{
    std::string nameOfTheStaff = params.at(0);
    if (staff_.find(nameOfTheStaff) != staff_.end())
    {
        if (staffAssignments.count(staff_[nameOfTheStaff]))
        {
            //has assignments
            for (auto element : staffAssignments[staff_[nameOfTheStaff]])
            {
                element->printCarePeriod();
                std::cout << "\n* Patient: " << element->returnNameOfThePatient() << std::endl;
            }
        }
        else
        {
            //does not have any assignment
            std::cout << "None" << std::endl;
        }
    }
    else
    {
        std::cout << CANT_FIND << nameOfTheStaff << std::endl;
    }
}

void Hospital::print_all_medicines(Params)
{
    if (medcinesInUse.size())
    {
        //if there is any drug
        for (auto element : medcinesInUse)
        {
            std::cout << element.first << " prescribed for" << std::endl;
            //sorting patient vector
            std::sort(element.second.begin(), element.second.end());
            for (auto patient : element.second)
            {
                std::cout << "- " << patient << std::endl;
            }
        }
    }
    else
    {
        //if no drug in use
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_all_staff(Params)
{
    if (staff_.empty())
    {
        std::cout << "None" << std::endl;
        return;
    }
    for (std::map<std::string, Person *>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter)
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
    if (all_patients_.empty())
    {
        std::cout << "None" << std::endl;
    }
    else
    {
        for (auto patient : all_patients_)
        {
            //print name of the patient
            std::cout<<patient.first<<std::endl;
            for (auto element : carePeriods_)
            {
                if (patient.first == element->returnNameOfThePatient())
                {
                    std::cout << "* Care period: ";
                    element->printCarePeriod();
                    std::cout << std::endl;
                    //print care givers
                    element->printCareGivers();
                    std::cout << std::endl;
                }
            }
            //print drugs
            std::cout << "* Medicines:";
            patient.second->print_medicines("  - ");
        }
    }
}

void Hospital::print_current_patients(Params)
{
    if (current_patients_.empty())
    {
        std::cout << "None" << std::endl;
    }
    else
    {
        for (auto patient : current_patients_)
        {
            //print name of the patient
            std::cout<<patient.first<<std::endl;
            for (auto element : carePeriods_)
            {
                if (patient.first == element->returnNameOfThePatient())
                {
                    std::cout << "* Care period: ";
                    element->printCarePeriod();
                    std::cout << std::endl;
                    //print care givers
                    element->printCareGivers();
                    std::cout << std::endl;
                }
            }
            //print drugs
            std::cout << "* Medicines:";
            all_patients_[patient.first]->print_medicines("  - ");
        }
    }
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if (not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false))
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if (not utils::is_numeric(amount, true))
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
