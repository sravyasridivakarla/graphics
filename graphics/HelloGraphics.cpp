#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;


float *PixelBuffer;
const int WINDOW_SIZE_WIDTH = 200;
const int WINDOW_SIZE_HEIGHT = 200;
const int WINDOW_SIZE_POS_X = 100;
const int WINDOW_SIZE_POS_Y = 100;

const int WIDTH = 200;
const int HEIGHT =  200;

const int CORD_X0 = 50;
const int CORD_Y0 = 50;
const int CORD_X1 = 150;
const int CORD_Y1 = 150;


void display();

class Point{
public:
    //Coordinate
    int x, y;
    //Color
    int r, g, b;
    
    //default rgb
    Point(int ex, int why){
        x = ex;
        y = why;
        r = 255;
        g = 255;
        b = 255;
    }
    
    //custom rgb
    Point(int ex, int why, int are, int gee, int bee){
        x = ex;
        y = why;
        r = are;
        g = gee;
        b = bee;
    }
};



void makePixel(Point p, float* pixels, int width, int height)
{
    if (0 <= p.x && p.x < width && 0 <= p.y && p.y < height) {
        int position = (p.x + p.y * width) * 3;
        pixels[position] = p.r;
        pixels[position + 1] = p.g;
        pixels[position + 2] = p.b;
    }
}

void drawLineDDA(Point p0, Point p1){
    
    int steps;
    
    //Calculate the difference b/w the two end points
    //IS THIS FLOAT????
    float dx = p1.x - p0.x;
    float dy = p1.y - p0.y;
    
    //Find out which axis has more steps
    if( abs(dx) > abs(dy) ) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }
    
    //Calculate the increment in x coordinate and y coordinate
    int xInc = dx / (float) steps;
    int yInc = dy / (float) steps;
    
    //initialize the starting point
    Point p(p0.x, p0.y);
    cout << p.x << " " << p.y ;
    
    //draw the line step by step by incrementing the x and y axis
    for(int v = 0; v < steps; v++)
    {
        p.x = p.x + xInc;
        p.y = p.y + yInc;
        
        p.x = round(p.x);
        p.y = round(p.y);
        makePixel(p, PixelBuffer, WIDTH, HEIGHT);
    }
}



void drawLineBresenham(Point p0, Point p1)
{
     //Calculate the difference b/w the two end points
    int dx = (p1.x - p0.x);
    int dy = (p1.y - p0.y);
    
    //initialize the starting points of line
    Point p(p0.x, p0.y);
    
    //initial value of slope_error
    int slopeError = 2 * dy - dx;
    
    while(p.x < p1.x){
        if( slopeError >= 0 ){
            makePixel(p, PixelBuffer, WIDTH, HEIGHT);
            p.y = p.y+1;
            slopeError = slopeError + 2 * dy-2 * dx;
        } else {
            makePixel(p, PixelBuffer, WIDTH, HEIGHT);
            slopeError = slopeError + 2 * dy;
        }
        p.x = p.x + 1;
    }
}

void drawLine(Point p0, Point p1, int choice){
    // 0 - drawLineDDA(int x0, int y0, int x1, int y1)
    // 1 - drawlineBresenham(int x0, int y0, int x1, int y1)
    
    if( choice == 0){
        drawLineDDA(p0, p1);
    } else {
        drawLineBresenham(p0, p1);
    }
}


int main(int argc, char *argv[])
{
    //allocate new pixel buffer, need initialization!!
    PixelBuffer = new float[HEIGHT * WIDTH * 3];
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    //Set window size
    glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
    //Set window position
    glutInitWindowPosition(WINDOW_SIZE_POS_X, WINDOW_SIZE_POS_Y);
    
    //create and set main window title
    int MainWindow = glutCreateWindow("Hello Graphics!!");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    
    //draw the pixel with the right color
    //p1(x0,y0) p2(x1,y1)
    Point p1(CORD_X0, CORD_Y0);
    Point p2(CORD_X1, CORD_Y1);
    makePixel(p1,PixelBuffer, WIDTH, HEIGHT);
    drawLine(p1,p2,1);
    
    //sets display function
    glutDisplayFunc(display);
    
    glutMainLoop();//main display loop, will display until terminate
    return 0;
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
    //Misc.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_FLOAT, PixelBuffer);
    
    //window refresh
    glFlush();
}
