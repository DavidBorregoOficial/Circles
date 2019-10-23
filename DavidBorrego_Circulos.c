/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include "raylib.h"
#define MAX_BOLAS 5 //cantidad de bolas

typedef struct Circulo{ //estructura de los circulos
    int radius;
    Vector2 center;
    Vector2 speed;
    Color color;
} Circulo;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "arrays");
    

    
    Circulo pelota [MAX_BOLAS];
    for(int i = 0; i < MAX_BOLAS; i++) //array con velocidad, radio, posicion y colores de las pelotas
    {        
        pelota[i].radius = GetRandomValue(5, 20);
        pelota[i].center.x = GetRandomValue(pelota[i].radius, screenWidth-pelota[i].radius);
        pelota[i].center.y = GetRandomValue(pelota[i].radius, screenHeight-pelota[i].radius);
        pelota[i].speed.x = GetRandomValue(1, 5);
        pelota[i].speed.y = GetRandomValue(1, 5);
        pelota[i].color.a = 255;
        pelota[i].color.r = GetRandomValue(1,255);
        pelota[i].color.g = GetRandomValue(1,255);
        pelota[i].color.b = GetRandomValue(1,255);
    }        
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        for(int i = 0; i < MAX_BOLAS; i++)
        {           
            for(int j = 0; j < MAX_BOLAS; j++)
            {
                if(i == j) //evitar que las bolas no tengan la opcion de no chocar
                {
                    j += 1;
                    if (j >= MAX_BOLAS)
                    {
                        break; //evitar que las bolas se queden quietas
                    }
                }  
                if(CheckCollisionCircles(pelota[i].center,pelota[i].radius, pelota[j].center, pelota[j].radius))
                {
                    if(pelota[i].speed.x > 0 && pelota[j].speed.x > 0)
                    {
                        if(pelota[i].speed.y > 0 && pelota[j].speed.y > 0) //1  choques misma direccion y velocidad. x+y+
                        {
                            if(pelota[i].speed.y > pelota[j].speed.y) // i > j
                            {
                                pelota[i].speed.y *= -1;
                                pelota[i].speed.x *= -1;
                            }
                        }
                        else if(pelota[i].speed.y < 0 && pelota[j].speed.y < 0) //2  choques misma direccion y velocidad. x+y-
                        {
                            if(pelota[i].speed.y < pelota[j].speed.y) // i < j
                            {
                                pelota[j].speed.y *= -1;
                                pelota[j].speed.x *= -1;
                            }                                
                        }
                        else if((pelota[i].speed.y < 0 && pelota[j].speed.y > 0) || (pelota[i].speed.y > 0 && pelota[j].speed.y < 0)) //choques opuestos i x+y- j x+y+ 2.  choques opuestos i x+y+ j x+y-
                        {
                            pelota[j].speed.y *= -1;
                            pelota[i].speed.y *= -1;                             
                        }                        
                    }
                    else if(pelota[i].speed.x < 0 && pelota[j].speed.x < 0) 
                    {
                        if(pelota[i].speed.y < 0 && pelota[j].speed.y < 0) //choques misma direccion y velocidad. x-y-
                        {
                            if(pelota[i].speed.y > pelota[j].speed.y) // i < j
                            {
                                pelota[j].speed.y *= -1;
                                pelota[j].speed.x *= -1;
                            }                            
                        }
                        else if(pelota[i].speed.y > 0 && pelota[j].speed.y > 0) //choques misma direccion y velocidad. x-y+
                        {
                            if(pelota[i].speed.y < pelota[j].speed.y) // i > j
                            {
                                pelota[i].speed.y *= -1;
                                pelota[i].speed.x *= -1;
                            }                            
                        }
                        else if((pelota[i].speed.y > 0 && pelota[j].speed.y < 0) || (pelota[i].speed.y < 0 && pelota[j].speed.y > 0)) //choques opuestos i x-y+ j x-y-.  choques opuestos i x-y- j x-y+
                        {
                            pelota[j].speed.y *= -1;
                            pelota[i].speed.y *= -1;                           
                        }                       
                    }
                    else //choques opuestos i x-y+ j x+y+ i x-y- j x+y-
                    {
                        if((pelota[i].speed.y < 0 && pelota[j].speed.y < 0) || (pelota[i].speed.y > 0 && pelota[j].speed.y > 0))
                        {
                            pelota[j].speed.x *= -1;
                            pelota[i].speed.x *= -1;                            
                        }
                        else //alternativa i y j 
                        {
                            pelota[j].speed.x *= -1;
                            pelota[j].speed.y *= -1;
                            pelota[i].speed.x *= -1;
                            pelota[i].speed.y *= -1;
                        }
                    }
                }
                pelota[i].center.x += pelota[i].speed.x;
                pelota[i].center.y += pelota[i].speed.y;               
                
                if(pelota[i].center.x + pelota[i].radius >= screenWidth || pelota[i].center.x - pelota[i].radius <= 0) //golpe en la pantalla anchura
                {
                    pelota[i].speed.x *= -1;
                }
                else if(pelota[i].center.y + pelota[i].radius >= screenHeight || pelota[i].center.y - pelota[i].radius <= 0)// golpe en la pantalla altura
                {
                    pelota[i].speed.y *= -1;
                }                
            }
        }    
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
            for(int i = 0; i < MAX_BOLAS; i++)
            {               
                DrawCircleV(pelota[i].center, pelota[i].radius, pelota[i].color); //pelotas
            }     
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}