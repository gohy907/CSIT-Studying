#include "raylib.h"
#include "resources.h"
#include "resourcesControl.h" // CARS_data, CARS_size

static Texture2D g_carsAtlas = {};
static Texture2D g_carsDamagedAtlas = {};
static bool g_inited = false;

void InitResources() {
    if (g_inited) return;
    Image img = LoadImageFromMemory(".png", CARS_data, CARS_size);
    g_carsAtlas = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImageFromMemory(".png", CARSDAMAGED_data, CARSDAMAGED_size);
    g_carsDamagedAtlas = LoadTextureFromImage(img);
    UnloadImage(img);
    g_inited = true;
}

Texture2D GetCarsAtlas() {
    return g_carsAtlas;
}

Texture2D GetDamagedCarsAtlas() {
    return g_carsDamagedAtlas;
}

void UnloadResources() {
    if (!g_inited) return;
    UnloadTexture(g_carsAtlas);
    g_inited = false;
}
