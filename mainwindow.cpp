#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <sstream>

using namespace std;


char ringbuffer[512];
int head = 0;
int tail = 0;
int globCounter = 0;

/** Fügt ein Zeichen in den Ringpuffer ein
 *  @param[in] zeichen Ein einzelnes Zeichen
 */
void ringbuffer_add(char zeichen){
    ringbuffer[head] = zeichen;
    head += 1;
    if(head>=512) head = 0;
}


/** Holt ein Zeichen aus dem Ringpuffer
 *  @return Das aktuelle Zeichen am Tail des Ringpuffers
 */
char ringbuffer_get(){
    char output = ringbuffer[tail];
    tail++;
    if(tail>=512) tail=0;
    return output;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    memset(ringbuffer, 0, sizeof(ringbuffer));
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::setInputText(QString text){
    ui->textEdit->setText(text);
}

void MainWindow::setOutputText(QString text){
    bool nl = false;
    stringstream output;

    for(int i=0; i<text.count(); i++){
        ringbuffer_add(text[i].toLatin1());
        if(text[i] == '\n'){
            nl = true;
            globCounter ++;
        }
    }

    if(nl){
        while(1){
            char nc = ringbuffer_get();
            output << nc;
            if(nc == '\n'){
                ui->textEdit_2->setText(QString("Zaehlerstand: ") + QString::fromStdString(to_string(globCounter)) + QString("\n") + QString::fromStdString(output.str()));
                break;
            }
        }
    }







}

