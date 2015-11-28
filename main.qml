import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2

Window {
    visible: true

    ColumnLayout {
        Text {
            text: "Státusz: " + robot.statusName;
        }
        Text {
            text: "Sebesség: " + robot.speed;
        }
        Text {
            text: "Szervó: " + robot.servo;
        }
        anchors.fill: parent
    }
}

