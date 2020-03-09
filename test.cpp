//
// Created by Alfred on 2/28/20.
//

#include "catch.h"

#include <cstring>
#include "DSString.h"
#include "DSVector.h"


// After each SECTION, the variables in the scope will be reset to the variables in the TEST_CASE

TEST_CASE("DSString class", "[DSString]"){

    DSString s[10];

    s[0] = DSString("testDSString");
    s[1] = DSString("a test string");
    s[2] = DSString("");
    s[3] = DSString("THIS IS AN UPPERCASE STRING");
    s[4] = DSString("this is an uppercase string");
    s[5] = DSString("\n");
    s[6] = DSString("");
    s[7] = DSString("  split  split  split  ");
    s[8] = DSString("                          ");
    s[9] = DSString("testDSString");




    SECTION("Equality operators"){
        REQUIRE(s[0] == DSString("testDSString"));
        REQUIRE(s[0] == s[9]);
        REQUIRE(s[2] == "");
        REQUIRE(s[1] == "a test string");
        REQUIRE(!(s[3] == s[4]));
    }

    SECTION("Greater than operators"){
        REQUIRE(s[0] > DSString("test"));
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }


    SECTION("Less than operators"){
        REQUIRE(s[0] < DSString("testDSStringgg"));
        REQUIRE(s[0] < s[4]);
        REQUIRE((s[7] < s[4]));
    }


    SECTION("Assignment operators"){
        DSString str;
        str = "a test string";
        REQUIRE(str == s[1]);
        str = DSString("testDSString");
        REQUIRE(str == s[0]);
        str = "";
        REQUIRE(str == s[6]);
        str = DSString("\n");
        REQUIRE(str == s[5]);
    }



    SECTION("get_data_length function"){
        REQUIRE(s[9].get_data_length() == 12);
        REQUIRE(s[2].get_data_length() == 0);
        REQUIRE(s[8].get_data_length() == 26);
        REQUIRE(s[3].get_data_length() == 27);
    }

    SECTION("is_empty function") {
        REQUIRE(s[2].is_empty() == false);
        REQUIRE(s[0].is_empty() == false);
    }

    SECTION("Substring function"){
        REQUIRE(s[0].substring(0, 5) == "testD");
        REQUIRE(s[4].substring(0, 4) == "this");
        REQUIRE(s[4].substring(1, 3) == "his");
    }

}




TEST_CASE("DSVector class", "[DSVector]"){

    DSVector<int> v1;
    DSVector<char> v2;


    SECTION("get_size function") {

        REQUIRE(v1.get_size() == 0);
        REQUIRE(v2.get_size() == 0);

        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);
        v1.push_back(5);
        v1.push_back(6);
        REQUIRE(v1.get_size() == 6);

        v2.push_back('a');
        v2.push_back('b');
        v2.push_back('c');
        REQUIRE(v2.get_size() == 3);
    }



    SECTION("get_capacity function") {

        REQUIRE(v1.get_capacity() == 1);
        REQUIRE(v2.get_capacity() == 1);

        v1.push_back(1);
        REQUIRE(v1.get_capacity() == 1);

        v1.push_back(2);
        REQUIRE(v1.get_capacity() == 2);

        v1.push_back(3);
        REQUIRE(v1.get_capacity() == 4);

        v1.push_back(4);
        REQUIRE(v1.get_capacity() == 4);

        v1.push_back(5);
        REQUIRE(v1.get_capacity() == 8);


        v2.push_back('a');
        REQUIRE(v2.get_capacity() == 1);

        v2.push_back('b');
        REQUIRE(v2.get_capacity() == 2);

        v2.push_back('c');
        REQUIRE(v2.get_capacity() == 4);
    }



    SECTION("pop function") {

        v1.push_back(1);
        v1.pop();
        REQUIRE(v1.get_size() == 0);

        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);
        v1.push_back(5);
        v1.pop();
        v1.pop();
        REQUIRE(v1.get_size() == 3);
    }
    


    SECTION("[] operator") {

        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);
        v1.push_back(5);
        REQUIRE(v1[0] == 1);
        REQUIRE(v1[1] == 2);
        REQUIRE(v1[2] == 3);
        REQUIRE(v1[3] == 4);
        REQUIRE(v1[4] == 5);

        v2.push_back('a');
        v2.push_back('b');
        v2.push_back('c');
        REQUIRE(v2[0] == 'a');
        REQUIRE(v2[1] == 'b');
        REQUIRE(v2[2] == 'c');
    }


    SECTION("Copy assignment operator") {

        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);
        v1.push_back(5);

        DSVector<int> v3;
        v3.push_back(99);

        v1 = v3;
        REQUIRE(v1[0] == 99);
    }


    SECTION("is_empty function") {

        REQUIRE(v1.is_empty() == true);

        v1.push_back(1);
        REQUIRE(v1.is_empty() == false);

        v1.pop();
        REQUIRE(v1.is_empty() == true);
    }


}





