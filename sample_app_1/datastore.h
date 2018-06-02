#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "memsinterface.h"
#include "memsdata.h"
#include <pthread.h>

class datastore : public QObject
{
    Q_OBJECT
public:
    explicit datastore(QObject *parent = nullptr);

signals:
    void increaseOne(QString ms);
    void dataReceive(MemsData* md);

    void requestToStartPolling();
    void requestThreadShutdown();

    void fuelPumpTest();
    void ptcRelayTest();
    void acRelayTest();
    void injectorTest();
    void coilTest();
    void moveIAC(int desiredPos);

public slots:
    void callMeFromQML();

    void onDataReady();
    void onConnect();
    void onDisconnect();
    void onReadError();
    void onReadSuccess();
    void onFailedToConnect(QString dev);
    void onInterfaceThreadReady();
    void onNotConnected();
    void onEcuIdReceived(uint8_t* id);
    void onFuelPumpTestComplete();
    void onACRelayTestComplete();
    void onPTCRelayTestComplete();
    void onMoveIACComplete();
    void onCommandError();
    void onFaultCodeClearComplete();

private:
    int count;
    QString msg;
    MemsData *m_mems_data;

    QThread *m_memsThread;
    MEMSInterface *m_mems;

    //const float mapGaugeMaxPsi = 16.0;
    //const float mapGaugeMaxKPa = 160.0;

    bool m_actuatorTestsEnabled;

    //QHash<TemperatureUnits,QString> *m_tempUnitSuffix;
    //QHash<TemperatureUnits,QPair<int,int> > *m_tempRange;
    //QHash<TemperatureUnits,QPair<int,int> > *m_tempLimits;

    void connectToECU();
    void initializeMemsData();
    void buildSpeedAndTempUnitTables();
    int convertTemperature(int tempF);
    void workerThread(QString name);
    void workerThread2(QString name);
};

#endif // DATASTORE_H
