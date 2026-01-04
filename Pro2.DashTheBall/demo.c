/************************************************************************************************************************************* 
 Ball & Dash game.
 Game designer : V.R.Jadeja
 Game music director : Mustansir Chhatariya
 Game logic : V.R.Jadeja
 ©Copyright reserved by owner V.R.Jadeja 2025.
**************************************************************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void saveHighscore(int high){
    FILE *file = fopen("highScore.txt","w");
    if (file == NULL) {
        printf("Error saving file!\n");
        return;
    }
    else{
        fprintf(file,"%d",high);
    }
}
int loadHighscore(){
    FILE *file = fopen("highScore.txt","r");
    int high;
    if (file == NULL) {
        printf("Error saving file!\n");
        return 0;
    }
    else{
        fscanf(file,"%d",&high);
        return high;
    }
}

int main(){
    SetTraceLogLevel(LOG_NONE);
    // Variable Declaration
    SetRandomSeed(time(0));
    int radius = 10;
    int hightWindow = 720;
    int widthWindow = 1080;
    int hightDash = 5;
    int widthDash = 80;
    int fps = 20;
    int hightGame = 720;
    int widhtGame = 720;
    int xBall = GetRandomValue(200,800);
    int yBall = 0;
    int xDash = 200;
    int yDash = 700;
    int speedxDash = 10;
    int speedxBall = 7;
    int speedyBall = 5;
    int score = 0;
    int highScore = loadHighscore();
    int gameover = 1;
    char *scoreBox;
    char highscorestrint[4];
    char highscorestr[15];
    itoa(score,scoreBox,10);
    itoa(highScore,highscorestrint,10);
    
    //intialization part
    // start:
    InitWindow(widthWindow,hightWindow,"Dash the Ball");
    InitAudioDevice();
    Sound ball_wall = LoadSound("ball_wall.wav");
    Sound ball_tap = LoadSound("ball_tap.wav");
    Sound game_over = LoadSound("game_over.wav");
    SetTargetFPS(fps);
    start:
    SetTargetFPS(fps);
    //main part
    while(!WindowShouldClose()){
        BeginDrawing();
        DrawRectangle(widthWindow/2-360,0,widhtGame,hightGame,SKYBLUE);
        DrawCircle(xBall,yBall+10,radius,RED);
        DrawRectangle(xDash,yDash,widthDash,hightDash,RED);
        DrawLine(0,710,1080,710,RED);
        DrawRectangle(50,50,90,MeasureText(scoreBox,50)+50,YELLOW);
        DrawText(scoreBox,67,70,50,RED);
        DrawText("Left: A or <-\nRight: W or ->\nRetry: R",10,200,20,DARKGREEN);
        //DrawRectangle(50,450,MeasureText(highscorestr,25),90,YELLOW);
        DrawText("High Score:",10,460,25,RED);
        DrawText(highscorestrint,10+MeasureText("High Score: ",25),460,25,BLUE);
        //highScore = loadHighscore();
        itoa(highScore,highscorestrint,10);
        if(score>highScore){
                saveHighscore(score);
                highScore=score;
                //highScore = loadHighscore();
                //itoa(score,highscorestrint,10);
            }
        if(yBall!=705){
            yBall+=speedyBall;
            xBall+=speedxBall;
            if(xBall>=890 && xBall<=910){
                speedxBall=-7;
                PlaySound(ball_wall);
            }
            if(xBall>=170 && xBall<=200){
                speedxBall=7;
                PlaySound(ball_wall);
            }
            if(yBall==5){
                speedyBall=5;
                PlaySound(ball_wall);
            }
            if(yBall==690 && xBall>xDash && xBall<xDash+widthDash){
                speedyBall=-5;
                score++;
                PlaySound(ball_tap);
                itoa(score,scoreBox,10);
                if(score!=0 && score<10) {
                    fps+=score;
                    SetTargetFPS(fps);
                }
            }
            if((IsKeyPressed(KEY_A)||IsKeyDown(KEY_A) || IsKeyPressed(KEY_LEFT)||IsKeyDown(KEY_LEFT))&&xDash!=170){
                xDash-=speedxDash;
            }
            if((IsKeyPressed(KEY_D)||IsKeyDown(KEY_D) || IsKeyPressed(KEY_RIGHT)||IsKeyDown(KEY_RIGHT))&&xDash!=830){
                xDash+=speedxDash;
            }
        }
        else {
            
            if(gameover==1){
                
                PlaySound(game_over);
                gameover=0;
               
            }
            saveHighscore(highScore);
            DrawText("Game Over",widthWindow/2-MeasureText("Game Over",50)/2,100,50,RED);
            DrawRectangle(900,50,MeasureText("RETRY",50),90,YELLOW);
            DrawText("RETRY",900,70,50,RED);
            Rectangle rec = {900,50,MeasureText("RETRY",50),90};
            if(CheckCollisionPointRec(GetMousePosition(),rec)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_R)){
                score = 0;
                itoa(score,scoreBox,10);
                xBall = GetRandomValue(200,800);
                yBall = 0;
                speedxBall=7;
                speedyBall=5;
                fps = 20;
                gameover=1;
                SetTargetFPS(fps);
                ClearBackground(RED);
                goto start;
                
            }
        
        }
        // UnloadSound(ball_tap);
        // UnloadSound(ball_wall);
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;

}
