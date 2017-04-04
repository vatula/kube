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
    property string busy: "view-refresh"
    property string noNetworkConnection: "network-disconnect"
    property string connected: "checkmark"
    property string success: "checkmark"

    property string markAsRead: "mail-mark-unread-new"
    property string markImportant: "mail-mark-important"
    property string undo: "edit-undo"
    property string moveToTrash: "edit-delete"
    property string edit: "document-edit"
    property string replyToSender: "mail-reply-sender"

    property string menu: "application-menu"
    property string user: "im-user"
    property string search: "edit-find"
    property string goBack: "go-previous"
    property string goDown: "go-down"
    property string goUp: "go-down"

    property string addNew: "list-add-new"
    property string folder: "folder"

}

