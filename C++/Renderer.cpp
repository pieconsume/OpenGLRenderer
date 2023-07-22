//Externs -lGL -lglfw -lm
 //Header files could be included instead but this lets you easily view function prototypes you use
 #define uint unsigned int
 extern "C" int    write(int fd, char* buffer, int count);
 extern "C" void   exit(int error);
 extern "C" double sin(double val);
 extern "C" double cos(double val);
 extern "C" int    glfwInit(void);
 extern "C" void   glfwTerminate(void);
 extern "C" void   glfwWindowHint(int hint, int value);
 extern "C" void*  glfwCreateWindow(int width, int height, const void* title, void* monitor, void* share);
 extern "C" void   glfwMakeContextCurrent(void* window);
 extern "C" void*  glfwSetWindowSizeCallback(void* window, void(*)(void*,int,int));
 extern "C" void*  glfwSetKeyCallback(void* window, void(*)(void*,int,int,int,int));
 extern "C" void   glfwSwapBuffers(void* window);
 extern "C" void   glfwPollEvents(void);
 extern "C" int    glfwWindowShouldClose(void* window);
 extern "C" int    glfwGetKey(void* window, uint key);
 extern "C" void   glGenVertexArrays(uint count, void* arrays);
 extern "C" void   glGenBuffers(uint count, void* buffers);
 extern "C" void   glBindVertexArray(uint array);
 extern "C" void   glBindBuffer(uint target, uint buf);
 extern "C" void   glBufferData(uint target, uint size, void* data, uint usage);
 extern "C" void   glVertexAttribPointer(uint index, uint size, uint type, int normalized, uint stride, void* pointer);
 extern "C" void   glEnableVertexAttribArray(uint index);
 extern "C" uint   glCreateShader(uint type);
 extern "C" void   glShaderSource(uint shader, uint count, void* sources, void* lengths); //String is a double pointer to a string
 extern "C" void   glCompileShader(uint shader);
 extern "C" void   glGetShaderiv(uint shader, uint param, void* returnval);
 extern "C" void   glGetShaderInfoLog(uint shader, uint bufsize, void* returnsize, void* buf);
 extern "C" void   glDeleteShader(uint shader);
 extern "C" uint   glCreateProgram(void);
 extern "C" void   glAttachShader(uint program, uint shader);
 extern "C" void   glLinkProgram(uint program);
 extern "C" void   glGetProgramiv(uint program, uint param, void* returnval);
 extern "C" void   glGetProgramInfoLog(uint program, uint bufsize, void* returnsize, void* buf);
 extern "C" void   glDetachShader(uint program, uint shader);
 extern "C" void   glDeleteProgram(uint program);
 extern "C" void   glUseProgram(uint program);
 extern "C" uint   glGetUniformLocation(uint program, const void* name);
 extern "C" void   glClear(uint flags);
 extern "C" void   glDrawElements(uint drawtype, uint count, uint elemtype, uint offset);
 extern "C" void   glUniform2f(uint uniform, float v1, float v2);
 extern "C" void   glUniform2fv(uint uniform, uint count, void* values);
 extern "C" void   glUniform3fv(uint uniform, uint count, void* values);
 extern "C" void   glViewport(uint x, uint y, uint width, uint height);
 extern "C" uint   glGetError(void);

//A bit ugly but I decided this was easier than loading from files
const char* vertshaderstr = "#version 450\nlayout (location = 0) in vec3 pos;uniform vec2 res;uniform vec3 loc;uniform vec2 cam;void main() {gl_Position = vec4(pos, 1.0);gl_Position.xyz -= loc;float z = gl_Position.z;gl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y);gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y);float y = gl_Position.y;gl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x);gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x);gl_Position.x *=  (res[1]/res[0]);gl_Position.w = gl_Position.z;}";
const char* fragshaderstr = "#version 450\nout vec4 color;void main() {color = vec4(1, 0, 0, 1);}";
void  resize(void*,int,int), keypress(void*,int,int,int,int), done();
void* window;
uint  objs[2], vao, program, unires, uniloc, unicam;
float loc[3], cam[2];
float vertices[24] = //Vertices of a cube
{
 -0.5, -0.5, -0.5, 
 -0.5, -0.5, +0.5, 
 +0.5, -0.5, +0.5, 
 +0.5, -0.5, -0.5, 
 -0.5, +0.5, -0.5, 
 -0.5, +0.5, +0.5,
 +0.5, +0.5, +0.5, 
 +0.5, +0.5, -0.5
};
char  elements[24] = //Elements for a wireframe cube with GL_LINES
{
 0, 1, 
 1, 2, 
 2, 3, 
 3, 0, 
 4, 5, 
 5, 6, 
 6, 7, 
 7, 4, 
 0, 4, 
 1, 5, 
 2, 6, 
 3, 7
};
char  buffer[256];
//Instead of doing a massive if-else chain for each key I decided to make it a bit more compact by having flags for each key which modify behavior
short keys[] = 
{ 
 32,  //Space
 65,  //A
 68,  //D
 83,  //S
 87,  //W
 262, //Right
 263, //Left
 264, //Down
 265, //Up
 340  //Left shift
};
char  flags[] = { 0b101, 0b00000, 0b01100, 0b11000, 0b10100, 0b1010, 0b1110, 0b0010, 0b0110, 0b001 };
int main()
{
 //GLFW init
  glfwInit();                                //Required before anything else
  glfwWindowHint(0x22002, 4);                //0x22002 is GL_VERSION_MAJOR
  glfwWindowHint(0x22003, 5);                //0x22003 is GL_VERSION_MINOR
  window = glfwCreateWindow(
   1600,         //Width
   900,          //Height
   "Scumpert!!", //Name
   0,            //Monitor
   0);           //Share
  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, resize);
  glfwSetKeyCallback(window, keypress);
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
  if(result == 0)
  {
   glGetShaderInfoLog(vertshader, 0xFF, &size, buffer);
   write(1, buffer, size); //1 is stdout
   glDeleteShader(vertshader);
  }
  uint fragshader = glCreateShader(0x8B30);         //0x8B30 is GL_FRAGMENT_SHADER
  glShaderSource(fragshader, 1, &fragshaderstr, 0);
  glCompileShader(fragshader);
  glGetShaderiv(fragshader, 0x8B81, &result);
  if(result == 0)
  {
   glGetShaderInfoLog(fragshader, 0xFF, &size, buffer);
   write(1, buffer, size);
   glDeleteShader(vertshader);
   glDeleteShader(fragshader);
  }
  program = glCreateProgram();
  glAttachShader(program, vertshader);
  glAttachShader(program, fragshader);
  glLinkProgram(program);
  glGetProgramiv(program, 0x8B82, &result); //0x8B82 is GL_LINK_STATUS
  if(result == 0)
  {
   glGetProgramInfoLog(program, 0xFF, &size, buffer);
   write(1, buffer, size);
   glDeleteShader(vertshader);
   glDeleteShader(fragshader);
   glDeleteProgram(program);
  }
  glUseProgram(program);
  glDetachShader(program, vertshader);
  glDetachShader(program, fragshader);
  glDeleteShader(vertshader);
  glDeleteShader(fragshader);
  unires = glGetUniformLocation(program, "res");
  uniloc = glGetUniformLocation(program, "loc");
  unicam = glGetUniformLocation(program, "cam");
 //Mainloop
 while(!glfwWindowShouldClose(window))
 {
  for(int i = 0;i<10;i++)
  {
   if(glfwGetKey(window, keys[i]))
   {  
    if((flags[i]&0b11) == 0)      //0b00 is wasd for camera movement
    {
     float negpos0 = -0.001;
     float negpos1 = -0.001;
     //Directional calculations. sin and cos are used to calculate the correct movement angles
     if((flags[i]&0b00100) == 0) { negpos0 = +0.001; } //Flags are weird for this one. Should fix this up later.
     if((flags[i]&0b01000) == 0) { negpos1 = +0.001; }
     if((flags[i]&0b10000) == 0) { loc[0] -= cos(cam[1]) * negpos0; loc[2] -= sin(cam[1]) * negpos1; } 
     else { loc[0] += sin(cam[1]) * negpos0; loc[2] += cos(cam[1]) * negpos1; }
     glUniform3fv(uniloc, 1, loc);
    }
    else if((flags[i]&0b10) == 0) //0b01 is shift/space for up/down
    {
     if(keys[i] == 340) { loc[1] -= 0.001; } else { loc[1] += 0.001; }
     glUniform3fv(uniloc, 1, loc);
    }
    else                          //0b10 is left/right/up/down for camera angles
    {
     float negpos = +0.001;
     if((flags[i]&0b0100) == 0) { negpos = -0.001; }                             //Negpos flag
     if((flags[i]&0b1000) == 0) { cam[0] += negpos; } else { cam[1] += negpos; } //X/Y flag
     glUniform2fv(unicam, 1, cam);
    }
   }
  }
  glClear(0x4000);                       //0x4000 is GL_COLOR_BUFFER_BIT
  glDrawElements(0x0001, 24, 0x1401, 0); //0x0001 is GL_LINES, 0x1401 is GL_UNSIGNED_BYTE
  glfwSwapBuffers(window);
  glfwPollEvents();
 }
 done();
}
void resize(void* win, int width, int height)
{
 glViewport(0, 0, width, height);
 glUniform2f(unires, (float)width, (float)height);
}
void keypress(void* win, int key, int scancode, int action, int mods)
{
 if(key == 256) {done();} //256 is escape
}
void done()
{
 glDeleteProgram(program);
 glfwTerminate();
 exit(0);
}