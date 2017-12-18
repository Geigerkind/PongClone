#include "main.h"

#define PI 3.14159265358979323
#define FRAMES_PER_SECOND 180
#define TITLE "Pong"
#define SPEED 10
#define BALLSPEED 8

/* GLOBALS */
int frames = 0;
const char wav[5][40] = {
  "../sound/FirstBlood.wav",
  "../sound/DoubleKill.wav",
  "../sound/TrippleKill.wav",
  "../sound/Dominating.wav",
  "../sound/Godlike.wav",
};
char buffer[40];
char cha[10];
struct Game gv;
SDL_Surface * BGsurface = NULL;
/* GLOBALS END */

/* FUNCTION DEFINITION */
/*
* Display functions:
*
*/
void write_Text(SDL_Renderer *renderer, char *text, int posx, int posy, int size){
  int texW = 0;
  int texH = 0;

  TTF_Init();
  TTF_Font * font = TTF_OpenFont("../assets/OpenSans.ttf", size);
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface * surface = TTF_RenderText_Solid(font,
  text, color);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  SDL_Rect dstrect = {posx, posy, texW, texH };

  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
  TTF_Quit();
}

// Not pretty but it works :)
char* format_Time(int t){
  int minutes = t/60;
  int seconds = t%60;
  if (seconds<10) sprintf(cha, "%d:0%d", minutes, seconds);
  else sprintf(cha, "%d:%d", minutes, seconds);
  return cha;
}

/*
* Draws a given texture and positions it.
*/
void draw_Texture(char *path, float *x, float *y){
  int texW,texH;
  SDL_Texture * texture = IMG_LoadTexture(gv.renderer, path);

  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  SDL_Rect dstrect = {*x, *y, texW, texH};

  SDL_RenderCopy(gv.renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
}

/*
* Returns the ball asset depending on the speed
*/
char* get_Ball_Asset(){
  if (gv.b.speed>8) 
    return "../assets/pong4.png";
  if (gv.b.speed>14)
    return "../assets/pong2.png";
  if (gv.b.speed>20)
    return "../assets/pong.png";
  return "../assets/pong3.png";
}

/* Display functions end */
/*
* Menu drawing functions:
* 
* Functions that are defined in order to display different menus
*/
void draw_Menu(){
  // Background animation
  updateEntities();

  SDL_SetRenderDrawColor(gv.renderer, 255, 255, 0, 255);

  draw_Texture(get_Ball_Asset(), &gv.b.o.posx1, &gv.b.o.posy1);

  // Drawing borders
  SDL_RenderDrawLine(gv.renderer, gv.neck.l1.posx1, gv.neck.l1.posy1, gv.neck.l1.posx2, gv.neck.l1.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l2.posx1, gv.neck.l2.posy1, gv.neck.l2.posx2, gv.neck.l2.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l3.posx1, gv.neck.l3.posy1, gv.neck.l3.posx2, gv.neck.l3.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l4.posx1, gv.neck.l4.posy1, gv.neck.l4.posx2, gv.neck.l4.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l5.posx1, gv.neck.l5.posy1, gv.neck.l5.posx2, gv.neck.l5.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l6.posx1, gv.neck.l6.posy1, gv.neck.l6.posx2, gv.neck.l6.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l7.posx1, gv.neck.l7.posy1, gv.neck.l7.posx2, gv.neck.l7.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l8.posx1, gv.neck.l8.posy1, gv.neck.l8.posx2, gv.neck.l8.posy2);

  SDL_SetRenderDrawColor(gv.renderer, 0, 0, 0, 255);

  // Menu points
  int center = gv.dim.width/2-180;
  int fontsize = 30;
  int startheight = 230;

  write_Text(gv.renderer, "Pong", center+25, startheight-180, 120);
  write_Text(gv.renderer, "Press G to start the game", center, startheight, fontsize);
  write_Text(gv.renderer, "Press P to select the player", center, startheight+fontsize, fontsize);
  write_Text(gv.renderer, "Press M to select the mode", center, startheight+2*fontsize, fontsize);
  write_Text(gv.renderer, "Press R to read the rules", center, startheight+3*fontsize, fontsize);
  write_Text(gv.renderer, "Press Q to quit the game", center, startheight+4*fontsize, fontsize);
}

void draw_PlayerSelection(){
  write_Text(gv.renderer, "Select a the amount of player:", 20, 20, 20);
  write_Text(gv.renderer, "1. Two player", 20, 50, 20);
  write_Text(gv.renderer, "2. Three player", 20, 70, 20);
  write_Text(gv.renderer, "3. Four player", 20, 90, 20);
  write_Text(gv.renderer, "Player 1 - Blue:    Up: Arrow-Left", 20, 120, 20);
  write_Text(gv.renderer, "                          Down: Arrow-Right", 18, 140, 20);
  write_Text(gv.renderer, "Player 2 - Red:     Up: A", 20, 170, 20);
  write_Text(gv.renderer, "                        Down: D", 26, 190, 20);
  write_Text(gv.renderer, "Player 3 - Green: Up: U", 20, 220, 20);
  write_Text(gv.renderer, "                         Down: O", 25, 240, 20);
  write_Text(gv.renderer, "Player 4 - Purple: Up: G", 20, 270, 20);
  write_Text(gv.renderer, "                          Down: J", 21, 290, 20);
  write_Text(gv.renderer, "Press ESC to go back.", 20, 534, 20);
}

void draw_ModeSelection(){
  write_Text(gv.renderer, "Select a mode:", 20, 20, 20);
  write_Text(gv.renderer, "1. Time-Pong: You will play 5 minutes and whoever has the", 20, 50, 20);
  write_Text(gv.renderer, "most points will loose.", 20, 70, 20);
  write_Text(gv.renderer, "2. Classic-Pong: Everyone has 10 lifes. Whoever drops to 0", 20, 100, 20);
  write_Text(gv.renderer, "first, will loose.", 20, 120, 20);
  write_Text(gv.renderer, "Press ESC to go back.", 20, 534, 20);
}

void draw_Rules(){
  write_Text(gv.renderer, "Every player has a set amount of lifes. Drops one to zero,", 20, 20, 20);
  write_Text(gv.renderer, "wins the other.", 20, 40, 20);
  write_Text(gv.renderer, "The speed of the ball increases over time.", 20, 75, 20);
  write_Text(gv.renderer, "There are different modifiers that spawn during the game:", 20, 110, 20);
  write_Text(gv.renderer, "Red: Modify the speed of the ball.", 20, 145, 20);
  write_Text(gv.renderer, "Green: Modify the speed of the player, who reflected the ball last.", 20, 170, 20);
  write_Text(gv.renderer, "Blue: Modify the size of the player, who reflected the ball last.", 20, 195, 20);
  write_Text(gv.renderer, "Yellow: Inverts the controls.", 20, 220, 20);
  write_Text(gv.renderer, "Turquoise: A barrier on the field.", 20, 245, 20);
  write_Text(gv.renderer, "Purple: Randomized change of the direction of the ball.", 20, 270, 20);
  write_Text(gv.renderer, "Press ESC to go back.", 20, 534, 20);
}
/* Menu functions end */

/* 
* Game drawing functions
*
*/

/*
* Attempts to spawn a perc if the time allows.
* Attempts to create a random position.
* Colors it appropriataly.
*/
void spawn_Perc(struct Perc *p){
  int t = time(0);
  if (p->spawnat<=t){
    if (p->o.posx1<=0 || (p->spawnat+20)<=t){
      int x,y;
      x = 80 + (rand()%904);
      y = 100 + (rand()%384);
      p->o.posx1 = x;
      p->o.posx2 = x+20;
      p->o.posy1 = y;
      p->o.posy2 = y+20;
    }
    if ((p->spawnat+20)<=t){
      p->spawnat += 20;
    }
    sprintf(buffer, "../assets/perc%d.png", p->type);
    draw_Texture(buffer, &p->o.posx1, &p->o.posy1);
  }
}

/*
* Sets a new random spawn time.
* Resets the position.
*/
void despawn_Perc(struct Perc *p){
  p->spawnat = time(0)+20 + rand()%80;
  p->o.posx1 = -100;
  p->o.posy1 = -100;
  p->o.posx2 = -100;
  p->o.posy2 = -100;
}

/*
* Draws the Game-Over screen
* Evaluates the winner.
*/
void draw_GameOver(){
  sprintf(buffer, "Time played: %s", format_Time(gv.timeend-gv.timestart));
  write_Text(gv.renderer, "Game over", gv.dim.width/2-120, 20, 50);
  write_Text(gv.renderer, buffer, 20, 85, 25);
  write_Text(gv.renderer, "Press ESC to go back.", 20, 534, 20);

  if (gv.mode){
    if (gv.p1.lifes>0) write_Text(gv.renderer, "BLUE WINS!", 20, 150, 90);
    else if (gv.p2.lifes>0) write_Text(gv.renderer, "RED WINS!", 20, 150, 90);
    else if (gv.p3.lifes>0) write_Text(gv.renderer, "GREEN WINS!", 20, 150, 90);
    else write_Text(gv.renderer, "PURPLE WINS!", 20, 150, 90);
  }else{
    char winner[4][15] = {
      "BLUE WINS!",
      "RED WINS!",
      "GREEN WINS!",
      "PURPLE WINS!",
    };
    int least = -1; int leastnum = 0;
    if (least==-1 || gv.p1.lifes<least){least=gv.p1.lifes; leastnum=0;}
    if (least==-1 || gv.p2.lifes<least){least=gv.p2.lifes; leastnum=1;}
    if (gv.player>2)
      if (least==-1 || gv.p3.lifes<least){least=gv.p3.lifes; leastnum=2;}
    if (gv.player>3)
      if (least==-1 || gv.p4.lifes<least){least=gv.p4.lifes; leastnum=3;}
    write_Text(gv.renderer, winner[leastnum], 20, 150, 90);
  }
}

/*
* Draws the gamefield depending on players and mode.
* Aborts depending on mode.
*/
void draw_Field(){
  int count = 0;
  updateEntities();
  SDL_Rect r1; r1.x=-100; r1.y=-100; r1.w = 0; r1.h = 0;
  SDL_Rect r2; r2.x=-100; r2.y=-100; r2.w = 0; r2.h = 0;
  SDL_Rect r5; r5.x=-100; r5.y=-100; r5.w = 0; r5.h = 0;
  SDL_Rect r4; r4.x=-100; r4.y=-100; r4.w = 0; r4.h = 0;
  if ((gv.mode && gv.p1.lifes>0) || !gv.mode){ r1.x = gv.p1.o.posx1; r1.y = gv.p1.o.posy1; r1.w = gv.p1.o.posx2-gv.p1.o.posx1; r1.h = gv.p1.o.posy2-gv.p1.o.posy1;}
  if ((gv.mode && gv.p2.lifes>0) || !gv.mode){ r2.x = gv.p2.o.posx1; r2.y = gv.p2.o.posy1; r2.w = gv.p2.o.posx2-gv.p2.o.posx1; r2.h = gv.p2.o.posy2-gv.p2.o.posy1;}
  if ((gv.mode && gv.p3.lifes>0) || !gv.mode){ r4.x = gv.p3.o.posx1; r4.y = gv.p3.o.posy1; r4.w = gv.p3.o.posx2-gv.p3.o.posx1-5; r4.h = gv.p3.o.posy2-gv.p3.o.posy1;}
  if ((gv.mode && gv.p4.lifes>0) || !gv.mode){ r5.x = gv.p4.o.posx1; r5.y = gv.p4.o.posy1; r5.w = gv.p4.o.posx2-gv.p4.o.posx1-5; r5.h = gv.p4.o.posy2-gv.p4.o.posy1;}
  
  // Drawing the framework
  SDL_SetRenderDrawColor(gv.renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(gv.renderer, &r1);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l4.posx1, gv.neck.l4.posy1, gv.neck.l4.posx2, gv.neck.l4.posy2);
  SDL_SetRenderDrawColor(gv.renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(gv.renderer, &r2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l2.posx1, gv.neck.l2.posy1, gv.neck.l2.posx2, gv.neck.l2.posy2);
  SDL_SetRenderDrawColor(gv.renderer, 0, 255, 0, 255);
  SDL_RenderFillRect(gv.renderer, &r4);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l6.posx1, gv.neck.l6.posy1, gv.neck.l6.posx2, gv.neck.l6.posy2);
  SDL_SetRenderDrawColor(gv.renderer, 255, 0, 255, 255);
  SDL_RenderFillRect(gv.renderer, &r5);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l8.posx1, gv.neck.l8.posy1, gv.neck.l8.posx2, gv.neck.l8.posy2);

  draw_Texture(get_Ball_Asset(), &gv.b.o.posx1, &gv.b.o.posy1);

  SDL_SetRenderDrawColor(gv.renderer, 255, 255, 0, 255);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l1.posx1, gv.neck.l1.posy1, gv.neck.l1.posx2, gv.neck.l1.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l3.posx1, gv.neck.l3.posy1, gv.neck.l3.posx2, gv.neck.l3.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l5.posx1, gv.neck.l5.posy1, gv.neck.l5.posx2, gv.neck.l5.posy2);
  SDL_RenderDrawLine(gv.renderer, gv.neck.l7.posx1, gv.neck.l7.posy1, gv.neck.l7.posx2, gv.neck.l7.posy2);
  // Drawing Text
  if (gv.mode){
    // checking for game over
    if (gv.p1.lifes>0) count++;
    if (gv.p2.lifes>0) count++;
    if (gv.p3.lifes>0) count++;
    if (gv.p4.lifes>0) count++;
    if (count==1){ gv.timeend = time(0); gv.state = 5;}
    write_Text(gv.renderer, "Mode: Classic-Pong", 20, 5, 20);
  }else{
    // checking for game over
    int t = time(0);
    if ((gv.timestart+300)-t<=0){ gv.timeend = t; gv.state = 5;}
    sprintf(buffer, "Mode: Time-Pong - %s", format_Time(gv.timestart+300-t));
    write_Text(gv.renderer, buffer, 20, 5, 20);
  }
  sprintf(buffer, "Blue: %d", gv.p1.lifes);
  write_Text(gv.renderer, buffer, 20, 25, 20);
  sprintf(buffer, "Red: %d", gv.p2.lifes);
  write_Text(gv.renderer, buffer, 120, 25, 20);
  if (gv.player>2){ 
    sprintf(buffer, "Green: %d", gv.p3.lifes);
    write_Text(gv.renderer, buffer, 220, 25, 20);
  }
  if (gv.player>3){
    sprintf(buffer, "Purple: %d", gv.p4.lifes);
    write_Text(gv.renderer, buffer, 340, 25, 20);
  }
  write_Text(gv.renderer, "Press ESC to go back", 824, 5, 20);

  // Drawing percs
  spawn_Perc(&gv.e1);
  spawn_Perc(&gv.e2);
  spawn_Perc(&gv.e3);
  spawn_Perc(&gv.e4);
  spawn_Perc(&gv.e5);
  spawn_Perc(&gv.e6);
}
/* Game drawing functions end */

/*
* Phyiscs
*
*/
/*
* Checks if two objects intersect. 
* Flag=0: Checks if two rectangles intersect.
* Flag=1: Checks if a rectangle intersect with a line.
*/
float checkCollision(struct Object *o1, struct Object *o2, int flag){
  int left, right, top, bottom;
  left = o2->posx1;
  right = o2->posx2;
  top = o2->posy1;
  bottom = o2->posy2;
  SDL_Rect r1; r1.x = o1->posx1; r1.y = o1->posy1; r1.w = o1->posx2-o1->posx1; r1.h = o1->posy2-o1->posy1;
  if (flag==1){
    if (SDL_IntersectRectAndLine(&r1, &left, &top, &right, &bottom))
      return acos((-(o2->posy2-o2->posy1))/sqrt(((o2->posx2-o2->posx1)*(o2->posx2-o2->posx1)) + ((o2->posy2-o2->posy1)*(o2->posy2-o2->posy1))));
    return 999;
  }
  if (SDL_IntersectRectAndLine(&r1, &left, &top, &left, &bottom))
    return acos(((o2->posy2-o2->posy1))/sqrt(((o2->posy2-o2->posy1)*(o2->posy2-o2->posy1))));
  if (SDL_IntersectRectAndLine(&r1, &right, &top, &right, &bottom))
    return acos(((o2->posy2-o2->posy1))/sqrt(((o2->posy2-o2->posy1)*(o2->posy2-o2->posy1))));
  if (SDL_IntersectRectAndLine(&r1, &left, &top, &right, &top))
    return 0.5*PI;
  if (SDL_IntersectRectAndLine(&r1, &left, &bottom, &right, &bottom))
    return 0.5*PI;
  if (flag==2)
    return 999;
  return checkCollision(o2, o1, 2);
}

/*
* Changes the ball direction relative to the hit angle of the object.
*/
void change_Ball_Direction(float angle){
  if (angle<360){
    angle = angle*180/PI;
    gv.b.angle = (2*angle-gv.b.angle);
  }
}

/*
* Updates the position of the ball object.
* Calls collision checks with all necessarry objects and calls needed events for:
* Percs - Do something if a perc object is being hit
* Player-"Goals": Respawn the ball, play sound and manage points.
* Change the Direction if it is some kind of border.
*/
void move_Ball(){
  float colangle;
  if ((colangle = checkCollision(&gv.b.o, &gv.p1.o, 0))<360){
    gv.b.lastHit = &gv.p1;
    change_Ball_Direction(colangle);
  }
  if ((colangle = checkCollision(&gv.b.o, &gv.p2.o, 0))<360){
    gv.b.lastHit = &gv.p2;
    change_Ball_Direction(colangle);
  }
  if ((colangle = checkCollision(&gv.b.o, &gv.p3.o, 0))<360){
    gv.b.lastHit = &gv.p3;
    change_Ball_Direction(colangle);
  }
  if ((colangle = checkCollision(&gv.b.o, &gv.p4.o, 0))<360){
    gv.b.lastHit = &gv.p4;
    change_Ball_Direction(colangle);
  }
  change_Ball_Direction(checkCollision(&gv.b.o, &gv.neck.l1, 1));
  change_Ball_Direction(checkCollision(&gv.b.o, &gv.neck.l3, 1));
  change_Ball_Direction(checkCollision(&gv.b.o, &gv.neck.l5, 1));
  change_Ball_Direction(checkCollision(&gv.b.o, &gv.neck.l7, 1));
  if (checkCollision(&gv.b.o, &gv.neck.l2, 1)<360){
    if ((gv.p2.lifes>0 || !gv.mode) && gv.state==1) respawn_Ball(&gv.p2);
    else change_Ball_Direction(0);
  }
  if (checkCollision(&gv.b.o, &gv.neck.l4, 1)<360){
    if ((gv.p1.lifes>0 || !gv.mode) && gv.state==1) respawn_Ball(&gv.p1);
    else change_Ball_Direction(0);
  }
  if ((colangle = checkCollision(&gv.b.o, &gv.neck.l6, 1))<360){
    if ((gv.p3.lifes>0 || (!gv.mode && gv.player>2)) && gv.state==1) respawn_Ball(&gv.p3);
    else change_Ball_Direction(colangle);
  }
  if ((colangle = checkCollision(&gv.b.o, &gv.neck.l8, 1))<360){
    if ((gv.p4.lifes>0 || (!gv.mode && gv.player>3)) && gv.state==1) respawn_Ball(&gv.p4);
    else change_Ball_Direction(colangle);
  }

  // Perc collosion
  if (checkCollision(&gv.b.o, &gv.e1.o, 0)<360){
    int *sign = malloc(16);
    sign[0] = 1;
    sign[1] = -1;
    if (gv.b.speed>1) gv.b.speed += sign[rand()%2]*2;
    else gv.b.speed += 2;
    free(sign);
    despawn_Perc(&gv.e1);
  }
  if (checkCollision(&gv.b.o, &gv.e2.o, 0)<360){
    if (gv.b.lastHit != NULL){
      int *sign = malloc(16);
      sign[0] = 1;
      sign[1] = -1;
      if (gv.b.lastHit->speed>2) gv.b.lastHit->speed += sign[rand()%2]*2;
      else gv.b.lastHit->speed += 2;
      free(sign);
      despawn_Perc(&gv.e2);
    }
  }
  if (checkCollision(&gv.b.o, &gv.e3.o, 0)<360){
    if (gv.b.lastHit != NULL){
      int *sign = malloc(16);
      sign[0] = 1;
      sign[1] = -1;
      if (gv.b.lastHit->size>10) gv.b.lastHit->size += sign[rand()%2]*40;
      else gv.b.lastHit->size += 40;
      free(sign);
      despawn_Perc(&gv.e3);
    }
  }
  if (checkCollision(&gv.b.o, &gv.e4.o, 0)<360){
    gv.invert = -gv.invert;
    despawn_Perc(&gv.e4);
  }
  change_Ball_Direction(checkCollision(&gv.b.o, &gv.e5.o, 0));
  if (checkCollision(&gv.b.o, &gv.e6.o, 0)<360){
    gv.b.angle = rand()%360;
    despawn_Perc(&gv.e6);
  }


  float radian = gv.b.angle*PI/180;
  gv.b.o.posx1 += sin(radian);
  gv.b.o.posy1 += -cos(radian);
  gv.b.o.posx2 += sin(radian);
  gv.b.o.posy2 += -cos(radian);

  if (frames>=2*FRAMES_PER_SECOND){
    frames = 0;
    if (gv.b.speed<26)
      gv.b.speed += 1;
  }

  // Hack incase it flies of through the borders
  if (gv.b.o.posx1<0 || gv.b.o.posx1>gv.dim.width || gv.b.o.posy1<0 || gv.b.o.posy1>gv.dim.height)
    respawn_Ball(0);
}
/* Physics end */

/* 
* General functions
*
*/
/*
* Updates the player position if possible.
*/
void move_Player(struct Player *p, int dirx, int diry){
  p->o.posy1 += diry;
  p->o.posy2 += diry;
  p->o.posx1 += dirx;
  p->o.posx2 += dirx;
  if ((checkCollision(&p->o, &gv.neck.l1, 1)<360) || (checkCollision(&p->o, &gv.neck.l3, 1)<360) || (checkCollision(&p->o, &gv.neck.l5, 1)<360) || (checkCollision(&p->o, &gv.neck.l7, 1)<360) || (checkCollision(&p->o, &gv.b.o, 0)<360)){
    p->o.posy1 -= diry;
    p->o.posy2 -= diry;
    p->o.posx1 -= dirx;
    p->o.posx2 -= dirx;
  }
}

/*
* Respawns the ball at a random angle.
* Plays a sound if a "goal" was hit.
* Manages lifes of the players.
*/
void respawn_Ball(struct Player *p){
  if (p != NULL){
    if (gv.b.lastHit!=gv.lastGoal) gv.lastGoal = gv.b.lastHit;
    if (gv.lastGoal != NULL){
      playSound(wav[gv.lastGoal->anim], SDL_MIX_MAXVOLUME / 2);
      if (gv.lastGoal->anim<4) gv.lastGoal->anim++;
    }else{
      playSound(wav[0], SDL_MIX_MAXVOLUME / 2);
    }
    if (gv.mode) p->lifes--;
    else p->lifes++;
  }
  gv.b = (struct Ball){
    .o = (struct Object){.posx1 = 315,.posy1 = 260,.posx2 = 335,.posy2 = 280,},
    .speed = BALLSPEED, .angle = rand()%360, .lastHit = NULL
  };
}

/*
* Calls all Entities.
* Calls move_Ball and move_Player for each player depending on the orientation.
*/
void updateEntities(){
  const Uint8 *ksa = SDL_GetKeyboardState(NULL);

  // Adjusting playersize
  gv.p1.o.posy2 = gv.p1.o.posy1+gv.p1.size;
  gv.p2.o.posy2 = gv.p2.o.posy1+gv.p2.size;
  gv.p3.o.posx2 = gv.p3.o.posx1+gv.p3.size;
  gv.p4.o.posx2 = gv.p4.o.posx1+gv.p4.size;

  for (int i=0; i<gv.b.speed; i++) move_Ball();

  if (gv.invert==1){
    if (ksa[SDL_SCANCODE_RIGHT]) move_Player(&gv.p1, 0, gv.p1.speed);
    if (ksa[SDL_SCANCODE_LEFT]) move_Player(&gv.p1, 0, -gv.p1.speed);

    if (ksa[SDL_SCANCODE_A]) move_Player(&gv.p2, 0, gv.p2.speed);
    if (ksa[SDL_SCANCODE_D]) move_Player(&gv.p2, 0, -gv.p2.speed);

    if (ksa[SDL_SCANCODE_O]) move_Player(&gv.p3, gv.p3.speed, 0);
    if (ksa[SDL_SCANCODE_U]) move_Player(&gv.p3, -gv.p3.speed, 0);

    if (ksa[SDL_SCANCODE_J]) move_Player(&gv.p4, gv.p4.speed, 0);
    if (ksa[SDL_SCANCODE_G]) move_Player(&gv.p4, -gv.p4.speed, 0);
  }else{
    if (ksa[SDL_SCANCODE_LEFT]) move_Player(&gv.p1, 0, gv.p1.speed);
    if (ksa[SDL_SCANCODE_RIGHT]) move_Player(&gv.p1, 0, -gv.p1.speed);

    if (ksa[SDL_SCANCODE_D]) move_Player(&gv.p2, 0, gv.p2.speed);
    if (ksa[SDL_SCANCODE_A]) move_Player(&gv.p2, 0, -gv.p2.speed);

    if (ksa[SDL_SCANCODE_U]) move_Player(&gv.p3, gv.p3.speed, 0);
    if (ksa[SDL_SCANCODE_O]) move_Player(&gv.p3, -gv.p3.speed, 0);

    if (ksa[SDL_SCANCODE_G]) move_Player(&gv.p4, gv.p4.speed, 0);
    if (ksa[SDL_SCANCODE_J]) move_Player(&gv.p4, -gv.p4.speed, 0);
  }
}

/*
* Main update function:
* Handles all keyboard events
* Draws game or menu depending on the state
* Counts frames.
*/
void draw_Game(){
  SDL_SetRenderDrawColor(gv.renderer, 0, 0, 0, 255); // Background color
  while (1) {
      SDL_Delay(1000/FRAMES_PER_SECOND);
      SDL_Event e;
      if (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) break;
          if (e.type == SDL_KEYDOWN){
            if (!gv.state){
              if (e.key.keysym.sym == SDLK_g){
                gv.state = 1;
                gv.timestart = time(0);
                set_Game_Vars();
              }
              if (e.key.keysym.sym == SDLK_p) gv.state = 2;
              if (e.key.keysym.sym == SDLK_m) gv.state = 3;
              if (e.key.keysym.sym == SDLK_r) gv.state = 4;
              if (e.key.keysym.sym == SDLK_q) break;
            }else if(gv.state==2){
              if (e.key.keysym.sym == SDLK_1){
                gv.player = 2;
                gv.state = 0;
                set_Game_Vars();
              }
              if (e.key.keysym.sym == SDLK_2){
                gv.player = 3;
                gv.state = 0;
                set_Game_Vars();
              }
              if (e.key.keysym.sym == SDLK_3){
                gv.player = 4;
                gv.state = 0;
                set_Game_Vars();
              }
            }else if(gv.state==3){
              if (e.key.keysym.sym == SDLK_1){
                gv.mode = 0;
                gv.state = 0;
                set_Game_Vars();
              }
              if (e.key.keysym.sym == SDLK_2){
                gv.mode = 1;
                gv.state = 0;
                set_Game_Vars();
              }
            }
            if (e.key.keysym.sym == SDLK_ESCAPE){
              gv.state = 0;
              set_Game_Vars();
            }
          }
      }
      SDL_RenderClear(gv.renderer);

      // Render background
      //SDL_Surface * surface = IMG_Load("../assets/background.jpg");
      SDL_Texture * texture = SDL_CreateTextureFromSurface(gv.renderer, BGsurface);

      SDL_RenderCopy(gv.renderer, texture, NULL, NULL);
      SDL_DestroyTexture(texture);
      //SDL_FreeSurface(surface);

      switch(gv.state){
        case 1:
          draw_Field();
          break;
        case 2:
          draw_PlayerSelection();
          break;
        case 3:
          draw_ModeSelection();
          break;
        case 4:
          draw_Rules();
          break;
        case 5:
          draw_GameOver();
          break;
        default :
          draw_Menu();
          break;
      }
      SDL_RenderPresent(gv.renderer);
      frames += 1;
  }

  SDL_DestroyRenderer(gv.renderer);
}

/*
* Sets all game variables depending on the mode, playeramount and state
* Sets the position of the borders and players
* Resets speed, lifes and orientation
* Sets first spawntimers for percs.
*/
// 680 -> 1024
// 344-46
// 298
// 149
// 195
// 347-50 = 294
// 105 + 147 = 252
void set_Game_Vars(){
  gv.invert = 1;
  gv.lastGoal = NULL;
  switch(gv.player){
    case 3 :
      gv.p1 = (struct Player){
        .o = (struct Object){.posx1 = 50,.posy1 = 252,.posx2 = 70,.posy2 = 302,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.p2 = (struct Player){
        .o = (struct Object){.posx1 = 952,.posy1 = 252,.posx2 = 972,.posy2 = 302,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.p3 = (struct Player){
        .o = (struct Object){.posx1 = 468,.posy1 = 80,.posx2 = 523,.posy2 = 100,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.p4 = (struct Player){
        .o = (struct Object){.posx1 = 0,.posy1 = 0,.posx2 = 0,.posy2 = 0,},
        .size = 50, .lifes = 0, .speed = SPEED, .anim = 0
      };
      gv.neck = (struct Neck){
        .l1 = (struct Object){.posx1 = 20,.posy1 = 105,.posx2 = 319,.posy2 = 50},
        .l2 = (struct Object){.posx1 = 1004,.posy1 = 105,.posx2 = 1004,.posy2 = 452},
        .l3 = (struct Object){.posx1 = 665,.posy1 = 50,.posx2 = 1004,.posy2 = 105},
        .l4 = (struct Object){.posx1 = 20,.posy1 = 105,.posx2 = 20,.posy2 = 452},
        .l5 = (struct Object){.posx1 = 665,.posy1 = 554,.posx2 = 1004,.posy2 = 452},
        .l6 = (struct Object){.posx1 = 319,.posy1 = 50,.posx2 = 665,.posy2 = 50},
        .l7 = (struct Object){.posx1 = 20,.posy1 = 452,.posx2 = 319,.posy2 = 554},
        .l8 = (struct Object){.posx1 = 319,.posy1 = 554,.posx2 = 665,.posy2 = 554}
      };
      break;
    case 4: 
      gv.p1 = (struct Player){
        .o = (struct Object){.posx1 = 50,.posy1 = 252,.posx2 = 70,.posy2 = 302,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.p2 = (struct Player){
        .o = (struct Object){.posx1 = 952,.posy1 = 252,.posx2 = 972,.posy2 = 302,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.p3 = (struct Player){
        .o = (struct Object){.posx1 = 468,.posy1 = 80,.posx2 = 523,.posy2 = 100,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.p4 = (struct Player){
        .o = (struct Object){.posx1 = 468,.posy1 = 504,.posx2 = 523,.posy2 = 524,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.neck = (struct Neck){
        .l1 = (struct Object){.posx1 = 20,.posy1 = 105,.posx2 = 319,.posy2 = 50},
        .l2 = (struct Object){.posx1 = 1004,.posy1 = 105,.posx2 = 1004,.posy2 = 452},
        .l3 = (struct Object){.posx1 = 665,.posy1 = 50,.posx2 = 1004,.posy2 = 105},
        .l4 = (struct Object){.posx1 = 20,.posy1 = 105,.posx2 = 20,.posy2 = 452},
        .l5 = (struct Object){.posx1 = 665,.posy1 = 554,.posx2 = 1004,.posy2 = 452},
        .l6 = (struct Object){.posx1 = 319,.posy1 = 50,.posx2 = 665,.posy2 = 50},
        .l7 = (struct Object){.posx1 = 20,.posy1 = 452,.posx2 = 319,.posy2 = 554},
        .l8 = (struct Object){.posx1 = 319,.posy1 = 554,.posx2 = 665,.posy2 = 554}
      };
      break;
    default :
      gv.p1 = (struct Player){
        .o = (struct Object){.posx1 = 50,.posy1 = 277,.posx2 = 70,.posy2 = 327,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.p2 = (struct Player){
        .o = (struct Object){.posx1 = 954,.posy1 = 277,.posx2 = 974,.posy2 = 327,},
        .size = 50, .lifes = gv.mode*10, .speed = SPEED, .anim = 0
      };
      gv.p3 = (struct Player){
        .o = (struct Object){.posx1 = 0,.posy1 = 0,.posx2 = 0,.posy2 = 0,},
        .size = 50, .lifes = 0, .speed = SPEED, .anim = 0
      };
      gv.p4 = (struct Player){
        .o = (struct Object){.posx1 = 0,.posy1 = 0,.posx2 = 0,.posy2 = 0,},
        .size = 50, .lifes = 0, .speed = SPEED, .anim = 0
      };
      gv.neck = (struct Neck){
        .l1 = (struct Object){.posx1 = 20,.posy1 = 50,.posx2 = 1004,.posy2 = 50},
        .l2 = (struct Object){.posx1 = 1004,.posy1 = 50,.posx2 = 1004,.posy2 = 554},
        .l3 = (struct Object){.posx1 = 20,.posy1 = 554,.posx2 = 1004,.posy2 = 554},
        .l4 = (struct Object){.posx1 = 20,.posy1 = 554,.posx2 = 20,.posy2 = 50},
        .l5 = (struct Object){.posx1 = 0,.posy1 = 0,.posx2 = 0,.posy2 = 0},
        .l6 = (struct Object){.posx1 = 0,.posy1 = 0,.posx2 = 0,.posy2 = 0},
        .l7 = (struct Object){.posx1 = 0,.posy1 = 0,.posx2 = 0,.posy2 = 0},
        .l8 = (struct Object){.posx1 = 0,.posy1 = 0,.posx2 = 0,.posy2 = 0}
      };
      break;
  }

  respawn_Ball(NULL);
  if (!gv.state){
    gv.p1 = (struct Player){
      .o = (struct Object){.posx1 = -100,.posy1 = -100,.posx2 = 0,.posy2 = 0,},
      .size = 0, .lifes = 0, .speed = SPEED
    };
    gv.p2 = (struct Player){
      .o = (struct Object){.posx1 = -100,.posy1 = -100,.posx2 = 0,.posy2 = 0,},
      .size = 0, .lifes = 0, .speed = SPEED
    };
    gv.p3 = (struct Player){
      .o = (struct Object){.posx1 = -100,.posy1 = -100,.posx2 = 0,.posy2 = 0,},
      .size = 0, .lifes = 0, .speed = SPEED
    };
    gv.p4 = (struct Player){
      .o = (struct Object){.posx1 = -100,.posy1 = -100,.posx2 = 0,.posy2 = 0,},
      .size = 0, .lifes = 0, .speed = SPEED
    };
  }else{
    despawn_Perc(&gv.e1);
    despawn_Perc(&gv.e2);
    despawn_Perc(&gv.e3);
    despawn_Perc(&gv.e4);
    despawn_Perc(&gv.e5);
    despawn_Perc(&gv.e6);
  }
}

/*
* Initialises the game
* Starts the SDL engine
* Starts the audio engine
* Starts the background music
* Starts draw_Game method
* Terminates SDL and audio engine
*/
void init_Game(){
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    initAudio();
    playMusic("../sound/song.wav", SDL_MIX_MAXVOLUME/2);
    gv.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, gv.dim.width, gv.dim.height,
      SDL_WINDOW_SHOWN);
    if (gv.window) {  
      SDL_SetWindowIcon(gv.window, IMG_Load("../assets/pong.png"));
	    BGsurface = IMG_Load("../assets/background.jpg");
      gv.renderer = SDL_CreateRenderer(gv.window, -1,
        SDL_RENDERER_ACCELERATED);
      if (gv.renderer) {
        draw_Game();
        return;
      }
	    SDL_FreeSurface(BGsurface);
      SDL_DestroyWindow(gv.window);
    }
    endAudio();
    SDL_Quit();
  }
}

/*
* Initialises the Game struct and starts the game.
*/
int main(int argc, char* args[]){
  gv.state = 0;
  gv.player = 2;
  gv.mode = 1;
  gv.invert = 1;
  gv.dim = (struct Dim){
    .width = 1024,.height = 576
  };
  gv.e1.type = 1; gv.e1.r = 255; gv.e1.g = 0; gv.e1.b = 0;
  gv.e2.type = 2; gv.e2.r = 0; gv.e2.g = 255; gv.e2.b = 0;
  gv.e3.type = 3; gv.e3.r = 0; gv.e3.g = 0; gv.e3.b = 255;
  gv.e4.type = 4; gv.e4.r = 255; gv.e4.g = 255; gv.e4.b = 0;
  gv.e5.type = 5; gv.e5.r = 0; gv.e5.g = 255; gv.e5.b = 255;
  gv.e6.type = 6; gv.e6.r = 255; gv.e6.g = 255; gv.e6.b = 255;

  set_Game_Vars();
  init_Game();
  return 0;
}
/* General functions end */
/* FUNCTION DEFINITION END */
