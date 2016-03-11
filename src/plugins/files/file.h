// albert - a simple application launcher for linux
// Copyright (C) 2014-2015 Manuel Schneider
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include <QMimeType>
#include <vector>
#include <map>
#include <memory>
#include "abstractobjects.hpp"
using std::vector;
using std::map;
using std::shared_ptr;
using std::unique_ptr;

namespace Files {

class File final : public AlbertItem
{
    friend class Extension;
    friend class Indexer;

public:

    class OpenFileAction;
    class RevealFileAction;
    class CopyFileAction;
    class CopyPathAction;

    File() = delete;
    File(const File &) = delete;
    File(QString path, QMimeType mimetype, short usage = 0);

    /*
     * Implementation of AlbertItem interface
     */

    QUrl iconUrl() const override;
    QString text() const override;
    QString subtext() const override;
    vector<QString> aliases() const override;
    void activate() override;
    uint16_t usageCount() const { return usage_; }
    ActionSPtrVec actions() override;

    /*
     * Item specific members
     */

    /** Serialize the desktop entry */
    void serialize(QDataStream &out);

    /** Deserialize the desktop entry */
    void deserialize(QDataStream &in);

    /** Return the path of the file */
    const QString &path() const { return path_; }

    /** Return the mimetype of the file */
    const QMimeType &mimetype() const { return mimetype_; }

    /** Clears the icon cache */
    static void clearIconCache();

private:
    QString path_;
    QMimeType mimetype_;
    mutable short usage_;
    unique_ptr<ActionSPtrVec> children_;
    static map<QString, QUrl> iconCache_;
};

}
