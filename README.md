<div style="text-align: center;">
    <h1 style="font-size: 300%; text-align: center;">PufferMake</h1>
    <p>A project management tool integrated with Visual Studio Code that is aimed for C++ projects made on linux.</p>
    <h1></h1>
</div>
<div>
    <p>
        This project is aimed to make the C++ project development experience on linux to feel more like a Visual Studio project. It achieves that simplicity by making use of tasks in Visual Studio Code and creating a new project structure.
    </p>
    </br>
    <h2 style="font-size: 250%">Initialization</h1>
    <p>There are three ways to start using <b style="color: blue;">PufferMake</b>.</p>
    <ul>
        <li>Building using Visual Studio Code tasks.</li>
        <li>Building using Terminal commands.</li>
        <li>Using the released pre-built binary.</li>
    </ul>
    </br>
    <h3 style="font-size: 150%">Building using Visual Studio Code tasks</h3>
    <p>Download this project and extract it to a folder. Open this folder in Visual Studio Code. At the top menu, go to: </p>
</div>

```
Terminal >> Run Task... >> Build
```

<div>
     <p>This will open a new terminal window on Visual Studio Code and run compilation and linking processes. The binary file will be in the <b>target</b> folder.</p>
     </br>
     <h3 style="font-size: 150%">Building using Terminal commands</h3>
     <p>Download this project and extract it to a folder. Open this folder in terminal and run these terminal commands in the given order.</p>
</div>

```bash
cd objects
```

```bash
g++ -c "../src/main.cpp" "../src/FileList/FileList.cpp" "../src/Configuration/Configuration.cpp" "../src/Maker/Maker.cpp" "../src/ParseCommand/ParseCommand.cpp" -std=c++20 -Os
```

```bash
cd ..
```

```bash
g++ objects/main.o objects/FileList.o objects/Configuration.o objects/ParseCommand.o objects/Maker.o -o ./target/PufferMake
```

<div>
    <p> The binary file will be in the <b>target</b> folder.</p>
    </br>
    <h3 style="font-size: 150%">Using the released pre-built binary.</h3>
    <p>Download the latest release or, for the bleeding edge executable, use the executable in the <b>target</b> folder.</p>
    </br>
    <h2 style="font-size: 250%">Creating the First Project</h2>
    <p>Move the binary named <b style="color: blue;">PufferMake</b> to the folder that you want to create your project in and run one of these commands in that folder. Both does the same thing.</p>
</div>

```bash
./PufferMake
./PufferMake create
```

<p>These commands will create the necessary structure to setup the project. This structure contains these:</p>

```
.vscode/                            -folder
objects/                            -folder
target/                             -folder
src/                                -folder
src/main.cpp                        -file
.vscode/tasks.json                  -file
build.json                          -file
defaults.json                       -file
```
</br>
<h3 style="font-size: 150%">".vscode" Folder and "tasks.json" file</h3>
You should not be changing this folder and its contents manually if you don't know what you are doing. It should provide necessary tasks for <b style="color: blue;">PufferMake</b> to operate and should work as it is.
</br>
</br>
<h3 style="font-size: 150%">"objects" Folder</h3>
This folder will contain the object files that are created after the compilation.
</br>
</br>
<h3 style="font-size: 150%">"target" Folder</h3>
This folder will contain the result of build/link operations. 
<li>If the build type is <b>executable</b> then the result's name will be <b style="color: rgb(50, 170, 70);">app</b> by default.</li>
<li>If the build type is <b>shared</b> then the result's name will be <b style="color: rgb(50, 170, 70);">libapp.so</b> by default.</li>
<li>If the build type is <b>static</b> then the result's name will be <b style="color: rgb(50, 170, 70);">libapp.a</b> by default.</li>
This name can be changed in <b>build.json</b> file.
</br>
</br>
<h3 style="font-size: 150%">"src" Folder</h3>
This folder will contain files of the project, It comes with an hello world application (main.cpp) as default.
</br>
</br>
<h3 style="font-size: 150%">"defaults.json" file</h3>
This file contains the default settings of the project manager. It is not advised to change any of the values in this file. 
<li><b>vs-code_integration</b>: This option comes true as default and generates the ".vscode" folder if it does not exist. Changing this field into false will not have an effect unless the ".vscode" folder is deleted.</li>
<li><b>source_file_filters</b>: The list of file extensions that will be recognized as source files.</li>
<li><b>header_file_filters</b>: The list of file extensions that will be recognized as header files.</li>
<li><b>object_file_filters</b>: The list of file extensions that will be recognized as object files.</li>
<li><b>preprocessed_file_filters</b>: The list of file extensions that will be recognized as preprocessed files.</li>
<li><b>staticlib_file_filters</b>: The list of file extensions that will be recognized as static library files.</li>
<li><b>dynamiclib_file_filters</b>: The list of file extensions that will be recognized as dynamic library files.</li>
<li><b>comments</b>: Fields of this json object does not affect anything, They are merely instructions that will also be explained here in detail</li>
</br>
</br>
<h3 style="font-size: 150%">"build.json" file</h3>
This file contains the build preferences of this project. This is the only file one is allowed to change without an issue.


* <b>build-name</b>: This option is the name of the project. This will be used as the name of the built products. It is adviced to use a name with lowercase characters without spaces.

</br>

* <b>build-type</b>: This option is the type of this project. Allowed options are:

    * <b>executable</b>: This option allows building a standalone executable file. The built product's name will be the same as the specified "{build-name}". As the default, the name should be "<b>app</b>".

    * <b>shared</b>: This option allows building a shared library. The built product's name will be in this format "lib{build-name}.so". As the default, the name should be "lib<b>app</b>.so".

    * <b>static</b>: The built product's name will be in this format "lib{build-name}.a". As the default, the name should be "lib<b>app</b>.a".

</br>


* <b>cpp-version</b>: C++ standard selection. It allows any keyword that is allowed after "-std=". [For more information.](https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html)

</br>


* <b>warnings</b>: This option allows 3 different keywords. <b>disabled</b> option disables all warnings, uses "-w" gcc option. <b>all</b> option enables all warnings, uses "-Wall" option. <b>extra</b> option enables warnings that are not enabled by <b>all</b> keyword, uses "-Wextra" option.

</br>


* <b>optimization</b>: This object is reserved for optimization but allows any compiler option. However, it is only advised to use this option to specify optimization options ([For more information](https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc/Optimize-Options.html)). Changing active option into false will disable optimization options. Recommended options are:

    * <b>O0</b> : Optimize for compilation time.
    * <b>O1</b>, <b>O</b> : Optimize for code size and execution time.
    * <b>O2</b> : Optimize for code size and more execution time.
    * <b>O3</b> : Optimize for code size and more(+) execution time.
    * <b>Os</b> : Optimize for code size.
    * <b>Ofast</b> : Same as -O3 with fast non-accurate math (aggressive speed optimization)
    * <b>Og</b> : Optimize for debugging experience.
    * <b>Oz</b> : Aggressive optimization for code size rather speed.

</br>

* <b>debug</b>: This object is reserved for debug but allows any compiler option. However, it is only advised to use this option to specify debug options ([For more information](https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc/Debugging-Options.html)). Changing active option into false will disable debug options. Recommended options are:

    * <b>g0</b> : No debug information.
    * <b>g1</b> : Minimal debug information.
    * <b>g</b> : Default debug information.
    * <b>g3</b> : Maximal debug information.
    * <b>ggdb</b> : Use most expressive information format that will ease gdb usage.
    * <b>gdwarf</b> : Produce debug information in DWARF format.

</br>

* <b>include-directories</b>: This is a list that specifies additional include directories.

</br>

* <b>static-linking</b>: When active option is true, it searches for <b>files</b> specified in <b>directories</b> and adds these libraries in linking process.

</br>

* <b>dynamic-linking</b>: When active option is true, it puts options that indicate <b>files</b> specified in <b>directories</b>.

</br>

<h2 style="font-size: 250%">Allowed Commands</h2>

These are the commands that the PufferMake allows calling. There will be no need to think about them if you are using Visual Studio Code because you can run these tasks by doing these:
```
Terminal >> Run Task...
```
If you are not using Visual Studio Code, it is advised to use only the create and build commands that are described below.


---


```bash
./PufferMake
./PufferMake create
```
These commands are used to create the project. The first command that should be used after optaining PufferMake.


---


```bash
./PufferMake preprocess
```
This command generates the results after applying the preprocessor macros to all the source files in preprocessed folder.


---


```bash
./PufferMake compile
```
This command compiles all source files and generates results in objects folder.


---


```bash
./PufferMake link-executable
```
This command links object files with specified build options as an executable. It is not advised to call any link command explicitly, other than the one specified in build.json, since it might not work as intended. It is better to call build or build-run.


---


```bash
./PufferMake link-shared
```
This command links object files with specified build options as a shared library. It is not advised to call any link command explicitly, other than the one specified in build.json, since it might not work as intended. It is better to call build or build-run.


---


```bash
./PufferMake link-static
```
This command links object files with specified build options as a static library. It is not advised to call any link command explicitly, other than the build-type specified in build.json, since it might not work as intended. It is better to call build or build-run.


---


```bash
./PufferMake run
```
This command runs the executable that is in the target folder. It will not run any executable if the specified build-type is static or shared.


---


```bash
./PufferMake build
```
This command builds the project with specified instructions in build.json and generates the result in target folder. It calls <b>compile</b> and <b>link</b> operations sequentially.


---


```bash
./PufferMake build-run
```
This command builds the project with specified instructions in build.json, generates the result in target folder and runs that result if the build-type of this project is executable. It calls <b>compile</b>, <b>link</b> and <b>run</b> operations sequentially.
