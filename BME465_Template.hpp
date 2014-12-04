#ifndef __BME465_TEMPLATE_HPP__
#define __BME465_TEMPLATE_HPP__
// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifdef __BORLANDC__
    #pragma hdrstop
#endif


// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/slider.h"
#include "wx/toolbar.h"
#include "wx/utils.h"
#include "wx/image.h"
#include "wx/filedlg.h"
#include "wx/pen.h"
#include "math.h"
#include "image_processor.hpp"
#include <cstdio>
#include <vector>
#include <algorithm>

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
	public:
		// called on startup
		virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
	public:
		// ctor(s)
		MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);
	
		// menu protos
		void OnOpen(wxCommandEvent& WXUNUSED(event));
		void OnSave(wxCommandEvent& event);
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		
		// image protos
		void OnFilter( wxCommandEvent& event );
		void OnPaint( wxPaintEvent& event);
		void OnTransform(wxCommandEvent& event);
		void OnToGray(wxCommandEvent& event);
	
		// image pointers
		wxImage *originalImage;
		wxImage *pImage;
		
		// any class wishing to process wxWindows events must use this macro
		DECLARE_EVENT_TABLE()
		
		// area prototypes
		void OnAreaCalculation(wxCommandEvent& event);
		void OnAreaFilter(wxCommandEvent& event);
		void OnLButton(wxMouseEvent& event);
		void OnDrag(wxMouseEvent& event);
		
		// area vars
		int areaindex ;
		wxPoint* areaborder ;
		int pointNumber ;
		double dist ;
		bool bAreaCalculation ;
		bool bleftDown ;
		bool bRed ;
		
		// area filter vars
		bool areaFilter;
		wxPoint* areaFilterStart;
		wxPoint* areaFilterEnd;
		
		int static const toolheight = 50;
};

// constants
enum
{
	// menu items
	MENU_FILE_OPEN = wxID_OPEN,
	MENU_FILE_SAVE = wxID_SAVE,
	MENU_FILE_QUIT = wxID_EXIT,
	
	// filter menu
	MENU_FILTER    = 100,
	MENU_FILTER_LP = 101,
	MENU_FILTER_HP = 102,
	MENU_FILTER_MEDIAN   = 105,
	MENU_FILTER_MINIMUM  = 106,
	MENU_FILTER_MAXIMUM  = 107,
	MENU_FILTER_EDGE     = 108,
	MENU_FILTER_BIN      = 109,
	MENU_FILTER_UNDO	 = 110,
	
	// transform menu
	MENU_IMAGE 				= 200,
	IMAGE_SCALE_UP 			= 201,
	IMAGE_SCALE_DOWN 		= 202,
	IMAGE_ROTATE_RIGHT 		= 203,
	IMAGE_ROTATE_LEFT 		= 204,
	IMAGE_MIRROR			= 205,
	IMAGE_ROTATE_HUE_RIGHT 	= 206,
	IMAGE_ROTATE_HUE_LEFT 	= 207,

	ID_ToGray = 300,
	ID_AreaCalculation = 301,
	ID_AreaFilter = 302,

	// about - special mac case "Apple Menu"
	MENU_HELP_ABOUT = wxID_ABOUT
};

#endif
