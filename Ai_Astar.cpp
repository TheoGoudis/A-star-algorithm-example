//Vlachogkountis Theofilos (Theo Goudis)
//A* search algorithm
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef struct Node Node;
struct Node{
	int cost;	//cost for each move
	int heur;	//heuristic (sum of vertical distances of out oof position elements )
	int sum;		//cost + heuristic
	int check;	//flag for expansion. if 1 then the node has been expanded
	string N[4][4];	//board state
	Node *next;		//next node in central array
	Node *par;		//parent node
	Node(){		//struct constructor
		cost=0;
		heur=0;
		sum=0;
		check=0;
		next=NULL;
		par=NULL;
	}
};

int solved=0;		//flag for optimal path finding. 1 if found
Node* head;		//central array first node
Node* tail;		//central array last node
Node* minn;		//pointer to node with lowest sum (cost + heuristic)

int firstBoard();		
void printBoard(Node *T);
void calcHeuristic(Node *T);
int rotateBoard(Node *T, int rotation);
void findMin();
void expand();
void printPath();

int main(int argc, char** argv){
	
	int i=firstBoard();
	if(i==1)
		return 0;
	
	cout<<"You entered:"<<endl;
	printBoard(head);
	cout<<endl;
	
	
	while(solved==0){		//flag for found optimal path
		findMin();			//performing A* search. find min sum and then expand until optimal path is found
		expand();
	}
	
	printPath();
		
	return 0;
}

int firstBoard(){		//this func creates the firt board state (first node) based on the user input. It also checkes for wrong iput.
	int cR=0;
	int cG=0;
	int cB=0;
	int cY=0;
	Node* S=new Node;
	string n;
	
	cout<<"Goal:"<<endl<<" R R R R"<<endl<<" G G G G"<<endl<<" B B B B"<<endl<<" Y Y Y Y"<<endl<<endl;
	cout<<"Create the 4x4 board. You have to to give 4xR, 4xG, 4xB and 4xY. (16values one after the other eg:RYRGRRGBGGBYBBYY) : ";
	cin>>n;
	cout<<endl<<endl;
	int x=0;
	for(int j=0;j<4;j++){
		for(int i=0;i<4;i++){
			if(n[x]=='R')
				cR++;
			else if(n[x]=='G')
				cG++;
			else if(n[x]=='B')
				cB++;
			else if(n[x]=='Y')
				cY++;
			else{
				cout<<"Error: Not acceptable value  "<<n[x]<<endl;
				return 1;
			}
			S->N[i][j]=n[x];
			x++;
		}
	}
	if(cR!=4||cG!=4||cB!=4||cY!=4){
		cout<<"Error: Wrong input. You have to to give 4xR, 4xG, 4xB and 4xY values"<<endl;
		return 1;
	}
	
	calcHeuristic(S);
	S->sum=S->heur;
	head=S;
	tail=S;
	minn=S;
	return 0;
}

void printBoard(Node *T){		//func that prints out the board state of a node T
	for(int j=0;j<4;j++){
			for(int i=0;i<4;i++){
				cout<<" "<<T->N[i][j];
			}
			cout<<endl;
	}
	cout<<"Heuristic: "<<T->heur<<endl;
}

void calcHeuristic(Node *T){			//this func calculates the heuristic value of a node. heuristic = SUM(vertical topological distances of nodes from their acceptable positions)
	T->heur=0;
	for(int j=0;j<4;j++){
		for(int i=0;i<4;i++){
			if(T->N[i][j]=="R")
					T->heur+=abs(j-0);
			else if(T->N[i][j]=="G")
					T->heur+=abs(j-1);
			else if(T->N[i][j]=="B")
					T->heur+=abs(j-2);
			else if(T->N[i][j]=="Y")
					T->heur+=abs(j-3);
		}
	}
}

int rotateBoard(Node *T, int rot){	//this func performs a rotation to the board of a node T  {rot=roation, values 0<=rotation<=15 for row/column rotation}
	string temp[4];
	int i;
	
	if(rot==0||rot==2||rot==4||rot==6){ //row rotation right
		if(rot==0)
			i=0;
		else if(rot==2)
			i=1;
		else if(rot==4)
			i=2;
		else if(rot==6)
			i=3;
		temp[0]=T->N[0][i];
		temp[1]=T->N[1][i];
		temp[2]=T->N[2][i];
		temp[3]=T->N[3][i];
		T->N[0][i]=temp[3];
		T->N[1][i]=temp[0];
		T->N[2][i]=temp[1];
		T->N[3][i]=temp[2];
	}
	else if(rot==1||rot==3||rot==5||rot==7){		//row rotation left
		if(rot==1)
			i=0;
		else if(rot==3)
			i=1;
		else if(rot==5)
			i=2;
		else if(rot==7)
			i=3;
		temp[0]=T->N[0][i];
		temp[1]=T->N[1][i];
		temp[2]=T->N[2][i];
		temp[3]=T->N[3][i];
		T->N[0][i]=temp[1];
		T->N[1][i]=temp[2];
		T->N[2][i]=temp[3];
		T->N[3][i]=temp[0];
	}
	else if(rot==8||rot==10||rot==12||rot==14){		//column rotation up
		if(rot==8)
			i=0;
		else if(rot==10)
			i=1;
		else if(rot==12)
			i=2;
		else if(rot==14)
			i=3;
		temp[0]=T->N[i][0];
		temp[1]=T->N[i][1];
		temp[2]=T->N[i][2];
		temp[3]=T->N[i][3];
		T->N[i][0]=temp[1];
		T->N[i][1]=temp[2];
		T->N[i][2]=temp[3];
		T->N[i][3]=temp[0];
	}
	else if(rot==9||rot==11||rot==13||rot==15){		//column rotation down
		if(rot==9)
			i=0;
		else if(rot==11)
			i=1;
		else if(rot==13)
			i=2;
		else if(rot==15)
			i=3;
		temp[0]=T->N[i][0];
		temp[1]=T->N[i][1];
		temp[2]=T->N[i][2];
		temp[3]=T->N[i][3];
		T->N[i][0]=temp[3];
		T->N[i][1]=temp[0];
		T->N[i][2]=temp[1];
		T->N[i][3]=temp[2];
	}
	else{
		cout<<"Error:rotateBoard wrong rot value"<<endl;
		return 1;
	}
	return 0;
}

void findMin(){		//func that finds the node with the lowest sum (heuristic+cost). needed for A* search algorithm
	int minT=1000000000;	//a very high value, just to catch the first sum comparison
	Node* S=head;
	
	minn=NULL;
	do{
		if(S->check==0){
			if(S->sum<minT){
				minn=S;
				minT=minn->sum;
			}
		}
		S=S->next;
	}while(S!=NULL);
}

void expand(){		//func that expands the minn node (node with lowest sum). for each node we create 16 child nodes, each for every possible rotation
	if(minn->heur==0)
		solved=1;
	else{
		minn->check=1;
		for(int i=0; i<16; i++){
			Node* temp=new Node;
			for(int j=0; j<4; j++)
				for(int z=0; z<4; z++)
					temp->N[j][z]=minn->N[j][z];
			rotateBoard(temp,i);
			temp->par=minn;
			calcHeuristic(temp);
			temp->cost=minn->cost+1;
			temp->sum=(temp->heur)+(temp->cost);
			tail->next=temp;
			tail=tail->next;
			temp=NULL;
		}
	}
}

void printPath(){		//TODO. reverse the print. reverse (up step) the parent-child pointers and then slide down.
	Node* temp=minn;
	cout<<"Moves needed to achieve final goal: "<<temp->cost<<endl<<"Printing the path. From Goal state to Start state"<<endl;
	do{
	printBoard(temp);
	temp=temp->par;
	}while(temp!=NULL);
}
