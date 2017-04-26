/*
  Copyright (C) 2017 Michael Bohlender, <bohlender@kolabsys.com>
  Copyright (C) 2017 Christian Mollekopf, <mollekopf@kolabsys.com>

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

pragma Singleton

import QtQuick 2.7

Item {
    property string error: "error"
    property string error_inverted: "error-inverted"
    property string busy: "view-refresh"
    property string busy_inverted: "view-refresh-inverted"
    property string noNetworkConnection_inverted: "network-disconnect-inverted"
    property string connected: "dialog-ok"
    property string connected_inverted: "dialog-ok-inverted"
    property string success: "dialog-ok"
    property string success_inverted: "dialog-ok-inverted"

    property string markAsRead: "mail-mark-unread-new-inverted"
    property string markAsUnread: "mail-mark-unread-new-inverted"
    property string markImportant: "mail-mark-important-inverted"
    property string undo: "edit-undo-inverted"
    property string moveToTrash: "edit-delete-inverted"
    property string edit: "document-edit"
    property string replyToSender: "mail-reply-sender"
    property string outbox: "mail-folder-outbox"
    property string outbox_inverted: "mail-folder-outbox-inverted"

    property string menu_inverted: "application-menu-inverted"
    property string user_inverted: "im-user-inverted"
    property string search_inverted: "edit-find-inverted"
    property string mail_inverted: "mail-message-inverted"
    property string goBack: "go-previous"
    property string goDown: "go-down"
    property string goUp: "go-down"

    property string addNew: "list-add-new"
    property string folder: "folder"

}

