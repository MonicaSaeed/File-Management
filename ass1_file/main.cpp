#include <iostream>
#include <fstream>

using namespace std;
/*long BinarySearch(fstream f, string ID)
{
    int _Id = stoi(ID); // type of explicit type casting

}*/

void addEmployees(string fileName,string EID, string DID, string EName, string EPosition)
{
    fstream f(fileName.c_str()); //opens file
    int recordLength = EID.size()+DID.size()+EName.size()+EPosition.size()+4;
    if( f.is_open() )
    {
        char indicator[3];
        if(recordLength < 100 && recordLength > 9)
        {
            //f<<std::string(temp)<<std::string(recordLength);
            indicator[0]='0';
            indicator[1]=recordLength%10;
            indicator[2]=recordLength%100-indicator[1];
            cout<<recordLength%10<<endl;

        }
        else if(recordLength<10)
        {
            //f<<temp<<temp<<recordLength;
            indicator[0]='0';
            indicator[1]='0';
            int i=recordLength%10;
            indicator[2] = static_cast<char>(i);
        }
        else
        {
            //f<<recordLength;
            indicator[2] = (char)recordLength%10;
            indicator[1] = (char)(recordLength%100-indicator[2]);
            indicator[0] = (char)(recordLength%1000-indicator[1]-indicator[2]);
        }
        for(int i=0 ;i<3;i++){
            f<<indicator[i];
        }
        f<<EID<<"$"<<DID<<"$"<<EName<<"$"<<EPosition<<"$";
    }
}


int main() {

    fstream Employees,Department;
    Employees.open("Employees.txt", ios::out | ios::trunc );
    Department.open("Department",ios::in | ios::out);

    addEmployees("Employees.txt","2","i","m","s");

}


