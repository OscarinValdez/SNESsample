.include "hdr.asm"

.section ".rodata1" superfree

snesfont:
.incbin "pvsneslibfont.pic"

.ends

.section ".rodata2" superfree

Foto:
.incbin "Foto.pic"
Foto_end:

palFoto
.incbin "Foto.pal"
palFoto_end:

mapFoto:
.incbin "Foto.map"
mapFoto_end:

.ends

.section ".rodata3" superfree

Nivel1scrn:
.incbin "Nivel1scrn.pic"
Nivel1scrn_end:

palNivel1scrn
.incbin "Nivel1scrn.pal"
palNivel1scrn_end:

mapNivel1scrn:
.incbin "Nivel1scrn.map"
mapNivel1scrn_end:

.ends

.section ".rodata4" superfree

sprjugador:
.incbin "jugador.pic"
sprjugador_end:

paljugador:
.incbin "jugador.pal"

sprEnemigo:
.incbin "Enemigo.pic"
sprEnemigo_end:

palEnemigo:
.incbin "Enemigo.pal"

sprMoneda:
.incbin "Moneda.pic"
sprMoneda_end:

palMoneda:
.incbin "Moneda.pal"

sprBala:
.incbin "Bala.pic"
sprBala_end:

palBala:
.incbin "Bala.pal"

.ends