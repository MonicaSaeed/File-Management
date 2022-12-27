#include <iostream>
#include <fstream>
#include <vector>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

struct Record {
    int key;
    int reference;

    Record() {
        this->key = -1;
        this->reference = -1;
    }
};

static const int m = 5;
static const int rows = 10;

// B-tree node structure
class BTreeNode {
public:

    int isLeaf; ///initial -> -1, 0 -> means a leaf node, 1 -> a non-leaf node
    Record recArray[m];
    bool isempty;

    // Default constructor
    BTreeNode() {
        this->isLeaf = -1;
        this->isempty = true;
        for (int i = 0; i < m; i++) {
            Record def;
            this->recArray[i] = def;
        }
    }

    // Constructor with isLeaf, m, keys, and references parameters
    BTreeNode(int isLeaf) {
        this->isLeaf = isLeaf;
        this->isempty = false;
        for (int i = 0; i < m; i++) {
            Record def;
            this->recArray[i] = def;
        }
    }

    void writeNode(string filename, int nodeNum) {
        ofstream file(filename, ios::app | ios::binary);
        file.seekp(nodeNum * sizeof(BTreeNode), ios::beg);
        //cout << this->isLeaf << "   " << this->recArray[0].key << " " << this->recArray[0].reference << endl;
        file.write((char *) this, sizeof(BTreeNode));
        this->readNode(filename, nodeNum);
        //cout << this->isLeaf << "   " << this->recArray[0].key << " " << this->recArray[0].reference << endl;

        file.close();
    }

    BTreeNode readNode(string filename, int nodeNum) {
        //Open the file in binary mode
        ifstream file(filename, ios::in | ios::binary);

        file.seekg(nodeNum * sizeof(BTreeNode), ios::beg);

        // Read the node from the file
//        BTreeNode btn;
        file.read((char *) this, sizeof(BTreeNode));
        // Close the file
        file.close();

        return *this;
    }

    // Constructor with isLeaf and m parameters
//    BTreeNode(int isLeaf, int m) {
//        this->isLeaf = isLeaf;
//        this->isempty = false;
//        //this->m = m;
//        for (int i = 0; i < m; i++) {
//            Record def;
//            this->recArray[i] = def;
//        }
//    }


};


// B-tree index on a binary file
class BTree {
private:
    int root;
    int firstEmptyNode;

public:
    vector<int> visitedNodes;

    BTree(int root, int firstEmptyNode) {
        this->root = root;
        this->firstEmptyNode = firstEmptyNode;
        //this->visitedNodes=NULL;
    }

    void CreateIndexFile(string filename, int numberOfRecords);///, int m);
    // static void writeNode(string filename, BTreeNode btn, int nodeNum);

    //BTreeNode readNode(string filename, int nodeNum);
    void DisplayIndexFileContent(string filename);//,int rows);

    int SearchARecord(string filename, int RecordID);

    void DeleteRecordFromIndex(string filename, int RecordID);

    int splitNode(string filename, int RecordID, int Reference, int nodeNO);

    int InsertNewRecordAtIndex(string filename, int RecordID, int Reference);

    int SearchNode(string filename, int RecordID);

};


void BTree::CreateIndexFile(string filename, int numberOfRecords) {//, int m){
    //initial write
    for (int i = 0; i < numberOfRecords; i++) {
        BTreeNode btn(-1);
        if (i != numberOfRecords - 1) {
            btn.recArray[0].key = i + 1;
        }
        btn.writeNode(filename, i);
    }

}

//Writes a node to the binary file
//void BTree::writeNode(string filename, BTreeNode btn, int nodeNum) {
//    fstream file(filename, ios::out | ios::in | ios::app | ios::binary);
//    file.seekp(nodeNum * sizeof(BTreeNode), ios::beg);
//    cout << file.tellp() << endl;
//    cout << btn.isLeaf << endl;
//    cout << btn.recArray[0].key << endl;
//    cout << btn.recArray[0].reference << endl;
//    file.write((char *) &btn, sizeof(BTreeNode));
//    file.close();
//}

void BTree::DisplayIndexFileContent(string filename) {//,int rows){
    //initial read
    for (int i = 0; i < rows; i++) {

        BTreeNode readN = readN.readNode(filename, i);
        cout << setw(8) << readN.isLeaf;

        for (int j = 0; j < m; j++) {
            cout << setw(8) << readN.recArray[j].key << setw(8) << readN.recArray[j].reference;
        }
        cout << endl;
    }
    cout << "after display" << endl;
}

// Reads a record from the binary file
//BTreeNode BTree::readNode(string filename, int nodeNum) {
//    //Open the file in binary mode
//    ifstream file(filename, ios::in | ios::out | ios::binary);
//    //cout<<!(!file)<<endl;
//    //file.open(filename);
//    cout << "display after opening the file" << endl;
//
//    //file.seekg(0,ios::end);
//
//    // Seek to the node position
//    file.seekg(nodeNum * sizeof(BTreeNode), ios::beg);
//    cout << "display after seeking" << file.tellg() << endl;
//
//    // Read the node from the file
//    BTreeNode btn;
//    file.read((char *) &btn, sizeof(BTreeNode));
//    cout << btn.isLeaf << endl;
//    cout << btn.recArray[0].key << endl;
//    cout << btn.recArray[0].reference << endl;
//    cout << "display after reading the file" << endl;
//
//    // Close the file
//    file.close();
//    //cout<<file.good()<<endl;
//
//    return btn;
//}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BTree::SearchARecord(string filename, int RecordID) {
    visitedNodes.clear();
    int refReturn = -1;
    BTreeNode btn;
    int first = 1;
    //int sz=1;
    visitedNodes.push_back(1);
    do {
        btn = btn.readNode(filename, first);
        if (btn.isLeaf == -1) {
            break;
        }

        for (int i = 0; i < m; i++) {
            if (btn.recArray[i].key > RecordID || btn.recArray[i].key == RecordID) {
                refReturn = btn.recArray[i].reference;
                first = refReturn;
                if (btn.isLeaf == 1) {
                    visitedNodes.push_back(btn.recArray[i].reference);
                }
                break;
            }
        }
    } while (btn.isLeaf == 1 && refReturn != -1); //non



    BTreeNode b;
    if (refReturn != -1) {
        b = b.readNode(filename, refReturn);
    }
    if (b.isLeaf == 0) {
        for (int i = 0; i < m; i++) {
            if (b.recArray[i].key == RecordID) {
                refReturn = b.recArray[i].reference;
                break;
            }
        }
    }
    return refReturn;
}

void BTree::DeleteRecordFromIndex(string filename, int RecordID) {
    int sz;
    int mx = -1;
    int searchReturn = SearchARecord(filename, RecordID);
    if (searchReturn != -1) {
        int tempRef;

        BTreeNode btn = btn.readNode(filename, visitedNodes.size() - 1);
        for (int j = 0; j < m; j++) {
            if (btn.recArray[j].key == RecordID && btn.isLeaf == 0) {
                btn.recArray[j].key = -1;
                btn.recArray[j].reference = -1;
                mx = btn.recArray[j - 1].key;
            }
        }

        vector<pair<int, int> > vec1;
        for (int i = 0; i < m; i++) {
            if (btn.recArray[i].key != -1) {
                vec1.push_back(make_pair(btn.recArray[i].key, btn.recArray[i].reference));
            }
        }


        sort(vec1.begin(), vec1.end());
        int secondLoop = 0;
        for (int i = 0; i < vec1.size(); i++) {
            btn.recArray[i].key = vec1[i].first;
            btn.recArray[i].reference = vec1[i].second;
            secondLoop++;
        }
        for (int i = secondLoop; i < m; i++) {
            btn.recArray[i].key = -1;
            btn.recArray[i].reference = -1;
        }

        btn.writeNode(filename, visitedNodes.size() - 1);


        for (int i = 0; i < visitedNodes.size() - 2; i++) //visited
        {
            btn = btn.readNode(filename, visitedNodes[i]);

            for (int j = 0; j < m; j++) {
                if (btn.recArray[j].key == RecordID && btn.isLeaf == 1) {
                    btn.recArray[j].key = mx;
                }
            }

            vector<pair<int, int> > vec2;
            for (int i = 0; i < m; i++) {
                if (btn.recArray[i].key != -1) {
                    vec2.push_back(make_pair(btn.recArray[i].key, btn.recArray[i].reference));
                }
            }


            sort(vec2.begin(), vec2.end());
            int secondLoop = 0;
            for (int i = 0; i < vec2.size(); i++) {
                btn.recArray[i].key = vec2[i].first;
                btn.recArray[i].reference = vec2[i].second;
                secondLoop++;
            }
            for (int i = secondLoop; i < m; i++) {
                btn.recArray[i].key = -1;
                btn.recArray[i].reference = -1;
            }

            btn.writeNode(filename, visitedNodes[i]);


        }
    }

}

//int BTree::splitNode(string filename, int RecordID, int Reference, int nodeNO) {
//    BTreeNode b1, b2;
//    b1.readNode(filename, nodeNO);
//    b2.readNode(filename, this->firstEmptyNode);
//
//
//
//
//}

int BTree::InsertNewRecordAtIndex(string filename, int RecordID, int Reference) {
    int currentNode = SearchNode(filename, RecordID);
    cout << "current/////////" << currentNode << endl;
    if (currentNode < 0) {
        cout << "the record already exist can't add it again!" << endl;
        return -2;
    }
    if (currentNode == 0) {
        BTreeNode btnn = btnn.readNode(filename, 1);
        btnn.isLeaf = true;
        btnn.recArray[0].key = RecordID;
        btnn.recArray[0].reference = Reference;
        btnn.writeNode(filename, 1);
        this->firstEmptyNode = 2;
        return 1;
        exit;

    }
    BTreeNode btn = btn.readNode(filename, currentNode);
    if (btn.recArray[m - 1].key != -1) {
        if (this->firstEmptyNode == -1)
            return -1;
        else{}
         //   currentNode= this->splitNode(filename, RecordID, Reference, currentNode);
        //call split change currentNode
    } else {
        int mx = -1;

        for (int j = 0; j < sizeof(btn.recArray); j++) {
            mx = max(mx, btn.recArray[j].key);
            if (btn.recArray[j].key == -1) {
                btn.recArray[j].key = RecordID;
                btn.recArray[j].reference = Reference;
                break;
            }
        }

        vector<pair<int, int> > vec;
        for (int i = 0; i < m; i++) {
            if (btn.recArray[i].key != -1) {
                vec.push_back(make_pair(btn.recArray[i].key, btn.recArray[i].reference));
            }
        }


        sort(vec.begin(), vec.end());
        int secondLoop = 0;
        for (int i = 0; i < vec.size(); i++) {
            btn.recArray[i].key = vec[i].first;
            btn.recArray[i].reference = vec[i].second;
            secondLoop++;
        }
        for (int i = secondLoop; i < m; i++) {
            btn.recArray[i].key = -1;
            btn.recArray[i].reference = -1;
        }

        btn.writeNode(filename, currentNode);

        if (mx < RecordID) {
            for (int i = 0; i < visitedNodes.size() - 1; i++) {
                BTreeNode bn = bn.readNode(filename, visitedNodes[i]);
                for (int j = 0; j < m; j++) {
                    if (bn.recArray[j + 1].key == -1 || j == m - 1) {
                        bn.recArray[j].key = RecordID;
                        break;
                    }
                }
            }
        }


    }

    return currentNode;
}

int BTree::SearchNode(string filename, int RecordID) {
    visitedNodes.clear();
    int refReturn = 0; //insert root
    BTreeNode btn;
    int first = 1;
    visitedNodes.push_back(1);
    do {
        btn = btn.readNode(filename, first);
        if (btn.isLeaf < 0) {
            return 0;
        }

        for (int i = 0; i < m; i++) {
            cout << btn.recArray[i].key << " " << RecordID << endl;
            if (btn.recArray[i].key == RecordID) {
                return -1;
            }

            if (btn.recArray[i].key > RecordID || btn.recArray[i + 1].key == -1 || i == m - 1) {
                refReturn = btn.recArray[i].reference;
                first = refReturn;
                if (btn.isLeaf == 1) {
                    visitedNodes.push_back(btn.recArray[i].reference);
                }
                break;
            }
        }
    } while (btn.isLeaf == 1);

    return refReturn;
}


int main() {
    // Create a B-tree with a maximum of 5 keys per node
    cout << "enter rows, m ,file name";
//    int rows;cin>>rows;
//    int m; cin>>m;
    string fileName;
    cin >> fileName;
    BTree btree(0, 7);
    btree.CreateIndexFile(fileName, 10);
    btree.DisplayIndexFileContent(fileName);
//    BTreeNode btn;
//    btree.writeNode(fileName,btn,0);
//    btree.readNode(fileName,0);

//    cout<< sizeof(BTreeNode)<<endl;
//    cout<< sizeof(Record)<<endl;
//    cout<< sizeof(BTree)<<endl;
    int ret;
    ret = btree.InsertNewRecordAtIndex(fileName, 3, 12);
    cout << "insert= " << ret << endl;
    btree.DisplayIndexFileContent(fileName);


    //////////////////////////////////////////////////////////
/*    BTreeNode btn(-1);

    btn.recArray[0].key = 7;
    btn.recArray[1].key = -1;
    btn.recArray[2].key = -1;
    btn.recArray[3].key = -1;
    btn.recArray[4].key = -1;

    btn.recArray[0].reference = -1;
    btn.recArray[1].reference = -1;
    btn.recArray[2].reference = -1;
    btn.recArray[3].reference = -1;
    btn.recArray[4].reference = -1;

    btree.writeNode(fileName, btn, 0);


    ////////////////////////////////////////////////////////
    BTreeNode b(1);

    b.recArray[0].key = 3;
    b.recArray[1].key = 7;
    b.recArray[2].key = 10;
    b.recArray[3].key = 15;
    b.recArray[4].key = 30;

    b.recArray[0].reference = 2;
    b.recArray[1].reference = 4;
    b.recArray[2].reference = 5;
    b.recArray[3].reference = 3;
    b.recArray[4].reference = 6;

    btree.writeNode(fileName, b, 1);
    btree.DisplayIndexFileContent(fileName);

*/
    //////////////////////////////////////////////////////////
    /*  BTreeNode n(0,m);

      n.recArray[0].key=1;
      n.recArray[1].key=2;
      n.recArray[2].key=3;
      n.recArray[3].key=-1;
      n.recArray[4].key=-1;

      n.recArray.push_back(120);
      n.recArray.push_back(144);
      n.recArray.push_back(12);
      n.recArray.push_back(-1);
      n.recArray.push_back(-1);

      btree.writeNode(fileName,n, 2);

  */
    //////////////////////////////////////////////////////////
/*    BTreeNode t(0,m);

    btn.keys.push_back(11);
    btn.keys.push_back(12);
    btn.keys.push_back(14);
    btn.keys.push_back(15);
    btn.keys.push_back(-1);

    btn.references.push_back(192);
    btn.references.push_back(72);
    btn.references.push_back(204);
    btn.references.push_back(108);
    btn.references.push_back(-1);

    btree.writeNode(fileName,t, 3);


    //////////////////////////////////////////////////////////
    BTreeNode bt(0,m);

    btn.keys.push_back(5);
    btn.keys.push_back(6);
    btn.keys.push_back(7);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);

    btn.references.push_back(132);
    btn.references.push_back(180);
    btn.references.push_back(24);
    btn.references.push_back(-1);
    btn.references.push_back(-1);

    btree.writeNode(fileName,bt, 4);


    //////////////////////////////////////////////////////////
    BTreeNode bb(0,m);

    btn.keys.push_back(8);
    btn.keys.push_back(9);
    btn.keys.push_back(10);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);

    btn.references.push_back(156);
    btn.references.push_back(168);
    btn.references.push_back(48);
    btn.references.push_back(-1);
    btn.references.push_back(-1);

    btree.writeNode(fileName,bb, 5);

    //////////////////////////////////////////////////////////
    BTreeNode bbtt(0,m);

    btn.keys.push_back(17);
    btn.keys.push_back(18);
    btn.keys.push_back(19);
    btn.keys.push_back(24);
    btn.keys.push_back(30);

    btn.references.push_back(216);
    btn.references.push_back(228);
    btn.references.push_back(84);
    btn.references.push_back(60);
    btn.references.push_back(196);

    btree.writeNode(fileName,bbtt, 6);

    //////////////////////////////////////////////////////////
    BTreeNode nn(-1,m);

    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);

    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);

    btree.writeNode(fileName,nn, 7);


    //////////////////////////////////////////////////////////
    BTreeNode bbbbb(-1,m);

    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);

    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);

    btree.writeNode(fileName,bbbbb, 8);


    //////////////////////////////////////////////////////////
    BTreeNode mm(-1,m);

    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);
    btn.keys.push_back(-1);

    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);
    btn.references.push_back(-1);

    btree.writeNode(fileName,nn, 7);
//*/
/*
//    //////////////////////////////////////////////////////////
//
//
//    //////////////////////////////////////////////////////////
//
//
//
//
//
//
//    keys = {-1, -1, -1, -1, -1};
//    references = {-1, -1, -1, -1, -1};
//    BTreeNode bbbbb(-1,m,keys,references);
//    btree.writeNode(fileName,bbbbb, 8);
//
//
//    keys = {-1, -1, -1, -1, -1};
//    references = {-1, -1, -1, -1, -1};
//    BTreeNode mm(-1,m,keys,references);
//    btree.writeNode(fileName,mm, 9);
//
//    btree.DisplayIndexFileContent(fileName,rows);
//
//
//
//    //cout<<btree.SearchARecord(fileName,30)<<endl; //132
//
//    //cout<<btree.SearchARecord(fileName,6)<<endl;//180*/
//
////    btree.DeleteRecordFromIndex(fileName,7);
////    btree.DeleteRecordFromIndex(fileName,10);
////    btree.DeleteRecordFromIndex(fileName,11);
////    btree.DeleteRecordFromIndex(fileName,15);
////    btree.DisplayIndexFileContent(fileName,rows);
//
////    btree.DeleteRecordFromIndex(fileName,30);
////    btree.DisplayIndexFileContent(fileName,rows);
////
////    cout<<"insert= "<<btree.InsertNewRecordAtIndex(fileName,30,196) <<endl;
////    btree.DisplayIndexFileContent(fileName,rows);

    return 0;
}
