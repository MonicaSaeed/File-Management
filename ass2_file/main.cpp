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
    string fileName;
    int m;
    int root;
    int firstEmptyNode;
    vector<int> visitedNodes;


public:
    BTree(string fileName,int m,int root,int firstEmptyNode){
        this->fileName=fileName;
        this->m=m;
        this->root=root;
        this->firstEmptyNode=firstEmptyNode;
        //this->visitedNodes=NULL;
    }
    BTreeNode readRecord(int nodeNum);
    void writeNode(BTreeNode btn, int nodeNum);

};

// Reads a record from the binary file
BTreeNode BTree::readRecord(int nodeNum) {
    // Open the file in binary mode
    fstream file(fileName, ios::in | ios::binary);

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
void BTree::writeNode(BTreeNode btn, int nodeNum) {
    // Open the file in binary mode
    fstream file(fileName, ios::out | ios::app | ios::binary);

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
    BTree btree(fileName, m, 0, 2);

    //initial write
    for(int i=0;i<rows;i++){
        vector <int> keys(m);
        vector <int>references(m);
        if(i==rows-1){
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
        btree.writeNode(btn, i);
    }

    //initial read
    for(int i=0;i<rows;i++){
        // Read the node from the file
        BTreeNode readNode = btree.readRecord(i);

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

    return 0;
}
