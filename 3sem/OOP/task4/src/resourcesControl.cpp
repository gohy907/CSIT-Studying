#include "resources.h"
#include "resourcesControl.h" // CARS_data, CARS_size

static Texture2D g_carsAtlas = {};
static bool g_inited = false;

void InitResources() {
    if (g_inited) return;
    Image img = LoadImageFromMemory(".png", CARS_data, CARS_size);
    g_carsAtlas = LoadTextureFromImage(img);
    UnloadImage(img);
    g_inited = true;
}

Texture2D GetCarsAtlas() {
    return g_carsAtlas;
}

void UnloadResources() {
    if (!g_inited) return;
    UnloadTexture(g_carsAtlas);
    g_inited = false;
}
