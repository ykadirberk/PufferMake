<div style="text-align: center;">
    <div style="font-size: 300%;">PufferMake</div>
    <p>Visual Studio Code-integrated project management tool for linux g++</p>
    <h1></h1>
</div>
<div>
    <p>
        This project is aimed to make the C++ project development experience on linux to feel more like a Visual Studio project. It achieves that simplicity by making use of tasks in Visual Studio Code and creating a new project structure.
    </p>
    </br>
    <h1 style="font-size: 250%">Initialization</h1>
    <p>There are three ways to start using <b style="color: blue;">PufferMake</b>.</p>
    <ul>
        <li>Building using Visual Studio Code tasks.</li>
        <li>Building using Terminal commands.</li>
        <li>Using the released pre-built binary.</li>
    </ul>
    </br>
    <h1 style="font-size: 150%">Building using Visual Studio Code tasks</h1>
    <p>Download this project and extract it to a folder. Open this folder in Visual Studio Code. At the top menu, go to: </p>
</div>

```
Terminal >> Run Task... >> Build
```

<div>
     <p>This will open a new terminal window on Visual Studio Code and run compilation and linking processes. The binary file will be in the <b>target</b> folder.</p>
     </br>
     <h1 style="font-size: 150%">Building using Terminal commands</h1>
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
    <h1 style="font-size: 150%">Using the released pre-built binary.</h1>
    <p>Download the latest release or, for the bleeding edge executable, use the executable in the <b>target</b> folder.</p>
    </br>
    <h1 style="font-size: 250%">Creating the First Project</h1>
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
<h1 style="font-size: 150%">".vscode" Folder and "tasks.json" file</h1>
You should not be changing this folder and its contents manually if you don't know what you are doing. It should provide necessary tasks for <b style="color: blue;">PufferMake</b> to operate and should work as it is.
</br>
</br>
<h1 style="font-size: 150%">"objects" Folder</h1>
This folder will contain the object files that are created after the compilation.
</br>
</br>
<h1 style="font-size: 150%">"target" Folder</h1>
This folder will contain the result of build/link operations. 
<li>If the build type is <b>executable</b> then the result's name will be <b style="color: rgb(50, 170, 70);">app</b> by default.</li>
<li>If the build type is <b>shared</b> then the result's name will be <b style="color: rgb(50, 170, 70);">libapp.so</b> by default.</li>
<li>If the build type is <b>static</b> then the result's name will be <b style="color: rgb(50, 170, 70);">libapp.a</b> by default.</li>
This name can be changed in <b>build.json</b> file.
</br>
</br>
<h1 style="font-size: 150%">"src" Folder</h1>
This folder will contain files of the project, It comes with an hello world application (main.cpp) as default.
</br>
</br>
<h1 style="font-size: 150%">"defaults.json" file</h1>
This file contains the default settings of the project manager. It is not advised to change any of the values in this file. 
<li><b>vs-code_integration</b>: This option comes true as default and generates the ".vscode" folder if it does not exist. Changing this field into false will not have an effect unless the ".vscode" folder is deleted.</li>
<li><b>source_file_filters</b>: The list of file extensions that will be recognized as source files.</li>
<li><b>header_file_filters</b>: The list of file extensions that will be recognized as header files.</li>
<li><b>object_file_filters</b>: The list of file extensions that will be recognized as object files.</li>
<li><b>preprocessed_file_filters</b>: The list of file extensions that will be recognized as preprocessed files.</li>
<li><b>staticlib_file_filters</b>: The list of file extensions that will be recognized as static library files.</li>
<li><b>dynamiclib_file_filters</b>: The list of file extensions that will be recognized as dynamic library files.</li>
<li><b>comments</b>: Fields of this json object does not affect anything, They are merely instructions that will also be explained here in detail<./li>
</br>
</br>
<h1 style="font-size: 150%">"build.json" file</h1>
This file contains the build preferences of this project. This is the only file one is allowed to change without an issue.
<li>
<b>build-name</b>: This option is the name of the project. This will be used as the name of the built products. It is adviced to use a name with lowercase characters without spaces.
</li>
<li>
<b>build-type</b>: This option is the type of this project. Allowed options are:
<li style="margin-left: 5%;"><b>executable</b></li>
<li style="margin-left: 10%;">The built product's name will be the same as the specified "{build-name}". As the default, the name should be <b style="color: rgb(50, 170, 70);">app</b></li>
<li style="margin-left: 5%;"><b>shared</b></li>
<li style="margin-left: 10%;">The built product's name will be in this format "lib{build-name}.so". As the default, the name should be lib<b style="color: rgb(50, 170, 70);">app</b>.so</li>
<li style="margin-left: 5%;"><b>static</b></li>
<li style="margin-left: 10%;">The built product's name will be in this format "lib{build-name}.a". As the default, the name should be lib<b style="color: rgb(50, 170, 70);">app</b>.a</li>
</li>
</br>