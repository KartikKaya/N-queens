#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#include<time.h>
#include<utility>



using namespace std;

#define SIZE 10


std::pair<int,int> * Q;
std::pair<int,int> * E;
int H;
void generate_random_square(char B[][SIZE]);
int cal_heu(char B[][SIZE]);

//hreuristic array
char T[SIZE][SIZE];

int Harr[SIZE][SIZE];
int Current_global_Heu;

void generate_random_square(char B[][SIZE]){


	/* initialize random seed: */
	srand (time(NULL));
	int ran=-1;		

	/*intialise board with random queens*/
	for(int i=0; i<SIZE; i++){	
		ran=rand() % SIZE;
			for(int j=0;j<SIZE;j++){
				
				if(ran==j){
				B[j][i]='Q';
				T[j][i]='Q';
				Q[i]=make_pair(j,i);	
				}else{
				B[j][i]='0';
				T[j][i]='0';
					
			}			
		}		
	
	}	
}


int cal_heu(char Z[][SIZE]){

	H=0;
	int k=0;
	int l=0;
	//n-1
	for(int i=0;i<SIZE-1;i++){
			
		k=Q[i].first;
		l=Q[i].second;

		//Horizontal attack
		l++;
		 while(l<SIZE){
			if(Z[k][l]=='Q'){	
			
			H++;
			}	
			
		 l++; 
		}
		

		k=Q[i].first;
		l=Q[i].second;
		//Top Right attack
		k--;
		l++;
		while(k>-1 && l<SIZE){
			if(Z[k][l]=='Q'){
			H++;
			}	
			k--;
			l++;
			
		}

			
	    k=Q[i].first;
		l=Q[i].second;
		//Top bottom attack
		k++;
		l++;
		while(k<SIZE && l<SIZE){
			if(Z[k][l]=='Q'){
			H++;
			}	
			k++;
			l++;
			
		}

		

	}	
	
	return H;
	
}








void generate_heu_matrix(char B[][SIZE]){
	
	int tmp_i=0;
	int tmp_j=0;
	
for(int i=0; i<SIZE;i++){ 
		for(int j=0;j<SIZE;j++){
		
	T[i][j]=B[i][j];
		}
	}
	
for(int i=0; i<SIZE;i++){
	
	tmp_i=Q[i].first;
	tmp_j=Q[i].second;
	
	T[Q[i].first][Q[i].second]='0';
	
	
	for(int j=0;j<SIZE;j++){	
	T[j][i]='Q';
	Q[i]=make_pair(j,i);
	Harr[j][i]=cal_heu(T);		
	T[j][i]='0'	;		
	}
 Q[i]=make_pair(tmp_i,tmp_j);	
 T[tmp_i][tmp_j]='Q';
	
	
}	
	
	
}




void make_move(char B[][SIZE],int eql_ran){
	
	
	int i=E[eql_ran].first;
	int j=E[eql_ran].second;
	
	
	for(int k=0; k<SIZE; k++){
	
		B[k][j]='0';
	}
	
	B[i][j]='Q';
	Q[j]=make_pair(i,j);
	
	
	for(int i=0; i<SIZE;i++){ 
		for(int j=0;j<SIZE;j++){
		
	T[i][j]=B[i][j];
		}
	}
	
	
}




void extract_min_h(int &size , int &min_heu){
	
	int min=Harr[0][0];
	int k=0;
	
	for(int i=0; i<SIZE; i++){	
		
		for(int j=0;j<SIZE;j++){
				
			if(min >= Harr[i][j]){
			min=Harr[i][j];		
				
			}
			
		}
		

	}
	
	for(int i=0; i<SIZE; i++){	
		
		for(int j=0;j<SIZE;j++){
				
			if(Harr[i][j]==min){
			E[k]=make_pair(i,j);
				k++;
			}
			
		}
		

	}
size=k;
min_heu=min;	
}



void print(char B[][SIZE]){
	for(int i=0; i<SIZE; i++){	
		
			for(int j=0;j<SIZE;j++){
				
				cout<<B[i][j]<<"   ";
			}
		
		cout<<endl;
	}
	
		
	
}




int main (int argc, char* argv[]) {


	int num_restart=-1;
	int total_num_steps=0;
	int steps_for_last_iteration=0;
	//Board Array
	char B[SIZE][SIZE];
	//Queen Placement Pairs
	Q = new pair<int,int> [SIZE];
	//Heuristic are values are equal at these places
	E = new pair<int,int> [SIZE*SIZE];

   //Intialise Gobal heuristic
	Current_global_Heu=-1;
	//extract MIN heuristc value and number of tiles with the same valle
	int size=0,min_heu=-2;
	
	while(Current_global_Heu){
		
			//Generate Random Square with Queen Placements
			generate_random_square(B);
			//Calculate Heuristic value for the board and make it currrent global heuristic value
			Current_global_Heu=cal_heu(B);
             num_restart++;
            steps_for_last_iteration=0;
      while(Current_global_Heu){
			//Generate Heurtisic martix for next move
			generate_heu_matrix(B);


			//extract tiles with mininum heuristic values
			extract_min_h(size, min_heu);
		  
            if(min_heu<Current_global_Heu){
			//select one of those tiles to make the next move
			srand (time(NULL));
			int eql_ran= rand()%size;
             
			
			//make move to best possible square	
		    
			make_move(B,eql_ran);
			total_num_steps++;
			steps_for_last_iteration++;
			Current_global_Heu=	min_heu;
				
			}else{
				
			break;
				
			}
		  
	  }


	}
	
	
	
	
cout<<"NUMBER OF RESTART REQUIRED : "<<num_restart<<endl;
cout<<"TOTAL NUMBER OF STEPS (INCLUDING ALL RESTARTS) : "<<total_num_steps<<endl;
cout<<"TOTAL NUMBER OF STEPS FOR LAST SUCCESSFUL ITERATION: "<<steps_for_last_iteration<<endl;
cout<<"*********SOLUTION FOR SIZE  "<<SIZE<<"-QUEENS******"<<endl;
print(B);	
	

	
}
	
	
	
	
	



