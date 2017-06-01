/*
    Copyright (c) 2016 Sandro Knauß <knauss@kolabsys.com>

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

#include "messageparser.h"
#include "mimetreeparser/interface.h"

#include <QDebug>
#include <KMime/Content>
#include <QFile>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QDir>

QString sizeHuman(const Content::Ptr &content)
{
    float num = content->content().size();
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("Bytes");

    while(num >= 1024.0 && i.hasNext())
     {
        unit = i.next();
        num /= 1024.0;
    }

    if (unit == "Bytes") {
        return QString().setNum(num) + " " + unit;
    } else {
        return QString().setNum(num,'f',2)+" "+unit;
    }
}

class AttachmentModelPrivate
{
public:
    AttachmentModelPrivate(AttachmentModel *q_ptr, const std::shared_ptr<Parser> &parser);

    AttachmentModel *q;
    std::shared_ptr<Parser> mParser;
    QVector<Part::Ptr> mAttachments;
};

AttachmentModelPrivate::AttachmentModelPrivate(AttachmentModel* q_ptr, const std::shared_ptr<Parser>& parser)
    : q(q_ptr)
    , mParser(parser)
{
    mAttachments = mParser->collectAttachmentParts();
}

AttachmentModel::AttachmentModel(std::shared_ptr<Parser> parser)
    : d(std::unique_ptr<AttachmentModelPrivate>(new AttachmentModelPrivate(this, parser)))
{
}

AttachmentModel::~AttachmentModel()
{
}

QHash<int, QByteArray> AttachmentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[NameRole] = "name";
    roles[SizeRole] = "size";
    roles[IconRole] = "iconName";
    roles[IsEncryptedRole] = "encrypted";
    roles[IsSignedRole] = "signed";
    return roles;
}

QModelIndex AttachmentModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row < 0 || column != 0) {
        return QModelIndex();
    }

    if (row < d->mAttachments.size()) {
        return createIndex(row, column, d->mAttachments.at(row).get());
    }
    return QModelIndex();
}

QVariant AttachmentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        switch (role) {
        case Qt::DisplayRole:
            return QString("root");
        }
        return QVariant();
    }

    if (index.internalPointer()) {
        const auto entry = static_cast<Part *>(index.internalPointer());
        const auto content = entry->content().at(0);
        switch(role) {
        case TypeRole:
            return content->mailMime()->mimetype().name();
        case NameRole:
            return entry->mailMime()->filename();
        case IconRole:
            return content->mailMime()->mimetype().iconName();
        case SizeRole:
            return sizeHuman(content);
        case IsEncryptedRole:
            return content->encryptions().size() > 0;
        case IsSignedRole:
            return content->signatures().size() > 0;
        }
    }
    return QVariant();
}

static QString saveAttachmentToDisk(const QModelIndex &index, const QString &path, bool readonly = false)
{
    if (index.internalPointer()) {
        const auto entry = static_cast<Part *>(index.internalPointer());
        const auto content = entry->content().at(0);
        auto filename = entry->mailMime()->filename();
        auto data = content->mailMime()->decodedContent();
        if (content->mailMime()->isText() && !data.isEmpty()) {
            // convert CRLF to LF before writing text attachments to disk
            data = KMime::CRLFtoLF(data);
        }
        auto fname = path + filename;
        QFile f(fname);
        if (!f.open(QIODevice::ReadWrite)) {
            qWarning() << "Failed to write attachment to file:" << fname << " Error: " << f.errorString();
            return {};
        }
        f.write(data);
        if (readonly) {
            // make file read-only so that nobody gets the impression that he migh edit attached files
            f.setPermissions(QFileDevice::ReadUser);
        }
        f.close();
        qInfo() << "Wrote attachment to file: " << fname;
        return fname;
    }
    return {};

}

bool AttachmentModel::saveAttachmentToDisk(const QModelIndex &index)
{
    auto downloadDir = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    if (downloadDir.isEmpty()) {
        downloadDir = "~";
    }
    downloadDir += "/kube/";
    QDir{}.mkpath(downloadDir);
    return !::saveAttachmentToDisk(index, downloadDir).isEmpty();
}

bool AttachmentModel::openAttachment(const QModelIndex &index)
{
    auto downloadDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation)+ "/kube/";
    QDir{}.mkpath(downloadDir);
    const auto filePath = ::saveAttachmentToDisk(index, downloadDir, true);
    if (!filePath.isEmpty()) {
        QDesktopServices::openUrl(QUrl("file://" + filePath));
        return true;
    }
    return false;
}

QModelIndex AttachmentModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int AttachmentModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return d->mAttachments.size();
    }
    return 0;
}

int AttachmentModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}
