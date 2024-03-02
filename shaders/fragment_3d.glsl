#version 330 core

in vec3 pos_xyz;
in vec3 FragPos;
in vec3 NormalVec;
in vec2 TexCoord;

out vec4 FragColor;

const float ambient_strength = 0.1;
const vec3 light_color = vec3(0.6, 0.4, 0.1); 
const vec3 light_pos = vec3(10.0, -15.0, 30.0);
const vec3 object_color = vec3(0.6, 0.4, 0.1);

void main()
{
    vec3 norm = normalize(NormalVec);

    vec3 light_dir = normalize(light_pos - FragPos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 ambient = ambient_strength * light_color;

    vec3 result = (ambient + diffuse) * object_color;

    FragColor = vec4(result, 1.0);
}
