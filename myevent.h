#ifndef MYEVENT_H
#define MYEVENT_H
#include <QEvent>

class myevent : public QEvent
{
public:
    //myevent() : QEvent((QEvent::Type)2000)) {}
    static const QEvent::Type myType = static_cast<QEvent::Type>(QEvent::User + 1);
};

#endif // MYEVENT_H
