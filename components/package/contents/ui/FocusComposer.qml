/*
  Copyright (C) 2016 Michael Bohlender, <michael.bohlender@kdemail.net>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import org.kde.kirigami 1.0 as Kirigami

import org.kube.components 1.0 as KubeComponents

KubeComponents.OverlayDialog {
    id: root

    function loadMessage(message, loadAsDraft) {
        composer.loadMessage(message, loadAsDraft);
    }

    Item {
        anchors.centerIn: parent

        height: root.height * 0.8
        width: root.width * 0.8

        ColumnLayout {

            anchors {
                fill: parent
                margins: Kirigami.Units.largeSpacing
            }

            Composer {
                id: composer

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight

                Button {
                    text: "Send"

                    onClicked: {
                        composer.send()
                        root.destroy()
                    }
                }
            }
        }
    }
}
