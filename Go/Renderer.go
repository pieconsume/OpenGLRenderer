package main

//#cgo LDFLAGS: -lglfw -lGL -lm
//#include <header.h>
import "C"
import "unsafe"
import "os"
import "fmt"

func main(){
 //Window init
  C.glfwInit()                 //Required before anything else
  C.glfwWindowHint(0x22002, 4) //0x22002 is GL_VERSION_MAJOR
  C.glfwWindowHint(0x22003, 5) //0x22003 is GL_VERSION_MINOR 
  window := C.glfwCreateWindow(1600, 900, unsafe.Pointer(C.CString("scumpert!!!")), nil, nil)
  C.glfwMakeContextCurrent(window)
 //Buffer init
  vao := make([]C.uint, 1)
  objs := make([]C.uint, 2)
  vertices := []C.float{ -0.5, -0.5, -0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5, +0.5, +0.5,+0.5, +0.5, +0.5, +0.5, +0.5, -0.5 }
  elements := []C.char{ 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 }
  C.glGenVertexArrays(1, unsafe.Pointer(&vao[0]))
  C.glGenBuffers(2, unsafe.Pointer(&objs[0]))
  C.glBindVertexArray(vao[0])
  C.glBindBuffer(0x8892, objs[0])                 //0x8892 is GL_ARRAY_BUFFER. objs[0] is the vertex buffer object
  C.glBufferData(0x8892, 96, unsafe.Pointer(&vertices[0]), 0x88E4)    //0x88E4 is STATIC_DRAW
  C.glBindBuffer(0x8893, objs[1])                 //0x8893 is GL_ELEMENT_BUFFER. objs[1] is the element buffer object
  C.glBufferData(0x8893, 24, unsafe.Pointer(&elements[0]), 0x88E4)
  C.glVertexAttribPointer(0, 3, 0x1406, 0, 12, nil) //Index 0, 3 elements, 0x1406 is float, don't normalize, entry size of 12 bytes, offset of 0
  C.glEnableVertexAttribArray(0)
 //Shader init
  buffer := make([]C.char, 256)
  vertstr := C.CString("#version 450\nlayout (location = 0) in vec3 pos;uniform vec2 res;uniform vec3 loc;uniform vec2 cam;void main() {gl_Position = vec4(pos, 1.0);gl_Position.xyz -= loc;float z = gl_Position.z;gl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y);gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y);float y = gl_Position.y;gl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x);gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x);gl_Position.x *=  (res[1]/res[0]);gl_Position.w = gl_Position.z;}")
  fragstr := C.CString("#version 450\nout vec4 color;void main() {color = vec4(1, 0, 0, 1);}")
  result := C.int(0)
  size := C.int(0)
  vertshader := C.glCreateShader(0x8B31)         //0x8B31 is GL_VERTEX_SHADER
  C.glShaderSource(vertshader, 1, unsafe.Pointer(&vertstr), nil) //Shader, line count, lines, linelengths
  C.glCompileShader(vertshader)
  C.glGetShaderiv(vertshader, 0x8B81, unsafe.Pointer(&result))       //0x8B81 is GL_COMPILE_STATUS
  if(result == 0) { C.glGetShaderInfoLog(vertshader, 0xFF, unsafe.Pointer(&size), unsafe.Pointer(&buffer[0])); C.write(1, &buffer[0], size); C.glDeleteShader(vertshader); done(); }
  fragshader := C.glCreateShader(0x8B30)         //0x8B30 is GL_FRAGMENT_SHADER
  C.glShaderSource(fragshader, 1, unsafe.Pointer(&fragstr), nil)
  C.glCompileShader(fragshader)
  C.glGetShaderiv(fragshader, 0x8B81, unsafe.Pointer(&result))
  if(result == 0) { C.glGetShaderInfoLog(fragshader, 0xFF, unsafe.Pointer(&size), unsafe.Pointer(&buffer[0])); C.write(1, &buffer[0], size); C.glDeleteShader(vertshader); C.glDeleteShader(fragshader); done(); }
  program := C.glCreateProgram()
  C.glAttachShader(program, vertshader)
  C.glAttachShader(program, fragshader)
  C.glLinkProgram(program)
  C.glGetProgramiv(program, 0x8B82, unsafe.Pointer(&result)) //0x8B82 is GL_LINK_STATUS
  if(result == 0) { C.glGetProgramInfoLog(program, 0xFF, unsafe.Pointer(&size), unsafe.Pointer(&buffer[0])); C.write(1, &buffer[0], size); C.glDeleteShader(vertshader); C.glDeleteShader(fragshader); C.glDeleteProgram(program); done(); }
  C.glUseProgram(program)
  C.glDetachShader(program, vertshader)
  C.glDetachShader(program, fragshader)
  C.glDeleteShader(vertshader)
  C.glDeleteShader(fragshader)
  loc := make([]C.float, 3)
  cam := make([]C.float, 2)
  unires := C.glGetUniformLocation(program, C.CString("res"))
  uniloc := C.glGetUniformLocation(program, C.CString("loc"))
  unicam := C.glGetUniformLocation(program, C.CString("cam"))
  oldwidth := C.int(0)
  oldheight := C.int(0)
  width := C.int(0)
  height := C.int(0)
  error := C.uint(10)
  r := C.float(0)
  g := C.float(0)
  b := C.float(0)
  a := C.float(0)
 for (C.glfwWindowShouldClose(window)==0){
  r += 0.0001;
  C.glClearColor(r, g, b, a);
  C.glfwGetFramebufferSize(window, &width, &height);
  if (oldwidth != width || oldheight != height) { oldwidth = width; oldheight = height; C.glViewport(0, 0, width, height); C.glUniform2f(unires, C.float(width), C.float(height)); }
  if (C.glfwGetKey(window, 256)==1) { done(); }
  if (C.glfwGetKey(window,  32)==1) { loc[1] += 0.01; C.glUniform3fv(uniloc, 1, &loc[0]); }                                                     //Space
  if (C.glfwGetKey(window,  65)==1) { loc[0] += C.cosf(cam[1]) * -0.01; loc[2] += C.sinf(cam[1]) * -0.01; C.glUniform3fv(uniloc, 1, &loc[0]); } //A
  if (C.glfwGetKey(window,  68)==1) { loc[0] += C.cosf(cam[1]) * +0.01; loc[2] += C.sinf(cam[1]) * +0.01; C.glUniform3fv(uniloc, 1, &loc[0]); } //D
  if (C.glfwGetKey(window,  83)==1) { loc[0] += C.sinf(cam[1]) * +0.01; loc[2] += C.cosf(cam[1]) * -0.01; C.glUniform3fv(uniloc, 1, &loc[0]); } //S
  if (C.glfwGetKey(window,  87)==1) { loc[0] += C.sinf(cam[1]) * -0.01; loc[2] += C.cosf(cam[1]) * +0.01; C.glUniform3fv(uniloc, 1, &loc[0]); } //W
  if (C.glfwGetKey(window, 262)==1) { cam[1] -= 0.01; C.glUniform2fv(unicam, 1, &cam[0]); }                                                     //Right
  if (C.glfwGetKey(window, 263)==1) { cam[1] += 0.01; C.glUniform2fv(unicam, 1, &cam[0]); }                                                     //Left
  if (C.glfwGetKey(window, 264)==1) { cam[0] -= 0.01; C.glUniform2fv(unicam, 1, &cam[0]); }                                                     //Down
  if (C.glfwGetKey(window, 265)==1) { cam[0] += 0.01; C.glUniform2fv(unicam, 1, &cam[0]); }                                                     //Up
  if (C.glfwGetKey(window, 340)==1) { loc[1] -= 0.01; C.glUniform3fv(uniloc, 1, &loc[0]); }                                                     //LShift
  C.glClear(0x4000)                       //0x4000 is GL_COLOR_BUFFER_BIT
  C.glDrawElements(0x0001, 24, 0x1401, 0) //0x0001 is GL_LINES, 0x1401 is GL_UNSIGNED_BYTE
  C.glfwSwapBuffers(window)
  C.glfwPollEvents()
  //fmt.Print(window)
  //fmt.Print("\n")
  error = C.glGetError()
  if (error != 0) { fmt.Print(error); fmt.Print("\n"); }
  error = C.glfwGetError(nil)
  if (error != 0) { fmt.Print(error); fmt.Print("\n"); }
 }
}

func done(){
  os.Exit(0)
}