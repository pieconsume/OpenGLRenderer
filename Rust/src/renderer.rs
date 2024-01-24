use libc::{c_int, c_uint, c_float, c_long};

#[link(name="c")]
extern
{
 fn write(fd: c_int, buffer: *const u8, count: c_int);
}
#[link(name="glfw")]
extern
{
  fn glfwInit() -> c_int;
  fn glfwWindowHint(hint: c_uint, value: c_uint) -> c_int;
  fn glfwCreateWindow(width: c_int, height: c_int, name: *const u8, monitor: c_long, share: c_long) -> c_long;
  fn glfwMakeContextCurrent(window: c_long);
  fn glfwWindowShouldClose(window: c_long) -> c_int;
  fn glfwGetFramebufferSize(window: c_long, width: *const i32, height: *const i32);
  fn glfwGetKey(window: c_long, character: c_uint) -> c_int;
  fn glfwSwapBuffers(window: c_long);
  fn glfwPollEvents();
  fn glfwTerminate();
}
#[link(name="GL")]
extern
{
 fn glGenVertexArrays(count: c_int, output: *const i32);
 fn glGenBuffers(count: c_int, output: *const i32);
 fn glBindVertexArray(vao: c_int);
 fn glBindBuffer(target: c_uint, bufobj: c_int);
 fn glBufferData(target: c_uint, size: c_int, buffer: *const u8, usage: c_uint);
 fn glVertexAttribPointer(index: c_int, size: c_int, datatype: c_uint, normalized: c_int, stride: c_int, offset: c_long);
 fn glEnableVertexAttribArray(index: c_int);
 fn glCreateShader(datatype: c_uint) -> c_int;
 fn glShaderSource(shader: c_int, count: c_int, strings: *const *const u8, lengths: c_long);
 fn glCompileShader(shader: c_int);
 fn glGetShaderiv(shader: c_int, target: c_uint, result: *const c_int);
 fn glGetShaderInfoLog(shader: c_int, bufsize: c_int, outsize: *const c_int, buffer: *const u8);
 fn glDeleteShader(shader: c_int);
 fn glCreateProgram() -> c_int;
 fn glAttachShader(program: c_int, shader: c_int);
 fn glLinkProgram(program: c_int);
 fn glGetProgramiv(program: c_int, target: c_uint, result: *const c_int);
 fn glGetProgramInfoLog(program: c_int, bufsize: c_int, outsize: *const c_int, buffer: *const u8);
 fn glDeleteProgram(program: c_int);
 fn glUseProgram(program: c_int);
 fn glDetachShader(program: c_int, shader: c_int);
 fn glGetUniformLocation(program: c_int, name: *const u8) -> c_int;
 fn glViewport(x: c_int, y: c_int, width: c_int, height: c_int);
 fn glUniform2f(uniform: c_int, width: c_float, height: c_float);
 fn glUniform2fv(uniform: c_int, count: c_int, value: *const f32);
 fn glUniform3fv(uniform: c_int, count: c_int, value: *const f32);
 fn glClear(flags: c_uint);
 fn glDrawElements(drawtype: c_uint, count: c_int, elementtype: c_uint, offset: c_int);
 fn glGetError() -> c_int;
}

fn main()
{
 let buffer:[u8;256] = [0;256];
 let vao:[i32;1] = [0];
 let vbo:[i32;2] = [0, 0];
 let vertices:[f32;24] = [ -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5,0.5, 0.5, 0.5, 0.5, 0.5, -0.5 ];
 let elements:[u8;24] = [ 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 ];
 let vertshaderstr = "#version 450\nlayout (location = 0) in vec3 pos;uniform vec2 res;uniform vec3 loc;uniform vec2 cam;void main() {gl_Position = vec4(pos, 1.0);gl_Position.xyz -= loc;float z = gl_Position.z;gl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y);gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y);float y = gl_Position.y;gl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x);gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x);gl_Position.x *=  (res[1]/res[0]);gl_Position.w = gl_Position.z;}\0";
 let fragshaderstr = "#version 450\nout vec4 color;void main() { color = vec4(1, 0, 0, 1);}\0";
 let mut loc:[f32;3] = [ 0.0, 0.0, 0.0 ];
 let mut res:[f32;2] = [ 0.0, 0.0 ];
 let mut cam:[f32;2] = [ 0.0, 0.0 ];
 unsafe
 {
  //Window init
   glfwInit();
   glfwWindowHint(0x22002, 4);
   glfwWindowHint(0x22003, 5);
   let window = glfwCreateWindow(1600, 900, "scumpert!!!\0".as_ptr() as *const u8, 0, 0);
   glfwMakeContextCurrent(window);
  //Buffer init
   glGenVertexArrays(1, vao.as_ptr());
   glGenBuffers(2, vbo.as_ptr());
   glBindVertexArray(vao[0]);
   glBindBuffer(0x8892, vbo[0]);                                     //0x8892 is GL_ARRAY_BUFFER
   glBufferData(0x8892, 96, vertices.as_ptr() as *const u8, 0x88E4); //0x88E4 is GL_STATIC_DRAW
   glBindBuffer(0x8893, vbo[1]);                                     //0x8893 is GL_ELEMENT_BUFFER
   glBufferData(0x8893, 24, elements.as_ptr(), 0x88E4);
   glVertexAttribPointer(0, 3, 0x1406, 0, 12, 0);                    //0x1406 is GL_FLOAT
   glEnableVertexAttribArray(0);
  //Shader init
   let result: c_int = 0;
   let size: c_int = 0;
   let vertshader = glCreateShader(0x8B31);    //0x8B31 is GL_VERTEX_SHADER
   glShaderSource(vertshader, 1, &vertshaderstr.as_ptr(), 0);
   glCompileShader(vertshader);
   glGetShaderiv(vertshader, 0x8B81, &result); //0x8B81 is GL_COMPILE_STATUS
   if result==0 { glGetShaderInfoLog(vertshader, 0xFF, &size, buffer.as_ptr()); write(1, buffer.as_ptr(), size); glDeleteShader(vertshader); done(); }
   let fragshader = glCreateShader(0x8B30);    //0x8B30 is GL_FRAGMENT SHADER
   glShaderSource(fragshader, 1, &fragshaderstr.as_ptr(), 0);
   glCompileShader(fragshader);
   glGetShaderiv(fragshader, 0x8B81, &result);
   if result==0 { glGetShaderInfoLog(fragshader, 0xFF, &size, buffer.as_ptr()); write(1, buffer.as_ptr(), size); glDeleteShader(vertshader); glDeleteShader(fragshader); done(); }
   let program = glCreateProgram();
   glAttachShader(program, vertshader);
   glAttachShader(program, fragshader);
   glLinkProgram(program);
   glGetProgramiv(program, 0x8B82, &result);   //0x8B82 is GL_LINK_STATUS
   if result==0 { glGetProgramInfoLog(program, 0xFF, &size, buffer.as_ptr()); write(1, buffer.as_ptr(), size); glDeleteShader(vertshader); glDeleteShader(fragshader); glDeleteProgram(program); done(); }
   glUseProgram(program);
   glDetachShader(program, vertshader);
   glDetachShader(program, fragshader);
   glDeleteShader(vertshader);
   glDeleteShader(fragshader);
   let unires = glGetUniformLocation(program, "res\0".as_ptr());
   let uniloc = glGetUniformLocation(program, "loc\0".as_ptr());
   let unicam = glGetUniformLocation(program, "cam\0".as_ptr());
   let mut oldwidth:  c_int =  0;
   let mut oldheight: c_int =  0;
   let mut width:     c_int =  0;
   let mut height:    c_int =  0;
  while glfwWindowShouldClose(window)==0
  {
   glfwGetFramebufferSize(window, &width, &height);
   if width!=oldwidth && height!=oldheight { oldwidth = width; oldheight = height; glViewport(0, 0, width, height); glUniform2f(unires, width as f32, height as f32); }
   if glfwGetKey(window, 256)==1 { done(); }
   if glfwGetKey(window,  32)==1 { loc[1] += 0.01; glUniform3fv(uniloc, 1, loc.as_ptr()); }                                                 //Space
   if glfwGetKey(window,  65)==1 { loc[0] += cam[1].cos() * -0.01; loc[2] += cam[1].sin() * -0.01; glUniform3fv(uniloc, 1, loc.as_ptr()); } //A
   if glfwGetKey(window,  68)==1 { loc[0] += cam[1].cos() *  0.01; loc[2] += cam[1].sin() *  0.01; glUniform3fv(uniloc, 1, loc.as_ptr()); } //D
   if glfwGetKey(window,  83)==1 { loc[0] += cam[1].sin() *  0.01; loc[2] += cam[1].cos() * -0.01; glUniform3fv(uniloc, 1, loc.as_ptr()); } //S
   if glfwGetKey(window,  87)==1 { loc[0] += cam[1].sin() * -0.01; loc[2] += cam[1].cos() *  0.01; glUniform3fv(uniloc, 1, loc.as_ptr()); } //W
   if glfwGetKey(window, 262)==1 { cam[1] -= 0.01; glUniform2fv(unicam, 1, cam.as_ptr()); }                                                 //Right
   if glfwGetKey(window, 263)==1 { cam[1] += 0.01; glUniform2fv(unicam, 1, cam.as_ptr()); }                                                 //Left
   if glfwGetKey(window, 264)==1 { cam[0] -= 0.01; glUniform2fv(unicam, 1, cam.as_ptr()); }                                                 //Down
   if glfwGetKey(window, 265)==1 { cam[0] += 0.01; glUniform2fv(unicam, 1, cam.as_ptr()); }                                                 //Up
   if glfwGetKey(window, 340)==1 { loc[1] -= 0.01; glUniform3fv(uniloc, 1, loc.as_ptr()); }                                                 //LShift
   glClear(0x4000);                       //0x4000 is GL_COLOR_BUFFER_BIT
   glDrawElements(0x0001, 24, 0x1401, 0); //0x0001 is GL_LINES, 0x1401 is GL_UNSIGNED_BYTE
   glfwSwapBuffers(window);
   glfwPollEvents();
  }
 }
}

fn done()
{
 unsafe
 {
  glfwTerminate();
  std::process::exit(0);
 }
}