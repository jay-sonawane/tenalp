#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D night;
        
    float shininess;
}; 


struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};



in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;



void main()
{
 
  vec3 ambient;
    
  	
    // diffuse 
    vec3 diffuse;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = dot(norm, lightDir);
    vec3 t0 = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 t1 = light.ambient * texture(material.night, TexCoords).rgb;
    
    if(diff>=0)
    {
    
     diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    }
    if(diff<=0)
    {
     
     diffuse = light.diffuse * diff * texture(material.night, TexCoords).rgb;  
    }
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
    float y = smoothstep(-0.4, 0.4, diff);
    vec3 t = t0*y + t1*(1-y);
        
    vec3 result = t + /*diffuse*/ + specular;
    FragColor = vec4(result, 1.0);
   
}
