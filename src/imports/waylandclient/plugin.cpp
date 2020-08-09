/****************************************************************************
 * This file is part of Liri.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPLv3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtQml>

#include <LiriWaylandClient/LiriColorPicker>
#include <LiriWaylandClient/LiriShell>
#include <LiriWaylandClient/WlrExportDmabufV1>
#include <LiriWaylandClient/WlrForeignToplevelManagementV1>
#include <LiriWaylandClient/WlrLayerShellV1>
#include <LiriWaylandClient/WlrOutputManagementV1>
#include <LiriWaylandClient/WlrScreencopyV1>

#include "lirishortcutqml.h"
#include "wlrlayersurfacev1qml.h"
#include "xdgshellqml.h"
#include "utils.h"

LIRI_DECLARE_CONTAINER_CLASS(WlrLayerShellV1)
LIRI_DECLARE_CONTAINER_CLASS(WlrLayerSurfaceV1Qml)
LIRI_DECLARE_CONTAINER_CLASS(XdgWmBase)
LIRI_DECLARE_CONTAINER_CLASS(XdgSurfaceQml)
LIRI_DECLARE_CONTAINER_CLASS(XdgPopupQml)

class WaylandClientPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void registerTypes(const char *uri)
    {
        // @uri Liri.WaylandClient
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Liri.WaylandClient"));

        const int versionMajor = 1;
        const int versionMinor = 0;

        qmlRegisterType<LiriColorPickerManager>(uri, versionMajor, versionMinor, "LiriColorPickerManager");
        qmlRegisterType<LiriShell>(uri, versionMajor, versionMinor, "LiriShell");
        qmlRegisterType<LiriShortcutQml>(uri, versionMajor, versionMinor, "LiriShortcut");
        qmlRegisterType<LiriOsd>(uri, versionMajor, versionMinor, "LiriOsd");

        qmlRegisterType<WlrExportDmabufManagerV1>(uri, versionMajor, versionMinor, "WlrExportDmabufManagerV1");
        qmlRegisterUncreatableType<WlrExportDmabufFrameV1>(uri, versionMajor, versionMinor, "WlrExportDmabufFrameV1",
                                                           QStringLiteral("Cannot create a WlrExportDmabufFrameV1 instance"));

        qmlRegisterType<WlrLayerShellV1Container>(uri, versionMajor, versionMinor, "WlrLayerShellV1");
        qmlRegisterType<WlrLayerSurfaceV1QmlContainer>(uri, versionMajor, versionMinor, "WlrLayerSurfaceV1");

        qmlRegisterType<WlrOutputManagerV1>(uri, versionMajor, versionMinor, "WlrOutputManagerV1");
        qmlRegisterUncreatableType<WlrOutputHeadV1>(uri, versionMajor, versionMinor, "WlrOutputHeadV1",
                                                    QStringLiteral("Cannot create a WlrOutputHeadV1 instance"));
        qmlRegisterUncreatableType<WlrOutputModeV1>(uri, versionMajor, versionMinor, "WlrOutputModeV1",
                                                    QStringLiteral("Cannot create a WlrOutputModeV1 instance"));
        qmlRegisterUncreatableType<WlrOutputConfigurationV1>(uri, versionMajor, versionMinor, "WlrOutputConfigurationV1",
                                                             QStringLiteral("Cannot create a WlrOutputConfigurationV1 instance"));
        qmlRegisterUncreatableType<WlrOutputConfigurationHeadV1>(uri, versionMajor, versionMinor, "WlrOutputConfigurationHeadV1",
                                                                 QStringLiteral("Cannot create a WlrOutputConfigurationHeadV1 instance"));

        qmlRegisterType<WlrScreencopyManagerV1>(uri, versionMajor, versionMinor, "WlrScreencopyManagerV1");
        qmlRegisterUncreatableType<WlrScreencopyFrameV1>(uri, versionMajor, versionMinor, "WlrScreencopyFrameV1",
                                                         QStringLiteral("Cannot create a WlrScreencopyFrameV1 instance"));

        qmlRegisterType<XdgWmBaseContainer>(uri, versionMajor, versionMinor, "XdgWmBase");
        qmlRegisterType<XdgSurface>();
        qmlRegisterType<XdgSurfaceQmlContainer>(uri, versionMajor, versionMinor, "XdgSurface");
        qmlRegisterType<XdgPopup>();
        qmlRegisterType<XdgPopupQmlContainer>(uri, versionMajor, versionMinor, "XdgPopup");
    }
};

#include "plugin.moc"
