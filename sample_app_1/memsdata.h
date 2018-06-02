#ifndef MEMSDATA_H
#define MEMSDATA_H

#include <QObject>
#include <QString>

class MemsData : public QObject
{
    Q_OBJECT
public:
    explicit MemsData(QObject *parent = nullptr);

    Q_INVOKABLE QString getEngine_rpm() const{ return m_engine_rpm; }
    Q_INVOKABLE void setEngine_rpm(const QString &engine_rpm) { m_engine_rpm = engine_rpm; }

    Q_INVOKABLE double getEngine_rpm_progress() const { return m_engine_rpm_progress; }
    Q_INVOKABLE void setEngine_rpm_progress(double engine_rpm_progress) { m_engine_rpm_progress = engine_rpm_progress; }

    Q_INVOKABLE QString getEngine_rpm_color() const { return m_engine_rpm_color; }
    Q_INVOKABLE void setEngine_rpm_color(const QString &engine_rpm_color) { m_engine_rpm_color = engine_rpm_color; }

    Q_INVOKABLE QString getCoolant_temp_f() const { return m_coolant_temp_f; }
    Q_INVOKABLE void setCoolant_temp_f(const QString &coolant_temp_f) { m_coolant_temp_f = coolant_temp_f; }

    Q_INVOKABLE double getCoolant_temp_f_progress() const { return m_coolant_temp_f_progress; }
    Q_INVOKABLE void setCoolant_temp_f_progress(double coolant_temp_f_progress) {m_coolant_temp_f_progress = coolant_temp_f_progress; }

    Q_INVOKABLE QString getCoolant_temp_f_color() const { return m_coolant_temp_f_color; }
    Q_INVOKABLE void setCoolant_temp_f_color(const QString &coolant_temp_f_color) { m_coolant_temp_f_color = coolant_temp_f_color; }

    Q_INVOKABLE QString getAmbient_temp_f() const { return m_ambient_temp_f; }
    Q_INVOKABLE void setAmbient_temp_f(const QString &ambient_temp_f) { m_ambient_temp_f = ambient_temp_f; }

    Q_INVOKABLE QString getIntake_air_temp_f() const { return m_intake_air_temp_f; }
    Q_INVOKABLE void setIntake_air_temp_f(const QString &intake_air_temp_f) { m_intake_air_temp_f = intake_air_temp_f; }

    Q_INVOKABLE double getIntake_air_temp_f_progress() const { return m_intake_air_temp_f_progress; }
    Q_INVOKABLE void setIntake_air_temp_f_progress(double intake_air_temp_f_progress) { m_intake_air_temp_f_progress = intake_air_temp_f_progress; }

    Q_INVOKABLE QString getIntake_air_temp_f_color() const { return m_intake_air_temp_f_color; }
    Q_INVOKABLE void setIntake_air_temp_f_color(const QString &intake_air_temp_f_color) { m_intake_air_temp_f_color = intake_air_temp_f_color; }

    Q_INVOKABLE QString getFuel_temp_f() const { return m_fuel_temp_f; }
    Q_INVOKABLE void setFuel_temp_f(const QString &fuel_temp_f) { m_fuel_temp_f = fuel_temp_f; }

    Q_INVOKABLE QString getMap_kpa() const { return m_map_kpa; }
    Q_INVOKABLE void setMap_kpa(const QString &map_kpa) { m_map_kpa = map_kpa; }

    Q_INVOKABLE QString getBattery_voltage() const { return m_battery_voltage; }
    Q_INVOKABLE void setBattery_voltage(const QString &battery_voltage) { m_battery_voltage = battery_voltage; }

    Q_INVOKABLE double getBattery_voltage_progress() const { return m_battery_voltage_progress; }
    Q_INVOKABLE void setBattery_voltage_progress(double battery_voltage_progress) { m_battery_voltage_progress = battery_voltage_progress; }

    Q_INVOKABLE QString getBattery_voltage_color() const { return m_battery_voltage_color; }
    Q_INVOKABLE void setBattery_voltage_color(const QString &battery_voltage_color) { m_battery_voltage_color = battery_voltage_color; }

    Q_INVOKABLE QString getThrottle_pot_voltage() const { return m_throttle_pot_voltage; }
    Q_INVOKABLE void setThrottle_pot_voltage(const QString &throttle_pot_voltage) { m_throttle_pot_voltage = throttle_pot_voltage; }

    Q_INVOKABLE QString getIdle_switch() const { return m_idle_switch; }
    Q_INVOKABLE void setIdle_switch(const QString &idle_switch) { m_idle_switch = idle_switch; }

    Q_INVOKABLE QString getPark_neutral_switch() const { return m_park_neutral_switch; }
    Q_INVOKABLE void setPark_neutral_switch(const QString &park_neutral_switch) { m_park_neutral_switch = park_neutral_switch; }

    Q_INVOKABLE QString getFault_codes() const { return m_fault_codes; }
    Q_INVOKABLE void setFault_codes(const QString &fault_codes) { m_fault_codes = fault_codes; }

    Q_INVOKABLE QString getIac_position() const { return m_iac_position; }
    Q_INVOKABLE void setIac_position(const QString &iac_position) { m_iac_position = iac_position; }

    Q_INVOKABLE QString getIdle_error() const { return m_idle_error; }
    Q_INVOKABLE void setIdle_error(const QString &idle_error) { m_idle_error = idle_error; }

    Q_INVOKABLE QString getIgnition_advance() const { return m_ignition_advance; }
    Q_INVOKABLE void setIgnition_advance(const QString &ignition_advance) { m_ignition_advance = ignition_advance; }

    Q_INVOKABLE QString getCoil_time() const { return m_coil_time; }
    Q_INVOKABLE void setCoil_time(const QString &coil_time) { m_coil_time = coil_time; }

    Q_INVOKABLE QString getLambda_voltage_mv() const { return m_lambda_voltage_mv; }
    Q_INVOKABLE void setLambda_voltage_mv(const QString &lambda_voltage_mv) { m_lambda_voltage_mv = lambda_voltage_mv; }

    Q_INVOKABLE QString getFuel_trim() const { return m_fuel_temp_f; }
    Q_INVOKABLE void setFuel_trim(const QString &fuel_trim) { m_fuel_trim = fuel_trim; }

    Q_INVOKABLE QString getClosed_loop() const { return m_closed_loop; }
    Q_INVOKABLE void setClosed_loop(const QString &closed_loop) { m_closed_loop = closed_loop; }

    Q_INVOKABLE QString getIdle_base_pos() const { return m_idle_base_pos; }
    Q_INVOKABLE void setIdle_base_pos(const QString &idle_base_pos) { m_idle_base_pos = idle_base_pos; }

    Q_INVOKABLE QString getEcuIdLabel() const { return m_ecuIdLabel; }
    Q_INVOKABLE void setEcuIdLabel(const QString &ecuIdLabel) { m_ecuIdLabel = ecuIdLabel; }

private:
    QString m_engine_rpm;
    double m_engine_rpm_progress;
    QString m_engine_rpm_color;
    QString m_coolant_temp_f;
    double m_coolant_temp_f_progress;
    QString m_coolant_temp_f_color;
    QString m_ambient_temp_f;
    QString m_intake_air_temp_f;
    double m_intake_air_temp_f_progress;
    QString m_intake_air_temp_f_color;
    QString m_fuel_temp_f;
    QString m_map_kpa;
    QString m_battery_voltage;
    double m_battery_voltage_progress;
    QString m_battery_voltage_color;
    QString m_throttle_pot_voltage;
    QString m_idle_switch;
    QString m_park_neutral_switch;
    QString m_fault_codes;
    QString m_iac_position;
    QString m_idle_error;
    QString m_ignition_advance;
    QString m_coil_time;
    QString m_lambda_voltage_mv;
    QString m_fuel_trim;
    QString m_closed_loop;
    QString m_idle_base_pos;
    QString m_ecuIdLabel;
};

#endif // MEMSDATA_H
