#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "figure.h"
#include "Line.h"
#include "sphere.h"
#include "videoSettings.h"

class Scene
{
private:
    std::vector<Figure *> Figures_;
    std::vector<Figure *> LightSrc_;
    Vector    ViewPoint_;
    uint32_t *Pixels_;
    Basis     Basis_;
    Vector    SkyBox_ = {0.3, 0.3, 1};

    Vector processLight(Line &Ray); 
public:
    Scene(Vector ViewPoint, Basis Basis) : Figures_(), LightSrc_(),
                                           ViewPoint_(ViewPoint), Basis_(Basis)
    {
        Pixels_ = new uint32_t [Settings::Width * Settings::Heigth];
    };

    void addFigure(Figure *fig);

    uint32_t * drawScene();

    ~Scene() { delete [] Pixels_; }
};

inline void Scene::addFigure(Figure *fig)
{
    Figures_.push_back(fig);
    
    if (fig->IsLightSrc())
        LightSrc_.push_back(fig);
}

#endif
