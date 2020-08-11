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

#ifndef LIRI_LIRISHELL_P_CLIENT_H
#define LIRI_LIRISHELL_P_CLIENT_H

#include <LiriWaylandClient/LiriShell>
#include <LiriWaylandClient/private/qwayland-liri-shell.h>

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Liri API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

class LiriShellPrivate : public QtWayland::liri_shell
{
    Q_DECLARE_PUBLIC(LiriShell)
public:
    LiriShellPrivate(LiriShell *qq);

    void setCursorShape(QWindow *window, LiriShell::GrabCursor cursor);

    static LiriShellPrivate *get(LiriShell *shell) { return shell ? shell->d_func() : nullptr; }

    QWindow *grabWindow = nullptr;

protected:
    LiriShell *q_ptr;

private:
    void liri_shell_grab_cursor(uint32_t cursor) override;
    void liri_shell_shutdown_requested() override;
    void liri_shell_quit() override;
};

class LiriShortcutPrivate : public QtWayland::liri_shortcut
{
    Q_DECLARE_PUBLIC(LiriShortcut)
public:
    LiriShortcutPrivate(LiriShortcut *self);
    ~LiriShortcutPrivate();

    LiriShell *shell = nullptr;
    QString sequence;

protected:
    LiriShortcut *q_ptr;

    void liri_shortcut_activated(struct ::wl_seat *seat);
};

class LiriOsdPrivate : public QtWayland::liri_osd
{
    Q_DECLARE_PUBLIC(LiriOsd)
public:
    LiriOsdPrivate(LiriOsd *self);

    bool initialized = false;
    LiriShell *shell = nullptr;

protected:
    LiriOsd *q_ptr;

    void liri_osd_text(const QString &icon_name, const QString &label) override;
    void liri_osd_progress(const QString &icon_name, uint32_t value) override;
};

#endif // LIRI_LIRISHELL_P_CLIENT_H
