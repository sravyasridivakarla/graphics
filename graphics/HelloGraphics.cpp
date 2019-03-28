#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

float *PixelBuffer;
void display();
int WIDTH = 200;
int HEIGHT =  200;



void makePixel(int x, int y, int r, int g, int b, float* pixels, int width, int height)
{
    if (0 <= x && x < width && 0 <= y && y < height) {
        int position = (x + y * width) * 3;
        pixels[position] = r;
        pixels[position + 1] = g;
        pixels[position + 2] = b;
    }
}

void drawLineDDA(int x0, int y0, int x1, int y1){
    
    int steps;
    
    //Calculate the difference b/w the two end points
    int dx = x1 - x0;
    int dy = y1 - y0;
    
    //find out which axis has more steps
    if( abs(dx) > abs(dy) ) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }
    
    //Calculate the increment in x coordinate and y coordinate
    int Xinc = dx / (float) steps;
    int Yinc = dy / (float) steps;
    
    //initialize the starting points
    int x=x1;
    int y=y1;
    
    //draw the line step by step by incrementing the x and y axis
    for(int v = 0; v < steps; v++)
    {
        x = x + Xinc;
        y = y + Yinc;
        makePixel(round(x), round(y),255, 255, 255, PixelBuffer, WIDTH, HEIGHT);
    }
}



int main(int argc, char *argv[])
{
    //allocate new pixel buffer, need initialization!!
    PixelBuffer = new float[HEIGHT * WIDTH * 3];
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    //set window size to 200*200
    glutInitWindowSize(200, 200);
    //set window position
    glutInitWindowPosition(100, 100);
    
    //create and set main window title
    int MainWindow = glutCreateWindow("Hello Graphics!!");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    
    //draw the pixel with the right color
    makePixel(100,100,255,255,255,PixelBuffer, WIDTH, HEIGHT);
    drawLineDDA(50, 50, 100, 100);
    
    
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
    glDrawPixels(200, 200, GL_RGB, GL_FLOAT, PixelBuffer);
    
    //window refresh
    glFlush();
}

