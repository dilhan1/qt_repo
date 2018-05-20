#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>

class datastore : public QObject
{
    Q_OBJECT
public:
    explicit datastore(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DATASTORE_H