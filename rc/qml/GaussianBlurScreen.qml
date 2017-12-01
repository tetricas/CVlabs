import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Rectangle {
    color: "white"

    Image {
        id: img
        anchors.centerIn: parent

        source: "qrc:/images/test.jpg"
    }

    GaussianBlur {
        id: blur
        anchors.fill: img
        source: img
        radius: 0
        samples: radius * 2 + 1
    }

    Slider{
        id: radiusSlider
        anchors.bottom: img.top
        anchors.left: parent.horizontalCenter
        from: 0
        to: 50
        stepSize: 0.1
        onMoved: blur.radius = value
    }

    Text{
        id: radiusText
        text: "Radius " + radiusSlider.value.toFixed(2) + ":"
        anchors.verticalCenter: radiusSlider.verticalCenter
        anchors.right: parent.horizontalCenter
        font.pixelSize: 30
    }
}
