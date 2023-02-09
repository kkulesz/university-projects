#include "../../include/meshes/cylinder.h"

#include <cmath>
#include <iostream>



void Cylinder::init()
{
    float z;
    float radius; 
    std::vector<glm::vec3> sideNormals = getSideNormals();
    for (int i = 0; i <= stacks; ++i)
    {
        z = -(height * 0.5f) + (float)i / stacks * height;
        radius = baseRadius +(float) i / stacks * (topRadius - baseRadius);
        float texV = 1.0f - (float)i / stacks;

        for (int j = 0; j <= segments; ++j)
        {
            std::pair<float, float> circleSegmentPos = unitCircle.getVertexPosition(j);
            vertices.push_back(Vertex(glm::vec3(circleSegmentPos.first * radius, circleSegmentPos.second * radius, z), color, glm::vec2(j / segments, texV), sideNormals[j]));
        }
    }

    unsigned int baseVertexIndex = 0;

    vertices.push_back(Vertex(glm::vec3(0, 0, z), color, glm::vec2(0.5f, 0.5f), glm::vec3(0, 0, -1)));
    for (int i = 0; i < segments; ++i)
    {
        std::pair<float, float> circleSegmentPos = unitCircle.getVertexPosition(i);
        vertices.push_back(Vertex(glm::vec3(circleSegmentPos.first * baseRadius, circleSegmentPos.second * baseRadius, z), color,
            glm::vec2(-circleSegmentPos.first * 0.5f + 0.5f, -circleSegmentPos.second* 0.5f + 0.5f), glm::vec3(0, 0, -1)));

    }

    unsigned int topVertexIndex = vertices.size();

    z = height * 0.5f;
    vertices.push_back(Vertex(glm::vec3(0, 0, z), color, glm::vec2(0.5f, 0.5f), glm::vec3(0, 0, 1)));
    for (int i = 0; i < (int) segments; ++i)
    {
        std::pair<float, float> circleSegmentPos = unitCircle.getVertexPosition(i);
        vertices.push_back(Vertex(glm::vec3(circleSegmentPos.first * topRadius, circleSegmentPos.second * topRadius, z), color,
            glm::vec2(circleSegmentPos.first * 0.5f + 0.5f, -circleSegmentPos.second * 0.5f + 0.5f), glm::vec3(0, 0, 1)));

    }

    unsigned int k1, k2;
    for (int i = 0; i < stacks; ++i)
    {
        k1 = i * (segments + 1);
        k2 = k1 + segments + 1;

        for (int j = 0; j < segments; ++j, ++k1, ++k2)
        {
            indices.push_back(k1);
            indices.push_back(k1 + 1); 
            indices.push_back(k2);
            indices.push_back(k2);
            indices.push_back(k1 + 1);
            indices.push_back(k2 + 1);
        }
    }

    for (int i = 0, k = baseVertexIndex + 1; i < segments; ++i, ++k)
    {
        if (i < (segments - 1)) {
            indices.push_back(baseVertexIndex);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
        else {
            indices.push_back(baseVertexIndex);
            indices.push_back(baseVertexIndex + 1);
            indices.push_back(k);
        }
    }

    for (int i = 0, k = topVertexIndex + 1; i < segments; ++i, ++k)
    {
        if (i < (segments - 1)) {
            indices.push_back(topVertexIndex);
            indices.push_back(k);
            indices.push_back(k + 1);
        }
        else {
            indices.push_back(topVertexIndex);
            indices.push_back(k);
            indices.push_back(topVertexIndex + 1);
        }
    }
 
}

std::vector<glm::vec3> Cylinder::getSideNormals()
{
    const float PI = acos(-1);
    float segmentStep = 2 * PI / segments;
    float segmentAngle;

    float zAngle = atan2(baseRadius - topRadius, height);
    float x = cos(zAngle);
    float z = sin(zAngle);

    std::vector<glm::vec3> normals;

    for (int i = 0; i <= segments; ++i)
    {
        segmentAngle = i * segmentStep;
        normals.push_back(glm::vec3(cos(segmentAngle) * x, sin(segmentAngle) * x, z));
    }

    return normals;
}


std::pair<float, float> Cylinder::Circle::getVertexPosition(int index)
{
    return verticesPositions[index];
}

void Cylinder::Circle::makeCircle()
{
    const float PI = acos(-1);
    float segmentStep = 2 * PI / segments;
    float segmentAngle;

    for (int i = 0; i <= segments; ++i)
    {
        segmentAngle = i * segmentStep;
        verticesPositions.push_back(std::make_pair<float, float> (cos(segmentAngle), sin(segmentAngle)));
    }
}