//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 Eran Ifrah
// file name            : theme_handler.cpp
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "theme_handler.h"
#include "clSystemSettings.h"
#include "cl_aui_tb_are.h"
#include "drawingutils.h"
#include "editor_config.h"
#include "event_notifier.h"
#include "frame.h"
#include "globals.h"
#include "workspace_pane.h"
#include <algorithm>
#include <queue>
#include <wx/aui/framemanager.h>
#include <wx/image.h>
#include <wx/listbox.h>
#include <wx/listctrl.h>

#ifdef __WXMAC__
#include <wx/srchctrl.h>
#endif

#define CHECK_POINTER(p) \
    if(!p)               \
        return;

ThemeHandler::ThemeHandler()
{
    EventNotifier::Get()->Bind(wxEVT_INIT_DONE, &ThemeHandler::OnInitDone, this);
    EventNotifier::Get()->Bind(wxEVT_CMD_COLOURS_FONTS_UPDATED, &ThemeHandler::OnColoursChanged, this);
}

ThemeHandler::~ThemeHandler()
{
    EventNotifier::Get()->Unbind(wxEVT_INIT_DONE, &ThemeHandler::OnInitDone, this);
    EventNotifier::Get()->Unbind(wxEVT_CMD_COLOURS_FONTS_UPDATED, &ThemeHandler::OnColoursChanged, this);
}

void ThemeHandler::OnInitDone(wxCommandEvent& e)
{
    e.Skip();
    // Fire "wxEVT_EDITOR_SETTINGS_CHANGED" to ensure that the notebook appearance is in sync with the settings
    PostCmdEvent(wxEVT_EDITOR_SETTINGS_CHANGED);
}

void ThemeHandler::OnColoursChanged(clCommandEvent& e)
{
    e.Skip();
    // We do the actual update in the next iteration to ensure that the all new colours are updated
    // in the clSystemSettings class
    CallAfter(&ThemeHandler::UpdateColours);
}

void ThemeHandler::UpdateColours() {}
