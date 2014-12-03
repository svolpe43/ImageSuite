// The Image Processing Suite

// - area filtering
// - save file

// headers
#include "BME465_Template.hpp"

// resources
#include "resources/bin.xpm"
#include "resources/edge.xpm"
#include "resources/highpass.xpm"
#include "resources/lowpass.xpm"
#include "resources/max.xpm"
#include "resources/median.xpm"
#include "resources/min.xpm"
#include "resources/undo.xpm"
#include "wx/image.h"

// event tables and other macros for wxWindows
BEGIN_EVENT_TABLE(MyFrame, wxFrame)

	// file commands
    EVT_MENU(MENU_FILE_OPEN,  MyFrame::OnOpen)
    EVT_MENU(MENU_FILE_QUIT,  MyFrame::OnQuit)
    EVT_MENU(MENU_HELP_ABOUT, MyFrame::OnAbout)
	EVT_MENU(MENU_FILE_SAVE, MyFrame::OnSave)
    EVT_MENU(ID_ToGray, MyFrame::OnToGray)

	// editting commands
    EVT_PAINT(MyFrame::OnPaint)
    EVT_MENU(MENU_FILTER_LP, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_HP, MyFrame::OnFilter)
    EVT_MENU(MENU_FILTER_MEDIAN, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_MINIMUM, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_MAXIMUM, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_EDGE, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_BIN, MyFrame::OnFilter)
	
	//transform commands
	EVT_MENU(IMAGE_SCALE_UP, MyFrame::OnTransform)
	EVT_MENU(IMAGE_SCALE_DOWN, MyFrame::OnTransform)
	EVT_MENU(IMAGE_ROTATE_RIGHT, MyFrame::OnTransform)
	EVT_MENU(IMAGE_ROTATE_LEFT, MyFrame::OnTransform)
	EVT_MENU(IMAGE_MIRROR, MyFrame::OnTransform)
	EVT_MENU(IMAGE_ROTATE_HUE_LEFT, MyFrame::OnTransform)
	EVT_MENU(IMAGE_ROTATE_HUE_RIGHT, MyFrame::OnTransform)
	
	// area calculation
	EVT_MENU(ID_AreaCalculation, MyFrame::OnAreaCalculation)
	EVT_MENU(ID_AreaFilter, MyFrame::OnAreaFilter)
		
	EVT_LEFT_DOWN(MyFrame::OnLButton)
	EVT_MOTION(MyFrame::OnDrag)
	// EVT_LEFT_UP(MyFrame::OnDragRelease)
	
	EVT_MENU(MENU_FILTER_UNDO, MyFrame::OnFilter)
	END_EVENT_TABLE()

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame(_T("BME 465 Template App"), wxPoint(50, 50), wxSize(800, 600));
	
	// show frame
    frame->Show(TRUE);
    
	// enable all handlers
    ::wxInitAllImageHandlers(); 

	// false will exit the program immediately
    return TRUE;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------
// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
       : wxFrame(NULL, -1, title, pos, size, style)
{
    // set the frame icon
    SetIcon(wxICON(mondrian));

#if wxUSE_MENUS
    // create the menu items
    wxMenu *fileMenu = new wxMenu;
    wxMenu *imageMenu = new wxMenu;
	wxMenu *helpMenu = new wxMenu;
	
	// sub image menus
    wxMenu *filterMenu = new wxMenu;
	wxMenu *transformMenu = new wxMenu;
	
	// build file menu
    fileMenu->Append(MENU_FILE_OPEN, _T("&Open...\tCtrl-O"), _T("Open a new Image"));
	fileMenu->Append(MENU_FILE_SAVE, _T("&Save\tCtrl-S"), _T("Save the image"));
    fileMenu->Append(MENU_FILE_QUIT, _T("E&xit\tCtrl-X"), _T("Quit this program"));
    
    //build filter menu
    filterMenu->Append(MENU_FILTER_LP, _T("&Lowpass Filter\tAlt-Q"), _T("Lowpass Filter"));
	filterMenu->Append(MENU_FILTER_HP, _T("&Highpass Filter\tAlt-W"), _T("Highpass Filter"));
	filterMenu->Append(MENU_FILTER_MEDIAN, _T("&Median Filter\tAlt-E"), _T("Median Filter"));
	filterMenu->Append(MENU_FILTER_MINIMUM, _T("&Minimum Filter\tAlt-R"), _T("Minimum Filter"));
	filterMenu->Append(MENU_FILTER_MAXIMUM, _T("&Maximum Filter\tAlt-T"), _T("Maximum Filter"));
	filterMenu->Append(MENU_FILTER_EDGE, _T("&Edge Detecting Filter\tAlt-Y"), _T("Edge Detecting Filter"));
	filterMenu->Append(MENU_FILTER_BIN, _T("&Binarize Filter\tAlt-U"), _T("Binarize Filter"));
	filterMenu->Append (ID_AreaCalculation , _T ( "&Area Calculation \tAlt-I" ), _T ( "<- Apply area calculation "));
	filterMenu->Append (ID_AreaFilter , _T ( "&Area Filter \tAlt-O" ), _T ( "<- Apply area filter "));
	
	// build transform menu
	transformMenu->Append(IMAGE_SCALE_UP, _T("&Scale up\tCtrl-Q"), _T("Scale up an image."));
	transformMenu->Append(IMAGE_SCALE_DOWN, _T("&Scale down\tCtrl-W"), _T("Scale down an image."));
	transformMenu->Append(IMAGE_ROTATE_RIGHT, _T("&Rotate right\tCtrl-E"), _T("Rotate an image right."));
	transformMenu->Append(IMAGE_ROTATE_LEFT, _T("&Rotate left\tCtrl-R"), _T("Rotate an image left."));
	transformMenu->Append(IMAGE_MIRROR, _T("&Mirror image\tCtrl-T"), _T("Mirros an image."));
	transformMenu->Append(IMAGE_ROTATE_HUE_RIGHT, _T("&Rotate hue right\tCtrl-Y"), _T("Rotate hue of image right."));
	transformMenu->Append(IMAGE_ROTATE_HUE_LEFT, _T("&Rotate hue left\tCtrl-U"), _T("Rotate hue of image left."));

	// build image menu
	imageMenu->Append(MENU_FILTER,_T("Fil&ters\tF"), filterMenu, _T("Filter")),
	imageMenu->Append(MENU_IMAGE, _T("&Transform\tT"), transformMenu, _T("Transform"));
    
	// build help menu
    helpMenu->Append(MENU_HELP_ABOUT, _T("&About...\tF1"), _T("Show about dialog"));
    
    // build main menu
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(imageMenu, _T("&Image Process"));
    menuBar->Append(helpMenu, _T("&Help"));
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_TOOLBAR
	// create the toolbar
	// wxPoint* point = new wxPoint(1, 1);
	// wxSize* size = new wxSize(100, 100);
	// wxString* title = new wxString("Toolbar");
    // wxToolBar *MyToolBar = new wxToolBar(this, wxID_ANY, point, size, wxTB_VERTICAL, ("ToolBar"));
	wxToolBar *MyToolBar = new wxToolBar(this, wxID_ANY);

	// add tools to the tool bar
    MyToolBar->AddTool(MENU_FILTER_LP,lowpass_xpm, _T("LowPass Filter"));
	MyToolBar->AddTool(MENU_FILTER_HP,highpass_xpm, _T("HighPass Filter"));
	MyToolBar->AddTool(MENU_FILTER_MEDIAN,median_xpm, _T("Median Filter"));
	MyToolBar->AddTool(MENU_FILTER_MINIMUM,min_xpm, _T("Minimum Filter"));
	MyToolBar->AddTool(MENU_FILTER_MAXIMUM,max_xpm, _T("Maximum Filter"));
	MyToolBar->AddTool(MENU_FILTER_EDGE,edge_xpm, _T("Edge Detecting Filter"));
	MyToolBar->AddTool(MENU_FILTER_BIN,bin_xpm, _T("Binarize Filter"));
	MyToolBar->AddTool(MENU_FILTER_UNDO,	undo_xpm,	_T("Undo"));
    MyToolBar->Realize();
    SetToolBar(MyToolBar);
#endif

#if wxUSE_STATUSBAR
    // create a status bar
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to the image processing suite."));
#endif // wxUSE_STATUSBAR

	// initialize imgage var
    pImage = NULL;
	// initialize area vars
	pointNumber = 99;
	areaborder = new wxPoint[pointNumber];
	areaindex = 0;
	bAreaCalculation = FALSE;
	bleftDown = FALSE;
	SetStatusText ("Out of Area", 1 );
	dist = 9999;
	
	areaFilter = false;
	areaFilterStart = new wxPoint;
	areaFilterEnd = new wxPoint;
}

// quit - true is to force the frame to close
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

// displays the about dialog
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("Welcome to The Image Processing Suit\n")
                _T("Powered by %s"), wxVERSION_STRING);
    wxMessageBox(msg, _T("IPS"), wxOK | wxICON_INFORMATION,this);
}

// when image is opened
void MyFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{   
    wxString filePath;
    wxString fileName;
    
    wxFileDialog fileDialog(NULL, "Choose a file to load ...", "", "", "*.bmp;*.tif;*.gif;*.jpg", wxOPEN, wxDefaultPosition);
    if( fileDialog.ShowModal() == wxID_OK )
    {
		// get file info
        filePath = fileDialog.GetPath();
        fileName = fileDialog.GetFilename();
		
        // update the view of main frame
        if( pImage != NULL )
			delete pImage;
		
		// create the wx image 
		pImage = new wxImage(filePath);
        if( pImage == NULL )
            wxMessageBox("File Failed to Open!", _T("Error"), wxOK | wxICON_INFORMATION, this);        
        else
        {
			originalImage = pImage; 
			SetTitle(fileName);
			Refresh(); 
        }
    }
    fileDialog.Destroy();     
}

// save the image file
void MyFrame::OnSave(wxCommandEvent& event)
{
	return;
}

// make image grey scale
void MyFrame::OnToGray(wxCommandEvent& event)
{
	// check if image is loaded
    if( pImage == NULL )
    {
        wxMessageBox("Image is not loaded yet!", _T("Error"), wxOK | wxICON_INFORMATION, this);
        return;
    }  
    
	// update pImage
    int* buffer = new int[ pImage->GetWidth()*pImage->GetHeight() ];
    wxImage2grayBuffer(pImage,buffer);     
    
    wxImage* temp = grayBuffer2wxImage(buffer, pImage->GetWidth(),pImage->GetHeight() );
    delete pImage;
    pImage = temp;
    delete buffer;
    
    Refresh();
    return;    
}

// drawing the contents of the window
void MyFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
	int spacingW = 0;
	int spacingH = 0;
	
    if( pImage == NULL )
    {
        event.Skip();
    }
    else
    {
        wxBitmap tempBitmap(*pImage);
        //SetClientSize(tempBitmap.GetWidth() * 1.25, tempBitmap.GetHeight()*1.25 + 10 );
		//spacingW = ceilf((tempBitmap.GetWidth()*1.25 - tempBitmap.GetWidth())/2);
		//spacingH = ceilf((tempBitmap.GetHeight()*1.25 - tempBitmap.GetHeight())/2);
		SetClientSize(tempBitmap.GetWidth(), tempBitmap.GetHeight());
        dc.DrawBitmap(tempBitmap,(int)spacingW,(int)spacingH + 25, TRUE);
    }

	if ( bleftDown )
		pointNumber = areaindex ;
	// threshold range for closed rectangle
	else if(dist >= 0 && dist < 5){
		pointNumber = areaindex ;
		int idist = ( int )(floor(dist)) ;
		SetStatusText ( wxString::Format( "The distance is %d" , idist ) , 0 ) ;
	}
	// calculate the area
	if((areaindex > 0) && ( areaindex <= pointNumber )) //If in area calculation mode
	{
		// wxPoint pt ( event.GetLogicalPosition(dc));
		wxPoint* acborder_pt=new wxPoint [pointNumber]; // the points coord to be drawn
		for ( int i = 0 ; i< areaindex ; i++)
		{
			acborder_pt [i].x = dc.LogicalToDeviceX(areaborder[i].x);
			acborder_pt [i].y = dc.LogicalToDeviceY(areaborder[i].y);
		}
		dc.SetPen(*wxRED_PEN);
		dc.DrawLines(areaindex, acborder_pt);
		if ( areaindex == pointNumber )
		{
			dc.DrawLine(acborder_pt[pointNumber - 1].x, acborder_pt[pointNumber -1].y ,acborder_pt[0].x, acborder_pt[0].y);
		
			float farea = 0;
			int area;
			int minborder = 9999;
			for ( int i = 0; i < pointNumber; i++){
				if (areaborder[i].x < minborder)
					minborder = areaborder[i].x;
			}
			for (int j = 0; j < pointNumber -1; j++){
				farea = ((float )((areaborder[j].x - minborder) + (areaborder[j + 1].x - minborder)) / 2.0)
				* (areaborder[j + 1].y - areaborder[j].y) + farea;
			}
			farea = ((float)((areaborder[pointNumber - 1].x - minborder) + (areaborder[0].x - minborder)) / 2.0)
			* (areaborder[0].y - areaborder[pointNumber -1].y) + farea;
			
			if ( farea < 0) farea = -farea;
			area = (int)farea;
			SetStatusText( wxString::Format("The area is %d" , area ) ,1);
			areaindex = 0;
			bleftDown = !bleftDown;
			bRed = FALSE;
			pointNumber = 99;
			dist = 9999;
		}
		delete acborder_pt ;
	}
	
	if(areaFilter)
	{
		dc.SetPen(*wxRED_PEN);
		int width = areaFilterEnd->x - areaFilterStart->x;
		int height = areaFilterEnd->y - areaFilterStart->y;
		dc.DrawLine(areaFilterStart->x, areaFilterStart->y, areaFilterEnd->x, areaFilterStart->y);
		dc.DrawLine(areaFilterEnd->x, areaFilterStart->y, areaFilterEnd->x, areaFilterEnd->y);
		dc.DrawLine(areaFilterEnd->x, areaFilterEnd->y, areaFilterStart->x, areaFilterEnd->y);
		dc.DrawLine(areaFilterStart->x, areaFilterEnd->y, areaFilterStart->x, areaFilterStart->y);
	}
    return;    
}

// filter the image
void MyFrame::OnFilter( wxCommandEvent& event )
{
        if( pImage == NULL )
            wxMessageBox("Image is not loaded yet!", _T("Error"), wxOK | wxICON_INFORMATION,this);
        else 
        {
            wxImage *Filtered = NULL;
            switch(event.GetId())
            {
               case MENU_FILTER_LP: Filtered 		= 	LowPass(pImage, areaFilter, areaFilterStart, areaFilterEnd); break;
			   case MENU_FILTER_HP: Filtered 		= 	HighPass(pImage, areaFilter, areaFilterStart, areaFilterEnd); break;
		       case MENU_FILTER_MEDIAN: Filtered 	= 	nonLinear(pImage, MEDIAN_FILTER, areaFilter, areaFilterStart, areaFilterEnd); break;
			   case MENU_FILTER_MAXIMUM: Filtered 	= 	nonLinear(pImage, MAXIMUM_FILTER, areaFilter, areaFilterStart, areaFilterEnd); break;
		       case MENU_FILTER_MINIMUM: Filtered 	= 	nonLinear(pImage, MINIMUM_FILTER, areaFilter, areaFilterStart, areaFilterEnd); break;
			   case MENU_FILTER_EDGE: Filtered 		= 	EdgeDet(pImage, areaFilter, areaFilterStart, areaFilterEnd); break;
			   case MENU_FILTER_BIN: Filtered 		= 	Binarize(pImage, areaFilter, areaFilterStart, areaFilterEnd); break;
			   
			   case MENU_FILTER_UNDO: Filtered 		= 	copy(originalImage); break;
			}  
            pImage = Filtered;
         }
    Refresh();
    return;
}

// on transform
void MyFrame::OnTransform(wxCommandEvent& event)
{
	 if( pImage == NULL )
            wxMessageBox("Image is not loaded yet!", _T("Error"), wxOK | wxICON_INFORMATION,this);
        else 
        {
            wxImage *transformed = NULL;
            
            switch(event.GetId())
            {
				case IMAGE_SCALE_UP: transformed = scale(pImage, 1.1); break;
				case IMAGE_SCALE_DOWN: transformed = scale(pImage, .9); break;
				case IMAGE_ROTATE_RIGHT: transformed = rotate(pImage, true); break;
				case IMAGE_ROTATE_LEFT: transformed = rotate(pImage, false); break;
				case IMAGE_MIRROR: transformed = mirror(pImage); break;
				case IMAGE_ROTATE_HUE_RIGHT: transformed = rotateHue(pImage, true); break;
				case IMAGE_ROTATE_HUE_LEFT: transformed = rotateHue(pImage, false); break;				
			}
            pImage = transformed;
         }
    Refresh();
    return;
}

// puts us into area calculation or not
void MyFrame::OnAreaCalculation( wxCommandEvent& WXUNUSED (event))
{
	bAreaCalculation = !bAreaCalculation;
	if(bAreaCalculation)
		SetStatusText("Out of area calculation.", 1);
	else
		SetStatusText("In area calculation.", 1);
	Refresh();
	return;
}

// puts us into area filtering or not
void MyFrame::OnAreaFilter(wxCommandEvent& WXUNUSED(event))
{
	areaFilter = !areaFilter;
	if(areaFilter)
		SetStatusText("In area filtering.", 0);
	else
		SetStatusText("Out of area filtering.", 0);
	
	Refresh();
	return;
}


// on mouse click down
void MyFrame::OnLButton(wxMouseEvent& event)
{
	wxClientDC dc(this);
	wxPoint area_pt(event.GetLogicalPosition(dc));

	SetStatusText(wxString::Format("Last Point x %d, y %d", area_pt.x, area_pt.y ), 0 );
	
	if (pImage == NULL)
	{
		wxMessageBox("Image is not loaded yet!", _T("Error"), wxOK | wxICON_INFORMATION, this );
		return;
	}
	
	// check if we are in area calculation and null image
	if (bAreaCalculation){
		// calculate the distance
		areaborder[areaindex].x = area_pt.x;
		areaborder[areaindex].y = area_pt.y + 25;
		if ( areaindex > 0)
			dist = sqrt((pow((double)(area_pt.x - areaborder[0].x), 2)+pow((double)(area_pt.y + 27 - areaborder[0].y), 2)));
		SetStatusText(wxString::Format("This point x %d, y %d, distance %d", area_pt.x , area_pt.y, (int)dist), 1);
			
		// update vars
		areaindex++;
		Refresh();
	}
	
	if(areaFilter)
	{
		areaFilterStart->x = area_pt.x;
		areaFilterStart->y = area_pt.y;
		Refresh();
	}
}


void MyFrame::OnDrag(wxMouseEvent& event)
{
	if (!areaFilter || !event.LeftIsDown())
		return;
	
	wxClientDC dc(this);
	wxPoint area_pt(event.GetLogicalPosition(dc));
	
	SetStatusText(wxString::Format("Start point (%d, %d)", areaFilterStart->x, areaFilterStart->y ), 1 );
	
	// check if we are in area calculation and null image
	
	if (pImage == NULL)
	{
		wxMessageBox("Image is not loaded yet!", _T("Error"), wxOK | wxICON_INFORMATION, this );
		return;
	}
	
	SetStatusText(wxString::Format("Dragged to (%d, %d)", area_pt.x, area_pt.y ), 0 );
	
	areaFilterEnd->x = area_pt.x;
	areaFilterEnd->y = area_pt.y + 25;
	Refresh();
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

