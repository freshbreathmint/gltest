#ifndef SHADER_H
#define SHADER_H

typedef struct {
    unsigned int ID;
} Shader;

void Shader_init(Shader *shader, const char *vertexPath, const char *fragmentPath);
void Shader_use(const Shader *shader);

void Shader_setBool(const Shader *shader, const char *name, int value);
void Shader_setInt(const Shader *shader, const char *name, int value);
void Shader_setFloat(const Shader *shader, const char *name, int value);

#endif