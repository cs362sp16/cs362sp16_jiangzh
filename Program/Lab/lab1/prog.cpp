#include<iostream>
#include<string>
#include<iomanip>
#include "./mult_div.h"

using namespace std;

int main(int argc, char *argv[]){
        int row, column;
        mult_div_values  **table;
	
        get_number(argv[1],argv[2],row,column);

        table = create_table(row,column);

        set_mult_values(table,row,column);

        set_div_values(table,row,column);

        exit(0);
}
