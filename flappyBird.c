#include "raylib.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include <time.h>
int main(){
    SetRandomSeed(time(NULL));
    // start:
    int wH = 1080;
    int wW = 1080;
    int bH = 100;
    int bW = 100;
    int gap = 200;
    int bx = 300;
    float by = 1080/2 - 100;
    int fps = 60;
    int score = 0;
    float gravity = 2;
    // float jump = 4;
    int jumpcheck = 0;
    int gameover = 1;
    int boxY = 1080;
    int boxH = GetRandomValue(0,1000);
    
    InitWindow(wW,wH,"Flappy Bird");
    SetTargetFPS(fps);
    start:
    while(!WindowShouldClose()){
        BeginDrawing();
        Rectangle rec1={bx,by+=gravity,bW,bH};
        Rectangle rec2={boxY,0,100,boxH};
        Rectangle rec3={boxY,boxH+400,100,1100-boxH};
        DrawRectangle(bx,by+=gravity,bW,bH,RED);
        DrawRectangle(boxY,0,100,boxH,RED);
        DrawRectangle(boxY,boxH+400,100,1100-boxH,RED);
        DrawText(TextFormat("%d",score/3),20,20,50,GREEN);
        if(IsKeyPressed(KEY_SPACE)){
            gravity=-5;
            jumpcheck = 1;
            // WaitTime(2);
            // gravity=2;
        }
        if(jumpcheck==1 && gravity!=2){
            gravity+=0.1;
        }
        if(gravity==2){
            // WaitTime(2);
            // gravity=2;
            jumpcheck=0;
        }
        if(by>=1080-80 || by<=0.000000-10){
            DrawText("Game Over",1080/2-MeasureText("Game Over",70)/2,1080/2-35,70,BLUE);
            gravity=10;
            if(by<=-10) by = 1080;
            gameover=0;
        }
        if(boxY<=-105){
            boxY=1080;
            boxH = GetRandomValue(0,500);
        }
        if(boxY<=bx-100 && boxY>=bx-105){
            score++;
        }
        if(CheckCollisionRecs(rec1,rec2) || CheckCollisionRecs(rec1,rec3)){
            DrawText("Game Over",1080/2-MeasureText("Game Over",70)/2,1080/2-35,70,BLUE);
            gravity=10;
            if(by<=-10) by = 1080;
            gameover=0;
        }
        if(gameover)boxY-=2;
    //     if(!gameover && IsKeyPressed(KEY_R)){
    //         goto start;
    //         // CloseWindow();
    //          bH = 100;
    //          bW = 100;
    //          gap = 200;
    //          bx = 300;
    //          by = 1080/2 - 100;
    //          score = 0;
    //          gravity = 2;
    // // float jump = 4;
    //          jumpcheck = 0;
    //          gameover = 1;
    //          boxY = 1080;
    //         boxH = GetRandomValue(0,1000);
    //     }
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}