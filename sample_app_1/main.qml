import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 480
    height: 272
    title: qsTr("Mini Cooper")
    color: "#101214"

    Connections{
        target: dataStore
        onIncreaseOne:{
            btn_new.text = ms
        }
    }

    Connections{
        target: dataStore
        onDataReceive:{
            engine_speed_value.text = md.getEngine_rpm()
            engine_speed_progress_bar.value = md.getEngine_rpm_progress()
            engine_speed_value.color = md.getEngine_rpm_color()
            map_sensor_value.text = md.getMap_kpa()

            engine_temp_value.text = md.getCoolant_temp_f()
            engine_temp_value.color = md.getCoolant_temp_f_color()

            air_temp_value.text = md.getIntake_air_temp_f()
            air_temp_value.color = md.getIntake_air_temp_f_color()

            throttle_position_value.text = md.getThrottle_pot_voltage()

            main_voltage_value.text = md.getBattery_voltage()
            main_voltage_value.color = md.getBattery_voltage_color()

            ecu_id.text = md.getEcuIdLabel()
        }
    }

   // Button{
   //     x: parent.width - width
   //     id: btn_new
   //     text: "Hit"
   //     onClicked: dataStore.callMeFromQML()
   // }

    Text{
        id: ecu_id
        text: "ECU ID: XX XX XX XX"
        font.pointSize: 14
        color: "#e4e4e4"
        x: 10
        y: 5
    }

    Rectangle{
        id: engine_speed_gauge
        visible: parent.visible
        width: (parent.width / 4) - 10
        height: width
        color: "#2a2a2a"
        border.color: "black"
        x: 8
        y: 30

        Text{
            id: engine_speed_header
            text: "Engine Speed"
            padding: 1

            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: 10
        }

        Text{
            id: engine_speed_footer
            text: "RPM"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: parent.height - height - 10
        }

        Text{
            id: engine_speed_value
            text: "1850"
            font.pointSize: 30

            anchors.centerIn: engine_speed_gauge
        }

        ProgressBar {
            id: engine_speed_progress_bar
            value: 0.0
            x: 1

            style: ProgressBarStyle {
                background: Rectangle {
                    color: "#454545"
                    implicitWidth: engine_speed_gauge.width - 2
                    implicitHeight: 4
                }

                progress: Rectangle {
                    property string colorA: "#3ba9ea"
                    property string colorB: "#8fc564"
                    property string colorC: "#eca245"
                    color: {
                        if (engine_speed_progress_bar.value >= 0.0 && engine_speed_progress_bar.value < 0.2)
                            colorA
                        else if (engine_speed_progress_bar.value >= 0.2 && engine_speed_progress_bar.value < 0.6)
                            colorB
                        else
                            colorC
                    }

                }
             }
        }
    }

    Rectangle{
        id: map_sensor_gauge
        visible: parent.visible
        width: (parent.width / 4) - 10
        height: width
        color: "#2a2a2a"
        border.color: "black"
        x: width + 16
        y: 30

        Text{
            id: map_sensor_header
            text: "MAP Sensor"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: 10
        }

        Text{
            id: map_sensor_footer
            text: "KPa"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: parent.height - height - 10
        }

        Text{
            id: map_sensor_value
            text: "16"
            font.pointSize: 30
            color: "#eca245"
            anchors.centerIn: map_sensor_gauge
        }
    }

    Rectangle{
        id: engine_temp_gauge
        visible: parent.visible
        width: (parent.width / 4) - 10
        height: width
        color: "#2a2a2a"
        opacity: 1
        border.color: "black"
        x: 2 * width + 24
        y: 30

        Text{
            id: engine_temp_header
            text: "Engine Temp"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: 10
        }

        Text{
            id: engine_temp_footer
            text: "Celcius"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: parent.height - height - 10
        }

        Text{
            id: engine_temp_value
            text: "80"
            font.pointSize: 30
            color: "#e3524f"
            anchors.centerIn: engine_temp_gauge
        }
    }

    Rectangle{
        id: mini_logo
        visible: parent.visible
        width: (parent.width / 4) - 10
        height: width
        color: "#2a2a2a"
        border.color: "black"
        x: 3 * width + 32
        y: 30

        Text{
            id: mini_logo_value
            text: "D"
            font.pointSize: 42
            color: "#e3524f"
            anchors.centerIn: mini_logo
        }

        Text{
            id: mini_logo_header
            text: "Gear"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: 10
        }

        Text{
            id: mini_logo_footer
            text: "P R N D 1 2 3"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: parent.height - height - 10
        }
    }

    Rectangle{
        id: air_temp_gauge
        visible: parent.visible
        width: (parent.width / 4) - 10
        height: width
        color: "#2a2a2a"
        border.color: "black"
        x: 8
        y: height + 40

        Text{
            id:air_temp_header
            text: "Air Temp"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: 10
        }

        Text{
            id: air_temp_footer
            text: "Celcius"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: parent.height - height - 10
        }

        Text{
            id: air_temp_value
            text: "54"
            font.pointSize: 30
            color: "white"
            anchors.centerIn: air_temp_gauge
        }
    }

    Rectangle{
        id: throttle_position_gauge
        visible: parent.visible
        width: (parent.width / 4) - 10
        height: width
        color: "#2a2a2a"
        border.color: "black"
        x: width + 16
        y: height + 40

        Text{
            id: throttle_position_header
            text: "Throttle Pos"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: 10
        }

        Text{
            id: throttle_position_footer
            text: "Volt"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: parent.height - height - 10
        }

        Text{
            id: throttle_position_value
            text: "0.8"
            font.pointSize: 30
            color: "white"
            anchors.centerIn: throttle_position_gauge
        }
    }

    Rectangle{
        id: main_voltage_gauge
        visible: parent.visible
        width: (parent.width / 4) - 10
        height: width
        color: "#2a2a2a"
        border.color: "black"
        x: 2 * width + 24
        y: height + 40

        Text{
            id: main_voltage_heading
            text: "Main Voltage"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: 10
        }

        Text{
            id: main_voltage_footer
            text: "Volt"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: parent.height - height - 10
        }

        Text{
            id: main_voltage_value
            text: "12.8"
            font.pointSize: 30
            color: "#3fb4f9"
            anchors.centerIn: main_voltage_gauge
        }
    }

    Rectangle{
        id: fault_codes_gauge
        visible: parent.visible
        width: (parent.width / 4) - 10
        height: width
        color: "#2a2a2a"
        border.color: "black"
        x: 3 * width + 32
        y: height + 40

        Text{
            id: fault_codes_header
            text: "Fault Codes"
            font.pointSize: 14
            color: "#e4e4e4"
            x: parent.width / 2 - width / 2
            y: 10
        }

        Column{
            topPadding: (fault_codes_gauge.height - row1.height - row2.height - spacing) / 2 + 10
            bottomPadding: (fault_codes_gauge.height - row1.height - row2.height - spacing) / 2  + 10
            spacing: 20
            Row{
                id: row1
                Text{
                    id: ats_codes_header
                    text: "ATS"
                    font.pointSize: 14
                    color: "white"
                    opacity: 0.2
                }
                Text{
                    id: cts_codes_header
                    text: "CTS"
                    font.pointSize: 14
                    color: "white"
                    opacity: 0.2
                }
                rightPadding: (fault_codes_gauge.width - ats_codes_header.width - cts_codes_header.width - spacing) / 2
                leftPadding: (fault_codes_gauge.width - ats_codes_header.width - cts_codes_header.width - spacing) / 2
                spacing: 30
            }

            Row{
                id: row2
                Text{
                    id: fts_codes_header
                    text: "FTS"
                    font.pointSize: 14
                    color: "white"
                }
                Text{
                    id: tps_codes_header
                    text: "TPS"
                    font.pointSize: 14
                    color: "white"
                    opacity: 0.2

                }
                rightPadding: (fault_codes_gauge.width - fts_codes_header.width - tps_codes_header.width - spacing) / 2
                leftPadding: (fault_codes_gauge.width - fts_codes_header.width - tps_codes_header.width - spacing) / 2
                spacing: 30
            }
        }
    }

}
