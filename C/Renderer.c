//Externs -lGL -lglfw -lm
 #define uint unsigned int
 extern int    write(int fd,char* buffer,int count);
 extern void   exit(int error);
 extern double sin(double val);
 extern double cos(double val);
 extern int    glfwInit(void);
 extern void   glfwTerminate(void);
 extern void   glfwWindowHint(int hint,int value);
 extern void*  glfwCreateWindow(int width,int height,void* title,void* monitor,void* share);
 extern void   glfwMakeContextCurrent(void* window);
 extern void*  glfwSetWindowSizeCallback(void* window,void* callback);
 extern void   glfwSwapBuffers(void* window);
 extern void   glfwPollEvents(void);
 extern int    glfwWindowShouldClose(void* window);
 extern int    glfwGetKey(void* window,uint key);
 extern void*  glfwSetKeyCallback(void* window,void* callback);
 extern void   glGenVertexArrays(uint count,void* arrays);
 extern void   glGenBuffers(uint count,void* buffers);
 extern void   glBindVertexArray(uint array);
 extern void   glBindBuffer(uint target,uint buf);
 extern void   glBufferData(uint target,uint size,void* data,uint usage);
 extern void   glVertexAttribPointer(uint index,uint size,uint type,int normalized,uint stride,void* pointer);
 extern void   glEnableVertexAttribArray(uint index);
 extern uint   glCreateShader(uint type);
 extern void   glShaderSource(uint shader,uint count,void* sources,void* lengths); //String is a double pointer to a string
 extern void   glCompileShader(uint shader);
 extern void   glGetShaderiv(uint shader,uint param,void* returnval);
 extern void   glGetShaderInfoLog(uint shader,uint bufsize,void* returnsize,void* buf);
 extern void   glDeleteShader(uint shader);
 extern uint   glCreateProgram(void);
 extern void   glAttachShader(uint program,uint shader);
 extern void   glLinkProgram(uint program);
 extern void   glGetProgramiv(uint program,uint param,void* returnval);
 extern void   glGetProgramInfoLog(uint program,uint bufsize,void* returnsize,void* buf);
 extern void   glDetachShader(uint program,uint shader);
 extern void   glDeleteProgram(uint program);
 extern void   glUseProgram(uint program);
 extern uint   glGetUniformLocation(uint program,void* name);
 extern void   glClear(uint flags);
 extern void   glDrawElements(uint drawtype,uint count,uint elemtype,uint offset);
 extern void   glUniform2f(uint uniform,float v1,float v2);
 extern void   glUniform2fv(uint uniform,uint count,void* values);
 extern void   glUniform3fv(uint uniform,uint count,void* values);
 extern void   glViewport(uint x,uint y,uint width,uint height);
 extern uint   glGetError(void);
const char* vertshaderstr="#version 450\nlayout (location=0) in vec3 pos;uniform vec2 res;uniform vec3 loc;uniform vec2 cam;void main(){gl_Position = vec4(pos,1.0);gl_Position.xyz -= loc;float z = gl_Position.z;gl_Position.z = gl_Position.z * cos(cam.y) - gl_Position.x * sin(cam.y);gl_Position.x = z * sin(cam.y)+gl_Position.x * cos(cam.y);float y = gl_Position.y;gl_Position.y = gl_Position.y * cos(cam.x) - gl_Position.z * sin(cam.x);gl_Position.z = y * sin(cam.x) + gl_Position.z * cos(cam.x);gl_Position.x *= (res[1]/res[0]);gl_Position.w = gl_Position.z;}";
const char* fragshaderstr="#version 450\nout vec4 color;void main(){color = vec4(1,0,0,1);}";
void  resize(),keypress(),done();
void* window;
uint  objs[2],vao,program,unires,uniloc,unicam;
float loc[3],cam[2];
float vertices[24]={ 
 -0.5,-0.5,-0.5,
 -0.5,-0.5,+0.5,
 +0.5,-0.5,+0.5,
 +0.5,-0.5,-0.5,
 -0.5,+0.5,-0.5,
 -0.5,+0.5,+0.5,
 +0.5,+0.5,+0.5,
 +0.5,+0.5,-0.5};
char  elements[24]={
 0,1,
 1,2,
 2,3,
 3,0,
 4,5,
 5,6,
 6,7,
 7,4,
 0,4,
 1,5,
 2,6,
 3,7};
char  buffer[256];
short keys[]={32,65,68,83,87,262,263,264,265,340};
char  flags[]={0b101,0b00000,0b01100,0b11000,0b10100,0b1010,0b1110,0b0010,0b0110,0b001};
int main(){
 glfwInit();
 glfwWindowHint(0x22002,4);
 glfwWindowHint(0x22003,5);
 glfwWindowHint(0x22006,1); //Can't remember why I was setting forward compat and core profile. Fixed some bug maybe? Can this be removed?
 glfwWindowHint(0x22008,0x32001);
 window=glfwCreateWindow(1600,900,"Scumpert!!",0,0);
 glfwMakeContextCurrent(window);
 glfwSetWindowSizeCallback(window,resize);
 glfwSetKeyCallback(window,keypress);
 glGenVertexArrays(1,&vao);
 glGenBuffers(2,objs);
 glBindVertexArray(vao);
 glBindBuffer(0x8892,objs[0]);
 glBufferData(0x8892,96,vertices,0x88E4);
 glBindBuffer(0x8893,objs[1]);
 glBufferData(0x8893,24,elements,0x88E4);
 glVertexAttribPointer(0,3,0x1406,0,12,0);
 glEnableVertexAttribArray(0);
 int result,size;
 uint vertshader=glCreateShader(0x8B31);
 glShaderSource(vertshader,1,&vertshaderstr,0);
 glCompileShader(vertshader);
 glGetShaderiv(vertshader,0x8B81,&result);
 if(result==0){
  glGetShaderInfoLog(vertshader,0xFF,&size,buffer);
  write(1,buffer,size);
  glDeleteShader(vertshader);}
 uint fragshader = glCreateShader(0x8B30);
 glShaderSource(fragshader,1,&fragshaderstr,0);
 glCompileShader(fragshader);
 glGetShaderiv(fragshader,0x8B81,&result);
 if(result==0){
  glGetShaderInfoLog(fragshader,0xFF,&size,buffer);
  write(1,buffer,size);
  glDeleteShader(vertshader);
  glDeleteShader(fragshader);}
 program = glCreateProgram();
 glAttachShader(program,vertshader);
 glAttachShader(program,fragshader);
 glLinkProgram(program);
 glGetProgramiv(program,0x8B82,&result);
 if(result==0){
  glGetProgramInfoLog(program,0xFF,&size,buffer);
  write(1,buffer,size);
  glDeleteShader(vertshader);
  glDeleteShader(fragshader);
  glDeleteProgram(program);}
 glUseProgram(program);
 glDetachShader(program,vertshader);
 glDetachShader(program,fragshader);
 glDeleteShader(vertshader);
 glDeleteShader(fragshader);
 unires=glGetUniformLocation(program,"res");
 uniloc=glGetUniformLocation(program,"loc");
 unicam=glGetUniformLocation(program,"cam");
 while(!glfwWindowShouldClose(window)){
  for(int i=0;i<10;i++){
   if(glfwGetKey(window,keys[i])){  
    if((flags[i]&0b11)==0){
     float negpos0=-0.001;
     float negpos1=-0.001;
     if((flags[i]&0b00100)==0){negpos0=+0.001;}
     if((flags[i]&0b01000)==0){negpos1=+0.001;}
     if((flags[i]&0b10000)==0){loc[0]-=cos(cam[1])*negpos0;loc[2]-=sin(cam[1])*negpos1;} 
     else {loc[0]+=sin(cam[1])*negpos0;loc[2]+=cos(cam[1])*negpos1;}
     glUniform3fv(uniloc,1,loc);}
    else if((flags[i]&0b10)==0){
     if(keys[i]==340){loc[1]-=0.001;}else{loc[1]+=0.001;}
     glUniform3fv(uniloc,1,loc);}
    else{
     float negpos=+0.001;
     if((flags[i]&0b0100)==0){negpos=-0.001;}
     if((flags[i]&0b1000)==0){cam[0]+=negpos;}else{cam[1]+=negpos;}
     glUniform2fv(unicam,1,cam);}}}
  glClear(0x4000);
  glDrawElements(0x0001,24,0x1401,0);
  glfwSwapBuffers(window);
  glfwPollEvents();}
  done();}
void resize(void* win,int width,int height){glViewport(0,0,width,height);glUniform2f(unires,(float)width,(float)height);}
void keypress(void* win,int key,int scancode,int action,int mods){if(key==256){done();}}
void done(){glDeleteProgram(program);glfwTerminate();exit(0);}