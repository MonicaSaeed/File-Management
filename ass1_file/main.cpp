#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include<bits/stdc++.h>

using namespace std;

void addEmployees(fstream &fileName,fstream &f2,fstream &f3,string EID, string DID, string EName, string EPosition);
int totalRecordsSize=0;
void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li);
int findEmployeeWithID(fstream &EPrimaryIndex, string id);
void deleteEmployee(fstream &Employee,fstream &EPrimaryIndex, string employeeID);
void addESecondaryIndex(fstream &ESecondaryIndex,fstream &ESecondaryData, string depId,string id);
vector <pair<string,int>>v(0);
void sortPrimaryIndex(fstream &EPrimaryIndex);
void deletePrimaryIndex(fstream &EPrimaryIndex,string id);
vector <pair<string,int>>EmpSecondaryIndex(0);
void sortSecondaryIndex(fstream& ESecondaryIndex);


int main()
{
    int listHeader=-1;
    fstream Employees,Department,EPrimaryIndex,ESecondaryIndex;
    Employees.open("Employees.txt", ios::out | ios::in | ios::app);
    Department.open("Department.txt",ios::in | ios::out| ios::app);
    EPrimaryIndex.open("EPrimaryIndex.txt",ios::in | ios::out| ios::app);
    ESecondaryIndex.open("ESecondaryIndex.txt", ios::in | ios::out|ios::app);
    ESecondaryData.open("ESecondaryData.txt",ios::in | ios::out | ios::app);
    Employees<<"00000000-1";
    addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"2","i","m","s");
    addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"30","is","monica","student");
    //addEmployees(Employees,EPrimaryIndex,"25","mirette","ai","studenttt");
   // deleteEmployee(Employees,EPrimaryIndex,"2");
    addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"25","ai","mirette","studenttt");
    //deleteEmployee(Employees,EPrimaryIndex,"30");
    // pair<int,int> p= printEmployee(EPrimaryIndex,"30");
    // cout<<p.first<<" "<<p.second<<endl;

    return 0;
}

void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li)
{
    EPrimaryIndex.seekp(0,ios::end);
    EPrimaryIndex<<li<<'&'<<id<<endl;
    sortPrimaryIndex(EPrimaryIndex);
    //totalRecordsSize+=li;

}
void addESecondaryIndex(fstream &ESecondaryIndex,fstream &ESecondaryData, string depId,string id)
{
    ESecondaryIndex.seekp(0,ios::end);
    ESecondaryIndex<<depId<<'&'<<id<<endl;
}

void sortPrimaryIndex(fstream &EPrimaryIndex){
    EPrimaryIndex.seekg(0,ios::beg);

    while(!EPrimaryIndex.eof())
    {
        string Sbo,SID;
        getline(EPrimaryIndex,Sbo,'&');
        getline(EPrimaryIndex,SID);
        if(Sbo=="" || SID=="")break;
        pair<string,int> p(SID,stoi(Sbo));
        v.push_back(p);
    }
    sort(v.begin(),v.end());
    EPrimaryIndex.close();
    EPrimaryIndex.open("EPrimaryIndex.txt", ios::in | ios::out |ios::ate);
    if(EPrimaryIndex.is_open())
    {
        EPrimaryIndex.seekp(0,ios::beg);
        for(int i=0;i<v.size();i++)
        {
            EPrimaryIndex<<v[i].first<<'&'<<v[i].second<<endl;
        }
    }
}

void deletePrimaryIndex(fstream &EPrimaryIndex,string id)
{
    vector <pair<string,int>>v2(v); //v carries the primary index
    v.clear();

    for(int i=v2.size();i<0;i--){
        if(v2[i].first != id){
            v.push_back(v2[i]);
        }
    }

    sortPrimaryIndex(EPrimaryIndex);

}
//first int is the byte offset in employee file and second int is the byte offset in primary key file
int findEmployeeWithID(fstream &EPrimaryIndex,string id)
{
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
        return -1;
    }

}

void addEmployees(fstream &fileName,fstream &f2,fstream &f3, string EID, string DID, string EName, string EPosition)
{
    //fileName.open("Employees.txt", ios::out | ios::in);
    if(fileName.is_open())
    {
    int recordLength = EID.size()+DID.size()+EName.size()+EPosition.size()+4;
    int firstBO;
    fileName.seekg(0,ios::beg);
    string h;
    char temp;
    for(int i=0; i<10; i++)
    {
        fileName>>temp;
        h+=temp;
    }
    cout<<h<<endl<<fileName.tellg()<<endl;
    stringstream transH(h);
    int findDeletRecord=0 ;
    transH>>findDeletRecord;
    cout<<"\\\\\\\\\\\\\\\\"<<findDeletRecord<<endl;
    //int findDeletRecord = stoi(h);
    if(findDeletRecord==0)
    {
        findDeletRecord=-1;
    }
    cout<<"\\\\\\\\\\\\\\\\"<<findDeletRecord<<endl;
    if(findDeletRecord!=-1)
    {
        while(findDeletRecord!=-1) /////////////////////////////////////////////////////aaaaaaaaaaaaaaaaaaaaaaaaah
        {
            cout<<"firsttt"<<endl;
            fileName.seekg(findDeletRecord+1,ios::beg);
            cout<<"\\\\\\\\\\\\\\"<<fileName.tellg()<<endl;
            char tmp;
            string SDR;
            fileName>>tmp;
            while(tmp!='|')
            {
                SDR+=tmp;
                fileName>>tmp;
            }
            stringstream transSDR(SDR);
            int sizeDeletedRecod=0 ;
            transSDR>>sizeDeletedRecod;
            cout<<"\\\\\\\\\\\\\\"<<SDR<<endl;
            cout<<"\\\\\\\\\\\\\\"<<sizeDeletedRecod<<endl;
            cout<<"\\\\\\\\\\\\\\"<<endl;
            //int sizeDeletedRecod = intSDR);

            if(recordLength <= sizeDeletedRecod)
            {
                cout<<"\\\\\\\\\\\\\\"<<recordLength<<endl;
                //cout<<"\\\\\\\\\\\\\\"<<fileName.tellg()<<endl;
                fileName.seekp(findDeletRecord,ios::beg);
                fileName << setfill ('0') << setw (3);
                fileName << recordLength ;
                fileName<<EID<<"$"<<DID<<"$"<<EName<<"$"<<EPosition<<"$";
                findDeletRecord=-1;
                addEPrimaryIndex(f2,EID,firstBO);
                break;
            }

            else
            {
                cout<<"second"<<endl;

                fileName.seekg(1,ios::cur);
                cout<<fileName.get()<<endl;
                char tmp2;
                string nextBO;
                fileName>>tmp2;
                while(tmp!='|')
                {
                    nextBO+=tmp2;
                    fileName>>tmp2;
                }
                stringstream transnextBO(nextBO);
                int findDeletRecord = 0;
                transnextBO>>findDeletRecord;

            }
        }
    }
    else
    {
    cout<<"blaa"<<endl;
    fileName.seekp(0,ios::end);
    firstBO=fileName.tellp();
    fileName << setfill ('0') << setw (3);
    fileName << recordLength ;
    fileName<<EID<<"$"<<DID<<"$"<<EName<<"$"<<EPosition<<"$";
    //fileName.close();
    }

    addEPrimaryIndex(f2,EID,firstBO);
    addESecondaryIndex(f3,DID,EID);
    }
}
void deleteEmployee(fstream &Employee,fstream &EPrimaryIndex, string employeeID)
{
    Employee.close();
    Employee.open("Employees.txt", ios::in | ios::out |ios::ate);
    if(Employee.is_open())
    {
        int deleteBO=findEmployeeWithID(EPrimaryIndex,employeeID);
        Employee.seekg(deleteBO,ios::beg);
        cout<<Employee.tellg()<<endl;
        string deletedRlength;
        char temp;
        for(int i=0; i<3; i++)
        {
            Employee>>temp;
            deletedRlength+=temp;
        }
        Employee.seekg(0, ios::beg);
        string previousHeader;
        char temp2;
        for(int i=0; i<10; i++)
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
        if(intPH==0)
        {
            intPH=-1;
        }
        cout<<'*'<<intDRL<<'|'<<intPH<<'|'<<endl;
        Employee<<'*'<<intDRL+3<<'|'<<intPH<<'|'; //+3 byte for byte offset(000)
        Employee.seekp(0,ios::beg);
        Employee << setfill ('0') << setw (10);
        Employee << deleteBO;
        Employee.close();

    }
    //Employee.open("Employee.txt", ios::in |ios::out|ios::app);
}

void sortSecondaryIndex(fstream& ESecondaryIndex)
{
    ESecondaryIndex.seekg(0,ios::beg);

    while(!ESecondaryIndex.eof())
    {
        string DID,SID;
        getline(ESecondaryIndex,DID,'&');
        getline(ESecondaryIndex,SID);
        if(DID=="" || SID=="")break;
        pair<string,string> p(DID,DID);
        EmpSecondaryIndex.push_back(p);
    }

    sort(v.begin(),v.end());

}
