import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    width: 303
    height: 500
    Image {
        id: image
        source: "image://imageprovider/qml/ColoringAlgo/testImage_small_red.png"
        anchors.fill: parent
        objectName: "image"
        cache: false

        MouseArea {
            anchors.fill: parent
            onClicked: {
                colorArea(mouseX, mouseY);
            }
        }
        function reload() {
            var oldSource = source;
            source = "";
            source = oldSource;
            console.log("RELOADING IMAGE!");
        }
        Connections {
            target: imageProvider
            onNewFrameReceived: image.reload();
        }
    }

    function colorArea(x, y) {
        //colorFiller.fillColor(image, x, y);
        imageProvider.fillColor(x, y);
        console.log("image pos: "+image.x+", "+image.y+ " size: "+image.width+", "+image.height, " --- mouse: "+x+", "+y);
    }
}


