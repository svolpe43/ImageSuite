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
MEDIAN_FILTER = 105,
MINIMUM_FILTER = 106,
MAXIMUM_FILTER = 107
};

void wxImage2grayBuffer(const wxImage* img, int* buffer);
wxImage* grayBuffer2wxImage(const int* buffer, int width, int height);
void wxImage2colorBuffer(const wxImage* img, int* buffer);
wxImage* colorBuffer2wxImage(const int* buffer, int width, int height);
wxImage* LowPass(wxImage *pImage);
wxImage* HighPass(wxImage *pImage);
wxImage* copy(wxImage *masterImage);
wxImage* nonLinear(wxImage *pImage, int type);
wxImage* EdgeDet(wxImage *pImage);
wxImage* Binarize(wxImage *pImage);

// transforms
wxImage* rotate(wxImage *pImage, bool right);
wxImage* scale(wxImage *pImage, float factor);
wxImage* mirror(wxImage *pImage);
wxImage* rotateHue(wxImage *pImage, bool right);
#endif
