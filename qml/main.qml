import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 900
    height: 640
    title: "Channels UI"

    ColumnLayout {
        anchors.fill: parent
        spacing: 10


        RowLayout 
        {
            Layout.fillWidth: true
            height: 60
            spacing: 5

            Repeater 
            {
                model: channelManager.channelCount ? channelManager.channelCount() : 4
                delegate: Button {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    text: channelManager.channelName ? channelManager.channelName(index) : "Channel " + (index + 1)

                    onClicked: channelManager.selectChannel(index)
                }
            }
        }
        
        
        Rectangle 
        {
            color: "#f4f4f4"
            radius: 8
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.color: "#ddd"

            ScrollView 
            {
                anchors.fill: parent
                anchors.margins: 5
                clip: true

                GridView 
                {
                    id: paramGrid
                    anchors.fill: parent
                    cellWidth: parent.width / 2
                    cellHeight: 100
                    model: channelManager.parameterModel

                    delegate: Rectangle {
                        width: paramGrid.cellWidth - 10
                        height: paramGrid.cellHeight - 5
                        color: "white"
                        border.color: "#e0e0e0"
                        border.width: 1
                        radius: 6

                        Column 
                        {
                            width: parent.width - 20
                            anchors.centerIn: parent
                            spacing: 5

                            // Parameter Name
                            Text {
                                width: parent.width
                                text: name
                                font.pixelSize: 14
                                font.bold: true
                                elide: Text.ElideRight
                                color: isFixed ? "#666" : "#333"
                            }

                            // loader chooses the right control
                            Loader {
                                id: ctlLoader
                                width: parent.width
                                property string nameRole: name
                                property string kindRole: kind
                                property var valueRole: value
                                property bool isFixedRole: isFixed
                                property bool isDecimalRole: isDecimal
                                property real minRole: min
                                property real maxRole: max
                                property var optionsRole: options
                                property int indexRole: index
                                
                                sourceComponent:
                                    kind === "bool" ? boolComp
                                    : kind === "category" ? categoryComp
                                    : numericComp
                            }
                            // Value display column (fixed width)
                            Text {
                                horizontalAlignment : Text.AlignHCenter
                                width: parent.width
                                font.pixelSize: 12
                                color: "#666"

                                text: {
                                    if (kind === "bool") return value ? "Enabled" : "Disabled";
                                    if (kind === "category") return options && options.length > value ? options[value] : "";
                                    if (kind === "numeric") return "Value: " + (isDecimal ? Number(value).toFixed(2) : Math.round(value));
                                    return value;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /* -------- Components -------- */

    Component {
        id: boolComp
        Switch {
            anchors.horizontalCenter: parent.horizontalCenter
            checked: valueRole === true
            enabled: !isFixedRole
            opacity: isFixedRole ? 0.7 : 1.0
            
            onCheckedChanged: {
                var oldVal = valueRole
                var newVal = checked
                if (oldVal !== newVal) {
                    channelManager.parameterModel.setParameterValue(indexRole, checked)
                    channelManager.logInteraction(nameRole, oldVal, checked, Date.now())
                }
            }
        }
    }

    Component {
        id: numericComp
        Column {
            width: parent.width
            spacing: 5

            Slider {
                width: parent.width
                from: minRole
                to: maxRole
                stepSize: isDecimalRole ? Math.max((to - from) / 100.0, 0.0001) : 1
                value: valueRole
                enabled: !isFixedRole
                opacity: isFixedRole ? 0.7 : 1.0

                property real previousValue: valueRole
                onPressedChanged: {
                    if (pressed) {
                        // Drag started
                        previousValue = value;
                    } else {
                        // Drag released
                        var nv = isDecimalRole ? value : Math.round(value);
                        if (nv !== previousValue) {
                            channelManager.parameterModel.setParameterValue(indexRole, nv);
                            channelManager.logInteraction(nameRole, previousValue, nv, Date.now())
                        }
                    }
                }
            }
            RowLayout {
                width: parent.width
                Text {
                    text: "Min: " + (isDecimalRole ? minRole.toFixed(2) : Math.round(minRole))
                    font.pixelSize: 10
                }
                Item { Layout.fillWidth: true }
                Text {
                    text: "Max: " + (isDecimalRole ? maxRole.toFixed(2) : Math.round(maxRole))
                    font.pixelSize: 10
                }
            }
        }
    }
                    

    Component {
        id: categoryComp
        
        Item {
            width: parent.width
            height: 40

            ComboBox {
                id: cb
                width: parent.width
                model: optionsRole
                enabled: !isFixedRole
                opacity: isFixedRole ? 0.7 : 1.0

                // Keep track of previous index before a change
                property int previousIndex: 0
                    
                // Use a binding to assign currentIndex only when valueRole and optionsRole are valid
                Binding {
                    target: cb
                    property: "currentIndex"
                    when: optionsRole !== undefined && optionsRole.length > 0 && valueRole !== undefined
                    value: Math.min(Math.max(Number(valueRole), 0), optionsRole.length - 1)
                }

                onCurrentIndexChanged: 
                {
                    if (currentIndex  !== previousIndex) 
                    { // avoid redundant writes
                        channelManager.parameterModel.setParameterValue(indexRole, currentIndex)
                        channelManager.logInteraction(nameRole, previousIndex, currentIndex, Date.now())
                        previousIndex = currentIndex
                    }
                }
            }
        }
    }
}
