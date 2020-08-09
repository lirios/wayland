// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "lirishortcutqml.h"

LiriShortcutQml::LiriShortcutQml()
    : LiriShortcut()
{
}

void LiriShortcutQml::componentComplete()
{
    QMetaObject::invokeMethod(this, "bindShortcut", Qt::QueuedConnection);
}
