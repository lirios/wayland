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

#ifndef LIRI_WAYLANDLIRISHELL_P_H
#define LIRI_WAYLANDLIRISHELL_P_H

#include <LiriWaylandServer/WaylandLiriShell>
#include <LiriWaylandServer/private/qwayland-server-liri-shell.h>

class WaylandLiriShell;
class WaylandLiriShortcut;

class LIRIWAYLANDSERVER_EXPORT WaylandLiriShellPrivate : public QtWaylandServer::liri_shell
{
    Q_DECLARE_PUBLIC(WaylandLiriShell)
public:
    explicit WaylandLiriShellPrivate(WaylandLiriShell *qq);

    static WaylandLiriShellPrivate *get(WaylandLiriShell *shell);

    QWaylandSurface *grabSurface = nullptr;

protected:
    WaylandLiriShell *q_ptr;

private:
    void liri_shell_bind_resource(Resource *r) override;
    void liri_shell_set_grab_surface(Resource *resource, struct ::wl_resource *wlSurface) override;
    void liri_shell_bind_shortcut(Resource *resource, uint32_t id, const QString &sequence) override;
    void liri_shell_ready(Resource *resource) override;
    void liri_shell_terminate(Resource *resource) override;
};

class LIRIWAYLANDSERVER_EXPORT WaylandLiriShortcutPrivate
        : public QtWaylandServer::liri_shortcut
{
    Q_DECLARE_PUBLIC(WaylandLiriShortcut)
public:
    explicit WaylandLiriShortcutPrivate(WaylandLiriShortcut *self);

    static WaylandLiriShortcutPrivate *get(WaylandLiriShortcut *self) { return self->d_func(); }

    QWaylandCompositor *compositor = nullptr;
    QString sequence;

protected:
    WaylandLiriShortcut *q_ptr;

    void liri_shortcut_destroy_resource(Resource *resource) override;
    void liri_shortcut_destroy(Resource *resource) override;
};

class LIRIWAYLANDSERVER_EXPORT WaylandLiriOsdPrivate : public QtWaylandServer::liri_osd
{
    Q_DECLARE_PUBLIC(WaylandLiriOsd)
public:
    explicit WaylandLiriOsdPrivate(WaylandLiriOsd *self);

protected:
    WaylandLiriOsd *q_ptr;
};

#endif // LIRI_WAYLANDLIRISHELL_P_H
