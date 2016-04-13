/**********************************************************************************************************************************************************************************************************
** Program:assignment1.cpp
** Author: ZHI JIANG
** Date: 19/01/2014
** Description; In this game, cell will be born or dead according their special rule. The users should put some cells in this world, and these cells will start to change. Eventually the world  has two 
		conditions. One is that remaining cells which never die, so it means you win. Another condition is that there is no cell in the world, so it means game over.  
** input:
** Output:
***********************************************************************************************************************************************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<unistd.h>

using namespace std;

#define row 24
#define column 82

struct cell{
	char fact;
	char type;
};
cell **creat_world();
void initialize_world(cell**);
void user_enter(cell**);
bool check_string(string);
bool check_number_range(string);
bool check_abscissa_range(string);
bool check_ordinate_range(string); 
bool get_number_cell(string);
bool get_correct_abscissa(string);
bool get_correct_ordinate(string);
void check_cell(cell**);
void modify_world(cell**);
void display_world(cell**);
void recheck_world(cell**, int&);
void make_edge(cell**);
void game_over(cell**);
void glider_gun(cell**);
void oscillators(cell**);
void glider(cell**);


int main(){
	int life=1, choice=1;
	cell **world; 
	
	while(choice==1){
		world = creat_world();
		initialize_world(world);
		while(!(life==0)){	
			system("clear");	
			check_cell(world);
			modify_world(world);
			display_world(world);
			recheck_world(world,life);
			sleep(1);
			life-=1;
		}	
		system("clear");
		game_over(world);
		cout << "Do you want to play a again? (1 for yes, 0 for no): ";
		cin >> choice;
		system("clear");
	}
	return 0;
}

/**********************************************************************************************************************************************************************************************************
** Function: creat_world
** Description: this function is used to creat this 24x82 world through pointer
** Parameters: none
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
cell **creat_world(){
	cell **world;
	world = new cell *[row];
	for(int i=0; i<row; i++){
		world[i] = new cell [column];
	}
	return world;
}

/**********************************************************************************************************************************************************************************************************
** Function: check_string
** Description: this function is used to check string users enter
** Parameters: a
** Pre-Condition: none 
** Post-Condition:  none
**********************************************************************************************************************************************************************************************************/
bool check_string(string a){
	for(int i=0; i<a.length(); i++)
		if(!((a.at(i)>='0')&&(a.at(i)<='9'))){
		cout << "Error: you did enter a positve number!" <<endl;
		return false;
	}
	return true;
}

/**********************************************************************************************************************************************************************************************************
** Function: check_number_range 
** Description: this function is used to check number of cells users want to add is in range or not
** Parameters: a
** Pre-Condition: none 
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
bool check_number_range(string a){
	int realnum;
	realnum = atoi(a.c_str());
	if(realnum>=0 && realnum<=1760){
		return true;
	}
	cout << "Error: you did not enter number between 0 and 1760!" <<endl;
	return false;
}

/**********************************************************************************************************************************************************************************************************
** Function: check_abscissa_range 
** Description: this function is used to check abscissa of cell is in range or not
** Parameters: a
** Pre-Condition: none 
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
bool check_abscissa_range(string a){
	int realnum;
	realnum = atoi(a.c_str());
	if(realnum>=0 && realnum<=22){
		return true;
	}
	cout << "Error: you did not enter number between 0 and 22 for abscissa!" << endl;
	return false;
}

/**********************************************************************************************************************************************************************************************************
** Function: check_ordinate_ange
** Description: this function is used to check ordinate of cell is in range or not 
** Parameters: a
** Pre-Condition: none 
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
bool check_ordinate_range(string a){
	int realnum;
	realnum = atoi(a.c_str());
	if(realnum>=0 && realnum<=80){
		return true; 
	}
	cout << "Error: you did not enter number between 0 and 88 for ordinate!" << endl;
	return false;
} 

/**********************************************************************************************************************************************************************************************************
** Function: get_number_cell
** Description: this function is used to get number of cells users want to add 
** Parameters: a 
** Pre-Condition: result==true
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
bool get_number_cell(string a){
	bool result=false;
	result=check_string(a);
		if(result==true)
			return check_number_range(a);
	 	else	
			return false;
}		

/**********************************************************************************************************************************************************************************************************
** Function: get_correct_abscissa
** Description: this function is used to get correct abscissa of cell users want to add
** Parameters: a 
** Pre-Condition: result==true 
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
bool get_correct_abscissa(string a){
	bool result=false;
	result=check_string(a);
		if(result==true)
			return check_abscissa_range(a);
		else
			return false;
}

/**********************************************************************************************************************************************************************************************************
** Function: get_correct_ordinate
** Description: this function is used to get correct ordinate of cell users want to add
** Parameters: a
** Pre-Condition: result==true 
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
bool get_correct_ordinate(string a){
	bool result=false;
	result=check_string(a);
		if(result==true)
			return check_ordinate_range(a);
		else
			return false;
}

/**********************************************************************************************************************************************************************************************************
** Function: user_enter
** Description: this function is used to make user enter loaction of cells they want to add 
** Parameters: **world
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void user_enter(cell **world){
	string number, a, b;
	int num, m, n;
	bool result1=false, result2=false, result3=false;
	while(result1==false){
		cout << "How many cells do you want to add(range: 0-1760): ";
		cin >> number;
		result1=get_number_cell(number);
	}
	num = atoi(number.c_str());

	for(int i=0; i<num; i++){
		while(!(result2==true&&result3==true)){
			cout << "Please enter two number fo your "<< i+1 << " cell's location (abscissa 0-22 ordinate 0-80): ";
			cin >> a >> b;
			result2=get_correct_abscissa(a);
			result3=get_correct_ordinate(b);
		}
		m = atoi(a.c_str());
		n = atoi(b.c_str());		
		world[m][n].fact='o';
		result2=false;
		result3=false;
	}
}
 
/**********************************************************************************************************************************************************************************************************
** Function: initialize_world
** Description: this function is used to initialize the world. The initialized world include a glider and a oscillator
** Parameters: **world
** Pre-Condition: none 
** Post-Condition: none 
**********************************************************************************************************************************************************************************************************/
void initialize_world(cell **world){
	int a=0;
	for(int i=1; i<row-1; i++)
		for(int j=1; j<column-1; j++){
			world[i][j].fact=' ';
			world[i][j].type='a';
	}
	make_edge(world);
    	oscillators(world);
    	glider(world);
	cout << endl <<setw(82) << "This is initialized world ";
	display_world(world);

	cout << "Do you want to add a glider gun in the world ？(1 for yes, 0 for no) ";
	cin >> a;
	if(a==1){
		glider_gun(world);
		cout << "glider gun has been added in the world " << endl;
		system("clear");
		display_world(world);
	} 

	user_enter(world);
	system("clear");
	cout << endl <<setw(82) << "This is your initialized world";
	display_world(world);
	cout << "The game will begin after three seconds" << endl;
	sleep(3);
	system("clear");
	 
}

/**********************************************************************************************************************************************************************************************************
** Function: check_cell
** Description: this function is used to check each element's state in the world
** Parameters: **world
** Pre-Condition: none 
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void check_cell(cell **world){
	int neighbor=0;
	for(int i=1; i<row-1; i++){
		for(int j=1; j<column-1; j++){
			if(world[i-1][j-1].fact=='o')
				neighbor+=1;
			if(world[i-1][j].fact=='o')
				neighbor+=1;
			if(world[i-1][j+1].fact=='o')
				neighbor+=1;
			if(world[i][j-1].fact=='o')
				neighbor+=1;
			if(world[i][j+1].fact=='o')
				neighbor+=1;
			if(world[i+1][j-1].fact=='o')
				neighbor+=1;
			if(world[i+1][j].fact=='o')
				neighbor+=1;
			if(world[i+1][j+1].fact=='o')
				neighbor+=1;

			if(neighbor>3||neighbor<2){
				if(world[i][j].fact=='o')
					world[i][j].type='d';
				else
					world[i][j].type='k';
			}
			if(neighbor==3){
				if(world[i][j].fact=='o')
					world[i][j].type='k';
				else
					world[i][j].type='b';
			}

			if(neighbor==2)
				world[i][j].type='k';

			neighbor=0;
		}
	}	
}

/**********************************************************************************************************************************************************************************************************
** Function: modify_world
** Description: this function is used to modify the world after check
** Parameters: **world
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void modify_world(cell **world){
	for(int a=1; a<row-1; a++){
		for(int b=1; b<column-1; b++){
			if(world[a][b].type=='d')
				world[a][b].fact=' ';
			else if(world[a][b].type=='k')
				world[a][b].fact=world[a][b].fact;   
			else if(world[a][b].type=='b')
				world[a][b].fact='o';
		}
	}
}

/**********************************************************************************************************************************************************************************************************
** Function: display_world
** Description: this function is used to display the world
** Parameters: **world
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void display_world(cell **world){
	for(int i=0; i<row; i++){
		cout << endl;
		for(int j=0; j<column; j++){
				cout << world[i][j].fact<< ' ';
		}
	}
	cout << endl << endl;
}

/**********************************************************************************************************************************************************************************************************
** Function: recheck_world
** Description: this function is used to check there is a cell exist or not
** Parameters: **world
** Pre-Condition: none 
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void recheck_world(cell **world, int& life){
	life=1;
	for(int m=1; m<row-1; m++)
		for(int n=1; n<column-1; n++){
			if(world[m][n].fact=='o')
				life+=1;
			else
				life+=0;
		}
}

/**********************************************************************************************************************************************************************************************************
** Function: make_edge
** Description: this function is used to make edge for the world
** Parameters: **world
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void make_edge(cell **world){
	for(int a=0; a<row; a++){
		world[a][0].fact='*';
		world[a][81].fact='*';
	}

	for(int b=0; b<column; b++){
		world[0][b].fact='*';
		world[23][b].fact='*';
	}
}

/**********************************************************************************************************************************************************************************************************
** Function: game_over
** Description: this function is used to display 'game over'
** Parameters: **world
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void game_over(cell **world){
	world[11][35].fact='G';
	world[11][36].fact='A';
	world[11][37].fact='M';
	world[11][38].fact='E';
	world[11][39].fact=' ';
	world[11][40].fact=' ';
	world[11][41].fact='O';
	world[11][42].fact='V';
	world[11][43].fact='E';
	world[11][44].fact='R';	

	display_world(world);
}

/**********************************************************************************************************************************************************************************************************
** Function: glider_gun
** Description: this function is used to make a glider gun in the world
** Parameters: **world
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void glider_gun(cell **world){
	world[10][10].fact='o';
	world[10][11].fact='o';
	world[11][10].fact='o';
	world[11][11].fact='o';
	

	world[8][22].fact='o';
	world[8][23].fact='o';
	world[9][21].fact='o';
	world[10][20].fact='o';
	world[11][20].fact='o';
	world[12][20].fact='o';
	world[13][21].fact='o';
	world[14][22].fact='o';
	world[14][23].fact='o';
	world[11][24].fact='o';
	world[9][25].fact='o';
	world[10][26].fact='o';
	world[11][26].fact='o';
	world[12][26].fact='o';
	world[13][25].fact='o';
	world[11][27].fact='o';

	world[8][30].fact='o';
	world[8][31].fact='o';
	world[9][30].fact='o';
	world[9][31].fact='o';
	world[10][30].fact='o';
	world[10][31].fact='o';
	world[7][32].fact='o';
	world[11][32].fact='o';
	world[7][34].fact='o';
	world[6][34].fact='o';
	world[11][34].fact='o';
	world[12][34].fact='o';

	world[8][44].fact='o';
	world[8][45].fact='o';
	world[9][44].fact='o';
	world[9][45].fact='o';
}

/**********************************************************************************************************************************************************************************************************
** Function: oscillators
** Description: this function is used make a oscillator in the world
** Parameters: **world
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void oscillators(cell **world){
    world[13][54].fact='o';
    world[13][55].fact='o';
    world[13][56].fact='o';
    world[14][53].fact='o';
    world[14][54].fact='o';
    world[14][55].fact='o';
}

/**********************************************************************************************************************************************************************************************************
** Function: glider
** Description: this function is used to make a glider in the world
** Parameters: **world
** Pre-Condition: none
** Post-Condition: none
**********************************************************************************************************************************************************************************************************/
void glider(cell **world){
    world[8][67].fact='o';
    world[8][68].fact='o';
    world[8][69].fact='o';
    world[6][68].fact='o';
    world[7][69].fact='o';
}
