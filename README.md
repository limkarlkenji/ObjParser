# ObjParser test project
OpenGL obj parser

Only parses triangles i.e. `f v/vt/vn v/vt/vn v/vt/vn`

Reads some values of .mtl file: `Ns`, `Ka`, `Kd` and `Ks`


![](objparser.gif)

Dependencies:
- [GLFW](https://www.glfw.org/)
- [glad](https://github.com/dav1dde/glad-web)
- [GLM](https://glm.g-truc.net/0.9.5/api/index.html)
- [stb_image](https://github.com/nothings/stb)

References:
- [Wavefront OBJ specification](http://paulbourke.net/dataformats/obj/)
- [MTL file specification](http://paulbourke.net/dataformats/mtl/)

Models for testing:
- [Cube](https://gist.github.com/noonat/1131091/450ad7bbb6e0c8fba1854cc86a9f6b7a224fca56)
- [Teapot](https://github.com/kevinroast/phoria.js/blob/master/teapot.obj)


