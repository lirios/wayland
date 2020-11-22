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
#include <QWaylandQuickExtension>

#include <LiriWaylandServer/GtkShell>
#include <LiriWaylandServer/KdeServerDecoration>
#include <LiriWaylandServer/WaylandLiriColorPicker>
#include <LiriWaylandServer/LiriDecoration>
#include <LiriWaylandServer/WaylandLiriModal>
#include <LiriWaylandServer/WaylandLiriShell>
#include <LiriWaylandServer/WaylandWlrExportDmabufV1>
#include <LiriWaylandServer/WaylandWlrForeignToplevelManagementV1>
#include <LiriWaylandServer/WaylandWlrLayerShellV1>
#include <LiriWaylandServer/WaylandWlrScreencopyV1>

#include "waylandwlrforeigntoplevelmanagementv1qml.h"
#include "waylandwlroutputmanagementv1qml.h"

Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(GtkShell)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(KdeServerDecorationManager)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandLiriColorPickerManager)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(LiriDecorationManager)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandLiriModalManager)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandLiriShell)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandLiriOsd)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandWlrExportDmabufManagerV1)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandWlrForeignToplevelManagerV1)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandWlrLayerShellV1)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandWlrOutputManagerV1)
Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(WaylandWlrScreencopyManagerV1)

class WaylandServerPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void registerTypes(const char *uri)
    {
        // @uri Liri.WaylandServer
        Q_ASSERT(strcmp(uri, "Liri.WaylandServer") == 0);

        const int versionMajor = 1;
        const int versionMinor = 0;

        qmlRegisterType<GtkShellQuickExtension>(uri, versionMajor, versionMinor, "GtkShell");
        qmlRegisterType<GtkSurface>(uri, versionMajor, versionMinor, "GtkSurface");

        qmlRegisterType<KdeServerDecorationManagerQuickExtension>(uri, versionMajor, versionMinor, "KdeServerDecorationManager");
        qmlRegisterUncreatableType<KdeServerDecoration>(uri, versionMajor, versionMinor, "KdeServerDecoration",
                                                        QStringLiteral("Cannot create instance of KdeServerDecoration"));

        qmlRegisterType<WaylandLiriColorPickerManagerQuickExtension>(uri, versionMajor, versionMinor, "LiriColorPickerManager");

        qmlRegisterType<LiriDecorationManagerQuickExtension>(uri, versionMajor, versionMinor, "LiriDecorationManager");
        qmlRegisterUncreatableType<LiriDecoration>(uri, versionMajor, versionMinor, "LiriDecoration",
                                                   QStringLiteral("Cannot create instance of LiriDecoration"));

        qmlRegisterType<WaylandLiriModalManagerQuickExtension>(uri, versionMajor, versionMinor, "LiriModalManager");

        qmlRegisterType<WaylandLiriShellQuickExtension>(uri, versionMajor, versionMinor, "LiriShell");
        qmlRegisterUncreatableType<WaylandLiriShortcut>(uri, versionMajor, versionMinor, "LiriShortcut",
                                                        QStringLiteral("Cannot create instance of LiriShortcut"));
        qmlRegisterType<WaylandLiriOsdQuickExtension>(uri, versionMajor, versionMinor, "LiriOsd");

        qmlRegisterType<WaylandWlrExportDmabufManagerV1QuickExtension>(uri, versionMajor, versionMinor, "WlrExportDmabufManagerV1");
        qmlRegisterUncreatableType<WaylandWlrExportDmabufFrameV1>(uri, versionMajor, versionMinor, "WlrExportDmabufFrameV1",
                                                                  QStringLiteral("Cannot create instance of WlrExportDmabufFrameV1"));

        qmlRegisterType<WaylandWlrForeignToplevelManagerV1QuickExtension>(uri, versionMajor, versionMinor, "WlrForeignToplevelManagerV1");
        qmlRegisterType<WaylandWlrForeignToplevelHandleV1Qml>(uri, versionMajor, versionMinor, "WlrForeignToplevelHandleV1");

        qmlRegisterType<WaylandWlrLayerShellV1QuickExtension>(uri, versionMajor, versionMinor, "WlrLayerShellV1");
        qmlRegisterUncreatableType<WaylandWlrLayerSurfaceV1>(uri, versionMajor, versionMinor, "WlrLayerSurfaceV1",
                                                             QStringLiteral("Cannot create instance of WlrLayerSurfaceV1"));

        qmlRegisterType<WaylandWlrOutputManagerV1QuickExtension>(uri, versionMajor, versionMinor, "WlrOutputManagerV1");
        qmlRegisterType<WaylandWlrOutputHeadV1Qml>(uri, versionMajor, versionMinor, "WlrOutputHeadV1");
        qmlRegisterType<WaylandWlrOutputModeV1>(uri, versionMajor, versionMinor, "WlrOutputModeV1");
        qmlRegisterType<WaylandWlrOutputManagerV1QuickExtension>(uri, versionMajor, versionMinor, "WlrOutputManagerV1");
        qmlRegisterType<WaylandWlrOutputConfigurationV1Qml>(uri, versionMajor, versionMinor, "WlrOutputConfigurationV1");
        qmlRegisterUncreatableType<WaylandWlrOutputConfigurationHeadV1>(uri, versionMajor, versionMinor, "WlrOutputConfigurationHeadV1",
                                                                        QStringLiteral("Cannot create instance of WlrOutputConfigurationHeadV1"));

        qmlRegisterType<WaylandWlrScreencopyManagerV1QuickExtension>(uri, versionMajor, versionMinor, "WlrScreencopyManagerV1");
        qmlRegisterUncreatableType<WaylandWlrScreencopyFrameV1>(uri, versionMajor, versionMinor, "WlrScreencopyFrameV1",
                                                                QStringLiteral("Cannot create instance of WlrScreencopyFrameV1"));
    }
};

#include "plugin.moc"
