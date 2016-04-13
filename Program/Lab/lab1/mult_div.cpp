#include<iostream>
#include<string>
#include<iomanip>
#include "./mult_div.h"

using namespace std;

bool check_string(string a){
	for(int i=0; i<a.length();i++)
		if(!((a.at(i)>='0') && (a.at(i)<='9'))){
		return false;
	}
	return true;
}

void get_number(string row, string column, int& a, int& b){
	bool result1=false, result2=false;
	while(result1==false){
		result1=check_string(row);
		if(result1==false){       	
			cout << "You did not input a valid row\n" << "Please enter an integer greater than 0 for a row: ";
                	cin >> row;
		}
	}
	a = atoi(row.c_str());

	while(result2==false){
		result2=check_string(column);
		if(result2==false){
			cout << "You did not input a valid column\n" << "Please enter an integer greater than 0 for a column: ";
        	        cin >> column;
		}
        }
	b = atoi(column.c_str());
}

mult_div_values** create_table(int a, int b){
	mult_div_values **table;
	table = new mult_div_values *[a];
	for(int i=0; i<a; i++){
		table[i] = new mult_div_values[b];
	}
	return table;
}

void set_mult_values(mult_div_values** table, int a, int b){
	cout << endl << "Multiplication Table："; 
	for(int i=0; i<a; i++){
		cout << '\n';
		for(int j=0; j<b; j++){
			table[i][j].mult = (i+1)*(j+1);
			cout << table[i][j].mult << setw(3);
		}
	}
	cout << endl;
}

void set_div_values(mult_div_values** table, int a, int b){
	cout << endl << "Divsion Table: ";
	for(int i=0; i<a; i++){
		cout << '\n';
		for(int j=0; j<b; j++){
			table[i][j].div = 1.00 *(i+1.00)*(1.00/(j+1.00));
			cout << setprecision(2) << setiosflags(ios::fixed) << table[i][j].div << ' ';
		} 
	}
	cout << endl;
}


