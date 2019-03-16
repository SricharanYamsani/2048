#include<iostream>
#include<stdlib.h>
#include<ctime>

using namespace std;

class Game2048
{
	int n_rows;
	int n_cols;
	bool has_moved;
	bool win;
	int score;
	int **a;
	bool **change;

	public:
	Game2048(int x,int y):n_rows(x),n_cols(y),has_moved(true),win(false),score(0)
	{
		a = new int*[n_rows];
		for(int i=0;i<n_rows;i++)
			a[i] = new int[n_cols];
			
		change = new bool*[n_rows];
		for(int i=0;i<n_cols;i++)
			change[i] = new bool[n_cols];	
	}
	
	~Game2048()
	{
		for(int i=0;i<n_rows;i++)
			delete []a[i];
		delete []a;
		
		for(int i=0;i<n_rows;i++)
			delete []change[i];
		delete []change;
	}
	void init();
	void reset_changes();
	void printgrid();						  	
	int isgridfull();
	int move_possible();
	int grid_blocked();
	void spawn();
	void play_left();
	void play_right();
	void play_up();
	void play_down();
	void play();
};
void Game2048::init()//Initializing all array elements to 0
{
	for(int i=0;i<n_rows;i++)
		for(int j=0;j<n_cols;j++)
		{
			a[i][j]=0;
			change[i][j]=false;
		}
		
/*	
	a[0][0]=2;
	a[0][1]=2;
	a[0][2]=2;
	a[0][3]=2;
	a[1][0]=0;
	a[1][1]=0;
	a[1][2]=0;
	a[1][3]=0;
	a[2][0]=0;
	a[2][1]=0;
	a[2][2]=0;
	a[2][3]=0;
	a[3][0]=0;
	a[3][1]=0;
	a[3][2]=0;
	a[3][3]=0;*/		
}

void Game2048::reset_changes()
{
	for(int i=0;i<n_rows;i++)
		for(int j=0;j<n_cols;j++)
			change[i][j]=false;
}
void Game2048::printgrid()//Printing the game grid
{
	cout<<"\n";
	cout<<"Score : "<<score;
	cout<<"\t\tPress X to exit\n";
	for(int i=0;i<n_rows;i++)
	{
		cout<<"\n|";
		for(int j=0;j<n_cols;j++)
		{
			if(a[i][j]) cout<<a[i][j];
			cout<<"\t|";
		}
		//cout<<"|";
	}
}

int Game2048::isgridfull()
{
	for(int i=0;i<n_rows;i++)
		for(int j=0;j<n_cols;j++)
			if(a[i][j]==0)
				return 0;
	return 1;			
}

int Game2048::move_possible()
{
	for(int i=0;i<n_rows;i++)
		for(int j=0;j<n_cols-1;j++)
			if(a[i][j]==a[i][j+1])
			{
				//cout<<"\n"<<a[i][j]<<"&"<<a[i][j+1];
				return 1;
			}
			
	for(int i=0;i<n_rows-1;i++)
		for(int j=0;j<n_cols;j++)
			if(a[i][j]==a[i+1][j])
			{
				//cout<<"\n"<<a[i][j]<<"&"<<a[i+1][j];
				return 1;
			}
	
	return 0;			
}

int Game2048::grid_blocked()
{
	if(isgridfull())
	{
		if(move_possible())
		{
			//cout<<"\nGrid full but move possible";
			return 0;
		}
		else
		{
			//cout<<"\nGrid blocked";
			return 1;
		}
	}
	else
	{
		//cout<<"\nGrid not full";
		return 0;
	}
}
void Game2048::spawn()
{
	int r,c;
	srand((unsigned)time(0));
	do
	{
		r=rand()%4;
		c=rand()%4;
	}while(a[r][c]!=0);
	
	a[r][c]=2;//100% chance of spawning a 2
	has_moved=false;
}
void Game2048::play_left()
{
	for(int i=0;i<n_rows;i++)
		for(int j=1;j<n_cols;j++)
		{
			for(int k=j;k>0;k--)
			{
				if(a[i][k]==0)
					break;
				else if(a[i][k-1]==0)
				{
					if(!has_moved)has_moved=true;
					a[i][k-1]=a[i][k];
					a[i][k]=0;
				}
				else if(a[i][k]==a[i][k-1])
				{
					if(!change[i][k-1]&&!change[i][k])
					{
						a[i][k-1]*=2;
						a[i][k]=0;
						score+=a[i][k-1];
						if(a[i][k-1]==2048)win = true;
						if(!has_moved)has_moved=true;
						change[i][k-1]=true;
						change[i][k]=false;
					}
				}
			}
		}
	reset_changes();
}


void Game2048::play_right()
{
	for(int i=0;i<n_rows;i++)
		for(int j=n_cols-2;j>=0;j--)
		{
			for(int k=j;k<n_rows-1;k++)
			{
				if(a[i][k]==0)
					break;
				else if(a[i][k+1]==0)
				{
					if(!has_moved)has_moved=true;
					a[i][k+1]=a[i][k];
					a[i][k]=0;
				}
				else if(a[i][k]==a[i][k+1])
				{
					if(!change[i][k+1]&&!change[i][k])
					{
						a[i][k+1]*=2;
						a[i][k]=0;
						score+=a[i][k+1];
						if(a[i][k+1]==2048)win = true;
						if(!has_moved)has_moved=true;
						change[i][k+1]=true;
						change[i][k]=false;
					}
				}
			}
		}
	reset_changes();
}


void Game2048::play_up()
{
	for(int j=0;j<n_cols;j++)
		for(int i=1;i<n_rows;i++)
		{
			for(int k=i;k>0;k--)
			{
				if(a[k][j]==0)
					break;
				else if(a[k-1][j]==0)
				{
					if(!has_moved)has_moved=true;
					a[k-1][j]=a[k][j];
					a[k][j]=0;
				}
				else if(a[k][j]==a[k-1][j])
				{
					if(!change[k-1][j]&&!change[k][j])
					{
						a[k-1][j]*=2;
						a[k][j]=0;
						score+=a[k-1][j];
						if(a[k-1][j]==2048)win = true;
						if(!has_moved)has_moved=true;
						change[k-1][j]=true;
						change[k][j]=false;
					}
				}
			}
		}
	reset_changes();
}


void Game2048::play_down()
{
	for(int j=0;j<n_cols;j++)
		for(int i=n_rows-2;i>=0;i--)
		{
			for(int k=i;k<n_rows-1;k++)
			{
				if(a[k][j]==0)
					break;
				else if(a[k+1][j]==0)
				{
					if(!has_moved)has_moved=true;
					a[k+1][j]=a[k][j];
					a[k][j]=0;
				}
				else if(a[k][j]==a[k+1][j])
				{
					if(!change[k+1][j]&&!change[k][j])
					{
						a[k+1][j]*=2;
						a[k][j]=0;
						score+=a[k+1][j];
						if(a[k+1][j]==2048)win = true;
						if(!has_moved)has_moved=true;
						change[k+1][j]=true;
						change[k][j]=false;
					}
				}
			}
		}
	reset_changes();
}

void Game2048::play()
{
	char ch;
	init();
	while(!win&&!grid_blocked())
	{
		if(has_moved)
			spawn();
		do
		{
			system("cls");	
			printgrid();
			cout<<"\n\nEnter you choice(w-up ; a-left ; s-down ; d-right) : ";
			fflush(stdin);
			cin>>ch;
		}while(ch!='w'&&ch!='a'&&ch!='s'&&ch!='d'&&ch!='x');
		
		switch(ch)
		{
			case 'w':play_up();
					 break;
			case 'a':play_left();
					 break;
			case 's':play_down();
					 break;
			case 'd':play_right();
					 break;
			case 'x':exit(0);		 
		}
		
	}
	
	if(win)
	{
		system("cls");
		printgrid();
		cout<<"\n\nYOU WIN";
	}
	else
	{
		system("cls");
		printgrid();
		cout<<"\n\nNO MORE MOVES POSSIBLE";	
	}
}

int main()
{
	Game2048 g(4,4); 
	g.play();
	
	return 0;
}
