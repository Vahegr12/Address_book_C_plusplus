#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>

// validation tests for memebers of Person 
    bool valid_email(const std::string& input) {
    if(input.empty()){
            return 0;
        }
    if(input == "Unknown"){
        return 1;
    }

    size_t at_pos = input.find('@');
    
    if (at_pos == std::string::npos) {
        return 0;
    }
    if (at_pos == 0) {
        return 0;
    }

    if (at_pos == input.length() - 1) {
        return 0;
    }

    size_t dot_pos = input.find('.', at_pos);
    if (dot_pos == std::string::npos) {
        return 0;
    }

    if (dot_pos - at_pos <= 1) {
        return 0;
    }

    if (dot_pos == input.length() - 1) {
        return 0;
    }

    if (input.length() - dot_pos < 3) {
        return 0;
    }

    return 1;
}
    bool valid_name(std::string& input) {
        if(input.empty()){
            return 0;
        }
        
        if(input == "Unknown"){
            return 1;
        }
        for(size_t i = 0; i < input.length(); ++i){
            if(input.at(i) < 'A' || (input.at(i) > 'Z' && input.at(i) < 'a') || input.at(i) > 'z'){
                    return 0;
                }
        }
        if(input.at(0) >= 'a' && input.at(0) <= 'z'){
            input.at(0) -= ('a' - 'A');
            }
        return 1;
    }
    bool valid_phone_n(std::string& input){
        if(input.empty()){
            return 0;
        }
        
        if(input == "Unknown"){
            return 1;
        }
        size_t phone_n_length = input.length(); 
        size_t correct_length = 12; //+xxxxxxxxxxx 11 numbers
        
        if(input.at(0) == '0' && phone_n_length == 9){ // 077_777_777 9 numbers
            for(int i = 0; i < phone_n_length; ++i){
                if(input.at(i) < '0' || input.at(i) > '9'){
                    return 0;
                }
            }
            
            std::string tmp = input;
            input.resize(correct_length);
            
            input.at(0) = '+';
            input.at(1) = '3';
            input.at(2) = '7';
            input.at(3) = '4';
            
            for(int i = 1; i < correct_length-3; ++i){
            input.at(i+3) = tmp.at(i);
            }
        }

        else if(input.at(0) == '+' && phone_n_length == correct_length){ // +374_77_777_777 11 numbers
            for(int i = 1; i < phone_n_length-1; ++i){
                if(input.at(i) < '0' || input.at(i) > '9'){
                    return 0;
                }
            }
        }
        else if((input.at(0) >= '0' || input.at(0) <= '9') && phone_n_length == correct_length -1){// 374_77_777_777 11 numbers
            return 1;
        }
        
        else{
            return 0;
        }

        return 1;
    }

class Person{
public:

//maps for get/set operations 
std::map<int, bool (Person::*)(std::string)> opers_set;
std::map<int, std::string (Person::*)()> opers_get;
    
//constructor/destructor
    Person(){
        opers_set = {
            {1, &Person::set_f_name},
            {2, &Person::set_l_name},
            {3, &Person::set_phone_n},
            {4, &Person::set_email}
        };
        opers_get = {
            {1, &Person::get_f_name},
            {2, &Person::get_l_name},
            {3, &Person::get_phone_n},
            {4, &Person::get_email}
        };
    }
    ~Person(){}

//operators
    bool operator==(Person& cmp_per){
        if(
           this -> get_f_name() == cmp_per.get_f_name() &&
           this -> get_l_name() == cmp_per.get_l_name() &&
           this -> get_phone_n() == cmp_per.get_phone_n() &&
           this -> get_email() == cmp_per.get_email()
        ){
            return 1;
        }
        return 0;
    }
    bool operator!=(Person& cmp_per){
        if(
           this -> get_f_name() != cmp_per.get_f_name() ||
           this -> get_l_name() != cmp_per.get_l_name() ||
           this -> get_phone_n() != cmp_per.get_phone_n() ||
           this -> get_email() != cmp_per.get_email()
        ){
            return 1;
        }
        return 0;
    }

//setters
    bool set_f_name(std::string in_f_name){
        if(valid_name(in_f_name)){
            this -> f_name = in_f_name;
        }        
        if(this -> f_name == in_f_name){
            return 1;
        }
        return 0;
    }
    bool set_l_name(std::string in_l_name){
        if(valid_name(in_l_name)){
            this -> l_name = in_l_name;
            
        } 
        if(this -> l_name == in_l_name){
            return 1;
        }
        return 0;
    }
    bool set_phone_n(std::string in_phone_n){
        if(valid_phone_n(in_phone_n)){
            this -> phone_n = in_phone_n;
        }
        if(this -> phone_n == in_phone_n){
            return 1;
        }
        return 0;
    }
    bool set_email(std::string in_email){
        if(valid_email(in_email)){
            this -> email = in_email;
        }
        
        if(this -> email == in_email){
            return 1;
        }
        return 0;
    }

//getters
    std::string get_f_name(){
        return this-> f_name;
    }
    std::string get_l_name(){
        return this -> l_name;
    }
    std::string get_phone_n(){
        return this -> phone_n; 
    }
    std::string get_email(){
        return this -> email;
    }

//functions
void print(){
    std::cout << "\n       Contact" << std::endl;
    std::cout << this -> f_name << std::endl;
    std::cout << this -> l_name << std::endl;
    std::cout << this -> phone_n << std::endl;
    std::cout << this -> email << std::endl;
}
void enter_info(){
    std::string tmp_str;
// enter the first_name
    std::cout << "Enter the first name: ";
    std::cin >> tmp_str;

    while(!valid_name(tmp_str)){
        std::cout << "Incorrect first_name. Please enter a correct first_name: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> tmp_str;
    }

    this -> set_f_name(tmp_str);

// enter the last_name
    std::cout << "Enter the last name: ";
    std::cin >> tmp_str;

    while(!valid_name(tmp_str)){
        std::cout << "Incorrect last_name. Please enter a correct last_name: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> tmp_str;
    }

    this -> set_l_name(tmp_str);

// enter the phone number
    std::cout << "Enter the phone number: ";
    std::cin >> tmp_str;

    while(!valid_phone_n(tmp_str)){
        std::cout << "Incorrect phone number. Please enter a correct phone number: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> tmp_str;
    }
    this -> set_phone_n(tmp_str);

// enter the email
    std::cout << "Enter the email: ";
    std::cin >> tmp_str;

    while(!valid_email(tmp_str)){
        std::cout << "Incorrect email. Please enter a correct email: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> tmp_str;
    }
    this -> set_email(tmp_str);

}
    
private:
    std::string f_name {"Unknown"};
    std::string l_name {"Unknown"};
    std::string phone_n {"Unknown"};
    std::string email {"Unknown"};
   
};


// '<<' and '>>' fstream operators overloading for my class
std::fstream& operator <<(std::fstream& ofs,Person person){
    ofs << person.get_f_name() << std::endl; // "f_name: " <<
    ofs << person.get_l_name() << std::endl; // "l_name: " <<
    ofs << person.get_phone_n() << std::endl; // "phone_n: " <<
    ofs << person.get_email() << std::endl << std::endl; // "email: " <<
    return ofs;
}
std::fstream& operator >>(std::fstream& ifs, Person& person){
    std::string tmp_data;
    std::getline(ifs,tmp_data);
    person.set_f_name(tmp_data);

    std::getline(ifs,tmp_data);
    person.set_l_name(tmp_data);

    std::getline(ifs,tmp_data);
    person.set_phone_n(tmp_data);

    std::getline(ifs,tmp_data);
    person.set_email(tmp_data);

    std::getline(ifs,tmp_data); // tmp = empty line
    return ifs;
}


// oerations for user
bool add_person(std::fstream& out_s) {
    std::cout << "---Add---" << std::endl;
    Person tmp_p;
    tmp_p.enter_info();
    try {
        out_s << tmp_p;
        std::cout << "---Done---" << std::endl;
        return 1;
    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 0;
    }
}
Person search_person(std::fstream& in_s){
    std::cout << "\n---Search---" << std::endl;
    int data_type{};
    std::cout << "1. first name," << std::endl
              << "2. last name," << std::endl
              << "3. phone number," << std::endl
              << "4. email," << std::endl 
              << "5. cencel" << std::endl
              << "Enter the ID of data type to search by: ";
    
    std::cin >> data_type;
    
    while (data_type < 1 || data_type > 5) {
        std::cout << "Wrong data type ID. Please enter a valid data type ID: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> data_type;
    }
    if(data_type == 5){
        std::cout << "---Cencel---";
        Person def_p;
        return def_p;
    }
    std::string data;
    std::cout << "Enter the data to search by: ";
    
    std::cin >> data;
    
    Person test_p;
    while (!(test_p.*test_p.opers_set.at(data_type))(data)) {
        std::cout << "Wrong data. Please enter a valid data: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> data_type;
    }
   
    Person def_p;
    Person current_per;
    bool is_find{};

    char ans{};
    while(in_s >> current_per){
        if ((current_per.*current_per.opers_get.at(data_type))() == (test_p.*test_p.opers_get.at(data_type))() ){
        std::cout << "\nIs the following contact Right?: " << std::endl;
            current_per.print();
            std::cout << "enter 'y'/'n' to conform of cencel or 'c' to cencel: ";

            std::cin >> ans; 
            while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N' && ans != 'c' && ans != 'C'){
                std::cout << "invalid character, enter 'y'/'n' to conform of cencel: ";
                std::cin.clear();
                std::cin.ignore(100,'\n');
                std::cin >> ans;
            }
            if(ans == 'y' || ans == 'Y'){
                is_find = 1;
                continue;
            }
            else if(ans == 'c' || ans == 'C'){
                std::cout << "\n----------Cenceled----------" << std::endl;
                return def_p;
            }
            else{
                is_find = 0;
            }
        }
        
    }
    if(!is_find){
        std::cout << "Conatact didnt been detected! " << std::endl;
    }

    return current_per;
    }
bool delete_person(std::fstream& in_s, std::string path){
    std::cout << "\n---Delete---" << std::endl;
    int data_type{};
    std::cout << "1. first name," << std::endl
              << "2. last name," << std::endl
              << "3. phone number," << std::endl
              << "4. email," << std::endl 
              << "5. cencel" << std::endl
              << "Enter the ID of data type to search by: ";
    
    std::cin >> data_type;
    
    while (data_type < 1 || data_type > 5) {
        std::cout << "Wrong data type ID. Please enter a valid data type ID: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> data_type;
    }
    if(data_type == 5){
        std::cout << "---Cencel---";
        return 0;
    }
    std::string data;
    std::cout << "Enter the data to search by: ";
    
    std::cin >> data;
    
    Person test_p;
    while (!(test_p.*test_p.opers_set.at(data_type))(data)) {
        std::cout << "Wrong data. Please enter a valid data: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> data_type;
    }
   

    std::vector<Person> tmp_data_base;
    Person tmp_per;
    bool is_find{};
    char ans{};
    // searching
    while(in_s >> tmp_per){ 
        
        if ((tmp_per.*tmp_per.opers_get.at(data_type))() == (test_p.*test_p.opers_get.at(data_type))()){
            std::cout << "\nDelete the following contact ?: " << std::endl;
            tmp_per.print();
            std::cout << "enter 'y'/'n' to conform of cencel or 'c' to cencel: ";

            std::cin >> ans; 
            while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N' && ans != 'c' && ans != 'C'){
                std::cout << "invalid character, enter 'y'/'n' to conform of cencel: ";
                std::cin.clear();
                std::cin.ignore(100,'\n');
                std::cin >> ans;
            }
            if(ans == 'y' || ans == 'Y'){
                is_find = 1;
                continue;
            }
            else if(ans == 'c' || ans == 'C'){
                std::cout << "\n----------Cenceled----------" << std::endl;
                return 0;
            }
            else{
                is_find = 0;
            }
        }
        tmp_data_base.push_back(tmp_per);
    }
    if(!is_find){
        std::cout << "Conatact didnt been detected! " << std::endl;
    }

//clear file
    std::ofstream tmp_strema(path);
    tmp_strema.close();
    
//returnning correct data_base; 
    int i = 0;
    in_s.seekp(0, std::ios::beg);
    in_s.clear();



    while(i < tmp_data_base.size()){
        in_s << tmp_data_base.at(i);
        ++i;
    }
    std::cout << "---Done---" << std::endl;
    return 1;
}
bool edit_person(std::fstream& in_s, std::string path){

    std::cout << "\n---Edit---" << std::endl;
    int data_type{};
    std::cout << "1. first name," << std::endl
              << "2. last name," << std::endl
              << "3. phone number," << std::endl
              << "4. email," << std::endl 
              << "5. cencel" << std::endl
              << "Enter the ID of data type to search by: ";
    
    std::cin >> data_type;
    
    while (data_type < 1 || data_type > 5) {
        std::cout << "Wrong data type ID. Please enter a valid data type ID: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> data_type;
    }
    if(data_type == 5){
        std::cout << "---Cencel---";
        return 0;
    }
    std::string data;
    std::cout << "Enter the data to search by: ";
    
    std::cin >> data;
    
    Person test_p;
    while (!(test_p.*test_p.opers_set.at(data_type))(data)) {
        std::cout << "Wrong data. Please enter a valid data: ";
        std::cin.clear(); 
        std::cin.ignore(100,'\n');                 
        std::cin >> data_type;
    }    

    std::vector<Person> tmp_data_base;
    Person tmp_per;
    bool is_find{};
    char ans{};
    // searching
    while(in_s >> tmp_per){ 

        if ((tmp_per.*tmp_per.opers_get.at(data_type))() == (test_p.*test_p.opers_get.at(data_type))()){
            std::cout << "\nEdit the following contact ?: " << std::endl;
            tmp_per.print();
            std::cout << "enter 'y'/'n' to conform of cencel or 'c' to cencel: ";

            std::cin >> ans; 
            while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N' && ans != 'c' && ans != 'C'){
                std::cout << "invalid character, enter 'y'/'n' to conform of cencel: ";
                std::cin.clear();
                std::cin.ignore(100,'\n');
                std::cin >> ans;
            }
            if(ans == 'y' || ans == 'Y'){
                is_find = 1;

                int oper_id{};
                std::cout << "\n1. first name," << std::endl << "2. last name," << std::endl << "3. phone number," << std::endl << "4. email," << std::endl << "5. cencel" << std::endl;
                std::cout << "Enter the ID of info type to edit: ";
                std::cin >> oper_id;
                
                while(oper_id < 1 || oper_id > 5){
                    std::cin.clear();
                    std::cin.ignore(100,'\n');
                    std::cout << "Incorrect ID, enter '1', '2', '3', '4' or '5': ";
                    std::cin >> oper_id;
                }
                if(oper_id == 5){
                    std::cout << "\n----------Cenceled----------" << std::endl;
                    return 0;
                }
                std::cout << "enter the new data: ";
                std::string data_e{};
                std::cin >> data_e;
                while(!(tmp_per.*tmp_per.opers_set.at(oper_id))(data_e)){
                    std::cout << "Invalid data, try again: ";
                    std::cin.clear();
                    std::cin.ignore(100,'\n');
                    std::cin >> data_e;
                }
            }
            else if(ans == 'c' || ans == 'C'){
                std::cout << "\n----------Cenceled----------" << std::endl;
                return 0;
            }
            else{
                is_find = 0;
            }
        }
        tmp_data_base.push_back(tmp_per);
    }
    if(!is_find){
        std::cout << "Conatact didnt been detected! " << std::endl;
    }

//clear file
    std::ofstream tmp_strema(path);
    tmp_strema.close();
    
//returnning correct data_base; 
    int i = 0;
    in_s.seekp(0, std::ios::beg);
    in_s.clear();



    while(i < tmp_data_base.size()){
        in_s << tmp_data_base.at(i);
        ++i;
    }
    std::cout << "---Done---" << std::endl;
    return 1;
}


int main(){

    std::fstream data_base;
    std::string path{"data.txt"};
    data_base.open(path, std::fstream::out | std::fstream::in | std::fstream::app);
    
   
    int com_id{};
    while(true){
        com_id = 0;
        std::cout << "\n******** ADDRESS BOOK ********" << std::endl
                  << "Enter the ID of the command to execute:" << std::endl
                  << "1. Add a new contact" << std::endl 
                  << "2. Delete the contact" << std::endl 
                  << "3. Edit the contact" << std::endl 
                  << "4. Search contact by name, surname, email, or phone number" << std::endl
                  << "5. exit" << std::endl
                  << "Command ID: ";
        
        std::cin >> com_id;
        
        while (com_id < 1 || com_id > 5) {
            std::cout << "Wrong command ID. Please enter a valid command ID: ";
            std::cin.clear(); 
            std::cin.ignore(100,'\n');                 
            std::cin >> com_id;
        }

        if(com_id == 1){
            add_person(data_base);
        }
        else if(com_id == 2){
            delete_person(data_base,path);
        }
        else if(com_id == 3){
            edit_person(data_base,path);
        }
        else if(com_id == 4){
            Person tmp_p = search_person(data_base);
            Person def_p;
            if(tmp_p == def_p){
            }
            else{
                tmp_p.print();
            }
            
        }
        else if(com_id == 5){
        std::cout << "---EXIT---" << std::endl;
        break;
    }
}
    
    data_base.close();
    return 0;

}
