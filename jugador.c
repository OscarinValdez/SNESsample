#include <snes.h>
#include "nivel1.h"
#include "enemigos.h"

extern u16 gravedad;
extern u16 showx;

u16 plx,ply, plvy;
u16 dir;
u16 pad0;
u16 framecount,frameID;

const char sprTiles[]=
{
    0,2,
	4,6,
	0,2,
	8,10,
	12,14
}; 

void iniciarJugador()
{
	plx=10; ply=100; plvy=0;
};

void actualizarJugador()
{
	pad0 = padsCurrent(0);
	
	if (pad0)
	{

        if(pad0 & KEY_LEFT)
		{   
		    if(Nivel1_map[((ply>>4)*32) + ((plx>>4)&159)]<5
			&& Nivel1_map[(((ply+16)>>4)*32) + ((plx>>4)&159)]<5)
			--plx;
			
			dir=1;
			
			framecount++;
			frameID=(((framecount>>3)&1)<<1)+2;
        }

        if(pad0 & KEY_RIGHT)
		{
            if(Nivel1_map[((ply>>4)*32) + (((plx>>4)+1)&159)]<5
			&& Nivel1_map[(((ply+16)>>4)*32) + (((plx>>4)+1)&159)]<5)	
			++plx;
			
			dir=0;   
			
			framecount++;
			frameID=(((framecount>>3)&1)<<1)+2;
        }
		
		if(pad0 & KEY_UP)
		{   
			--ply;
        }

        if(pad0 & KEY_DOWN)
		{
			++ply;
        }
		
	} else { framecount=0; frameID=0; }
	
	if ( Nivel1_map[(((ply+32)>>4)*32) + ((plx>>4)&159)]>=5
	||   Nivel1_map[(((ply+32)>>4)*32) + (((plx>>4)+1)&159)]>=5)
	{
		plvy=0; ply=((ply>>4)<<4);
	}
	
	++plvy;
	ply+=plvy;
	
	if (plvy>gravedad) plvy=gravedad;
	
	if(padsDown(0) & KEY_B)
	{
		ply-=5; plvy=-64;
	}
	
	if(padsDown(0) & KEY_Y)
	{
		dispararBala();
	}

	///Puerta
	 if ( Nivel1_map[((ply>>4)*32) + ((plx>>4)&31)]==4
	||   Nivel1_map[((ply>>4)*32) + (((plx>>4)+1)&31)]==4)
	{
		reiniciarTodo();
	}

	oamSet(0, showx,ply, 3, dir, 0, sprTiles[frameID], 0);
	oamSetEx(0, OBJ_SMALL, OBJ_SHOW);
	oamSet(4, showx,ply+16, 3, dir, 0, 2+sprTiles[frameID], 0);
	oamSetEx(4, OBJ_SMALL, OBJ_SHOW);
};