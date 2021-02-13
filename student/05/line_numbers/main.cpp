#include <iostream>
#include <fstream> 
#include <string>
 
using namespace std;
 
int main() {
    string filename = "";
    string outputFileName= "";
    cout << "Input file: ";
    getline(cin, filename);
    cout << "Output file: ";
    getline(cin, outputFileName);
 
    ifstream file_object(filename);
    ofstream outputFile_object(outputFileName);
    if ( not file_object ) {
        cout << "Error! The file "<< filename <<" cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string line;
        int lineCounter=1;
        while ( getline(file_object, line) ) {
           outputFile_object << lineCounter << " " << line << endl;
           lineCounter+=1;
        }
        file_object.close();
        outputFile_object.close();
    }

    return EXIT_SUCCESS;
}