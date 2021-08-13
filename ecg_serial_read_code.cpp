#include<wiringSerial.h>
#include<iostream>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;


string convertToString(char* a, int size)
{
    string s(a);
    return s;
}

int main()
{ 
 ofstream myfile; 
 int serial_port;
 char input;
 char input1;
 serial_port = serialOpen("/dev/ttyACM0",115200);  
 char a[100] = {'4'};
 int cnt =0;
 int index = 0;
 string array_string;
 int buffer_size = 0;

 while (1) 
 {
     if (serialDataAvail(serial_port))
     {
       while (serialDataAvail(serial_port))
       {
         
         input = serialGetchar(serial_port);
         while(input !='\n'){
           input = serialGetchar(serial_port);
         }

         char array[25];
         int n=0;         
         while(input !='\r'){
           input = serialGetchar(serial_port);
           array[n] = input;
           n++;
          //  cout<<input;
         }
        array[n]='\0';
        int buffer_size = sizeof(array) / sizeof(char);
        string s_a = convertToString(array, buffer_size);
        //array_string = array;
        vector<string> v;
        stringstream ss(s_a);
        while (ss.good()) {
          string substr;
          getline(ss, substr, ',');
          v.push_back(substr);
        }
        float val1 = std::stof(v[0]);
        float val2 = std::stof(v[1]);
        cout<<val1<<endl;
        //cout<<val1<<" "<<val2<<endl;
        myfile.open ("spo2.txt");
        myfile <<val1<<","<<val2;
        myfile.close();

        }
      }
   }

}