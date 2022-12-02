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
void SecondaryIndex(fstream &ESecondaryIndex,fstream &ESecondaryData, string depId,string id);
vector <pair<string,int>>v(0);
void sortPrimaryIndex(fstream &EPrimaryIndex);
void deletePrimaryIndex(fstream &EPrimaryIndex,string id);
vector <pair<string,int>>EmpSecondaryIndex(0); //DID , BO
vector <pair<int,pair<string,int>> >IDList(0); //BOfile, EID, pointer to second EID
void sortSecondaryIndex(fstream& ESecondaryIndex);
void printEmployee(fstream &EPrimaryIndex,fstream &Employees,string id);
void printEmployeeDepID(fstream &EPrimaryIndex, fstream &ESecondaryData, fstream &ESecondaryIndex, fstream &Employees,string DId);


int main()
{
    int listHeader=-1;
    fstream Employees,Department,EPrimaryIndex,ESecondaryIndex,ESecondaryData;
    Employees.open("Employees.txt", ios::out | ios::in | ios::app);
    Department.open("Department.txt",ios::in | ios::out| ios::app);
    EPrimaryIndex.open("EPrimaryIndex.txt",ios::in | ios::out| ios::app);
    ESecondaryIndex.open("ESecondaryIndex.txt", ios::in | ios::out|ios::app);
    ESecondaryData.open("ESecondaryData.txt",ios::in | ios::out | ios::app);
    Employees<<"00000000-1";
   // addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"2","i","m","s");
   // addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"30","is","monica","student");
    //addEmployees(Employees,EPrimaryIndex,"25","mirette","ai","studenttt");
   // deleteEmployee(Employees,EPrimaryIndex,"2");
   // addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"25","ai","mirette","studenttt");
    //deleteEmployee(Employees,EPrimaryIndex,"30");
    // pair<int,int> p= printEmployee(EPrimaryIndex,"30");
    // cout<<p.first<<" "<<p.second<<endl;
    int num;
    string EmpId,DepID,EmpName,EmpPosition;
    cin>>num;
    while(num=1)
    {
        cout<<"choose operation: "<<endl;

        if(num==1)
        {
            cout<<"enter employee's ID, departement ID ,Employees's name, and position"<<endl;
            cin>>EmpId>>DepID>>EmpName>>EmpPosition;
            addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,EmpId,DepID,EmpName,EmpPosition);
        }
      /*  else if(num==2)
        {

        }*/

    }

    /*cout<<"Enter a number
    switch(num)
    {
        case 1;
        addEmployees()
    }*/
    return 0;
}
void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li){
    EPrimaryIndex.seekp(0,ios::end);
    EPrimaryIndex<<li<<'&'<<id<<endl;
    sortPrimaryIndex(EPrimaryIndex);
    //totalRecordsSize+=li;

}
void SecondaryIndex(fstream &ESecondaryIndex,fstream &ESecondaryData, string depId,string id){
    bool findDepID = false;
    int position=0;
    if(!EmpSecondaryIndex.empty()){
        for(int i=0;i<EmpSecondaryIndex.size();i++){
            if(EmpSecondaryIndex[i].first==depId)
            {
                findDepID == true;
                position=i;
                break;
            }
        }
    }
    int IDlistBO= IDList.size()+1;
    if(findDepID==false)
    {
        pair<string,int>p(depId,IDlistBO);
        EmpSecondaryIndex.push_back(p);
        pair<string,int>p2(id,-1);
        pair<int,pair<string,int>> p3(IDlistBO,p2);
        IDList.push_back(p3);
    }
    else
    {
        int temp= EmpSecondaryIndex[position].second;
        EmpSecondaryIndex[position].second=IDlistBO;
        pair<string,int>p2(id,temp);
        pair<int,pair<string,int>> p3(IDlistBO,p2);
        IDList.push_back(p3);
    }
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

void deletePrimaryIndex(fstream &EPrimaryIndex,string id){
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
    //fileName.open("Employees.txt", ios::out | ios::in | ios::ate);

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
    cout<<"third"<<endl;

    fileName.seekp(0,ios::end);
    firstBO=fileName.tellp();
    fileName << setfill ('0') << setw (3);
    fileName << recordLength ;
    fileName<<EID<<"$"<<DID<<"$"<<EName<<"$"<<EPosition<<"$";
    //fileName.close();
    addEPrimaryIndex(f2,EID,firstBO);

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

void writeSecondaryIndex(fstream& ESecondaryIndex,fstream &ESecondaryData)
{
    sort(EmpSecondaryIndex.begin(),v.end());
    for(int i=0;i<EmpSecondaryIndex.size();i++)
    {
        ESecondaryIndex<<EmpSecondaryIndex[i].first<<'|'<<EmpSecondaryIndex[i].second<<endl;

    }
    for(int i=0;i<IDList.size();i++)
    {
        //vector <pair<int,pair<string,int>> >IDList(0); //BOfile, EID, pointer to second EID
        pair<string,int> p=IDList[i].second;
        ESecondaryData<<IDList[i].first<<'|'<<p.first<<'|'<<p.second<<endl;
    }
}

void printEmployee(fstream &EPrimaryIndex,fstream &Employees,string id)
{
    int pos=findEmployeeWithID(EPrimaryIndex,id);
    Employees.seekg(0,ios::beg);
    char temp;
    string Bo;
    for(int i=0;i<3;i++){
        Employees>>temp;
        Bo+=temp;
    }

    int intBO=stoi(Bo);
    for(int i=0;i<intBO;i++){
        Employees>>temp;
        if(temp!='&'){
            cout<<temp;
        }
        else{
            cout<<" ";
        }
    }
    cout<<endl;
}
void printEmployeeDepID(fstream &EPrimaryIndex, fstream &ESecondaryData, fstream &ESecondaryIndex, fstream &Employees,string DId)
{
    int searchSBO=0;
    for(int i=0;i<EmpSecondaryIndex.size();i++)
    {
        if(EmpSecondaryIndex[i].first==DId)
        {
           searchSBO=EmpSecondaryIndex[i].second;
           break;
        }
    }
    if(searchSBO==0){
        cout<<"departement not found";
        return;}

    string searchID;

    for(int i=0; i<IDList.size();i++)
    {
         pair<string,int>p=IDList[i].second;
        if(IDList[i].first==searchSBO)
        {
            printEmployee(EPrimaryIndex,Employees, p.first);
        }
    }
}
