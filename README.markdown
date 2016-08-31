**TextureAnalysis**
===================

**TextrueAnalysis** is a Project for GL API analysis based on [Apitrace](http://apitrace.github.io/). Through this Project we can get the unique binary files for GL API with MD5 name( include the raw data pointed by Texture GL API).

**Requirement**
==================

Apitrace for Linux, there are two opitions below:
* [Apitrace Github](https://github.com/apitrace/apitrace)
  you should disable some option, here you are [Disable Pager](https://github.com/c14006078/apitrace/commit/d60ea31beaad32958da014ab329c0a837a4236fc)
* Modify Version: https://github.com/c14006078/apitrace

**Installation**
==================

 Compile this Project.

    `make [PROCESS_NUM=4 MAX_CALLS=10 DEBUG=1]`

  * PROCESS_NUM will decide the parallel parameter about process number.(default is 4)
  * MAX_CALLS will determine the batch of instruction number.(default is 10)
  * DEBUG will turn on the Debug option.


**Usage**
==================

* First, you should link the apitrace.

    `export PATH=$apitrace_build:$PATH`

* Second, get the trace file by apitrace.

    `apitrace trace GL_APP`

  if you want to stop traceing, you can use CTRL+C to interrup it. It will also generate the .trace file.

* Third, edit configuration file. We can use these to make a rule for selecting needed calls.

  * group.cf assign group and member.
  * exclude.cfg exclude specify the GL API.
  * FORMAT: Group name will be at the first. Then we use [tab] for our member. It is pretty easy and we already supply the basic example at this Project.

* Forth, trace files analysis and dump the specify binary
 
    `./main OUTPUT_DIR file.trace [file1.trace ...]`

  it will output the unique binary file whose name will replace by MD5.
  
  
