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

        onSourceChanged: {
            setupImageProvider(image.paintedWidth, image.paintedHeight, width, height);
            console.log("RELOADING IMAGE2!");
        }
        Component.onCompleted: {
            setupImageProvider(image.paintedWidth, image.paintedHeight, width, height);
            console.log("RELOADING IMAGE!");
        }

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
        console.log("image pos: "+image.x+", "+image.y+ " size: "+image.paintedWidth+", "+image.paintedHeight, " --- mouse: "+x+", "+y);
    }

    function setupImageProvider(iw, ih, ww, wh) {
        imageProvider.setWindowWidth(ww);
        imageProvider.setWindowHeight(wh);
        imageProvider.setImageWidth(iw);
        imageProvider.setImageHeight(ih);
    }
}


