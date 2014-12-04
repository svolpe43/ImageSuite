// This file provides the basic routines for image processing

#include "image_processor.hpp"
#include "BME465_Template.hpp"
#include <vector> //FOR MEDIAN FILTER
#include <algorithm> //FOR SORT()

// low pass filter
wxImage * LowPass(wxImage *pImage, bool areaFilter, wxPoint *start, wxPoint *end)
{
    int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;	
    int* pResult;
    
    pTemp=new int[width*height];
    pResult=new int[width*height];	
    wxImage2grayBuffer(pImage,pTemp);	
    
    for(x=0;x<width;x++)
    {
    	for(y=0;y<height;y++)
    	{
            if(x != 0 && y != 0 && x != (width -1) && y != (height -1))
            {
    		    unsigned long index;
        		index=(unsigned long)y*width+x;
        		double value=1.0/9.0*
        			( float(pTemp[index-width-1])+float(pTemp[index-width])+float(pTemp[index-width+1])
        			 +float(pTemp[index-1])+float(pTemp[index])+float(pTemp[index+1])
        			 +float(pTemp[index+width-1])+float(pTemp[index+width])+float(pTemp[index+width+1])
        			);
					
				// handle the filtered area
				if(areaFilter)
					if(inFilterArea(wxPoint(x, y), *start, *end))
						pResult[(y)*width+(x)]=(int)(value);
					else
						pResult[y*width+x]=pTemp[y*width+x];
				else
					pResult[(y)*width+(x)]=(int)(value);
					
			}
   		    else
   		    {
                pResult[y*width+x]=pTemp[y*width+x];
            }
    	}
    }
    
    wxImage* temp;
    temp = grayBuffer2wxImage(pResult, width, height);
    delete pResult;
    return temp;
}

// high pass filter
wxImage * HighPass(wxImage *pImage, bool areaFilter, wxPoint *start, wxPoint *end)
{
    int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;	
    int* pResult;
    
    pTemp=new int[width*height];
    pResult=new int[width*height];	
    wxImage2grayBuffer(pImage,pTemp);	
    
    for(x=0;x<width;x++)
    {
    	for(y=0;y<height;y++)
    	{
            if(x != 0 && y != 0 && x != (width -1) && y != (height -1))
            {
    		    unsigned long index;
        		index=(unsigned long)y*width+x;
        		double value=1.0/9.0*
        			( 0*float(pTemp[index-width-1])+float(pTemp[index-width])+0*float(pTemp[index-width+1])
        			 +float(pTemp[index-1])-4*float(pTemp[index])+float(pTemp[index+1])
        			 +0*float(pTemp[index+width-1])+float(pTemp[index+width])+0*float(pTemp[index+width+1])
        			);
					
				// handle the filtered area
				if(areaFilter)
					if(inFilterArea(wxPoint(x, y), *start, *end))
						pResult[(y)*width+(x)]=abs(pTemp[y*width+x]-(int)(value));
					else
						pResult[y*width+x]=pTemp[y*width+x];
				else
					pResult[(y)*width+(x)]=abs(pTemp[y*width+x]-(int)(value));
   		    }
   		    else
   		    {
                pResult[y*width+x]=pTemp[y*width+x];
            }
    	}
    }
    
    wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}

// edge detection
wxImage * EdgeDet(wxImage *pImage, bool areaFilter, wxPoint *start, wxPoint *end)
{
    int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;	
    int* pResult;
    
    pTemp=new int[width*height];
    pResult=new int[width*height];	
    wxImage2grayBuffer(pImage,pTemp);	
    
    for(x=0;x<width;x++)
    {
    	for(y=0;y<height;y++)
    	{
            if(x != 0 && y != 0 && x != (width -1) && y != (height -1))
            {
    		    unsigned long index;
        		index=(unsigned long)y*width+x;
        		double value=
					(abs(pTemp[index-width-1]*(-1)+pTemp[index-width+1]+
					pTemp[index-1]*(-2)+pTemp[index
					+1]*2+pTemp[index+width-1]*(-1)+pTemp[index+width+1])+abs(
					pTemp[index-width-1]*(-1)+pTemp[index-width]*(-2)+
					pTemp[index-width+1]*(-1)+pTemp[index+width-1]+pTemp[index+width]*2+pTemp[index+
					width+1]) 
					);
					
					if(areaFilter){
						if(inFilterArea(wxPoint(x, y), *start, *end)){
							if(value<0)
								value=0;
							if(value>255)
								value=64;
							pResult[y*width+x]=(int)value;
						}else
							pResult[y*width+x]=pTemp[y*width+x];
					}else{
						if(value<0)
							value=0;
						if(value>255)
							value=64;
						pResult[y*width+x]=(int)value;
					}
   		    }
   		    else
   		    {
                pResult[y*width+x]=pTemp[y*width+x];
            }
    	}
    }
    
    wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}

// 255 or 0 pixels
wxImage * Binarize(wxImage *pImage, bool areaFilter, wxPoint *start, wxPoint *end)
{
    int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;	
    int* pResult;
    
    pTemp=new int[width*height];
    pResult=new int[width*height];	
    wxImage2grayBuffer(pImage,pTemp);	
    
    for(x=0;x<width;x++)
    {
    	for(y=0;y<height;y++)
    	{
            if(x != 0 && y != 0 && x != (width -1) && y != (height -1))
            {
    		    unsigned long index;
        		index=(unsigned long)y*width+x;
        		double value=
					(abs(pTemp[index-width-1]*(-1)+pTemp[index-width+1]+
					pTemp[index-1]*(-2)+pTemp[index
					+1]*2+pTemp[index+width-1]*(-1)+pTemp[index+width+1])+abs(
					pTemp[index-width-1]*(-1)+pTemp[index-width]*(-2)+
					pTemp[index-width+1]*(-1)+pTemp[index+width-1]+pTemp[index+width]*2+pTemp[index+
					width+1]) 
					);
					
					if(areaFilter){
						if(inFilterArea(wxPoint(x, y), *start, *end)){
							if(value<127)
								value=0;
							if(value>127)
								value=255;
							pResult[y*width+x]=(int)value;
						}else
							pResult[y*width+x]=pTemp[y*width+x];
					}else{
						if(value<127)
							value=0;
						if(value>127)
							value=255;
						pResult[y*width+x]=(int)value;
					}
   		    }
   		    else
   		    {
                pResult[y*width+x]=pTemp[y*width+x];
            }
    	}
    }
    
    wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}

// 3 non-linear filters
wxImage * nonLinear(wxImage *pImage, int type, bool areaFilter, wxPoint *start, wxPoint *end)
{
    int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;	
    int* pResult;
    
    pTemp=new int[width*height];
    pResult=new int[width*height];	
    wxImage2grayBuffer(pImage,pTemp);	
    
    std::vector<int> valArray ( 9 ) ;
double value ;
for ( x = 0 ; x < width ; x++) {
  for ( y = 0 ; y < height ; y++) {
      unsigned long index ;
           index = ( unsigned long ) ( y * width + x ) ; // Part of code that sorts values of 3x3 mask
           if ( y!=0 && x!=0 && x!= ( width -1) && y!=( height-1) ) {
           valArray [ 0 ] = pTemp [ index - width - 1 ] ;
           valArray [ 1 ] = pTemp [ index - width ] ;
           valArray [ 2 ] = pTemp [ index - width + 1 ] ;
           valArray [ 3 ] = pTemp [ index - 1 ] ;
           valArray [ 4 ] = pTemp [ index ] ;
           valArray [ 5 ] = pTemp [ index + 1 ] ;
           valArray [ 6 ] = pTemp [ index + width - 1 ] ;
           valArray [ 7 ] = pTemp [ index + width ] ;
           valArray [ 8 ] = pTemp [ index + width + 1 ] ;
           sort ( valArray . begin ( ) , valArray . end ( ) ) ;
			switch ( type ) {
				case MEDIAN_FILTER : value = valArray [ 4 ] ; break ; // Part of code that chooses pixel
				case MINIMUM_FILTER : value = valArray [ 0 ] ; break ;
				case MAXIMUM_FILTER : value = valArray [ 8 ] ; break ;
			}
			
			if(areaFilter){
				if(inFilterArea(wxPoint(x, y), *start, *end)){
					if ( value > 255 )
						value = 255;
					else if ( value < 0 )
						value = 0;
					pResult [ index ] = ( int ) value;
				}else
					pResult[y*width+x]=pTemp[y*width+x];
			}else{
				if ( value > 255 )
					value = 255;
				else if ( value < 0 )
					value = 0;
				pResult [ index ] = ( int ) value;
			}
			
         }
         else {
	 pResult [ index ] = pTemp [ index ] ;
         }
     }
 }
    
    wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}

// tells whether the needle is inside or outside of the
// rectangle created by the start and end points
// only handles end lower and to the right of start
bool inFilterArea(wxPoint needle, wxPoint start, wxPoint end)
{
	bool inXRange = needle.x < end.x && needle.x > start.x;
	bool inYRange = needle.y < end.y - toolheight && needle.y > start.y - toolheight;
	
	return inXRange && inYRange;
}

// rotates the image
wxImage* rotate(wxImage *pImage, bool right)
{
	wxImage* rotated = new wxImage();
	*rotated = pImage->Rotate90(right);
	return rotated;
}

// scales the image
wxImage* scale(wxImage *pImage, float factor)
{
    float height = pImage->GetHeight() * factor;
    float width = pImage->GetWidth() * factor;
	wxImage* scaled = new wxImage();
	*scaled = pImage->Scale((int)width, (int)height);
	return scaled;
}

// mirrors the image
wxImage* mirror(wxImage *pImage)
{
	wxImage* mirrored = new wxImage();
	*mirrored = pImage->Mirror(pImage);
	return mirrored;
}

// rotates the hue of the image
wxImage* rotateHue(wxImage *pImage, bool right)
{
	return pImage;
}



wxImage *copy(wxImage *masterImage) {
    int x,y;
	int height = masterImage->GetHeight();
	int width = masterImage->GetWidth();
	int* pTemp;	
	int* pResult;
	
    pTemp=new int [width*height];
	pResult=new int[width*height];
 	
    wxImage2grayBuffer(masterImage, pTemp);	

	for(x=0;x<width;x++) {
		for(y=0;y<height;y++) {
			unsigned long index;
    		index=(unsigned long)y*width+x;
			pResult[index] = pTemp[index];
		}
	}
	
	wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}

// image to gray scale buffer
void wxImage2grayBuffer(const wxImage* img, int* buffer)
{
    unsigned long pix_index = 0, byte_index=0;
    unsigned long buffer_len;
    unsigned char* img_buffer;
    
    buffer_len = img->GetWidth()* img->GetHeight();
    img_buffer = img->GetData();
        
    for( pix_index=0, byte_index=0; pix_index<buffer_len; pix_index++ )
    {
        int sum = 0;
        sum = img_buffer[byte_index++];
        sum += img_buffer[byte_index++];
        sum += img_buffer[byte_index++];
        
        buffer[pix_index] = sum/3;
    }
    
    return;
}

// gray image to a wxImage
wxImage* grayBuffer2wxImage(const int* buffer, int width, int height)
{
    unsigned long pix_index = 0, byte_index=0;
    unsigned long buffer_len;
    unsigned char* img_buffer;
    
    wxImage* img = new wxImage(width,height);
    buffer_len = width*height;
    img_buffer = new unsigned char[width*height*3];
            
    for( pix_index=0, byte_index=0; pix_index<buffer_len; pix_index++ )
    {
        img_buffer[byte_index++] = (unsigned char)buffer[pix_index];
        img_buffer[byte_index++] = (unsigned char)buffer[pix_index];
        img_buffer[byte_index++] = (unsigned char)buffer[pix_index];
    }
    
    img->SetData(img_buffer);
        
    return img;    
}

// color image to a wxImage
wxImage* colorBuffer2wxImage(const int* buffer, int width, int height)
{
    unsigned long pix_index = 0, byte_index=0;
    unsigned long buffer_len;
    unsigned char* img_buffer;
	double PI = 3.1415; 
    
    wxImage* img = new wxImage(width,height);
    buffer_len = width*height;
    img_buffer = new unsigned char[width*height*3];
            
    for( pix_index=0, byte_index=0; pix_index<buffer_len; pix_index++ )
    {
        if(buffer[pix_index] > 0)
        {
                img_buffer[byte_index++] = 255-(unsigned char)(buffer[pix_index]*255/PI);
                img_buffer[byte_index++] = (unsigned char)(0);
                img_buffer[byte_index++] = 255-(unsigned char)(buffer[pix_index]*255/PI);
        }
        if(buffer[pix_index] < 0)
        {
                img_buffer[byte_index++] = (unsigned char)(0);
                img_buffer[byte_index++] = (unsigned char)(buffer[pix_index]*255/PI);
                img_buffer[byte_index++] = (unsigned char)(0);
        }
        if(buffer[pix_index] == 0)
        {
                img_buffer[byte_index++] = (unsigned char)(0);
                img_buffer[byte_index++] = (unsigned char)(0);
                img_buffer[byte_index++] = (unsigned char)(0);
        }
        
                
    }
    
    img->SetData(img_buffer);
        
    return img;    
}


void wxImage2colorBuffer(const wxImage* img, int* buffer)
{
    unsigned long pix_index = 0, byte_index=0;
    unsigned long buffer_len;
    unsigned char* img_buffer;
    
	double PI = 3.1415;
    buffer_len = img->GetWidth()* img->GetHeight();
    img_buffer = img->GetData();
        
    for( pix_index=0, byte_index=0; pix_index<buffer_len; pix_index++ )
    {
        int sum = 0;
        sum = img_buffer[byte_index++]*255/PI;
        sum += img_buffer[byte_index++]*255/PI;
        sum += img_buffer[byte_index++]*255/PI;
        
        buffer[pix_index] = 255-sum/3;
    }
    
    return;
}
