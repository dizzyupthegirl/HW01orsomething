/*
 
 Samantha Wolf
 CSE 274
 Homework One...or something
 To meet the requirements of this homework I 
 did the following:
 Main goals PART A: A1, A2, A3, and A4. 
 All seen in seperate methods.
 Main goals PART B:I attempted to complete B1, but it actually 
 copied parts of the screen instead of blurring them. 
 See the blurScreen method. 
 Strech goals PART E: 
 E5(the lines move)
 E6(click to toggle the line animation)
 */



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

	// NC: There are no method declarations here! Be sure to take care of 
	// NC: that on your nect project in a .h file
};

	//Variables that are used through out the program
	int counter;
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;
	bool animate;
	
	
	void HW01orsomethingApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
	}

	void HW01orsomethingApp::setup()
	{
		my_surface_ = new Surface(kAppWidth, kAppHeight, false);
		counter=0;
	}
	
	/*
	*This method takes a mouse click and toggles the animation of the 
	*vertical lines moving across the screen
	*/
	void HW01orsomethingApp::mouseDown( MouseEvent event )
	{
		animate=!animate;
	}

	/*
	*This method returns the index of the x y coordinates.
	* Similar to getters we used in java
	* 
	*@param x the x coordinate
	*@param y the y coordinate
	*/
	int getIndex(int x, int y) {
		// NC: Clever. This makes the rest of your code more easily understood.
		return 3*(y*kAppWidth+x);
	}

	/*
	*This method draws vertical lines, it's a variation of the drawRectangle method
	*@param pixelData the "array" of bits that appear on the screen
	*@param x the starting x coordinate
	*@param y the starting y coordinate
	*@param width the width of the line
	*@param height the height of the line
	*@param color the color
	*/
	void drawVerticalLine(uint8_t* pixelData, int x, int y, int width, int height, int color) {
	
		//NC: Is this method necessary? It seems as if the drawLine method
		//NC: would be able to take of this for you
		for(x; x<width; x++) {
		for(y; y<height; y++) {
			pixelData[3*(y*kAppWidth+x)]=color;
			}
		}
	}

	/*
	*This method changes the color of a pixel
	*@param r the amount of red
	*@param g the amount of green
	*@param b the amount of blue
	*@param index the index of the pixel to be changed
	*@param pixelData the "array" of bits that appear on the screen
	*/
	void changeColor(int r, int g, int b, int index, uint8_t* pixelData) {
		 if(index>=0 && index <kAppHeight*kAppWidth*3){
			pixelData[index]=r;
			pixelData[index+1]=g;
			pixelData[index+2]=b;
		}
	}

	/*
	*This method draws circles on the screen. 
	*Cite: Brandon Sonoda for helping me understand this method
	*@param x the starting x coordinate
	*@param y the starting y coordinate
	*@param r the radius of the circle
	*@param pixelData the "array" of bits that appear on the screen
	*/
	void drawCircle(int x, int y, int r, uint8_t* pixelData){
    int tempX, tempY;
    double angle = 0;
    
    int i;
    
	// Very good and interesting approach here.
    while(angle < 6.28){
        tempX = x+r*sin(angle+3.14/2);
        tempY = y+r*sin(angle);
        i = getIndex(tempX, tempY);    
        changeColor(0,0,255,i, pixelData);
        angle+=.01;
    }
}

	/*
	*Okay, so this method was supposed to blue the screen, however, it doesn't.
	*But what it does is way cooler, and I just couldn't change it.
	*I know that to get the blue method to work, I would've had to change 
	*my approach to nested for loops, but I'm still happy with the way this turned out
	*
	*@param pixelData the "array" of bits that appear on the screen
	*/
	void blurScreen(uint8_t* pixelData) {
		
		// NC: While this method does produce a very cool effect,
		// NC: it could be cleaned up in regards to the several variables it creates
		// NC: and uses. Arrays may be able to assist in this.
		int red1, red2, red3, red4, red5, red6, red7, red8, red9;
		int green1, green2, green3, green4, green5, green6, green7, green8, green9;
		int blue1, blue2, blue3, blue4, blue5, blue6,blue7, blue8, blue9;
		double redAv, greenAv, blueAv;
		for(int pixel=0; pixel<(3*kAppWidth*kAppHeight)-1; pixel+=3) {
			red1=pixelData[pixel];
			green1=pixelData[pixel+1];
			blue1=pixelData[pixel+2];
			red2=pixelData[pixel+3];
			green2=pixelData[pixel+4];
			blue2=pixelData[pixel+5];
			red3=pixelData[pixel+6];
			green3=pixelData[pixel+7];
			blue3=pixelData[pixel+8];
			red4=pixelData[pixel+kAppWidth];
			green4=pixelData[pixel+kAppWidth+1];
			blue4=pixelData[pixel+2+kAppWidth];
			red5=pixelData[pixel+3+kAppWidth];
			green5=pixelData[pixel+4+kAppWidth];
			blue5=pixelData[pixel+5+kAppWidth];
			red6=pixelData[pixel+6+kAppWidth];
			green6=pixelData[pixel+7+kAppWidth];
			blue6=pixelData[pixel+8+kAppWidth];
			red7=pixelData[pixel+2*kAppWidth];
			green7=pixelData[pixel+1+2*kAppWidth];
			blue7=pixelData[pixel+2+2*kAppWidth];
			red8=pixelData[pixel+3+2*kAppWidth];
			green8=pixelData[pixel+4+2*kAppWidth];
			blue8=pixelData[pixel+5+2*kAppWidth];
			red9=pixelData[pixel+6+2*kAppWidth];
			green9=pixelData[pixel+7+2*kAppWidth];
			blue9=pixelData[pixel+8+2*kAppWidth];

			redAv=(red1+red2+red3+red4+red5+red6+red7+red8+red9)/9.0;
			greenAv=(green1+green2+green3+green4+green5+green6+green7+green8+green9)/9.0;
			blueAv=(blue1+blue2+blue3+blue4+blue5+blue6+blue7+blue8+blue9)/9.0;
			pixelData[pixel+3]=(int)redAv;
			pixelData[pixel+4]=(int)greenAv;
			pixelData[pixel+5]=(int)blueAv;
		}
}
	
	/*
	*This method draw a rectangle that starts at the center of the screen and goes out 
	* leaving 1/4 of the screen no matter which way you go
	*
	*@param pixelData the "array" of bits that appear on the screen
	*@param color messes with the color red in the pixel
	*/
	void drawRectangles(uint8_t* pixelData, int color) {
 
		// NC: It may be beneficial to pass a few more parameters, 
		// NC: just to make the placement of the rectangle more easily
		// NC: controlled
 	for(int x= (kAppWidth/4); x<(kAppWidth/4*3); x++) {
 		for(int y=kAppHeight/4; y<(kAppHeight/4*3); y++) {
			pixelData[3*(y*kAppWidth+x)]=color;
 			}
 		}
 	}

	
	/*I found most of this method online, at 
	* http://roguebasin.roguelikedevelopment.org/index.php/Bresenham's_Line_Algorithm
	* I tweaked some of it to follow other methods I already had in my program
	* This draws the lines that appear on the bottom of the screen
	*/

	void drawLine(int x1, int y1, int const x2, int const y2, uint8_t* pixelData) {
		int tempX, tempY, holder;
		if(x1>x2) 
			tempX=x1-x2;
		else
			tempX=x2-x1;
		if(y1>y2) 
			tempY=y1-y2;
		else
			tempY=y2-y1;

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
        while (y1 != y2) {
            if ((error >= 0) && (error || (iy > 0))) {
                error -= delta_y;
                x1 += ix;
            }
            error += delta_x;
            y1 += iy;
            changeColor(0,255,0,getIndex(x1, y1), pixelData);
        }
    }

	
}
	
	/*
	*This method makes the screen have a gradient to it
	*
	*@param redTop the amount of red in the top color
	*@param greenTop the amount of green in the top color
	*@param blueTop the amount of blue in the top color
	@param redBottom the amount of red in the bottom color
	*@param greenBottom the amount of green in the bottom color
	*@param blueBottom the amount of blue in the bottom color
	*@param pixelData the "array" of bits that appear on the screen
	*/
	void gradientBackground(int redTop, int greenTop, int blueTop, int redBottom , int greenBottom, int blueBottom, uint8_t* pixelData){
	int i, y, x;
	double percent;
    for(y = 0; y<kAppHeight; y++){
        for(x= 0; x<kAppWidth; x++){
            i = getIndex(x, y);
            if( i>= 0 && i < (kAppWidth*kAppHeight*3)){
                percent = ((double)y/kAppHeight);
                pixelData[i] = ((1-percent)*redTop)+(percent*redBottom);
                pixelData[i+1] = ((1-percent)*greenTop)+(percent*greenBottom);
                pixelData[i+2] = ((1-percent)*blueTop)+(percent*blueBottom);
            }
        }
    }
}

	void HW01orsomethingApp::update()
	{
	uint8_t* pixelData = (*my_surface_).getData();
	
	gradientBackground(0, 0, 0, 190, 190, 255, pixelData);
	drawRectangles(pixelData, 90);
	drawLine(0, 300, 400, 600, pixelData);
	drawLine(400, 600, 800, 300, pixelData);
	drawCircle(kAppWidth/2, kAppHeight/2, 200, pixelData);
	if(counter<400) {
	drawVerticalLine(pixelData, 400+counter, 0, kAppWidth, kAppHeight, 255);
	drawVerticalLine(pixelData, 400-counter, 0, kAppWidth, kAppHeight, 255);
	if(animate) 
	counter++;
	}
	else {
		counter=0;
	}
	blurScreen(pixelData);
	}	
	
	void HW01orsomethingApp::draw()
	{
	gl::draw(*my_surface_);
	}

	CINDER_APP_BASIC( HW01orsomethingApp, RendererGl )
