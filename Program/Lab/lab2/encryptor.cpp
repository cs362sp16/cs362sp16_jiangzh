#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdlib>

using namespace std;
void get_string(string&, string&);
void set_key(string ,string, char*);
void set_sentence(string, char*);
void make_answer(string ,char* ,char* );
	
int main(){
    int i=0;
	string key, sentence;
	char a[100], b[100];
	
    
    while(i<2){
	get_string(key, sentence);

	cout << endl << "You would XOR: " << endl << endl; 
    
	set_key(key,sentence,a);

	cout << endl;

	set_sentence(sentence,b);

	cout << endl;

	make_answer(sentence,a,b);

        cout <<endl << endl;
        i+=1;
    }
        return 0;
}

void get_string(string& a, string& b){
        cout << "Key: ";
        cin >> a;
        cout << "Sentence: ";
        cin >> b;
}

void set_key(string key, string sentence, char *a){
	int number=0; 
 	for(int i=0; i<sentence.length();i++){
                        a[i]=key.at(number);
                        number++;

                         if(number>=key.length())
                         number-=key.length();
        } 

	for(int i=0; i<sentence.length(); i++)
                cout << a[i] << ' ';
}        

void set_sentence(string sentence, char* a){
    for(int i=0; i<sentence.length(); i++){
		a[i]=sentence.at(i);
		cout << a[i] << ' ';
	}
}

void make_answer(string sentence,char *a, char *b){
        char c[100];
        for(int i=0; i<sentence.length(); i++){
                c[i]=(32+(a[i]^b[i]));
                cout << c[i] << ' ';
        }
}
