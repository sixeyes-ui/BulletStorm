#include "include/SpriteRenderer.h"
#include "include/Config.h"
#include "include/Render.h"

#include <cmath>

void SpriteRenderer::renderSprite(
    const sf::Vector2f& cameraPosition,
    float cameraAngle,
    float horizon,

    const sf::Vector2f& spritePosition,

    const sf::Image& sprite,

    const std::vector<float>& depthBuffer
)
{
    // ============================
    // Distance from camera
    // ============================

    float dx =
        spritePosition.x -
        cameraPosition.x;

    float dy =
        spritePosition.y -
        cameraPosition.y;

    float distance =
        std::sqrt(dx * dx + dy * dy);

    if (distance <= 0.001f)
        return;


    // ============================
    // Angle to sprite
    // ============================

    float spriteAngle =
        std::atan2(dy, dx);

    float angleDifference =
        spriteAngle -
        cameraAngle;


    // Normalize angle
    while (angleDifference > PI)
        angleDifference -= 2.f * PI;

    while (angleDifference < -PI)
        angleDifference += 2.f * PI;


    // ============================
    // Is sprite visible?
    // ============================

    if (std::abs(angleDifference) >
        FOV / 2.f)
    {
        return;
    }


    // ============================
    // Fix fisheye
    // ============================

    float correctedDistance =
        distance *
        std::cos(angleDifference);

    if (correctedDistance <= 0.001f)
        return;


    // ============================
    // Convert angle to screen X
    // ============================

    float normalized =
        (angleDifference + FOV / 2.f)
        / FOV;

    float screenX =
        normalized * SCREEN_WIDTH;


    // ============================
    // Calculate sprite size
    // ============================

    constexpr float PROJECTION_SCALE = 6000.f;

    float spriteHeight =
        PROJECTION_SCALE /
        correctedDistance;

    float aspectRatio =
        static_cast<float>(sprite.getSize().x) /
        static_cast<float>(sprite.getSize().y);

    float spriteWidth =
        spriteHeight *
        aspectRatio;


    // ============================
    // Screen rectangle
    // ============================

    int left =
        static_cast<int>(
            screenX -
            spriteWidth / 2.f
            );

    int right =
        static_cast<int>(
            screenX +
            spriteWidth / 2.f
            );

    int top =
        static_cast<int>(
            horizon -
            spriteHeight / 2.f
            );

    int bottom =
        static_cast<int>(
            horizon +
            spriteHeight / 2.f
            );


    // ============================
    // Draw sprite
    // ============================

    for (int x = left; x < right; x++)
    {
        if (x < 0 ||
            x >= SCREEN_WIDTH)
        {
            continue;
        }


        // Convert screen X ? texture X
        float u =
            static_cast<float>(x - left) /
            spriteWidth;

        int texX =
            static_cast<int>(
                u * sprite.getSize().x
                );

        if (texX < 0 ||
            texX >=
            static_cast<int>(sprite.getSize().x))
        {
            continue;
        }


        // Depth buffer
        int ray =
            static_cast<int>(
                static_cast<float>(x) /
                SCREEN_WIDTH *
                depthBuffer.size()
                );

        if (ray < 0 ||
            ray >=
            static_cast<int>(depthBuffer.size()))
        {
            continue;
        }


        // Behind wall?
        if (correctedDistance >=
            depthBuffer[ray])
        {
            continue;
        }


        for (int y = top; y < bottom; y++)
        {
            if (y < 0 ||
                y >= SCREEN_HEIGHT)
            {
                continue;
            }


            // Convert screen Y ? texture Y
            float v =
                static_cast<float>(y - top) /
                spriteHeight;

            int texY =
                static_cast<int>(
                    v * sprite.getSize().y
                    );

            if (texY < 0 ||
                texY >=
                static_cast<int>(sprite.getSize().y))
            {
                continue;
            }


            sf::Color pixel =
                sprite.getPixel(
                    texX,
                    texY
                );


            // Transparent pixel?
            if (pixel.a == 0)
                continue;


            Render::setPixel(
                x,
                y,
                pixel
            );
        }
    }
}