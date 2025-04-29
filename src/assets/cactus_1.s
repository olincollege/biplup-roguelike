
@{{BLOCK(cactus_1)

@=======================================================================
@
@	cactus_1, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2025-04-24, 22:09:58
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global cactus_1Tiles		@ 128 unsigned chars
	.hidden cactus_1Tiles
cactus_1Tiles:
	.word 0x00000000,0x11000000,0x11100000,0x11100000,0x11101100,0x11101110,0x11101110,0x11101110
	.word 0x00000000,0x00000111,0x00001111,0x00001111,0x00101111,0x01101111,0x01101111,0x01101111
	.word 0x11101110,0x11111110,0x11111100,0x11111100,0x11100000,0x11100000,0x11100000,0x11100000
	.word 0x01101111,0x01101111,0x01101111,0x01101111,0x01111111,0x00111111,0x00001111,0x00001111

	.section .rodata
	.align	2
	.global cactus_1Pal		@ 32 unsigned chars
	.hidden cactus_1Pal
cactus_1Pal:
	.hword 0x7FFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(cactus_1)
