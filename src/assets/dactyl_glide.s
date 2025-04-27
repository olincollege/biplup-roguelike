
@{{BLOCK(dactyl_glide)

@=======================================================================
@
@	dactyl_glide, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2025-04-24, 23:08:07
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global dactyl_glideTiles		@ 128 unsigned chars
	.hidden dactyl_glideTiles
dactyl_glideTiles:
	.word 0x00000000,0x00000000,0x11000000,0x11110000,0x01111000,0x10111100,0x11111110,0x11001111
	.word 0x10000000,0x11000000,0x11100001,0x11110000,0x01111000,0x00111111,0x00111111,0x00111111
	.word 0x11100000,0x11111000,0x01111000,0x00001100,0x00000100,0x00000000,0x00000000,0x00000000
	.word 0x11111111,0x00011001,0x01100000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global dactyl_glidePal		@ 32 unsigned chars
	.hidden dactyl_glidePal
dactyl_glidePal:
	.hword 0x7FFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(dactyl_glide)
