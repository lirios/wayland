// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "lirimodal_p.h"
#include "utils_p.h"

/*
 * LiriModalPrivate
 */

LiriModalPrivate::LiriModalPrivate(LiriModal *self)
    : QtWayland::liri_modal_manager()
    , q_ptr(self)
{
}

LiriModalPrivate::~LiriModalPrivate()
{
    qDeleteAll(grabs);
}

void LiriModalPrivate::removeGrab(LiriModalGrab *grab)
{
    Q_Q(LiriModal);

    if (grabs.removeOne(grab)) {
        Q_EMIT q->grabbedChanged();
        delete grab;
    }
}

void LiriModalPrivate::removeAllGrabs()
{
    Q_Q(LiriModal);

    bool changed = false;

    auto it = grabs.begin();
    while (it != grabs.end()) {
        delete (*it);
        it = grabs.erase(it);
        changed = true;
    }

    if (changed)
        Q_EMIT q->grabbedChanged();
}

/*
 * LiriModalGrab
 */

LiriModalGrab::LiriModalGrab(LiriModal *modal)
    : manager(modal)
{
}

LiriModalGrab::~LiriModalGrab()
{
    destroy();
}

void LiriModalGrab::liri_modal_done()
{
    LiriModalPrivate::get(manager)->removeGrab(this);
}

/*
 * LiriModal
 */

LiriModal::LiriModal()
    : QWaylandClientExtensionTemplate<LiriModal>(1)
    , d_ptr(new LiriModalPrivate(this))
{
}

LiriModal::~LiriModal()
{
    delete d_ptr;
}

void LiriModal::grab()
{
    Q_D(LiriModal);

    auto *modalGrab = new LiriModalGrab(this);
    modalGrab->init(d->grab(getWlSeat()));
    d->grabs.append(modalGrab);
}

void LiriModal::close()
{
    Q_D(LiriModal);
    d->removeAllGrabs();
}

void LiriModal::init(struct ::wl_registry *registry, int id, int version)
{
    Q_D(LiriModal);
    d->init(registry, id, version);
}

const struct ::wl_interface *LiriModal::interface()
{
    return LiriModalPrivate::interface();
}

bool LiriModal::isGrabbed() const
{
    Q_D(const LiriModal);
    return d->grabs.size() > 0;
}
