#version 330

// Input
in vec3 world_position;
in vec3 world_normal;
in vec2 texcoord;



uniform vec3 obj_position;
uniform vec3 eye_position;

uniform vec3 material_ke;
uniform vec3 material_kd;
uniform vec3 material_ks;
uniform int material_shininess;
uniform int nrLights;

uniform  vec3 light_direction[70];
uniform  vec3 light_position[70];
uniform  vec3 light_color[70];


uniform vec3 SpotLight_position[4];
uniform vec3 SpotLight_direction[4];
uniform vec3 SpotLight_color[4];
uniform int is_spot;

uniform vec3 light_direction1;
uniform vec3 light_position1;
uniform int spot_light_status;

uniform int tranzitie;

uniform sampler2D texture_1;
uniform vec3 stroboPoz;
uniform int text;
uniform float time;
// TODO(student): Declare any other uniforms



// Output
layout(location = 0) out vec4 out_color;




vec3    CuloarePodea(){
         
          vec3 emisive_light = material_ke;
          return emisive_light ;

}

vec3 PointLightContribution(vec3 lightPos, vec3 lightColor, vec3 L,vec3 H)
{
	vec3 color =  vec3(0,0,0);
    float light_radius = 1.5f;
	//calculele componentelor difuze si speculare din modelul Phong de iluminare pentru lumina punctiforma
      
      
      vec3 diffuse_light = material_kd * max(dot(world_normal, L), 0);
      vec3 specular_aux;
      specular_aux = vec3(0,0,0);
      
      if (dot(world_normal, L) > 0)
          specular_aux = vec3(0.0001,0.00001,0000.1);
      vec3 specular_light = material_ks * specular_aux *
                pow(max(dot(world_normal, H), 0), material_shininess);

      
      float att = 0.f;
      float dist = distance(lightPos,world_position);
     
     if(dist < light_radius) 
     {
           att = pow(light_radius - dist, 2);

       color = lightColor * (   att * 
                                 ( diffuse_light + specular_light) 
                               );
                               
                            
     }
    


	return color;
}



// this isn't really work proprely, but that`s for sure the right way to make the stroboscop`s reflecting lights

vec3 stroboLightContribution( vec3 disco_ball_position, sampler2D textura_generata){
  


    // light_dir  este directia de iluminare
  vec3 light_dir = world_position - disco_ball_position;
 
  // texcoord este coordonata de textura utilizata pentru esantionare
  vec2 texcoord;
  texcoord.x = (1.0 / (2 * 3.14159)) * atan (light_dir.x, light_dir.z) + time/4;
  texcoord.y = (1.0 / 3.14159) * acos (light_dir.y / length (light_dir));
 
// color este culoarea corespunzatoare pozitiei world_position
vec3 color = texture (textura_generata, texcoord).xyz;

  
  
  
    return color;


}

vec3 iluminareStrobo(vec3 L, vec3 H, vec3 Antcolor){
   vec3 color;
   vec3 diffuse_light = material_kd * max(dot(world_normal, L), 0);


   float specular_aux = 0;

    if (dot(world_normal, L) > 0)
      specular_aux = 1;

    vec3 specular_light = material_ks * specular_aux *
        pow(max(dot(world_normal, H), 0), material_shininess);

   float d = distance(world_position, stroboPoz);
    float factor;
    if (d == 0)
        factor = 1;
    else
        factor = 1 / (d * d);
       
    color =    Antcolor*factor*( diffuse_light + specular_light ) ;
return color;
}




vec3    SpotLightContribution( vec3 L ,vec3 H, vec3 lightPos , vec3 lightDir, vec3 lightColor ){
      vec3 color;
    vec3 diffuse_light = material_kd * max(dot(world_normal, L), 0);


   float specular_aux = 0;

    if (dot(world_normal, L) > 0)
      specular_aux = 1;

    vec3 specular_light = material_ks * specular_aux *
        pow(max(dot(world_normal, H), 0), material_shininess);

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    float light_att_factor = 0.4;
   
          float cut_off = radians(50.0f);
        float spot_light = dot(-L, lightDir);
        float spot_light_limit = cos(cut_off);
        if (spot_light > spot_light_limit) {
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            light_att_factor = linear_att * linear_att*0.5;
        }
    

     float d = distance(world_position, lightPos);
    float factor;
    if (d == 0)
        factor = 1;
    else
        factor = 1 / (d * d);
       
    color =(material_ke +(light_att_factor * factor) * lightColor*( diffuse_light + specular_light )) ;
  

	return color;
         

}





void main()
{ 
    // TODO(student): Define ambient, diffuse and specular light components
   
   vec3 V = normalize( eye_position - world_position );

  
     vec3 color = vec3(0,0,0);
     vec3 color1 = vec3(0,0,0);
     vec3 color2 = vec3(0,0,0);
     vec3 color3 = vec3(0,0,0);
     vec4 colorText = vec4(0,0,0,0);
      
      if(text == 1 )
    { 
   
    vec4 colorText = texture2D(texture_1, texcoord); 
    
    }

     for(int i = 0;i<nrLights;i++)
       { 

        vec3 L = normalize( light_position[i] - world_position );
        
        vec3 H = normalize( L + V );
        vec3 R = reflect(-L, world_normal);
        color += PointLightContribution(light_position[i],light_color[i],L,H);
        color1 += PointLightContribution(light_position[i],light_color[i],L,H);

      }

     if(tranzitie == 1)
  { 
     if(material_kd == vec3 (0,0,0) && material_ks == vec3(0,0,0) )
            color1 += CuloarePodea();
 
  }
   
   
   for(int i = 0; i< 4;i++)
   {
   
        V = normalize( eye_position - world_position );
       vec3 L = normalize( SpotLight_position[i] - world_position );
      vec3 H = normalize( L + V );
        vec3 R = reflect(-L, world_normal);
       color += SpotLightContribution(L,H,SpotLight_position[i],SpotLight_direction[i],SpotLight_color[i]);
       color2 +=SpotLightContribution(L,H,SpotLight_position[i],SpotLight_direction[i],SpotLight_color[i]);
   }
  
  if(tranzitie == 3 && text ==1){
     
      vec3 L = normalize( stroboPoz - world_position );
      vec3 H = normalize( L + V );
      vec3 colorPix = stroboLightContribution( stroboPoz,texture_1);
       color += colorPix;
     // color += iluminareStrobo(L,H,colorPix);
  }
      

    if( tranzitie == 1 )
        out_color = vec4(color1, 0.5f);
    else
   
      if(tranzitie == 2){
      out_color = vec4(color2, 0.5f);
      }
      else
      if(tranzitie == 0)
      {out_color = vec4(color, 0.5f) ;}
       else
       if(tranzitie == 3)
         {out_color = vec4(color, 0.5f) ;}

}


