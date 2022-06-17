/*---------------------------------------------------------------------------------


	template for main c file
	-- alekmaul


---------------------------------------------------------------------------------*/
#include <snes.h>
#include "soundbank.h"

extern char SOUNDBANK__;
extern char snesfont;
extern char Foto, Foto_end, palFoto, palFoto_end, mapFoto, mapFoto_end;
extern char Nivel1scrn, Nivel1scrn_end, palNivel1scrn, palNivel1scrn_end, mapNivel1scrn, mapNivel1scrn_end;
extern char sprjugador, sprjugador_end, paljugador;
extern char sprEnemigo, sprEnemigo_end, palEnemigo;
extern char sprMoneda, sprMoneda_end, palMoneda;
extern char sprBala, sprBala_end, palBala;

u16 sprnum, i, gravedad, num_monedas;

#include "jugador.h"
#include "pantalla.h"
#include "enemigos.h"

void desaparecerObjetos(void)
{
	for (sprnum=0;sprnum<=90;++sprnum)
	oamSetEx(sprnum, OBJ_SMALL, OBJ_HIDE);
}

void reiniciarTodo(void)
{
	desaparecerObjetos();

	bgInitMapSet(0, &mapNivel1scrn, (&mapNivel1scrn_end - &mapNivel1scrn),SC_64x32, 0x1000);
	bgSetMapPtr(0, 0x1000, SC_64x32);

	mapUpdateCamera(0,0);
	iniciarJugador();
	cargarMonedas();
	cargarEnemigos();
}

//---------------------------------------------------------------------------------
int main(void) {
	gravedad=4;
	num_monedas=0;
    // Initialize SNES 
	consoleInit();
	
	spcBoot();
	// Set give soundbank
	spcSetBank(&SOUNDBANK__);
	
	// allocate around 10K of sound ram (39 256-byte blocks)
	spcAllocateSoundRegion(39);
	// Load music
	spcLoad(MOD_POLLEN8);
	// Play file from the beginning
	spcPlay(0);
	
	// Now Put in 16 color mode 
	setMode(BG_MODE1,0); bgSetDisable(2);
	
	bgInitTileSet(0, &Nivel1scrn,&palNivel1scrn, 2, (&Nivel1scrn_end - &Nivel1scrn), (&palNivel1scrn_end - &palNivel1scrn), BG_16COLORS, 0x6000);
	bgInitMapSet(0, &mapNivel1scrn, (&mapNivel1scrn_end - &mapNivel1scrn),SC_64x32, 0x1000);
	bgSetMapPtr(0, 0x1000, SC_64x32);
	
	oamInitGfxSet(&sprjugador, (&sprjugador_end-&sprjugador), &paljugador, 16*2, 0, 0x4000, OBJ_SIZE16_L32);
	dmaCopyVram(&sprEnemigo, 0x4200, (&sprEnemigo_end-&sprEnemigo));
	dmaCopyVram(&sprMoneda, 0x4400, (&sprMoneda_end-&sprMoneda));
	dmaCopyVram(&sprBala, 0x4600, (&sprBala_end-&sprBala));
	
	iniciarJugador();
	cargarEnemigos();
	cargarMonedas();
	cargarBalas();
	
	consoleInitText(1, 1, &snesfont);
	consoleSetTextCol(RGB5(0,0,0), RGB5(31,31,31));
	
	setScreenOn(); 
	// Infinite loop to keep the program running
	while(1) {
		consoleDrawText(1,1,"MONEDAS: %d",num_monedas);
		// Put your code here
		spcProcess();
		actualizarJugador();
		desplazarPantalla();
		mapUpdate();
		actualizarEnemigos();
		actualizarMonedas();
		actualizarBalas();
		colisionBalasEnemigos();
		WaitForVBlank();
		mapVblank();
	}
	return 0;
}