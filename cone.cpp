#include "cone.h"
#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"





/*

Mesh* Tema3Object3D::CreateCone(const std::string& name, glm::vec3 Origin, float BaseRad, float height, float numberOfSides,glm::vec3 color) {

	Mesh* cone = new Mesh(name);

	//origin este (0,0,0)
    int numberOfVertices = numberOfSides + 2;

    float twicePi = 2.0f * M_PI;

    std::vector<VertexFormat> coneVertices;
 


    coneVertices.push_back(VertexFormat(glm::vec3(Origin.x,Origin.y,Origin.z),color));

    float x, y, z;
    x = Origin.x;
    y = Origin.y;
    z = Origin.z;

    for (int i = 1; i < numberOfVertices; i++)
    {
        x += BaseRad * cos(i * twicePi / numberOfSides);
        y;
        z += BaseRad * sin(i * twicePi / numberOfSides);
        
        
        coneVertices.push_back(VertexFormat(glm::vec3(x, y, z), color));
    }

   
    std::vector<unsigned int> coneIndices;
    for (int i = 0; i < numberOfVertices; i++)
        coneIndices.push_back(i);
    coneIndices.push_back(1);

    cone->SetDrawMode(GL_TRIANGLE_FAN);
    cone->InitFromData(coneVertices, coneIndices);

    return cone;
}
*/

Mesh* Tema3Object3D::CreateCone(const std::string& name, float nr)
{
    Mesh* cone = new Mesh(name);
    std::vector<VertexFormat> vertices_cone{
        VertexFormat(glm::vec3(0,1,0)),
   
    };
    for (int i = 0; i < nr; i++) {
        float grade = RADIANS((float)360 / nr);
        vertices_cone.push_back(VertexFormat(glm::vec3(cos(grade * i), 0, sin(grade * i))));
    }

    std::vector<unsigned int> indices_cone;
    for (int i = 0; i < nr; i++)
        indices_cone.push_back(i);
    indices_cone.push_back(1);

    cone->SetDrawMode(GL_TRIANGLE_FAN);
    cone->InitFromData(vertices_cone, indices_cone);
    return cone;
}