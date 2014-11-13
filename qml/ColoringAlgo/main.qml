import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    width: 303
    height: 500
    color: "blue"

    Image {
        id: image
        fillMode: Image.PreserveAspectFit
        source: "image://imageprovider/qml/ColoringAlgo/giraffe.svg"
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
        }
        Connections {
            target: imageProvider
            onNewFrameReceived: image.reload();
        }

        onSourceChanged: {
            setupImageProvider(image.paintedWidth, image.paintedHeight, width, height);
        }

        Component.onCompleted: {
            setupImageProvider(image.paintedWidth, image.paintedHeight, width, height);
        }
    }


    function colorArea(x, y) {
        imageProvider.fillColor(x, y);
    }

    function setupImageProvider(iw, ih, ww, wh) {
        imageProvider.setWindowWidth(ww);
        imageProvider.setWindowHeight(wh);
        imageProvider.setImageWidth(iw);
        imageProvider.setImageHeight(ih);
    }
}


