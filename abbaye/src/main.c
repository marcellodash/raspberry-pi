/* Abbaye des Morts */
/* Version 2.0 */

/* (c) 2010 - Locomalito & Gryzor87 */
/* 2013 - David "Nevat" Lara */

/* GPL v3 license */

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "platform.h"
#include "fb.h"

extern void sdl_audio_dma_irq();

extern void startscreen(SDL_Window *screen,uint *state,uint *grapset,uint *fullscreen);
extern void history(SDL_Window *screen,uint *state,uint *grapset,uint *fullscreen);
extern void game(SDL_Window *screen,uint *state,uint *grapset,uint *fullscreen);
extern void gameover (SDL_Window *screen,uint *state);
extern void ending (SDL_Window *screen,uint *state);

#if defined(__cplusplus)
extern "C" {
#endif

__attribute__ ((interrupt ("IRQ"))) void interrupt_irq() {
    if ((IRQ->irqBasicPending & INTERRUPT_ARM_TIMER) != 0)
        ;
    if ((IRQ->irq1Pending & INTERRUPT_DMA0) != 0)
        sdl_audio_dma_irq();
}

#if defined(__cplusplus)
}
#endif

void main () {

	uint state = 0; /* 0-intro,1-history,2-game */
	uint grapset = 1; /* 0-8bits, 1-16bits */
	uint fullscreen = 0; /* 0-Windowed,1-Fullscreen */

	/* Initialize framebuffer */
    fb_init(16+256+16, 16+192+16);
    fb_begin_doublebuffer();

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

	/* Creating window */
	SDL_Window *screen = SDL_CreateWindow("Abbaye des Morts v2.0",16,16,256,192,SDL_WINDOWEVENT_SHOWN);

	/* Init audio */
	Mix_OpenAudio (22050,MIX_DEFAULT_FORMAT,2,4096);
	Mix_AllocateChannels(5);

	while (1) {
		switch (state) {
			case 0: startscreen(screen,&state,&grapset,&fullscreen);
							break;
			case 1: history(screen,&state,&grapset,&fullscreen);
							break;
			case 2: game(screen,&state,&grapset,&fullscreen);
							break;
			case 3: gameover(screen,&state);
							break;
			case 4: ending(screen,&state);
							break;
		}
	}

}