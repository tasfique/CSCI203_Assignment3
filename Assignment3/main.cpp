//Name-Tasfique Enam
//Student ID- 5886429

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define MAXCHAR 256
using namespace std;

void rabinKarpSearch(string mainString, string pattern, int prime, int array[], int *index) {
   int patternLength = pattern.size();
   int stringlength = mainString.size();
   int charIndex, patternHash = 0, stringHash = 0, h = 1;

   for(int i = 0; i<patternLength-1; i++) {
      h = (h*MAXCHAR) % prime;    //calculating h = {d^(M-1)} mod prime
   }

   for(int i = 0; i<patternLength; i++) {
      patternHash = (MAXCHAR*patternHash + pattern[i]) % prime;    //pattern hash value
      stringHash = (MAXCHAR*stringHash + mainString[i]) % prime;   //hash for first window
   }

   for(int i = 0; i<=(stringlength-patternLength); i++) {
      if(patternHash == stringHash) {      //when hash values are same check for matching
         for(charIndex = 0; charIndex < patternLength; charIndex++) {
            if(mainString[i+charIndex] != pattern[charIndex])
               break;
         }

         if(charIndex == patternLength) {    //the pattern is found
            (*index)++;
            array[(*index)] = i;
         }
      }

      if(i < (stringlength-patternLength)) {    //find hash value for next window
         stringHash = (MAXCHAR*(stringHash - mainString[i]*h) + mainString[i+patternLength])%prime;
         if(stringHash < 0) {
            stringHash += prime;    //when hash value is negative, make it positive
         }
      }
   }
}

int main()
{
    string fileName;
    string line;
    ifstream ifs;
    int c = 0;
    bool check = true;
    char data;
    string pattern;
    int prime = 101;
    int index = -1;
    //char arrayStorage [];

    do{
        cout << "Enter the name of the File with .txt " << endl;
        cin >> fileName;

        if(fileName != "document.txt") {
            cout << "File name is invalid." << endl;
        } else {
            ifs.open("document.txt");

            if (ifs.is_open()) {
                cout<<"The File have been successfully opened." << endl;
                while(getline(ifs, line)) { ///Do a or condition for the loop to work if the T is greater than 500.
                cout << "\n" << line << "\n"<< endl;
                c += line.length();
                //c++;
                }
                cout <<"The text file contains " << c << " Characters. \n" << endl;
                if(c > 500) {
                    cout << "The Characters in the Text file is greater than 500 " << endl; //validation for over 500 characters.
                    cout << "Change the content in your text file " << endl;
                    exit(0);
                }
            } else {
                cout << "File failed to Open " << endl;
                check = false;
            }
            ifs.close();
        }
    }while(fileName != "document.txt" || check == false);

    ifs.close();

    cout << "\nEnter the pattern you want to find " << endl; ///S needs to be smaller than 10 characters.
    cin >> pattern; //S
    int c2 =0;
    c2 += pattern.length();
    cout << "\nPattern length is " << c2 << "\n" << endl;
    while (c2>10) { //validation for characters more than 10
        cout << "\nThe Pattern you have entered is greater than 10 " << endl;
        cout << "\nEnter the pattern you want to find " << endl;
        cin >> pattern; //S
        c2=0;
        c2 += pattern.length();
        //cout << c2 << endl;
    }
    int arr [c];
    rabinKarpSearch(line, pattern, prime, arr, &index); //putting all the values in the function.

    for (int i=0; i<=index; i++) { //for loop to find the pattern in the given string.
        cout << "Pattern found at position: " << arr[i]<<endl;
    }


    return 0;
}
