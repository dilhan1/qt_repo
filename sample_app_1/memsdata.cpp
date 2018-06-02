#include "memsdata.h"

MemsData::MemsData(QObject *parent) : QObject(parent),
    m_engine_rpm("0"),
    m_engine_rpm_progress(0.0),
    m_engine_rpm_color("#8fc564"),
    m_coolant_temp_f("0"),
    m_coolant_temp_f_progress(0.0),
    m_coolant_temp_f_color("#8fc564"),
    m_ambient_temp_f("0"),
    m_intake_air_temp_f("0"),
    m_intake_air_temp_f_progress(0.0),
    m_intake_air_temp_f_color("#8fc564"),
    m_fuel_temp_f("0"),
    m_map_kpa("0"),
    m_battery_voltage("0"),
    m_battery_voltage_progress(0.0),
    m_battery_voltage_color("#8fc564"),
    m_throttle_pot_voltage("0"),
    m_idle_switch("0"),
    m_park_neutral_switch("0"),
    m_fault_codes("0"),
    m_iac_position("0"),
    m_idle_error("0"),
    m_ignition_advance("0"),
    m_coil_time("0"),
    m_lambda_voltage_mv("0"),
    m_fuel_trim("0"),
    m_closed_loop("0"),
    m_idle_base_pos("0"),
    m_ecuIdLabel("0")
{

}
