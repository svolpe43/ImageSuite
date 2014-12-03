// Image_processer.hpp

#ifndef IMAGE_PROCESSOR_HPP
#define IMAGE_PROCESSOR_HPP

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <vector>
#include "wx/image.h"

enum {               // Added enumeration table for nonlinear filters
MEDIAN_FILTER = 400,
MINIMUM_FILTER = 401,
MAXIMUM_FILTER = 402
};

// helpers
void wxImage2grayBuffer(const wxImage* img, int* buffer);
wxImage* grayBuffer2wxImage(const int* buffer, int width, int height);
void wxImage2colorBuffer(const wxImage* img, int* buffer);
wxImage* colorBuffer2wxImage(const int* buffer, int width, int height);

// filters
wxImage* LowPass(wxImage *pImage, bool areaFilter, wxPoint *start, wxPoint *end);
wxImage* HighPass(wxImage *pImage, bool areaFilter, wxPoint *start, wxPoint *end);
wxImage* nonLinear(wxImage *pImage, int type, bool areaFilter, wxPoint *start, wxPoint *end);
wxImage* EdgeDet(wxImage *pImage, bool areaFilter, wxPoint *start, wxPoint *end);
wxImage* Binarize(wxImage *pImage, bool areaFilter, wxPoint *start, wxPoint *end);

bool inFilterArea(wxPoint needle, wxPoint start, wxPoint end);

// undo
wxImage* copy(wxImage *masterImage);

// transforms
wxImage* rotate(wxImage *pImage, bool right);
wxImage* scale(wxImage *pImage, float factor);
wxImage* mirror(wxImage *pImage);
wxImage* rotateHue(wxImage *pImage, bool right);
#endif
