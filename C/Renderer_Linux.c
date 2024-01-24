//Defs
 #define uint unsigned int
 extern int    write(int fd, char* buffer, int count);
 extern void   exit(int error);
 extern float sinf(float val);
 extern float cosf(float val);
 extern int    glfwInit(void);
 extern void   glfwWindowHint(int hint, int value);
 extern void*  glfwCreateWindow(int width, int height, void* title, void* monitor, void* share);
 extern void   glfwMakeContextCurrent(void* window);
 extern void   glfwSwapBuffers(void* window);
 extern void   glfwPollEvents(void);
 extern int    glfwWindowShouldClose(void* window);
 extern void   glfwGetFramebufferSize(void* window,  int* width, int* height);
 extern int    glfwGetKey(void* window, uint key);
 extern void   glfwTerminate(void);
 extern void   glGenVertexArrays(int count, int* arrays);
 extern void   glGenBuffers(int count, int* buffers);
 extern void   glBindVertexArray(int array);
 extern void   glBindBuffer(uint target, int buf);
 extern void   glBufferData(uint target, int size, void* data, uint usage);
 extern void   glVertexAttribPointer(int index, int size, uint type, int normalized, int stride, void* pointer);
 extern void   glEnableVertexAttribArray(int index);
 extern int    glCreateShader(uint type);
 extern void   glShaderSource(int shader, int count, char** sources, int* lengths); //String is a double pointer to a string
 extern void   glCompileShader(int shader);
 extern void   glGetShaderiv(int shader, uint param, void* returnval);
 extern void   glGetShaderInfoLog(int shader, int bufsize, int* returnsz, void* buf);
 extern void   glDeleteShader(int shader);
 extern int    glCreateProgram(void);
 extern void   glAttachShader(int program, int shader);
 extern void   glLinkProgram(int program);
 extern void   glGetProgramiv(int program, uint param, void* returnval);
 extern void   glGetProgramInfoLog(int program, int bufsize, int* returnsz, void* buf);
 extern void   glDetachShader(int program, int shader);
 extern void   glDeleteProgram(int program);
 extern void   glUseProgram(int program);
 extern uint   glGetUniformLocation(int program, char* name);
 extern void   glClear(uint flags);
 extern void   glDrawElements(uint drawtype, int count, uint elemtype, int offset);
 extern void   glUniform2f(int uniform, float v1, float v2);
 extern void   glUniform2fv(int uniform, int count, float* values);
 extern void   glUniform3fv(int uniform, int count, float* values);
 extern void   glViewport(int x, int y, int width, int height);
 extern uint   glGetError(void);
 void  done();
 
int main()
{
 char  buffer[256];
 //Window init
  glfwInit();                 //Required before anything else
  void* window = glfwCreateWindow(1600, 900, "Scumpert!!", 0, 0);
  glfwMakeContextCurrent(window);
 //Buffer init
  int vao;
  int objs[2];
  float vertices[24] = { -0.5, -0.5, -0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5, +0.5, +0.5,+0.5, +0.5, +0.5, +0.5, +0.5, -0.5 }; //Cube vertices
  char  elements[24] = { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 };                                                                        //Wireframe cube elements
  glGenVertexArrays(1, &vao);
  glGenBuffers(2, objs);
  glBindVertexArray(vao);
  glBindBuffer(0x8892, objs[0]);                  //0x8892 is GL_ARRAY_BUFFER. objs[0] is the vertex buffer object
  glBufferData(0x8892, 96, vertices, 0x88E4);     //0x88E4 is STATIC_DRAW
  glBindBuffer(0x8893, objs[1]);                  //0x8893 is GL_ELEMENT_BUFFER. objs[1] is the element buffer object
  glBufferData(0x8893, 24, elements, 0x88E4);
  glVertexAttribPointer(0, 3, 0x1406, 0, 12, 0);  //Index 0, 3 elements, 0x1406 is float, don't normalize, entry size of 12 bytes, offset of 0
  glEnableVertexAttribArray(0);
 //Shader init
  char* vertshaderstr = "#version 420\nlayout (location = 0) in vec3 pos;uniform vec2 res;uniform vec3 loc;uniform vec2 cam;void main() {gl_Position = vec4(pos, 1.0);gl_Position.xyz -= loc;float z = gl_Position.z;gl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y);gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y);float y = gl_Position.y;gl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x);gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x);gl_Position.x *=  (res[1]/res[0]);gl_Position.w = gl_Position.z;}";
  char* fragshaderstr = "#version 420\nout vec4 color;void main() {color = vec4(1, 0, 0, 1);}";
  int result, size;
  uint vertshader = glCreateShader(0x8B31);         //0x8B31 is GL_VERTEX_SHADER
  glShaderSource(vertshader, 1, &vertshaderstr, 0); //Shader, line count, lines, linelengths
   glCompileShader(vertshader);
  glGetShaderiv(vertshader, 0x8B81, &result);       //0x8B81 is GL_COMPILE_STATUS
  if(result == 0) { glGetShaderInfoLog(vertshader, 0xFF, &size, buffer); write(1, buffer, size); glDeleteShader(vertshader); done(); }
  uint fragshader = glCreateShader(0x8B30);         //0x8B30 is GL_FRAGMENT_SHADER
  glShaderSource(fragshader, 1, &fragshaderstr, 0);
  glCompileShader(fragshader);
  glGetShaderiv(fragshader, 0x8B81, &result);
  if(result == 0) { glGetShaderInfoLog(fragshader, 0xFF, &size, buffer); write(1, buffer, size); glDeleteShader(vertshader); glDeleteShader(fragshader); done(); }
  int program = glCreateProgram();
  glAttachShader(program, vertshader);
  glAttachShader(program, fragshader);
  glLinkProgram(program);
  glGetProgramiv(program, 0x8B82, &result); //0x8B82 is GL_LINK_STATUS
  if(result == 0) { glGetProgramInfoLog(program, 0xFF, &size, buffer); write(1, buffer, size); glDeleteShader(vertshader); glDeleteShader(fragshader); glDeleteProgram(program); done(); }
  glUseProgram(program);
  glDetachShader(program, vertshader);
  glDetachShader(program, fragshader);
  glDeleteShader(vertshader);
  glDeleteShader(fragshader);
  float loc[3], cam[2];
  int unires = glGetUniformLocation(program, "res");
  int uniloc = glGetUniformLocation(program, "loc");
  int unicam = glGetUniformLocation(program, "cam");
  int oldwidth = 0, oldheight = 0, width, height;
 while(!glfwWindowShouldClose(window))
 {
  glfwGetFramebufferSize(window, &width, &height);
  if (oldwidth != width || oldheight != height) { oldwidth = width; oldheight = height;  glViewport(0, 0, width, height); glUniform2f(unires, (float)width, (float)height); }
  if (glfwGetKey(window, 256)) { done(); }
  if (glfwGetKey(window,  32)) { loc[1] += 0.01; glUniform3fv(uniloc, 1, loc); }                                               //Space
  if (glfwGetKey(window,  65)) { loc[0] += cosf(cam[1]) * -0.01; loc[2] += sinf(cam[1]) * -0.01; glUniform3fv(uniloc, 1, loc); } //A
  if (glfwGetKey(window,  68)) { loc[0] += cosf(cam[1]) * +0.01; loc[2] += sinf(cam[1]) * +0.01; glUniform3fv(uniloc, 1, loc); } //D
  if (glfwGetKey(window,  83)) { loc[0] += sinf(cam[1]) * +0.01; loc[2] += cosf(cam[1]) * -0.01; glUniform3fv(uniloc, 1, loc); } //S
  if (glfwGetKey(window,  87)) { loc[0] += sinf(cam[1]) * -0.01; loc[2] += cosf(cam[1]) * +0.01; glUniform3fv(uniloc, 1, loc); } //W
  if (glfwGetKey(window, 262)) { cam[1] -= 0.01; glUniform2fv(unicam, 1, cam); }                                               //Right
  if (glfwGetKey(window, 263)) { cam[1] += 0.01; glUniform2fv(unicam, 1, cam); }                                               //Left
  if (glfwGetKey(window, 264)) { cam[0] -= 0.01; glUniform2fv(unicam, 1, cam); }                                               //Down
  if (glfwGetKey(window, 265)) { cam[0] += 0.01; glUniform2fv(unicam, 1, cam); }                                               //Up
  if (glfwGetKey(window, 340)) { loc[1] -= 0.01; glUniform3fv(uniloc, 1, loc); }                                               //LShift
  glClear(0x4000);                       //0x4000 is GL_COLOR_BUFFER_BIT
  glDrawElements(0x0001, 24, 0x1401, 0); //0x0001 is GL_LINES, 0x1401 is GL_UNSIGNED_BYTE
  glfwSwapBuffers(window);
  glfwPollEvents();
 }
 done();
}
void done()
{
 exit(0);
}