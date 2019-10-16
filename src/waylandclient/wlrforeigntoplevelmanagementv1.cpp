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

#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>
#include <QWindow>
#include <QScreen>

#include "logging_p.h"
#include "wlrforeigntoplevelmanagementv1_p.h"

static inline struct ::wl_surface *getWlSurface(QWindow *window)
{
    void *surface = QGuiApplication::platformNativeInterface()->nativeResourceForWindow("surface", window);
    return static_cast<struct ::wl_surface *>(surface);
}

static inline struct ::wl_output *getWlOutput(QScreen *screen)
{
    void *output = QGuiApplication::platformNativeInterface()->nativeResourceForScreen("output", screen);
    return static_cast<struct ::wl_output *>(output);
}

static inline QScreen *getScreen(struct ::wl_output *output)
{
    const auto screens = QGuiApplication::screens();
    for (auto screen : screens) {
        if (getWlOutput(screen) == output)
            return screen;
    }

    return nullptr;
}


WlrForeignToplevelManagerV1Private::WlrForeignToplevelManagerV1Private(WlrForeignToplevelManagerV1 *self)
    : QtWayland::zwlr_foreign_toplevel_manager_v1()
    , q_ptr(self)
{
}

void WlrForeignToplevelManagerV1Private::zwlr_foreign_toplevel_manager_v1_toplevel(struct ::zwlr_foreign_toplevel_handle_v1 *toplevel)
{
    Q_Q(WlrForeignToplevelManagerV1);

    auto *handle = new WlrForeignToplevelHandleV1(q);
    handle->d_func()->init(toplevel);
    emit q->toplevel(handle);
}

void WlrForeignToplevelManagerV1Private::zwlr_foreign_toplevel_manager_v1_finished()
{
}


WlrForeignToplevelHandleV1Private::WlrForeignToplevelHandleV1Private(WlrForeignToplevelHandleV1 *self)
    : QtWayland::zwlr_foreign_toplevel_handle_v1()
    , q_ptr(self)
{
}

void WlrForeignToplevelHandleV1Private::zwlr_foreign_toplevel_handle_v1_title(const QString &title)
{
    pending.title = title;
}

void WlrForeignToplevelHandleV1Private::zwlr_foreign_toplevel_handle_v1_app_id(const QString &appId)
{
    pending.appId = appId;
}

void WlrForeignToplevelHandleV1Private::zwlr_foreign_toplevel_handle_v1_output_enter(wl_output *output)
{
    Q_Q(WlrForeignToplevelHandleV1);

    auto screen = getScreen(output);
    if (!screen) {
        qCWarning(lcWaylandClient, "Cannot find a screen for wl_output");
        return;
    }

    emit q->enteredOutput(screen);
}

void WlrForeignToplevelHandleV1Private::zwlr_foreign_toplevel_handle_v1_output_leave(wl_output *output)
{
    Q_Q(WlrForeignToplevelHandleV1);

    auto screen = getScreen(output);
    if (!screen) {
        qCWarning(lcWaylandClient, "Cannot find a screen for wl_output");
        return;
    }

    emit q->leftOutput(screen);
}

void WlrForeignToplevelHandleV1Private::zwlr_foreign_toplevel_handle_v1_state(wl_array *rawData)
{
    if (rawData) {
        pending.minimized = pending.maximized = pending.fullscreen = pending.activated = false;

        const auto rawStateCount = rawData->size / sizeof(uint32_t);
        uint32_t *s = static_cast<uint32_t *>(rawData->data);
        for (auto i = 0; i < rawStateCount; ++i) {
            uint32_t state = *s++;

            if (state == state_minimized)
                pending.minimized = true;
            if (state == state_maximized)
                pending.maximized = true;
            if (state == state_fullscreen)
                pending.fullscreen = true;
            if (state == state_activated)
                pending.activated = true;
        }
    }
}

void WlrForeignToplevelHandleV1Private::zwlr_foreign_toplevel_handle_v1_done()
{
    Q_Q(WlrForeignToplevelHandleV1);

    // All pending changes are valid now
    if (effective.title != pending.title) {
        effective.title = pending.title;
        emit q->titleChanged(effective.title);
    }
    if (effective.appId != pending.appId) {
        QString oldAppId = effective.appId;
        effective.appId = pending.appId;
        emit q->appIdChanged(oldAppId, effective.appId);
    }
    if (effective.minimized != pending.minimized) {
        effective.minimized = pending.minimized;
        emit q->minimizedChanged(effective.minimized);
    }
    if (effective.maximized != pending.maximized) {
        effective.maximized = pending.maximized;
        emit q->maximizedChanged(effective.maximized);
    }
    if (effective.fullscreen != pending.fullscreen) {
        effective.fullscreen = pending.fullscreen;
        emit q->fullscreenChanged(effective.fullscreen);
    }
    if (effective.activated != pending.activated) {
        effective.activated = pending.activated;
        emit q->activatedChanged(effective.activated);
    }
}

void WlrForeignToplevelHandleV1Private::zwlr_foreign_toplevel_handle_v1_closed()
{
    Q_Q(WlrForeignToplevelHandleV1);
    emit q->closed();
}


WlrForeignToplevelManagerV1::WlrForeignToplevelManagerV1()
    : QWaylandClientExtensionTemplate<WlrForeignToplevelManagerV1>(2)
    , d_ptr(new WlrForeignToplevelManagerV1Private(this))
{
}

WlrForeignToplevelManagerV1::~WlrForeignToplevelManagerV1()
{
    delete d_ptr;
}

void WlrForeignToplevelManagerV1::init(wl_registry *registry, int id, int version)
{
    Q_D(WlrForeignToplevelManagerV1);
    d->init(registry, id, version);
}

const wl_interface *WlrForeignToplevelManagerV1::interface()
{
    return WlrForeignToplevelManagerV1Private::interface();
}


WlrForeignToplevelHandleV1::WlrForeignToplevelHandleV1(QObject *parent)
    : QObject(parent)
    , d_ptr(new WlrForeignToplevelHandleV1Private(this))
{
}

WlrForeignToplevelHandleV1::~WlrForeignToplevelHandleV1()
{
    delete d_ptr;
}

QString WlrForeignToplevelHandleV1::title() const
{
    Q_D(const WlrForeignToplevelHandleV1);
    return d->effective.title;
}

QString WlrForeignToplevelHandleV1::appId() const
{
    Q_D(const WlrForeignToplevelHandleV1);
    return d->effective.appId;
}

bool WlrForeignToplevelHandleV1::isMinimized() const
{
    Q_D(const WlrForeignToplevelHandleV1);
    return d->effective.minimized;
}

bool WlrForeignToplevelHandleV1::isMaximized() const
{
    Q_D(const WlrForeignToplevelHandleV1);
    return d->effective.maximized;
}

bool WlrForeignToplevelHandleV1::isFullscreen() const
{
    Q_D(const WlrForeignToplevelHandleV1);
    return d->effective.fullscreen;
}

bool WlrForeignToplevelHandleV1::isActived() const
{
    Q_D(const WlrForeignToplevelHandleV1);
    return d->effective.activated;
}

void WlrForeignToplevelHandleV1::setMinimized()
{
    Q_D(WlrForeignToplevelHandleV1);
    d->set_minimized();
}

void WlrForeignToplevelHandleV1::unsetMinimized()
{
    Q_D(WlrForeignToplevelHandleV1);
    d->unset_minimized();
}

void WlrForeignToplevelHandleV1::setMaximized()
{
    Q_D(WlrForeignToplevelHandleV1);
    d->set_maximized();
}

void WlrForeignToplevelHandleV1::unsetMaximized()
{
    Q_D(WlrForeignToplevelHandleV1);
    d->unset_maximized();
}

void WlrForeignToplevelHandleV1::setFullscreen(QScreen *screen)
{
    Q_D(WlrForeignToplevelHandleV1);

    auto output = getWlOutput(screen);
    if (!output) {
        qCWarning(lcWaylandClient, "Cannot find wl_output for screen %s",
                  qPrintable(screen->name()));
        return;
    }

    d->set_fullscreen(output);
}

void WlrForeignToplevelHandleV1::unsetFullscreen()
{
    Q_D(WlrForeignToplevelHandleV1);
    d->unset_fullscreen();
}

void WlrForeignToplevelHandleV1::activate(struct ::wl_seat *seat)
{
    Q_D(WlrForeignToplevelHandleV1);
    d->activate(seat);
}

void WlrForeignToplevelHandleV1::setRectangle(QWindow *window, const QRect &rect)
{
    Q_D(WlrForeignToplevelHandleV1);
    d->set_rectangle(getWlSurface(window), rect.x(), rect.y(), rect.width(), rect.height());
}

void WlrForeignToplevelHandleV1::close()
{
    Q_D(WlrForeignToplevelHandleV1);
    d->close();
}
