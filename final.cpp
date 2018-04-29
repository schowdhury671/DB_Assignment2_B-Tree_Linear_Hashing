#include <bits/stdc++.h>

#define minDegree 24
#define Lex_comp(veca, vecb) lexicographical_compare(veca.begin(), veca.end(), vecb.begin(), vecb.end())

using namespace std;
		
ifstream iFilePtr;
ofstream oFilePtr;
string iFile;
string oFile;

vector<string> blocks, outputBlock;
vector<int> aux;

int blockPtr;
int numBlocks;
int blockSize;

class BPlusTreeNode {

    vector< vector<int> > keys;
    vector< BPlusTreeNode* > children;
    bool isLeaf;
    int minDeg;
    int numKeys;

public:

    BPlusTreeNode(int _minDeg, bool _isLeaf) {

    	minDeg=_minDeg;
    	isLeaf=_isLeaf;
    	numKeys=0;
    	keys.resize(2*minDeg-1);
    	for(int i=0;i<2*minDeg-1;i++)
    		keys[i].resize(4);
    	children.resize(2*minDeg);
    }

    void insertNonFull(vector<int> k) {

    	int i=numKeys-1;
	    if(isLeaf==true) {
        	while(i>=0 && Lex_comp(keys[i], k)!=0) {
        		keys[i+1]=keys[i];
        		i--;
        	}
	        keys[i+1]=k;
    	    numKeys++;
    	}
    	else {

	        while(i>=0 && Lex_comp(keys[i], k)!=0)
	        	i--;
	        if(children[i+1]->numKeys==2*minDeg-1) {
	            splitChild(i+1, children[i+1]);
            if(Lex_comp(k, keys[i+1])!=0)
            	i++;
        	}
        	children[i+1]->insertNonFull(k);
    	}
    }

    void splitChild(int i, BPlusTreeNode *y) {

    	BPlusTreeNode *z=new BPlusTreeNode(y->minDeg, y->isLeaf);
    	z->numKeys=minDeg-1;

    	for(int j=0;j<minDeg-1;j++)	
        	z->keys[j]=y->keys[j+minDeg];

	    if (y->isLeaf==false) {
	        for(int j=0;j<minDeg;j++)
    	        z->children[j]=y->children[j+minDeg];
    	}
 		
 		y->numKeys=minDeg-1;
	    
	    for(int j=numKeys;j>=i+1;j--)
    	    children[j+1]=children[j];
	    children[i+1]=z;
	    
	    for(int j=numKeys-1;j>=i;j--)
        	keys[j+1]=keys[j];
	    keys[i]=y->keys[minDeg-1];
	    
	    numKeys=numKeys+1;
    }
    
    BPlusTreeNode *search(vector<int> k) {
    	int i = 0;
    	while(i<numKeys && Lex_comp(k, keys[i])!=0)
    		i++;

	    if(k==keys[i])
    	    return this;
	
	    if(isLeaf==true)
        	return NULL;
	
	    return children[i]->search(k);
    }

    int count(vector<int> k) {

    	static int count1 = 0;
    	int i = 0;
    	while(i<numKeys && Lex_comp(k, keys[i])!=0)
    		i++;

	    if(k==keys[i]){
	    	
    	    return count1+1;
    	    
    	}

    	if(isLeaf==true)
        	return 0;

    	return children[i]->count(k);

  
    }
 
friend class BPlusTree;
};

class BPlusTree {

    BPlusTreeNode *root;
    int minDeg;
public:
    BPlusTree() {

    	root=NULL;
    	minDeg=24;
  	
    }

    BPlusTreeNode* search(vector<int> k) {
    	return (root == NULL)?NULL:root->search(k);
    }

    int count(vector<int> k) {
    	return (root == NULL)?0:root->count(k);
    }

    void insert(vector<int> k) {

    	if(root==NULL) {
    		
	        root = new BPlusTreeNode(minDeg, true);
        	root->keys[0]=k;
        	root->numKeys=1;
        	aux.push_back(k[0]);
    	}
    	else {

	        if(root->numKeys==2*minDeg-1) {

	            BPlusTreeNode *s=new BPlusTreeNode(minDeg, false);
	            aux.push_back(k[0]);
	            s->children[0]=root;
            	s->splitChild(0, root);
	            int i=0;
            	if(Lex_comp(k, s->keys[0])!=0)
                	i++;
            	s->children[i]->insertNonFull(k);
	            root=s;
    	    }
        	else {
        		root->insertNonFull(k);
        		aux.push_back(k[0]);
        	}
    	}

    }
};

BPlusTree tree;

void handle_BPlusTree(string line) {

	vector<int> record;
	vector<int>::iterator it;

	int value = atoi (line.c_str());
		record.push_back(value);

	//cout<<"Line in handle = "<<line<<endl;
	
	tree.insert(record);
	
}


void find_func_helper(string line) {

	//cout<<"FIND FUNCTION IS CALLED"<<endl;

	vector<int> record1;

	int value = atoi (line.c_str());

	// cout<<"value = "<<value<<endl;
	record1.push_back(value);
	
	if(tree.search(record1)){

		oFilePtr<<"YES"<<"\n";
		return;
	}
	else {
		oFilePtr<<"NO"<<"\n";
		return;
	}
	
}


void count_helper(string line) {

	vector<int> record1;

	int value = atoi (line.c_str());

	//cout<<"value = "<<value<<endl;
	record1.push_back(value);

	oFilePtr<<tree.count(record1)<<"\n";

	
}

void count(vector < int> &aux, int value){

	int mycount = std::count (aux.begin(), aux.end(), value);
	oFilePtr<<mycount<<"\n";

}

void range(vector < int> &aux, vector < int> &val){

	int count=0;
	vector <int> :: iterator it;
	for(it=aux.begin();it!=aux.end();it++){

		if((*it >= val[0])&& (*it <= val[1])){
			count++;
		}
	}

	oFilePtr<<count<<"\n";


}

void intermediate(vector<string> &blocks){

	//cout<<"intermediate called "<<endl;

	int iter=0;

	vector <string>:: iterator it;
	string line;
	for(it=blocks.begin();it!=blocks.end();it++){

		iter++;
		while(iter==blockPtr+1){

				return;

		}

		line = *it;

		std::size_t pos1 = line.find("INSERT");
		if(pos1 != -1){

			line = line.substr (7);
			handle_BPlusTree(line);
			
		}

		std::size_t pos2 = line.find("FIND");
		if(pos2 != -1){

			line = line.substr (5);
			//cout<<line<<endl;
			find_func_helper(line);
		}

		std::size_t pos3 = line.find("COUNT");
		if(pos3 != -1){

			line = line.substr (6);
			const char * ch = line.c_str();
			int val = atoi(ch);

			count(aux,val);
		}

		vector<int> record;
			

		std::size_t pos4 = line.find("RANGE");
		if(pos4 != -1){

			line = line.substr (6);
			stringstream linestream(line);
			string curnum;

			while(getline(linestream, curnum, ' ')) {
				int value = atoi (curnum.c_str());
				record.push_back(value);
			}

			range(aux,record);
		}

	}

}

void readFile(){

	string line;

	while(getline(iFilePtr, line)) {

		if(blockPtr==blockSize*(numBlocks-1)) {

			intermediate(blocks);
			blockPtr=0;

		}

		blocks[blockPtr++]=line;

	}

	intermediate(blocks);

}


int main(int argc, char* argv[]){

	if(argc!=5) {

		cout<<"Invalid number of arguments!\n";
		cout<<"Usage: <Input file> <Number of blocks>";
		cout<<" <Block size>  <output file>\n";
		return 0;
	}

	iFile = argv[1];

	numBlocks = atoi(argv[2]);

	blockSize = atoi(argv[3]);

	oFile = argv[4];

	iFilePtr.open(iFile.c_str());
	oFilePtr.open(oFile.c_str());

	if(numBlocks <= 1){
		cout<<"Atleast 2 blocks are required"<<endl;
		return 0;
	}

	blocks.resize(blockSize*(numBlocks-1));
	outputBlock.resize(blockSize);
	blockPtr=0;

	readFile();
	sort (aux.begin(), aux.end());

	iFilePtr.close();
	oFilePtr.close();

	return 0;
}