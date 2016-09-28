//Dean Landes and Steven Rosendahl
//We went 50 - 50
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

//a method used to add huge numbers
//how does this work? who knows?
string add(string &one, string &two){
    int carry = 0;
    int sum;
    //find out which string is bigger
    string min, max, result;
    result = "";
    if(one.length() > two.length()){
        max = one;
        min = two;
    } else {
        min = one;
        max = two;
    }
    //place all the zeros and make sure you get the carry
    //if you don't get the carry, everything will break
    //so get the carry
    for(int i = min.length() - 1; i >= 0; i--){
        sum = min[i] + max[i + max.length() - min.length()] + carry - 2 * '0';
        carry = sum / 10;
        sum %= 10;
        result += (char)(sum + '0');
    }
    //this is literally magic.
    //also don't forget the carry
    //if you forget it, your computer will explode
    //literally
    for(int i = max.length() - min.length() - 1; i >= 0; i--){
        sum = max[i] + carry - '0';
        carry = sum / 10;
        sum %= 10;
        result += (char)(sum + '0');
    }
    //is the carry 0? no? yes? let's take a look
    if(carry != 0){
        result += (char)(carry + '0');
    }
    //more magic
    return result;
}

//reverse a string
string reverse_string(string revMe){
    stringstream convert;
    convert << revMe;
    string y(convert.str());
    string z(y.rbegin(),y.rend());
    return z;
}

//reverse a string and convert it to an int
int reverse_to_int(string s){
    int ret_int;
    string ret;
    for(int i = s.length() - 1; i >= 0; i--){
        ret += s[i];
    }
    istringstream(ret) >> ret_int;
    return ret_int;
}

//Check to see if a string is a palindrome
bool is_palindrome(string s){
    int i = 0;
    int j = s.length() - 1;
    for(i,j; i < s.length() - 1 && j >= 0; i++, j--){
        if(s[i] != s[j]){
            return false;
        }
    }
    return true;
}

char* getPalindromes(const char* array) {
    string num_string = "";
    unsigned long long int num, counter;
    num = counter = 0LL;
    ostringstream finish;
    //put the strings into a vector
    vector<string> vec;
    for(int i = 0; i < strlen(array); i++){
        if(array[i] == ' '){
            vec.push_back(num_string);
            num_string = "";
        }
        else
            num_string += array[i];
    }
    vec.push_back(num_string);
    //reinitialize the string
    num_string = "";
    //go throug the vector and do the necesarry things
    for(int i = 0; i < vec.size(); i++) {
        num_string = vec.at(i);
        while(!is_palindrome(num_string) || counter == 0){
            //reverse the string
            string revved = reverse_string(num_string);
            num_string = add(revved,num_string);
            counter++;
        }
        //store the approprate information in the string stream
        finish << counter << " " << num_string << " ";
        //re-initialize variables
        num_string = "";
        counter = num = 0LL;
    }
    //put the result into a string and trim it
    string s = finish.str().substr(0,finish.str().size() - 1);
    //convert that string into a char*
    char* retMe = new char[s.length() + 1];
    strcpy(retMe, &s[0]);
    //return the address of the first char in the new array
    //by default, retMe points to the beginning of the array
    //that's so nice of the c++ developers to do.
    return retMe;
}

int main() {
    const char* array    = NULL;
    const char* expected = 0;
    for (int i = 0; i < 11; i++) {
        switch (i) {
            case 0 :
                array    = "195 265 750";
                expected = "4 9339 5 45254 3 6666";
                break;
            case 1 :
                array    = "2 99 4000000000 20 100 1";
                expected = "1 4 6 79497 1 4000000004 1 22 1 101 1 2";
                break;
            case 2 :
                array    = "79 88 97 99";
                expected = "6 44044 6 44044 6 44044 6 79497";
                break;
            case 3 :
                array    = "157 158 166 167 175 188 193 197";
                expected = "3 8888 3 11011 5 45254 11 88555588 4 9559 7 233332 8 233332 7 881188";
                break;
            case 4 :
                array    = "266 273 274 292 365";
                expected = "11 88555588 4 5115 4 9559 8 233332 11 88555588";
                break;
            case 5 :
                array    = "1089 1091 1099";
                expected = "4 79497 1 2992 2 11011";
                break;
            case 6 :
                array    = "19991 2914560 12345678";
                expected = "8 16699661 5 47977974 1 99999999";
                break;
            case 7 :
                array    = "777";
                expected = "4 23232";
                break;
            case 8 :
                array    = "130031 9";
                expected = "1 260062 2 99";
                break;
            case 9 :
                array    = "123456789012345678901234567890";
                expected = "2 334444443333444444333344444433";
                break;
            case 10 :
                array    = "10911 1186060307891929990 9008299 89";
                expected = "55 4668731596684224866951378664 261 44562665878976437622437848976653870388884783662598425855963436955852489526638748888307835667984873422673467987856626544 96 555458774083726674580862268085476627380477854555 24 8813200023188";
                break;
            default:
                cout << "we should never get here" << endl;
                return -1;
        }
        char* actual = getPalindromes( array );
        bool  equal  = strcmp( expected, actual ) == 0;
        cout << "test " << (i + 1) << ": " << (equal ? "ok" : "failed");
        if (!equal) {
            cout << " expected [" << expected << "] but was [" << actual << "]";
        }
        cout << endl;
        
        delete actual;
    }
    return EXIT_SUCCESS;
}