//
//This program was completely implemented by me
/* Hospital 
*
* Desc:
* This is a project for the Programmming 2 course at Tampere University 
* This program contains multiple class, modules, and files 
* This program simulates a Hospital where patient can be admitted, medicine can be assigned, care givers can be appointed and assigned
* All the class interact with each other to make this program work. I implemented the careperiod, hospital class for the most part.
*
* Program author
* Name: Shamsur Raza Chowdhury
* Student number: 050359798
* UserID: rvshch 
* E-Mail: shamsurraza.chowdhury@tuni.fi
* */

#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";

int main()
{
    Hospital *hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while (cli.exec())
    {
    }

    delete hospital;
    return EXIT_SUCCESS;
}
