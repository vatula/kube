/*
 * Copyright (C) 2018 Christian Mollekopf, <mollekopf@kolabsys.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

import org.kube.framework 1.0 as Kube
import org.kube.test 1.0
import "qml"

ApplicationWindow {
    id: app
    height: Screen.desktopAvailableHeight * 0.8
    width: Screen.desktopAvailableWidth * 0.8

    Component.onCompleted: {
        var initialState = {
            accounts: [{
                    id: "account1",
                    name: "Test Account"
                }],
            identities: [{
                    account: "account1",
                    name: "Test Identity",
                    address: "identity@example.org"
                }],
            resources: [{
                    id: "resource1",
                    account: "account1",
                    type: "dummy"
                },
                {
                    id: "resource2",
                    account: "account1",
                    type: "mailtransport"
                }],
            folders: [{
                    id: "folder1",
                    resource: "resource1",
                    name: "Folder 1",
                    specialpurpose: ["drafts"],
                    mails: [{
                            resource: "resource1",
                            messageId: "<msg1@test.com>",
                            date: "2017-07-24T15:46:29",
                            subject: "subject1",
                            body: "body",
                            to: ["to@example.org"],
                            cc: ["cc@example.org"],
                            bcc: ["bcc@example.org"],
                            draft: true
                        },
                        {
                            resource: "resource1",
                            messageId: "<msg2@test.com>",
                            date: "2017-07-23T15:46:29",
                            subject: "LooooooooooooooooooooooooooooooooooooooooooooooooooooooooonggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggEnd",
                            body: "LooooooooooooooooooooooooooooooooooooooooooooooooooooooooonggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggEnd\nbody\nbody\n\n\nbody\n\n\nbody\n\n\nbody\n\n\nbody\nbody\n\n\nbody\n\n\nbody\n\n\nbody\n\n\nbody\n\n\n\n\n\n\n\n\nbody\nbody\n\n\nbody\n\n\nbody\n\n\nbody\n\n\nbody\n\n\nbody",
                            to: ["toLoooooooooooooooooooooooooooooooooooooooooooooooooong@example.org"],
                            cc: ["ccLoooooooooooooooooooooooooooooooooooooooooooooooooong@example.org"],
                            bcc: ["bccLoooooooooooooooooooooooooooooooooooooooooooooooooong@example.org"],
                            draft: true
                        }
                    ]
                }],
        }
        TestStore.setup(initialState)
        Kube.Fabric.postMessage(
            Kube.Messages.notification,
            {
                "type": Kube.Notifications.error,
                "subtype": Kube.Notifications.loginError,
                message: "Failed to login",
                resource: "resource1",
                entities: []
            }
        );
        Kube.Fabric.postMessage(
            Kube.Messages.notification,
            {
                "type": Kube.Notifications.error,
                "subtype": Kube.Notifications.hostNotFoundError,
                message: "Host Not Found",
                resource: "resource1",
                entities: []
            }
        )
        Kube.Fabric.postMessage(
            Kube.Messages.notification,
            {
                "type": Kube.Notifications.error,
                "subtype": Kube.Notifications.connectionError,
                message: "connection error",
                resource: "resource1",
                entities: []
            }
        )
        var mail = TestStore.load("mail", {messageId: "msg1@test.com"})
        var mail_uid = TestStore.read(mail).uid
        Kube.Fabric.postMessage(
            Kube.Messages.notification,
            {
                "type": Kube.Notifications.error,
                "subtype": Kube.Notifications.transmissionError,
                message: "transmission error with mail uid",
                resource: "resource1",
                entities: [mail_uid]
            }
        )
        var mail2 = TestStore.load("mail", {messageId: "msg2@test.com"})
        var mail2_uid = TestStore.read(mail2).uid
        Kube.Fabric.postMessage(
            Kube.Messages.notification,
            {
                "type": Kube.Notifications.error,
                "subtype": Kube.Notifications.transmissionError,
                message: "transmission error with another mail uid",
                resource: "resource1",
                entities: [mail2_uid]
            }
        )
        Kube.Fabric.postMessage(
            Kube.Messages.notification,
            {
                "type": Kube.Notifications.error,
                "subtype": "customSubType",
                message: "custom subtype error",
                resource: "resource1",
                entities: []
            }
        )
    }

    View {
        anchors.fill: parent
    }
}
