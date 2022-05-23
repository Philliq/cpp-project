#include "jitteryinput.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;


#define inttype uint16_t

char Nutzlast[] = "Das hier sollte alles auf einer Zeile stehen!!!\r\n";
char Outpout[128] = { 0 };

jitteryInput::jitteryInput(QObject *parent) : QObject(parent){
    srand(time(nullptr));

    QObject::connect(&this->tim, &QTimer::timeout, [&](){
        static inttype cnt = 0;
        static int l_pos = 0;
        int random_variable = 1 + rand()/((RAND_MAX + 1u)/sizeof(Nutzlast));
        int new_pos = ( l_pos + random_variable ) % ( sizeof(Nutzlast) -1 );
        memset(Outpout, 0, sizeof Outpout);

        for( int i = 0; l_pos != new_pos; i++ ){
            Outpout[i] = Nutzlast[l_pos];
            l_pos = ( l_pos + 1 ) % ( sizeof(Nutzlast) -1 );
        }
        cnt++;
        QString message(Outpout);
        emit newData(message);
    });
}

void jitteryInput::start(int msec){
    this->tim.start(msec);
}
