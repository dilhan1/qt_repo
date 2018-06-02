#include "datastore.h"
#include "memsdata.h"
#include <unistd.h>
#include <QCoreApplication>
#include <qtconcurrentrun.h>
#include <QThread>

datastore::datastore(QObject *parent) :
    QObject(parent),
    count(0),
    msg("%1 Hits"),
    //m_actuatorTestsEnabled(false),
    m_mems_data(0),
    m_memsThread(0),
    m_mems(0)
{
    //msg.arg(count);
    m_mems = new MEMSInterface("devttyAM0");

    m_mems_data = new MemsData();

    //connect to ECU
    connectToECU();
    initializeMemsData();

    connect(m_mems, SIGNAL(dataReady()), this, SLOT(onDataReady()));
    connect(m_mems, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(m_mems, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
    connect(m_mems, SIGNAL(readError()), this, SLOT(onReadError()));
    connect(m_mems, SIGNAL(readSuccess()), this, SLOT(onReadSuccess()));
    connect(m_mems, SIGNAL(failedToConnect(QString)), this, SLOT(onFailedToConnect(QString)));
    connect(m_mems, SIGNAL(interfaceThreadReady()), this, SLOT(onInterfaceThreadReady()));
    connect(m_mems, SIGNAL(notConnected()), this, SLOT(onNotConnected()));
    connect(m_mems, SIGNAL(gotEcuId(uint8_t *)), this, SLOT(onEcuIdReceived(uint8_t *)));
    connect(m_mems, SIGNAL(errorSendingCommand()), this, SLOT(onCommandError()));

    connect(this, SIGNAL(requestToStartPolling()), m_mems, SLOT(onStartPollingRequest()));
    connect(this, SIGNAL(requestThreadShutdown()), m_mems, SLOT(onShutdownThreadRequest()));

    QFuture<void> t1 = QtConcurrent::run(this, &datastore::workerThread, QString("Thead1"));
    QFuture<void> t2 = QtConcurrent::run(this, &datastore::workerThread2, QString("Thread2"));
    //t1.waitForFinished();
}

void datastore::callMeFromQML(){
    qDebug("Inside Call Me From QML");
    count++;
    //m_mems_data->setEngine_rpm(QString::number((count*100)));
    emit increaseOne(msg.arg(count));
    emit dataReceive(m_mems_data);
}

void datastore::workerThread(QString name){
    QString colorA = "#3ba9ea";
    QString colorB = "#8fc564";
    QString colorC = "#eca245";
    QString color;
    double progress = 0.0;

   while(1){
       qDebug() << name;
       count += 100;
       if(count >= 8000){
           count = 0;
       }
       qDebug() << "Count :" << count % 120;
       progress = count / 8000.0;
       //emit dataReceive(m_mems_data);
       QThread::msleep(100);
       m_mems_data->setEngine_rpm(QString::number(count));
       m_mems_data->setEngine_rpm_progress(progress);

       if(progress >= 0.0 && progress < 0.2){
           color = colorA;
       }else if(progress >= 0.2 && progress < 0.6){
           color = colorB;
       }else{
           color = colorC;
       }
       m_mems_data->setEngine_rpm_color(color);

       m_mems_data->setCoolant_temp_f(QString::number(count % 120));
       m_mems_data->setCoolant_temp_f_progress(0.5);
       m_mems_data->setAmbient_temp_f("110");
       m_mems_data->setIntake_air_temp_f("200");
       m_mems_data->setIntake_air_temp_f_progress(0.0);
       m_mems_data->setMap_kpa(QString::number(count % 140));
       m_mems_data->setBattery_voltage("0.0");
       m_mems_data->setBattery_voltage_color("#8fc564");
       m_mems_data->setBattery_voltage_progress(0.0);
       m_mems_data->setThrottle_pot_voltage("0.0");
       m_mems_data->setIdle_switch("0");
       m_mems_data->setPark_neutral_switch("0");
       m_mems_data->setFault_codes("0");
       m_mems_data->setIac_position("0");
       m_mems_data->setIdle_error("0");
       m_mems_data->setIgnition_advance("0");
       m_mems_data->setCoil_time("0");
       m_mems_data->setLambda_voltage_mv("0.0");
       m_mems_data->setFuel_trim("0");
       m_mems_data->setClosed_loop("0");
       m_mems_data->setIdle_base_pos("0");
       m_mems_data->setEcuIdLabel("ECU ID: 00 00 00 00");

    }
}

void datastore::workerThread2(QString name){
   while(1){
        qDebug() << name;
        QThread::msleep(100);
        emit dataReceive(m_mems_data);
   }
}

/**
 * Attempts to open the serial device connected to the ECU,
 * and starts updating the display with data if successful.
 */
void datastore::connectToECU()
{
  // If the worker thread hasn't been created yet, do that now.
  if (m_memsThread == 0)
  {
    m_memsThread = new QThread(this);
    m_mems->moveToThread(m_memsThread);
    connect(m_memsThread, SIGNAL(started()), m_mems, SLOT(onParentThreadStarted()));
  }

  // If the worker thread is alreay running, ask it to start polling the ECU.
  // Otherwise, start the worker thread, but don't ask it to begin polling
  // yet; it'll signal us when it's ready.
  if (m_memsThread->isRunning())
  {
    emit requestToStartPolling();
  }
  else
  {
    m_memsThread->start();
  }
}

void datastore::initializeMemsData()
{
    m_mems_data->setEngine_rpm("1000");
    m_mems_data->setEngine_rpm_color("#8fc564");
    m_mems_data->setEngine_rpm_progress(0.6);
    m_mems_data->setCoolant_temp_f("0");
    m_mems_data->setCoolant_temp_f_color("#8fc564");
    m_mems_data->setCoolant_temp_f_progress(0.0);
    m_mems_data->setAmbient_temp_f("0");
    m_mems_data->setIntake_air_temp_f("0");
    m_mems_data->setIntake_air_temp_f_color("#8fc564");
    m_mems_data->setIntake_air_temp_f_progress(0.0);
    m_mems_data->setFuel_temp_f("0");
    m_mems_data->setMap_kpa("0");
    m_mems_data->setBattery_voltage("0.0");
    m_mems_data->setBattery_voltage_color("#8fc564");
    m_mems_data->setBattery_voltage_progress(0.0);
    m_mems_data->setThrottle_pot_voltage("0.0");
    m_mems_data->setIdle_switch("0");
    m_mems_data->setPark_neutral_switch("0");
    m_mems_data->setFault_codes("0");
    m_mems_data->setIac_position("0");
    m_mems_data->setIdle_error("0");
    m_mems_data->setIgnition_advance("0");
    m_mems_data->setCoil_time("0");
    m_mems_data->setLambda_voltage_mv("0.0");
    m_mems_data->setFuel_trim("0");
    m_mems_data->setClosed_loop("0");
    m_mems_data->setIdle_base_pos("0");
    m_mems_data->setEcuIdLabel("ECU ID: 00 00 00 00");
}

void datastore::onInterfaceThreadReady()
{
    emit requestToStartPolling();
}

void datastore::onNotConnected()
{
    qDebug("Not Connected");
}

void datastore::onEcuIdReceived(uint8_t *id)
{
    char idString[20];

    sprintf(idString, "ECU ID: %02X %02X %02X %02X", id[0], id[1], id[2], id[3]);
    m_mems_data->setEcuIdLabel(QString(idString));
}

void datastore::onFuelPumpTestComplete()
{
    qDebug("Fuel Pump Test Complete");
}

void datastore::onACRelayTestComplete()
{
    qDebug("AC Relay Test Complete");
}

void datastore::onPTCRelayTestComplete()
{
    qDebug("PTC Relay Test Complete");
}

void datastore::onMoveIACComplete()
{
    qDebug("Move IAC Complete");
}

void datastore::onCommandError()
{
    qDebug("Error sending command");
}

void datastore::onFaultCodeClearComplete()
{
    qDebug("Successfully cleared fault codes");
}

void datastore::onDataReady()
{
    qDebug("Data is ready");
    mems_data *data;
    data = m_mems->getData();

    //int corrected_iac = (data->iac_position > IAC_MAXIMUM) ? IAC_MAXIMUM : data->iac_position;
    //float corrected_throttle = (data->throttle_pot_voltage > 5.0) ? 5.0 : data->throttle_pot_voltage;

    if ((data->engine_rpm == 0) && !m_actuatorTestsEnabled)
    {
        //setActuatorTestsEnabled(true);
    }
    else if ((data->engine_rpm > 0) && m_actuatorTestsEnabled)
    {
        //setActuatorTestsEnabled(false);
    }

    m_mems_data->setEngine_rpm(QString::number(data->engine_rpm));
    m_mems_data->setEngine_rpm_progress((data->engine_rpm / 8000));
    if(data->engine_rpm >= 0 && data->engine_rpm < 3000){ m_mems_data->setEngine_rpm_color("#8fc564");}
    else if(data->engine_rpm >= 3000 && data->engine_rpm < 6000){ m_mems_data->setEngine_rpm_color("#eca245");}
    else if(data->engine_rpm >= 6000){ m_mems_data->setEngine_rpm_color("#e3524f");}

    m_mems_data->setCoolant_temp_f(QString::number(data->coolant_temp_f));
    m_mems_data->setCoolant_temp_f_progress(data->coolant_temp_f / 120.0);
    if(data->coolant_temp_f >= 0.0 && data->coolant_temp_f < 80.0){ m_mems_data->setCoolant_temp_f_color("#8fc564");}
    else if(data->coolant_temp_f >= 80.0 && data->coolant_temp_f < 105.0){ m_mems_data->setCoolant_temp_f_color("#eca245");}
    else if(data->coolant_temp_f >= 105.0){ m_mems_data->setCoolant_temp_f_color("#e3524f");}

    m_mems_data->setAmbient_temp_f(QString::number(data->ambient_temp_f));

    m_mems_data->setIntake_air_temp_f(QString::number(data->intake_air_temp_f));
    m_mems_data->setIntake_air_temp_f_progress(data->intake_air_temp_f / 80.0 );
    if(data->intake_air_temp_f >= 0.0 && data->intake_air_temp_f < 30.0){ m_mems_data->setIntake_air_temp_f_color("#8fc564");}
    else if(data->intake_air_temp_f >= 30.0 && data->intake_air_temp_f < 50.0){ m_mems_data->setIntake_air_temp_f_color("#eca245");}
    else if(data->intake_air_temp_f >= 50.0){ m_mems_data->setIntake_air_temp_f_color("#e3524f");}

    m_mems_data->setFuel_temp_f(QString::number(data->fuel_temp_f));
    m_mems_data->setMap_kpa(QString::number(data->map_kpa));

    m_mems_data->setBattery_voltage(QString::number(data->battery_voltage));
    m_mems_data->setBattery_voltage_progress(data->battery_voltage / 16.0 );
    if(data->battery_voltage >= 0.0 && data->battery_voltage < 12.0){ m_mems_data->setBattery_voltage_color("#eca245"); }
    else if(data->battery_voltage >= 12.0 && data->battery_voltage < 14.5){ m_mems_data->setBattery_voltage_color("#8fc564"); }
    else if(data->battery_voltage >= 14.5){ m_mems_data->setBattery_voltage_color("#e3524f");}

    m_mems_data->setThrottle_pot_voltage(QString::number(data->throttle_pot_voltage));
    m_mems_data->setIdle_switch(QString::number(data->idle_switch));
    m_mems_data->setPark_neutral_switch(QString::number(data->park_neutral_switch));
    m_mems_data->setFault_codes(QString::number(data->fault_codes));
    m_mems_data->setIac_position(QString::number(data->iac_position));
    m_mems_data->setCoil_time(QString::number(data->coil_time));
    m_mems_data->setIdle_error(QString::number(data->idle_error));
    m_mems_data->setIgnition_advance(QString::number(data->ignition_advance));
    m_mems_data->setLambda_voltage_mv(QString::number(data->lambda_voltage_mv));
    m_mems_data->setFuel_trim(QString::number(data->fuel_trim));
    m_mems_data->setClosed_loop(QString::number(data->closed_loop));
    m_mems_data->setIdle_base_pos(QString::number(data->idle_base_pos));

    emit dataReceive(m_mems_data);
}

void datastore::onConnect()
{
    qDebug("Connected");
}

void datastore::onDisconnect()
{
    qDebug("Disconnected");
}

void datastore::onReadError()
{
    qDebug("Read Error");
}

void datastore::onReadSuccess()
{
    qDebug("Read Error");
    emit dataReceive(m_mems_data);
}

void datastore::onFailedToConnect(QString dev)
{
    qDebug() << "not connected to " << dev;
}

