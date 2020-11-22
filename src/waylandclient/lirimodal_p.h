// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef LIRI_LIRIMODAL_CLIENT_P_H
#define LIRI_LIRIMODAL_CLIENT_P_H

#include <LiriWaylandClient/LiriModal>
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

class LIRIWAYLANDCLIENT_EXPORT LiriModalGrab
        : public QtWayland::liri_modal
{
public:
    LiriModalGrab(LiriModal *modal);
    ~LiriModalGrab();

    LiriModal *manager = nullptr;

protected:
    void liri_modal_done() override;
};

class LIRIWAYLANDCLIENT_EXPORT LiriModalPrivate
        : public QtWayland::liri_modal_manager
{
    Q_DECLARE_PUBLIC(LiriModal)
public:
    LiriModalPrivate(LiriModal *self);
    ~LiriModalPrivate();

    QVector<LiriModalGrab *> grabs;

    void removeGrab(LiriModalGrab *grab);
    void removeAllGrabs();

    static LiriModalPrivate *get(LiriModal *modal) { return modal->d_func(); }

protected:
    LiriModal *q_ptr = nullptr;
};

#endif // LIRI_LIRIMODAL_CLIENT_P_H
