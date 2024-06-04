#ifndef SHADER_H
#define SHADER_H

#include <cglm/types.h>

typedef struct shader {
  unsigned int programId;
  unsigned int vsId;
  unsigned int fsId;
} shader_t;

void shader_init(shader_t *self, const char *vsSource, const char *fsSource);
void shader_initFromFiles(shader_t *self, const char *vsPath,
                          const char *fsPath);

void shader_use(const shader_t *self);

void shader_setVec3(const shader_t *self, const char *name, vec3 value);
void shader_setMat4(const shader_t *self, const char *name, mat4 value);

#endif
