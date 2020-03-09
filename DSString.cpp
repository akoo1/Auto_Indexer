//
// Created by Alfred on 2/7/20.
//

#include <iostream>
#include <cstring>

#include "DSString.h"

using namespace std;


// default constructor
DSString::DSString() {

    data = nullptr;

}


// parameterized constructor
DSString::DSString(char* new_data) {

    if (new_data != nullptr) {
        data = new char[strlen(new_data) + 1];   // add 1 spaces for the null terminator
        strcpy(data, new_data);                  // copies str2 over to str1. Deep copy
    }
    else {
        data = nullptr;
    }

    
}


// destructor
DSString::~DSString() {

   if (data!= nullptr) {
        delete[] data;
        data = nullptr;
   }
}


// copy constructor
DSString::DSString(const DSString& rhs) {

    if (rhs.data != nullptr) {
        data = new char[strlen(rhs.data) + 1];
        strcpy(data, rhs.data);
    }
    else {
        data = nullptr;
    }

    // All DSString's data members need to be copied in copy constructor to handle vector resizing and copying    
    page_nums = rhs.page_nums;  // Added in order to make DSVector<char*> page_nums; work 

    //cout << "(DSString) copy constructor called..." << endl;

}
// reference: https://stackoverflow.com/questions/57731678/how-do-implement-the-copy-constructor-for-my-custom-c-class




// copy assignment operator
DSString& DSString::operator=(const DSString& rhs) {

    // avoid self-copy
    if (this != &rhs) {

        // destructor
        delete[] data;

        // copy constructor
        if (rhs.data != nullptr) {
            data = new char[strlen(rhs.data) + 1];
            strcpy(data, rhs.data);

        }
        else {
            data = nullptr;
        }

        page_nums = rhs.page_nums;  // Added in order to make DSVector<char*> page_nums; work 
    }

    //cout << "(DSString) copy assignment operator called..." << endl;

    return *this;
}


//================================================================================================================================


bool DSString::operator<=(const DSString& rhs) const{

    if (strcmp(this->data, rhs.data) < 0) {
        return true;
    }
    else if (strcmp(this->data, rhs.data) == 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DSString::operator>=(const DSString& rhs) const {

    if (strcmp(this->data, rhs.data) > 0) {
        return true;
    }
    else if (strcmp(this->data, rhs.data) == 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DSString::operator<(const DSString& rhs) const {

    if (strcmp(this->data, rhs.data) < 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DSString::operator>(const DSString& rhs) const {

    if (strcmp(this->data, rhs.data) > 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DSString::operator==(const DSString& rhs) const {

    if (strcmp(this->data, rhs.data) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool DSString::operator==(const char* rhs) const {

    if (strcmp(this->data, rhs) == 0) {
        return true;
    }
    else {
        return false;
    }
}






// Another copy assignment operator
DSString& DSString::operator=(const char* new_data) {

    // avoid self-copy
    if (this->data != new_data) {

        // destructor
        delete[] data;

        // copy constructor
        if (new_data != nullptr) {
            data = new char[strlen(new_data) + 1];
            strcpy(data, new_data);

        }
        else {
            data = nullptr;
        }
    }


    return *this;
}




DSString DSString::substring(int start, int num_chars) {

    // input validation
    if (start >= 0 && num_chars > 0) {
        // if index exceeds the length of data, then just include all the chars after starting index
        if ((start + num_chars) > strlen(data)) {
            num_chars = strlen(data) - start;
        }

        char* temp = new char[num_chars + 1];   // add 1 space for the null terminator
        memcpy(temp, data + start, num_chars);

        temp[num_chars] = '\0';    // append the null terminator

        DSString substr(temp);

        delete [] temp;

        return substr;
    }

    // for invalid inputs, return an empty DSString
    return DSString();
}
// reference: https://stackoverflow.com/questions/57751384/what-is-wrong-with-this-substring-function






bool DSString::constains(char* sub_str) {

	// strstr() returns a pointer to the first occurrence of sub_str in str, or a null pointer if sub_str is not part of str.
	if (strstr(data, sub_str) != nullptr) {
		return true;
	}
	else {
		return false;
	}
}


char* DSString::getData() {
    return data;
}



int DSString::get_data_length() {
    return strlen(data);
}



bool DSString::is_empty() {
    if (data == nullptr) {
        return true;
    }
    else {
        return false;
    }
}


void DSString::print() {
    cout << data << ": ";
    
    page_nums.print_pages();  // This calls the print_pages() function in DSVector class
}


// This function push_back a char* that contains the page_num to the data mamber page_nums, which is a vector of DSStrings 
void DSString::add_page_num(char* page_num) {
    page_nums.push_back(page_num);
}


int DSString::get_page_num_vec_size() {
    return page_nums.get_size();
}


DSVector<char*> DSString::get_vec() {
    return page_nums;
}





