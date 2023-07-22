//Libaries
 using System;
 using System.Text;
 using System.Runtime.InteropServices;

public unsafe class Renderer
{
 //Externals
  [DllImport("libglfw.so")]
  private static extern int glfwInit();
  [DllImport("libglfw.so")]
  private static extern void glfwTerminate();
  [DllImport("libglfw.so")]
  private static extern void glfwWindowHint(int hint, int value);
  [DllImport("libglfw.so")]
  private static extern IntPtr glfwCreateWindow(int width, int height, IntPtr title, IntPtr monitor, IntPtr share);
  [DllImport("libglfw.so")]
  private static extern void glfwMakeContextCurrent(IntPtr window);
  [DllImport("libglfw.so")]
  private static extern IntPtr glfwSetWindowSizeCallback(IntPtr window, IntPtr callback);
  [DllImport("libglfw.so")]
  private static extern void glfwSwapBuffers(IntPtr window);
  [DllImport("libglfw.so")]
  private static extern void glfwPollEvents();
  [DllImport("libglfw.so")]
  private static extern bool glfwWindowShouldClose(IntPtr window);
  [DllImport("libglfw.so")]
  private static extern bool glfwGetKey(IntPtr window, uint key);
  [DllImport("libglfw.so")]
  private static extern IntPtr glfwSetKeyCallback(IntPtr window, IntPtr callback);
  [DllImport("libGL.so")]
  private static extern void glGenVertexArrays(uint count, IntPtr arrays);
  [DllImport("libGL.so")]
  private static extern void glGenBuffers(uint count, IntPtr buffers);
  [DllImport("libGL.so")]
  private static extern void glBindVertexArray(uint array);
  [DllImport("libGL.so")]
  private static extern void glBindBuffer(uint target, uint buf);
  [DllImport("libGL.so")]
  private static extern void glBufferData(uint target, uint size, IntPtr data, uint usage);
  [DllImport("libGL.so")]
  private static extern void glVertexAttribPointer(uint index, uint size, uint type, bool normalized, uint stride, IntPtr pointer);
  [DllImport("libGL.so")]
  private static extern void glEnableVertexAttribArray(uint index);
  [DllImport("libGL.so")]
  private static extern uint glCreateShader(uint type);
  [DllImport("libGL.so")]
  private static extern void glShaderSource(uint shader, uint count, IntPtr sources, IntPtr lengths); //String is a double pointer to a string
  [DllImport("libGL.so")]
  private static extern void glCompileShader(uint shader);
  [DllImport("libGL.so")]
  private static extern void glGetShaderiv(uint shader, uint param, IntPtr returnval);
  [DllImport("libGL.so")]
  private static extern void glGetShaderInfoLog(uint shader, uint bufsize, IntPtr returnsize, IntPtr buf);
  [DllImport("libGL.so")]
  private static extern void glDeleteShader(uint shader);
  [DllImport("libGL.so")]
  private static extern uint glCreateProgram();
  [DllImport("libGL.so")]
  private static extern void glAttachShader(uint program, uint shader);
  [DllImport("libGL.so")]
  private static extern void glLinkProgram(uint program);
  [DllImport("libGL.so")]
  private static extern void glGetProgramiv(uint program, uint param, IntPtr returnval);
  [DllImport("libGL.so")]
  private static extern void glGetProgramInfoLog(uint program, uint bufsize, IntPtr returnsize, IntPtr buf);
  [DllImport("libGL.so")]
  private static extern void glDetachShader(uint program, uint shader);
  [DllImport("libGL.so")]
  private static extern void glDeleteProgram(uint program);
  [DllImport("libGL.so")]
  private static extern void glUseProgram(uint program);
  [DllImport("libGL.so")]
  private static extern uint glGetUniformLocation(uint program, IntPtr name);
  [DllImport("libGL.so")]
  private static extern void glClear(uint flags);
  [DllImport("libGL.so")]
  private static extern void glDrawElements(uint drawtype, uint count, uint elemtype, uint offset);
  [DllImport("libGL.so")]
  private static extern void glUniform2f(uint uniform, float v1, float v2);
  [DllImport("libGL.so")]
  private static extern void glUniform2fv(uint uniform, uint count, IntPtr values);
  [DllImport("libGL.so")]
  private static extern void glUniform3fv(uint uniform, uint count, IntPtr values);
  [DllImport("libGL.so")]
  private static extern void glViewport(uint x, uint y, uint width, uint height);
  [DllImport("libGL.so")]
  private static extern uint glGetError();

 private delegate void  WindowSizeCallback(IntPtr window, int width, int height);
 private delegate void  KeyPressedCallback(IntPtr window, int key, int scancode, int action, int mods);
 private static IntPtr  window;
 private static uint    shader;
 private static uint    vao;
 private static uint    unires;
 private static uint    uniloc;
 private static uint    unicam;
 private static float[] loc = new float[3];
 private static float[] cam = new float[2];
 private static byte[]  resstr = Encoding.ASCII.GetBytes("res\0");
 private static byte[]  locstr = Encoding.ASCII.GetBytes("loc\0");
 private static byte[]  camstr = Encoding.ASCII.GetBytes("cam\0");
 private static uint[]  bufobjs = new uint[2];
 private static byte[]  winstr = Encoding.ASCII.GetBytes("Scumpert\0");
 private static byte[]  vertshaderstr = Encoding.ASCII.GetBytes("#version 450\nlayout (location=0) in vec3 pos;uniform vec2 res;uniform vec3 loc;uniform vec2 cam;void main(){gl_Position = vec4(pos,1.0);gl_Position.xyz -= loc;float z = gl_Position.z;gl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y);gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y);float y = gl_Position.y;gl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x);gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x);gl_Position.x *= (res[1]/res[0]);gl_Position.w = gl_Position.z;}\0");
 private static byte[]  fragshaderstr = Encoding.ASCII.GetBytes("#version 450\nout vec4 color;void main(){color = vec4(1,0,0,1);}\0");
 private static float[] vertices = new float[24] //Vertices of a cube
 {
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, +0.5f,
  +0.5f, -0.5f, +0.5f,
  +0.5f, -0.5f, -0.5f,
  -0.5f, +0.5f, -0.5f,
  -0.5f, +0.5f, +0.5f,
  +0.5f, +0.5f, +0.5f,
  +0.5f, +0.5f, -0.5f,
 };
 private static byte[]  elements = new byte[24]  //Elements fora wireframe cube with GL_LINES
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
  3, 7,
 };
 private static byte[]  buffer = new byte[256];
 private static short[] keys  = { 32, 65, 68, 83, 87, 262, 263, 264, 265, 340 };
 private static byte[]  flags = { 0b101, 0b00000, 0b01100, 0b11000, 0b10100, 0b1010, 0b1110, 0b0010, 0b0110, 0b001 };
 public static void Main()
 {
  //GLFW init
   glfwInit();                       //Required before anything else
   glfwWindowHint(0x22002, 4);       //0x22002 is GL_VERSION_MAJOR
   glfwWindowHint(0x22003, 5);       //0x22003 is GL_VERSION_MINOR
   fixed(byte* winname = winstr)
   {
    window = glfwCreateWindow(
     1600,            //Width
     900,             //Height
     (IntPtr)winname, //Name
     (IntPtr)0,       //Monitor
     (IntPtr)0);      //Share
   }
   glfwMakeContextCurrent(window);
   WindowSizeCallback winsizeDelegate = new WindowSizeCallback(WindowResized);
   glfwSetWindowSizeCallback(window, Marshal.GetFunctionPointerForDelegate(winsizeDelegate));
   KeyPressedCallback keypressDelegate = new KeyPressedCallback(KeyPressed);
   glfwSetKeyCallback(window, Marshal.GetFunctionPointerForDelegate(keypressDelegate));
  //Buffer init
   fixed(uint* vaoptr = &vao)
   {
    glGenVertexArrays(1, (IntPtr)vaoptr);
   }
   fixed(uint* bufobjptr = bufobjs)
   {
    glGenBuffers(2, (IntPtr)bufobjptr);
   }
   glBindVertexArray(vao);
   glBindBuffer(0x8892, bufobjs[0]);                          //0x8892 is GL_ARRAY_BUFFER. objs[0] is the vertex buffer object
   fixed(float* vertptr = vertices)
   {
    glBufferData(0x8892, 96, (IntPtr)vertptr, 0x88E4);        //0x88E4 is STATIC_DRAW
   }
   glBindBuffer(0x8893, bufobjs[1]);                          //0x8893 is GL_ELEMENT_BUFFER. objs[1] is the element buffer object
   fixed(byte* elemptr = elements)
   {
    glBufferData(0x8893, 24, (IntPtr)elemptr, 0x88E4);
   }
   glVertexAttribPointer(0, 3, 0x1406, false, 12, (IntPtr)0); //Index 0, 3 elements, 0x1406 is float, don't normalize, entry size of 12 bytes, offset of 0
   glEnableVertexAttribArray(0);
  //Shader init
   uint vertshader = glCreateShader(0x8B31);                  //0x8B31 is GL_VERTEX_SHADER
   uint result;
   uint size;
   fixed(byte* vertstrptr = vertshaderstr)
   {
    IntPtr ptr = new IntPtr(vertstrptr);
    glShaderSource(vertshader, 1, (IntPtr)(&ptr), (IntPtr)0); //Shader, line count, lines, linelengths
   }
   glCompileShader(vertshader);
   glGetShaderiv(vertshader, 0x8B81, (IntPtr)(&result));      //0x8B81 is GL_COMPILE_STATUS
   if(result == 0)
   {
    fixed(byte* bufptr = buffer)
    {
     glGetShaderInfoLog(vertshader, 0xFF, (IntPtr)(&size), (IntPtr)bufptr);
     Console.WriteLine(Encoding.ASCII.GetString(buffer));
     glDeleteShader(vertshader);
     Done();
    }
   }
   uint fragshader = glCreateShader(0x8B30);                  //0x8B30 is GL_FRAGMENT_SHADER
   fixed(byte* fragstrptr = fragshaderstr)
   {
    IntPtr ptr = new IntPtr(fragstrptr);
    glShaderSource(fragshader, 1, (IntPtr)(&ptr), (IntPtr)0);
   }
   glCompileShader(fragshader);
   glGetShaderiv(fragshader, 0x8B81, (IntPtr)(&result));
   if(result == 0)
   {
    fixed(byte* bufptr = buffer)
    {
     glGetShaderInfoLog(fragshader, 0xFF, (IntPtr)(&size), (IntPtr)bufptr);
     Console.WriteLine(Encoding.ASCII.GetString(buffer));
     glDeleteShader(vertshader);
     glDeleteShader(fragshader);
     Done();
    }
   }
   shader = glCreateProgram();
   glAttachShader(shader, vertshader);
   glAttachShader(shader, fragshader);
   glLinkProgram(shader);
   glGetProgramiv(shader, 0x8B82, (IntPtr)(&result));         //0x8B82 is GL_LINK_STATUS
   if(result == 0)
   {
    fixed(byte* bufptr = buffer)
    {
     glGetShaderInfoLog(shader, 0xFF, (IntPtr)(&size), (IntPtr)bufptr);
     Console.WriteLine(Encoding.ASCII.GetString(buffer));
     glDeleteShader(vertshader);
     glDeleteShader(fragshader);
     glDeleteProgram(shader);
     Done();
    }
   }
   glUseProgram(shader);
   glDetachShader(shader, vertshader);
   glDetachShader(shader, fragshader);
   glDeleteShader(vertshader);
   glDeleteShader(fragshader);
   fixed(byte* resstrptr = resstr)
   {
    unires = glGetUniformLocation(shader, (IntPtr)resstrptr);
   }
   fixed(byte* locstrptr = locstr)
   {
    uniloc = glGetUniformLocation(shader, (IntPtr)locstrptr);
   }
   fixed(byte* camstrptr = camstr)
   {
    unicam = glGetUniformLocation(shader, (IntPtr)camstrptr);
   }
  //Render loop
   while(true)
   {
    for(int i = 0; i < 10; i++)
    {
     if(glfwGetKey(window, (uint)keys[i])) 
     {  
      if((flags[i] & 0b11) == 0)      //0b00 is wasd for camera movement
      {
        float negpos0  = -0.001f;
        float negpos1  = -0.001f;
        if((flags[i] & 0b00100) == 0) { negpos0 = +0.001f; }
        if((flags[i] & 0b01000) == 0) { negpos1 = +0.001f; }
        if((flags[i] & 0b10000) == 0) { loc[0] -= (float)Math.Cos(cam[1]) * negpos0; loc[2] -= (float)Math.Sin(cam[1]) * negpos1; } 
        else { loc[0] += (float)Math.Sin(cam[1]) * negpos0; loc[2] += (float)Math.Cos(cam[1]) * negpos1; }
        fixed(float* locptr = loc)
        {
         glUniform3fv(uniloc, 1, (IntPtr)locptr);
        }
      }
      else if((flags[i] & 0b10) == 0) //0b01 is shift/space for up/down
      {
       if(keys[i] == 340) { loc[1] -= 0.001f; } else { loc[1] += 0.001f; }
       fixed(float* locptr = loc)
       {
        glUniform3fv(uniloc, 1, (IntPtr)locptr);
       }
      }
      else                            //0b10 is left/right/up/down for camera angles
      {
        float negpos = +0.001f;
        if((flags[i] & 0b0100) == 0) { negpos = -0.001f; }
        if((flags[i] & 0b1000) == 0) { cam[0] += negpos; } else { cam[1] += negpos; }
        fixed(float* camptr = cam)
        {
         glUniform2fv(unicam, 1, (IntPtr)camptr);
        }
      }
     }
    }
    glClear(0x4000);                       //0x4000 is GL_COLOR_BUFFER_BIT
    glDrawElements(0x0001, 24, 0x1401, 0); //0x0001 is GL_LINES, 0x1401 is GL_UNSIGNED_CHAR
    glfwSwapBuffers(window);
    glfwPollEvents();
    if(glfwWindowShouldClose(window)) { Done(); }
   }
 }
 private static void WindowResized(IntPtr window, int width, int height)
 {
  glViewport(0, 0, (uint)width, (uint)height);
  glUniform2f(unires, (float)width, (float)height);
  Console.WriteLine(glGetError());
 }
 private static void KeyPressed(IntPtr window, int key, int scancode, int action, int mods)
 {
  if(key == 256) { Done(); } //256 is escape
 }
 private static void Done()
 {
  glDeleteProgram(shader);
  glfwTerminate();
  Environment.Exit(0);
 }
}