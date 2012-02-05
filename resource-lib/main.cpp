#include "include/resource.h"
#include "include/resource_string.h"
#include "include/resource_image.h"
#include "include/resource_palette.h"
#include "include/resource_tech.h"

#define putpixel(s, x, y, c) *((Uint8 *)s->pixels + y * s->pitch + x * s->format->BytesPerPixel) = c

int main(int argc, char **argv) {
	SDL_Surface *screen = NULL;
	SDL_Rect screenRc = { 0, 0, 640, 480 };
	SDL_Event event;
	int needExit = 0;
	
	// initialize random numbers
	srandom(time(NULL));
	
	// initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(screenRc.w, screenRc.h, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
	
	// load resources
	Resource *universeImages = new Resource("../paxdata/images/Universe.img");	
	Resource *paxPalettes = new Resource("../paxdata/data/PalData");
	
	// pick a random one
	ImageResourceObject *imageObject = (ImageResourceObject*)universeImages->getObjectByIndex(atoi(argv[1]));
	PaletteResourceObject *paletteObject = (PaletteResourceObject*)paxPalettes->getObjectByIndex(atoi(argv[2]));
	
	// output data 
	cout << "Found " << universeImages->getObjectsCount() << " images." << endl;
	cout << "Found " << dec << paxPalettes->getObjectsCount() << " palettes." << endl;
	cout << "Palette picked: " << hex << paletteObject->getId() << endl;
	cout << "Image id: " << hex << imageObject->getId() << endl;
	cout << "Size: " << dec << imageObject->width() << "x" << imageObject->height() << endl;
	cout << "Unknown1: " << hex << imageObject->unknown1() << endl;
	cout << "Unknown2: " << hex << imageObject->unknown2() << endl;
	
	// main loop
	while (!needExit) {
		// process events 
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN)
				needExit = 1;
		}
		
		// clear screen
		SDL_FillRect(screen, &screenRc, 0);
		
		// redraw image
		uint8 *imageData = imageObject->pixels();
		for (int i=0;i<imageObject->height();i++) {
			for (int j=0;j<imageObject->width();j++) {
				PaletteEntry *entry = paletteObject->getColorByIndex(*imageData++);
				putpixel(screen, j, i, SDL_MapRGB(screen->format, entry->r, entry->g, entry->b));
			}
		}
				
		// Flip surface
		SDL_Flip(screen);
		
		// wait a bit
		SDL_Delay(1000/33);
		
	}
	SDL_Quit();
	
	delete universeImages;
	delete paxPalettes;	
	
	return 0;
}
