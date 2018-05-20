#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QDebug>

class datastore : public QObject
{
    Q_OBJECT
public:
    explicit datastore(QObject *parent = nullptr);

signals:
    void increaseOne(QString ms);

public slots:
    void callMeFromQML();

private:
    int count;
    QString msg;
};

#endif // DATASTORE_H
