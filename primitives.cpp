/*
 * primitives.cpp
 *
 *  Created on: Nov 2, 2016
 *      Author: alex
 */


#include "primitives.hpp"


void add_to_primitives(         t_primitive & scene
                        , const t_primitive & objToAdd
                        , GLfloat xOffset, GLfloat yOffset)
{
    std::size_t idxOffset = scene.first.size() / 3;

    // add new vertices
    for (std::size_t i = 0; i < objToAdd.first.size() / 3; ++i)
    {
        scene.first.push_back(objToAdd.first[i*3    ] + xOffset);
        scene.first.push_back(objToAdd.first[i*3 + 1] + yOffset);
        scene.first.push_back(objToAdd.first[i*3 + 2]          );
    }

    // add new indices with proper offset
    for (std::size_t i = 0; i < objToAdd.second.size(); ++i)
    {
        scene.second.push_back(objToAdd.second[i] + idxOffset);
    }
}


void scale_primitives(t_primitive & scene, GLfloat scale)
{
    for (auto & e : scene.first)
        e = (e + 1.0f) * scale - 1.0f;
}


void move_primitives(t_primitive & scene, GLfloat xOffset, GLfloat yOffset)
{

    for (std::size_t i = 0; i < scene.first.size() / 3; ++i)
    {
        scene.first[i*3    ] += xOffset;
        scene.first[i*3 + 1] += yOffset;
    }
}


