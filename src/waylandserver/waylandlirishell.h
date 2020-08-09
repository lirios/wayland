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

#ifndef LIRI_WAYLANDLIRISHELL_H
#define LIRI_WAYLANDLIRISHELL_H

#include <QtWaylandCompositor/QWaylandCompositorExtension>

#include <LiriWaylandServer/liriwaylandserverglobal.h>

QT_FORWARD_DECLARE_CLASS(QWaylandSeat)
QT_FORWARD_DECLARE_CLASS(QWaylandSurface)

class WaylandLiriShellPrivate;
class WaylandLiriShortcutPrivate;
class WaylandLiriOsdPrivate;

class LIRIWAYLANDSERVER_EXPORT WaylandLiriShortcut : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(WaylandLiriShortcut)
    Q_PROPERTY(QString sequence READ sequence CONSTANT)
public:
    explicit WaylandLiriShortcut(const QString &sequence,
                                 QWaylandCompositor *compositor,
                                 QObject *parent = nullptr);
    ~WaylandLiriShortcut();

    QString sequence() const;

    Q_INVOKABLE void activate(QWaylandSeat *seat = nullptr);

private:
    WaylandLiriShortcutPrivate *const d_ptr;
};

class LIRIWAYLANDSERVER_EXPORT WaylandLiriShell : public QWaylandCompositorExtensionTemplate<WaylandLiriShell>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(WaylandLiriShell)
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

    WaylandLiriShell();
    explicit WaylandLiriShell(QWaylandCompositor *compositor);
    ~WaylandLiriShell();

    void initialize() override;

    Q_INVOKABLE void grabCursor(WaylandLiriShell::GrabCursor cursor);
    Q_INVOKABLE void sendQuit();

    static const struct wl_interface *interface();
    static QByteArray interfaceName();

Q_SIGNALS:
    void shortcutBound(WaylandLiriShortcut *shortcut);
    void grabSurfaceAdded(QWaylandSurface *surface);
    void ready();

private:
    WaylandLiriShellPrivate *const d_ptr;
};

class LIRIWAYLANDSERVER_EXPORT WaylandLiriOsd : public QWaylandCompositorExtensionTemplate<WaylandLiriOsd>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(WaylandLiriOsd)
public:
    WaylandLiriOsd();
    WaylandLiriOsd(QWaylandCompositor *compositor);
    ~WaylandLiriOsd();

    void initialize() override;

    Q_INVOKABLE void showText(const QString &iconName, const QString &text = QString());
    Q_INVOKABLE void showProgress(const QString &iconName, quint32 value);

    static const struct wl_interface *interface();
    static QByteArray interfaceName();

private:
    WaylandLiriOsdPrivate *const d_ptr;
};

#endif // LIRI_WAYLANDLIRISHELL_H
