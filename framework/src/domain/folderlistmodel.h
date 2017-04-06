/*
    Copyright (c) 2016 Michael Bohlender <michael.bohlender@kdemail.net>
    Copyright (c) 2016 Christian Mollekopf <mollekopf@kolabsys.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#pragma once

#include <QObject>
#include <QSortFilterProxyModel>
#include <QSharedPointer>
#include <QStringList>

namespace Sink {
    class Query;
}

class FolderListModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY (QVariant accountId READ accountId WRITE setAccountId)

public:
    enum Status {
        NoStatus,
        InProgressStatus,
        ErrorStatus,
        SuccessStatus,
    };
    Q_ENUMS(Status)

    FolderListModel(QObject *parent = Q_NULLPTR);
    ~FolderListModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    enum Roles {
        Name  = Qt::UserRole + 1,
        Icon,
        Id,
        DomainObject,
        Status
    };
    Q_ENUMS(Roles)

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    void setAccountId(const QVariant &accountId);
    QVariant accountId() const;
protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

private:
    void runQuery(const Sink::Query &query);
    QSharedPointer<QAbstractItemModel> mModel;
};