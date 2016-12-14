/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <iostream>
#include <mb/mb.h>
#include <shaderFiles.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc( float dt );

mb::PostProcessMaterial *ppm1, *ppm2;

mb::Framebuffer* fbo;

mb::CustomPingPong<mb::Texture*>* customPP;
mb::Texture2D *tex1;
int main(void)
{
    mb::GLContext context(3, 3, 512, 512, "Advention demo");

    mb::TexOptions opts;
    opts.minFilter = mb::ctes::TextureFilter::Nearest;
    opts.magFilter = mb::ctes::TextureFilter::Nearest;
    opts.type = GL_FLOAT;

    unsigned int ww = context.getWidth();
    unsigned int hh = context.getHeight();

    float h = 2.0f / ww;

    std::vector<float> pixels; // TODO: OPTIMIZE (ww * hh * 4);
    pixels.reserve(ww * hh * 4);
    unsigned int Ro = 0.3f;
    for (unsigned int i = 0; i < ww; ++i)
    {
        for (unsigned int j = 0; j < hh; ++j)
        {
            float x = h * (j - ww / 2.0f), 
                  y = h * (i - hh / 2.0f), 
                  exp = std::exp(-4.0f * (x * x + y * y));
            pixels.push_back(exp * y);
            pixels.push_back(-exp * x);
            pixels.push_back(3.0f * std::exp(-30.0f * 
                ((x - Ro) * (x - Ro) + y * y)));
            pixels.push_back(1.0f);
        }
    }

    tex1 = new mb::Texture2D(opts, pixels.data(),
        context.getWidth(), context.getHeight());
    mb::Texture2D *tex2 = new mb::Texture2D(opts, pixels.data(),
        context.getWidth(), context.getHeight());

    customPP = new mb::CustomPingPong<mb::Texture*>(tex1, tex2);
    std::vector<mb::Texture*> textures = { tex1, tex2 };
    fbo = new mb::Framebuffer(textures, 
        mb::Vect2(context.getWidth(), context.getHeight()));

    engine = new mb::Engine(&context, false);
    scene = new mb::Scene(engine);

    std::ifstream file1(MB_SHADER_FILES_ADVENTION_FIRST_FRAG);
    std::stringstream buffer1;
    buffer1 << file1.rdbuf();

    ppm1 = new mb::PostProcessMaterial(buffer1.str().c_str( ));

    ppm1->addUniform("tex", new mb::Uniform(mb::Integer, 0));


    std::ifstream file2(MB_SHADER_FILES_ADVENTION_SECOND_FRAG);
    std::stringstream buffer2;
    buffer2 << file2.rdbuf();

    ppm2 = new mb::PostProcessMaterial(buffer2.str().c_str( ));

    ppm2->addUniform("tex", new mb::Uniform(mb::Integer, 0));


    engine->run(renderFunc);

    delete(scene);
    delete(engine);

    return 0;
}

void swap()
{
    customPP->first()->bind(0);
    fbo->bind();
    fbo->replaceTexture(customPP->last(), 0);
}

float globalTime = 0.0f;
void renderFunc(float /*dt*/)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //globalTime += dt;
    swap();
    ppm1->renderPP();
    fbo->unbind();

    tex1->bind(0);
    ppm2->renderPP();
}
