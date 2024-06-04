#ifndef CUBE_H
#define CUBE_H

#define CUBE_VERTICES                                                          \
  {                                                                            \
    -0.5f, -0.5f, -0.5f,    /* Bottom Left  (-z) 0 */                          \
        -0.5f, 0.5f, -0.5f, /* Top Left     (-z) 1 */                          \
        0.5f, 0.5f, -0.5f,  /* Top Right    (-z) 2 */                          \
        0.5f, -0.5f, -0.5f, /* Bottom Right (-z) 3 */                          \
        -0.5f, -0.5f, 0.5f, /* Bottom Left  (+z) 4 */                          \
        -0.5f, 0.5f, 0.5f,  /* Top Left     (+z) 5 */                          \
        0.5f, 0.5f, 0.5f,   /* Top Right    (+z) 6 */                          \
        0.5f, -0.5f, 0.5f   /* Bottom Right (+z) 7 */                          \
  }
#define CUBE_VERTICES_LENGTH 24

#define CUBE_INDICES                                                           \
  {                                                                            \
    1, 2, 5, 2, 5, 6,     /* +y */                                             \
        0, 3, 4, 3, 4, 7, /* -y */                                             \
        2, 3, 6, 3, 6, 7, /* -x */                                             \
        0, 1, 4, 1, 4, 5, /* +x */                                             \
        0, 1, 2, 0, 2, 3, /* -z */                                             \
        4, 5, 6, 4, 6, 7, /* +z */                                             \
  }
#define CUBE_INDICES_LENGTH 36

#endif // CUBE_H
