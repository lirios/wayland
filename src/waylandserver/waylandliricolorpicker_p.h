// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef LIRI_WAYLANDLIRICOLORPICKER_P_H
#define LIRI_WAYLANDLIRICOLORPICKER_P_H

#include <QPointer>
#include <QWaylandOutput>
#include <QWaylandSeat>

#include <LiriWaylandServer/WaylandLiriColorPicker>
#include <LiriWaylandServer/private/qwayland-server-liri-color-picker.h>

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

class WaylandLiriColorPickerEventFilter;

class LIRIWAYLANDSERVER_EXPORT WaylandLiriColorPicker
        : public QObject
        , public QtWaylandServer::liri_color_picker
{
    Q_OBJECT
public:
    explicit WaylandLiriColorPicker(QObject *parent = nullptr);

    WaylandLiriColorPickerManager *manager = nullptr;
    QWaylandOutput *output = nullptr;
    QPointer<WaylandLiriColorPickerEventFilter> filter;

protected:
    void liri_color_picker_bind_resource(Resource *resource) override;
    void liri_color_picker_destroy_resource(Resource *resource) override;
    void liri_color_picker_destroy(Resource *resource) override;
};

class LIRIWAYLANDSERVER_EXPORT WaylandLiriColorPickerEventFilter
        : public QObject
{
    Q_OBJECT
public:
    explicit WaylandLiriColorPickerEventFilter(WaylandLiriColorPicker *picker,
                                               QWaylandSeat *seat,
                                               QObject *parent = nullptr);

private:
    WaylandLiriColorPicker *m_picker = nullptr;
    QWaylandSeat *m_seat = nullptr;
    QColor m_color;

protected:
    bool eventFilter(QObject *receiver, QEvent *event) override;
};

class LIRIWAYLANDSERVER_EXPORT WaylandLiriColorPickerManagerPrivate
        : public QtWaylandServer::liri_color_picker_manager
{
    Q_DECLARE_PUBLIC(WaylandLiriColorPickerManager)
public:
    explicit WaylandLiriColorPickerManagerPrivate(WaylandLiriColorPickerManager *self);

    static WaylandLiriColorPickerManagerPrivate *get(WaylandLiriColorPickerManager *self) { return self ? self->d_func() : nullptr; }

    QString layerName;
    QVector<WaylandLiriColorPicker *> pickers;

protected:
    WaylandLiriColorPickerManager *q_ptr = nullptr;

    void liri_color_picker_manager_pick_at_location(
            Resource *resource,
            uint32_t id,
            struct ::wl_resource *output_res,
            uint32_t x, uint32_t y) override;
    void liri_color_picker_manager_pick_interactively(
            Resource *resource,
            uint32_t id,
            struct ::wl_resource *seat_res) override;
};

#endif // LIRI_WAYLANDLIRICOLORPICKER_P_H
