#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
/*long BinarySearch(fstream f, string ID)
{
    int _Id = stoi(ID); // type of explicit type casting

}*/

void addEmployees(fstream &fileName,string EID, string DID, string EName, string EPosition)
{
    //fstream f(fileName.c_str(),ios::app); //opens file
    int recordLength = EID.size()+DID.size()+EName.size()+EPosition.size()+4;
    if( fileName.is_open() )
    {
        cout << setfill ('0') << setw (3);
        cout << recordLength << endl;

        fileName << setfill ('0') << setw (3);
        fileName << recordLength ;


        /*int temp=0,temp2;
        int indicator[3];
        if(recordLength < 100 && recordLength > 9)
        {
            f<<temp;
            f<<recordLength;
            /*indicator[0]='0';
            indicator[1]=recordLength%10;
            indicator[2]=recordLength%100-indicator[1];
            cout<<recordLength%10<<endl;*//*

        }
        else if(recordLength<10)
        {
            temp2=(int)recordLength;
            f<<temp<<temp<<recordLength;
            /*indicator[0]='0';
            indicator[1]='0';
            int i=recordLength%10;
            indicator[2] = static_cast<char>(i);*//*
        }
        else
        {
            f<<recordLength;
            /*indicator[2] = (char)recordLength%10;
            indicator[1] = (char)(recordLength%100-indicator[2]);
            indicator[0] = (char)(recordLength%1000-indicator[1]-indicator[2]);*//*
        }
        for(int i=0 ; i<3; i++)
        {
            f<<indicator[i];
        }*/
        fileName<<EID<<"$"<<DID<<"$"<<EName<<"$"<<EPosition<<"$";
    }
}


int main()
{

    fstream Employees,Department;
    Employees.open("Employees.txt", ios::out | ios::in | ios::app);
    Department.open("Department",ios::in | ios::out| ios::app);

    addEmployees(Employees,"2","i","m","s");
    addEmployees(Employees,"30","monica","is","student");




    return 0;
}


