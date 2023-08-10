/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.5
import QtQuick.Controls 6.5
import TextEditor

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    TextEdit {
        id: textEdit
        x: 465
        y: 231
        width: 991
        height: 672
        text: qsTr("Text Edit")
        font.pixelSize: 12
    }

    ToolBar {
        id: toolBar
        x: 465
        y: 177
        width: 991
        height: 48
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
