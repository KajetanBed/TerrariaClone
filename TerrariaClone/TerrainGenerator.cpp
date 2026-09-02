#include "TerrainGenerator.h"
#include "FastNoiseLite.h"
#include "Config.h" 
#include <cmath>
#include <ctime>

void TerrainGenerator::generateWorld(
    std::vector<std::vector<std::unique_ptr<Block>>>& world, 
    const sf::Texture& grassTex,
    const sf::Texture& dirtTex,
    const sf::Texture& stoneTex)
{
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetSeed(static_cast<int>(time(nullptr)));
    noise.SetFrequency(0.01f);

    int baseHeightY = 5;
    int maxWorldDepth = 30;

    world.clear();
    world.resize(Config::MAP_MAX_X - Config::MAP_MIN_X + 1);

    for (int x = Config::MAP_MIN_X; x <= Config::MAP_MAX_X; ++x) {

        float noiseVal = noise.GetNoise((float)x * 10.0f, 0.0f);
        int heightVariation = static_cast<int>(std::round(noiseVal * 4.0f));
        int surfaceBlockY = baseHeightY + heightVariation;

        float pixelX = x * Config::BLOCK_SIZE;
        int colIndex = x - Config::MAP_MIN_X;
        world[colIndex].push_back(std::make_unique<Grass>(grassTex, pixelX, surfaceBlockY * Config::BLOCK_SIZE));

        for (int d = 1; d <= 3; ++d) {
            world[colIndex].push_back(std::make_unique<Dirt>(dirtTex, pixelX, (surfaceBlockY + d) * Config::BLOCK_SIZE));
        }

        for (int s = surfaceBlockY + 4; s <= maxWorldDepth; ++s) {
            world[colIndex].push_back(std::make_unique<Stone>(stoneTex, pixelX, s * Config::BLOCK_SIZE));
        }
    }
}