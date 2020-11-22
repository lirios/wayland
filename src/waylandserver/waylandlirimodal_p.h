// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef LIRI_WAYLANDLIRIMODAL_P_H
#define LIRI_WAYLANDLIRIMODAL_P_H

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

#include <LiriWaylandServer/WaylandLiriModal>
#include <LiriWaylandServer/private/qwayland-server-liri-shell.h>

class LIRIWAYLANDSERVER_EXPORT WaylandLiriModal
        : public QtWaylandServer::liri_modal
{
public:
    WaylandLiriModal() = default;

    WaylandLiriModalManagerPrivate *manager = nullptr;

protected:
    void liri_modal_destroy_resource(Resource *resource) override;
    void liri_modal_destroy(Resource *resource) override;
};

class LIRIWAYLANDSERVER_EXPORT WaylandLiriModalManagerPrivate
        : public QtWaylandServer::liri_modal_manager
{
    Q_DECLARE_PUBLIC(WaylandLiriModalManager)
public:
    explicit WaylandLiriModalManagerPrivate(WaylandLiriModalManager *self);

    void removeGrab(WaylandLiriModal *grab);

    QVector<WaylandLiriModal *> grabs;

protected:
    WaylandLiriModalManager *q_ptr = nullptr;

    void liri_modal_manager_grab(Resource *resource, uint32_t id,
                                 struct ::wl_resource *seatResource) override;
};

#endif // LIRI_WAYLANDLIRIMODAL_P_H
