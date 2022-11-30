#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

#include<bits/stdc++.h>

using namespace std;

template<class T>
struct slNode
{
    T info;
    slNode<T>* next;
    slNode(T info, slNode<T>* Ptr = NULL)
    {
        this->info=info;
        this->next=Ptr;
    }
};

template<class T>
class list
{
private:
    slNode<T> *head, *tail;
    int Size;
public:
    class iterator
    {
    private:
        slNode<T> *nodePtr;
    public:
        iterator(slNode<T> *p = NULL)
        {
            nodePtr = p;
        }
        slNode<T>* getnodePtr()
        {
            return nodePtr;
        };
        iterator operator++(int num)
        {
            iterator tmp = *this;
            nodePtr = nodePtr->next;
            return tmp;
        }
        iterator operator++()
        {
            nodePtr = nodePtr->next;
            return *this;
        }
        iterator operator+=(int num)
        {
            iterator *tmp = this;
            while (num--)
            {
                nodePtr = nodePtr->next;
            }
            return *this;
        }
        T& operator*()
        {
            return nodePtr->info;
        }
        bool operator==(const iterator& Node)
        {
            return (nodePtr == Node.nodePtr);
        }
        bool operator!=(const iterator& Node)
        {
            return (nodePtr != Node.nodePtr);
        }
    };


    list()
    {
        head = tail = NULL;
        Size = 0;
    }

    ~list()
    {
        //deallocate();
    }


    void push_front(T info)
    {
        slNode<T> *Ptr = new slNode<T>(info);
        if(!head)
        {
            head = tail = Ptr;
        }
        else
        {
            Ptr->next=head;
            head=Ptr;
        }
        Size++;
    }
    void push_back(T info)
    {
        slNode<T> *Ptr = new slNode<T>(info);
        if(!head)
        {
            head = tail = Ptr;
        }
        else
        {
            tail->next=Ptr;
            tail=Ptr;
        }
        Size++;
    }
    void insert(iterator loc, T info)
    {
        slNode<T>* Ptr = head;
        if (loc.getnodePtr()==tail)
        {
            push_back(info);
        }
        else
        {
            while(Ptr&&Ptr->next!=loc.getnodePtr())
            {
                Ptr = Ptr->next;
            }
            Ptr->next = new slNode<T>(info);
            Ptr->next->next = loc.getnodePtr();
            Size++;
        }
    }
    void pop_front()
    {
        slNode<T>* Ptr=head;
        if(head==tail)
        {
            head=tail=NULL;
        }
        else
        {
            head=head->next;
        }
        delete Ptr;
        Size--;
    }
    void pop_back()
    {
        slNode<T>* Ptr=head;
        if(head==tail)
        {
            head=tail=NULL;
        }
        else
        {
            while(Ptr&&Ptr->next!=tail)
            {
                Ptr = Ptr->next;
            }
            tail = Ptr;
            Ptr = Ptr->next;
            tail->next = NULL;
        }
        delete Ptr;
        Size--;
    }
    iterator remove(iterator loc)
    {
        slNode<T>* Ptr = head;
        if (loc.getnodePtr()==tail)
        {
            pop_back();
        }
        else
        {
            while(Ptr&&Ptr->next!=loc.getnodePtr())
            {
                Ptr = Ptr->next;
            }
            Ptr->next = loc.getnodePtr()->next;
            Size--;
        }
        delete loc.getnodePtr();
        return iterator(Ptr);
    }
    iterator search(T info)
    {
        slNode<T>* Ptr = head;
        while(Ptr&&Ptr->info!=info)
        {
            Ptr = Ptr->next;
        }
        return iterator(Ptr);
    }
    void clear()
    {
        slNode<T> *tmp;
        while(head != NULL)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        Size = 0;
    }
    int size()
    {
        return Size;
    }
    T front()
    {
        return head->info;
    }
    T back()
    {
        return tail->info;
    }
    iterator begin()
    {
        return iterator(head);
    }
    iterator end()
    {
        return iterator(tail->next);
    }
    iterator rbegin()
    {
        return iterator(tail);
    }
    iterator rend()
    {
        slNode<T> tmp(0,head);
        return iterator(tmp);
    }
};

void addEmployees(fstream &fileName,fstream &f2,string EID, string DID, string EName, string EPosition);
int totalRecordsSize=0;
void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li);
string printEmployee(fstream &EPrimaryIndex, string id);


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

    //addEmployees(Employees,EPrimaryIndex,"2","i","m","s");
    //addEmployees(Employees,EPrimaryIndex,"30","monica","is","student");
    cout<<printEmployee(EPrimaryIndex,"30");


    return 0;
}

void addEPrimaryIndex(fstream &EPrimaryIndex, string id,int li)
{
    EPrimaryIndex.seekp(0,ios::end);
    EPrimaryIndex<<totalRecordsSize<<'&'<<id<<'&';
    totalRecordsSize+=li;
}
string printEmployee(fstream &EPrimaryIndex,string id){ //return byteofficet
    vector <pair<string,string>>v(0);
    EPrimaryIndex.seekg(0,ios::end);
    int textLength = (int)EPrimaryIndex.tellg();
    EPrimaryIndex.seekg(0,ios::beg);
    int textStart =0;

    while(textStart<textLength){
        char temp1,temp2;
        string Sbo,SID;
        EPrimaryIndex>>temp1;
        while(temp1!='&')
        {
            Sbo+=temp1;
            EPrimaryIndex>>temp1;
        }
        EPrimaryIndex>>temp2;
        while(temp2!='&')
        {
            SID+=temp2;
            EPrimaryIndex>>temp2;
        }
        textStart += (int)EPrimaryIndex.tellg();
        pair<string,string> p(SID,Sbo);
        v.push_back(p);
    }
    sort(v.begin(),v.end());

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
    if(start>end) //if not found
    {
        return "-1";
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
