
#define  CATCH_CONFIG_RUNNER
#include  "catch.h"

#include "DSVector.h"
#include "DSString.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

// This is the second version of the AutoIndexer
// It reads in one line at a time and look for keywords
// It accounts for cases where there are '< or '>' in the text, ex.  P<0.05.



/* The high-level design and outline of the AutoIndexer program */

// 1. Read in keywords from input file
// 2. Lowercase every key word
// 3. Create a vector of DSString, push back each keyword as a DSString, 
//    Check for duplicates, make sure only unique keywords in the vector.
// 4. Get the page number
// 5. Compare each keyword with each line, to see if the keyword is a substring of the line
// 6. If it's a substring, add the current page number to the key word's data attribute "page_nums", a DSVector of int
// 7. Make sure not to double count a keyword in the same line, until the next page number is read
// 8. Sort the DSVector of DSString
// 9. Properly format the output to create an index page


// helper functions
void set_lower(char*);
char get_upper(char cha);
int isSubString(char* str, char* sub_str);
bool way_to_sort(DSString& lhs, DSString& rhs);


// command line arguments to run the program
// ./a.out keywords1.txt book1.txt output01.txt

int main(int argc, char **argv) {

	// If pass less than 4 arguments in the terminal , run the test.
    // Else, run the program.
    // (2 input files +  1 output file + ./a.out) usually we will pass 4 args in terminal.
    if(argc < 4) {
        Catch::Session().run();
        return 0;
    }



	// Reading key words
    char key_word_file[50] = "keywords1.txt";

    ifstream key_word_file_ifs(argv[1]);

    if (!key_word_file_ifs.is_open()) {
        cout << "Unable to open file: " << key_word_file << endl;
        return -1;
    }


    // A vector of DSString, push back each keyword as a DSString
    DSVector<DSString> key_words_list;


    char line_key_word[1000];


    while (!key_word_file_ifs.eof()) {

    	// get one key word
        key_word_file_ifs.getline(line_key_word, 100, '\n');

        // lowercase the key word
        set_lower(line_key_word);


        // make sure initially there is at least one object in the vector, so the for loop will execute
        if (key_words_list.is_empty()) {
			key_words_list.push_back(DSString(line_key_word));
	     }



        // check if the key word already exists in the key_words_list or not 
        // iterate through the vector
        bool key_exists = false;

        for (int i = 0; i < key_words_list.get_size(); i += 1) {

        	// if exists already, break out of the for loop, check the next key word
        	if (strcmp(line_key_word, key_words_list[i].getData()) == 0) { // strcmp() returns 0 if both c-strings are equal, otherwise > 0 or < 0
        		
        		key_exists = true;
        		break;
        	}
        }


        // doesn't already exist, push_back a new keyword object
        if (!key_exists) {
		
			key_words_list.push_back(DSString(line_key_word));
		}
    }



    key_word_file_ifs.close();



//=================================================================================================================================



	// Reading text from the book
    char book_file[50] = "book1.txt";

   
    // Because 1. char[] are not assignable, we cannot redeclare a new char[] for every for loop iteration 
    //         2. a char* cannot be initialized
    // so a work-around to it is to either assign the char[] to a new char* or declare a fixed size dynamic array

    // char book_line[10000];
    // char* book_line_arr = book_line;

    // char page_num[6];
    // char* page_num_arr = page_num;



    // a buffer that stores a page of text
    char* book_line = new char[10000];

    // a buffer that stores a page of text
    char* page_num = new char[6];

    // set the bool varibale to false once a keyword is found in a line, and it will not be reset to true until the next page is read
    // to aviod double counting a keyword 
    bool can_add_page;
    


    



    // Iterate through the key_words_list
    // Compare a key word with every page, to see if the key word is a substring of each page
	// If it's a substring, add the current page number to the key word's data attribute "page_nums", which is a DSVector of int
    for (int i = 0; i < key_words_list.get_size(); i += 1) {


	    // create an input file object that's associated with the book file
	    ifstream my_book_ifs(argv[2]);

	    // input filename validation
	    if (!my_book_ifs.is_open()) {
	        cout << "Unable to open file: " << book_file << endl;
	        return -1;
	    }	


	    while (!my_book_ifs.eof()) {
	    	
	    	// get one line at a time
	    	// <1>
	        my_book_ifs.getline(book_line, 10000, '\n');

	        // lowercase all letter in the page 
	        set_lower(book_line);


	        // Check if it's a page line or text line

	        // If the first char is '<' and the last char is '>' in this line, it's a page line,
	        // get the page number (the page_num will not change for the rest of the lines until it finds the next <#>)
	        if (*(book_line) == '<' && *(book_line + strlen(book_line) - 1) == '>') {

	        	can_add_page = true;

		        // assign a new memory address for each page_num, so they don't all point to the same memory location 
		   		page_num = new char[6];

	        	int j;
		        // get the page number of a page by getting all chars between < > 
		        for (j = 0; j < strlen(book_line) - 2; j += 1) {
		        	page_num[j] = book_line[j + 1];
		        }

		        // Add a null-terminator right after the page numbers to avoid additional white spaces or garbage values
		        // being printed or written when cout, because we declared a fixed size char array
		        page_num[j] = '\0';  
	        }

	        // else it's a text line, start searching for keywords
	        else {
	        	// If the first found keyword in the line is an exact match 
		        if (isSubString(book_line, key_words_list[i].getData()) == 1 && can_add_page == true) {
		  
		        	key_words_list[i].add_page_num(page_num);

		        	can_add_page = false;
		        }

		        // Else if the first found keyword in the page is not an exact match, keep checking the rest of the line
		        else if (isSubString(book_line, key_words_list[i].getData()) == 0) {

		        	// Make the pointer to a char* that points to the first char of the current line, now point to
		        	// the last char of the first found keyword, to check the rest of the line 
		        	book_line = strstr(book_line, key_words_list[i].getData()) + strlen(key_words_list[i].getData());

		        	// Keep checking the rest of the line until the end of the line
		        	while (strstr(book_line, key_words_list[i].getData()) != nullptr) {

		        		if (isSubString(book_line, key_words_list[i].getData()) && can_add_page == true) {
				        	key_words_list[i].add_page_num(page_num);

				        	can_add_page = false;

				        	// Once an exact match is found, break out of the while loop, no need to check further,
				        	// but this will only break the while loop for the current line, the next line will still
				        	// be read and compared, so I added a bool variable to get around this problem 
				        	break;
		        		}

		        		else {
		        			// keep moving the pointer
		        			book_line = strstr(book_line, key_words_list[i].getData()) + strlen(key_words_list[i].getData());
		        		}
	        		}
				}
			}
		}


	 // close and reopen the book file every for loop iteration. Go through the whole book once for every keyword 
     my_book_ifs.close();

	}
	    



	// Sort the keyword list
	sort(key_words_list.get_arr(), key_words_list.get_arr() + key_words_list.get_size());

 


	bool new_index_letter = true;

    // Display the index page
	cout << endl;
	cout << "Index Page: " << endl;

    for (int i = 0; i < key_words_list.get_size(); i += 1) {

    	if (new_index_letter == true) {
    		// Formatting the output
	    	// Get the pointer to first char of each keyword, dereference it, and convert to uppercase 
			cout << "[" << get_upper(*(key_words_list[i].getData())) << "]" << endl;

			new_index_letter = false;
		}

    	key_words_list[i].print();

    	// If the first letter of the next keyword is different than the first letter of the current keyword, 
    	// set bool variable new_index_letter to true, so it will print out a new category header  
    	if (i < key_words_list.get_size() - 1) {     // so i doesn't go out of range
	    	if (*(key_words_list[i + 1].getData()) != *(key_words_list[i].getData())) {
				new_index_letter = true;
			}
		}

    }
    cout << endl;





    // Write data to the output file
	ofstream my_output_ifs(argv[3]);


	new_index_letter = true;

    for (int i = 0; i < key_words_list.get_size(); i += 1) {

    	if (new_index_letter == true) {
	    	// Get the pointer to first char of each keyword, dereference it, and convert to uppercase 
			// Formatting the output
			my_output_ifs << "[" << get_upper(*(key_words_list[i].getData())) << "]" << endl;

			new_index_letter = false;
		}


		my_output_ifs << key_words_list[i].getData() << ": ";

		// First for loop to iterate through a vector of DSStrings
		// Second for loop to iterate through a vector of char* in each DSString
		for (int j = 0; j < key_words_list[i].get_page_num_vec_size(); j += 1) {
			// To avoid printing an extra comma in the end
			if (j < key_words_list[i].get_page_num_vec_size() - 1) {
				my_output_ifs << key_words_list[i].get_vec()[j] << ", ";
			}
			else {
				my_output_ifs << key_words_list[i].get_vec()[j] << endl;
			}
		}

		// If the first letter of the next keyword is different than the first letter of the current keyword, 
    	// set bool variable new_index_letter to true, so it will print out a new category header  
    	if (i < key_words_list.get_size() - 1) {     // so i doesn't go out of range
			if (*(key_words_list[i + 1].getData()) != *(key_words_list[i].getData())) {
				new_index_letter = true;
			}
		}


	}

	my_output_ifs.close();


}


























// This functions takes a char array and lowercase every letter
void set_lower(char* cha) {

    for (int i = 0; cha[i] != 0; i += 1) {

        if ((cha[i] >= 'A') && (cha[i] <= 'Z')){       // Ascii table. A = 65, Z = 90, a = 97, z = 122.
            cha[i] = cha[i] - 'A' + 'a';
        }

    }
}


// This functions takes a char and return its uppercase letter
char get_upper(char cha) {

    if ((cha >= 'a') && (cha <= 'z')){       // Ascii table. A = 65, Z = 90, a = 97, z = 122.
        cha = cha - 'a' + 'A';
    }

    return cha;
}



// This function handles three different substring scenarios, and return either 1, -1, or 0 based on how the keyword substring 
// appeared in a book page.
int isSubString(char* str, char* sub_str) {

	
	// Suppose the current keyword is "owl" 

	// Returns 1 if there's an exact match. Meaning the char right after and the char right before the substring is not a letter
	// Yes: owl, owl. owl?    No: owls  owling   
	// Yes: form, from.       No: inform  infrom,     //  && !isalpha(*(strstr(str, sub_str) - 1))
    if (strstr(str, sub_str) != nullptr  &&  !isalpha(*(strstr(str, sub_str) + strlen(sub_str))) ) {
        return 1;
    }

    // Returns -1 if the keyword doesn't appear in the page at all
    else if (strstr(str, sub_str) == nullptr) {
        return -1;
    }

    // Returns 0 if there might be a match. Meaning the first keyword found in the page is "owls" or "owling", but 
    // there might be an exact match in the rest of the page, will need to keep checking.   
    else {
    	return 0;
    }
}
// Note: strstr() returns a pointer to the first occurrence of sub_str in str, or a null pointer if str2 is not part of str1.




// We usually need a third parameter to tell the sort() function how to compare special type/ custom objects in a vector, a bool function.
// We actually don't need to pass a comparator to sort() in this case, because we already overloaded the < operator,
// so it knows how to compare the objects lol
bool way_to_sort(DSString& lhs, DSString& rhs) {

    return lhs < rhs;
}






