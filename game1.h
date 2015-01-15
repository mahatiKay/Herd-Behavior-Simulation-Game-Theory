#include<stdio.h>
//#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include "postfix_eval.h"
#include "in_postfix.h"


#define N 200
#define M 20

//#define NR 30
#define W 5


#define alpha 1  //spread parameter
#define beta 0.6 //probability of choosing highest payoff

//#define herd_percent 10

#define opt_percent 5
#define rand_percent 5

struct info
{
	int signal;
	double payoff;
	int choice;
};

struct player
{
	int ws;
	int type;
	struct info *window;
};

double assets[M],sorted_assets[M][2],reduced_assets[M][M];
int reduced_lim;
int complement_asset[M];
int current_history[M];
struct player players[N];
int Window[N];
int threshold;
int NR, herd_percent;



void refresh_current_history()
{
	int i=0;
	for(i=0;i<M;i++)
		current_history[i]=0;
}

void reinitialize()
{
	int i;
	for(i=0;i<N;i++)
	{
		players[i].type = 0;
		players[i].ws=0;
	}
}

void generate_player_types()  //  Assignes [1]Optimizer [2]Imitator [3]Randomizer 
{
	int i=0,r;
	int opt_lim=N*opt_percent/100;
	int rand_lim=N*rand_percent/100;
	for(i=0;i<opt_lim;i++)
	{
		r = rand()%N;
		if(players[r].type==0)
			players[r].type=1;
		else 
			i--;
		
	}
	for(i=0;i<rand_lim;i++)
	{
		r = rand()%N;
		if(players[r].type==0)
			players[r].type=3;
		else 
			i--;
		
	}
	for(i=0;i<N-opt_lim-rand_lim;i++) // Imitator types are set.
	{
		r = rand()%N;
		if(players[r].type==0)
			players[r].type=2;
		else 
			i--;
		
	}
}

void disp_player_types()
{
	int i=0;
	printf("\n\n Player Type Assignment:");
	for(i=0;i<N;i++)
		printf("\nPlayer[%d] Type--> %d",i,players[i].type);
}
/*
 void generate_windows() // Generate the windows for the players
 {
 int i;
 for(i=0;i<N;i++)
 Window[i]=5;
 }
 */
void initialize_windows() //Initializes the windows for each player
{
	//generate_windows();
	int i;
	for(i=0;i<N;i++)
	{
		players[i].ws=0;
		players[i].window = (struct info*) malloc(W * sizeof(struct info));
		//printf("Player %d -> %d\n",i,W);
		players[i].type=0;
	}
}   
/*
 double  evaluate_payoff_function( char func[])
 {
 int payoff=0;
 char expr[200][20];
 for(i=0;
 return payoff;
 }
 */

void generate_reduced_assets()
{
	int i,k=1,j;
	reduced_assets[0][0]=sorted_assets[0][0];
	reduced_assets[0][1]=1;
	reduced_assets[0][2]=sorted_assets[0][1];
	for(i=1;i<M;i++)
	{
		if(sorted_assets[i-1][0]==sorted_assets[i][0])
		{
			reduced_assets[k][1]++;
			reduced_assets[k][(int)reduced_assets[k][1]+1]=sorted_assets[i][1];
		}
		else
		{
			reduced_assets[k][0]=sorted_assets[i][0];
			reduced_assets[k][1]=1;
			reduced_assets[k++][2]=sorted_assets[i][1];
			
		}
	}
	reduced_lim=k;
	for(i=0;i<reduced_lim;i++)
	{
		printf("\n%f  %d   ",reduced_assets[i][0],(int)reduced_assets[i][1]);
		for(j=0;j<reduced_assets[i][1];j++)
			printf("%d   ",(int)reduced_assets[i][j+2]);
		printf("\n");
	}
}

void assign_assets_payoff() //Generates the payoff distribution for assets
{
	int i,k=0,j=0,l;
	srand(time(NULL));
	char* function=(char*)malloc(sizeof(char)*100);
	function=in_postfix();
	
	printf("\nsorted :");
	for(i=0;i<M;i++)
	{       
		//double  r = rand()/(float)RAND_MAX;
		assets[i] = postfix_eval(function,i);
		
		for(j=0;j<k;j++)
		{
			if(sorted_assets[j][0]>assets[i])
			{
				for(l=k;l>j;l--)
				{
					sorted_assets[l][0]=sorted_assets[l-1][0];
					
					sorted_assets[l][1]=sorted_assets[l-1][1];
				}
				break;
			}
		}
		sorted_assets[j][0]=assets[i];
		
		sorted_assets[j][1]=i;
		printf("%f  %f\n",sorted_assets[j][0],sorted_assets[j][1]);
		k++;
	}
	generate_reduced_assets();
	
}

void disp_payoff_distribution() //Displays the payoff distribution of the assets
{
	int i;
	printf("\n\n Asset distribution : \n");
	for(i=0;i<M;i++)
		printf("Asset %d --> %0.2f\n",i,assets[i]);
}

int choose_index(double pay, int pos)
{
	int i,pivot,r,lim=0;
	for(i=0;i<reduced_lim;i++)
		if(pay==reduced_assets[i][0])
			break;
	
	pivot = i;
	
	if( ( pivot==0 && pos==-1 ) || ( pivot==reduced_lim-1 && pos==1) )
		pos=0;
	
	lim = reduced_assets[pivot+pos][1];
	r = rand()%lim;
	return (int)reduced_assets[pivot+pos][r+2];
}


int findmax(int p) //Returns the max payoff index of a player
{
	
	int i,index=-1;
	double max=-1;
	for(i=0;i<players[p].ws;i++)
		if(players[p].window[i].payoff > max)
		{ 
			max = players[p].window[i].payoff;
			index=i;
		}
	return index;
}

int generate_signal(int p) //Returns the signal for a player
{
    //First round - Some random signal generated
    if(players[p].ws==0)
    {
        double  r = rand()/(float)RAND_MAX;
        r*=M;
        return (int)r;
    }
    //Other rounds - Signal generated based on History (looking at max-payoff)
    else
    {     
		int maxindex = findmax(p);
		double  r = rand()/(float)RAND_MAX;
		if(r < beta)
		{
			return players[p].window[maxindex].choice;
		}
		else if((int)(r*100)%2 == 0) return choose_index(players[p].window[maxindex].payoff,1);
		else return choose_index(players[p].window[maxindex].payoff,-1);
    }
}
double findmin(int p) //Returns the index of the asset with least payoff for a player
{
	int i,min=999,index=-1;
	for(i=0;i<players[p].ws;i++)
		if(players[p].window[i].payoff < min)
		{ 
			min = players[p].window[i].payoff;
			index=i;
		}
	return index;
}

void optimize_window(int p,int signal,int decision) //Optimizes the values in the window of a player using different strategies 
{
	int minindex;
	//Till window size not full
	if(players[p].ws<W)
	{
		players[p].window[players[p].ws].signal=signal;
		players[p].window[players[p].ws].payoff=assets[decision];
		
		players[p].window[players[p].ws].choice=decision;
		players[p].ws++;
	}
	//Once window is full
	else
	{
		minindex=findmin(p);
		if(players[p].window[minindex].payoff<assets[decision])
		{
			players[p].window[minindex].signal=signal;
			players[p].window[minindex].payoff=assets[decision];
			players[p].window[minindex].choice=decision;
			
		}
	}   
}

int randomizer_cost_function(int p,int signal)  // Experimental decision
{
	int  decision = rand()%M;
	return decision;
}

int imitator_cost_function(int p,int signal)  // If (HERD) --> Follow ; ELSE --> Signal
{
	int decision=-1,max=0,i;
	for(i=0;i<M;i++)
	{
		if(current_history[i]>=threshold && current_history[i]>max)
		{    
			max = current_history[i];
			decision = i;
		}
	}
	if(decision==-1) decision = signal;
	return decision;
	
}

// 5 Level Checks 

int payoff_check(int p,int signal)  // Level 1: Checks if Payoff known 
{
	int i;
	for(i=0;i<players[p].ws;i++)
		if(players[p].window[i].choice == signal)
			return 1;
	return 0;
}

int signal_check(int p, int signal) // Level 2: Checks if Signal received before
{
	int i;
	for(i=0;i<players[p].ws;i++)
		if(players[p].window[i].signal == signal)
			return 1;
	return 0;
}

int chosen_already_check(int signal) // Level 3: Checks if chosen by someother player
{
	if(current_history[signal]!=0)
		return 1;
	return 0;
}

int herd_check_decision()            // Level 4: If (herd formed) return decision else -1
{
	int decision=-1,max=0,i;
	for(i=0;i<M;i++)				// If (HERD) --> Follow ; ELSE --> Signal
	{
		if(current_history[i]>=threshold && current_history[i]>max)
		{    
			max = current_history[i];
			decision = i;
		}
	}		
	return decision;
}

int randomized_decision(int p,int signal)
{
	int i,k=0,decision=-1;
	int temp_asset[M];
	for(i=0;i<M;i++)
	{
		temp_asset[i] = i;
		complement_asset[i]=0;
	}
	
	for(i=0;i<players[p].ws;i++)
		temp_asset[players[p].window[i].choice] = -1;
	
	for(i=0;i<M;i++)
		if(temp_asset[i]!=-1)
			complement_asset[k++] = temp_asset[i];
	
	if(k!=M)
		decision = complement_asset[rand()%k];
	else 
		decision=signal;
	return decision;
}

int optimizer_cost_function(int p,int signal)
{
	int decision = -1; 
	
	if(payoff_check(p,signal))            // Level 1: If (payoff seen)-->Level 4  
	{
		decision = herd_check_decision();
	}
	else if(signal_check(p,signal))       // Level 2: If (signal seen)--> decide
	{
		decision = signal;
	}
	else if(chosen_already_check(signal)) // Level 3: If (chosen before)--> decide
	{
		decision = signal;
	}
	else decision = herd_check_decision();// Level 4: If (herd) --> follow
	
	if(decision == -1) decision = randomized_decision(p,signal); // Level 5: If (ALL filters FAIL) --> choose signal
	
	return decision;
}

int cost_function(int p, int signal)      // Returns the decision of a player in a round
{
    int i,max=0,index=-1,decision=-1;
	switch(players[p].type)
	{
		case 1:
			decision=optimizer_cost_function(p,signal);
			break;
		case 2:
			decision=imitator_cost_function(p,signal);
			break;
		case 3:
			decision=randomizer_cost_function(p,signal);
			break;
	}
	return decision;
}

void decision(int p,int signal)          // Makes a decision and changes the window of a player for one round
{
	//decide asset
	int decision=-1;
	decision = cost_function(p,signal);  // calls function based on Player Type
	optimize_window(p,signal,decision);  // adding decision to History "window"
	current_history[decision]++;         // decision reflected on current round "game board"
	
}
void display_hist()                      // Displays Game Round Outcome as Histogram
{
	int i,j;
	for(i=0;i<M;i++)
	{
		printf("\n Asset %d :",i);
		for(j=0;j<current_history[i];j++)
			printf("|");
	}
	printf("\n");
}

int herd_count()
{
	int i,herd=0,no_of_herds=0;
	
	for(i=0;i<M;i++)
	{
		//printf("\n curr hist: %d thresh:%d",current_history[i], threshold);
		if(current_history[i] > threshold)
		{
			herd+=current_history[i];
			no_of_herds++;
		}
	}
	//printf("\nHERD SUM: %d",herd);
	if(herd==0) return 0;
	else return herd/no_of_herds;
	
}

/*float not_herd_count()
 {
 int i,not_herd=0,no_of_not_herds=0;
 
 for(i=0;i<M;i++)
 {
 //printf("\n curr hist: %d thresh:%d",current_history[i], threshold);
 if(current_history[i] < threshold && current_history[i]!=0)
 {
 not_herd+=current_history[i];
 no_of_not_herds++;
 }
 }
 //printf("\nHERD SUM: %d",herd);
 if(not_herd==0) return 0;
 else return (float)not_herd/no_of_not_herds;
 
 }*/


void initialize_game()
{
	assign_assets_payoff();
    disp_payoff_distribution(); 
	
    initialize_windows(); // assignning Herd defining Threshold.
	
}
int play_game1(int nr, int hp)                         // The function to play the game
{
	NR = nr;
	herd_percent = hp;
	
	threshold=fabs(N*herd_percent/100.0);
	generate_player_types();
	
    int i,signals[N],r;
	
	
	for(r=0;r<NR;r++)
	{
		refresh_current_history();
		for(i=0;i<N;i++)                     // Playing Rounds 1 and 2
		{
			signals[i] = generate_signal(i); // generating signal for each player
			decision(i,signals[i]);			 // decision made by each player based on Player Type
		}
	}
	//printf("\nGame done. %d %d %d",opt_percent,rand_percent,100-opt_percent-rand_percent);
	return herd_count();
	
}


/*float* play_game2(int op, int rp)                         // The function to play the game
 {
 opt_percent=op;
 rand_percent=rp;
 generate_player_types();
 
 int i,signals[N],r;
 float *value=(float*)malloc(sizeof(float)*NR*2);
 
 for(r=0;r<NR;r++)
 {
 refresh_current_history();
 for(i=0;i<N;i++)                     // Playing Rounds 1 and 2
 {
 signals[i] = generate_signal(i); // generating signal for each player
 decision(i,signals[i]);			 // decision made by each player based on Player Type
 }
 
 value[2*r] = herd_count();
 value[2*r+1] = not_herd_count();
 }
 //printf("\nGame done. %d %d %d",opt_percent,rand_percent,100-opt_percent-rand_percent);
 return value;
 
 }*/

/*int main()
 {
 printf("\n\nGame: \n\nAssets : %d\n", M);
 printf("Players : %d\n", N);
 printf("No. of Rounds: %d\n",NR);
 play_game();
 return 0;
 }*/   

