#pragma once

#include "mesh.h"

class Cylinder : public Mesh
{
public:

    Cylinder(float height, float baseRadius, float topRadius, int segments, int stacks) : height(height), baseRadius(baseRadius), topRadius(topRadius), segments(segments),
        stacks(stacks), unitCircle(segments){ }

private:
    class Circle
    {
    public:
        Circle(int segments) : segments(segments) { makeCircle(); }
        std::pair<float, float> getVertexPosition(int index);
    private:
        
        void makeCircle();
        int segments;
        std::vector < std::pair < float, float > > verticesPositions;

    };
    void init();
 
    std::vector<glm::vec3> getSideNormals();
    Circle unitCircle;
    GLfloat height;
    GLfloat baseRadius;
    GLfloat topRadius;
    GLint segments;
    GLint stacks;
    glm::vec3 color;

};
