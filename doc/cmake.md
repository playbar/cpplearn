#CMAKE的使用

一、      基本使用
安装：下载二进制包后可直接解压使用

从源码安装则执行命令：./bootstrap; make; make install——尝试执行bootstrap失败

使用：cmake dir_path，生成工程文件或makefile文件

二、      概念
out-of-source build，与in-source build相对，即将编译输出文件与源文件放到不同目录中；

三、      基本结构
1，依赖CMakeLists.txt文件，项目主目标一个，主目录中可指定包含的子目录；

2，在项目CMakeLists.txt中使用project指定项目名称，add_subdirectory添加子目录

3，子目录CMakeLists.txt将从父目录CMakeLists.txt继承设置（TBD，待检验）

四、      语法
1.       #注释

2.       变量：使用set命令显式定义及赋值，在非if语句中，使用${}引用，if中直接使用变量名引用；后续的set命令会清理变量原来的值；

3.       command (args ...)  #命令不分大小写，参数使用空格分隔，使用双引号引起参数中空格

4.       set(var a;b;c) <=> set(var a b c)  #定义变量var并赋值为a;b;c这样一个string list

5.       Add_executable(${var}) <=> Add_executable(a b c)   #变量使用${xxx}引用

6.       条件语句：

if(var) #var 非empty 0 N No OFF FALSE... #非运算使用NOT

       …

else()/elseif() … endif(var)

7.       循环语句

Set(VAR a b c)

Foreach(f ${VAR})       …Endforeach(f)

8.       循环语句

WHILE() … ENDWHILE()

五、      内部变量
CMAKE_C_COMPILER：指定C编译器

CMAKE_CXX_COMPILER：

CMAKE_C_FLAGS：编译C文件时的选项，如-g；也可以通过add_definitions添加编译选项

EXECUTABLE_OUTPUT_PATH：可执行文件的存放路径

LIBRARY_OUTPUT_PATH：库文件路径

CMAKE_BUILD_TYPE:：build 类型(Debug, Release, ...)，CMAKE_BUILD_TYPE=Debug

BUILD_SHARED_LIBS：Switch between shared and static libraries

内置变量的使用：

>> 在CMakeLists.txt中指定，使用set

>> cmake命令中使用，如cmake -DBUILD_SHARED_LIBS=OFF

六、      命令
project (HELLO)   #指定项目名称，生成的VC项目的名称；

>>使用${HELLO_SOURCE_DIR}表示项目根目录

include_directories：指定头文件的搜索路径，相当于指定gcc的-I参数

>> include_directories (${HELLO_SOURCE_DIR}/Hello)  #增加Hello为include目录

link_directories：动态链接库或静态链接库的搜索路径，相当于gcc的-L参数

       >> link_directories (${HELLO_BINARY_DIR}/Hello)     #增加Hello为link目录

add_subdirectory：包含子目录

       >> add_subdirectory (Hello)

add_executable：编译可执行程序，指定编译，好像也可以添加.o文件

       >> add_executable (helloDemo demo.cxx demo_b.cxx)   #将cxx编译成可执行文件——

add_definitions：添加编译参数

>> add_definitions(-DDEBUG)将在gcc命令行添加DEBUG宏定义；

>> add_definitions( “-Wall -ansi –pedantic –g”)

target_link_libraries：添加链接库,相同于指定-l参数

>> target_link_libraries(demo Hello) #将可执行文件与Hello连接成最终文件demo

add_library:

>> add_library(Hello hello.cxx)  #将hello.cxx编译成静态库如libHello.a

add_custom_target:

message( status|fatal_error, “message”):

set_target_properties( ... ): lots of properties... OUTPUT_NAME, VERSION, ....

link_libraries( lib1 lib2 ...): All targets link with the same set of libs

七、      说明
1，CMAKE生成的makefile能够处理好.h文件更改时只编译需要的cpp文件；

八、      FAQ
1）  怎样获得一个目录下的所有源文件
>> aux_source_directory(<dir> <variable>)

>> 将dir中所有源文件（不包括头文件）保存到变量variable中，然后可以add_executable (ss7gw ${variable})这样使用。

2）  怎样指定项目编译目标
>>  project命令指定

3）  怎样添加动态库和静态库
>> target_link_libraries命令添加即可

4）  怎样在执行CMAKE时打印消息
>> message([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)

>> 注意大小写

5）  怎样指定头文件与库文件路径
>> include_directories与link_directories

>>可以多次调用以设置多个路径

>> link_directories仅对其后面的targets起作用

6）  怎样区分debug、release版本
>>建立debug/release两目录，分别在其中执行cmake -DCMAKE_BUILD_TYPE=Debug（或Release），需要编译不同版本时进入不同目录执行make即可；

Debug版会使用参数-g；Release版使用-O3 –DNDEBUG

>> 另一种设置方法——例如DEBUG版设置编译参数DDEBUG

IF(DEBUG_mode)

    add_definitions(-DDEBUG)

ENDIF()

在执行cmake时增加参数即可，例如cmake -D DEBUG_mode=ON

7）  怎样设置条件编译
例如debug版设置编译选项DEBUG，并且更改不应改变CMakelist.txt

>> 使用option command，eg：

option(DEBUG_mode "ON for debug or OFF for release" ON)

IF(DEBUG_mode)

    add_definitions(-DDEBUG)

ENDIF()

>> 使其生效的方法：首先cmake生成makefile，然后make edit_cache编辑编译选项；Linux下会打开一个文本框，可以更改，该完后再make生成目标文件——emacs不支持make edit_cache；

>> 局限：这种方法不能直接设置生成的makefile，而是必须使用命令在make前设置参数；对于debug、release版本，相当于需要两个目录，分别先cmake一次，然后分别make edit_cache一次；

>> 期望的效果：在执行cmake时直接通过参数指定一个开关项，生成相应的makefile——可以这样做，例如cmake –DDEBUGVERSION=ON

8）  怎样添加编译宏定义
>> 使用add_definitions命令，见命令部分说明

9）  怎样添加编译依赖项
用于确保编译目标项目前依赖项必须先构建好

>>add_dependencies

10）        怎样指定目标文件目录
>> 建立一个新的目录，在该目录中执行cmake生成Makefile文件，这样编译结果会保存在该目录——类似

>> SET_TARGET_PROPERTIES(ss7gw PROPERTIES

                      RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")

11）        很多文件夹，难道需要把每个文件夹编译成一个库文件？
>> 可以不在子目录中使用CMakeList.txt，直接在上层目录中指定子目录

12）        怎样设定依赖的cmake版本
>>cmake_minimum_required(VERSION 2.6)

13）        相对路径怎么指定
>> ${projectname_SOURCE_DIR}表示根源文件目录，${ projectname _BINARY_DIR}表示根二进制文件目录？

14）        怎样设置编译中间文件的目录
>> TBD

15）        怎样在IF语句中使用字串或数字比较
>>数字比较LESS、GREATER、EQUAL，字串比STRLESS、STRGREATER、STREQUAL，

>> Eg：

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

set(AAA abc)

IF(AAA STREQUAL abc)

    message(STATUS "true")   #应该打印true

ENDIF()

16）        更改h文件时是否只编译必须的cpp文件
>> 是

17）        机器上安装了VC7和VC8，CMAKE会自动搜索编译器，但是怎样指定某个版本？
>> TBD

18）        怎样根据OS指定编译选项
>> IF( APPLE ); IF( UNIX ); IF( WIN32 )

19）        能否自动执行某些编译前、后命令？
>> 可以，TBD

20）        怎样打印make的输出
make VERBOSE=1

一,cmake 变量引用的方式:
前面我们已经提到了,使用${}进行变量的引用。在 IF 等语句中,是直接使用变量名而不通过${}取值
二,cmake 自定义变量的方式:
主要有隐式定义和显式定义两种,前面举了一个隐式定义的例子,就是 PROJECT 指令,他会隐式的定义<projectname>_BINARY_DIR 和<projectname>_SOURCE_DIR 两个变量。
显式定义的例子我们前面也提到了,使用 SET 指令,就可以构建一个自定义变量了。
比如:
SET(HELLO_SRC main.SOURCE_PATHc),就 PROJECT_BINARY_DIR 可以通过${HELLO_SRC}来引用这个自定义变量了.

三,cmake 常用变量:
1,CMAKE_BINARY_DIR
  PROJECT_BINARY_DIR
 <projectname>_BINARY_DIR
这三个变量指代的内容是一致的,如果是 in source 编译,指得就是工程顶层目录,如果是 out-of-source 编译,指的是工程编译发生的目录。PROJECT_BINARY_DIR 跟其他指令稍有区别,现在,你可以理解为他们是一致的。
2,CMAKE_SOURCE_DIR
   PROJECT_SOURCE_DIR
   <projectname>_SOURCE_DIR
这三个变量指代的内容是一致的,不论采用何种编译方式,都是工程顶层目录。
也就是在 in source 编译时,他跟 CMAKE_BINARY_DIR 等变量一致。
PROJECT_SOURCE_DIR 跟其他指令稍有区别,现在,你可以理解为他们是一致的。

3,CMAKE_CURRENT_SOURCE_DIR
指的是当前处理的 CMakeLists.txt 所在的路径,比如上面我们提到的 src 子目录。

4,CMAKE_CURRRENT_BINARY_DIR
如果是 in-source 编译,它跟 CMAKE_CURRENT_SOURCE_DIR 一致,如果是 out-of-source 编译,他指的是 target 编译目录。
使用我们上面提到的 ADD_SUBDIRECTORY(src bin)可以更改这个变量的值。
使用 SET(EXECUTABLE_OUTPUT_PATH <新路径>)并不会对这个变量造成影响,它仅仅修改了最终目标文件存放的路径。

5,CMAKE_CURRENT_LIST_FILE
输出调用这个变量的 CMakeLists.txt 的完整路径



6,CMAKE_CURRENT_LIST_LINE
输出这个变量所在的行



7,CMAKE_MODULE_PATH
这个变量用来定义自己的 cmake 模块所在的路径。如果你的工程比较复杂,有可能会自己编写一些 cmake 模块,这些 cmake 模块是随你的工程发布的,为了让 cmake 在处理CMakeLists.txt 时找到这些模块,你需要通过 SET 指令,将自己的 cmake 模块路径设置一下。
比如
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
这时候你就可以通过 INCLUDE 指令来调用自己的模块了。

8,EXECUTABLE_OUTPUT_PATH 和 LIBRARY_OUTPUT_PATH
分别用来重新定义最终结果的存放目录,前面我们已经提到了这两个变量。

9,PROJECT_NAME
返回通过 PROJECT 指令定义的项目名称。

四,cmake 调用环境变量的方式
使用$ENV{NAME}指令就可以调用系统的环境变量了。
比如
MESSAGE(STATUS “HOME dir: $ENV{HOME}”)
设置环境变量的方式是:
SET(ENV{变量名} 值)
1,CMAKE_INCLUDE_CURRENT_DIR
自动添加 CMAKE_CURRENT_BINARY_DIR 和 CMAKE_CURRENT_SOURCE_DIR 到当前处理
的 CMakeLists.txt。相当于在每个 CMakeLists.txt 加入:
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_CURRENT_SOURCE_DIR})

2,CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE
将工程提供的头文件目录始终至于系统头文件目录的前面,当你定义的头文件确实跟系统发生冲突时可以提供一些帮助。

3,CMAKE_INCLUDE_PATH 和 CMAKE_LIBRARY_PATH 我们在上一节已经提及。
五,系统信息
1,CMAKE_MAJOR_VERSION,CMAKE 主版本号,比如 2.4.6 中的 2
2,CMAKE_MINOR_VERSION,CMAKE 次版本号,比如 2.4.6 中的 4
3,CMAKE_PATCH_VERSION,CMAKE 补丁等级,比如 2.4.6 中的 6
4,CMAKE_SYSTEM,系统名称,比如 Linux-2.6.22
5,CMAKE_SYSTEM_NAME,不包含版本的系统名,比如 Linux
6,CMAKE_SYSTEM_VERSION,系统版本,比如 2.6.22
7,CMAKE_SYSTEM_PROCESSOR,处理器名称,比如 i686.
8,UNIX,在所有的类 UNIX 平台为 TRUE,包括 OS X 和 cygwin
9,WIN32,在所有的 win32 平台为 TRUE,包括 cygwin
六,主要的开关选项:
1,CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS,用来控制 IF ELSE 语句的书写方式,在
下一节语法部分会讲到。
2,BUILD_SHARED_LIBS
这个开关用来控制默认的库编译方式,如果不进行设置,使用 ADD_LIBRARY 并没有指定库
类型的情况下,默认编译生成的库都是静态库。
如果 SET(BUILD_SHARED_LIBS ON)后,默认生成的为动态库。
3,CMAKE_C_FLAGS
设置 C 编译选项,也可以通过指令 ADD_DEFINITIONS()添加。
4,CMAKE_CXX_FLAGS
设置 C++编译选项,也可以通过指令 ADD_DEFINITIONS()添加。
小结:
本章介绍了一些较常用的 cmake 变量,这些变量仅仅是所有 cmake 变量的很少一部分,目
前 cmake 的英文文档也是比较缺乏的,如果需要了解更多的 cmake 变量,更好的方式是阅
读一些成功项目的 cmake 工程文件,比如 KDE4 的代码。

八,cmake 常用指令
前面我们讲到了 cmake 常用的变量,相信“cmake 即编程”的感觉会越来越明显,无论如何,我们仍然可以看到 cmake 比 autotools 要简单很多。接下来我们就要集中的看一看cmake 所提供的常用指令。在前面的章节我们已经讨论了很多指令的用法,如
PROJECT,ADD_EXECUTABLE,INSTALL,ADD_SUBDIRECTORY,SUBDIRS,
INCLUDE_DIRECTORIES,LINK_DIRECTORIES,TARGET_LINK_LIBRARIES,SET 等。
本节会引入更多的 cmake 指令,为了编写的方便,我们将按照 cmake man page 的顺序来介绍各种指令,不再推荐使用的指令将不再介绍,INSTALL 系列指令在安装部分已经做了非常详细的说明,本节也不在提及。(你可以将本章理解成选择性翻译,但是会加入更多的个人理解)

一,基本指令
1,ADD_DEFINITIONS
向 C/C++编译器添加-D 定义,比如:
ADD_DEFINITIONS(-DENABLE_DEBUG -DABC),参数之间用空格分割。
如果你的代码中定义了#ifdef ENABLE_DEBUG #endif,这个代码块就会生效。
如果要添加其他的编译器开关,可以通过 CMAKE_C_FLAGS 变量和 CMAKE_CXX_FLAGS 变量设置。


2,ADD_DEPENDENCIES
定义 target 依赖的其他 target,确保在编译本 target 之前,其他的 target 已经被构建。
ADD_DEPENDENCIES(target-name depend-target1
                 depend-target2 ...)


3,ADD_EXECUTABLE、ADD_LIBRARY、ADD_SUBDIRECTORY 前面已经介绍过了,这里不再罗唆。


4,ADD_TEST 与 ENABLE_TESTING 指令。
ENABLE_TESTING 指令用来控制 Makefile 是否构建 test 目标,涉及工程所有目录。语法很简单,没有任何参数,ENABLE_TESTING(),一般情况这个指令放在工程的主CMakeLists.txt 中.


ADD_TEST 指令的语法是:
ADD_TEST(testname Exename arg1 arg2 ...)
testname 是自定义的 test 名称,Exename 可以是构建的目标文件也可以是外部脚本等等。后面连接传递给可执行文件的参数。如果没有在同一个 CMakeLists.txt 中打开ENABLE_TESTING()指令,任何 ADD_TEST 都是无效的。
比如我们前面的 Helloworld 例子,可以在工程主 CMakeLists.txt 中添加
ADD_TEST(mytest ${PROJECT_BINARY_DIR}/bin/main)
ENABLE_TESTING()
生成 Makefile 后,就可以运行 make test 来执行测试了。


5,AUX_SOURCE_DIRECTORY
基本语法是:
AUX_SOURCE_DIRECTORY(dir VARIABLE)
作用是发现一个目录下所有的源代码文件并将列表存储在一个变量中,这个指令临时被用来自动构建源文件列表。因为目前 cmake 还不能自动发现新添加的源文件。
比如
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(main ${SRC_LIST})
你也可以通过后面提到的 FOREACH 指令来处理这个 LIST


6,CMAKE_MINIMUM_REQUIRED
其语法为 CMAKE_MINIMUM_REQUIRED(VERSION versionNumber [FATAL_ERROR])
比如 CMAKE_MINIMUM_REQUIRED(VERSION 2.5 FATAL_ERROR)
如果 cmake 版本小与 2.5,则出现严重错误,整个过程中止。


7,EXEC_PROGRAM
在 CMakeLists.txt 处理过程中执行命令,并不会在生成的 Makefile 中执行。

具体语法为:
EXEC_PROGRAM(Executable [directory in which to run]
                [ARGS <arguments to executable>]
                [OUTPUT_VARIABLE <var>]
                [RETURN_VALUE <var>])
用于在指定的目录运行某个程序,通过 ARGS 添加参数,如果要获取输出和返回值,可通过OUTPUT_VARIABLE 和 RETURN_VALUE 分别定义两个变量.


这个指令可以帮助你在 CMakeLists.txt 处理过程中支持任何命令,比如根据系统情况去修改代码文件等等。
举个简单的例子,我们要在 src 目录执行 ls 命令,并把结果和返回值存下来。
可以直接在 src/CMakeLists.txt 中添加:
EXEC_PROGRAM(ls ARGS "*.c" OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE
LS_RVALUE)
IF(not LS_RVALUE)
MESSAGE(STATUS "ls result: " ${LS_OUTPUT})
ENDIF(not LS_RVALUE)


在 cmake 生成 Makefile 的过程中,就会执行 ls 命令,如果返回 0,则说明成功执行,那么就输出 ls *.c 的结果。关于 IF 语句,后面的控制指令会提到。


8,FILE 指令
文件操作指令,基本语法为:
       FILE(WRITE filename "message to write"... )
       FILE(APPEND filename "message to write"... )
       FILE(READ filename variable)
       FILE(GLOB variable [RELATIVE path] [globbing expression_r_rs]...)
       FILE(GLOB_RECURSE variable [RELATIVE path] [globbing expression_r_rs]...)
       FILE(REMOVE [directory]...)
       FILE(REMOVE_RECURSE [directory]...)
       FILE(MAKE_DIRECTORY [directory]...)
       FILE(RELATIVE_PATH variable directory file)
       FILE(TO_CMAKE_PATH path result)
       FILE(TO_NATIVE_PATH path result)
这里的语法都比较简单,不在展开介绍了。


9,INCLUDE 指令,用来载入 CMakeLists.txt 文件,也用于载入预定义的 cmake 模块.
       INCLUDE(file1 [OPTIONAL])
       INCLUDE(module [OPTIONAL])
OPTIONAL 参数的作用是文件不存在也不会产生错误。
你可以指定载入一个文件,如果定义的是一个模块,那么将在 CMAKE_MODULE_PATH 中搜索这个模块并载入。
载入的内容将在处理到 INCLUDE 语句是直接执行。
二,INSTALL 指令
INSTALL 系列指令已经在前面的章节有非常详细的说明,这里不在赘述,可参考前面的安装部分。
三,FIND_指令
FIND_系列指令主要包含一下指令:
FIND_FILE(<VAR> name1 path1 path2 ...)
VAR 变量代表找到的文件全路径,包含文件名
FIND_LIBRARY(<VAR> name1 path1 path2 ...)
VAR 变量表示找到的库全路径,包含库文件名
FIND_PATH(<VAR> name1 path1 path2 ...)
VAR 变量代表包含这个文件的路径。
FIND_PROGRAM(<VAR> name1 path1 path2 ...)
VAR 变量代表包含这个程序的全路径。
FIND_PACKAGE(<name> [major.minor] [QUIET] [NO_MODULE]
                [[REQUIRED|COMPONENTS] [componets...]])
用来调用预定义在 CMAKE_MODULE_PATH 下的 Find<name>.cmake 模块,你也可以自己定义 Find<name>模块,通过 SET(CMAKE_MODULE_PATH dir)将其放入工程的某个目录中供工程使用,我们在后面的章节会详细介绍 FIND_PACKAGE 的使用方法和 Find 模块的编写。


FIND_LIBRARY 示例:
FIND_LIBRARY(libX X11 /usr/lib)
IF(NOT libX)
MESSAGE(FATAL_ERROR “libX not found”)
ENDIF(NOT libX)



四,控制指令:
1,IF 指令,基本语法为:
       IF(expression_r_r)
         # THEN section.
         COMMAND1(ARGS ...)
         COMMAND2(ARGS ...)
         ...
       ELSE(expression_r_r)
         # ELSE section.
         COMMAND1(ARGS ...)
         COMMAND2(ARGS ...)
         ...
       ENDIF(expression_r_r)
另外一个指令是 ELSEIF,总体把握一个原则,凡是出现 IF 的地方一定要有对应的ENDIF.出现 ELSEIF 的地方,ENDIF 是可选的。
表达式的使用方法如下:
IF(var),如果变量不是:空,0,N, NO, OFF, FALSE, NOTFOUND 或<var>_NOTFOUND 时,表达式为真。
IF(NOT var ),与上述条件相反。
IF(var1 AND var2),当两个变量都为真是为真。
IF(var1 OR var2),当两个变量其中一个为真时为真。
IF(COMMAND cmd),当给定的 cmd 确实是命令并可以调用是为真。
IF(EXISTS dir)或者 IF(EXISTS file),当目录名或者文件名存在时为真。
IF(file1 IS_NEWER_THAN file2),当 file1 比 file2 新,或者 file1/file2 其中有一个不存在时为真,文件名请使用完整路径。
IF(IS_DIRECTORY dirname),当 dirname 是目录时,为真。
IF(variable MATCHES regex)
IF(string MATCHES regex)
当给定的变量或者字符串能够匹配正则表达式 regex 时为真。比如:
IF("hello" MATCHES "ell")
MESSAGE("true")
ENDIF("hello" MATCHES "ell")
IF(variable LESS number)
IF(string LESS number)
IF(variable GREATER number)
IF(string GREATER number)
IF(variable EQUAL number)
IF(string EQUAL number)
数字比较表达式
IF(variable STRLESS string)
IF(string STRLESS string)
IF(variable STRGREATER string)
IF(string STRGREATER string)
IF(variable STREQUAL string)
IF(string STREQUAL string)
按照字母序的排列进行比较.
IF(DEFINED variable),如果变量被定义,为真。
一个小例子,用来判断平台差异:
IF(WIN32)
    MESSAGE(STATUS “This is windows.”)
    #作一些 Windows 相关的操作
ELSE(WIN32)
    MESSAGE(STATUS “This is not windows”)
    #作一些非 Windows 相关的操作
ENDIF(WIN32)
上述代码用来控制在不同的平台进行不同的控制,但是,阅读起来却并不是那么舒服,
ELSE(WIN32)之类的语句很容易引起歧义。
这就用到了我们在“常用变量”一节提到的 CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS 开关。
可以 SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
这时候就可以写成:
IF(WIN32)
ELSE()
ENDIF()
如果配合 ELSEIF 使用,可能的写法是这样:
IF(WIN32)
#do something related to WIN32
ELSEIF(UNIX)
#do something related to UNIX
ELSEIF(APPLE)
#do something related to APPLE
ENDIF(WIN32)
2,WHILE
WHILE 指令的语法是:
        WHILE(condition)
          COMMAND1(ARGS ...)
          COMMAND2(ARGS ...)
          ...
        ENDWHILE(condition)
其真假判断条件可以参考 IF 指令。
3,FOREACH
FOREACH 指令的使用方法有三种形式:
1,列表
        FOREACH(loop_var arg1 arg2 ...)
          COMMAND1(ARGS ...)
          COMMAND2(ARGS ...)
          ...
        ENDFOREACH(loop_var)
像我们前面使用的 AUX_SOURCE_DIRECTORY 的例子
AUX_SOURCE_DIRECTORY(. SRC_LIST)
FOREACH(F ${SRC_LIST})
    MESSAGE(${F})
ENDFOREACH(F)
2,范围
FOREACH(loop_var RANGE total)
ENDFOREACH(loop_var)
从 0 到 total 以1为步进
举例如下:
FOREACH(VAR RANGE 10)
MESSAGE(${VAR})
ENDFOREACH(VAR)
最终得到的输出是:
0
1
2
3
4
5
6
7
8
9
10
3,范围和步进
FOREACH(loop_var RANGE start stop [step])
ENDFOREACH(loop_var)
从 start 开始到 stop 结束,以 step 为步进,
举例如下
FOREACH(A RANGE 5 15 3)
MESSAGE(${A})
ENDFOREACH(A)
最终得到的结果是:
5
8
11
14
这个指令需要注意的是,知道遇到 ENDFOREACH 指令,整个语句块才会得到真正的执行。
小结:
本小节基本涵盖了常用的 cmake 指令,包括基本指令、查找指令、安装指令以及控制语句等,特别需要注意的是,在控制语句条件中使用变量,不能用${}引用,而是直接应用变量名。


掌握了以上的各种控制指令,你应该完全可以通过 cmake 管理复杂的程序了,下一节,我
们将介绍一个比较复杂的例子,通过他来演示本章的一些指令,并介绍模块的概念。


九,复杂的例子:模块的使用和自定义模块
你现在还会觉得 cmake 简单吗?


本章我们将着重介绍系统预定义的 Find 模块的使用以及自己编写 Find 模块,系统中提供了其他各种模块,一般情况需要使用 INCLUDE 指令显式的调用,FIND_PACKAGE 指令是一个特例,可以直接调用预定义的模块.

其实使用纯粹依靠 cmake 本身提供的基本指令来管理工程是一件非常复杂的事情,所以,cmake 设计成了可扩展的架构,可以通过编写一些通用的模块来扩展 cmake.


在本章,我们准备首先介绍一下 cmake 提供的 FindCURL 模块的使用。然后,基于我们前面的 libhello 共享库,编写一个 FindHello.cmake 模块.

一,使用 FindCURL 模块
在/backup/cmake 目录建立 t5 目录,用于存放我们的 CURL 的例子。
建立 src 目录,并建立 src/main.c,内容如下:
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
FILE *fp;
int write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
int written = fwrite(ptr, size, nmemb, (FILE *)fp);
return written;
}
int main()
{
const char * path = “/tmp/curl-test”;
const char * mode = “w”;
fp = fopen(path,mode);
curl_global_init(CURL_GLOBAL_ALL);
CURLcode res;
CURL *curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, “http://www.linux-ren.org”);
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
res = curl_easy_perform(curl);
curl_easy_cleanup(curl);
}
这段代码的作用是通过 curl 取回 www.linux-ren.org 的首页并写入/tmp/curl-test文件中。
建立主工程文件 CMakeLists.txt
PROJECT(CURLTEST)
ADD_SUBDIRECTORY(src)
建立 src/CMakeLists.txt
ADD_EXECUTABLE(curltest main.c)
现在自然是没办法编译的,我们需要添加 curl 的头文件路径和库文件。
方法 1:
直接通过 INCLUDE_DIRECTORIES 和 TARGET_LINK_LIBRARIES 指令添加:
我们可以直接在 src/CMakeLists.txt 中添加:
INCLUDE_DIRECTORIES(/usr/include)
TARGET_LINK_LIBRARIES(curltest curl)
然后建立 build 目录进行外部构建即可。
现在我们要探讨的是使用 cmake 提供的 FindCURL 模块。
方法 2,使用 FindCURL 模块。
向src/CMakeLists.txt 中添加:
FIND_PACKAGE(CURL)
IF(CURL_FOUND)
  INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
  TARGET_LINK_LIBRARIES(curltest ${CURL_LIBRARY})
ELSE(CURL_FOUND)
    MESSAGE(FATAL_ERROR ”CURL library not found”)
ENDIF(CURL_FOUND)
对于系统预定义的 Find<name>.cmake 模块,使用方法一般如上例所示:
每一个模块都会定义以下几个变量
    <name>_FOUND
  •
    <name>_INCLUDE_DIR or <name>_INCLUDES
  •
    <name>_LIBRARY or <name>_LIBRARIES
  •
你可以通过<name>_FOUND 来判断模块是否被找到,如果没有找到,按照工程的需要关闭某些特性、给出提醒或者中止编译,上面的例子就是报出致命错误并终止构建。


如果<name>_FOUND 为真,则将<name>_INCLUDE_DIR 加入 INCLUDE_DIRECTORIES,
将<name>_LIBRARY 加入 TARGET_LINK_LIBRARIES 中。
我们再来看一个复杂的例子,通过<name>_FOUND 来控制工程特性:
SET(mySources viewer.c)
SET(optionalSources)
SET(optionalLibs)
FIND_PACKAGE(JPEG)
IF(JPEG_FOUND)
  SET(optionalSources ${optionalSources} jpegview.c)
  INCLUDE_DIRECTORIES( ${JPEG_INCLUDE_DIR} )
  SET(optionalLibs ${optionalLibs} ${JPEG_LIBRARIES} )
  ADD_DEFINITIONS(-DENABLE_JPEG_SUPPORT)
ENDIF(JPEG_FOUND)
IF(PNG_FOUND)
  SET(optionalSources ${optionalSources} pngview.c)
  INCLUDE_DIRECTORIES( ${PNG_INCLUDE_DIR} )
  SET(optionalLibs ${optionalLibs} ${PNG_LIBRARIES} )
  ADD_DEFINITIONS(-DENABLE_PNG_SUPPORT)
ENDIF(PNG_FOUND)
ADD_EXECUTABLE(viewer ${mySources} ${optionalSources} )
TARGET_LINK_LIBRARIES(viewer ${optionalLibs}
通过判断系统是否提供了 JPEG 库来决定程序是否支持 JPEG 功能。


二,编写属于自己的 FindHello 模块。
我们在此前的 t3 实例中,演示了构建动态库、静态库的过程并进行了安装。
接下来,我们在 t6 示例中演示如何自定义 FindHELLO 模块并使用这个模块构建工程:
请在建立/backup/cmake/中建立 t6 目录,并在其中建立 cmake 目录用于存放我们自己定义的 FindHELLO.cmake 模块,同时建立 src 目录,用于存放我们的源文件。


1,定义 cmake/FindHELLO.cmake 模块
FIND_PATH(HELLO_INCLUDE_DIR hello.h /usr/include/hello
/usr/local/include/hello)
FIND_LIBRARY(HELLO_LIBRARY NAMES hello PATH /usr/lib
/usr/local/lib)
IF (HELLO_INCLUDE_DIR AND HELLO_LIBRARY)
  SET(HELLO_FOUND TRUE)
ENDIF (HELLO_INCLUDE_DIR AND HELLO_LIBRARY)
IF (HELLO_FOUND)
  IF (NOT HELLO_FIND_QUIETLY)
     MESSAGE(STATUS "Found Hello: ${HELLO_LIBRARY}")
  ENDIF (NOT HELLO_FIND_QUIETLY)
ELSE (HELLO_FOUND)
  IF (HELLO_FIND_REQUIRED)
     MESSAGE(FATAL_ERROR "Could not find hello library")
  ENDIF (HELLO_FIND_REQUIRED)
ENDIF (HELLO_FOUND)
针对上面的模块让我们再来回顾一下 FIND_PACKAGE 指令:
       FIND_PACKAGE(<name> [major.minor] [QUIET] [NO_MODULE]
                 [[REQUIRED|COMPONENTS] [componets...]])
前面的 CURL 例子中我们使用了最简单的 FIND_PACKAGE 指令,其实他可以使用多种参数,
QUIET 参数,对应与我们编写的 FindHELLO 中的 HELLO_FIND_QUIETLY,如果不指定这个参数,就会执行:
MESSAGE(STATUS "Found Hello: ${HELLO_LIBRARY}")


REQUIRED 参数,其含义是指这个共享库是否是工程必须的,如果使用了这个参数,说明这个链接库是必备库,如果找不到这个链接库,则工程不能编译。对应于
FindHELLO.cmake 模块中的 HELLO_FIND_REQUIRED 变量。
同样,我们在上面的模块中定义了 HELLO_FOUND,
HELLO_INCLUDE_DIR,HELLO_LIBRARY 变量供开发者在 FIND_PACKAGE 指令中使用。
OK,下面建立 src/main.c,内容为:
#include <hello.h>
int main()
{
    HelloFunc();
    return 0;
}
建立 src/CMakeLists.txt 文件,内容如下:
FIND_PACKAGE(HELLO)
IF(HELLO_FOUND)
   ADD_EXECUTABLE(hello main.c)
   INCLUDE_DIRECTORIES(${HELLO_INCLUDE_DIR})
   TARGET_LINK_LIBRARIES(hello ${HELLO_LIBRARY})
ENDIF(HELLO_FOUND)
为了能够让工程找到 FindHELLO.cmake 模块(存放在工程中的 cmake 目录)我们在主工程文件 CMakeLists.txt 中加入:
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


三,使用自定义的 FindHELLO 模块构建工程
仍然采用外部编译的方式,建立 build 目录,进入目录运行:
cmake ..
我们可以从输出中看到:
Found Hello: /usr/lib/libhello.so
如果我们把上面的 FIND_PACKAGE(HELLO)修改为 FIND_PACKAGE(HELLO QUIET),则不会看到上面的输出。
接下来就可以使用 make 命令构建工程,运行:
./src/hello 可以得到输出
Hello World。
说明工程成功构建。
四,如果没有找到 hello library 呢?
我们可以尝试将/usr/lib/libhello.x 移动到/tmp 目录,这样,按照 FindHELLO 模块的定义,就找不到 hello library 了,我们再来看一下构建结果:
cmake ..
仍然可以成功进行构建,但是这时候是没有办法编译的。
修改 FIND_PACKAGE(HELLO)为 FIND_PACKAGE(HELLO REQUIRED),将 hello library 定义为工程必须的共享库。


这时候再次运行 cmake ..
我们得到如下输出:
CMake Error: Could not find hello library.
因为找不到 libhello.x,所以,整个 Makefile 生成过程被出错中止。

