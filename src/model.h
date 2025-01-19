// model.h

#ifndef MODEL_H
#define MODEL_H

typedef struct {
    float x, y, z;
} v;

void check_shader_compile(unsigned int shader);
void check_program_link(unsigned int program);

#endif // MODEL_H