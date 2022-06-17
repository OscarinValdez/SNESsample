#include <snes.h>
#include "nivel1.h"

extern u16 i, sprnum, camx, gravedad, showenemx, plx,ply, num_monedas, dir;
u16 j;

typedef struct
{
	u16 x, y;
	u16 vely;
	u16 anim_frame;
	bool act,dir;
	int life;
} Objeto;

const char enemTiles[]=
{
    32,34,
};

const char monedaTiles[]=
{
    64,66,68,70,
}; 

Objeto Bala[2], Moneda[5], Enemigo[5];

void cargarMonedas()
{
	Objeto* m = Moneda;
	for (i=0;i<512;++i)
	{
		if (Nivel1_map[i]==3)
		{
			m->x=(i&31)<<4;
			m->y=(i/32)<<4;
			m->life=1;
			m->anim_frame=0;
			
			m++;
		}
	}
}

void actualizarMonedas()
{
	Objeto* m = Moneda;
	sprnum=28;
	for (i=0;i<5;++i)
	{
		if (m->x>=camx && m->x<(camx+256))
			m->act=1;
		else m->act=0;
		
		if (m->act && m->life)
		{
			++(m->anim_frame);
			
			oamSet(sprnum, (m->x)-(showenemx),m->y, 3, 0, 0, monedaTiles[(((m->anim_frame)/8)&3)], 0); 
			oamSetEx(sprnum, OBJ_SMALL, OBJ_SHOW);
			sprnum+=4;
			
			if ( m->x <= plx && m->x+16 > plx &&
                 m->y <= ply && m->y+16 > ply )
			{ m->life =0; ++num_monedas; }
		} else oamSetEx(sprnum, OBJ_SMALL, OBJ_HIDE);
		
		m++;
	}
}

void cargarEnemigos()
{
	
	Objeto* e = Enemigo;
	for (i=0;i<512;++i)
	{
		if (Nivel1_map[i]==2)
		{
			e->x=(i&31)<<4;
			e->y=(i/32)<<4;
			e->dir=0;
			e->life=1;
			e->anim_frame=0;
			
			e++;
		}
	}
}

void actualizarEnemigos()
{
	Objeto* e = Enemigo;
	sprnum=8;
	
	for (i=0;i<5;++i)
	{
		if (e->x>=camx && e->x<(camx+256))
			e->act=1;
		else e->act=0;
		
		if (e->act && e->life)
		{
			// Piso
			if ( Nivel1_map[((((e->y)+16)>>4)*32) + (((e->x)>>4)&31)]>=5
			||   Nivel1_map[((((e->y)+16)>>4)*32) + ((((e->x)>>4)+1)&31)]>=5)
			{
				e->vely=0; (e->y)=(((e->y)>>4)<<4);
			}
			else 	if ( Nivel1_map[((((e->y)-1)>>4)*32) + (((e->x)>>4)&31)]>=5
			||  Nivel1_map[((((e->y)-1)>>4)*32) + ((((e->x)>>4)+1)&31)]>=5)
			{
				e->vely=0; ++(e->y);
			}	
			else ++(e->vely);
			
			//moviendose
            if(Nivel1_map[(((e->y)>>4)*32) + (((e->x)>>4)&31)]>=5)
			e->dir=1;
			if(Nivel1_map[(((e->y)>>4)*32) + ((((e->x)>>4)+1)&31)]>=5)
			e->dir=0;
			
			if (e->dir==0) --(e->x);
			else if (e->dir==1) ++(e->x);
			
			e->y+=e->vely;
			if (e->vely>gravedad) e->vely=gravedad;
			
			++(e->anim_frame);
			oamSet(sprnum, (e->x)-showenemx,e->y, 3, e->dir, 0, enemTiles[((e->anim_frame)/8)&1], 0); 
			oamSetEx(sprnum, OBJ_SMALL, OBJ_SHOW);
			sprnum+=4;
		} else oamSetEx(sprnum, OBJ_SMALL, OBJ_HIDE);
		e++;
	}
}

void cargarBalas()
{
	Objeto* b = Bala;
	for (i=0;i<2;++i)
	{
		b->x=0;
		b->y=0;
		b->life=1;
		b->anim_frame=0;
		b->act=0;
		
		b++;
	}
}


void actualizarBalas()
{
	Objeto* b = Bala;
	sprnum=48;
	
	for (i=0;i<2;++i)
	{
		if(b->act == 1)
		{
			if (b->dir)
			b->x+=5;
			else b->x-=5;
			
			oamSet(sprnum, (b->x)-(showenemx),b->y, 3, 0, 0, 96, 0); 
			oamSetEx(sprnum, OBJ_SMALL, OBJ_SHOW);
			sprnum+=4;
			
			if (!(b->x>=camx && b->x<(camx+256)))
			b->act=0;
			
		} else oamSetEx(sprnum, OBJ_SMALL, OBJ_HIDE);
		b++;
	}
}

void dispararBala()
{
	Objeto* b = Bala;
	for (i=0;i<2;++i)
	{
		if(b->act == 0)
		{
			b->x = plx;
			b->y = ply+16;
			b->dir = !dir;
			b->act = 1;
			
			break;
		}
		
		b++;
	}
}

void colisionarObjetos(Objeto* a, Objeto* b)
{
    return (a->x < b->x + (b->x)+16 && a->x + (a->x)+16 > b->x && a->y < b->y + (b->y)+16 && a->y + (a->y)+16 >= b->y);
}

void colisionBalasEnemigos()
{
    Objeto* b = Bala;
    Objeto* e = Enemigo;

    for(i = 0; i < 2; i++)
	{
        if(b->act > 0)
		{
            for(j = 0; j < 5; j++)
			{
                if(e->life > 0 && e->act==1)
				{
                    if (colisionarObjetos(b,e))
					{
                        b->act=0;
                        e->act=0;
						e->life=0;
                        break;
                    }
                }
				e++;
            }
        }
		b++;
    }
}