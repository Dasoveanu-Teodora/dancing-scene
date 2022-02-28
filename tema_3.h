#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include <vector>
#include <map>
#include "cone.h"

#define SPEED 20;

using namespace std;
namespace m1
{

    class tema_3 : public gfxc::SimpleScene
    {
    public:
        tema_3();
        ~tema_3();

        void Init() override;

        struct Info_Obj
        {
            Info_Obj(
                glm::vec3 objPosition,   // objPosition    
                unsigned int materialShininess,
                glm::vec3 materialKe,
                glm::vec3 materialKd,
                glm::vec3 materialKs) : objPosition(objPosition), materialShininess(materialShininess),
                materialKe(materialKe),
                materialKd(materialKd), materialKs(materialKs) {};
            Info_Obj() {
            
                objPosition = glm::vec3(0, 0, 0);
                materialShininess = 0;
                materialKe = glm::vec3(0, 0, 0);
                materialKd = glm::vec3(0, 0, 0);
                materialKs = glm::vec3(0, 0, 0);
           
            };
          void  resetKdKs(glm::vec3 material_kd, glm::vec3 material_ks) {
              materialKd = material_kd;
              materialKs = material_ks;
            };

          void resetKe(glm::vec3 material_ke) {
              materialKe = material_ke;

          };
        

         
            glm::vec3 objPosition;
            unsigned int materialShininess;
            glm::vec3 materialKe;
            glm::vec3 materialKd;
            glm::vec3 materialKs;
        
        };



    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMeshTema3(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,const Info_Obj & ob, Texture2D* texture1 = NULL);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void MoveDancers(float deltaTimeSeconds);

       Texture2D* CreateRandomTextureTema3(unsigned int width, unsigned int height);
        void ResetColor();
       std::unordered_map<std::string, Texture2D*> tema3Texture;
       int text = 0;
       glm::vec3 floor = glm::vec3(5,0,5);
        float dimBucata = floor.x / 8;
         
        glm::vec3 perete1 = glm::vec3(0, 3, 5);
     

        
      
        float dimBucataPereteY = perete1.y;
        float dimBucataPereteXZ= perete1.z /7 ;
        

        
        vector<Info_Obj> bucati;
        vector<Info_Obj> celulePereteStanga;
        vector<Info_Obj> celulePereteSpate;
        vector<Info_Obj> celulePereteDreapta;
        vector<Info_Obj> dansatori;
        vector<Info_Obj> ceiling;
        vector<Info_Obj> floorlights;
        vector<Info_Obj> Conuri;
        Info_Obj  stroboscop;
        float xDansatori = 0.3;
        float zDansatori = 0.3;
        float yDansatori = 0.5;
        float RandomRot = 0;
        float heightCone = 3;
        float spot_angle =14.f;
        float rotation1 = 0;

      vector< glm::vec3> lightPosition;
      vector< glm::vec3> lightDirection;
      vector< glm::vec3> intensity;
      vector< glm::vec3> lightColor;



      vector<glm::vec3> SpotLightPos;
      vector<glm::vec3> SpotLightDir;
      vector<glm::vec3> SpotLightColor;
      float spot_dist = 1;
      float spot_dist2 = 3;
      float stroboscopX = 2.f;
      float stroboscopZ = 2.f;
       float stroboscopY = 2.5f;

      


        // TODO(student): If you need any other class variables, define them here.
        int spot_light_status = 0;
        float rotation = 0;
        float translateX = 0;
        float translateY = 0;
        float translateZ = 0;
        glm::vec3  rotObjPosition;
        float coef;
        float rad;
        int direction = 0;
      
        int iluminare = 0;
        float dist = 0;
        float spot_height = 0.6;
        int model_iluminare = 0;
       // int text = 0;
    };
}   // namespace m1
