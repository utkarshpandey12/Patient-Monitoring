#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


         //Create a curve chart
    ui->widget_graph->setObjectName(QString::fromUtf8("customPlot"));
    //ui->widget_graph->setBackground(Qt::white); //Set the background color

    ui->widget_graph->plotLayout()->insertRow(0);
    //ui->widget_graph->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_graph, "Cure")); //Insert a row and add a title element
    ui->widget_graph->addGraph(); // blue line
    ui->widget_graph->graph(0)->setPen(QPen(Qt::blue));
//    ui->widget_graph->graph(0)->setBrush(QBrush(QColor(240, 255, 200))); // The color of the shadow below the line
    ui->widget_graph->graph(0)->setAntialiasedFill(false);

         //Set up to zoom in and out
    ui->widget_graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);



     //Display the current numerical text
   textLabel = new QCPItemText(ui->widget_graph);
   //ui->widget_graph->addItem(textLabel);
   textLabel->setPositionAlignment(Qt::AlignTop); //Controls in the layout
   textLabel->position->setType(QCPItemPosition::ptAxisRectRatio); //Set the position proportionally, depending on the size of the axis rectangle, which is different from the viewport size
   textLabel->position->setCoords(0, 0); // place position at center/top of axis rect
   textLabel->setFont(QFont(font().family(), 15)); // make font a bit larger
   textLabel->setPen(QPen(Qt::black)); // show black border around text



         //Set the current curve name text
   textLabel2 = new QCPItemText(ui->widget_graph);
   //ui->widget_graph->addItem(textLabel2);
   textLabel2->setPositionAlignment(Qt::AlignBottom);
   textLabel2->position->setType(QCPItemPosition::ptAxisRectRatio);
   textLabel2->position->setCoords(0, 1.0);
   textLabel2->setFont(QFont(font().family(), 15)); // make font a bit larger
   textLabel2->setPen(QPen(Qt::black)); // show black border around text
   CureName="123";//Set curve name
   textLabel2->setText("CureName:"+CureName); //Display the current value


       //x coordinate axis setting
   //ui->widget_graph->xAxis->setLabel("time:");//Set the coordinate name

   ui->widget_graph->xAxis->setLabelColor(Qt::black);//Set the coordinate color
   ui->widget_graph->xAxis->setLabelPadding(1);//Set the axis name text distance from the axis tick mark
         //y coordinate axis setting
   //ui->widget_graph->yAxis->rescale(true);
  // ui->widget_graph->yAxis->setTickStep(25);// The size of the value is half of the y-axis, set the scale interval
   ui->widget_graph->yAxis->setLabelColor(QColor(0, 160, 230)); //Set the text color
   ui->widget_graph->yAxis->setRange(100,400); //Y axis range

       ui->widget_graph->xAxis2-> setTicks(false); //Do not display the axis
       ui->widget_graph->yAxis2-> setTicks(false); //Do not display the axis


    value0=1; //Test used
    value1=1;
    val1 = 0;
    key=0;
    QTimer *dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(0);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::realtimeDataSlot()
{
    key++;

    static double lastPointKey = 0;
    string line;
    ifstream myfile ("/home/pi/Downloads/testc/ecg.txt");
    if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {
          //cout << line << '\n';
        }
        myfile.close();
      }
    cout<<line<<endl;

    vector<string> v;
    stringstream ss(line);
    while (ss.good()) {
              string substr;
              getline(ss, substr, ',');
              v.push_back(substr);
            }
    try{
        val1 = std::stod(v[0]);
        //cout<<val1<<endl;
        if (key-lastPointKey >0.01) // at most add point every 10 ms
        {
                     //For testing
             //if(value0>0 && value0<10)
            //{
              //value0=value0+5;
           // }
            //else  {value0=5;}

            ui->widget_graph->graph(0)->addData(key,val1);

            lastPointKey = key;

        }
    }
    catch (...) {
      cout<<val1<<endl;
    }
    //if (line==""){
        //cout<<"empty line";
    //}
    //cout<<line<<endl;


    //textLabel->setText("Current:"+QString::number( value0 )); //Display the current value
         //ui->widget_graph->xAxis->setAutoTickStep(false); ////Set whether to automatically allocate tick spacing
    //ui->widget_graph->xAxis->setTickStep(0.5);// The size of the value is half of the y-axis, set the scale interval
    ui->widget_graph->xAxis->setRange(key,250,Qt::AlignRight);
    //ui->widget_graph->yAxis->setRange(val1-20,val1+20);
    //ui->widget_graph->xAxis->setRange(0,50);
    ui->widget_graph->replot();
}
