//Externs -lGL -lglfw -lm
 //Header files could be included instead but this lets you easily view function prototypes you use
 #define uint unsigned int
 extern int    write(int fd, char* buffer, int count);
 extern void   exit(int error);
 extern double sin(double val);
 extern double cos(double val);
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
 extern void   glGenVertexArrays(uint count, void* arrays);
 extern void   glGenBuffers(uint count, void* buffers);
 extern void   glBindVertexArray(uint array);
 extern void   glBindBuffer(uint target, uint buf);
 extern void   glBufferData(uint target, uint size, void* data, uint usage);
 extern void   glVertexAttribPointer(uint index, uint size, uint type, int normalized, uint stride, void* pointer);
 extern void   glEnableVertexAttribArray(uint index);
 extern uint   glCreateShader(uint type);
 extern void   glShaderSource(uint shader, uint count, void* sources, void* lengths); //String is a double pointer to a string
 extern void   glCompileShader(uint shader);
 extern void   glGetShaderiv(uint shader, uint param, void* returnval);
 extern void   glGetShaderInfoLog(uint shader, uint bufsize, void* returnsize, void* buf);
 extern void   glDeleteShader(uint shader);
 extern uint   glCreateProgram(void);
 extern void   glAttachShader(uint program, uint shader);
 extern void   glLinkProgram(uint program);
 extern void   glGetProgramiv(uint program, uint param, void* returnval);
 extern void   glGetProgramInfoLog(uint program, uint bufsize, void* returnsize, void* buf);
 extern void   glDetachShader(uint program, uint shader);
 extern void   glDeleteProgram(uint program);
 extern void   glUseProgram(uint program);
 extern uint   glGetUniformLocation(uint program, void* name);
 extern void   glClear(uint flags);
 extern void   glDrawElements(uint drawtype, uint count, uint elemtype, uint offset);
 extern void   glUniform2f(uint uniform, float v1, float v2);
 extern void   glUniform2fv(uint uniform, uint count, void* values);
 extern void   glUniform3fv(uint uniform, uint count, void* values);
 extern void   glViewport(uint x, uint y, uint width, uint height);
 extern uint   glGetError(void);

//Variables
 //A bit ugly but I decided this was easier than loading from files
 const char* vertshaderstr = "#version 450\nlayout (location = 0) in vec3 pos;uniform vec2 res;uniform vec3 loc;uniform vec2 cam;void main() {gl_Position = vec4(pos, 1.0);gl_Position.xyz -= loc;float z = gl_Position.z;gl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y);gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y);float y = gl_Position.y;gl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x);gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x);gl_Position.x *=  (res[1]/res[0]);gl_Position.w = gl_Position.z;}";
 const char* fragshaderstr = "#version 450\nout vec4 color;void main() {color = vec4(1, 0, 0, 1);}";
 void  resize(), keypress(), done();
 void* window;
 uint  objs[2], vao, program, unires, uniloc, unicam;
 float loc[3], cam[2];
 float vertices[24] = { -0.5, -0.5, -0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5, +0.5, +0.5,+0.5, +0.5, +0.5, +0.5, +0.5, -0.5 }; //Cube vertices
 char  elements[24] = { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 };                                                                        //Wireframe cube elements
 char  buffer[256];
 
int main()
{
 //Window init
  glfwInit();                 //Required before anything else
  glfwWindowHint(0x22002, 4); //0x22002 is GL_VERSION_MAJOR
  glfwWindowHint(0x22003, 5); //0x22003 is GL_VERSION_MINOR
  window = glfwCreateWindow(1600, 900, "Scumpert!!", 0, 0);
  glfwMakeContextCurrent(window);
 //Buffer init
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
  program = glCreateProgram();
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
  unires = glGetUniformLocation(program, "res");
  uniloc = glGetUniformLocation(program, "loc");
  unicam = glGetUniformLocation(program, "cam");
  int oldwidth = 0, oldheight = 0, width, height;
 while(!glfwWindowShouldClose(window))
 {
  glfwGetFramebufferSize(window, &width, &height);
  if (oldwidth != width || oldheight != height) { oldwidth = width; oldheight = height;  glViewport(0, 0, width, height); glUniform2f(unires, (float)width, (float)height); }
  if (glfwGetKey(window, 256)) { done(); }
  if (glfwGetKey(window,  32)) { loc[1] += 0.01; glUniform3fv(uniloc, 1, loc); }                                               //Space
  if (glfwGetKey(window,  65)) { loc[0] += cos(cam[1]) * -0.01; loc[2] += sin(cam[1]) * -0.01; glUniform3fv(uniloc, 1, loc); } //A
  if (glfwGetKey(window,  68)) { loc[0] += cos(cam[1]) * +0.01; loc[2] += sin(cam[1]) * +0.01; glUniform3fv(uniloc, 1, loc); } //D
  if (glfwGetKey(window,  83)) { loc[0] += sin(cam[1]) * +0.01; loc[2] += cos(cam[1]) * -0.01; glUniform3fv(uniloc, 1, loc); } //S
  if (glfwGetKey(window,  87)) { loc[0] += sin(cam[1]) * -0.01; loc[2] += cos(cam[1]) * +0.01; glUniform3fv(uniloc, 1, loc); } //W
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
 glDeleteProgram(program);
 glfwTerminate();
 exit(0);
}