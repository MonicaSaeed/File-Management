#include <iostream>
#include <fstream>
#include <vector>
#include<bits/stdc++.h>
#include<cmath>
using namespace std;

// B-tree node structure
struct BTreeNode {
    int isLeaf; ///initial -> -1, 0 -> means a leaf node, 1 -> a non-leaf node
    int m; ///number of keys and number of references
    vector<int> keys; ///node value v(5) max
    vector<int> references; ///node reference v(5) max

    // Default constructor
    BTreeNode(){
    }

    // Constructor with isLeaf, m, keys, and references parameters
    BTreeNode(int isLeaf, int m, vector<int> keys, vector<int> references) {
        this->isLeaf = isLeaf;
        this->m = m;
        this->keys = keys;
        this->references = references;
    }

    // Constructor with isLeaf and m parameters
    BTreeNode(int isLeaf, int m) {
        this->isLeaf = isLeaf;
        this->m = m;
        this->keys = vector<int>(m);
        this->references = vector<int>(m);
    }

};


// B-tree index on a binary file
class BTree {
private:
    int root;
    int firstEmptyNode;

public:
    vector<int> visitedNodes;

    BTree(int root,int firstEmptyNode){
        this->root=root;
        this->firstEmptyNode=firstEmptyNode;
        //this->visitedNodes=NULL;
    }
    void CreateIndexFile (string filename, int numberOfRecords, int m);
    void writeNode(string filename,BTreeNode btn, int nodeNum);
    void DisplayIndexFileContent (string filename,int rows);
    BTreeNode readRecord(string filename,int nodeNum);
    int SearchARecord (string filename, int RecordID);
    void DeleteRecordFromIndex (string filename, int RecordID);
    int InsertNewRecordAtIndex (string filename, int RecordID, int Reference);
    int SearchNode (string filename, int RecordID);

};


void BTree::CreateIndexFile (string filename, int numberOfRecords, int m){
    //initial write
    for(int i=0;i<numberOfRecords;i++){
        vector <int> keys(m);
        vector <int>references(m);
        if(i==numberOfRecords-1){
            for(int j=0;j<m;j++){
                keys[j]=-1;
                references[j]=-1;
            }
        }
        else{
            for(int j=0;j<m;j++){
                if(j==0){
                    keys[j]=i+1;
                    references[j]=-1;
                }
                else{
                    keys[j]=-1;
                    references[j]=-1;
                }
            }
        }

        BTreeNode btn(-1,m,keys,references);
        writeNode(filename,btn, i);
    }

}

// Writes a node to the binary file
void BTree::writeNode(string filename,BTreeNode btn, int nodeNum) {
    // Open the file in binary mode
    fstream file(filename, ios::out | ios::app | ios::binary);

    // Seek to the node position
    file.seekp(nodeNum * sizeof(BTreeNode), ios::beg);

    // Write the node to the file
    file.write((char*)&btn, sizeof(BTreeNode));

    // Close the file
    file.close();
}

void BTree::DisplayIndexFileContent (string filename,int rows){
    //initial read
    for(int i=0;i<rows;i++){
        // Read the node from the file(open file)
        BTreeNode readNode = readRecord(filename,i);
        cout <<setw(8)<< readNode.isLeaf;

        for (int i=0;i<readNode.keys.size();i++) {
            cout <<setw(8)<< readNode.keys[i] << setw(8)<< readNode.references[i];
        }
        cout << endl;
    }
}

// Reads a record from the binary file
BTreeNode BTree::readRecord(string filename,int nodeNum) {
    // Open the file in binary mode
    fstream file(filename, ios::in | ios::binary);

    //file.seekg(0,ios::end);

    // Seek to the node position
    file.seekg(nodeNum * sizeof(BTreeNode), ios::beg);

    // Read the node from the file
    BTreeNode btn;
    file.read((char*)&btn, sizeof(BTreeNode));

    // Close the file
    file.close();

    return btn;
}

int BTree::SearchARecord (string filename, int RecordID){
    visitedNodes.clear();
    int refReturn=-1;
    BTreeNode btn;
    int m=1;
    //int sz=1;
    visitedNodes.push_back(1);
    do
    {
        btn = readRecord(filename,m);
        if(btn.isLeaf==-1){
            break;
        }

        for(int i=0;i<btn.m;i++)
        {
            if(btn.keys[i]>RecordID || btn.keys[i]==RecordID){
                refReturn=btn.references[i];
                m=refReturn;
               if(btn.isLeaf==1){
                    visitedNodes.push_back(btn.references[i]);
                }
                break;
            }
        }
    }while(btn.isLeaf==1 && refReturn != -1); //non



    BTreeNode b;
    if(refReturn!=-1){
        b=readRecord(filename,refReturn);
    }
    if(b.isLeaf==0)
    {
        //cout<<"LLLLLLLLLL"<<endl;
        for(int i=0;i<b.m;i++)
        {
            if(b.keys[i]==RecordID){
                //cout<<"keys "<<b.keys[i]<<"cccccc "<<b.references[i]<<endl;
                refReturn=b.references[i];
                break;
            }
        }
     }
     //cout<<"end"<<endl;
     return refReturn;
}

void BTree::DeleteRecordFromIndex (string filename, int RecordID){
    int sz ;
    int searchReturn = SearchARecord(filename,RecordID);
    if(searchReturn != -1)
    {
        int tempRef;
        for(int i=0;i<visitedNodes.size();i++) //visited
        {
            BTreeNode btn = readRecord(filename,visitedNodes[i]);
            sz = btn.keys.size();
            for(int j=0 ;j<btn.keys.size();j++)
            {
                if(btn.keys[j]==RecordID){
                    btn.keys[j]=-1;
                    btn.references[j]=-1;
                }
            }
            vector < pair<int,int> > vec;
            for(int i=0;i<sz;i++){
                if(btn.keys[i]!=-1){
                    /*pair<int,int> p;
                    p.first=btn.keys[i];
                    p.second=btn.references[i];*/
                    vec.push_back( make_pair(btn.keys[i],btn.references[i]) );
                }
            }

            btn.keys.clear();
            btn.references.clear();

            sort(vec.begin(), vec.end());
            for(int i=0;i<vec.size();i++){
                btn.keys.push_back(vec[i].first) ;
                btn.references.push_back( vec[i].second);
            }


            while(btn.keys.size() < sz){
            btn.keys.push_back(-1) ;
            btn.references.push_back(-1);
            }

            writeNode(filename,btn,visitedNodes[i]);
        }
    }

}

int BTree::InsertNewRecordAtIndex (string filename, int RecordID, int Reference){

}

int BTree::SearchNode (string filename, int RecordID){
    visitedNodes.clear();
    int refReturn=1; //insert root
    BTreeNode btn;
    int m=1;
    visitedNodes.push_back(1);
    do
    {
        btn = readRecord(filename,m);
        if(btn.isLeaf <= 0 ){
            return refReturn;
        }

        for(int i=0;i<btn.m;i++)
        {
            cout<<btn.keys[i]<<" "<<RecordID<<endl;
            if(btn.keys[i]==RecordID){
                cout<<"blaaaaaaa"<<endl;
                return -1;
            }

            if(btn.keys[i]>RecordID || btn.keys[i+1] == -1 || i == btn.m - 1)
            {
                refReturn=btn.references[i];
                m=refReturn;
               if(btn.isLeaf==1){
                    visitedNodes.push_back(btn.references[i]);
                    //cout<<"push= "<<refReturn<<endl;
                }
               // cout<<"ref= "<<refReturn<<endl;
                break;
            }
        }
    }while(btn.isLeaf==1);

     return refReturn;
}




int main()
{
    // Create a B-tree with a maximum of 5 keys per node
    cout<<"enter rows, m ,file name";
    int rows;cin>>rows;
    int m; cin>>m;
    string fileName;cin>>fileName;
    BTree btree(0, 7);
    //btree.CreateIndexFile(fileName,rows,m);
    //btree.DisplayIndexFileContent(fileName,rows);


    vector <int> keys = {7, -1, -1, -1, -1};
    vector <int>references = {-1, -1, -1, -1, -1};
    BTreeNode btn(-1,m,keys,references);
    btree.writeNode(fileName,btn, 0);


    keys = {3,7,10,15,30};
    references = {2,4,5,3,6};
    BTreeNode b(1,m,keys,references);
    btree.writeNode(fileName,b,1);

    keys = {1,2,3,-1,-1};
    references = {120,144,12,-1,-1};
    BTreeNode n(0,m,keys,references);
    btree.writeNode(fileName,n,2);

     keys = {11,14,12,15,-1};
    references = {192,72,204,108,-1};
    BTreeNode t(0,m,keys,references);
    btree.writeNode(fileName,t,3);

     keys = {5,6,7,-1,-1};
    references = {132,180,24,-1,-1};
    BTreeNode bt(0,m,keys,references);
    btree.writeNode(fileName,bt,4);


     keys = {8,9,10,-1,-1};
    references = {156,168,48,-1,-1};
    BTreeNode bb(0,m,keys,references);
    btree.writeNode(fileName,bb,5);


     keys = {17,18,19,24,30};
    references = {216,228,84,60,196};
    BTreeNode bbtt(0,m,keys,references);
    btree.writeNode(fileName,bbtt,6);


     keys = {-1, -1, -1, -1, -1};
    references = {-1, -1, -1, -1, -1};
    BTreeNode nn(-1,m,keys,references);
    btree.writeNode(fileName,nn, 7);


     keys = {-1, -1, -1, -1, -1};
    references = {-1, -1, -1, -1, -1};
    BTreeNode bbbbb(-1,m,keys,references);
    btree.writeNode(fileName,bbbbb, 8);


     keys = {-1, -1, -1, -1, -1};
    references = {-1, -1, -1, -1, -1};
    BTreeNode mm(-1,m,keys,references);
    btree.writeNode(fileName,mm, 9);

    btree.DisplayIndexFileContent(fileName,rows);




    cout<<btree.SearchARecord(fileName,30)<<endl; //196

    cout<<btree.SearchARecord(fileName,6)<<endl;//180

    btree.DeleteRecordFromIndex(fileName,7);
    btree.DeleteRecordFromIndex(fileName,10);
    btree.DeleteRecordFromIndex(fileName,11);
    btree.DeleteRecordFromIndex(fileName,15);
    btree.DisplayIndexFileContent(fileName,rows);

    //cout<<btree.SearchNode(fileName,12)<<endl;


    return 0;
}
