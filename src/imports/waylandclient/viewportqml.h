// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef VIEWPORTQML_H
#define VIEWPORTQML_H

#include <QQmlParserStatus>

#include <LiriWaylandClient/Viewporter>

class ViewportQml : public Viewport, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    explicit ViewportQml(QObject *parent = nullptr);

protected:
    void classBegin() override {}
    void componentComplete() override;
};

#endif // VIEWPORTQML_H
