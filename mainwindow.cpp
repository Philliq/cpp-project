#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <sstream>

using namespace std;


char ringbuffer[512];
int head = 0;
int tail = 0;
void ringbuffer_add(char zeichen){
    ringbuffer[head] = zeichen;
    head += 1;
    if(head>=512) head = 0;

}

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
    /*
     * Aufgabe: Nehmen Sie bitte den Input (text) engegen und
     * speichern Sie alle einzelnen Zeichen in einem Ringpuffer ab.
     * anschließend gehen Sien den Rinpuffer von Beginn an durch und
     * suchen sie nach einem Zeilenumbruch. Wenn Sie den Zeilenumbruch
     * gefunden haben, entnehmen sie alle zeichen inklusive dem umbruch
     * und geben ssie diese im unteren textfeld aus.
     */
    //ui->textEdit_2->setText(text);

//cout << text.toStdString() << endl;
    bool nl = false;
    stringstream output;

    for(int i=0; i<text.count(); i++){
        ringbuffer_add(text[i].toLatin1());
        if(text[i] == '\n'){
            nl = true;
            //cout << "Ende der Zeile" << endl;

        }
    }

    if(nl){
        while(1){
            char nc = ringbuffer_get();
            output << nc;
            if(nc == '\n'){
                ui->textEdit_2->setText(QString::fromStdString(output.str()));
                break;
            }
        }


    }







}

