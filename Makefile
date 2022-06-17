ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules
 
.PHONY: bitmaps all
 
#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := template

# to build musics, define SMCONVFLAGS with parameters you want
SMCONVFLAGS	:= -s -o $(SOUNDBANK) -v -b 5
musics: $(SOUNDBANK).obj

all: bitmaps $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx

#--------------------------------------

pvsneslibfont.pic: pvsneslibfont.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -n -gs8 -po2 -pc16 -pe1 -mR! -m! -p! $<
	
Foto.pic: Foto.bmp
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs16 -pe2 -fbmp -m $<
	
Nivel1scrn.pic: Nivel1scrn.bmp	
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs16 -pe2 -fbmp -m -m32p $<

jugador.pic: jugador.png
	@echo convert sprite bitmap ... $(notdir $@)
	$(GFXCONV) -gs16 -pc16 -po16 -fpng -n $<
	
Enemigo.pic: Enemigo.png
	@echo convert sprite bitmap ... $(notdir $@)
	$(GFXCONV) -gs16 -pc16 -po16 -fpng -n $<
	
Moneda.pic: Moneda.png
	@echo convert sprite bitmap ... $(notdir $@)
	$(GFXCONV) -gs16 -pc16 -po16 -fpng -n $<

Bala.pic: Bala.png
	@echo convert sprite bitmap ... $(notdir $@)
	$(GFXCONV) -gs16 -pc16 -po16 -fpng -n $<
	
bitmaps : pvsneslibfont.pic Foto.pic Nivel1scrn.pic jugador.pic Enemigo.pic Moneda.pic Bala.pic