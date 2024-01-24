#Imports
from ctypes import *
import math
#Vars
libc=CDLL("libc.so.6")
glfw=CDLL("libglfw.so")
gl=CDLL("libGL.so")
buffer = (c_byte * 256)(0)
vertices = (c_float * 24)(
 -0.2, -0.2, -0.2, 
 -0.2, -0.2, +0.2, 
 +0.2, -0.2, +0.2, 
 +0.2, -0.2, -0.2, 
 -0.2, +0.2, -0.2, 
 -0.2, +0.2, +0.2,
 +0.2, +0.2, +0.2, 
 +0.2, +0.2, -0.2)
elements = (c_byte * 24)(
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
 3, 7)
vao = (c_int*1)(5)
objs = (c_int * 2)()
vertptr = POINTER(c_char_p)(c_char_p(bytes("#version 450\nlayout (location = 0) in vec3 posuniform vec2 resuniform vec3 locuniform vec2 camvoid main() {gl_Position = vec4(pos, 1.0)gl_Position.xyz -= locfloat z = gl_Position.zgl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y)gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y)float y = gl_Position.ygl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x)gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x)gl_Position.x *=  (res[1]/res[0])gl_Position.w = gl_Position.z}", "UTF-8")))
fragptr = POINTER(c_char_p)(c_char_p(bytes("#version 450\nout vec4 colorvoid main() {color = vec4(1, 0, 0, 1)}", "UTF-8")))
loc = (c_float*3)()
cam = (c_float*2)()
#Functions
def done():
 glfw.glfwTerminate()
 quit()
#Window init
glfw.glfwInit()
glfw.glfwWindowHint(0x22002,4)
glfw.glfwWindowHint(0x22003,5)
glfw.glfwWindowHint(0x22006,1)
glfw.glfwWindowHint(0x22008,0x32001)
window=c_void_p(glfw.glfwCreateWindow(1600,900,c_char_p(bytes("scumpert!!", 'UTF-8')),0,0))
glfw.glfwMakeContextCurrent(window)
#Buffer init
gl.glGenVertexArrays(1, vao)
gl.glGenBuffers(2, objs)
gl.glBindVertexArray(vao[0])
gl.glBindBuffer(0x8892, objs[0])                 #0x8892 is GL_ARRAY_BUFFER
gl.glBufferData(0x8892, 96, vertices, 0x88E4)    #0x88E4 is GL_STATIC_DRAW
gl.glBindBuffer(0x8893, objs[1])                 #0x8893
gl.glBufferData(0x8893, 24, elements, 0x88E4)
gl.glVertexAttribPointer(0, 3, 0x1406, 0, 12, 0) #0x1406 is GL_FLOAT
gl.glEnableVertexAttribArray(0)
#Shader init
result = POINTER(c_int)(c_int(0))
size = POINTER(c_int)(c_int(0))
vertshader = c_uint(gl.glCreateShader(0x8B31))        #0x8B31 is GL_VERTEX_SHADER
gl.glShaderSource(vertshader, 1, vertptr, 0)
gl.glCompileShader(vertshader)
gl.glGetShaderiv(vertshader, 0x8B81, result)          #0x8B81 is GL_COMPILE_STATUS
if result[0] == 0:
 gl.glGetShaderInfoLog(vertshader, 0xFF, size, buffer)
 libc.write(1, buffer, size[0])
 gl.glDeleteShader(vertshader)
 done()
fragshader = c_uint(gl.glCreateShader(0x8B30))
gl.glShaderSource(fragshader, 1, fragptr, 0)
gl.glCompileShader(fragshader)
gl.glGetShaderiv(fragshader,0x8B81, result)
if result[0] == 0:
 gl.glGetShaderInfoLog(fragshader, 0xFF, size, buffer)
 libc.write(1, buffer, size[0])
 gl.glDeleteShader(vertshader)
 gl.glDeleteShader(fragshader)
 done()
program = c_uint(gl.glCreateProgram())
gl.glAttachShader(program, vertshader)
gl.glAttachShader(program, fragshader)
gl.glLinkProgram(program)
gl.glGetProgramiv(program, 0x8B82, result) #0x8B82 is GL_LINK_STATUS
if result[0] == 0:
 gl.glGetProgramInfoLog(program, 0xFF, size, buffer)
 libc.write(1, buffer, size[0])
 gl.glDeleteShader(vertshader)
 gl.glDeleteShader(fragshader)
 gl.glDeleteProgram(program)
 done()
gl.glUseProgram(program)
gl.glDetachShader(program, vertshader)
gl.glDetachShader(program, fragshader)
gl.glDeleteShader(vertshader)
gl.glDeleteShader(fragshader)
unires = gl.glGetUniformLocation(program, c_char_p(bytes("res", "UTF-8")))
uniloc = gl.glGetUniformLocation(program, c_char_p(bytes("loc", "UTF-8")))
unicam = gl.glGetUniformLocation(program, c_char_p(bytes("cam", "UTF-8")))
oldwidth = 0
oldheight = 0
while glfw.glfwWindowShouldClose(window) == 0:
 width = POINTER(c_int)(c_int(0))
 height = POINTER(c_int)(c_int(0))
 glfw.glfwGetFramebufferSize(window, width, height) #Because of how the python FFI works it's far easier to poll than set up events
 if width[0] != oldwidth and height[0] != oldheight:
  oldwidth = width[0]
  oldheight = height[0]
  gl.glViewport(0, 0, width[0], height[0])
  gl.glUniform2f(unires, c_float(float(width[0])), c_float(float(height[0])))
 if glfw.glfwGetKey(window, 256) == 1:              #256 is escape
  done()
 if glfw.glfwGetKey(window,  32) == 1:              # 32 is Space
  loc[1] += 0.01
  gl.glUniform3fv(uniloc, 1, loc)
 if glfw.glfwGetKey(window,  65) == 1:              # 65 is A
  loc[0] += math.cos(cam[1]) * -0.01
  loc[2] += math.sin(cam[1]) * -0.01
  gl.glUniform3fv(uniloc, 1, loc)
 if glfw.glfwGetKey(window,  68) == 1:              # 68 is D
  loc[0] += math.cos(cam[1]) * 0.01
  loc[2] += math.sin(cam[1]) * 0.01
  gl.glUniform3fv(uniloc, 1, loc)
 if glfw.glfwGetKey(window,  83) == 1:              # 83 is S
  loc[0] += math.sin(cam[1]) * 0.01
  loc[2] += math.cos(cam[1]) * -0.01
  gl.glUniform3fv(uniloc, 1, loc)
 if glfw.glfwGetKey(window,  87) == 1:              # 87 is W
  loc[0] += math.sin(cam[1]) * -0.01
  loc[2] += math.cos(cam[1]) * 0.01
  gl.glUniform3fv(uniloc, 1, loc)
 if glfw.glfwGetKey(window, 262) == 1:              #262 is Right
  cam[1] -= 0.01
  gl.glUniform2fv(unicam, 1, cam)
 if glfw.glfwGetKey(window, 263) == 1:              #263 is Left
  cam[1] += 0.01
  gl.glUniform2fv(unicam, 1, cam)
 if glfw.glfwGetKey(window, 264) == 1:              #264 is Down
  cam[0] -= 0.01
  gl.glUniform2fv(unicam, 1, cam)
 if glfw.glfwGetKey(window, 265) == 1:              #265 is Up
  cam[0] += 0.01
  gl.glUniform2fv(unicam, 1, cam)
 if glfw.glfwGetKey(window, 340) == 1:              #340 is Left shift
  loc[1] -= 0.01
  gl.glUniform3fv(uniloc, 1, loc)
 gl.glClear(0x4000)                                 #0x4000 is GL_COLOR_BUFFER_BIT
 gl.glDrawElements(0x0001, 24, 0x1401, 0)           #0x0001 is GL_LINES, 0x1401 is GL_UNSIGNED_BYTE
 glfw.glfwSwapBuffers(window)
 glfw.glfwPollEvents()
 continue
done()