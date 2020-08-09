// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef LIRI_LIRISHORTCUTQML_H
#define LIRI_LIRISHORTCUTQML_H

#include <QQmlParserStatus>

#include <LiriWaylandClient/LiriShell>

class LiriShortcutQml : public LiriShortcut, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    LiriShortcutQml();

protected:
    void classBegin() override {}
    void componentComplete() override;
};

#endif // LIRI_LIRISHORTCUTQML_H
