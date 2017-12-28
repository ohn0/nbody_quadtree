#ifndef VISUALIZER_H
#define VISUALIZER_H
#include "../quadtree.h"
#include "nBody.h"
#include <vector>
#include <SDL.h>
class visualizer
{
    public:
        visualizer();
        visualizer(const char*, int, int);
        int updateVisuals(nBody*);
        int deleteVisualizer();
        virtual ~visualizer();
        void toggleTreeView(bool view){showTree = view;}
    protected:

    private:
        bool showTree = false;
        int screenWidth = 640;
        int screenHeight = 480;
        SDL_Window* visWindow;
        int updateVisualsShowTree(nBody*);
        int initVisualizer(const char*, int, int);
        SDL_Surface* visSurface;
        SDL_Renderer* visRenderer;
};


#endif // VISUALIZER_H
