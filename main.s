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
	.importzp	_InputPort1
	.export		_inputPort1Old
	.import		_WaitFrame
	.export		_i
	.export		_x
	.export		_y
	.export		_mapX
	.export		_mapY
	.export		_tileIndex
	.export		_player
	.export		_TEXT
	.export		_PALETTE
	.export		_mapWidth
	.export		_map
	.export		_drawBackground
	.export		_main

.segment	"DATA"

_inputPort1Old:
	.byte	$00

.segment	"RODATA"

_TEXT:
	.byte	$48,$65,$6C,$6C,$6F,$2C,$20,$57,$6F,$72,$6C,$64,$21,$00
_PALETTE:
	.byte	$0F
	.byte	$00
	.byte	$10
	.byte	$20
	.byte	$0F
	.byte	$11
	.byte	$21
	.byte	$31
	.byte	$0F
	.byte	$15
	.byte	$25
	.byte	$35
	.byte	$0F
	.byte	$19
	.byte	$29
	.byte	$39
	.byte	$0F
	.byte	$06
	.byte	$15
	.byte	$36
	.byte	$0F
	.byte	$11
	.byte	$21
	.byte	$31
	.byte	$0F
	.byte	$15
	.byte	$25
	.byte	$35
	.byte	$0F
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
	.byte	$04
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
	.byte	$00
	.byte	$00

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
.segment	"BSS"
.segment	"OAM"
_player:
	.res	4,$00
.segment	"BSS"

; ---------------------------------------------------------------
; void __near__ drawBackground (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_drawBackground: near

.segment	"CODE"

;
; PPU.vram.address = 0x20;
;
	lda     #$20
	sta     $2006
;
; PPU.vram.address = 0x20;
;
	sta     $2006
;
; for(i = 0; i < 1024; i++) {
;
	lda     #$00
	sta     _i
	sta     _i+1
L0235:	ldx     _i+1
	cpx     #$04
	bcc     L02CC
;
; }
;
	rts
;
; mapX = (i & 0x1F) >> 1;
;
L02CC:	lda     _i
	ldx     #$00
	and     #$1F
	lsr     a
	sta     _mapX
	stx     _mapX+1
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
; tileIndex = (map[mapX + (mapY << 6)] & 39) << 1;
;
	lda     _mapY
	ldx     _mapY+1
	jsr     shlax4
	jsr     shlax2
	clc
	adc     _mapX
	sta     ptr1
	txa
	adc     _mapX+1
	clc
	adc     #>(_map)
	sta     ptr1+1
	ldy     #<(_map)
	lda     (ptr1),y
	ldx     #$00
	and     #$27
	asl     a
	bcc     L02CA
	inx
L02CA:	sta     _tileIndex
	stx     _tileIndex+1
;
; if((i >> 5) & 0x1) {
;
	lda     _i
	ldx     _i+1
	jsr     shrax4
	jsr     shrax1
	and     #$01
	beq     L0249
;
; tileIndex += 16;
;
	lda     #$10
	clc
	adc     _tileIndex
	sta     _tileIndex
	bcc     L0249
	inc     _tileIndex+1
;
; if(i & 0x1) {
;
L0249:	lda     _i
	and     #$01
	beq     L02CB
;
; ++tileIndex;
;
	inc     _tileIndex
	bne     L02CB
	inc     _tileIndex+1
;
; PPU.vram.data = (uint8_t)tileIndex;
;
L02CB:	lda     _tileIndex
	sta     $2007
;
; for(i = 0; i < 1024; i++) {
;
	lda     _i
	ldx     _i+1
	clc
	adc     #$01
	bcc     L023D
	inx
L023D:	sta     _i
	stx     _i+1
	jmp     L0235

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
L025D:	lda     _i+1
	cmp     #$00
	bne     L0265
	lda     _i
	cmp     #$20
L0265:	bcs     L025E
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
	bne     L025D
	inc     _i+1
	jmp     L025D
;
; drawBackground();
;
L025E:	jsr     _drawBackground
;
; PPU.vram.address = 0x23;
;
	lda     #$23
	sta     $2006
;
; PPU.vram.address = 0xC0;
;
	lda     #$C0
	sta     $2006
;
; for(i = 0; i < 64; i++) {
;
	lda     #$00
	sta     _i
	sta     _i+1
L0273:	lda     _i+1
	cmp     #$00
	bne     L027A
	lda     _i
	cmp     #$40
L027A:	bcs     L0274
;
; PPU.vram.data = i & 0x0F;
;
	lda     _i
	and     #$0F
	sta     $2007
;
; for(i = 0; i < 64; i++) {
;
	lda     _i
	ldx     _i+1
	clc
	adc     #$01
	bcc     L027C
	inx
L027C:	sta     _i
	stx     _i+1
	jmp     L0273
;
; player.x = 20;
;
L0274:	lda     #$14
	sta     _player+3
;
; player.y = 20;
;
	sta     _player
;
; player.tile_index = 0x0;
;
	lda     #$00
	sta     _player+1
;
; PPU.scroll = 0x00;
;
	sta     $2005
;
; PPU.scroll = 0x00;
;
	sta     $2005
;
; PPU.control = PPUCTRL_NAMETABLE_0 | PPUCTRL_INC_1_HORIZ | PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_1 | PPUCTRL_NMI_ON;
;
	lda     #$88
	sta     $2000
;
; PPU.mask = PPUMASK_COLOR | PPUMASK_L8_BSHOW | PPUMASK_L8_SSHOW | PPUMASK_SSHOW | PPUMASK_BSHOW;
;
	lda     #$1E
	sta     $2001
;
; APU.status = 0x0F;
;
	lda     #$0F
	sta     $4015
;
; WaitFrame();
;
L0295:	jsr     _WaitFrame
;
; PPU.scroll = 0;
;
	lda     #$00
	sta     $2005
;
; PPU.scroll = 0;
;
	sta     $2005
;
; if (InputPort1 & BUTTON_UP) {
;
	lda     _InputPort1
	and     #$08
	beq     L02CD
;
; if (player.y > 0) {
;
	lda     _player
	beq     L02CD
;
; --player.y;
;
	dec     _player
;
; if(!(inputPort1Old & BUTTON_UP)) {
;
	lda     _inputPort1Old
	and     #$08
	bne     L02CD
;
; APU.pulse[0].control = 0x0F;
;
	lda     #$0F
	sta     $4000
;
; APU.pulse[0].ramp = 0x01;
;
	lda     #$01
	sta     $4001
;
; APU.pulse[0].period_low = 0x05;
;
	lda     #$05
	sta     $4002
;
; APU.pulse[0].len_period_high = (0x0F << 5) + 0x01;
;
	lda     #$E1
	sta     $4003
;
; if (InputPort1 & BUTTON_DOWN) {
;
L02CD:	lda     _InputPort1
	and     #$04
	beq     L02CE
;
; if (player.y < 255) {
;
	lda     _player
	cmp     #$FF
	bcs     L02CE
;
; ++player.y;
;
	inc     _player
;
; if (InputPort1 & BUTTON_LEFT) {
;
L02CE:	lda     _InputPort1
	and     #$02
	beq     L02CF
;
; if (player.x > 0) {
;
	lda     _player+3
	beq     L02CF
;
; --player.x;
;
	dec     _player+3
;
; if (InputPort1 & BUTTON_RIGHT) {
;
L02CF:	lda     _InputPort1
	and     #$01
	beq     L02D0
;
; if (player.x < 255) {
;
	lda     _player+3
	cmp     #$FF
	bcs     L02D0
;
; ++player.x;
;
	inc     _player+3
;
; inputPort1Old = InputPort1;
;
L02D0:	lda     _InputPort1
	sta     _inputPort1Old
;
; while (1) {
;
	jmp     L0295

.endproc
