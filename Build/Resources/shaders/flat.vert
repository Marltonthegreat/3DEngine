#version 430 core 
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

flat out vec3 fs_color;
out vec2 fs_texcoord;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec4 position;
};

uniform Material material;
uniform Light light;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 model_view = view * model;

    // ambient
    vec3 ambient = material.ambient * light.ambient;

    // diffuse
    vec3 vert_normal = mat3(model_view) * normal;
    vec4 vert_position = model_view * vec4(position, 1);
    vec3 light_dir = normalize(vec3(light.position - vert_position));

    float intensity = max(dot(light_dir, vert_normal), 0);
    
    vec3 diffuse = material.diffuse * light.diffuse * intensity;

    // specular
    vec3 specular = vec3(0);
    if(intensity > 0)
    {
        vec3 view_dir = normalize(-vec3(vert_position));
        vec3 reflection = reflect(-light_dir, vert_normal);
        intensity = max(dot(view_dir, reflection), 0);
        intensity = pow(intensity, material.shininess);
        specular = material.specular * light.specular * intensity;
    }

    fs_color = ambient + diffuse + specular;
    fs_texcoord = texcoord;
    gl_Position = projection * model_view * vec4(position, 1.0f);
}