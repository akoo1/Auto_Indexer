
#ifndef DSSTRING_H
#define DSSTRING_H

#include "DSVector.h"


class DSString {


private:
    char* data;
    DSVector<char*> page_nums;




public:

    DSString();      								// default constructor
    DSString(char* new_data);  						// parameterized constructor

    ~DSString();									// destructor
    DSString(const DSString& rhs);			    	// copy constructor
    DSString& operator=(const DSString& rhs);	    // copy assignment operator


    DSString& operator=(const char* new_data);

    // my projects works good in github action, no issues, but when I added in the catch test cases, I’m having errors.
    // Adding "const" at the end of each overloaded operator fixed it the errors

    bool operator<=(const DSString& rhs) const;            // overloaded less than or equal to operator
    bool operator>=(const DSString& rhs) const;            // overloaded greater than or equal to operator
    bool operator<(const DSString& rhs) const;             // overloaded less than operator
    bool operator>(const DSString& rhs) const;             // overloaded greater than operator
    bool operator==(const DSString& rhs) const;            // overloaded equal to operator
    bool operator==(const char* rhs) const;                // overloaded equal to operator

    // DSString operator+(const DSString& oriObj);     // ? why not return the reference of the object
    // DSString& operator+=(const DSString& oriObj);   // ?


    void add_page_num(char* page_num);
    char* getData();
    DSVector<char*> get_vec();
    int get_page_num_vec_size();
    void print();


    // unused functions
    DSString substring(int start, int num_chars);
    int get_data_length();
    bool is_empty();
    bool constains(char* sub_str);

};




#endif












