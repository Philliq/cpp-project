#ifndef JITTERYINPUT_H
#define JITTERYINPUT_H

#include <QObject>
#include <QTimer>

class jitteryInput : public QObject
{
    Q_OBJECT
    public:
        explicit jitteryInput(QObject *parent = nullptr);
        void start(int msec);

    private:
        QTimer tim;

    signals:
        void newData(QString data);

};

#endif // JITTERYINPUT_H
