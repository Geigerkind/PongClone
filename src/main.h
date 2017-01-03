#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

struct Dim{
  int width, height;
};

struct Object{
  float posx1, posy1, posx2, posy2;
};

struct Player{
  struct Object o;
  int size, lifes, speed, anim;
};

struct Ball{
  struct Object o;
  float speed, angle;
  struct Player *lastHit;
  struct Player *lastGoal;
};

struct Perc{
  struct Object o;
  int spawnat,type,r,g,b;
};

struct Neck{
  struct Object l1;
  struct Object l2;
  struct Object l3;
  struct Object l4;
  struct Object l5;
  struct Object l6;
  struct Object l7;
  struct Object l8;
};

struct Game{
  SDL_Window *window;
  SDL_Renderer *renderer;
  struct Ball b;
  struct Player p1;
  struct Player p2;
  struct Player p3;
  struct Player p4;
  struct Dim dim;
  struct Neck neck;
  int state,player,mode,timestart,timeend,invert;
  struct Perc e1;
  struct Perc e2;
  struct Perc e3;
  struct Perc e4;
  struct Perc e5;
  struct Perc e6;
};

void draw_menu();
void draw_Rules();
void draw_PlayerSelection();
void draw_ModeSelection();
void draw_GameOver();
void move_player(struct Player *p, int dirx, int diry);
void move_Ball();
void change_Ball_Direction(float angle);
float checkCollision(struct Object *o1, struct Object *o2, int flag);
void updateEntities();
void draw_Field(); 
void draw_Game();
void init_Game();
void write_text(SDL_Renderer *renderer, char text, int posx, int posy, int size);
void set_Game_Vars();
void respawn_Ball(struct Player *p);
void spawn_Perc(struct Perc *p);
void despawn_Perc(struct Perc *p);
char* format_Time(int t);
char* get_Ball_Asset();
void draw_Texture(char *path, float *x, float *y);

#endif