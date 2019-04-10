#include "primlib.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUMBER_OF_VERTICES 6

#define ANGLE_OF_ROTATION (M_PI/360)

#define X_COORDINATE_CENTER  (screenWidth() / 2)
#define Y_COORDINATE_CENTER (screenHeight() / 2)

#define RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED 100
#define RADIUS_MAX 150
#define RADIUS_MIN 50

#define DELAY_TIME 7


int main(int argc, char* argv[])
{
	if(initGraph())
	{
		exit(3);
	}
	/* clear screen */
	filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);


//if GetSmaller==1 the polygon is getting smaller - in other case it is getting bigger
int GetSmaller=0; 

//all values that are used in loops to calculate coordinates of apex and to connect those points
int CurrentApex, XcoordinateOfCurrentApex, YcoordinateOfCurrentApex; 
int CoordinatesOfApex[NUMBER_OF_VERTICES+15][2]; 
float CurrentAngleBetweenYaxisAndRadius;

//variable to change number of vertices
int ChangeNumberOfVertices = 0;

//variable to change radius of circle in which polygon is inscribed
int ChangeRadius = 0; 

//variable of event type that detect whether a key/mousebutton is pressed
SDL_Event ButtonPressed;

//array to switch between different colors of polygon
enum color Color[] = {WHITE, BLUE, GREEN, RED, YELLOW, CYAN, MAGENTA};
int CurrentColor = 1;



do
{
    
    for(CurrentAngleBetweenYaxisAndRadius=0.0;CurrentAngleBetweenYaxisAndRadius<M_PI*2.0;CurrentAngleBetweenYaxisAndRadius=CurrentAngleBetweenYaxisAndRadius+ANGLE_OF_ROTATION)
    {
        
        
        filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);
        textout(20, 20,"Press RIGHT/LEFT to change color",WHITE);        
        textout(20, 30,"Press UP/DOWN to change number of vertices",WHITE); 

        updateScreen();
        
        for(CurrentApex=1;CurrentApex<=(NUMBER_OF_VERTICES+ChangeNumberOfVertices);CurrentApex++)
        {
            XcoordinateOfCurrentApex=sin(2*M_PI/(NUMBER_OF_VERTICES+ChangeNumberOfVertices)*CurrentApex -CurrentAngleBetweenYaxisAndRadius)*(RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED+ChangeRadius) + X_COORDINATE_CENTER;
            
            YcoordinateOfCurrentApex=cos(2*M_PI/(NUMBER_OF_VERTICES+ChangeNumberOfVertices)*CurrentApex -CurrentAngleBetweenYaxisAndRadius)*(RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED+ChangeRadius) + Y_COORDINATE_CENTER;

            CoordinatesOfApex[CurrentApex-1][0]=XcoordinateOfCurrentApex;
            CoordinatesOfApex[CurrentApex-1][1]=YcoordinateOfCurrentApex;
        }

        for(CurrentApex=1;CurrentApex<=(NUMBER_OF_VERTICES+ChangeNumberOfVertices);CurrentApex++)
        {
            if(CurrentApex!=(NUMBER_OF_VERTICES+ChangeNumberOfVertices))
                line(CoordinatesOfApex[CurrentApex-1][0], CoordinatesOfApex[CurrentApex-1][1], CoordinatesOfApex[CurrentApex][0], CoordinatesOfApex[CurrentApex][1], Color[CurrentColor]);
            else
                line(CoordinatesOfApex[CurrentApex-1][0], CoordinatesOfApex[CurrentApex-1][1], CoordinatesOfApex[0][0], CoordinatesOfApex[0][1], Color[CurrentColor]);
        }

        updateScreen();

        SDL_Delay(DELAY_TIME);
        
        if((RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED+ChangeRadius)<RADIUS_MAX && GetSmaller==0)
        {
            ChangeRadius++;
            if((RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED+ChangeRadius)==RADIUS_MAX) GetSmaller=1;
        }
        else if((RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED+ChangeRadius)>RADIUS_MIN && GetSmaller==1)
        {
            ChangeRadius--;
            if((RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED+ChangeRadius)==RADIUS_MIN) GetSmaller=0;
        }
    
        
        while(SDL_PollEvent(&ButtonPressed))
        {
            if(ButtonPressed.type == SDL_QUIT || ButtonPressed.key.keysym.sym == SDLK_ESCAPE)
                return 0;
            else if(ButtonPressed.type == SDL_KEYDOWN)
            {
                if(ButtonPressed.key.keysym.sym == SDLK_LEFT)
                {
                    if(CurrentColor>0) CurrentColor--;
                    else if(CurrentColor==0) CurrentColor=6;
                }
                else if(ButtonPressed.key.keysym.sym == SDLK_RIGHT)
                {
                    if(CurrentColor<6) CurrentColor++;
                    else if(CurrentColor==6) CurrentColor=0;
                }
                else if(ButtonPressed.key.keysym.sym == SDLK_UP && (NUMBER_OF_VERTICES+ChangeNumberOfVertices)<15)
                {
                   ChangeNumberOfVertices++; 
                }
                else if(ButtonPressed.key.keysym.sym == SDLK_DOWN && (NUMBER_OF_VERTICES+ChangeNumberOfVertices)>3)
                {
                    ChangeNumberOfVertices--;
                }
            }
        }
        
        // potential errors
        if(RADIUS_MAX < (RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED+ChangeRadius) || RADIUS_MIN > (RADIUS_OF_CIRCLE_IN_WHICH_POLYGON_IS_INSCRIBED+ChangeRadius))
        {
            printf("\n\nError.\nCurrent radius exceed RADIUS_MAX or RADIUS_MIN.\n");
            return 0;
        }
        if(RADIUS_MAX<RADIUS_MIN)
        {
            printf("\n\nError.\nRADIUS_MAX is smaller than RADIUS_MIN. That's impossible.\n");
            return 0;
        }
        if(NUMBER_OF_VERTICES<3)
        {
            printf("\n\nError.\nThis is not a polygon.\n");
            return 0;
        }
        
    }
}while(1);

	updateScreen();
	getkey();
	return 0;
}


