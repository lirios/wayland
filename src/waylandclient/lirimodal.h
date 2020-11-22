// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef LIRI_LIRIMODAL_CLIENT_H
#define LIRI_LIRIMODAL_CLIENT_H

#include <QtWaylandClient/QWaylandClientExtension>

#include <LiriWaylandClient/liriwaylandclientglobal.h>

class LiriModalPrivate;

class LIRIWAYLANDCLIENT_EXPORT LiriModal
        : public QWaylandClientExtensionTemplate<LiriModal>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriModal)
    Q_PROPERTY(bool grabbed READ isGrabbed NOTIFY grabbedChanged)
public:
    LiriModal();
    ~LiriModal();

    bool isGrabbed() const;

    Q_INVOKABLE void grab();
    Q_INVOKABLE void close();

    void init(struct ::wl_registry *registry, int id, int version);

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void grabbedChanged();

private:
    LiriModalPrivate *const d_ptr = nullptr;
};


#endif // LIRI_LIRIMODAL_CLIENT_H
