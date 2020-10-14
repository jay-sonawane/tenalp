#version 330 core

in vec4 FragPos;

uniform vec4 EyePosW;   // Eye position in world space.
uniform vec4 LightPosW; // Light's position in world space.

uniform float inner_radius; // for atmosphere
uniform float outer_radius; // for atmosphere

const float PI = 3.14159265359;
const float degToRad = PI / 180.0;
const float MAX = 10000.0;

float K_R = 0.166; // Rayleigh Scattering constant term
const float K_M = 0.0025; // Mei Scattering constant
const float E = 14.4; // Proportional to Intensity of Sun's light near Earth's surface 
const vec3 C_R = vec3(0.18, 0.26, 1.0); // Rayleigh scattering 1/(lambda^4) terms for RGB light channels
const float G_M = -0.85;  // g for Mie phase function

float SCALE_H = 4.0 / (outer_radius - inner_radius);
float SCALE_L = 1.0 / (outer_radius - inner_radius);

// Number of steps for calculating the integration loop for out-scattering and in-scattering equations
const int numOutScatter = 10;
const float fNumOutScatter = 10.0;
const int numInScatter = 10;
const float fNumInScatter = 10.0;


vec2 rayIntersection(vec3 p, vec3 dir, float radius) {
    float b = dot(p,dir);
    float c = dot(p,p) - radius*radius;
    float d = b*b - c;
    if (d < 0.0) return vec2(MAX,-MAX);
    
    d = sqrt(d);
    float near = -b - d;
    float far = -b + d;

    return vec2(near, far);
 }

float miePhase( float g, float c, float c2) {
    float g2 = g * g;
    float a = ( 1.0 - g2 ) * ( 1.0 + c2 );
    float b = 1.0 + g2 - 2.0 * g * c;
    b *= sqrt(b);
    b *= 2.0 + g2;  

    return 1.5 * a / b;
}

float rayleighPhase( float c2) { return 0.75 * (1.0 + c2);}

float density(vec3 p) { return exp(-(length(p) - inner_radius) * SCALE_H);}   // exp(-h/H0) term

float optic(vec3 p, vec3 q) { 
    vec3 step = (q - p) / fNumOutScatter;
    vec3 v = p + step * 0.5;

    float sum = 0.0;
    for(int i = 0; i < numOutScatter; i++) {
        sum += density(v);
        v += step;
    }
    sum *= length(step)*SCALE_L;
    return sum;
}

vec3 inScatter(vec3 o, vec3 dir, vec2 e, vec3 l) {
    float len = (e.y - e.x) / fNumInScatter;
    vec3 step = dir * len;
    vec3 p = o + dir * e.x;
    vec3 v = p + dir * (len * 0.5);

    vec3 sum = vec3(0.0);
    for(int i = 0; i < numInScatter; i++) {
        vec2 f = rayIntersection(v, l, outer_radius);
        vec3 u = v + l * f.y;
        float n = (optic(p, v) + optic(v, u))*(PI * 4.0);
        sum += density(v)* exp(-n * ( K_R * C_R + K_M ));
        v += step;
    }
    sum *= len * SCALE_L;
    float c = dot(dir, -l);
    float c2 = c * c;
    return sum * ( K_R * C_R * rayleighPhase(c2) + K_M * miePhase(G_M,c,c2) ) * E;
}



 out vec4 out_color;

void main() {
    vec4 L = normalize( LightPosW - FragPos );

    vec3 dir = vec3(normalize(FragPos - EyePosW));
    vec3 eye = vec3(EyePosW);
    vec3 l = normalize(vec3(L)); 
    vec2 e = rayIntersection(eye, dir, outer_radius);
    if(e.x > e.y) discard;
    vec2 f = rayIntersection(eye, dir, inner_radius);
    e.y = min(e.y, f.x);
    vec3 InScatter = inScatter(eye, dir, e, l);
    vec4 Scatter = vec4(InScatter, 0.65); 
    out_color = Scatter;

}
