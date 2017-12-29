#include "visualizer.h"

visualizer::visualizer()
{
    this->initVisualizer("visualizer", this->screenWidth, this->screenHeight);
}

visualizer::visualizer(const char* name, int width, int height)
{
    this->initVisualizer(name, width, height);
}

visualizer::~visualizer()
{
    //dtor
}

int visualizer::initVisualizer(const char* name, int width, int height)
{
    if(SDL_Init(SDL_INIT_VIDEO)< 0){
        printf("Error initiating SDL, erro %s\n", SDL_GetError());
        return -1;
    }
    this->screenWidth = width;
    this->screenHeight = height;
    this->visWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED, width, height,
                                       SDL_WINDOW_SHOWN);
    this->visRenderer = SDL_CreateRenderer(this->visWindow, -1, SDL_RENDERER_ACCELERATED);
    if(this->visWindow == NULL){
        printf("Unable to create SDL Window. Error: %s\n", SDL_GetError());
        return -1;
    }
    this->visSurface = SDL_GetWindowSurface(visWindow);
    return 0;
}

int visualizer::updateVisuals(nBody* nSystem)
{
    const particle* particles = nSystem->getParticles();
    int pX, pY;
    SDL_SetRenderDrawColor(this->visRenderer, 0,0,0,255);
    SDL_RenderClear(this->visRenderer);
    if(this->showTree){
        this->updateVisualsShowTree(nSystem);
    }
    SDL_SetRenderDrawColor(this->visRenderer, 255,255,255,255);

    double nWidth = nSystem->getFieldWidth();
    double nHeight = nSystem->getFieldHeight();
    for(int i = 0; i < nSystem->getParticleNum(); i++){
        pX = ((double)particles[i].xPos / nWidth) * this->screenWidth;
        pY = ((double)particles[i].yPos / nHeight) * this->screenHeight;

//        printf("Drawing point at %d, %d\n", pX, pY);
        if(pX >= 0 && pX <= this->screenWidth &&
           pY >= 0 && pY <= this->screenHeight){
            SDL_SetRenderDrawColor(this->visRenderer, 255, 255, 255, 255);
            SDL_RenderDrawPoint(this->visRenderer, pX, pY);
       }
    }
    SDL_RenderPresent(this->visRenderer);

    return 0;
}

int visualizer::updateVisualsShowTree(nBody* nSystem)
{
    SDL_Rect r;
    quadtree<quadNode>* qTree = nSystem->getQuadTree();
    quadtree<quadNode>* child;
    std::vector<quadtree<quadNode>*> children;
    children.push_back(qTree);
    SDL_SetRenderDrawColor(this->visRenderer, 0,0,0,255);
    SDL_SetRenderDrawColor(this->visRenderer, 255,255,255,255);
    double nWidth = nSystem->getFieldWidth();
    double nHeight = nSystem->getFieldHeight();

    while(children.size() > 0){
        child = children.back();
        children.pop_back();
        for(int i = 0; i < 4; i++){
            if(!child->isExternalNode()){
                if(child->getQuads()[i]->getValue() != nullptr){
                    children.push_back(child->getQuads()[i]);
                }
            }
        }
        r.x = (child->getstX()/nWidth) * this->screenWidth;
        r.y = (child->getstY()/nHeight) * this->screenHeight;
        r.w = (child->getsX()/nWidth) * this->screenWidth;
        r.h = (child->getsY()/nHeight) * this->screenHeight;
        SDL_RenderDrawRect(this->visRenderer, &r);
    }
    return 0;
}

int visualizer::deleteVisualizer()
{
    SDL_DestroyRenderer(this->visRenderer);
    SDL_DestroyWindow(this->visWindow);
    SDL_Quit();
    return 0;
}
