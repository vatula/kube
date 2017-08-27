/*
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

#include <QAbstractItemModel>
#include <QModelIndex>

#include <memory>

namespace MimeTreeParser {
    class ObjectTreeParser;
}
class PartModelPrivate;

class PartModel : public QAbstractItemModel {
    Q_OBJECT
public:
    PartModel(std::shared_ptr<MimeTreeParser::ObjectTreeParser> parser);
    ~PartModel();

public:
    enum Roles {
        TypeRole  = Qt::UserRole + 1,
        ContentRole,
        IsEmbeddedRole,
        IsEncryptedRole,
        IsSignedRole,
        IsErrorRole,
        SecurityLevelRole,
        SignatureDetails,
        EncryptionDetails,
        ErrorType,
        ErrorString,
        SenderRole,
        DateRole
    };

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
    std::unique_ptr<PartModelPrivate> d;
};

class SignatureInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QByteArray keyId MEMBER mKeyId CONSTANT)
    Q_PROPERTY(bool keyMissing MEMBER mKeyMissing CONSTANT)
    Q_PROPERTY(bool keyRevoked MEMBER mKeyRevoked CONSTANT)
    Q_PROPERTY(bool keyExpired MEMBER mKeyExpired CONSTANT)
    Q_PROPERTY(bool sigExpired MEMBER mSigExpired CONSTANT)
    Q_PROPERTY(bool crlMissing MEMBER mCrlMissing CONSTANT)
    Q_PROPERTY(bool crlTooOld MEMBER mCrlTooOld CONSTANT)

    Q_PROPERTY(QString signer MEMBER mSigner CONSTANT)
    Q_PROPERTY(QString signClass MEMBER mSignClass CONSTANT)
    Q_PROPERTY(QStringList signerMailAddresses MEMBER mSignerMailAddresses CONSTANT)
    Q_PROPERTY(bool signatureIsGood MEMBER mSignatureIsGood CONSTANT)
    Q_PROPERTY(bool keyIsTrusted MEMBER mKeyIsTrusted CONSTANT)

public:
    bool mKeyRevoked = false;
    bool mKeyExpired = false;
    bool mSigExpired = false;
    bool mKeyMissing = false;
    bool mCrlMissing = false;
    bool mCrlTooOld = false;
    QByteArray mKeyId;

    QString mSigner;
    QString mSignClass;
    QStringList mSignerMailAddresses;
    bool mSignatureIsGood = false;
    bool mKeyIsTrusted = false;
};

