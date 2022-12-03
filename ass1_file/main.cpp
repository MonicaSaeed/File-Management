#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include<bits/stdc++.h>

using namespace std;

vector <pair<string,int>>v(0);
vector <pair<string,int>>EmpSecondaryIndex(0); //DID , BO
vector <pair<int,pair<string,int>> >IDList(0); //BOfile, EID, pointer to second EID

//int totalRecordsSize=0;

void addEmployees(fstream &Employees, fstream &EPrimaryIndex, fstream &ESecondaryIndex, fstream &ESecondaryData, string EID, string DID, string EName, string EPosition);

void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li);
void readPrimaryIndexToVector(fstream &EPrimaryIndex);
void sortPrimaryIndex(fstream &EPrimaryIndex);

void SecondaryIndex(fstream &ESecondaryIndex,fstream &ESecondaryData, string depId,string id);
void writeSecondaryIndex(fstream& ESecondaryIndex,fstream &ESecondaryData);

int searchEmployeeWithID(string id);
void printEmployee(fstream &EPrimaryIndex,fstream &Employees,string id);

int searchEmployeesWithDID(string DId);
void printEmployeeDepID(fstream &EPrimaryIndex, fstream &ESecondaryData, fstream &ESecondaryIndex, fstream &Employees,string DId);

void deleteEmployee(fstream &Employee,fstream &EPrimaryIndex, string employeeID);
void deletePrimaryIndex(fstream &EPrimaryIndex,string id);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int listHeader=-1;
    fstream Employees,Department,EPrimaryIndex,ESecondaryIndex,ESecondaryData;
    Employees.open("Employees.txt", ios::out | ios::in | ios::app);
    Employees<<"00000000-1";
    Employees.close();
    // addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"2","i","m","s");
    // addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"30","is","monica","student");
    //addEmployees(Employees,EPrimaryIndex,"25","mirette","ai","studenttt");
    // deleteEmployee(Employees,EPrimaryIndex,"2");
    // addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"25","ai","mirette","studenttt");
    //deleteEmployee(Employees,EPrimaryIndex,"30");
    // pair<int,int> p= printEmployee(EPrimaryIndex,"30");
    // cout<<p.first<<" "<<p.second<<endl;
    //addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,"sjnkc","acs","EmpName","EmpPosition");


    int num;
    do{
        cout<<"choose operation: "<<endl;
        cout<<"1: Add new Employee"<<endl;
        cout<<"2: Add new Department"<<endl;
        cout<<"3: Delete Employee"<<endl;
        cout<<"4: Delete Department"<<endl;
        cout<<"5: Search Employee with ID"<<endl;
        cout<<"6: Search Employee with department ID"<<endl;
        cout<<"7: Search Department with ID"<<endl;
        cout<<"8: Search Department with name"<<endl;
        cout<<"9: Write a Query"<<endl;
        cout<<"10: Exit."<<endl;
        cin>>num;

        if(num==1)
        {
            string EmpId,DepID,EmpName,EmpPosition;
            cout<<"enter employee's ID, departement ID ,Employees's name, and position"<<endl;
            cin>>EmpId>>DepID>>EmpName>>EmpPosition;
            addEmployees(Employees,EPrimaryIndex,ESecondaryIndex,ESecondaryData,EmpId,DepID,EmpName,EmpPosition);
        }
        else if (num==3){
            string EmpId;
            cout<<"enter employee's ID"<<endl;
            cin>>EmpId;
            deleteEmployee(Employees,EPrimaryIndex,EmpId);
        }
        else if(num==5){
            //load data from Primary Index file to vector v
            readPrimaryIndexToVector(EPrimaryIndex);
            cout<<"enter employee's ID"<<endl;
            string EmpId;
            cin>>EmpId;
            printEmployee(Employees,EPrimaryIndex,EmpId);
        }
        else if (num == 6){
            cout<<"enter Department ID"<<endl;
            string DepId;
            cin>>DepId;
            printEmployeeDepID(EPrimaryIndex,ESecondaryData,ESecondaryIndex,Employees,DepId);
        }

    }while(num != 0);

    return 0;
}

void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li){
    EPrimaryIndex.open("EPrimaryIndex.txt",ios::in | ios::out| ios::app);
    EPrimaryIndex.seekp(0,ios::end);
    EPrimaryIndex<<id<<'&'<<li<<endl;
    EPrimaryIndex.close();
    sortPrimaryIndex(EPrimaryIndex);
}

void SecondaryIndex(fstream &ESecondaryIndex,fstream &ESecondaryData, string depId,string id){
    bool findDepID = false;
    int position=0;
    if(!EmpSecondaryIndex.empty()){
        for(int i=0;i<EmpSecondaryIndex.size();i++){
            if(EmpSecondaryIndex[i].first==depId)
            {
                findDepID = true;
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
    //create secondary index file and secondary data file if not exist
    ESecondaryIndex.open("ESecondaryIndex.txt",ios::in | ios::out| ios::app);
    ESecondaryData.open("ESecondaryData.txt",ios::in | ios::out| ios::app);
    ESecondaryIndex.close();
    ESecondaryData.close();
    //write the secondary index and secondary data
    writeSecondaryIndex(ESecondaryIndex,ESecondaryData);
}

void readPrimaryIndexToVector(fstream &EPrimaryIndex){
    v.clear();
    EPrimaryIndex.open("EPrimaryIndex.txt",ios::in | ios::out| ios::app);
    while(!EPrimaryIndex.eof())
    {
        string Sbo,SID;
        getline(EPrimaryIndex,SID,'&');
        getline(EPrimaryIndex,Sbo);
        if(Sbo.empty() || SID.empty())break;
        pair<string,int> p(SID,stoi(Sbo));
        v.push_back(p);
    }

    EPrimaryIndex.close();
}

void sortPrimaryIndex(fstream &EPrimaryIndex){
    readPrimaryIndexToVector(EPrimaryIndex);
    sort(v.begin(),v.end());
    EPrimaryIndex.open("EPrimaryIndex.txt", ios::in | ios::out | ios::trunc);
    for(int i=0;i<v.size();i++)
    {
        EPrimaryIndex<<v[i].first<<'&'<<v[i].second<<endl;
    }
    EPrimaryIndex.close();
}

void deletePrimaryIndex(fstream &EPrimaryIndex,string id){
    vector <pair<string,int>>v2(v); //v carries the primary index
    v.clear();
    cout<<v2.size()<<"v2 size"<<endl;
    cout<<v.size()<<"v size befor"<<endl;
    int s=v2.size();
    for(int i=0;i<s;i++){
        if(v2[i].first != id){
            v.push_back(v2[i]);
        }
    }
    s=v.size();
    cout<<v.size()<<"v size after"<<endl;
  //  sortPrimaryIndex(EPrimaryIndex);
    EPrimaryIndex.open("EPrimaryIndex.txt", ios::in | ios::out | ios::trunc);
    for(int i=0;i<v.size();i++)
    {
        EPrimaryIndex<<v[i].first<<'&'<<v[i].second<<endl;
    }
    EPrimaryIndex.close();


}

int searchEmployeeWithID(string id)
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

int searchEmployeesWithDID(string DId)
{
    //binary search
    int start = 0;
    int end = (int)EmpSecondaryIndex.size()-1;
    int mid = (start+end)/2;
    while(start<=end)
    {
        if(EmpSecondaryIndex[mid].first==DId)
        {
            return EmpSecondaryIndex[mid].second;
            break;
        }
        else if(EmpSecondaryIndex[mid].first<DId)
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

void addEmployees(fstream &Employees, fstream &EPrimaryIndex, fstream &ESecondaryIndex, fstream &ESecondaryData, string EID, string DID, string EName, string EPosition)
{
    Employees.open("Employees.txt", ios::out | ios::in );

    int recordLength = EID.size()+DID.size()+EName.size()+EPosition.size()+4;
    int firstBO;
    Employees.seekg(0, ios::beg);
    string h;
    char temp;
    for(int i=0; i<10; i++)
    {
        Employees >> temp;
        h+=temp;
    }
    cout << h << endl << Employees.tellg() << endl;
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
    bool done= false;
    if(findDeletRecord!=-1)
    {
        while(findDeletRecord!=-1) /////////////////////////////////////////////////////aaaaaaaaaaaaaaaaaaaaaaaaah
        {
            cout<<"firsttt"<<endl;
            Employees.seekg(findDeletRecord + 1, ios::beg);
            cout << "\\\\\\\\\\\\\\" << Employees.tellg() << endl;
            char tmp;
            string SDR;
            Employees >> tmp;
            while(tmp!='|')
            {
                SDR+=tmp;
                Employees >> tmp;
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
                int diff=sizeDeletedRecod-recordLength-3;
                string dif;
                cout<<"\\\\\\\\\\\\\\"<<recordLength<<endl;
                //cout<<"\\\\\\\\\\\\\\"<<Employees.tellg()<<endl;
                Employees.seekp(findDeletRecord, ios::beg);
                Employees << setfill ('0') << setw (3);
                for(int i=0;i<diff;i++)
                {
                    dif+='-';
                }
                Employees << recordLength+dif.size() ;
                Employees << EID << "$" << DID << "$" << EName << "$" << EPosition <<dif<< "$";
                findDeletRecord=-1;
                //cout<<"diff--------"<<diff<<endl;
                Employees.close();
                addEPrimaryIndex(EPrimaryIndex, EID, firstBO);
                SecondaryIndex(ESecondaryIndex, ESecondaryData, DID, EID);
                done=true;
                break;
            }

            else
            {
                cout<<"second"<<endl;

                Employees.seekg(1, ios::cur);
                cout << Employees.get() << endl;
                char tmp2;
                string nextBO;
                Employees >> tmp2;
                while(tmp!='|')
                {
                    nextBO+=tmp2;
                    Employees >> tmp2;
                }
                stringstream transnextBO(nextBO);
                int findDeletRecord = 0;
                transnextBO>>findDeletRecord;

            }
        }
    }
    cout<<"third"<<endl;
    if(done== false) {
        Employees.seekp(0, ios::end);
        firstBO = Employees.tellp();
        Employees << setfill('0') << setw(3);
        Employees << recordLength;
        Employees << EID << "$" << DID << "$" << EName << "$" << EPosition << "$";
        Employees.close();
        addEPrimaryIndex(EPrimaryIndex, EID, firstBO);
        SecondaryIndex(ESecondaryIndex, ESecondaryData, DID, EID);
    }
}

void deleteEmployee(fstream &Employee,fstream &EPrimaryIndex, string employeeID)
{
    Employee.open("Employees.txt", ios::in | ios::out);
    if(Employee.is_open())
    {
        int deleteBO= searchEmployeeWithID(employeeID);
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
        deletePrimaryIndex(EPrimaryIndex,employeeID);
        Employee.close();

    }
    //deletePrimaryIndex(EPrimaryIndex,employeeID);///////matnafezsh
    //Employee.open("Employee.txt", ios::in |ios::out|ios::app);
}

void writeSecondaryIndex(fstream& ESecondaryIndex,fstream &ESecondaryData)
{
    ESecondaryIndex.open("ESecondaryIndex.txt",ios::in | ios::out);
    ESecondaryData.open("ESecondaryData.txt",ios::in | ios::out);
    sort(EmpSecondaryIndex.begin(),EmpSecondaryIndex.end());
    for(int i=0; i<EmpSecondaryIndex.size(); i++)
    {
        ESecondaryIndex<<EmpSecondaryIndex[i].first<<'|'<<EmpSecondaryIndex[i].second<<endl;
    }
    for(int i=0; i<IDList.size();i++)
    {
        pair<string,int> p=IDList[i].second;
        ESecondaryData<<IDList[i].first<<'|'<<p.first<<'|'<<p.second<<endl;
    }
    ESecondaryIndex.close();
    ESecondaryData.close();
}

void printEmployee(fstream &EPrimaryIndex,fstream &Employees,string id)
{
    Employees.open("Employees.txt", ios::out | ios::in );
    int pos= searchEmployeeWithID(id);
    if (pos == -1)
    {
        cout << "Employee not found" << endl;
        return;
    }
    Employees.seekg(pos,ios::beg);
    char temp;
    string Bo;
    for(int i=0;i<3;i++){
        Employees>>temp;
        Bo+=temp;
    }
    int intBO=stoi(Bo);
    for(int i=0;i<intBO;i++){
        Employees>>temp;
        if(temp!='$'){
            cout<<temp;
        }
        else{
            cout<<" ";
        }
    }
    cout<<endl;
    Employees.close();
}

void printEmployeeDepID(fstream &EPrimaryIndex, fstream &ESecondaryData, fstream &ESecondaryIndex, fstream &Employees,string DId)
{
    int searchSBO = searchEmployeesWithDID(DId);
    if(searchSBO==-1){
        cout<<"departement not found";
        return;}

    string searchID;

    pair<string,int> p;
    do {
        p = IDList[searchSBO-1].second;
        printEmployee(EPrimaryIndex,Employees,p.first);
        searchSBO=p.second;
    } while (p.second!=-1);
}
