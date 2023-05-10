int LIMITE_X=LARGO/20;
int LIMITE_Y=ANCHO/20;
int DIR = DERECHA;
int TAM=3;
int COMIDA_X,COMIDA_Y;
int PUNTOS=0,VIDAS2=3;
int VEL2=100;
struct Nodo{
    int x,y;
};
struct Nodo cuerpo[LIMITE_NODOS];
void setup(){
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    buffer= create_bitmap(LARGO,ANCHO);
    srand(time(NULL));
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,LARGO,ANCHO,0,0);
    buffer= create_bitmap(LARGO,ANCHO);

    cabeza= create_bitmap(20,20);
    cabeza_up= create_bitmap(20,20);
    cabeza_down= create_bitmap(20,20);
    cabeza_right= create_bitmap(20,20);
    cabeza_left= create_bitmap(20,20);
    nodo_cuerpo= create_bitmap(20,20);
    corazon= create_bitmap(20,20);
    comida= create_bitmap(20,20);
    cabeza_up= load_bitmap("../head_up.bmp",NULL);
    cabeza_down= load_bitmap("../head_down.bmp",NULL);
    cabeza_right= load_bitmap("../head_right.bmp",NULL);
    cabeza_left= load_bitmap("../head_left.bmp",NULL);
    nodo_cuerpo= load_bitmap("../body.bmp",NULL);
    comida= load_bitmap("../apple.bmp",NULL);
    corazon= load_bitmap("../borders.bmp",NULL);
};
void dibujar_bordes(){
    int color= makecol(0,0,255);
    rectfill(buffer,0,ANCHO-20,LARGO,ANCHO,color);
    rectfill(buffer,0,20,20,ANCHO,color);
    rectfill(buffer,0,20,LARGO,20,color);
    rectfill(buffer,LARGO-20,20,LARGO,ANCHO,color);
}
void actualizar_pantalla(){
    blit(buffer,screen,0,0,0,0,LARGO,ANCHO);

}

void generar_snake(){
    cuerpo[0].x=10;
    cuerpo[0].y=9;
    for(int i=1;i<=TAM;i++){
        cuerpo[i].x =cuerpo[0].x - i;
        cuerpo[i].y =cuerpo[0].y;
    }
}
void generar_comida(){
    COMIDA_X=(rand()%(LIMITE_X-2))+1;
    COMIDA_Y=(rand()%(LIMITE_Y-3))+2;
    int c=0;
    while(c<=TAM){
        if(COMIDA_X==cuerpo[c].x&&COMIDA_Y==cuerpo[c].y){
            COMIDA_X=(rand()%(LIMITE_X-2))+1;
            COMIDA_Y=(rand()%(LIMITE_Y-3))+2;
            c=0;
        }
        else{
            c++;
        }

    }

}
void dibujar_comida(){
    draw_sprite(buffer,comida,COMIDA_X*20,COMIDA_Y*20);

}
void dibujar_snake(){

    switch(DIR)
    {
        case ARRiBA:
            blit(cabeza_up,cabeza,0,0,0,0,20,20);
            break;
        case ABAJO:
            blit(cabeza_down,cabeza,0,0,0,0,20,20);
            break;
        case DERECHA:
            blit(cabeza_right,cabeza,0,0,0,0,20,20);
            break;
        case IZQUIERDA:
            blit(cabeza_left,cabeza,0,0,0,0,20,20);
            break;
    }
    draw_sprite(buffer,cabeza,cuerpo[0].x*20,cuerpo[0].y*20);
    for(int i=1;i<=TAM;i++){
        draw_sprite(buffer,nodo_cuerpo,cuerpo[i].x*20,cuerpo[i].y*20);
    }

}
void actualizar_direction(){
    if(key[KEY_UP]){
        if(DIR !=ABAJO){
            DIR=ARRiBA;
        }

    }
    else if(key[KEY_DOWN]){
        if(DIR !=ARRiBA){
            DIR=ABAJO;
        }

    }
    else if(key[KEY_RIGHT]){
        if(DIR !=IZQUIERDA){
            DIR=DERECHA;
        }

    }
    else if(key[KEY_LEFT]){
        if(DIR !=DERECHA){
            DIR=IZQUIERDA;
        }

    }
}
void perder_vida1(){
    VIDAS--;
    if(VIDAS>0){
        clear(screen);
        textout_ex(screen,font,"Has perdido una vida cabron",40*10,40*9,0xFFFFFF,0x00000);
        rest(2000);
    }
    else{
        clear(screen);
        textout_ex(screen,font,"GAME OVER",40*10,40*9,0xFF0000,0x00000);
        rest(4000);
        // exit(0);
    }


}
void mover_snake(){
    for(int i=TAM;i>0;i--){
        cuerpo[i]=cuerpo[i-1];
    }
    switch(DIR){
        case ARRiBA:
            cuerpo[0].y--;
            break;
        case ABAJO:
            cuerpo[0].y++;
            break;
        case DERECHA:
            cuerpo[0].x++;
            break;
        case IZQUIERDA:
            cuerpo[0].x--;
            break;

    }
    if(cuerpo[0].x == COMIDA_X && cuerpo[0].y ==COMIDA_Y){
        generar_comida();
        TAM++;
        cuerpo[TAM]=cuerpo[TAM-1];
        PUNTOS=PUNTOS+10;
        if(PUNTOS%100==0&& PUNTOS>0&&VEL>30){
            VEL-=15;
        }
    }
    if(cuerpo[0].x<1||cuerpo[0].x>(LIMITE_X-2)||cuerpo[0].y<2||cuerpo[0].y>(LIMITE_Y-2)){
        perder_vida1();
        generar_snake();
        DIR=DERECHA;
    }
    for(int i=1;i<=TAM;i++){
        if(cuerpo[0].x==cuerpo[i].x && cuerpo[0].y == cuerpo[i].y){
            perder_vida1();
            generar_snake();
            DIR=DERECHA;
            break;
        }
    }

}
void comenzar_partida1(){
    clear(screen);
    textout_ex(screen,font,"commenzar partida ",40*10,40*9,0xFFFFFF,0x00000);
    rest(2000);

}
void dibujar_puntos(){

    char str_puntos[10];
    sprintf(str_puntos, "%d", PUNTOS);
    textout_ex(buffer, font, str_puntos, 25, 8, 0xFFFFFF, 0x000000);
}
void dibujar_vidas(){
    textout_ex(buffer,font,"VIDAS:",LARGO-120,7,0xFFFFFF,0x000000);
    for(int i=0;i<VIDAS;i++){
        draw_sprite(buffer,corazon,i*20+(LARGO-60),5);
    }
}
void partida_1(){
    while(VIDAS>0){
        clear(buffer);
        actualizar_direction();
        mover_snake();
        dibujar_bordes();
        dibujar_snake();
        dibujar_comida();
        dibujar_puntos();
        dibujar_vidas();
        actualizar_pantalla();
        rest(VEL);
    }


}