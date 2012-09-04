#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW01orsomethingApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);

	private:
    Surface* my_surface_;
};
	int counter;
	int xIndex;
	int yIndex;
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;
	
	


	void HW01orsomethingApp::setup()
	{
		my_surface_ = new Surface(kAppWidth, kAppHeight, false);
		counter=0;
		xIndex=kAppWidth/4;
		yIndex=kAppHeight/4;
	}
	

	void HW01orsomethingApp::mouseDown( MouseEvent event )
	{
	}

	void HW01orsomethingApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
	}

	int getIndex(int x, int y) {
		return 3*(y*kAppWidth+x);
	}
	void drawVerticalLine(uint8_t* pixelData, int x, int y, int width, int height, int color) {
	
	for(x; x<width; x++) {
		for(y; y<height; y++) {
			pixelData[3*(y*kAppWidth+x)]=color;
			}
		}
	}

	void changeColor(int r, int g, int b, int index, uint8_t* pixelData) {
		 if(index>=0 && index <kAppHeight*kAppWidth*3){
			pixelData[index]=r;
			pixelData[index+1]=g;
			pixelData[index+2]=b;
	
	}
	}


	void drawCircle(int posX, int posY, int radius, uint8_t* pixelData){
    int tempX, tempY;
    double angle = 0;
    
    int index;
    
    while(angle < 6.28){
        tempX = posX+radius*sin(angle+3.14/2);
        tempY = posY+radius*sin(angle);
        index = getIndex(tempX, tempY);    
        changeColor(0,0,255,index, pixelData);
        angle+=.01;
    }
}

	void clearBackground(uint8_t* data){
    for(int i = 0; i<kAppWidth*kAppHeight*3; i++){
        data[i] = 0;
    }
}
	
	
	void drawRectangles(uint8_t* pixelData, int color) {
 
 	for(int x= (kAppWidth/4); x<(kAppWidth/4*3); x++) {
 		for(int y=kAppHeight/4; y<(kAppHeight/4*3); y++) {
			pixelData[3*(y*kAppWidth+x)]=color;
 			}
 		}
 	}

	/*void drawTriangle() {
		int count=0;
	 for(int x= (kAppWidth/4); x<(kAppWidth/4*3); x++) {
 		for(int y=kAppHeight/4; y>0; y--) {
			pixelData[3*(y*AppWidth+x)]=color;
		}
	
	}
	}
	*/
	void drawLine(int x1, int y1, int const x2, int const y2, uint8_t* pixelData) {
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
 
    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
 
    changeColor(0,255,0,getIndex(x1, y1), pixelData);
 
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
 
            error += delta_y;
            x1 += ix;
 
            changeColor(0,255,0,getIndex(x1, y1), pixelData);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            
 
            error += delta_x;
            y1 += iy;
 
            changeColor(0,255,0,getIndex(x1, y1), pixelData);
        }
    }
}




	void HW01orsomethingApp::update()
	{
	uint8_t* pixelData = (*my_surface_).getData();
	clearBackground(pixelData);
	drawRectangles(pixelData,50);
	drawRectangles(pixelData, 255);
	drawRectangles(pixelData, 40);
	drawLine(20, 20, 520, 520, pixelData);
	drawCircle(kAppWidth/2, kAppHeight/2, 200, pixelData);
	if(counter<400) {
	drawVerticalLine(pixelData, 400+counter, 0, kAppWidth, kAppHeight, 255);
	drawVerticalLine(pixelData, 400-counter, 0, kAppWidth, kAppHeight, 255);
	counter++;
	}
	else {
		counter=0;
	}
	}
	
	
	void HW01orsomethingApp::draw()
	{
	gl::draw(*my_surface_);
	}

	CINDER_APP_BASIC( HW01orsomethingApp, RendererGl )
