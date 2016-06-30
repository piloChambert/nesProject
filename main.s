;
; File generated by cc65 v 2.15
;
	.fopt		compiler,"cc65 v 2.15"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.forceimport	__STARTUP__
	.importzp	_FrameCount
	.importzp	_InputPort1
	.importzp	_VRAMUpdateReady
	.importzp	_SplitEnable
	.importzp	_Scroll
	.import		_WaitFrame
	.import		_bankswitch
	.export		_i
	.export		_x
	.export		_y
	.export		_mapX
	.export		_mapY
	.export		_tileIndex
	.export		_playerX
	.export		_playerY
	.export		_playerSpeedX
	.export		_playerYOffset
	.export		_relativePlayerX
	.export		_score
	.export		_sprites
	.export		_ScoreText
	.export		_PALETTE
	.export		_mapWidth
	.export		_map
	.export		_drawStatus
	.export		_drawBackground
	.export		_playerSpriteFrames
	.export		_drawMetaSprite
	.export		_main

.segment	"DATA"

_playerX:
	.word	$0000
_playerY:
	.word	$0000
_playerSpeedX:
	.byte	$00
_playerYOffset:
	.byte	$00
_score:
	.word	$152D

.segment	"RODATA"

_ScoreText:
	.byte	$53,$43,$4F,$52,$45,$2E,$00
_PALETTE:
	.byte	$22
	.byte	$00
	.byte	$10
	.byte	$20
	.byte	$22
	.byte	$11
	.byte	$21
	.byte	$31
	.byte	$22
	.byte	$15
	.byte	$25
	.byte	$35
	.byte	$22
	.byte	$19
	.byte	$29
	.byte	$39
	.byte	$22
	.byte	$16
	.byte	$05
	.byte	$27
	.byte	$22
	.byte	$11
	.byte	$21
	.byte	$31
	.byte	$22
	.byte	$15
	.byte	$25
	.byte	$35
	.byte	$22
	.byte	$19
	.byte	$29
	.byte	$39
_mapWidth:
	.byte	$20
_map:
	.byte	$00
	.byte	$01
	.byte	$02
	.byte	$03
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$01
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$01
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$01
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$01
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$01
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
	.byte	$04
_playerSpriteFrames:
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$00
	.byte	$08
	.byte	$00
	.byte	$01
	.byte	$00
	.byte	$00
	.byte	$08
	.byte	$10
	.byte	$00
	.byte	$08
	.byte	$08
	.byte	$11
	.byte	$00
	.byte	$7F
	.byte	$00
	.byte	$00
	.byte	$02
	.byte	$00
	.byte	$08
	.byte	$00
	.byte	$03
	.byte	$00
	.byte	$00
	.byte	$08
	.byte	$12
	.byte	$00
	.byte	$08
	.byte	$08
	.byte	$13
	.byte	$00
	.byte	$7F

.segment	"BSS"

.segment	"ZEROPAGE"
_i:
	.res	2,$00
_x:
	.res	2,$00
_y:
	.res	2,$00
_mapX:
	.res	2,$00
_mapY:
	.res	2,$00
_tileIndex:
	.res	2,$00
_relativePlayerX:
	.res	2,$00
.segment	"BSS"
.segment	"OAM"
_sprites:
	.res	256,$00
.segment	"BSS"

; ---------------------------------------------------------------
; void __near__ drawStatus (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_drawStatus: near

.segment	"CODE"

;
; PPU.vram.address = 0x20;
;
	lda     #$20
	sta     $2006
;
; PPU.vram.address = 0x40 + 0x04;    
;
	lda     #$44
	sta     $2006
;
; for(i = 0; i < sizeof(ScoreText); i++) {
;
	lda     #$00
	sta     _i
	sta     _i+1
L01DD:	lda     _i+1
	cmp     #$00
	bne     L01E5
	lda     _i
	cmp     #$07
L01E5:	bcs     L01DE
;
; PPU.vram.data = ScoreText[i];
;
	lda     #<(_ScoreText)
	sta     ptr1
	lda     #>(_ScoreText)
	clc
	adc     _i+1
	sta     ptr1+1
	ldy     _i
	lda     (ptr1),y
	sta     $2007
;
; for(i = 0; i < sizeof(ScoreText); i++) {
;
	lda     _i
	ldx     _i+1
	clc
	adc     #$01
	bcc     L01E7
	inx
L01E7:	sta     _i
	stx     _i+1
	jmp     L01DD
;
; }
;
L01DE:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ drawBackground (unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_drawBackground: near

.segment	"CODE"

;
; void drawBackground(uint8_t table) {
;
	jsr     pusha
;
; PPU.vram.address = 0x20 + (table * 4);
;
	ldy     #$00
	lda     (sp),y
	asl     a
	asl     a
	clc
	adc     #$20
	sta     $2006
;
; PPU.vram.address = 0xA0;
;
	lda     #$A0
	sta     $2006
;
; for(i = 0; i < 32 * 26; i++) {
;
	tya
	sta     _i
	sta     _i+1
L01F5:	lda     _i+1
	cmp     #$03
	bne     L01FC
	lda     _i
	cmp     #$40
L01FC:	jcs     L01F6
;
; mapX = ((i & 0x1F) >> 1) + (table << 4);
;
	lda     _i
	ldx     #$00
	and     #$1F
	lsr     a
	sta     ptr1
	stx     ptr1+1
	lda     (sp,x)
	jsr     aslax4
	clc
	adc     ptr1
	sta     _mapX
	txa
	adc     ptr1+1
	sta     _mapX+1
;
; mapY = (i >> 6);
;
	lda     _i
	ldx     _i+1
	jsr     shrax4
	jsr     shrax2
	sta     _mapY
	stx     _mapY+1
;
; tileIndex = map[mapX + (mapY << 5)] << 1;
;
	lda     _mapY
	ldx     _mapY+1
	jsr     shlax4
	stx     tmp1
	asl     a
	rol     tmp1
	clc
	adc     _mapX
	sta     ptr1
	lda     tmp1
	adc     _mapX+1
	clc
	adc     #>(_map)
	sta     ptr1+1
	ldy     #<(_map)
	ldx     #$00
	lda     (ptr1),y
	asl     a
	bcc     L02FD
	inx
L02FD:	sta     _tileIndex
	stx     _tileIndex+1
;
; if((i >> 5) & 0x1) {
;
	lda     _i
	ldx     _i+1
	jsr     shrax4
	jsr     shrax1
	and     #$01
	beq     L020B
;
; tileIndex += 16;
;
	lda     #$10
	clc
	adc     _tileIndex
	sta     _tileIndex
	bcc     L020B
	inc     _tileIndex+1
;
; if(i & 0x1) {
;
L020B:	lda     _i
	and     #$01
	beq     L02FE
;
; ++tileIndex;
;
	inc     _tileIndex
	bne     L02FE
	inc     _tileIndex+1
;
; PPU.vram.data = (uint8_t)tileIndex;
;
L02FE:	lda     _tileIndex
	sta     $2007
;
; for(i = 0; i < 32 * 26; i++) {
;
	lda     _i
	ldx     _i+1
	clc
	adc     #$01
	bcc     L01FE
	inx
L01FE:	sta     _i
	stx     _i+1
	jmp     L01F5
;
; PPU.vram.address = 0x23 + (table * 4);
;
L01F6:	ldy     #$00
	lda     (sp),y
	asl     a
	asl     a
	clc
	adc     #$23
	sta     $2006
;
; PPU.vram.address = 0xC0;
;
	lda     #$C0
	sta     $2006
;
; for(i = 0; i < 64; i++) {
;
	tya
	sta     _i
	sta     _i+1
L0220:	lda     _i+1
	cmp     #$00
	bne     L0227
	lda     _i
	cmp     #$40
L0227:	bcs     L0221
;
; PPU.vram.data = 0x00;
;
	lda     #$00
	sta     $2007
;
; for(i = 0; i < 64; i++) {
;
	lda     _i
	ldx     _i+1
	clc
	adc     #$01
	bcc     L0229
	inx
L0229:	sta     _i
	stx     _i+1
	jmp     L0220
;
; }
;
L0221:	jmp     incsp1

.endproc

; ---------------------------------------------------------------
; unsigned char __near__ drawMetaSprite (unsigned char, unsigned char, unsigned char, __near__ const unsigned char *)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_drawMetaSprite: near

.segment	"CODE"

;
; uint8_t drawMetaSprite(uint8_t id, uint8_t x, uint8_t y, const uint8_t *data) {
;
	jsr     pushax
;
; const uint8_t *ptr = data;
;
	jsr     pushw0sp
;
; while(*ptr != 127) {
;
	jmp     L0255
;
; sprites[id].x = x + *(ptr++);
;
L0253:	ldy     #$06
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	clc
	adc     #<(_sprites)
	tay
	txa
	adc     #>(_sprites)
	tax
	tya
	jsr     pushax
	ldy     #$07
	lda     (sp),y
	jsr     pusha0
	ldy     #$05
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	sta     regsave
	stx     regsave+1
	clc
	adc     #$01
	bcc     L025B
	inx
L025B:	jsr     staxysp
	ldx     #$00
	lda     (regsave,x)
	jsr     tosadda0
	ldy     #$03
	jsr     staspidx
;
; sprites[id].y = y + *(ptr++);
;
	ldy     #$06
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	clc
	adc     #<(_sprites)
	tay
	txa
	adc     #>(_sprites)
	tax
	tya
	jsr     pushax
	ldy     #$06
	lda     (sp),y
	jsr     pusha0
	ldy     #$05
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	sta     regsave
	stx     regsave+1
	clc
	adc     #$01
	bcc     L0260
	inx
L0260:	jsr     staxysp
	ldx     #$00
	lda     (regsave,x)
	jsr     tosadda0
	ldy     #$00
	jsr     staspidx
;
; sprites[id].tile_index = *(ptr++);
;
	ldy     #$06
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	clc
	adc     #<(_sprites)
	tay
	txa
	adc     #>(_sprites)
	tax
	tya
	jsr     pushax
	ldy     #$03
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	sta     regsave
	stx     regsave+1
	clc
	adc     #$01
	bcc     L0265
	inx
L0265:	jsr     staxysp
	ldy     #$00
	lda     (regsave),y
	iny
	jsr     staspidx
;
; sprites[id].attributes = *(ptr++);
;
	ldy     #$06
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	clc
	adc     #<(_sprites)
	tay
	txa
	adc     #>(_sprites)
	tax
	tya
	jsr     pushax
	ldy     #$03
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	sta     regsave
	stx     regsave+1
	clc
	adc     #$01
	bcc     L026A
	inx
L026A:	jsr     staxysp
	ldy     #$00
	lda     (regsave),y
	ldy     #$02
	jsr     staspidx
;
; id++;
;
	ldy     #$06
	lda     (sp),y
	clc
	adc     #$01
	sta     (sp),y
;
; while(*ptr != 127) {
;
L0255:	ldy     #$01
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	lda     (ptr1),y
	cmp     #$7F
	jne     L0253
;
; return id;
;
	ldy     #$06
	ldx     #$00
	lda     (sp),y
;
; }
;
	jmp     incsp7

.endproc

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

;
; PPU.vram.address = 0x3f;
;
	lda     #$3F
	sta     $2006
;
; PPU.vram.address = 0x00;
;
	lda     #$00
	sta     $2006
;
; for ( i = 0; i < sizeof(PALETTE); ++i ) {
;
	sta     _i
	sta     _i+1
L0274:	lda     _i+1
	cmp     #$00
	bne     L027C
	lda     _i
	cmp     #$20
L027C:	bcs     L0275
;
; PPU.vram.data = PALETTE[i];
;
	lda     #<(_PALETTE)
	sta     ptr1
	lda     #>(_PALETTE)
	clc
	adc     _i+1
	sta     ptr1+1
	ldy     _i
	lda     (ptr1),y
	sta     $2007
;
; for ( i = 0; i < sizeof(PALETTE); ++i ) {
;
	inc     _i
	bne     L0274
	inc     _i+1
	jmp     L0274
;
; bankswitch(0);
;
L0275:	lda     #$00
	jsr     _bankswitch
;
; drawStatus();
;
	jsr     _drawStatus
;
; drawBackground(1);
;
	lda     #$01
	jsr     _drawBackground
;
; drawBackground(0);
;
	lda     #$00
	jsr     _drawBackground
;
; Scroll = 0;
;
	ldx     #$00
	txa
	sta     _Scroll
	sta     _Scroll+1
;
; sprites[0].x = 72;
;
	lda     #$48
	sta     _sprites+3
;
; sprites[0].y = 16;
;
	lda     #$10
	sta     _sprites
;
; sprites[0].tile_index = 0xFF;
;
	lda     #$FF
	sta     _sprites+1
;
; playerX = 32;
;
	lda     #$20
	sta     _playerX
	stx     _playerX+1
;
; VRAMUpdateReady = 1;
;
	lda     #$01
	sta     _VRAMUpdateReady
;
; PPU.control = PPUCTRL_NAMETABLE_0 | PPUCTRL_INC_1_HORIZ | PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_1 | PPUCTRL_NMI_ON;
;
	lda     #$88
	sta     $2000
;
; PPU.mask = PPUMASK_L8_BSHOW | PPUMASK_L8_SSHOW | PPUMASK_SSHOW | PPUMASK_BSHOW;
;
	lda     #$1E
	sta     $2001
;
; APU.status = 0x0F;
;
	lda     #$0F
	sta     $4015
;
; Scroll = 0;
;
	txa
	sta     _Scroll
	sta     _Scroll+1
;
; SplitEnable = 1;
;
	lda     #$01
	sta     _SplitEnable
;
; WaitFrame();
;
L02A6:	jsr     _WaitFrame
;
; if(InputPort1 & BUTTON_UP) {
;
	lda     _InputPort1
	and     #$08
	beq     L0300
;
; if (playerY > 0) {
;
	lda     _playerY
	ora     _playerY+1
	beq     L0300
;
; --playerY;
;
	lda     _playerY
	sec
	sbc     #$01
	sta     _playerY
	bcs     L0300
	dec     _playerY+1
;
; if(InputPort1 & BUTTON_DOWN) {
;
L0300:	lda     _InputPort1
	and     #$04
	beq     L0301
;
; if (playerY < 240) {
;
	lda     _playerY+1
	cmp     #$00
	bne     L02B6
	lda     _playerY
	cmp     #$F0
L02B6:	bcs     L0301
;
; ++playerY;
;
	inc     _playerY
	bne     L0301
	inc     _playerY+1
;
; if(InputPort1 & BUTTON_LEFT) {
;
L0301:	lda     _InputPort1
	and     #$02
	beq     L0302
;
; if (playerSpeedX > -8) {
;
	lda     _playerSpeedX
	sec
	sbc     #$F9
	bvs     L02BE
	eor     #$80
L02BE:	bpl     L02DA
;
; --playerSpeedX;
;
	dec     _playerSpeedX
	bpl     L02DA
;
; } else if(InputPort1 & BUTTON_RIGHT) {
;
	jmp     L02DA
L0302:	lda     _InputPort1
	and     #$01
	beq     L0303
;
; if (playerSpeedX < 8) {
;
	lda     _playerSpeedX
	sec
	sbc     #$08
	bvc     L02C7
	eor     #$80
L02C7:	bpl     L02DA
;
; ++playerSpeedX;
;
	inc     _playerSpeedX
	bpl     L02DA
;
; } else if(playerSpeedX > 3) {
;
	jmp     L02DA
L0303:	lda     _playerSpeedX
	sec
	sbc     #$04
	bvs     L02CE
	eor     #$80
L02CE:	bpl     L0304
;
; playerSpeedX -= 4;
;
	lda     _playerSpeedX
	sec
	sbc     #$04
	sta     _playerSpeedX
	bpl     L02DA
;
; } else if(playerSpeedX < -3) {
;
	jmp     L02DA
L0304:	lda     _playerSpeedX
	sec
	sbc     #$FD
	bvc     L02D6
	eor     #$80
L02D6:	asl     a
	lda     #$00
	bcc     L0306
;
; playerSpeedX += 4;
;
	lda     #$04
	clc
	adc     _playerSpeedX
	sta     _playerSpeedX
	bpl     L02DA
;
; } else {
;
	jmp     L02DA
;
; playerSpeedX = 0;
;
L0306:	sta     _playerSpeedX
;
; if(playerX < Scroll + 32 && Scroll > 0) {
;
L02DA:	lda     _playerX
	ldx     _playerX+1
	jsr     pushax
	lda     _Scroll
	ldx     _Scroll+1
	clc
	adc     #$20
	bcc     L02DF
	inx
L02DF:	jsr     tosicmp
	bcs     L02DD
	lda     _Scroll
	ora     _Scroll+1
	beq     L02DD
;
; Scroll -= 2;
;
	lda     _Scroll
	sec
	sbc     #$02
	sta     _Scroll
	bcs     L02DD
	dec     _Scroll+1
;
; if(playerX > Scroll + 256 - 32 && Scroll < 256) {
;
L02DD:	lda     _playerX
	ldx     _playerX+1
	jsr     pushax
	lda     _Scroll
	ldx     _Scroll+1
	inx
	sec
	sbc     #$20
	bcs     L02E8
	dex
L02E8:	jsr     tosicmp
	bcc     L02ED
	beq     L02ED
	ldx     _Scroll+1
	cpx     #$01
	bcs     L02ED
;
; Scroll += 2;
;
	lda     #$02
	clc
	adc     _Scroll
	sta     _Scroll
	bcc     L02ED
	inc     _Scroll+1
;
; playerX += playerSpeedX;
;
L02ED:	ldx     #$00
	lda     _playerSpeedX
	cmp     #$80
	bcc     L02FF
	dex
	clc
L02FF:	adc     _playerX
	sta     _playerX
	txa
	adc     _playerX+1
	sta     _playerX+1
;
; relativePlayerX = playerX - Scroll;
;
	lda     _playerX
	sec
	sbc     _Scroll
	sta     _relativePlayerX
	lda     _playerX+1
	sbc     _Scroll+1
	sta     _relativePlayerX+1
;
; drawMetaSprite(1, relativePlayerX, playerY, playerSpriteFrames[(FrameCount >> 2) & 0x01]);
;
	jsr     decsp3
	lda     #$01
	ldy     #$02
	sta     (sp),y
	lda     _relativePlayerX
	dey
	sta     (sp),y
	lda     _playerY
	dey
	sta     (sp),y
	lda     _FrameCount
	lsr     a
	lsr     a
	and     #$01
	jsr     pusha0
	lda     #$11
	jsr     tosmula0
	clc
	adc     #<(_playerSpriteFrames)
	tay
	txa
	adc     #>(_playerSpriteFrames)
	tax
	tya
	jsr     _drawMetaSprite
;
; VRAMUpdateReady = 1;
;
	lda     #$01
	sta     _VRAMUpdateReady
;
; while (1) {
;
	jmp     L02A6

.endproc

