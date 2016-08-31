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

    `make [PROCESS_NUM=4 MAX_CALLS=10 DEBUG=0]`

  * PROCESS_NUM will decide the parallel parameter about process number.It should be as many as your CPU cores.(default is 4, min 1)
  * MAX_CALLS will determine the batch of instruction number.(default is 10, min 1)
  * DEBUG will turn on the Debug option if DEBUG=1.


**Usage**
==================

* First, you should link the apitrace.

    `export PATH=$apitrace_build:$PATH`

* Second, get the trace file by apitrace.

    `apitrace trace GL_APP`

  if you want to stop traceing, you can use CTRL+C to interrup it. It will also generate the .trace file.

* Third, edit configuration file. We can use these to make a rule for selecting needed calls.

  * `include.cfg` the api we want to analysis.
  * `exclude.cfg` the api we don't want to analysis.

* Forth, trace files analysis and dump the specify binary
 
    `./main OUTPUT_DIR file.trace [file1.trace ...]`

  it will output the unique binary file whose name will replace by MD5.
  
  
