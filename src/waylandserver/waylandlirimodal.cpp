// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QWaylandCompositor>

#include "logging_p.h"
#include "waylandlirimodal_p.h"

/*
 * WaylandLiriModal
 */

void WaylandLiriModal::liri_modal_destroy_resource(Resource *resource)
{
    Q_UNUSED(resource);
    manager->removeGrab(this);
    delete this;
}

void WaylandLiriModal::liri_modal_destroy(Resource *resource)
{
    wl_resource_destroy(resource->handle);
}

/*
 * WaylandLiriModalManagerPrivate
 */

WaylandLiriModalManagerPrivate::WaylandLiriModalManagerPrivate(WaylandLiriModalManager *self)
    : QtWaylandServer::liri_modal_manager()
    , q_ptr(self)
{
}

void WaylandLiriModalManagerPrivate::removeGrab(WaylandLiriModal *grab)
{
    Q_Q(WaylandLiriModalManager);

    if (grabs.removeOne(grab))
        Q_EMIT q->grabbedChanged();
}

void WaylandLiriModalManagerPrivate::liri_modal_manager_grab(Resource *resource, uint32_t id,
                                                             struct ::wl_resource *seatResource)
{
    Q_UNUSED(seatResource);
    Q_Q(WaylandLiriModalManager);

    auto *modal = new WaylandLiriModal();
    modal->manager = this;
    modal->init(resource->client(), id, WaylandLiriModal::interfaceVersion());

    grabs.append(modal);
    Q_EMIT q->grabbedChanged();
}

/*
 * WaylandLiriModalManager
 */

WaylandLiriModalManager::WaylandLiriModalManager()
    : QWaylandCompositorExtensionTemplate<WaylandLiriModalManager>()
    , d_ptr(new WaylandLiriModalManagerPrivate(this))
{
}

WaylandLiriModalManager::WaylandLiriModalManager(QWaylandCompositor *compositor)
    : QWaylandCompositorExtensionTemplate<WaylandLiriModalManager>(compositor)
    , d_ptr(new WaylandLiriModalManagerPrivate(this))
{
}

WaylandLiriModalManager::~WaylandLiriModalManager()
{
    delete d_ptr;
}

void WaylandLiriModalManager::initialize()
{
    Q_D(WaylandLiriModalManager);

    QWaylandCompositorExtensionTemplate::initialize();
    QWaylandCompositor *compositor = static_cast<QWaylandCompositor *>(extensionContainer());
    if (!compositor) {
        qCWarning(lcLiriShell) << "Failed to find QWaylandCompositor when initializing WaylandLiriModal";
        return;
    }
    d->init(compositor->display(), WaylandLiriModalManagerPrivate::interfaceVersion());
}

bool WaylandLiriModalManager::isGrabbed() const
{
    Q_D(const WaylandLiriModalManager);
    return d->grabs.size() > 0;
}

void WaylandLiriModalManager::sendDone()
{
    Q_D(WaylandLiriModalManager);

    bool changed = false;

    auto it = d->grabs.begin();
    while (it != d->grabs.end()) {
        (*it)->send_done();
        it = d->grabs.erase(it);
        changed = true;
    }

    if (changed)
        Q_EMIT grabbedChanged();
}

const wl_interface *WaylandLiriModalManager::interface()
{
    return WaylandLiriModalManagerPrivate::interface();
}

QByteArray WaylandLiriModalManager::interfaceName()
{
    return WaylandLiriModalManagerPrivate::interfaceName();
}
