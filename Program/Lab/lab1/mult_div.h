struct mult_div_values{
        int mult;
        float div;
};

mult_div_values** create_table(int, int);
bool check_string(std::string); 
void get_number(std::string, std::string, int&, int&);
void set_mult_values(mult_div_values**, int, int);
void set_div_values(mult_div_values**, int, int);
