	#include <snes.h>
	
	u16 showx, camx, showenemx;
	extern u16 plx;
	
	void desplazarPantalla()
	{
		if (plx>128)
		camx=plx-128;
		else camx=0;
	
		if (plx>128&&plx<512-128)
		{
			showx=128;
			showenemx=plx-128;
			mapUpdateCamera(plx,0);
		}
		else
		{
			showx=plx;
			showenemx=0;
		}
	}