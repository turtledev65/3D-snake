#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

static unsigned int compileShader(const char *src, GLenum type);
static unsigned int linkProgram(unsigned int vs, unsigned int fs);
static char        *readShaderFile(const char *path);
static int          getUniformLocation(const shader_t *self, const char *name);

// Public Functions
void shader_init(shader_t *self, const char *vsSource, const char *fsSource)
{
  self->vsId      = compileShader(vsSource, GL_VERTEX_SHADER);
  self->fsId      = compileShader(fsSource, GL_FRAGMENT_SHADER);
  self->programId = linkProgram(self->vsId, self->fsId);
}

void shader_initFromFiles(shader_t *self, const char *vsPath,
                          const char *fsPath)
{
  const char *vsSource = readShaderFile(vsPath);
  const char *fsSource = readShaderFile(fsPath);

  if (vsSource && fsSource)
    shader_init(self, vsSource, fsSource);
}

void shader_use(const shader_t *self) { glUseProgram(self->programId); }

void shader_setVec3(const shader_t *self, const char *name, vec3 value)
{
  glUniform3fv(getUniformLocation(self, name), 1, &value[0]);
}

void shader_setMat4(const shader_t *self, const char *name, mat4 value)
{
  glUniformMatrix4fv(getUniformLocation(self, name), 1, GL_FALSE, value[0]);
}

// Private Functions
static unsigned int compileShader(const char *src, GLenum type)
{
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    fprintf(stderr, "ERROR: Faied to compile %s shader:\n %s\n",
            type == GL_VERTEX_SHADER ? "vertex" : "fragment", infoLog);
  }
  return shader;
}

static unsigned int linkProgram(unsigned int vs, unsigned int fs)
{
  unsigned int program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  int success;
  glGetShaderiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(program, 1024, NULL, infoLog);
    fprintf(stderr, "ERROR: Faied to link shader program:\n %s\n", infoLog);
  }

  return program;
}

static char *readShaderFile(const char *path)
{
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "ERROR: Failed to open shader file: %s\n", path);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  size_t strSize = ftell(file);
  rewind(file);

  char *src = malloc(strSize + 1);
  fread(src, 1, strSize, file);
  src[strSize] = 0;

  return src;
}

static int getUniformLocation(const shader_t *self, const char *name)
{
  int location = glGetUniformLocation(self->programId, name);
  if (location < 0)
    fprintf(stderr, "ERROR: Failed to find location of unifrom %s\n", name);

  return location;
}
