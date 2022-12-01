#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include<bits/stdc++.h>

using namespace std;

void addEmployees(fstream &fileName,fstream &f2,string EID, string DID, string EName, string EPosition);
int totalRecordsSize=0;
void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li);
pair<int,int> printEmployee(fstream &EPrimaryIndex, string id);
void deleteEmployee(fstream &Employee,fstream &EPrimaryIndex, string employeeID);


int main()
{
     int listHeader=-1;
    fstream Employees,Department,EPrimaryIndex;
    Employees.open("Employees.txt", ios::out | ios::in | ios::app);
    Department.open("Department.txt",ios::in | ios::out| ios::app);
    EPrimaryIndex.open("EPrimaryIndex.txt",ios::in | ios::out| ios::app);
    Employees<<"00000000-1";
    addEmployees(Employees,EPrimaryIndex,"2","i","m","s");
    addEmployees(Employees,EPrimaryIndex,"30","monica","is","student");
    addEmployees(Employees,EPrimaryIndex,"25","mirette","ai","studenttt");
    //deleteEmployee(Employees,EPrimaryIndex,"2");
    deleteEmployee(Employees,EPrimaryIndex,"30");
  // pair<int,int> p= printEmployee(EPrimaryIndex,"30");
  // cout<<p.first<<" "<<p.second<<endl;




    return 0;
}

void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li)
{
    EPrimaryIndex.seekp(0,ios::end);
    EPrimaryIndex<<li<<'&'<<id<<endl;
    //totalRecordsSize+=li;

}

//first int is the byte offset in employee file and second int is the byte offset in primarykey file
pair<int,int> printEmployee(fstream &EPrimaryIndex,string id){
    vector <pair<string,pair<int,int>>>v(0);
    EPrimaryIndex.seekg(0,ios::beg);
    int textStart =0;

    while(!EPrimaryIndex.eof()){
        string Sbo,SID;
        getline(EPrimaryIndex,Sbo,'&');
        getline(EPrimaryIndex,SID);
        if(Sbo=="" || SID=="")break;
        pair<int,int> p(stoi(Sbo),textStart);
        pair<string,pair<int,int>> p1(SID,p);
        v.push_back(p1);
        textStart ++;
    }

    sort(v.begin(),v.end());

    //binary search
    int start = 0;
    int end = (int)v.size()-1;
    int mid = (start+end)/2;
    while(start<=end)
    {
        if(v[mid].first==id)
        {
            return v[mid].second;
            break;
        }
        else if(v[mid].first<id)
        {
            start = mid+1;
        }
        else
        {
            end = mid-1;
        }
        mid = (start+end)/2;
    }
    if(start>end)
    {
        return {-1,-1};
    }

}

void addEmployees(fstream &fileName,fstream &f2,string EID, string DID, string EName, string EPosition)
{
   // fileName.open("Employees.txt", ios::out | ios::in | ios::ate);

        int recordLength = EID.size()+DID.size()+EName.size()+EPosition.size()+4;
        int firstBO;

        if( fileName.is_open() )
        {
            firstBO=fileName.tellp();
            fileName << setfill ('0') << setw (3);
            fileName << recordLength ;
            fileName<<EID<<"$"<<DID<<"$"<<EName<<"$"<<EPosition<<"$";

        }
        addEPrimaryIndex(f2,EID,firstBO);
        //fileName.close();
}
void deleteEmployee(fstream &Employee,fstream &EPrimaryIndex, string employeeID)
{
    Employee.close();
    Employee.open("Employees.txt", ios::in | ios::out);
    if(Employee.is_open())
    {
        pair<int,int>p=printEmployee(EPrimaryIndex,employeeID);
        int deleteBO=p.first;
        Employee.seekg(deleteBO,ios::beg);
        cout<<Employee.tellg()<<endl;
        string deletedRlength;
        char temp;
        for(int i=0;i<3;i++)
        {
            Employee>>temp;
            deletedRlength+=temp;
        }
        Employee.seekg(0, ios::beg);
        string previousHeader;
        char temp2;
        for(int i=0;i<10;i++)
        {
            Employee>>temp2;
            previousHeader+=temp2;
        }
        //Employee.close();
        //Employee.open("Employees.txt",ios::in);
        Employee.seekp(deleteBO);

        stringstream transDRL(deletedRlength), transPH(previousHeader);
        int intDRL=0 ;
        int intPH=0;
        transDRL>>intDRL ;
        transPH>>intPH;

        cout<<Employee.tellp()<<endl;
        if(intPH==0){intPH=-1;}
        cout<<'*'<<intDRL<<'|'<<intPH<<endl;
        Employee<<'*'<<intDRL+3<<'|'<<intPH; //+3 byte for byte offset(000)
        Employee.seekp(0,ios::beg);
        Employee << setfill ('0') << setw (10);
        Employee << deleteBO;
        Employee.close();
    }
}

