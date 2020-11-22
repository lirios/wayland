find_package(QtWaylandScanner REQUIRED)

ecm_add_qtwayland_client_protocol(SOURCES
    PROTOCOL "${WaylandProtocols_DATADIR}/stable/xdg-shell/xdg-shell.xml"
    BASENAME "xdg-shell")
ecm_add_qtwayland_client_protocol(SOURCES
    PROTOCOL "${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/liri-color-picker.xml"
    BASENAME "liri-color-picker")
ecm_add_qtwayland_client_protocol(SOURCES
    PROTOCOL "${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/liri-shell.xml"
    BASENAME "liri-shell")
ecm_add_qtwayland_client_protocol(SOURCES
    PROTOCOL "${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-export-dmabuf-unstable-v1.xml"
    BASENAME "wlr-export-dmabuf-unstable-v1")
ecm_add_qtwayland_client_protocol(SOURCES
    PROTOCOL "${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-foreign-toplevel-management-unstable-v1.xml"
    BASENAME "wlr-foreign-toplevel-management-unstable-v1")
ecm_add_qtwayland_client_protocol(SOURCES
    PROTOCOL "${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-layer-shell-unstable-v1.xml"
    BASENAME "wlr-layer-shell-unstable-v1")
ecm_add_qtwayland_client_protocol(SOURCES
    PROTOCOL "${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-output-management-unstable-v1.xml"
    BASENAME "wlr-output-management-unstable-v1")
ecm_add_qtwayland_client_protocol(SOURCES
    PROTOCOL "${CMAKE_CURRENT_SOURCE_DIR}/../../data/protocols/wlr-screencopy-unstable-v1.xml"
    BASENAME "wlr-screencopy-unstable-v1")

set(_generated_files
    "${CMAKE_CURRENT_BINARY_DIR}/wayland-liri-color-picker-client-protocol.h"
    "${CMAKE_CURRENT_BINARY_DIR}/wayland-liri-shell-client-protocol.h"
    "${CMAKE_CURRENT_BINARY_DIR}/wayland-wlr-export-dmabuf-unstable-v1-client-protocol.h"
    "${CMAKE_CURRENT_BINARY_DIR}/wayland-wlr-layer-shell-unstable-v1-client-protocol.h"
    "${CMAKE_CURRENT_BINARY_DIR}/wayland-wlr-output-management-unstable-v1-client-protocol.h"
    "${CMAKE_CURRENT_BINARY_DIR}/wayland-wlr-screencopy-unstable-v1-client-protocol.h"
    "${CMAKE_CURRENT_BINARY_DIR}/wayland-xdg-shell-client-protocol.h"
)
set_source_files_properties(${_generated_files} PROPERTIES SKIP_AUTOMOC ON)

liri_add_module(WaylandClient
    DESCRIPTION
        "Wayland client extensions"
    SOURCES
        liricolorpicker.cpp
        liricolorpicker.h
        liricolorpicker_p.h
        lirimodal.cpp
        lirimodal.h
        lirimodal_p.h
        lirishell.cpp
        lirishell.h
        lirishell_p.h
        logging.cpp
        logging_p.h
        utils_p.h
        wlrexportdmabufv1.cpp
        wlrexportdmabufv1.h
        wlrexportdmabufv1_p.h
        wlrforeigntoplevelmanagementv1.cpp
        wlrforeigntoplevelmanagementv1.h
        wlrforeigntoplevelmanagementv1_p.h
        wlrlayershellv1.cpp
        wlrlayershellv1.h
        wlrlayershellv1_p.h
        wlroutputmanagementv1.cpp
        wlroutputmanagementv1.h
        wlroutputmanagementv1_p.h
        wlrscreencopyv1.cpp
        wlrscreencopyv1.h
        wlrscreencopyv1_p.h
        xdgshell.cpp
        xdgshell.h
        xdgshell_p.h
        ${SOURCES}
    FORWARDING_HEADERS
        LiriColorPicker
        LiriModal
        LiriShell
        WlrExportDmabufV1
        WlrForeignToplevelManagementV1
        WlrLayerShellV1
        WlrOutputManagementV1
        WlrScreencopyV1
        XdgShell
    PRIVATE_HEADERS
        liricolorpicker_p.h
        lirimodal_p.h
        lirishell_p.h
        wlrexportdmabufv1_p.h
        wlrforeigntoplevelmanagementv1_p.h
        wlrlayershellv1_p.h
        wlroutputmanagementv1_p.h
        wlrscreencopyv1_p.h
        xdgshell_p.h
        "${CMAKE_CURRENT_BINARY_DIR}/wayland-liri-color-picker-client-protocol.h"
        "${CMAKE_CURRENT_BINARY_DIR}/qwayland-liri-color-picker.h"
        "${CMAKE_CURRENT_BINARY_DIR}/qwayland-liri-shell.h"
        "${CMAKE_CURRENT_BINARY_DIR}/qwayland-wlr-export-dmabuf-unstable-v1.h"
        "${CMAKE_CURRENT_BINARY_DIR}/qwayland-wlr-foreign-toplevel-management-unstable-v1.h"
        "${CMAKE_CURRENT_BINARY_DIR}/qwayland-wlr-layer-shell-unstable-v1.h"
        "${CMAKE_CURRENT_BINARY_DIR}/qwayland-wlr-screencopy-unstable-v1.h"
        "${CMAKE_CURRENT_BINARY_DIR}/qwayland-xdg-shell.h"
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
    PUBLIC_LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Qml
        Qt5::WaylandClient
        Wayland::Client
    LIBRARIES
        Qt5::GuiPrivate
    PKGCONFIG_DEPENDENCIES
        Qt5Core
        Qt5Gui
        Qt5Qml
        Qt5WaylandClient
        wayland-client
)
