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
        spacing: 20

        Item {
            Layout.fillWidth: true
            height: 50
            
            RowLayout {
                anchors.fill: parent
                spacing: 0
                
                // Dynamic buttons if ChannelManager exposes channelCount() and channelName()
                Repeater {
                    model: channelManager.channelCount ? channelManager.channelCount() : 4
                    delegate: Button {
                        Layout.fillWidth: true
                        Layout.preferredHeight: parent.height
                        Layout.margins : 5
                        
                        text: channelManager.channelName ? channelManager.channelName(index) : (index + 1).toString()
                        onClicked: {
                            channelManager.selectChannel(index)
                        }
                    }
                }
            }
        }
        
        Rectangle {
            color: "#f4f4f4"
            radius: 8
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.color: "#ddd"

            ListView {
                id: paramList
                anchors.fill: parent
                model: channelManager.parameterModel
                clip: true

                delegate: Item 
                {
                    id: rowItem
                    width: paramList.width
                    height: kind === "numeric" ? 60 : 40  // taller for numeric with slider

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 12

                        // Name column (fixed width)
                        Text {
                            id: nameText
                            text: name
                            elide: Text.ElideRight
                            font.pixelSize: 14
                            Layout.preferredWidth: 200  // Fixed width for name column
                            verticalAlignment: Text.AlignVCenter
                        }

                        // loader chooses the right control
                        Loader {
                            id: ctlLoader
                            Layout.fillWidth: true
                            property string nameRole: name
                            property string kindRole: kind
                            property var valueRole: value
                            property bool isFixedRole: isFixed
                            property bool isDecimalRole: isDecimal
                            property real minRole: min
                            property real maxRole: max
                            property var optionsRole: options
                            property int indexRole: index
                            onLoaded: {
                                console.log("Delegate loaded kind:", kind, "valueRole:", valueRole)
                            }
                            sourceComponent:
                                kind === "bool" ? boolComp
                                : kind === "category" ? categoryComp
                                : numericComp
                        }
                        // Value display column (fixed width)
                        Text {
                            Layout.preferredWidth: 120  // Fixed width for value display
                            verticalAlignment: Text.AlignVCenter
                            text: {
                                if (kind === "bool") return value ? "On" : "Off";
                                if (kind === "category") return options && options.length > value ? options[value] : "";
                                if (kind === "numeric") return isDecimal ? Number(value).toFixed(2) : Math.round(value);
                                return value;
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
        Item {
            width: parent.width
            height: 40
            RowLayout {
                anchors.fill: parent
                spacing: 12

                Switch {
                    checked: valueRole === true
                    enabled: !isFixedRole

                    onCheckedChanged: {
                        var oldVal = valueRole
                        var newVal = checked    // new UI state
                        if (oldVal !== newVal) 
                        { // avoid redundant writes
                            // update C++ model and log
                            channelManager.parameterModel.setParameterValue(indexRole, checked)
                            channelManager.logInteraction(nameRole, oldVal, checked, Date.now())
                        }
                    }
                }
            }
        }
    }

    Component {
        id: numericComp
        Item {
            width: parent.width
            height: 60

            RowLayout {
                anchors.fill: parent
                spacing: 12

                // Slider area
                Slider {
                    id: numSlider
                    Layout.fillWidth: true
                    from: minRole
                    to: maxRole
                    // step size: integer or fine step when decimal allowed
                    stepSize: isDecimalRole ? Math.max((to - from) / 100.0, 0.0001) : 1
                    value: valueRole
                    enabled: !isFixedRole

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
            }
        }
    }

    Component {
        id: categoryComp
        
        Item {
            width: parent.width
            height: 40

            RowLayout {
                anchors.fill: parent
                spacing: 12
                
                ComboBox {
                    id: cb
                    Layout.preferredWidth: 300
                    model: optionsRole
                    //currentIndex: valueRole ? Number(valueRole) : 0  // value is the selected index stored in model
                    enabled: !isFixedRole

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
                        console.log("ComboBox Initial Value: ", currentIndex)
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
}
