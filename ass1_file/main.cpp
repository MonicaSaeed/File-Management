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


/*long BinarySearch(fstream f, string ID)
{
    int _Id = stoi(ID); // type of explicit type casting

}*/

int main()
{

    fstream Employees,Department,EPrimaryIndex;
    Employees.open("Employees.txt", ios::out | ios::in | ios::app);
    Department.open("Department.txt",ios::in | ios::out| ios::app);
    EPrimaryIndex.open("EPrimaryIndex.txt",ios::in | ios::out| ios::app);

//    addEmployees(Employees,EPrimaryIndex,"2","i","m","s");
//    addEmployees(Employees,EPrimaryIndex,"30","monica","is","student");
   pair<int,int> p= printEmployee(EPrimaryIndex,"30");
   cout<<p.first<<" "<<p.second<<endl;




    return 0;
}

void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li)
{
    EPrimaryIndex.seekp(0,ios::end);
    EPrimaryIndex<<totalRecordsSize<<'&'<<id<<'&';
    totalRecordsSize+=li;
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
    int recordLength = EID.size()+DID.size()+EName.size()+EPosition.size()+4;

    if( fileName.is_open() )
    {
        fileName << setfill ('0') << setw (3);
        fileName << recordLength ;

        fileName<<EID<<"$"<<DID<<"$"<<EName<<"$"<<EPosition<<"$";
    }
    addEPrimaryIndex(f2,EID,recordLength);
}
























/*


int main() {

    list<int> intList1;
    intList1.push_back(2);
    intList1.push_back(5);
    intList1.push_back(8);
    intList1.push_back(3);
    intList1.push_back(1);
    intList1.push_back(9);
    intList1.push_back(5);
    cout<<"list #1 : ";
    cout<<intList1;
    cout<<"size of list #1 : "<<intList1.size()<<endl;
    list<int>::iterator it = intList1.begin();
    it++,it++;
    list<int>::iterator temp=intList1.remove(it);
    cout<<"the value of iterator returned after erase : "<<*temp<<endl;
    cout<<"list #1 after erase : ";
    cout<<intList1;
    cout<<"size of list #1 after erase : "<<intList1.size()<<endl;
    list<int> intList2(10, 5); //list #2 with initial size
    cout<<"list #2 : ";
    cout<<intList2;
    intList2=intList1;
    cout<<"list #2 after copy values of list 1: ";
    cout<<intList2;
    it=intList2.begin();
    it+=2; //to insert in list #2 in position 3
    intList2.insert(it,11);
    cout<<"list #2 after inserting value '11' : ";
    cout<<intList2;
    cout<<"size of list #2 : "<<intList2.size()<<endl;
    return 0;

//    list<int> intList1;
//    intList1.push_back(2);
//    intList1.push_back(5);
//    intList1.push_back(8);
//    intList1.push_back(3);
//    intList1.push_back(1);
//    intList1.push_back(9);
//    intList1.push_back(5);
//    cout<<"list #1 : ";
//    cout<<intList1;
//    list<int>::iterator it = intList1.begin();
//    it++;
//    cout<<*++it<<endl;
//    it = intList1.remove(it);
//    cout<<*it<<endl;
//    intList1.pop_back();
//    intList1.push_back(7);
//    intList1.push_front(2);
//
//    cout<<"list #1 : ";
//    cout<<intList1;
//
//    list<int> t(5,3);
//    t = intList1;
//    cout<<"list #1 : ";
//    cout<<t;
//
//
//    return 0;
}

*/
















/*


int main() {

    list<int> intList1;
    intList1.push_back(2);
    intList1.push_back(5);
    intList1.push_back(8);
    intList1.push_back(3);
    intList1.push_back(1);
    intList1.push_back(9);
    intList1.push_back(5);
    cout<<"list #1 : ";
    cout<<intList1;
    cout<<"size of list #1 : "<<intList1.size()<<endl;
    list<int>::iterator it = intList1.begin();
    it++,it++;
    list<int>::iterator temp=intList1.remove(it);
    cout<<"the value of iterator returned after erase : "<<*temp<<endl;
    cout<<"list #1 after erase : ";
    cout<<intList1;
    cout<<"size of list #1 after erase : "<<intList1.size()<<endl;
    list<int> intList2(10, 5); //list #2 with initial size
    cout<<"list #2 : ";
    cout<<intList2;
    intList2=intList1;
    cout<<"list #2 after copy values of list 1: ";
    cout<<intList2;
    it=intList2.begin();
    it+=2; //to insert in list #2 in position 3
    intList2.insert(it,11);
    cout<<"list #2 after inserting value '11' : ";
    cout<<intList2;
    cout<<"size of list #2 : "<<intList2.size()<<endl;
    return 0;

//    list<int> intList1;
//    intList1.push_back(2);
//    intList1.push_back(5);
//    intList1.push_back(8);
//    intList1.push_back(3);
//    intList1.push_back(1);
//    intList1.push_back(9);
//    intList1.push_back(5);
//    cout<<"list #1 : ";
//    cout<<intList1;
//    list<int>::iterator it = intList1.begin();
//    it++;
//    cout<<*++it<<endl;
//    it = intList1.remove(it);
//    cout<<*it<<endl;
//    intList1.pop_back();
//    intList1.push_back(7);
//    intList1.push_front(2);
//
//    cout<<"list #1 : ";
//    cout<<intList1;
//
//    list<int> t(5,3);
//    t = intList1;
//    cout<<"list #1 : ";
//    cout<<t;
//
//
//    return 0;
}

*/
