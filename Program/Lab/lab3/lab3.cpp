#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

class list_item{

	public:
	string name;
	string unit;
	int nr_wanted;
	int unit_price;

	void add_item(list_item*, int);
	void remove_item(list_item*, int&, int);
	void display_list(list_item*, int);
};

void list_item::add_item(list_item *a, int number){
	cout << "Name of item: ";
	cin >> a[number].name;
	cout << "Unit of item: ";
	cin >> a[number].unit;
	cout << "Number of item: ";
	cin >> a[number].nr_wanted;
	cout << "Price of peer unit: ";
	cin >> a[number].unit_price;
} 


void list_item::remove_item(list_item *a, int& remove, int number){
		cout << "Which row do you want to remove: ";
		cin >> remove;

		for(int i=remove; i<number; i++){
			a[i-1].name=a[i].name;
			a[i-1].unit=a[i].unit;
			a[i-1].nr_wanted=a[i].nr_wanted;
			a[i-1].unit_price=a[i].unit_price;
		}
}	

void list_item::display_list(list_item *a, int number){
	
	cout << a[number].name << setw(20) << a[number].unit << setw(20) << a[number].nr_wanted << setw(20) << a[number].unit_price << endl;
} 


int main(){
	int choice=1, number=0, remove=0;
	list_item  item;
	list_item *array;

	array = new list_item[100];
	

	cout << setw(40) <<"Your shopping list" << endl << "nothing" << endl;
	while(!(choice==0)){
		cout << "Do you want add or remove ( 1 for add, 2 for remove, 0 for exit): ";
		cin >> choice;

		if(choice==1){
			item.add_item(array,number);
			number++;
			system("clear");
			cout << setw(40) <<"Your shopping List " << endl;
			cout << "name" << setw(20) << "unit" << setw(20) << "number" << setw(20) << "unit price" << endl;
			for(int j=0; j<number; j++){
				item.display_list(array,j);
	
			}
		}

		if(choice==2){
			if(number==0)
				cout << "There is nothing, so you can not remove anything" << endl;
			else{
				item.remove_item(array,remove,number);
				number--;
				system("clear");
				cout <<  setw(40) << "Your shopping list" << endl;
				for(int a=0; a<number; a++)
					item.display_list(array,a);
			}	
		}
	}			

	return 0;
}
