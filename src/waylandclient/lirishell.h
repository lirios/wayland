/****************************************************************************
 * This file is part of Liri.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPLv3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef LIRI_LIRISHELL_CLIENT_H
#define LIRI_LIRISHELL_CLIENT_H

#include <QtCore/QObject>
#include <QtWaylandClient/QWaylandClientExtension>

#include <LiriWaylandClient/liriwaylandclientglobal.h>

#include <wayland-client.h>

QT_FORWARD_DECLARE_CLASS(QWindow)

class LiriShellPrivate;
class LiriShortcutPrivate;
class LiriOsdPrivate;

class LIRIWAYLANDCLIENT_EXPORT LiriShell : public QWaylandClientExtensionTemplate<LiriShell>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriShell)
public:
    enum GrabCursor {
        NoGrabCursor = 0,
        ResizeTopGrabCursor,
        ResizeBottomGrabCursor,
        ArrowGrabCursor,
        ResizeLeftGrabCursor,
        ResizeTopLeftGrabCursor,
        ResizeBottomLeftGrabCursor,
        MoveGrabCursor,
        ResizeRightGrabCursor,
        ResizeTopRightGrabCursor,
        ResizeBottomRightGrabCursor,
        BusyGrabCursor
    };
    Q_ENUM(GrabCursor)

    LiriShell();
    ~LiriShell();

    void init(struct ::wl_registry *registry, int id, int version);

    Q_INVOKABLE void registerGrabSurface(QWindow *window);
    Q_INVOKABLE void sendReady();

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void cursorChangeRequested(LiriShell::GrabCursor cursor);
    void quitRequested();

private:
    LiriShellPrivate *const d_ptr;
};

class LIRIWAYLANDCLIENT_EXPORT LiriShortcut : public QWaylandClientExtension
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriShortcut)
    Q_PROPERTY(LiriShell *shell READ shell WRITE setShell NOTIFY shellChanged)
    Q_PROPERTY(QString sequence READ sequence WRITE setSequence NOTIFY sequenceChanged)
public:
    LiriShortcut();
    ~LiriShortcut();

    LiriShell *shell() const;
    void setShell(LiriShell *shell);

    QString sequence() const;
    void setSequence(const QString &sequence);

    const struct wl_interface *extensionInterface() const override { return interface(); }
    void bind(struct ::wl_registry *registry, int id, int ver) override;

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void shellChanged();
    void sequenceChanged();
    void activated(struct ::wl_seat *seat);

public Q_SLOTS:
    void bindShortcut();

private:
    LiriShortcutPrivate *const d_ptr;
};

class LIRIWAYLANDCLIENT_EXPORT LiriOsd : public QWaylandClientExtensionTemplate<LiriOsd>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriOsd)
public:
    LiriOsd();
    ~LiriOsd();

    void init(struct ::wl_registry *registry, int id, int version);

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void textRequested(const QString &iconName, const QString &text);
    void progressRequested(const QString &iconName, quint32 value);

private:
    LiriOsdPrivate *const d_ptr;
};

#endif // LIRI_LIRISHELL_CLIENT_H
