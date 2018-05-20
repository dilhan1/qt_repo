#include "datastore.h"

datastore::datastore(QObject *parent) : QObject(parent), count(0), msg("%1 Hits")
{
    msg.arg(count);
}

void datastore::callMeFromQML(){
    qDebug("Inside Call Me From QML");
    count++;
    emit increaseOne(msg.arg(count));
}
