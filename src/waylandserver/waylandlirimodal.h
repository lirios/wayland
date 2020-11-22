// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef LIRI_WAYLANDLIRIMODAL_H
#define LIRI_WAYLANDLIRIMODAL_H

#include <QtWaylandCompositor/QWaylandCompositorExtension>

#include <LiriWaylandServer/liriwaylandserverglobal.h>

class WaylandLiriModalManagerPrivate;

class LIRIWAYLANDSERVER_EXPORT WaylandLiriModalManager
        : public QWaylandCompositorExtensionTemplate<WaylandLiriModalManager>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(WaylandLiriModalManager)
    Q_PROPERTY(bool grabbed READ isGrabbed NOTIFY grabbedChanged)
public:
    WaylandLiriModalManager();
    WaylandLiriModalManager(QWaylandCompositor *compositor);
    ~WaylandLiriModalManager();

    void initialize() override;

    bool isGrabbed() const;

    Q_INVOKABLE void sendDone();

    static const wl_interface *interface();
    static QByteArray interfaceName();

Q_SIGNALS:
    void grabbedChanged();

private:
    WaylandLiriModalManagerPrivate *const d_ptr = nullptr;
};

#endif // LIRI_WAYLANDLIRIMODAL_H
