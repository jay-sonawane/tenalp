#include "gl_framework.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "camera.h"
#include "shader.h"
#include "Sphere.cpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

unsigned int loadTexture(const char *path);
unsigned int loadCubemap(std::vector<std::string> faces);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//LIGHTENINGS , MAPS
bool blinn = false;
bool blinnKeyPressed = false;
bool dirLight = true;
bool dirLightKeyPressed = false;
bool spotLight = false;
bool spotLightKeyPressed = false;
bool pointLight = false;
bool pointLightKeyPressed = false;
bool np = false;
bool npPressed = false;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 20.f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

glm::vec3 lightPos(50.0f, 0.0f , 2.0f);
const float fRotationRate3 = 20.0f;
float g_fSunRotation = 0.0f;
unsigned int vertexCountPerRow = (unsigned int)pow(2, 4) + 1;
float radius=1.0;


float earthrad=radius;
glm::vec4 earthPos(0.0f, 0.0f, 0.0f,1.0f);

glm::vec4 sunPos(30,0,0,0);
 glm::vec3 orbit(60.0f, 0.0f, 0.0f);




//-----------------------------------------------------------------

std::vector<unsigned int> tempindices;
std::vector<unsigned int> tempindices1;
std::vector<float> tempvertices;
std::vector<float> tempnormals;
std::vector<float> temptexCoords;
std::vector<float> tempvertices1;
std::vector<float> tempvertices2;
std::vector<float> tempvertices3;
std::vector<float> tempvertices4;
std::vector<float> tempvertices5;
std::vector<float> tempvertices6;
std::vector<float> tempnormals1;
std::vector<float> tempnormals2;
std::vector<float> tempnormals3;
std::vector<float> tempnormals4;
std::vector<float> tempnormals5;
std::vector<float> tempnormals6;



void addNormals(const float n1[3], const float n2[3], const float n3[3], const float n4[3])
{
    tempnormals.insert(tempnormals.end(), n1, n1 + 3);  // n1
    tempnormals.insert(tempnormals.end(), n2, n2 + 3);  // n2
    tempnormals.insert(tempnormals.end(), n3, n3 + 3);  // n3
    tempnormals.insert(tempnormals.end(), n4, n4 + 3);  // n4
}


void addNormal(float nx, float ny, float nz)
{
    tempnormals.push_back(nx);
    tempnormals.push_back(ny);
    tempnormals.push_back(nz);
}

void addNormal1(float nx, float ny, float nz)
{
    tempnormals1.push_back(nx);
    tempnormals1.push_back(ny);
    tempnormals1.push_back(nz);
}
void addNormal2(float nx, float ny, float nz)
{
    tempnormals2.push_back(nx);
    tempnormals2.push_back(ny);
    tempnormals2.push_back(nz);
}
void addNormal3(float nx, float ny, float nz)
{
    tempnormals3.push_back(nx);
    tempnormals3.push_back(ny);
    tempnormals3.push_back(nz);
}

void addNormal4(float nx, float ny, float nz)
{
    tempnormals4.push_back(nx);
    tempnormals4.push_back(ny);
    tempnormals4.push_back(nz);
}

void addNormal5(float nx, float ny, float nz)
{
    tempnormals5.push_back(nx);
    tempnormals5.push_back(ny);
    tempnormals5.push_back(nz);
}

void addNormal6(float nx, float ny, float nz)
{
    tempnormals6.push_back(nx);
    tempnormals6.push_back(ny);
    tempnormals6.push_back(nz);
}


void addTexCoord(float s, float t)
{
    temptexCoords.push_back(s);
    temptexCoords.push_back(t);
}






void addVertices(const float v1[3], const float v2[3], const float v3[3], const float v4[3])
{
    tempvertices.insert(tempvertices.end(), v1, v1 + 3);    // v1
    tempvertices.insert(tempvertices.end(), v2, v2 + 3);    // v2
    tempvertices.insert(tempvertices.end(), v3, v3 + 3);    // v3
    tempvertices.insert(tempvertices.end(), v4, v4 + 3);    // v4
}

void addVertex(float x, float y, float z)
{
    tempvertices.push_back(x);
    tempvertices.push_back(y);
    tempvertices.push_back(z);
}

void addVertex1(float x, float y, float z)
{
    tempvertices1.push_back(x);
    tempvertices1.push_back(y);
    tempvertices1.push_back(z);
}

void addVertex2(float x, float y, float z)
{
    tempvertices2.push_back(x);
    tempvertices2.push_back(y);
    tempvertices2.push_back(z);
}
void addVertex3(float x, float y, float z)
{
    tempvertices3.push_back(x);
    tempvertices3.push_back(y);
    tempvertices3.push_back(z);
}

void addVertex4(float x, float y, float z)
{
    tempvertices4.push_back(x);
    tempvertices4.push_back(y);
    tempvertices4.push_back(z);
}

void addVertex5(float x, float y, float z)
{
    tempvertices5.push_back(x);
    tempvertices5.push_back(y);
    tempvertices5.push_back(z);
}

void addVertex6(float x, float y, float z)
{
    tempvertices6.push_back(x);
    tempvertices6.push_back(y);
    tempvertices6.push_back(z);
}









void addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    tempindices.push_back(i1);
    tempindices.push_back(i2);
    tempindices.push_back(i3);
}
void addIndices1(unsigned int i1, unsigned int i2, unsigned int i3)
{
    tempindices1.push_back(i1);
    tempindices1.push_back(i2);
    tempindices1.push_back(i3);
}


void scaleVertex(float v[3], float scale)
{
    v[0] *= scale;
    v[1] *= scale;
    v[2] *= scale;
}



float computeScaleForLength(const float v[3], float length)
{
    
    return length / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}



std::vector<float> getUnitPositiveX(unsigned int pointsPerRow)
{
    const float DEG2RAD = acos(-1) / 180.0f;

    std::vector<float> vertices;
    float n1[3];        // normal of longitudinal plane rotating along Y-axis
    float n2[3];        // normal of latitudinal plane rotating along Z-axis
    float v[3];         // direction vector intersecting 2 planes, n1 x n2
    float a1;           // longitudinal angle along y-axis
    float a2;           // latitudinal angle
    float scale;

    // rotate latitudinal plane from 45 to -45 degrees along Z-axis
    for(unsigned int i = 0; i < pointsPerRow; ++i)
    {
        // normal for latitudinal plane
        a2 = DEG2RAD * (45.0f - 90.0f * i / (pointsPerRow - 1));
        n2[0] = -sin(a2);
        n2[1] = cos(a2);
        n2[2] = 0;

        // rotate longitudinal plane from -45 to 45 along Y-axis
        for(unsigned int j = 0; j < pointsPerRow; ++j)
        {
            // normal for longitudinal plane
            a1 = DEG2RAD * (-45.0f + 90.0f * j / (pointsPerRow - 1));
            n1[0] = -sin(a1);
            n1[1] = 0;
            n1[2] = -cos(a1);

            // find direction vector of intersected line, n1 x n2
            v[0] = n1[1] * n2[2] - n1[2] * n2[1];
            v[1] = n1[2] * n2[0] - n1[0] * n2[2];
            v[2] = n1[0] * n2[1] - n1[1] * n2[0];

            // normalize direction vector
            scale = computeScaleForLength(v, 1);
            v[0] *= scale;
            v[1] *= scale;
            v[2] *= scale;

            vertices.push_back(v[0]);
            vertices.push_back(v[1]);
            vertices.push_back(v[2]);

            // DEBUG
            //std::cout << "vertex: (" << v[0] << ", " << v[1] << ", " << v[2] << "), "
            //          << sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]) << std::endl;
        }
    }

    return vertices;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void buildVerticesSmooth()
{
    // generate unit-length verties in +X face
    
    tempindices1.clear();
    tempindices.clear();
    tempvertices.clear();
    tempvertices1.clear();
    tempvertices2.clear();
    tempvertices3.clear();
    tempvertices4.clear();
    tempvertices5.clear();
    tempvertices6.clear();
    tempnormals.clear();
    tempnormals1.clear();
    tempnormals2.clear();
    tempnormals3.clear();
    tempnormals4.clear();
    tempnormals5.clear();
    tempnormals6.clear();
    temptexCoords.clear();
    
    std::vector<float> unitVertices = getUnitPositiveX(vertexCountPerRow);

    // clear memory of prev arrays

    float x, y, z, s, t;
    int k = 0, k1, k2;

    // build +X face
    for(unsigned int i = 0; i < vertexCountPerRow; ++i)
    {
        k1 = i * vertexCountPerRow;     // index for curr row
        k2 = k1 + vertexCountPerRow;    // index for next row
        t = (float)i / (vertexCountPerRow - 1);

        for(unsigned int j = 0; j < vertexCountPerRow; ++j, k += 3, ++k1, ++k2)
        {
            x = unitVertices[k];
            y = unitVertices[k+1];
            z = unitVertices[k+2];
            s = (float)j / (vertexCountPerRow - 1);
            addVertex(x*radius, y*radius, z*radius);
            addVertex1(x*radius, y*radius, z*radius);
            addNormal1(x, y, z);
            addNormal(x, y, z);
            addTexCoord(s, t);

            // add indices
            if(i < (vertexCountPerRow-1) && j < (vertexCountPerRow-1))
            {
                addIndices(k1, k2, k1+1);
                addIndices(k1+1, k2, k2+1);
                addIndices1(k1, k2, k1+1);
                addIndices1(k1+1, k2, k2+1);
                // lines: left and top
               
        }
    }
    }

    // array size and index for building next face
    unsigned int startIndex;                    // starting index for next face
    int vertexSize = (int)tempvertices.size();      // vertex array size of +X face
    int indexSize = (int)tempindices.size();        // index array size of +X face
   // line index size of +X face

    // build -X face by negating x and z
    startIndex = tempvertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-tempvertices[i], tempvertices[i+1], -tempvertices[i+2]);
        addVertex2(-tempvertices[i], tempvertices[i+1], -tempvertices[i+2]);
        
        addNormal(-tempnormals[i], tempnormals[i+1], -tempnormals[i+2]);
        addNormal2(-tempnormals[i], tempnormals[i+1], -tempnormals[i+2]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        tempindices1.push_back(startIndex + tempindices1[i]);
    }
  

    // build +Y face by swapping x=>y, y=>-z, z=>-x
    startIndex = tempvertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-tempvertices[i+2], tempvertices[i], -tempvertices[i+1]);
        addVertex3(-tempvertices[i+2], tempvertices[i], -tempvertices[i+1]);
       
        addNormal(-tempnormals[i+2], tempnormals[i], -tempnormals[i+1]);
        addNormal3(-tempnormals[i+2], tempnormals[i], -tempnormals[i+1]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        tempindices1.push_back(startIndex + tempindices1[i]);
    }
  

    // build -Y face by swapping x=>-y, y=>z, z=>-x
    startIndex = tempvertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-tempvertices[i+2], -tempvertices[i], tempvertices[i+1]);
        addVertex4(-tempvertices[i+2], -tempvertices[i], tempvertices[i+1]);
       
        addNormal(-tempnormals[i+2], -tempnormals[i], tempnormals[i+1]);
        addNormal4(-tempnormals[i+2], -tempnormals[i], tempnormals[i+1]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        tempindices1.push_back(startIndex + tempindices1[i]);
    }
    

    // build +Z face by swapping x=>z, z=>-x
    startIndex = tempvertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-tempvertices[i+2], tempvertices[i+1], tempvertices[i]);
        addVertex5(-tempvertices[i+2], tempvertices[i+1], tempvertices[i]);
        
        addNormal(-tempnormals[i+2], tempnormals[i+1], tempnormals[i]);
        addNormal5(-tempnormals[i+2], tempnormals[i+1], tempnormals[i]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        tempindices1.push_back(startIndex + tempindices1[i]);
    }
   
   

    // build -Z face by swapping x=>-z, z=>x
    startIndex = tempvertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(tempvertices[i+2], tempvertices[i+1], -tempvertices[i]);
        addVertex6(tempvertices[i+2], tempvertices[i+1], -tempvertices[i]);
        
        addNormal(tempnormals[i+2], tempnormals[i+1], -tempnormals[i]);
        addNormal6(tempnormals[i+2], tempnormals[i+1], -tempnormals[i]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        tempindices1.push_back(startIndex + tempindices1[i]);
    }
   

    // generate interleaved vertex array
    
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










float skyVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

int main(int argc, char** argv)
{
  GLFWwindow* window;

  glfwSetErrorCallback(opengl::error_callback);

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  window = glfwCreateWindow(SCR_WIDTH , SCR_HEIGHT , "Lights", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetKeyCallback(window,key_callback);
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  opengl::initGL();

  Shader ourShader("02_vshader.glsl","02_fshader.glsl");
  Shader skyShader("sky_vs.glsl","sky_fs.glsl");
  Shader lampShader("light_vs.glsl","light_fs.glsl");
  Shader atmosphereShader("atmos_vs.glsl","atmos_fs.glsl");
  
    buildVerticesSmooth();
    float normals[tempnormals.size()];
    float vertices[tempvertices.size()];
    unsigned indices1[tempindices1.size()];
  float vertices1[tempvertices1.size()];
  
  float vertices2[tempvertices2.size()];
  float vertices3[tempvertices3.size()];
  float vertices4[tempvertices4.size()];
  float vertices5[tempvertices5.size()];
  float vertices6[tempvertices6.size()];
  
  float normals1[tempnormals1.size()];
  float normals2[tempnormals2.size()];
  float normals3[tempnormals3.size()];
  float normals4[tempnormals4.size()];
  float normals5[tempnormals5.size()];
  float normals6[tempnormals6.size()];
  
  unsigned indices[tempindices.size()];
  float texCoords[temptexCoords.size()];
 
   
  std::copy(tempnormals1.begin(),tempnormals1.end(),normals1); 
  
  std::copy(tempnormals2.begin(),tempnormals2.end(),normals2);
  std::copy(tempnormals3.begin(),tempnormals3.end(),normals3);
  std::copy(tempnormals4.begin(),tempnormals4.end(),normals4);
  std::copy(tempnormals5.begin(),tempnormals5.end(),normals5);
  std::copy(tempnormals6.begin(),tempnormals6.end(),normals6);
  
   
  
   std::copy(tempvertices.begin(),tempvertices.end(),vertices);  
   std::copy(tempvertices1.begin(),tempvertices1.end(),vertices1);
   
      
   std::copy(tempvertices2.begin(),tempvertices2.end(),vertices2);
   
   std::copy(tempvertices3.begin(),tempvertices3.end(),vertices3);
   
   std::copy(tempvertices4.begin(),tempvertices4.end(),vertices4);
   
   std::copy(tempvertices5.begin(),tempvertices5.end(),vertices5);      
   std::copy(tempvertices6.begin(),tempvertices6.end(),vertices6);
     
  
  std::copy(tempindices.begin(),tempindices.end(),indices); 
  std::copy(tempindices1.begin(),tempindices1.end(),indices1); 
  std::copy(temptexCoords.begin(),temptexCoords.end(),texCoords);
  
  
  

  unsigned int VBO[6], VAO[6], EBO; 

 
 
  glGenBuffers(1, &EBO);
  glGenVertexArrays (1, &VAO[0]);
  glGenBuffers (1, &VBO[0]);
  
  glBindVertexArray (VAO[0]);
  glBindBuffer (GL_ARRAY_BUFFER, VBO[0]);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertices1) + sizeof(normals1) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices1), vertices1 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(normals1), normals1 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(normals1)+sizeof(vertices1), sizeof(texCoords), texCoords );
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  //POSITION ATTRIBUTE
   glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  
  //NORMAL ATTRIBUTE
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices1)));
  glEnableVertexAttribArray(1);
 
   //texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(vertices1)+sizeof(normals1)));
  glEnableVertexAttribArray(2);
  
  
  
  glGenVertexArrays (1, &VAO[1]);
  glGenBuffers (1, &VBO[1]);
  glBindVertexArray (VAO[1]);
  glBindBuffer (GL_ARRAY_BUFFER, VBO[1]);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertices2) + sizeof(normals2) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertices2), sizeof(normals2), normals2 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(normals2)+sizeof(vertices2), sizeof(texCoords), texCoords );
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices2)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(vertices2)+sizeof(normals2)));
  glEnableVertexAttribArray(2);
  
  
  
  glGenVertexArrays (1, &VAO[2]);
  glGenBuffers (1, &VBO[2]);
  glBindVertexArray (VAO[2]);
  glBindBuffer (GL_ARRAY_BUFFER, VBO[2]);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertices3) + sizeof(normals3) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices3), vertices3 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertices3), sizeof(normals3), normals3 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(normals3)+sizeof(vertices3), sizeof(texCoords), texCoords );
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices3)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(vertices3)+sizeof(normals3)));
  glEnableVertexAttribArray(2);
  
  
  glGenVertexArrays (1, &VAO[3]);
  glGenBuffers (1, &VBO[3]);
  glBindVertexArray (VAO[3]);
  glBindBuffer (GL_ARRAY_BUFFER, VBO[3]);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertices4) + sizeof(normals4) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices4), vertices4 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertices4), sizeof(normals4), normals4 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(normals4)+sizeof(vertices4), sizeof(texCoords), texCoords );
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices4)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(vertices4)+sizeof(normals4)));
  glEnableVertexAttribArray(2);
  
  
  glGenVertexArrays (1, &VAO[4]);
  glGenBuffers (1, &VBO[4]);
  glBindVertexArray (VAO[4]);
  glBindBuffer (GL_ARRAY_BUFFER, VBO[4]);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertices5) + sizeof(normals5) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices5), vertices5 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertices5), sizeof(normals5), normals5 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(normals5)+sizeof(vertices5), sizeof(texCoords), texCoords );
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices5)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(vertices5)+sizeof(normals5)));
  glEnableVertexAttribArray(2);
  
  glGenVertexArrays (1, &VAO[5]);
  glGenBuffers (1, &VBO[5]);
  glBindVertexArray (VAO[5]);
  glBindBuffer (GL_ARRAY_BUFFER, VBO[5]);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertices6) + sizeof(normals6) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices6), vertices6 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertices6), sizeof(normals6), normals6 );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(normals6)+sizeof(vertices6), sizeof(texCoords), texCoords );
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices6)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(vertices6)+sizeof(normals6)));
  glEnableVertexAttribArray(2);
  
  
  
  
  
  
  
  
  
  
  /*
  //Tangent Attribute
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tangent));
  glEnableVertexAttribArray(3);
  */
  
  unsigned int skyVAO, skyVBO;
  glGenVertexArrays(1, &skyVAO);
  glGenBuffers(1, &skyVBO);
  glBindVertexArray(skyVAO);
  glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), &skyVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  unsigned int lightVAO,lightVBO,lightEBO;
  glGenBuffers (1, &lightVBO);
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  glGenBuffers(1, &lightEBO);
  glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  
  
 
  
  std::copy(tempvertices.begin(),tempvertices.end(),vertices);  
  std::copy(tempindices1.begin(),tempindices1.end(),indices1);
  
  unsigned int atmosphereVAO, atmosphereVBO, atmosphereIBO;
  
float atmosphereRadius = radius * 1.05;
  	Sphere atmosphere(atmosphereRadius , 36, 18);
 
   
  	glGenVertexArrays(1, &atmosphereVAO);
 	glBindVertexArray(atmosphereVAO);
  	glGenBuffers(1, &atmosphereVBO);
  	glBindBuffer(GL_ARRAY_BUFFER, atmosphereVBO);
  	glBufferData(GL_ARRAY_BUFFER, atmosphere.getInterleavedVertexSize(), atmosphere.getInterleavedVertices(), GL_STATIC_DRAW);
  	
  	glEnableVertexAttribArray(0);
  	int stride = atmosphere.getInterleavedStride();
  	glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, 0);
  	
  	glGenBuffers(1, &atmosphereIBO);
  	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, atmosphereIBO);
  	glBufferData(GL_ELEMENT_ARRAY_BUFFER, atmosphere.getIndexSize(), atmosphere.getIndices(), GL_STATIC_DRAW);
  
  
  
  
  
  

  
  unsigned int diffuseMap1= loadTexture("right.jpg");
  unsigned int diffuseMap2= loadTexture("left.jpg");
  unsigned int diffuseMap3= loadTexture("top.jpg");
  unsigned int diffuseMap4= loadTexture("down.jpg");
  unsigned int diffuseMap5= loadTexture("front.jpg");
  unsigned int diffuseMap6= loadTexture("back.jpg");
  
  unsigned int specularMap1= loadTexture("sright.jpeg");
  unsigned int specularMap2= loadTexture("sleft.jpeg");
  unsigned int specularMap3= loadTexture("stop.jpeg");
  unsigned int specularMap4= loadTexture("sbottom.jpeg");
  unsigned int specularMap5= loadTexture("sfront.jpeg");
  unsigned int specularMap6= loadTexture("sback.jpeg");
  
  unsigned int night1= loadTexture("lright.jpeg");
  unsigned int night2= loadTexture("lleft.jpeg");
  unsigned int night3= loadTexture("ltop.jpeg");
  unsigned int night4= loadTexture("lbottom.jpeg");
  unsigned int night5= loadTexture("lfront.jpeg");
  unsigned int night6= loadTexture("lback.jpeg");
  
  //unsigned int normalMap = loadTexture("containernormal.jpg");
  

  std::vector<std::string> faces=
  {
    "space/right.tga",
    "space/left.tga",
    "space/top.tga",
    "space/down.tga",
    "space/front.tga",
    "space/back.tga"
  };
  unsigned int cubemapTexture = loadCubemap(faces);  

  skyShader.use();
  skyShader.setInt("skybox", 0);

  ourShader.use();
  
  ourShader.setInt("material.diffuse", 0);
  ourShader.setInt("material.specular", 1);
  ourShader.setInt("material.night", 2);
  //ourShader.setInt("material.normal",2);
  
  
  while (glfwWindowShouldClose(window) == 0)
    {
    
      
      float currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;
      deltaTime=2*deltaTime;
      glm::mat4 model = glm::mat4(1.0f);
       
      if(false) {
	    		model=glm::translate(glm::rotate(model,glm::radians(g_fSunRotation), glm::vec3(0,-1,0) ) ,orbit);
			sunPos = model * earthPos;
    		}
    		else { 
	    		model = glm::mat4(1.0f);
	    		model=  glm::translate(model,glm::vec3(sunPos));
    		}
      g_fSunRotation += fRotationRate3 * deltaTime;
     g_fSunRotation = fmod(g_fSunRotation, 360.0f);  

      processInput(window);
      glfwSetScrollCallback(window, scroll_callback); 
      glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
  	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ourShader.use();
      
      ourShader.setVec3("viewPos", camera.Position);
      ourShader.setVec3("lightPos", glm::vec3(sunPos));
  
      
        ourShader.setVec3("light.position", glm::vec3(sunPos));
        ourShader.setVec3("viewPos", camera.Position);

        // light properties
        ourShader.setVec3("light.ambient", 0.6f, 0.6f, 0.6f);
        ourShader.setVec3("light.diffuse", 0.95f, 0.95f, 0.95f);
        ourShader.setVec3("light.specular", 0.65f, 0.65f, 0.65f);

        //material properties
        ourShader.setFloat("material.shininess", 4.0f);

        
      // view/projection transformations
      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
      glm::mat4 view = camera.GetViewMatrix();
      ourShader.setMat4("projection", projection);
      ourShader.setMat4("view", view);
      // world transformation
      model = glm::mat4(1.0f);
      ourShader.setMat4("model", model);
       /*
      ourShader.setInt("blinn", blinn);
      ourShader.setInt("np", np);
      */

      // bind diffuse map
     
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap1);
      // bind specular map
     glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap1);
      
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, night1);
      // Bind Normal Map
      //glActiveTexture(GL_TEXTURE2);
      //glBindTexture(GL_TEXTURE_2D, normalMap);
      
      // render containers
      glBindVertexArray(VAO[0]);
      glDrawElements(GL_TRIANGLES, tempindices.size(), GL_UNSIGNED_INT, 0);
      
      
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap2);
      
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap2);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, night2);
      glBindVertexArray(VAO[1]);
      glDrawElements(GL_TRIANGLES, tempindices.size(), GL_UNSIGNED_INT, 0);
      
      
      
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap3);
      
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap3);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, night3);
      glBindVertexArray(VAO[2]);
      glDrawElements(GL_TRIANGLES, tempindices.size(), GL_UNSIGNED_INT, 0);
      
      
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap4);
      
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap4);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, night4);
      
      glBindVertexArray(VAO[3]);
      glDrawElements(GL_TRIANGLES, tempindices.size(), GL_UNSIGNED_INT, 0);
      
      
     
       
      
      
      
       glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap6);
      
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap6);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, night6);
      glBindVertexArray(VAO[5]);
      glDrawElements(GL_TRIANGLES, tempindices.size(), GL_UNSIGNED_INT, 0);
      
      
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap5);
      
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap5);
      
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, night5);
      glBindVertexArray(VAO[4]);
      glDrawElements(GL_TRIANGLES, tempindices.size(), GL_UNSIGNED_INT, 0);
      
      model = glm::mat4(1.0f);
      glm::vec4 eyePosW = glm::vec4(camera.Position, 1 );
      
      
      
     
      
      
      glEnable(GL_BLEND);

      glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
     
     
            
	
    		
    		atmosphereShader.use();
    		model = glm::mat4(1.0f);
    		model = glm::translate(model, glm::vec3(earthPos));
         	
    		atmosphereShader.setMat4("model", model);
    		atmosphereShader.setMat4("projection", projection);
    		atmosphereShader.setMat4("view", view);
    		atmosphereShader.setVec4("EyePosW",eyePosW);
    		atmosphereShader.setVec4("LightPosW",sunPos);
    		atmosphereShader.setFloat("inner_radius",earthrad);
    		atmosphereShader.setFloat("outer_radius",atmosphereRadius);
		
    		glBindVertexArray(atmosphereVAO);
    		glDrawElements(GL_TRIANGLES,atmosphere.getIndexCount(), GL_UNSIGNED_INT, 0);
    		
    		
      
                glDisable(GL_BLEND);

    		glDepthFunc(GL_LEQUAL);
         
    
      lampShader.use();
      lampShader.setMat4("projection", projection);
      lampShader.setMat4("view", view);
 
      glBindVertexArray(lightVAO);
      model = glm::mat4(1.0f);
          model = glm::translate(model, glm::vec3(sunPos));
          model = glm::scale(model, glm::vec3(0.5f)); // Make it a smaller cube
          lampShader.setMat4("model", model);
           glDrawElements(GL_TRIANGLES, tempindices1.size(), GL_UNSIGNED_INT, 0);
      

      glDepthFunc(GL_LEQUAL);
      skyShader.use();
      view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
      skyShader.setMat4("view", view);
      skyShader.setMat4("projection", projection);
      glBindVertexArray(skyVAO);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      glBindVertexArray(0);
      glDepthFunc(GL_LESS); // set depth function back to default
      
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  glDeleteVertexArrays(1, &VBO[0]);
  glDeleteVertexArrays(1, &VBO[1]);
  glDeleteVertexArrays(1, &VBO[2]);
  glDeleteVertexArrays(1, &VBO[3]);
  glDeleteVertexArrays(1, &VBO[4]);
  glDeleteVertexArrays(1, &VBO[5]);
  
  glDeleteBuffers(1, &VAO[0]);
  glDeleteBuffers(1, &VAO[1]);
  glDeleteBuffers(1, &VAO[2]);
  glDeleteBuffers(1, &VAO[3]);
  glDeleteBuffers(1, &VAO[4]);
  glDeleteBuffers(1, &VAO[5]);
  glDeleteVertexArrays(1, &skyVAO);
  glDeleteBuffers(1, &skyVAO);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !blinnKeyPressed) 
    {
        blinn = !blinn;
        blinnKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) 
    {
        blinnKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && !spotLightKeyPressed) 
    {
        spotLight = !spotLight;
        spotLightKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_RELEASE) 
    {
        spotLightKeyPressed = false;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && !dirLightKeyPressed) 
    {
        dirLight = !dirLight;
        dirLightKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE) 
    {
        dirLightKeyPressed = false;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pointLightKeyPressed) 
    {
        pointLight = !pointLight;
        pointLightKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) 
    {
        pointLightKeyPressed = false;
    }
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && !npPressed) 
    {
        np = !np;
        npPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE) 
    {
        npPressed = false;
    }
}

//!GLFW keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  //!Close the window if the ESC key was pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const * path)
{
    
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height, nrChannels;

  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
   
  if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
  else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
  stbi_image_free(data); 

    return textureID;
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
