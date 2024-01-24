import java.lang.foreign.*;
import java.lang.invoke.*;
import static java.lang.foreign.ValueLayout.*;

public class Renderer
{
 public static void main(String[] args) throws Throwable
 {
  try (Arena arena = Arena.ofConfined())
  {
   //Externs
    Linker linker = Linker.nativeLinker();
    SymbolLookup libc = SymbolLookup.libraryLookup("libc.so.6", arena);
    SymbolLookup glfw = SymbolLookup.libraryLookup("libglfw.so", arena);
    SymbolLookup gl = SymbolLookup.libraryLookup("libGL.so", arena);
    MemorySegment write_addr = libc.find("write").get();
    MemorySegment glfwInit_addr = glfw.find("glfwInit").get();
    MemorySegment glfwWindowHint_addr = glfw.find("glfwWindowHint").get();
    MemorySegment glfwCreateWindow_addr = glfw.find("glfwCreateWindow").get();
    MemorySegment glfwMakeContextCurrent_addr = glfw.find("glfwMakeContextCurrent").get();
    MemorySegment glfwGetFramebufferSize_addr = glfw.find("glfwGetFramebufferSize").get();
    MemorySegment glfwSwapBuffers_addr = glfw.find("glfwSwapBuffers").get();
    MemorySegment glfwPollEvents_addr = glfw.find("glfwPollEvents").get();
    MemorySegment glfwWindowShouldClose_addr = glfw.find("glfwWindowShouldClose").get();
    MemorySegment glfwGetKey_addr = glfw.find("glfwGetKey").get();
    MemorySegment glfwTerminate_addr = glfw.find("glfwTerminate").get();
    MemorySegment glGenVertexArrays_addr = gl.find("glGenVertexArrays").get();
    MemorySegment glGenBuffers_addr = gl.find("glGenBuffers").get();
    MemorySegment glBindVertexArray_addr = gl.find("glBindVertexArray").get();
    MemorySegment glBindBuffer_addr = gl.find("glBindBuffer").get();
    MemorySegment glBufferData_addr = gl.find("glBufferData").get();
    MemorySegment glVertexAttribPointer_addr = gl.find("glVertexAttribPointer").get();
    MemorySegment glEnableVertexAttribArray_addr = gl.find("glEnableVertexAttribArray").get();
    MemorySegment glCreateShader_addr = gl.find("glCreateShader").get();
    MemorySegment glShaderSource_addr = gl.find("glShaderSource").get();
    MemorySegment glCompileShader_addr = gl.find("glCompileShader").get();
    MemorySegment glGetShaderiv_addr = gl.find("glGetShaderiv").get();
    MemorySegment glGetShaderInfoLog_addr = gl.find("glGetShaderInfoLog").get();
    MemorySegment glDeleteShader_addr = gl.find("glDeleteShader").get();
    MemorySegment glCreateProgram_addr = gl.find("glCreateProgram").get();
    MemorySegment glAttachShader_addr = gl.find("glAttachShader").get();
    MemorySegment glLinkProgram_addr = gl.find("glLinkProgram").get();
    MemorySegment glGetProgramiv_addr = gl.find("glGetProgramiv").get();
    MemorySegment glGetProgramInfoLog_addr = gl.find("glGetProgramInfoLog").get();
    MemorySegment glDetachShader_addr = gl.find("glDetachShader").get();
    MemorySegment glDeleteProgram_addr = gl.find("glDeleteProgram").get();
    MemorySegment glUseProgram_addr = gl.find("glUseProgram").get();
    MemorySegment glGetUniformLocation_addr = gl.find("glGetUniformLocation").get();
    MemorySegment glClear_addr = gl.find("glClear").get();
    MemorySegment glDrawElements_addr = gl.find("glDrawElements").get();
    MemorySegment glUniform2f_addr = gl.find("glUniform2f").get();
    MemorySegment glUniform2fv_addr = gl.find("glUniform2fv").get();
    MemorySegment glUniform3fv_addr = gl.find("glUniform3fv").get();
    MemorySegment glViewport_addr = gl.find("glViewport").get();
    MemorySegment glGetError_addr = gl.find("glGetError").get();
    FunctionDescriptor write_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, ADDRESS, JAVA_INT);
    FunctionDescriptor glfwInit_desc = FunctionDescriptor.of(JAVA_INT);
    FunctionDescriptor glfwWindowHint_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT);
    FunctionDescriptor glfwCreateWindow_desc = FunctionDescriptor.of(JAVA_LONG, JAVA_INT, JAVA_INT, ADDRESS, JAVA_LONG, JAVA_LONG);
    FunctionDescriptor glfwMakeContextCurrent_desc = FunctionDescriptor.of(JAVA_INT, JAVA_LONG);
    FunctionDescriptor glfwSwapBuffers_desc = FunctionDescriptor.of(JAVA_INT, JAVA_LONG);
    FunctionDescriptor glfwPollEvents_desc = FunctionDescriptor.of(JAVA_INT);
    FunctionDescriptor glfwWindowShouldClose_desc = FunctionDescriptor.of(JAVA_INT, JAVA_LONG);
    FunctionDescriptor glfwGetFramebufferSize_desc = FunctionDescriptor.of(JAVA_INT, JAVA_LONG, ADDRESS, ADDRESS);
    FunctionDescriptor glfwGetKey_desc = FunctionDescriptor.of(JAVA_INT, JAVA_LONG, JAVA_INT);
    FunctionDescriptor glfwTerminate_desc = FunctionDescriptor.of(JAVA_INT);
    FunctionDescriptor glGenVertexArrays_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, ADDRESS);
    FunctionDescriptor glGenBuffers_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, ADDRESS);
    FunctionDescriptor glBindVertexArray_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glBindBuffer_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT);
    FunctionDescriptor glBufferData_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, ADDRESS, JAVA_INT);
    FunctionDescriptor glVertexAttribPointer_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, JAVA_INT, JAVA_INT, JAVA_INT, JAVA_LONG);
    FunctionDescriptor glEnableVertexAttribArray_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glCreateShader_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glShaderSource_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, ADDRESS, JAVA_LONG);
    FunctionDescriptor glCompileShader_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glGetShaderiv_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, ADDRESS);
    FunctionDescriptor glGetShaderInfoLog_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, ADDRESS, ADDRESS);
    FunctionDescriptor glDeleteShader_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glCreateProgram_desc = FunctionDescriptor.of(JAVA_INT);
    FunctionDescriptor glAttachShader_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT);
    FunctionDescriptor glLinkProgram_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glGetProgramiv_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, ADDRESS);
    FunctionDescriptor glGetProgramInfoLog_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, ADDRESS, ADDRESS);
    FunctionDescriptor glDetachShader_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT);
    FunctionDescriptor glDeleteProgram_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glUseProgram_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glGetUniformLocation_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, ADDRESS);
    FunctionDescriptor glClear_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT);
    FunctionDescriptor glDrawElements_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, JAVA_INT, JAVA_INT);
    FunctionDescriptor glUniform2f_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_FLOAT, JAVA_FLOAT);
    FunctionDescriptor glUniform2fv_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, ADDRESS);
    FunctionDescriptor glUniform3fv_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, ADDRESS);
    FunctionDescriptor glViewport_desc = FunctionDescriptor.of(JAVA_INT, JAVA_INT, JAVA_INT, JAVA_INT, JAVA_INT);
    FunctionDescriptor glGetError_desc = FunctionDescriptor.of(JAVA_INT);
    MethodHandle write = linker.downcallHandle(write_addr, write_desc);
    MethodHandle glfwInit = linker.downcallHandle(glfwInit_addr, glfwInit_desc);
    MethodHandle glfwWindowHint = linker.downcallHandle(glfwWindowHint_addr, glfwWindowHint_desc);
    MethodHandle glfwCreateWindow = linker.downcallHandle(glfwCreateWindow_addr, glfwCreateWindow_desc);
    MethodHandle glfwMakeContextCurrent = linker.downcallHandle(glfwMakeContextCurrent_addr, glfwMakeContextCurrent_desc);
    MethodHandle glfwSwapBuffers = linker.downcallHandle(glfwSwapBuffers_addr, glfwSwapBuffers_desc);
    MethodHandle glfwPollEvents = linker.downcallHandle(glfwPollEvents_addr, glfwPollEvents_desc);
    MethodHandle glfwWindowShouldClose = linker.downcallHandle(glfwWindowShouldClose_addr, glfwWindowShouldClose_desc);
    MethodHandle glfwGetFramebufferSize = linker.downcallHandle(glfwGetFramebufferSize_addr, glfwGetFramebufferSize_desc);
    MethodHandle glfwGetKey = linker.downcallHandle(glfwGetKey_addr, glfwGetKey_desc);
    MethodHandle glfwTerminate = linker.downcallHandle(glfwTerminate_addr, glfwTerminate_desc);
    MethodHandle glGenVertexArrays = linker.downcallHandle(glGenVertexArrays_addr, glGenVertexArrays_desc);
    MethodHandle glGenBuffers = linker.downcallHandle(glGenBuffers_addr, glGenBuffers_desc);
    MethodHandle glBindVertexArray = linker.downcallHandle(glBindVertexArray_addr, glBindVertexArray_desc);
    MethodHandle glBindBuffer = linker.downcallHandle(glBindBuffer_addr, glBindBuffer_desc);
    MethodHandle glBufferData = linker.downcallHandle(glBufferData_addr, glBufferData_desc);
    MethodHandle glVertexAttribPointer = linker.downcallHandle(glVertexAttribPointer_addr, glVertexAttribPointer_desc);
    MethodHandle glEnableVertexAttribArray = linker.downcallHandle(glEnableVertexAttribArray_addr, glEnableVertexAttribArray_desc);
    MethodHandle glCreateShader = linker.downcallHandle(glCreateShader_addr, glCreateShader_desc);
    MethodHandle glShaderSource = linker.downcallHandle(glShaderSource_addr, glShaderSource_desc);
    MethodHandle glCompileShader = linker.downcallHandle(glCompileShader_addr, glCompileShader_desc);
    MethodHandle glGetShaderiv = linker.downcallHandle(glGetShaderiv_addr, glGetShaderiv_desc);
    MethodHandle glGetShaderInfoLog = linker.downcallHandle(glGetShaderInfoLog_addr, glGetShaderInfoLog_desc);
    MethodHandle glDeleteShader = linker.downcallHandle(glDeleteShader_addr, glDeleteShader_desc);
    MethodHandle glCreateProgram = linker.downcallHandle(glCreateProgram_addr, glCreateProgram_desc);
    MethodHandle glAttachShader = linker.downcallHandle(glAttachShader_addr, glAttachShader_desc);
    MethodHandle glLinkProgram = linker.downcallHandle(glLinkProgram_addr, glLinkProgram_desc);
    MethodHandle glGetProgramiv = linker.downcallHandle(glGetProgramiv_addr, glGetProgramiv_desc);
    MethodHandle glGetProgramInfoLog = linker.downcallHandle(glGetProgramInfoLog_addr, glGetProgramInfoLog_desc);
    MethodHandle glDetachShader = linker.downcallHandle(glDetachShader_addr, glDetachShader_desc);
    MethodHandle glDeleteProgram = linker.downcallHandle(glDeleteProgram_addr, glDeleteProgram_desc);
    MethodHandle glUseProgram = linker.downcallHandle(glUseProgram_addr, glUseProgram_desc);
    MethodHandle glGetUniformLocation = linker.downcallHandle(glGetUniformLocation_addr, glGetUniformLocation_desc);
    MethodHandle glClear = linker.downcallHandle(glClear_addr, glClear_desc);
    MethodHandle glDrawElements = linker.downcallHandle(glDrawElements_addr, glDrawElements_desc);
    MethodHandle glUniform2f = linker.downcallHandle(glUniform2f_addr, glUniform2f_desc);
    MethodHandle glUniform2fv = linker.downcallHandle(glUniform2fv_addr, glUniform2fv_desc);
    MethodHandle glUniform3fv = linker.downcallHandle(glUniform3fv_addr, glUniform3fv_desc);
    MethodHandle glViewport = linker.downcallHandle(glViewport_addr, glViewport_desc);
    MethodHandle glGetError = linker.downcallHandle(glGetError_addr, glGetError_desc);
   //Allocations
    int vao, vbo, ebo;
    float[] vertices = { -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, +0.5f, +0.5f, -0.5f, +0.5f, +0.5f, -0.5f, -0.5f, -0.5f, +0.5f, -0.5f, -0.5f, +0.5f, +0.5f, +0.5f, +0.5f, +0.5f, +0.5f, +0.5f, -0.5f };
    byte[]  elements = { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 };
    MemorySegment buffer = arena.allocate(256, 1);
    MemorySegment vaomem = arena.allocate(4, 4);
    MemorySegment vbomem = arena.allocate(8, 4);
    MemorySegment verticesmem = arena.allocateArray(JAVA_FLOAT, vertices);
    MemorySegment elementsmem = arena.allocateArray(JAVA_BYTE, elements);
    MemorySegment vertstr = arena.allocateUtf8String("#version 450\nlayout (location = 0) in vec3 pos;uniform vec2 res;uniform vec3 loc;uniform vec2 cam;void main() {gl_Position = vec4(pos, 1.0);gl_Position.xyz -= loc;float z = gl_Position.z;gl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y);gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y);float y = gl_Position.y;gl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x);gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x);gl_Position.x *=  (res[1]/res[0]);gl_Position.w = gl_Position.z;}");
    MemorySegment fragstr = arena.allocateUtf8String("#version 450\nout vec4 color;void main(){color = vec4(1, 0, 0, 1);}");
    MemorySegment vertstrptr = arena.allocate(ADDRESS, vertstr);
    MemorySegment fragstrptr = arena.allocate(ADDRESS, fragstr);
    MemorySegment loc = arena.allocate(12,4);
    MemorySegment cam = arena.allocate(8,4);
   //Window init
    glfwInit.invoke();
    glfwWindowHint.invoke(0x22002, 4); //0x22002 is GLFW_VERSION_MAJOR
    glfwWindowHint.invoke(0x22003, 5); //0x22003 is GLFW_VERSION_MINOR
    long window = (long)glfwCreateWindow.invoke(1600, 900, arena.allocateUtf8String("scumpert!!!"), 0, 0);
    glfwMakeContextCurrent.invoke(window);
   //Buffer init
    glGenVertexArrays.invoke(1, vaomem);
    glGenBuffers.invoke(2, vbomem);
    vao = vaomem.get(JAVA_INT, 0);
    vbo = vbomem.get(JAVA_INT, 0);
    ebo = vbomem.get(JAVA_INT, 4);
    glBindVertexArray.invoke(vao);
    glBindBuffer.invoke(0x8892, vbo);                     //0x8892 is GL_ARRAY_BUFFER
    glBufferData.invoke(0x8892, 96, verticesmem, 0x88E4); //0x88E4 is GL_STATIC_DRAW
    glBindBuffer.invoke(0x8893, ebo);                     //0x8893 is GL_ELEMENT_BUFFER
    glBufferData.invoke(0x8893, 24, elementsmem, 0x88E4);
    glVertexAttribPointer.invoke(0, 3, 0x1406, 0, 12, 0);
    glEnableVertexAttribArray.invoke(0);
   //Shader init
    MemorySegment result = arena.allocate(4, 4);
    MemorySegment size = arena.allocate(4, 4);
    int vertshader = (int)glCreateShader.invoke(0x8B31); //0x8B31 is GL_VERTEX_SHADER
    glShaderSource.invoke(vertshader, 1, vertstrptr, 0);
    glCompileShader.invoke(vertshader);
    glGetShaderiv.invoke(vertshader, 0x8B81, result);    //0x8B81 is GL_COMPILE_STATUS
    if(result.get(JAVA_INT, 0) == 0) { glGetShaderInfoLog.invoke(vertshader, 0xFF, size, buffer); write.invoke(1, buffer, size.get(JAVA_INT, 0)); glDeleteShader.invoke(vertshader); done(glfwTerminate); }
    int fragshader = (int)glCreateShader.invoke(0x8B30); //0x8B80 is GL_FRAGMENT_SHADER
    glShaderSource.invoke(fragshader, 1, fragstrptr, 0);
    glCompileShader.invoke(fragshader);
    glGetShaderiv.invoke(fragshader, 0x8B81, result);
    if(result.get(JAVA_INT, 0) == 0) { glGetShaderInfoLog.invoke(fragshader, 0xFF, size, buffer); write.invoke(1, buffer, size.get(JAVA_INT, 0)); glDeleteShader.invoke(vertshader); glDeleteShader.invoke(fragshader); done(glfwTerminate); }
    int program = (int)glCreateProgram.invoke();
    glAttachShader.invoke(program, vertshader);
    glAttachShader.invoke(program, fragshader);
    glLinkProgram.invoke(program);
    glGetProgramiv.invoke(program, 0x8B82, result); //0x8B82 is GL_LINK_STATUS
    if(result.get(JAVA_INT, 0) == 0) { glGetProgramInfoLog.invoke(program, 0xFF, size, buffer); write.invoke(1, buffer, size.get(JAVA_INT, 0)); glDeleteShader.invoke(vertshader); glDeleteShader.invoke(fragshader); glDeleteProgram.invoke(program); done(glfwTerminate); }
    glUseProgram.invoke(program);
    glDetachShader.invoke(program, vertshader);
    glDetachShader.invoke(program, fragshader);
    glDeleteShader.invoke(vertshader);
    glDeleteShader.invoke(fragshader);
    int unires = (int)glGetUniformLocation.invoke(program, arena.allocateUtf8String("res"));
    int unicam = (int)glGetUniformLocation.invoke(program, arena.allocateUtf8String("cam"));
    int uniloc = (int)glGetUniformLocation.invoke(program, arena.allocateUtf8String("loc"));
    MemorySegment width = arena.allocate(4,4);
    MemorySegment height = arena.allocate(4,4);
    int oldwidth = 0;
    int oldheight = 0;
   while((int)glfwWindowShouldClose.invoke(window)==0)
   {
    glfwGetFramebufferSize.invoke(window, width, height);
    if(width.get(JAVA_INT, 0) != oldwidth || height.get(JAVA_INT, 0) != oldheight) { oldwidth = width.get(JAVA_INT, 0); oldheight = height.get(JAVA_INT, 0); glViewport.invoke(0, 0, oldwidth, oldheight); glUniform2f.invoke(unires, (float)oldwidth, (float)oldheight); } 
    if ((int)glfwGetKey.invoke(window, 256)==1) { done(glfwTerminate); }                                                                                                                                                                                                                       //Escape
    if ((int)glfwGetKey.invoke(window,  32)==1) { loc.set(JAVA_FLOAT, 4, loc.get(JAVA_FLOAT, 4) + 0.01f); glUniform3fv.invoke(uniloc, 1, loc); }                                                                                                                                               //Space
    if ((int)glfwGetKey.invoke(window,  65)==1) { loc.set(JAVA_FLOAT, 0, loc.get(JAVA_FLOAT, 0) + (float)Math.cos(cam.get(JAVA_FLOAT, 4)) * -0.01f); loc.set(JAVA_FLOAT, 8, loc.get(JAVA_FLOAT, 8) + (float)Math.sin(cam.get(JAVA_FLOAT, 4)) * -0.01f); glUniform3fv.invoke(uniloc, 1, loc); } //A    
    if ((int)glfwGetKey.invoke(window,  68)==1) { loc.set(JAVA_FLOAT, 0, loc.get(JAVA_FLOAT, 0) + (float)Math.cos(cam.get(JAVA_FLOAT, 4)) * +0.01f); loc.set(JAVA_FLOAT, 8, loc.get(JAVA_FLOAT, 8) + (float)Math.sin(cam.get(JAVA_FLOAT, 4)) * +0.01f); glUniform3fv.invoke(uniloc, 1, loc); } //D
    if ((int)glfwGetKey.invoke(window,  83)==1) { loc.set(JAVA_FLOAT, 0, loc.get(JAVA_FLOAT, 0) + (float)Math.sin(cam.get(JAVA_FLOAT, 4)) * +0.01f); loc.set(JAVA_FLOAT, 8, loc.get(JAVA_FLOAT, 8) + (float)Math.cos(cam.get(JAVA_FLOAT, 4)) * -0.01f); glUniform3fv.invoke(uniloc, 1, loc); } //S
    if ((int)glfwGetKey.invoke(window,  87)==1) { loc.set(JAVA_FLOAT, 0, loc.get(JAVA_FLOAT, 0) + (float)Math.sin(cam.get(JAVA_FLOAT, 4)) * -0.01f); loc.set(JAVA_FLOAT, 8, loc.get(JAVA_FLOAT, 8) + (float)Math.cos(cam.get(JAVA_FLOAT, 4)) * +0.01f); glUniform3fv.invoke(uniloc, 1, loc); } //W
    if ((int)glfwGetKey.invoke(window, 262)==1) { cam.set(JAVA_FLOAT, 4, cam.get(JAVA_FLOAT, 4) - 0.01f); glUniform2fv.invoke(unicam, 1, cam); }                                                                                                                                               //Right
    if ((int)glfwGetKey.invoke(window, 263)==1) { cam.set(JAVA_FLOAT, 4, cam.get(JAVA_FLOAT, 4) + 0.01f); glUniform2fv.invoke(unicam, 1, cam); }                                                                                                                                               //Left
    if ((int)glfwGetKey.invoke(window, 264)==1) { cam.set(JAVA_FLOAT, 0, cam.get(JAVA_FLOAT, 0) - 0.01f); glUniform2fv.invoke(unicam, 1, cam); }                                                                                                                                               //Down
    if ((int)glfwGetKey.invoke(window, 265)==1) { cam.set(JAVA_FLOAT, 0, cam.get(JAVA_FLOAT, 0) + 0.01f); glUniform2fv.invoke(unicam, 1, cam); }                                                                                                                                               //Up
    if ((int)glfwGetKey.invoke(window, 340)==1) { loc.set(JAVA_FLOAT, 4, loc.get(JAVA_FLOAT, 4) - 0.01f); glUniform3fv.invoke(uniloc, 1, loc); }                                                                                                                                               //LShift
    glClear.invoke(0x4000);
    glDrawElements.invoke(0x0001, 24, 0x1401, 0); //0x0001 is GL_LINES, 0x1401 is GL_UNSIGNED_BYTE
    glfwSwapBuffers.invoke(window);
    glfwPollEvents.invoke();
    //done(glfwTerminate);
   }
  }
 }
 public static void done(MethodHandle terminate) throws Throwable
 {
  terminate.invoke();
  System.exit(0);
 }
}