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
	int count;
	int xIndex;
	int yIndex;
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;

	
};

	void HW01orsomethingApp::setup()
	{
		my_surface_ = new Surface(kAppWidth, kAppHeight, false);
		count=0;
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

	//This method puts a rectangle in the middle of the screen
	void drawRectangle(uint8_t* pixelData, int x, int y, int width, int height, int color, int kAppWidth, int kAppHeight) {
	for(x; x<width; x++) {
		for(y; y<height; y++) {
			pixelData[3*(y*kAppWidth+x)]=color;
			}
		}
	}


	void clearBackground(uint8_t* data, int kAppWidth, int kAppHeight){
    for(int i = 0; i<kAppWidth*kAppHeight*3; i++){
        data[i] = 0;
    }
}
	void drawLine(uint8_t* pixelData, int X, int Y, int length, int color, int kAppWidth, int kAppHeight) {
		drawRectangle(pixelData, X, Y, length, 3, color, kAppWidth, kAppHeight);
	}

	void HW01orsomethingApp::update()
	{
	uint8_t* pixelData = (*my_surface_).getData();
	
	//clearBackground(pixelData, kAppWidth, kAppHeight);
	//drawRectangle(pixelData, xIndex, yIndex, xIndex*3, yIndex*3, 50, kAppWidth, kAppHeight);
	drawRectangle(pixelData, 0,0, kAppWidth, kAppHeight, 255, kAppWidth, kAppHeight);
	//count++;
	/*if(count>5) {
		count=0;
		xIndex=kAppWidth/4;
		yIndex=kAppHeight/4;

	}
	else {
		xIndex=xIndex/2;
		yIndex/2;
	}
	
	*/
	}

	

	void HW01orsomethingApp::draw()
	{
	gl::draw(*my_surface_);
	}

	CINDER_APP_BASIC( HW01orsomethingApp, RendererGl )
