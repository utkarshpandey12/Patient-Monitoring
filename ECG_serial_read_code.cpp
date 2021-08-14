#include<wiringSerial.h>
#include<iostream>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;


int main()
{ 
  ofstream myfile; 
  int serial_port;
  char input;
  //char input1;
  serial_port = serialOpen("/dev/ttyUSB0",115200);  
  //char a[100] = {'4'};
 int cnt =0;
 int index = 0;
 int flag = 0;
 int count_avg = 0;
 int array_full = 0;

 //string array_string;
 //int buffer_size = 0;
 //float val1;
 //float val2;
 //vector<string> v;
 char array[25];
 char temp1[15];
 char temp2[15];
 double f1, f2;
 double ecg_avg , rr_avg;
 double x[10][2] = {{0.0,0.0},{0.0,0.0},{0.0,0.0},
      {0.0,0.0},{0.0,0.0},{0.0,0.0},{0.0,0.0},
          {0.0,0.0},{0.0,0.0},{0.0,0.0}};
 //string s_a;

 while (1) 
 {
     if (serialDataAvail(serial_port))
     { 
       while (serialDataAvail(serial_port))
       { 
         if (count_avg>9)
         {

         ecg_avg = f1/10;
         rr_avg = f2/10;
         
         if (array_full==10){
           array_full = 0;
         }
         if (array_full<10){
           x[array_full][0] = ecg_avg;
           x[array_full][1] = rr_avg;
           array_full++;
           cout<<x[0][0]<<" "<<x[0][1]<<endl;
           myfile.open ("ecg.txt");
           for (int i = 0; i < 10; i++)
            {
              for (int j = 0; j < 2; j++)
               { 
                if (j==0){
                myfile<<x[i][j];
                myfile<<',';}
                else{
                  myfile<<x[i][j]<<endl;
                }
               }
               //myfile<<endl;
            }

           myfile.close();
         }
         f1 = 0.0;
         f2 = 0.0;
         count_avg = 0;
               
         } 
         
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
        //cout<<array<<endl;
        index = 0;
        cnt = 0;
        flag = 0;
        temp1[0] = '\0';
        temp2[0] = '\0';
        //int buffer_size = sizeof(array) / sizeof(char);
        while (array[index]!='\0')
        { 
          if (flag==0 && array[index]!=','){
          temp1[cnt] = array[index];
          index++;
          cnt++;
          }
          if (flag==1 && array[index]!=','){
          temp2[cnt] = array[index];
          index++;
          cnt++;

          }
          if (array[index]==','){
            cnt = 0;
            flag = 1;
            temp1[index] = '\0';
            index++;

          }


        }
        temp2[cnt] = '\0';
        //cout<<temp1<<" "<<temp2<<endl;
        f1 += atof (temp1);
        f2 += atof (temp2);
        //cout<<f1<<" "<<f2<<endl;
        count_avg++;



        //cout<<temp1<<temp2<<endl;
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


