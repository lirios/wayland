// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "utils_p.h"
#include "viewporter_p.h"

/*
 * ViewporterInterface
 */

ViewporterInterface::ViewporterInterface()
    : QWaylandClientExtensionTemplate<ViewporterInterface>(1)
    , QtWayland::wp_viewporter()
{
}

/*
 * ViewportPrivate
 */

ViewportPrivate::~ViewportPrivate()
{
    if (viewport)
        viewport->destroy();
    if (viewporter)
        viewporter->deleteLater();
}

/*
 * Viewport
 */

Viewport::Viewport(QObject *parent)
    : QObject(parent)
    , d_ptr(new ViewportPrivate)
{
    //Q_D(Viewport);

    //connect(d->viewporter, &ViewporterInterface::activeChanged,
            //this, &Viewport::activeChanged);
}

Viewport::~Viewport()
{
    delete d_ptr;
}

bool Viewport::isActive() const
{
    Q_D(const Viewport);
    return d->viewporter && d->viewporter->isActive() && d->viewport;
}

QWindow *Viewport::window() const
{
    Q_D(const Viewport);
    return d->window;
}

void Viewport::setWindow(QWindow *window)
{
    Q_D(Viewport);

    if (d->isInitialized)
        return;

    d->window = window;
    Q_EMIT windowChanged();
}

void Viewport::initialize()
{
    Q_D(Viewport);

    if (d->isInitialized)
        return;

    const bool wasActive = isActive();

    d->isInitialized = true;

    d->viewporter = new ViewporterInterface();
    connect(d->viewporter, &ViewporterInterface::activeChanged,
            this, [d] {
        if (d->viewporter->isActive()) {
            auto *surface = getWlSurface(d->window);
            auto *object = d->viewporter->get_viewport(surface);

            d->viewport = new ViewportInterface();
            d->viewport->init(object);
            auto x = wl_fixed_from_int(400);
            auto y = wl_fixed_from_int(400);
            auto w = wl_fixed_from_int(400);
            auto h = wl_fixed_from_int(400);
            d->viewport->set_destination(400, 400);
            d->viewport->set_source(x, y, w, h);

            //wl_surface_commit(surface);
        }
    });

    const bool isActiveNow = isActive();

    if (wasActive != isActiveNow)
        Q_EMIT activeChanged();
}
