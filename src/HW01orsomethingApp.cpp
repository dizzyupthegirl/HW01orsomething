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
	int red;
	int green;
	int blue;
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;
	
};

	void HW01orsomethingApp::setup()
	{
		my_surface_ = new Surface(kAppWidth, kAppHeight, false);
	
	}
	

	void HW01orsomethingApp::mouseDown( MouseEvent event )
	{
	}

	void HW01orsomethingApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
	}

	//This method puts a rectangle in the middle of the screen
	void drawRectangle(uint8_t* pixelData, int AppWidth, int AppHeight, int color) {

	for(int x= (AppWidth/4); x<(AppWidth/4*3); x++) {
		for(int y=AppHeight/4; y<(AppHeight/4*3); y++) {
			pixelData[3*(y*AppWidth+x)]=color;
			}
		}
	}


	void HW01orsomethingApp::update()
	{
	uint8_t* pixelData = (*my_surface_).getData();
	drawRectangle(pixelData, kAppWidth, kAppHeight, 50);
	drawRectangle(pixelData, 400, 300, 255);
	drawRectangle(pixelData, 400, 2400, 255);
			

	}
	


	

	void HW01orsomethingApp::draw()
	{
	gl::draw(*my_surface_);
	}

	CINDER_APP_BASIC( HW01orsomethingApp, RendererGl )