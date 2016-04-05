#include <fstream>
// #include "apstring.h"
// #include "apstring.cpp"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std; 	//introduces namespace std

const int maxVotes=100;
const int states=50;
ofstream dataout;

struct state
{
	string name;
	int votes;
	double power;
	int population;
};

int voteSum(int votes[states]);
int sum(int pass[states]);
void calculateBanzhaf(int votetype[maxVotes], int required, double power[states]);
void calculateBanzhafOveride(int votetype[maxVotes], int required, double power[maxVotes]);
int pass(int vote[states]);
void printState(state a);
void printStateFile(state a);
void printHeader();
void printHeaderFile();
double combin(int n, int r);
int worst(state UnitedStates[states]);

int main( void )
{
	const string stateNames[states] = {
    "Alabama","Alaska","Arizona","Arkansas","California","Colorado","Connecticut","Delaware","Florida",
    "Georgia","Hawaii","Idaho","Illinois","Indiana","Iowa","Kansas","Kentucky","Louisiana","Maine",
    "Maryland","Massachusetts","Michigan","Minnesota","Mississippi","Missouri","Montana","Nebraska","Nevada","New Hampshire",
    "New Jersey","New Mexico","New York","North Carolina","North Dakota","Ohio","Oklahoma","Oregon","Pennsylvania","Rhode Island",
    "South Carolina","South Dakota","Tennessee","Texas","Utah","Vermont","Virginia","Washington","West Virginia","Wisconsin",
    "Wyoming"};
	int totalVotes;
	int required;
	int worstRep;
	const long populations[states]={4447100, 626932, 5130632, 2673400, 33871648, 4301261, 3405565, 783600, 15982378,
	8186453, 1211537, 1293953, 12419293, 6080485, 2926324, 2688418, 4041769, 4468976, 1274923,
	5296486, 6349097, 9938444, 4919479, 2844658, 5595211, 902195, 1711263, 1998257, 1235786,
	8414350, 1819046, 18976457, 8049313, 642200, 11353140, 3450654, 3421399, 12281054, 1048319,
	4012012, 754844, 5689283, 20851820, 2233169, 608827, 7078515, 5894121, 1808344, 5363675,
	493782};
	double powertype[maxVotes];
	int votes[states];
    int votetype[maxVotes];
    state UnitedStates[states];//create the united states
	for(int loop=0; loop<states; loop++)
	{
		votes[loop]=1;
		UnitedStates[loop].votes=votes[loop];
		UnitedStates[loop].name=stateNames[loop];
		UnitedStates[loop].population=populations[loop];
	}//initiallize each phase
//initialization phase of the program - sets all states to 1 vote and tells the population values
	int checkSanity=0;
	do
	{
		checkSanity++;
	    for(int loop=0; loop < maxVotes; loop++)
	    {
    		votetype[loop]=0;
	    	powertype[loop]=0;
	    }//initialize power
		for(int loop=0; loop<states; loop++)
		{
			UnitedStates[loop].power=0;
			votetype[votes[loop]]++;
		}//initiallize each phase
		totalVotes=voteSum(votetype);
		required=totalVotes-totalVotes/2;
		calculateBanzhaf(votetype,required,powertype);
		required=totalVotes-totalVotes/3;
		calculateBanzhafOveride(votetype,required,powertype);
		for(int loop=0; loop<states; loop++)
		{
			UnitedStates[loop].power=powertype[UnitedStates[loop].votes];
		}//input power with each state
		if (checkSanity%10==9)
		{
			for(int loop=0; loop<states; loop++)
			{
				cout.setf(ios::fixed);
				printState(UnitedStates[loop]);
			}
			cout<<"Votes = "<<totalVotes<<endl;
		}//sanity checker
		dataout.open("VotePow.txt", ios::app);
		worstRep=worst(UnitedStates);
		UnitedStates[worstRep].votes++;
		votes[worstRep]++;
		dataout.close();
	}while(totalVotes<435);
	dataout.open("VotePow.txt", ios::app);
	for(int loop=0; loop<states; loop++)
		{
			if (loop%10==0)
			{
				cin.ignore(80,'\n');
				printHeader();
				printHeaderFile();
			}//every 10 lines
			cout.setf(ios::fixed);
			dataout.setf(ios::fixed);
			printState(UnitedStates[loop]);
			printStateFile(UnitedStates[loop]);
		}
	dataout.close();
	return 0;
}

int pass(int vote[states])
{
	int tally=0;
	for(int loop=1; loop<maxVotes; loop++)
		tally+=vote[loop]*loop;
	return (tally);
}//did the vote pass?

int voteSum(int votes[maxVotes])
{
	int tally=0;
	for(int loop=0; loop<maxVotes; loop++)
		tally+=votes[loop]*loop;
	return tally;
}//voteSum

int sum(int pass[states])
{
	int tally=0;
	for(int loop=0; loop<states; loop++)
		tally+=pass[loop];
	return tally;
}//sum

void calculateBanzhaf(int votetype[maxVotes], int required, double power[maxVotes])
{
	int x;
	int i[maxVotes];
	double y;
	for(int a=0; a<maxVotes; a++)
		i[a]=0;
	while(i[1]<votetype[1]+1)
	{
		i[maxVotes-1]++;
		if(i[maxVotes-1]>votetype[maxVotes-1])
		{
			i[maxVotes-1]=0;
			i[maxVotes-2]++;
			for(int j=maxVotes-2; j>=2; j--)
				if(i[j]>votetype[j])
				{
					i[j]=0;
					i[j-1]++;
				}
		}//if the first exceeds
		x=pass(i);
		if(x>=required)
		{
			for(int loop=0; loop<maxVotes; loop++)
				if(i[loop]>=1)
				{
					if((x-loop)<required)
					{
						y=1;
						for (int loop1=1; loop1<loop; loop1++)
						{
							if ((votetype[loop1]>1)&&(i[loop1]>0))
								y*=combin(votetype[loop1],i[loop1]);
						}
						if(i[loop]>=2)
							y*=combin(votetype[loop]-1,i[loop]-1);
						for (int loop1=loop+1; loop1<maxVotes; loop1++)
						{
							if ((votetype[loop1]>1)&&(i[loop1]>0))
								y*=combin(votetype[loop1],i[loop1]);
						}
						power[loop]+=y;
					}//if critical to pass
				}

		}//it passed
	}//massive recursive loop
}//calculatePower Banzhaf

void calculateBanzhafOveride(int votetype[maxVotes], int required, double power[maxVotes])
{
	int x;
	int i[maxVotes];
	double y;
	for(int a=0; a<maxVotes; a++)
		i[a]=0;
	while(i[1]<votetype[1]+1)
	{
		i[maxVotes-1]++;
		if(i[maxVotes-1]>votetype[maxVotes-1])
		{
			i[maxVotes-1]=0;
			i[maxVotes-2]++;
			for(int j=maxVotes-2; j>=2; j--)
				if(i[j]>votetype[j])
				{
					i[j]=0;
					i[j-1]++;
				}
		}//if the first exceeds
		x=pass(i);
		if(x>=required)
		{
			for(int loop=0; loop<maxVotes; loop++)
				if(i[loop]>=1)
				{
					if((x-loop)<required)
					{
						y=1;
						for (int loop1=1; loop1<loop; loop1++)
						{
							if ((votetype[loop1]>1)&&(i[loop1]>0))
								y*=combin(votetype[loop1],i[loop1]);
						}
						if(i[loop]>=2)
							y*=combin(votetype[loop]-1,i[loop]-1);
						for (int loop1=loop+1; loop1<maxVotes; loop1++)
						{
							if ((votetype[loop1]>1)&&(i[loop1]>0))
								y*=combin(votetype[loop1],i[loop1]);
						}
						power[loop]+=(y/4);
					}//if critical to pass
				}

		}//it passed
	}//massive recursive loop
}//calculatePower Banzhaf overide

void printState(state a)
{
	cout.setf(ios::fixed);
	cout.setf(ios::right);
	cout<<setw(20)<<a.name<<setw(15)<<a.population<<setw(10)<<a.votes<<setw(30)<<setprecision(2)<<a.power<<endl;
}

void printHeader()
{
	cout.setf(ios::fixed);
	cout.setf(ios::right);
	cout<<setw(20)<<"State Name"<<setw(15)<<"Population"<<setw(10)<<"Votes"<<setw(30)<<"Power"<<endl;
}

void printStateFile(state a)
{
	dataout.setf(ios::fixed);
	dataout.setf(ios::right);
	dataout<<setw(20)<<a.name<<setw(15)<<a.population<<setw(10)<<a.votes<<setw(30)<<setprecision(2)<<a.power<<endl;
}

void printHeaderFile()
{
	dataout.setf(ios::fixed);
	dataout.setf(ios::right);
	dataout<<setw(20)<<"State Name"<<setw(15)<<"Population"<<setw(10)<<"Votes"<<setw(30)<<"Power"<<endl;
}

double combin(int n, int r)
{
	double top = 1;
	if((n==r)||(r==0))
		return 1;
	else
		for( int k = 0; k < r; k++)
		{
			top *= (double)(n - k)/(double)(r - k);
		}
		return (top);
}

int worst(state UnitedStates[states])
{
	int a=0;
	double ratio=UnitedStates[0].power/(double) UnitedStates[0].population;
	for(int loop=1; loop<states; loop++)
		if (UnitedStates[loop].power/(double) UnitedStates[loop].population < ratio)
		{
			ratio = UnitedStates[loop].power/(double) UnitedStates[loop].population;
			a=loop;
		}//compare each state in the loop
	cout<<UnitedStates[a].name<<endl;
	dataout<<UnitedStates[a].name<<endl;
	return a;
}//find the worst representation
