// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef LIRI_VIEWPORTER_P_CLIENT_H
#define LIRI_VIEWPORTER_P_CLIENT_H

#include <QPointer>
#include <QWaylandClientExtension>
#include <QWindow>

#include <LiriWaylandClient/Viewporter>
#include <LiriWaylandClient/private/qwayland-viewporter.h>

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

class LIRIWAYLANDCLIENT_EXPORT ViewporterInterface
        : public QWaylandClientExtensionTemplate<ViewporterInterface>
        , public QtWayland::wp_viewporter
{
    Q_OBJECT
public:
    ViewporterInterface();
};

class LIRIWAYLANDCLIENT_EXPORT ViewportInterface
        : public QtWayland::wp_viewport
{
public:
    ViewportInterface() = default;
};

class LIRIWAYLANDCLIENT_EXPORT ViewportPrivate
{
public:
    ViewportPrivate() = default;
    ~ViewportPrivate();

    bool isInitialized = false;
    ViewporterInterface *viewporter = nullptr;
    ViewportInterface *viewport = nullptr;
    QPointer<QWindow> window;
};

#endif // LIRI_VIEWPORTER_P_CLIENT_H
