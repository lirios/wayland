// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "viewportqml.h"

ViewportQml::ViewportQml(QObject *parent)
    : Viewport(parent)
{
}

void ViewportQml::componentComplete()
{
    //QMetaObject::invokeMethod(this, "initialize", Qt::QueuedConnection);
}
