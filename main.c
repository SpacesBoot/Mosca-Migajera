#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int crumbs = 0;
int lifetime;
int highscore = 0;

bool are_phone;
Rectangle flym = {500, 205, 150, 150};
Rectangle fly = {0, 0, 25, 25};
float flyr = 0.0f;
Rectangle crumb = {0, 0, 20, 20};
Rectangle hand = {400, 300, 100, 300};

float velocity;

int scene = 4;

void RespawnCrumb() {
    crumb.x = GetRandomValue(0, 800); 
    crumb.y = GetRandomValue(0, 600);
}

void RespawnHand() {
    hand.x = crumb.x;
    hand.y = 350;
}

int main (void) {
    InitWindow(800, 600, "Mosca Migajera");
    SetTargetFPS(60);
    
    Music GameM = LoadMusicStream("game.ogg");
    GameM.looping = true;
    
    Texture2D crumbtexture = LoadTexture("crump.png");
    Texture2D handtexture = LoadTexture("hand.png");

    while (!WindowShouldClose()) {
        UpdateMusicStream(GameM);
        if (scene == 1) {
            PlayMusicStream(GameM);
            lifetime --;
            
            if(highscore > 10 && highscore < 50) {    
                velocity = 3.2f;
            }
            if(highscore > 50 && highscore < 150) {
                velocity = 3.5f;
            }
            if(highscore > 150 && highscore < 270) {
                velocity = 3.8f;
            } 
            if(highscore > 270 && highscore < 300) {
                velocity = 4.5f;
            }
            if(highscore > 350) {
                velocity = 5.2f;
            }
            if(highscore < 10) {
                velocity = 3.0f;
            }
            
            if (IsKeyDown(KEY_D)) {
                fly.x += velocity;
                flyr = 0.0f;
            }
            
            if (IsKeyDown(KEY_A)){
                fly.x -= velocity;
                flyr = 180.0f;
            }
            
            if (IsKeyDown(KEY_W)) {
                fly.y -= velocity;
                flyr = -90.0f;
            }
            
            if (IsKeyDown(KEY_S)) {
                fly.y += velocity;
                flyr = 90.0f;            
            }
            
            if (lifetime < 0) {
                highscore += crumbs;
                crumbs = 0;
                scene = 2;
            }
            
            if(CheckCollisionRecs(fly, crumb)) {
                RespawnCrumb();
                crumbs ++;
            }
            
            if(CheckCollisionRecs(fly, hand)) {
                RespawnHand();
            }
            
            if(!CheckCollisionRecs(fly, hand)) {
                if(hand.y > 0) {
                    if(!CheckCollisionRecs(hand, crumb)) {
                        hand.y --;
                    } else {
                        RespawnCrumb();
                    }
                } else {
                    RespawnHand();
                }
            }
        }
        
        BeginDrawing();
        if (scene == 1) {
            ClearBackground(WHITE);
            DrawTextureEx(crumbtexture, (Vector2){crumb.x, crumb.y}, 0.0, 0.1f, WHITE);
            if(highscore > 10 && highscore < 50) {    
                DrawRectangleRec(fly, BROWN);
            }
            if(highscore > 50 && highscore < 150) {
                DrawRectangleRec(fly, BLUE);
            }
            if(highscore > 150 && highscore < 270) {
                DrawRectangleRec(fly, YELLOW);
            } 
            if(highscore > 270 && highscore < 300) {
                DrawRectangleRec(fly, MAGENTA);
            }
            if(highscore > 350) {
                DrawRectangleRec(fly, RED);
            }
            if(highscore < 10) {
                DrawRectangleRec(fly, BLACK);
            }
            DrawTextureEx(handtexture, (Vector2){hand.x - 5, hand.y}, 0.0f, 0.5f, WHITE);
            
            if (are_phone) {
                if (GuiButton((Rectangle){ 70, 430, 60, 60 }, "W")) {
                    fly.y -= velocity;
                }
                if (GuiButton((Rectangle){ 10, 500, 60, 60 }, "A")) {
                    fly.x -= velocity;
                }
                if (GuiButton((Rectangle){ 70, 500, 60, 60 }, "S")) {
                    fly.y += velocity;
                }
                if (GuiButton((Rectangle){ 130, 500, 60, 60 }, "D")) {
                    fly.x += velocity;
                }
            }
            
            DrawText(TextFormat("Migajas: %d", crumbs), 10, 10, 20, BLACK);
            DrawText(TextFormat("Tiempo de vida: %d", lifetime), 10, 30, 20, BLACK);
        } else if (scene == 0) {
            StopMusicStream(GameM);
            ClearBackground(WHITE);
            DrawText(TextFormat("Maximas Migajas: %d", highscore), 10, 10, 20, BLACK);
            DrawText("MOSCA MIGAJERA", 300, 200, 20, BLACK);
            if (are_phone) {
                if (GuiButton((Rectangle){ 280, 300, 220, 80 }, "Jugar")) {
                    scene = 1;
                }
                
                if (GuiButton((Rectangle){ 280, 420, 220, 80 }, "Vestuario")) {
                    scene = 3;
                }
            } else {
                DrawText("Toca Espacio para jugar", 280, 400, 20, GRAY);
                DrawText("Toca X para ir al vestuario", 280, 500, 20, GRAY);
            }
            
            DrawText("suitscape games 2026 (spacesxd)", 10, 570, 20, GRAY);
            
            if(highscore > 10 && highscore < 50) {    
                lifetime = 900;
            }
            if(highscore > 50 && highscore < 150) {
                lifetime = 900;
            }
            if(highscore > 150 && highscore < 270) {
                lifetime = 930;
            } 
            if(highscore > 270 && highscore < 300) {
                lifetime = 960;
            }
            if(highscore > 350) {
                lifetime = 1200;
            }
            if(highscore < 10) {
                lifetime = 900;
            }
            
            fly.x = 0; fly.y = 0;
            if (IsKeyDown(KEY_SPACE)) scene = 1;
            if (IsKeyDown(KEY_X)) scene = 3;
        } else if (scene == 2) {
            StopMusicStream(GameM);
            ClearBackground(WHITE);
            DrawText(TextFormat("Maximas Migajas: %d", highscore), 10, 10, 20, BLACK);
            DrawText("LLEGO TU HORA COMPA :(", 270, 200, 20, BLACK);
            if (are_phone) {
                if (GuiButton((Rectangle){ 280, 400, 220, 80 }, "Ir al Menu")) {
                    scene = 0;
                }
            } else {
                DrawText("Toca W para ir al Menu", 280, 400, 20, GRAY);
            }
            
            if (IsKeyDown(KEY_W)) scene = 0;
        } else if (scene == 3) {
            StopMusicStream(GameM);
            ClearBackground(WHITE);
            DrawText(TextFormat("Maximas Migajas: %d", highscore), 10, 10, 20, BLACK);
            
            if(highscore > 10 && highscore < 50) {    
                DrawRectangleRec(flym, BROWN);
                DrawText("BRONCE", 155, 200, 50, BROWN);
                DrawText("* ETAPA BRONCE * \n + 0.2 de velocidad \n 40 puntos mas para Diamante", 80, 300, 20, BLACK);
            }
            if(highscore > 50 && highscore < 150) {
                DrawRectangleRec(flym, BLUE);
                DrawText("DIAMANTE", 155, 200, 50, BLUE);
                DrawText("* ETAPA DIAMANTE * \n + 0.5 de velocidad \n 100 puntos mas para Oro", 80, 300, 20, BLACK);
            }
            if(highscore > 150 && highscore < 270) {
                DrawRectangleRec(flym, YELLOW);
                DrawText("ORO", 155, 200, 50, YELLOW);
                DrawText("* ETAPA ORO * \n + 0.8 de velocidad \n + 0.5 minutos de vida \n 120 puntos mas para Ninja", 80, 300, 20, BLACK);
            } 
            if(highscore > 270 && highscore < 300) {
                DrawRectangleRec(flym, MAGENTA);
                DrawText("NINJA", 155, 200, 50, MAGENTA);
                DrawText("* ETAPA NINJA * \n + 1.5 de velocidad \n + 1 minuto de vida\n 50 puntos mas para Leyenda", 80, 300, 20, BLACK);
            }
            if(highscore > 350) {
                DrawRectangleRec(flym, RED);
                DrawText("LEYENDA", 155, 200, 50, RED);
                DrawText("* ETAPA LEYENDA * \n + 2.2 de velocidad \n + 5 minutos de vida\n Gracias Encerio no se como lo hiciste", 80, 300, 20, BLACK);
            }
            if(highscore < 10) {
                DrawRectangleRec(flym, BLACK);
                DrawText("NORMAL", 155, 200, 50, BLACK);
                DrawText("* ETAPA NORMAL * \n 3.0 velocidad base \n eres una mosca normal", 80, 300, 20, BLACK);
            }
            
            if (are_phone) {
                if (GuiButton((Rectangle){ 280, 400, 220, 80 }, "Ir al Menu")) {
                    scene = 0;
                }
            } else {
                DrawText("Toca W para ir al Menu", 280, 400, 20, GRAY);
            }
            
            if (IsKeyDown(KEY_W)) scene = 0;
        } else if (scene == 4) {
            StopMusicStream(GameM);
            
            ClearBackground(WHITE);
            DrawText("Eres de PC o Celular?", 250, 120, 25, BLACK);
            
            if (GuiButton((Rectangle){ 180, 220, 150, 150 }, "PC")) {
                are_phone = false;
                scene = 0;
            }
            if (GuiButton((Rectangle){ 450, 220, 150, 150 }, "CELULAR")) {
                are_phone = true;
                scene = 0;
            }
        }
        EndDrawing();
    }
    
    CloseWindow();
}