module callbacks ! Not sure how to include this in the main program section. Fortran doesn't seem to like routines outside of modules.
 use iso_c_binding
 implicit none
 interface
  subroutine              exit(err) bind(c,name='exit')
   import::c_int
   integer(c_int),value,intent(in)::err
   end subroutine exit
  subroutine              glfwTerminate() bind(c,name='glfwTerminate')
   end subroutine glfwTerminate
  subroutine              glUniform2f(uniform,width,height) bind(c,name='glUniform2f')
   import::c_int,c_float
   integer(c_int),value,intent(in)::uniform
   real(c_float),value,intent(in)::width,height
   end subroutine glUniform2f
  subroutine              glViewport(x,y,width,height) bind(c,name='glViewport')
   import::c_int
   integer(c_int),value,intent(in)::x,y,width,height
   end subroutine glViewport
  integer(c_int) function glGetError() bind(c,name='glGetError')
   import::c_int
   end function glGetError
  end interface
 integer(c_int)::unires
 contains
  subroutine resize(window,width,height) bind(c)
   integer(c_int),value,intent(in)::width,height
   type(c_ptr),value,intent(in)::window
   call glViewport(0,0,width,height)
   call glUniform2f(unires,real(width),real(height))
   end subroutine resize
  subroutine keypress(window,key,scancode,action,mods) bind(c)
   integer(c_int),value,intent(in)::key,scancode,action,mods
   type(c_ptr),value,intent(in)::window
   if (key==256) then
    call done
    end if
   end subroutine keypress
  subroutine done()
   call glfwTerminate
   call exit(0)
   end subroutine done
 end module callbacks
program renderer
 use callbacks
 use iso_c_binding
 implicit none
 interface
  integer(c_int) function write(fd,buffer,size) bind(c,name='write')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::fd,size
   type(c_ptr),value,intent(in)::buffer
   end function write
  integer(c_int) function glfwInit() bind(c,name='glfwInit')
   import::c_int
   end function glfwInit
  subroutine              glfwWindowHint(hint,value) bind(c,name='glfwWindowHint')
   import::c_int
   integer(c_int),value,intent(in)::hint,value
   end subroutine glfwWindowHint
  type(c_ptr) function    glfwCreateWindow(width,height,title,monitor,share) bind(c,name='glfwCreateWindow')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::width,height
   type(c_ptr),value,intent(in)::title,monitor,share
   end function glfwCreateWindow
  subroutine              glfwMakeContextCurrent(window) bind(c,name='glfwMakeContextCurrent')
   import::c_ptr
   type(c_ptr),value,intent(in)::window
   end subroutine glfwMakeContextCurrent
  type(c_funptr) function glfwSetWindowSizeCallback(window,callback) bind(c,name='glfwSetWindowSizeCallback')
   import::c_ptr,c_funptr
   type(c_ptr),value,intent(in)::window
   type(c_funptr),value,intent(in)::callback
   end function glfwSetWindowSizeCallback
  type(c_funptr) function glfwSetKeyCallback(window,callback) bind(c,name='glfwSetKeyCallback')
   import::c_ptr,c_funptr
   type(c_ptr),value,intent(in)::window
   type(c_funptr),value,intent(in)::callback
   end function glfwSetKeyCallback
  integer(c_int) function glfwGetKey(window,key) bind(c,name='glfwGetKey')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::key
   type(c_ptr),value,intent(in)::window
   end function glfwGetKey
  subroutine              glfwSwapBuffers(window) bind(c,name='glfwSwapBuffers')
   import::c_ptr
   type(c_ptr),value,intent(in)::window
   end subroutine glfwSwapBuffers
  subroutine              glfwPollEvents() bind(c,name='glfwPollEvents')
   end subroutine glfwPollEvents
  integer(c_int) function glfwWindowShouldClose(window) bind(c,name='glfwWindowShouldClose')
   import::c_int,c_ptr
   type(c_ptr),value,intent(in)::window
   end function glfwWindowShouldClose
  subroutine              glGenVertexArrays(count,array) bind(c,name='glGenVertexArrays')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::count
   type(c_ptr),value,intent(in)::array
   end subroutine glGenVertexArrays
  subroutine              glGenBuffers(count,array) bind(c,name='glGenBuffers')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::count
   type(c_ptr),value,intent(in)::array
   end subroutine glGenBuffers
  subroutine              glBindVertexArray(object) bind(c,name='glBindVertexArray')
   import::c_int
   integer(c_int),value,intent(in)::object
   end subroutine glBindVertexArray
  subroutine              glBindBuffer(type,object) bind(c,name='glBindBuffer')
   import::c_int
   integer(c_int),value,intent(in)::type,object
   end subroutine glBindBuffer
  subroutine              glBufferData(type,count,buffer,flags) bind(c,name='glBufferData')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::type,count,flags
   type(c_ptr),value,intent(in)::buffer
   end subroutine glBufferData
  subroutine              glVertexAttribPointer(index,size,type,normalized,stride,offset) bind(c,name='glVertexAttribPointer')
   import::c_int
   integer(c_int),value,intent(in)::index,size,type,normalized,stride,offset
   end subroutine glVertexAttribPointer
  subroutine              glEnableVertexAttribArray(index) bind(c,name='glEnableVertexAttribArray')
   import::c_int
   integer(c_int),value,intent(in)::index
   end subroutine glEnableVertexAttribArray
  integer(c_int) function glCreateShader(type) bind(c,name='glCreateShader')
   import::c_int
   integer(c_int),value,intent(in)::type
   end function glCreateShader
  subroutine              glShaderSource(shader,count,string,length) bind(c,name='glShaderSource')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::shader,count,length
   type(c_ptr),value,intent(in)::string
   end subroutine glShaderSource
  subroutine              glCompileShader(shader) bind(c,name='glCompileShader')
   import::c_int
   integer(c_int),value,intent(in)::shader
   end subroutine glCompileShader
  subroutine              glGetShaderiv(shader,type,result) bind(c,name='glGetShaderiv')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::shader,type
   type(c_ptr),value,intent(in)::result
   end subroutine glGetShaderiv
  subroutine              glGetShaderInfoLog(shader,bufsz,readsz,buffer) bind(c,name='glGetShaderInfoLog')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::shader,bufsz
   type(c_ptr),value,intent(in)::readsz,buffer
   end subroutine glGetShaderInfoLog
  subroutine              glDeleteShader(shader) bind(c,name='glDeleteShader')
   import::c_int
   integer(c_int),value,intent(in)::shader
   end subroutine glDeleteShader
  integer(c_int) function glCreateProgram() bind(c,name='glCreateProgram')
   import::c_int
   end function glCreateProgram
  subroutine              glAttachShader(program,shader) bind(c,name='glAttachShader')
   import::c_int
   integer(c_int),value,intent(in)::program,shader
   end subroutine glAttachShader
  subroutine              glLinkProgram(program) bind(c,name='glLinkProgram')
   import::c_int
   integer(c_int),value,intent(in)::program
   end subroutine glLinkProgram
  subroutine              glGetProgramiv(program,type,result) bind(c,name='glGetProgramiv')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::program,type
   type(c_ptr),value,intent(in)::result
   end subroutine glGetProgramiv
  subroutine              glGetProgramInfoLog(program,bufsz,readsz,buffer) bind(c,name='glGetProgramInfoLog')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::program,bufsz
   type(c_ptr),value,intent(in)::readsz,buffer
   end subroutine glGetProgramInfoLog
  subroutine              glDeleteProgram(program) bind(c,name='glDeleteProgram')
   import::c_int
   integer(c_int),value,intent(in)::program
   end subroutine glDeleteProgram
  subroutine              glUseProgram(program) bind(c,name='glUseProgram')
   import::c_int
   integer(c_int),value,intent(in)::program
   end subroutine glUseProgram
  subroutine              glDetachShader(program,shader) bind(c,name='glDetachShader')
   import::c_int
   integer(c_int),value,intent(in)::program,shader
   end subroutine glDetachShader
  integer(c_int) function glGetUniformLocation(program,name) bind(c,name='glGetUniformLocation')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::program
   type(c_ptr),value,intent(in)::name
   end function glGetUniformLocation
  subroutine              glUniform2fv(uniform,count,values) bind(c,name='glUniform2fv')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::uniform,count
   type(c_ptr),value,intent(in)::values
   end subroutine glUniform2fv
  subroutine              glUniform3fv(uniform,count,values) bind(c,name='glUniform3fv')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::uniform,count
   type(c_ptr),value,intent(in)::values
   end subroutine glUniform3fv
  subroutine              glClear(flags) bind(c,name='glClear')
   import::c_int
   integer(c_int),value,intent(in)::flags
   end subroutine glClear
  subroutine              glDrawElements(type,count,elemtype,offset) bind(c,name='glDrawElements')
   import::c_int
   integer(c_int),value,intent(in)::type,count,elemtype,offset
   end subroutine glDrawElements
  end interface
 integer(c_int)::vert,frag,program,uniloc,unicam,i,keys(0:9)=[32,65,68,83,87,262,263,264,265,340]
 integer(c_int),target::size,result,vao,bufobjs(0:1)
 integer(c_char)::flags(0:9)=[b'101',b'00000',b'01100',b'11000',b'10100',b'1010',b'1110',b'0010',b'0110',b'001']
 integer(c_char),target::elements(0:23)=[&
  0,1,&
  1,2,&
  2,3,&
  3,0,&
  4,5,&
  5,6,&
  6,7,&
  7,4,&
  0,4,&
  1,5,&
  2,6,&
  3,7]
 integer(c_char),target::buffer(0:255)
 real(c_float)::np0,np1
 real(c_float),target::loc(0:2)=[0,0,0],cam(0:1)=[0,0]
 real(c_float),target::vertices(0:23)=[&
  -0.5,-0.5,-0.5,&
  -0.5,-0.5,+0.5,&
  +0.5,-0.5,+0.5,&
  +0.5,-0.5,-0.5,&
  -0.5,+0.5,-0.5,&
  -0.5,+0.5,+0.5,&
  +0.5,+0.5,+0.5,&
  +0.5,+0.5,-0.5] 
 type(c_ptr)::window
 type(c_ptr),target::vertstrptr,fragstrptr
 type(c_funptr)::oldfunc
 character(len=11),target::scumpert="scumpert!!"//char(0)
 character(len=600),target::vertstr="&
  #version 450"//char(10)//&
  "layout(location=0) in vec3 pos;&
  uniform vec2 res;&
  uniform vec3 loc;&
  uniform vec2 cam;&
  void main(){&
    gl_Position=vec4(pos,1.0);&
    gl_Position.xyz-=loc;&
    float z=gl_Position.z;&
    gl_Position.z=gl_Position.z*cos(cam.y)-gl_Position.x*sin(cam.y);&
    gl_Position.x=z*sin(cam.y)+gl_Position.x*cos(cam.y);&
    float y=gl_Position.y;&
    gl_Position.y=gl_Position.y*cos(cam.x)-gl_Position.z*sin(cam.x);&
    gl_Position.z=y*sin(cam.x)+gl_Position.z*cos(cam.x);&
    gl_Position.x*=(res[1]/res[0]);&
    gl_Position.w=gl_Position.z;}"//char(0)
 character(len=100),target::fragstr="&
  #version 450"//char(10)//&
  "out vec4 color;&
  void main(){color=vec4(1,0,0,1);}"//char(0)
 character(len=4),target::resstr='res'//char(0),locstr='loc'//char(0),camstr='cam'//char(0)
 vertstrptr=c_loc(vertstr)
 fragstrptr=c_loc(fragstr)
 result=glfwInit()
 call glfwWindowHint(int(z'22002'),4)
 call glfwWindowHint(int(z'22003'),5)
 call glfwWindowHint(int(z'22006'),1);
 call glfwWindowHint(int(z'22008'),int(z'32001'));
 window=glfwCreateWindow(1600,900,c_loc(scumpert),c_null_ptr,c_null_ptr)
 call glfwMakeContextCurrent(window)
 oldfunc=glfwSetWindowSizeCallback(window,c_funloc(resize))
 oldfunc=glfwSetKeyCallback(window,c_funloc(keypress))
 call glGenVertexArrays(1,c_loc(vao))
 call glGenBuffers(2,c_loc(bufobjs))
 call glBindVertexArray(vao);
 call glBindBuffer(int(z'8892'),bufobjs(0))
 call glBufferData(int(z'8892'),96,c_loc(vertices),int(z'88E4'))
 call glBindBuffer(int(z'8893'),bufobjs(1))
 call glBufferData(int(z'8893'),24,c_loc(elements),int(z'88E4'))
 call glVertexAttribPointer(0,3,int(z'1406'),0,12,0)
 call glEnableVertexAttribArray(0)
 vert=glCreateShader(int(z'8B31'))
 call glShaderSource(vert,1,c_loc(vertstrptr),0)
 call glCompileShader(vert)
 call glGetShaderiv(vert,int(z'8B81'),c_loc(result))
 if(result==0) then
  call glGetShaderInfoLog(vert,int(z'FF'),c_loc(size),c_loc(buffer))
  size=write(1,c_loc(buffer),size)
  call glDeleteShader(vert)
  call done
  end if
 frag=glCreateShader(int(z'8B30'))
 call glShaderSource(frag,1,c_loc(fragstrptr),0)
 call glCompileShader(frag)
 call glGetShaderiv(frag,int(z'8B81'),c_loc(result))
 if(result==0) then
  call glGetShaderInfoLog(frag,int(z'FF'),c_loc(size),c_loc(buffer))
  size=write(1,c_loc(buffer),size)
  call glDeleteShader(vert)
  call glDeleteShader(frag)
  call done
  end if
 program=glCreateProgram()
 call glAttachShader(program,vert)
 call glAttachShader(program,frag)
 call glLinkProgram(program)
 call glGetProgramiv(program,int(z'8B82'),c_loc(result))
 if(result==0) then
  call glGetProgramInfoLog(program,int(z'FF'),c_loc(size),c_loc(buffer))
  size=write(1,c_loc(buffer),size)
  call glDeleteShader(vert)
  call glDeleteShader(frag)
  call glDeleteProgram(program)
  call done
  end if
 call glUseProgram(program)
 call glDetachShader(program,vert)
 call glDetachShader(program,frag)
 call glDeleteShader(vert)
 call glDeleteShader(frag)
 unires=glGetUniformLocation(program,c_loc(resstr))
 uniloc=glGetUniformLocation(program,c_loc(locstr))
 unicam=glGetUniformLocation(program,c_loc(camstr))
 do while(glfwWindowShouldClose(window)==0)
  do i=0,9
   if(glfwGetKey(window,keys(i))==1) then
    if(iand(flags(i),b'11')==0) then
     np0=-0.001
     np1=-0.001
     if(iand(flags(i),b'00100')==0) then
      np0=0.001
      end if
     if(iand(flags(i),b'01000')==0) then
      np1=0.001
      end if
     if(iand(flags(i),b'10000')==0) then
      loc(0)=loc(0)-cos(cam(1))*np0
      loc(2)=loc(2)-sin(cam(1))*np1
     else
      loc(0)=loc(0)+sin(cam(1))*np0
      loc(2)=loc(2)+cos(cam(1))*np1
      end if
     call glUniform3fv(uniloc,1,c_loc(loc))
    else if(iand(flags(i),b'10')==0) then
     if(keys(i)==340) then
      loc(1)=loc(1)-0.001
     else
      loc(1)=loc(1)+0.001
      end if
     call glUniform3fv(uniloc,1,c_loc(loc))
    else
     np0=0.001
     if(iand(flags(i),b'0100')==0) then
      np0=-0.001
      end if
     if(iand(flags(i),b'1000')==0) then
      cam(0)=cam(0)+np0
     else
      cam(1)=cam(1)+np0
      end if
     call glUniform2fv(unicam,1,c_loc(cam))
     end if
    end if
   end do
  call glClear(int(z'4000'))
  call glDrawElements(int(z'1'),24,int(z'1401'),0)
  call glfwSwapBuffers(window)
  call glfwPollEvents
  end do
 end program