// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef LIRI_VIEWPORTER_CLIENT_H
#define LIRI_VIEWPORTER_CLIENT_H

#include <QObject>

QT_FORWARD_DECLARE_CLASS(QWindow)

#include <LiriWaylandClient/liriwaylandclientglobal.h>

class ViewportPrivate;

class LIRIWAYLANDCLIENT_EXPORT Viewport : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Viewport)
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged)
public:
    explicit Viewport(QObject *parent = nullptr);
    ~Viewport();

    bool isActive() const;

    QWindow *window() const;
    void setWindow(QWindow *window);

public Q_SLOTS:
    void initialize();

Q_SIGNALS:
    void activeChanged();
    void windowChanged();

private:
    ViewportPrivate *const d_ptr = nullptr;;
};

#endif // LIRI_VIEWPORTER_CLIENT_H
