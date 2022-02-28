#include "lab_m1/tema_3/tema_3.h"


#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema_3::tema_3()
{
    coef = 1.f;
    rad = 3.f;
    rotObjPosition = glm::vec3(rad, 0, 0);
}


tema_3::~tema_3()
{
}


void tema_3::Init()
{  


    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("Tema3Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema_3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema_3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    
 

    {
        tema3Texture["Stroboscop"] = CreateRandomTextureTema3(16, 16);
    }








    for(int x = 0; x < 7; x++ )
        for (int y = 0; y < 7; y++)
        {     
            glm::vec3 objPos;
           // glm::vec3 objDir;
            unsigned int matShin;
            glm::vec3 mKe;
            glm::vec3 mKd;
            glm::vec3 mKs;
            
            objPos = glm::vec3(dimBucata * x, 0, dimBucata * y);
            lightPosition.push_back(objPos);
            lightDirection.push_back(glm::vec3(0, 1, 0));
            

            matShin = 5;
           
           mKe = glm::vec3( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
         //  mKe = glm::vec3(0, 0, 0);
     
         
              mKd = glm::vec3(0.1, 0.2, 0.1);
              mKs = glm::vec3(0.1, 0.1, 0.2);
         
            lightColor.push_back(mKe);
            bucati.push_back(Info_Obj(objPos, matShin, mKe, mKd, mKs));
         
            objPos = glm::vec3(dimBucata * x,perete1.y, dimBucata * y);
            
            ceiling.push_back(Info_Obj(objPos,  matShin, mKe, mKd, mKs));
        }
    //Poszitionare Spot-uri
  {
        Mesh* cone = Tema3Object3D::CreateCone("cone", 40);
        AddMeshToList(cone);

        glm::vec3 lightPos;
        glm::vec3 lightDir;
        unsigned int matShin;
        glm::vec3 mKe;
        glm::vec3 mKd;
        glm::vec3 mKs;
        glm::vec3 spot_pos;
        glm::vec3 spot_dir;
        glm::vec3 spot_color;

        //Con1 
        {
            

            
            spot_pos = glm::vec3(spot_dist, spot_height,spot_dist);
            SpotLightPos.push_back(spot_pos);
            spot_dir = glm::vec3(0, -1, 0);
            SpotLightDir.push_back(spot_dir);
            spot_color = glm::vec3(1, 0, 0);
            SpotLightColor.push_back(spot_color);
            lightPos = glm::vec3(spot_dist, 0, spot_dist);
            matShin = 20;
            mKd = glm::vec3(0.1, 0.1, 0.2);
            mKs = glm::vec3(0.3, 0.2, 0.2);

            mKe = spot_color;
            Conuri.push_back(Info_Obj(lightPos, matShin, mKe, mKd, mKs));

        }
       // Coon 2

        {   
            

            spot_pos = glm::vec3(spot_dist2, spot_height, spot_dist);
            SpotLightPos.push_back(spot_pos);
            spot_dir = glm::vec3(0, -1, 0);
            SpotLightDir.push_back(spot_dir);
            spot_color = glm::vec3(0, 1, 0);
            SpotLightColor.push_back(spot_color);
            lightPos = glm::vec3(spot_dist2, 0, spot_dist);
          
            matShin = 20;
            mKd = glm::vec3(0.1, 0.1, 0.2);
            mKs = glm::vec3(0.3, 0.2, 0.2);

            mKe = spot_color;
            Conuri.push_back(Info_Obj(lightPos, matShin, mKe, mKd, mKs));
        }
       //Con3
        {
         

            spot_pos = glm::vec3(spot_dist, spot_height, spot_dist2);
            SpotLightPos.push_back(spot_pos);
            spot_dir = glm::vec3(0, -1, 0);
            SpotLightDir.push_back(spot_dir);
            spot_color = glm::vec3(0, 0, 1);
            SpotLightColor.push_back(spot_color);
            lightPos = glm::vec3(spot_dist, 0, spot_dist2);
            matShin = 20;
            mKd = glm::vec3(0.1, 0.1, 0.2);
            mKs = glm::vec3(0.3, 0.2, 0.2);


            mKe = spot_color;
            Conuri.push_back(Info_Obj(lightPos, matShin, mKe, mKd, mKs));

        }
        //Con4
        {
           
            spot_pos = glm::vec3(spot_dist2, spot_height, spot_dist2);
            SpotLightPos.push_back(spot_pos);
            spot_dir = glm::vec3(0, -1, 0);
            SpotLightDir.push_back(spot_dir);
            spot_color = glm::vec3(0.5, 0.5, 0);
            SpotLightColor.push_back(spot_color);
            lightPos = glm::vec3(spot_dist2, 0, spot_dist2);
            matShin = 20;
            mKd = glm::vec3(0.1, 0.1, 0.2);
            mKs = glm::vec3(0.3, 0.2, 0.2);



            mKe = spot_color;
            Conuri.push_back(Info_Obj(lightPos, matShin, mKe, mKd, mKs));
        }


    }



    //perete stanga

    for(int x = 0; x < 7; x++)
    {
            glm::vec3 objPos;
            glm::vec3 objDir;
            unsigned int matShin;
            glm::vec3 mKe;
            glm::vec3 mKd;
            glm::vec3 mKs;

            objPos = glm::vec3(-0.3, dimBucataPereteY / 2 ,dimBucataPereteXZ * x);
          
            matShin = 5;
            mKe = glm::vec3(0, 0, 0);
            mKd = glm::vec3(0.1, 0.2, 0.1);
            mKs = glm::vec3(0.3, 0.5, 0.6);

           celulePereteStanga.push_back(Info_Obj ( objPos,
           matShin, mKe, mKd, mKs));

        }

    //perete spate
    for (int x = 0; x < 7; x++)
    {
        glm::vec3 objPos;
        glm::vec3 objDir;
        unsigned int matShin;
        glm::vec3 mKe;
        glm::vec3 mKd;
        glm::vec3 mKs;

        objPos = glm::vec3(dimBucataPereteXZ * x, dimBucataPereteY / 2, -0.3);

        matShin = 5;
        mKe = glm::vec3(0, 0, 0);
        mKd = glm::vec3(0.1, 0.2, 0.1);
        mKs = glm::vec3(0.3, 0.5, 0.6);

        celulePereteSpate.push_back(Info_Obj(objPos,
            matShin, mKe, mKd, mKs));

    }

    //perete dreapta
    for (int x = 0; x < 7; x++)
    {
        glm::vec3 objPos;
        glm::vec3 objDir;
        unsigned int matShin;
        glm::vec3 mKe;
        glm::vec3 mKd;
        glm::vec3 mKs;

        objPos = glm::vec3( -0.2+ dimBucataPereteXZ* 6, dimBucataPereteY / 2, dimBucataPereteXZ * x);

        matShin = 5;
        mKe = glm::vec3(0, 0, 0);
        mKd = glm::vec3(0.1, 0.2, 0.1);
        mKs = glm::vec3(0.3, 0.5, 0.6);

        celulePereteDreapta.push_back(Info_Obj(objPos,
            matShin, mKe, mKd, mKs));

    }


    for (int j = 0; j <= 3; j++)
    {
        glm::vec3 objPos;
        unsigned int matShin;
        glm::vec3 mKe;
        glm::vec3 mKd;
        glm::vec3 mKs;
       
        objPos = glm::vec3( j, yDansatori / 2, j +1 );
   
        matShin = 5;
        mKe = glm::vec3(0, 0, 0);
        mKd = glm::vec3(0.2, 0.4, 0.6);
        mKs = glm::vec3(0.3, 0.5, 0.6);

        dansatori.push_back(Info_Obj(objPos,  matShin, mKe, mKd, mKs));

    }

   
    //DiscoGlobe
    {
        glm::vec3 objPos;
        objPos = glm::vec3(stroboscopX, stroboscopY, stroboscopZ);
        unsigned int matShin;
        glm::vec3 mKe;
        glm::vec3 mKd;
        glm::vec3 mKs;
        matShin = 10;
        mKe = glm::vec3(0, 0, 0);
        mKd = glm::vec3(0.2, 0.4, 0.6);
        mKs = glm::vec3(0.3, 0.5, 0.6);

        stroboscop = Info_Obj(objPos, matShin, mKe, mKd, mKs);

    }

    
   
}


void tema_3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void tema_3::Update(float deltaTimeSeconds)
{
   
    text = 0;
     

    int i = 0;
    for (auto it = bucati.begin(); it != bucati.end(); it++)
    {
       
        if (model_iluminare == 1)
        {
            it->resetKdKs(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

        }
        else
            if (model_iluminare == 0)
            {
                it->resetKdKs(glm::vec3(0.1, 0.2, 0.1), glm::vec3(0.1, 0.1, 0.2));

            }else
                if (model_iluminare == 2) {
                    it->resetKe(glm::vec3(0, 0, 0));
                    it->resetKdKs(glm::vec3(0, 0.2, 0.1), glm::vec3(0.1, 0.1, 0.2));
                }

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3((*it).objPosition));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(dimBucata, 0.1, dimBucata));
        RenderSimpleMeshTema3(meshes["box"], shaders["Tema3Shader"], modelMatrix, bucati[i]);
        i++;
    }


    i = 0;
    for (auto it = celulePereteStanga.begin(); it != celulePereteStanga.end(); it++)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3((*it).objPosition));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1,dimBucataPereteY, dimBucataPereteXZ));
        RenderSimpleMeshTema3(meshes["box"], shaders["Tema3Shader"], modelMatrix, celulePereteStanga[i]);
        i++;
    }

    i = 0;
    for (auto it = celulePereteSpate.begin(); it != celulePereteSpate.end(); it++)
    {

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3((*it).objPosition));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(dimBucataPereteXZ, dimBucataPereteY,0.1 ));
        RenderSimpleMeshTema3(meshes["box"], shaders["Tema3Shader"], modelMatrix, celulePereteSpate[i]);
        i++;
    }

    i = 0;
    for (auto it = celulePereteDreapta.begin(); it != celulePereteDreapta.end(); it++)
    {

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3((*it).objPosition));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, dimBucataPereteY, dimBucataPereteXZ));
        RenderSimpleMeshTema3(meshes["box"], shaders["Tema3Shader"], modelMatrix, celulePereteDreapta[i]);
        i++;
    }



    //miscare dansatori
    i = 0;
   
   for (auto it = dansatori.begin(); it != dansatori.end(); it++)
   { 
      
       text = 0;
        glm::mat4 modelMatrix = glm::mat4(1);

        float speed = 0.6f;
        rotation += 0.4 * cos(deltaTimeSeconds);
      



        switch (direction)
        {
        case 0:
            (*it).objPosition.x += speed * deltaTimeSeconds;
            dist += speed * deltaTimeSeconds;
            if (dist > 2)
            {
                dist = 0;
                direction = 1;
            }
            break;

        case 1:
            it->objPosition.z -= speed * deltaTimeSeconds;

            dist += speed * deltaTimeSeconds;
            if (dist > 2)
            {
                dist = 0;
                direction = 2;
            }
            break;

        case 2:
            it->objPosition.z += speed * deltaTimeSeconds;

            dist += speed * deltaTimeSeconds;
            if (dist> 2)
            {
                dist= 0;
                direction = 3;
            }
            break;


        case 3:
            it->objPosition.x -= speed * deltaTimeSeconds;

            dist += speed * deltaTimeSeconds;
            if (dist > 2)
            {
                dist = 0;
                direction = 0;
            }
            break;

        }


      
        modelMatrix = glm::translate(modelMatrix, glm::vec3((*it).objPosition.x , (*it).objPosition.y, (*it).objPosition.z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(xDansatori,yDansatori, zDansatori));
        modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0, 1, 0));
        RenderSimpleMeshTema3(meshes["box"], shaders["Tema3Shader"], modelMatrix, dansatori[i]);
        i++;
    }
  
   
   i = 0;
    for (auto it = ceiling.begin(); it != ceiling.end(); it++)
   {
        if (model_iluminare == 2) {
            it->resetKe(glm::vec3(0, 0, 0));

        }
        else
        {
            ResetColor();
        }
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix,(*it).objPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(dimBucata, 0.1, dimBucata));
        RenderSimpleMeshTema3(meshes["box"], shaders["Tema3Shader"], modelMatrix, ceiling[i],tema3Texture[""]);
        i++;
    }



    if (model_iluminare != 1)
    {
        i = 0;
        for (auto it = Conuri.begin(); it != Conuri.end(); it++)
        {

            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            // aceasta directiva este folosita pentru nu se scrie in depth buffer
            glDepthMask(GL_FALSE);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, it->objPosition);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(tan( RADIANS(spot_angle)) *heightCone, heightCone, tan(RADIANS(spot_angle)) * heightCone));
       

            RenderSimpleMeshTema3(meshes["cone"], shaders["Tema3Shader"], modelMatrix, Conuri[i]);


            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);
            glDisable(GL_CULL_FACE);
            i++;
        }
    }


    text = 1;

    if(text == 1 && model_iluminare == 3)
    {
        //rotation1 += 0.4 * cos(deltaTimeSeconds);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, stroboscop.objPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(rotation1), glm::vec3(0, 1, 0));
        RenderSimpleMeshTema3(meshes["sphere"], shaders["Tema3Shader"], modelMatrix, stroboscop, tema3Texture["Stroboscop"]);
    }

}


void tema_3::FrameEnd()
{

}


void tema_3::RenderSimpleMeshTema3(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,const  Info_Obj & ob, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);


    // Set shader uniforms for SpotLight properties

    glUniform1f(glGetUniformLocation(shader->program, "time"), Engine::GetElapsedTime());
   
       glUniform1i(glGetUniformLocation(shader->program, "text"),text);
   
    glUniform3fv(glGetUniformLocation(shader->program, "SpotLight_position") , SpotLightPos.size(), glm::value_ptr(SpotLightPos[0]));


    glUniform3fv(glGetUniformLocation(shader->program, "SpotLight_direction") , SpotLightDir.size(), glm::value_ptr(SpotLightDir[0]));


    glUniform3fv(glGetUniformLocation(shader->program, "SpotLight_color"), SpotLightColor.size(), glm::value_ptr(SpotLightColor[0]));
   
    
    

    
    // Set shader uniforms for light properties

    
    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_position, lightPosition.size(),glm::value_ptr(lightPosition[0]));



    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3fv(light_direction, lightDirection.size(), glm::value_ptr(lightDirection[0]) );


    glUniform3fv(glGetUniformLocation(shader->program, "light_color"), lightColor.size(), glm::value_ptr(lightColor[0]));

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);




    // Set material property uniforms (shininess, kd, ks, object color) 


    glUniform3f(glGetUniformLocation(shader->program, "obj_position"), ob.objPosition.x,ob. objPosition.y,ob. objPosition.z);

    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess,ob.materialShininess);

    int locNrLigh = glGetUniformLocation(shader->program, "nrLights");
    glUniform1i(locNrLigh, lightPosition.size());

    int material_ke = glGetUniformLocation(shader->program, "material_ke");
    glUniform3f(material_ke, ob.materialKe.x, ob.materialKe.y, ob.materialKe.z);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform3f(material_kd, ob.materialKd.x, ob.materialKd.y, ob.materialKd.z);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform3f(material_ks, ob.materialKs.x, ob.materialKs.y, ob.materialKs.z);
    //Stroboscop positions

    glUniform3f(glGetUniformLocation(shader->program, "stroboPoz"), ob.objPosition.x, ob.objPosition.y, ob.objPosition.z);

//  ca sa trec prin iluminari                
    glUniform1i(glGetUniformLocation(shader->program, "tranzitie"), model_iluminare);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));




    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema_3::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));


    }
}


void tema_3::OnKeyPress(int key, int mods)
{
    // Add key press event
    //for switching scenes 
  
    if (key == GLFW_KEY_T && model_iluminare == 0)
    {
        model_iluminare = 1;
    }
    else
        if (key == GLFW_KEY_T && model_iluminare == 1)
        {
            model_iluminare = 2;
        }
        else
            if (key==GLFW_KEY_T && model_iluminare == 2)
            {
                model_iluminare =3 ;
            }
            else
                if (key == GLFW_KEY_T && model_iluminare == 3)
                {
                    model_iluminare = 0;
                }
         


}


void tema_3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema_3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void tema_3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void tema_3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void tema_3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema_3::OnWindowResize(int width, int height)
{
}

void tema_3::ResetColor()
{
    for (int i = 0; i < bucati.size(); i++) {

        bucati[i].materialKe = lightColor[i];
        ceiling[i].materialKe = lightColor[i];
    }

}


Texture2D* tema_3::CreateRandomTextureTema3(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    // TODO(student): Generate random texture data
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 128;
    }
    // TODO(student): Generate and bind the new texture ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);


    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }
    // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri

   //TASK 7
   //GL_TEXTURE_MAG_FILTER:  cu gl_nearest  fiecare fragment de 
    //culoare se vede detaliat (selecteaza pixelul al carui centru este cel mai aproape de coordonatele de texturare),
    //  nu se ameseteca culorile  vertexilor,
    //iar la GL_linear se interpoleaza culorile, se vede asa mai blur-at, dar aproximeaza mai bine culorile

      //GL_TEXTURE_MIN_FILTER: gl_nearest : acelasi aranjament ca la MAG, sunt alesi aceiasi texeli 
      //  gl_linear , GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
    //GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR      - pt toate metodele de filtrare se face interpolarea  


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   


    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // TODO(student): Generate texture mip-maps
    glGenerateMipmap(GL_TEXTURE_2D);

    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}
