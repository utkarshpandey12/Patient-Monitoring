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
 //ofstream myfile; 
 int serial_port;
 char input;
 //char input1;
 serial_port = serialOpen("/dev/ttyUSB0",115200);  
 //char a[100] = {'4'};
int cnt =0;
int index = 0;
int flag = 0;
 //string array_string;
 //int buffer_size = 0;
 //float val1;
 //float val2;
 //vector<string> v;
 char array[25];
 char temp1[15];
 char temp2[15];
 //string s_a;

 while (1) 
 {
     if (serialDataAvail(serial_port))
     {  
       while (serialDataAvail(serial_port))
       {
         array[0] = '\0';
         input = serialGetchar(serial_port);
         while(input !='\n'){
           input = serialGetchar(serial_port);
         }

         
         int n=0;         
         while(input !='\r'){
           input = serialGetchar(serial_port);
           array[n] = input;
           n++;
          //  cout<<input;
         }
        array[n]='\0';
        index = 0;
        cnt = 0;
        //int buffer_size = sizeof(array) / sizeof(char);
        while (array[index]!='\0')
        { 
          if (flag==0 && array[index]!=','){
          temp1[cnt] = array[index];
          index++;
          cnt++;
          }
          if (flag==1){
          temp2[cnt] = array[index];
          index++;
          cnt++;

          }
          if (array[index]==','){
            cnt = 0;
            flag = 1;
            temp1[index] = '\0';

          }


        }
        temp2[cnt] = '\0';
        

        cout<<temp1<<temp2<<endl;
        //int buffer_size = sizeof(array) / sizeof(char);
        //s_a = convertToString(array, buffer_size);
        //cout<<s_a<<endl;
        
        
       
        //array_string = array;
        // v.clear();
        // stringstream ss(s_a);
        // while (ss.good()) {
        //   string substr;
        //   getline(ss, substr, ',');
        //   v.push_back(substr);
        // }
        // try{
        // val1 = std::stof(v[0]);
        // val2 = std::stof(v[1]);
        // //cout<<val1<<endl;
        // //cout<<val1<<" "<<val2<<endl;
        //myfile.open ("ecg.txt");
        //myfile<<s_a;
        //myfile.close();
        // }
        // catch (...){
        //   cout<<input<<endl;
        // }

        }
        
      }
 
   }

}