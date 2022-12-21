#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// B-tree node structure
struct BTreeNode {
    int isLeaf; ///initial -> -1, 0 -> means a leaf node, 1 -> a non-leaf node
    int m;
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
    vector<int> visitedNodes;


public:
    BTree(int root,int firstEmptyNode){
        this->root=root;
        this->firstEmptyNode=firstEmptyNode;
        //this->visitedNodes=NULL;
    }
    void CreateIndexFile (string filename, int numberOfRecords, int m);
    void DisplayIndexFileContent (string filename,int rows);

    //int InsertNewRecordAtIndex (string filename, int RecordID, BTreeNode btn);
    BTreeNode readRecord(string filename,int nodeNum);
    void writeNode(string filename,BTreeNode btn, int nodeNum);

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

void BTree::DisplayIndexFileContent (string filename,int rows){
    //initial read
    for(int i=0;i<rows;i++){
        // Read the node from the file
        BTreeNode readNode = readRecord(filename,i);

        // Print the node values
        cout << "Is leaf: " << readNode.isLeaf << endl;
        cout << "m: " << readNode.m << endl;
        cout << "Keys: ";
        for (int key : readNode.keys) {
            cout << key << " ";
        }
        cout << endl;
        cout << "References: ";
        for (int ref : readNode.references) {
            cout << ref << " ";
        }
        cout << endl;
    }
}

// Reads a record from the binary file
BTreeNode BTree::readRecord(string filename,int nodeNum) {
    // Open the file in binary mode
    fstream file(filename, ios::in | ios::binary);

    // Seek to the node position
    file.seekg(nodeNum * sizeof(BTreeNode), ios::beg);

    // Read the node from the file
    BTreeNode btn;
    file.read((char*)&btn, sizeof(BTreeNode));

    // Close the file
    file.close();

    return btn;
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


int main()
{
    // Create a B-tree with a maximum of 5 keys per node
    cout<<"enter rows, m ,file name";
    int rows;cin>>rows;
    int m; cin>>m;
    string fileName;cin>>fileName;
    BTree btree(0, 1);
    btree.CreateIndexFile(fileName,rows,m);
    btree.DisplayIndexFileContent(fileName,rows);



    return 0;
}

//search  vest
//
