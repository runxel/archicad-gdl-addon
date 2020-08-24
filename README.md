# GDL Add-on Template
or  
**The Missing Docs for Creating GDL Add-ons**

![Tested on Archicad version](https://img.shields.io/badge/Tested_on-v23-3458B0?style=flat&logo=archicad&logoColor=white)
![Tested on Visual Studio version](https://img.shields.io/badge/Compiled_with-Visual_Studio_2019-8F53CC?style=flat&logo=visual-studio&logoColor=white)


> An unofficial documentation by @runxel on how to make your own GDL add-on (*.gdx file) plus providing a template.

## Purpose
The aim of this repo is to help you with onboarding to make your own GDL add-ons, which you then can call from GDL itself.  
**Why would you want that?** Glad you asked. Sometimes you need to do calculations or other stuff, that would be either very hard, or even straight impossible to do in GDL, since it's not a full-blown programming language.

Bear in mind: Add-ons developed with the GDL dev-kit are very limited and _can not_ interact with the project or communicate with other add-ons.  
You should just use them to offload heavy tasks or computations you can't do in GDL (like bitwise calculations or I/O).

## What you need
- Download and install [Visual Studio](https://visualstudio.microsoft.com/de/downloads/) (2017 or up)
- Intall the C++ environment for Visual Studio
- Download the [GDL Addon Dev Kit](http://archicadapi.graphisoft.com/downloads/gdl-development-kit)
- This repo with the template in [GDX-Template](/GDX-Template/)
- Tiny bit of C++ knowledge
- Dedication and frustration resistance 😉

One thing ahead:  
GDL add-ons **do not** use the `'MDID' 32500` resource, therefore you can't (and don't have to) register the developer or add-on ID.

### Let's start!
First: Unzip the downloaded devkit. The structure will look like this:
```
DevKit \
  + Documentation \..
  + Inc \..
  + Lib \..
  + ReportGD \..
  + Tools \..
    License Agreement.html
    ReadMe First.html
```
The `ReportGD` folder contains the example GDX project by Graphisoft. It is worth checking out. This repo wants to be a much leaner, barebone base structure and better at explaining the stuff which is going on.

Important are the `Inc` and `Lib` folders. They need to be present for a successful [compilation](#compilation) later on. **Those folders need to be next to your project folder in the default configuration.**

Copy now the "GDX-Template" folder from this repo next to the other folders from the DevKit.

### A Solution
Now we need to have a ["_solution_"](https://docs.microsoft.com/en-us/visualstudio/get-started/tutorial-projects-solutions?view=vs-2019). The Visual Studio solution will enable us to _build_ (aka compile) the `.gdx` later on. Without the solution this command is missing. The easiest way to make a solution is to let VS generate it for us. To do so hit <kbd>ctrl + shift + N</kbd> and select <samp>New Solution</samp>.  
There is a [`.sln`](GDX-Template/GDX-Template.sln) file in this repo which you can use, but see it more as a reference. Feel free to edit it directly. What you need to do is to generate new GUIDs.  
One _solution_ can contain multiple _projects_.

### A Project
The next important piece is the [`*.vcxproj`](GDX-Template/GDX-Template.vcxproj) project file. This is what defines the actual settings of your project. It contains information about how to build it and what files comprise it.

There are multiple options to make a project file by yourself: Let [CMake](https://stackoverflow.com/questions/7865700/create-new-visual-studio-project-add-files-and-run-it-command-line) generate it for you, or keep track of all files and prerequisites by hand. The project file is basically a [XML file](https://docs.microsoft.com/de-de/visualstudio/msbuild/msbuild-reference). You can also see all the property pages and configuration options by right clicking your project and selecting <samp>Properties</samp> as well. If you do editing the file itself beware of the [rules](https://docs.microsoft.com/de-de/cpp/build/reference/vcxproj-file-structure) that apply. Keep in mind that the GUIDs need to match with the solution file, too.

Most interesting part except for the build instruction is that the project file contains a link to all the items (source files, etc.) in the project.  
Please be aware of the lack of wildcard support:
```xml
<ItemGroup>
  <ClCompile Include="*.cpp"> <!--Error-->
</ItemGroup>
```

The `<ItemGroup>` with `<ClInclude>` nodes is more less just for the VS user interface. [<sup>source</sup>](https://stackoverflow.com/questions/53621957/using-include-vs-clinclude-in-vcxproj).

Remember the `Inc` and `Lib` folders from above? They are also linked in the project file – which means you could change the path accordingly.

### Some Filters
The filters file (`*.vcxproj.filters`) is an XML file in MSBuild format that is located in the root project folder. It specifies which file types go into which logical folder in the Solution Explorer. Visual Studio creates this file automatically, making it rather uninteresting. You can still edit it to better suit to your needs. [See the docs](https://docs.microsoft.com/de-de/cpp/build/reference/vcxproj-filters-files).

---

Short break for breathing. If you're still with me: Congratulations! If this sounds a bit wild already, don't worry. We get to it.


### Programming
The most important bit of your GDL Add-on is the main [GDX-Template](GDX-Template/Src/GDX-Template.cpp).  
This is where the main functions live. Have a close look at the file.

There are also finished [headers](GDX-Template/Inc/) which you just need to link, depending on what your goal is. Have a look at the original documentation for that. Only one thing to know:
```cpp
#include	"ACGDinc.h"
```
You always need to include this specific header.

There is a second folder called [Lib](GDX-Template/Lib/) with precompiled headers. Those are already linked inside the project file; you can mostly ignore them (but don't delete! They are necessary.)

Last but not least there is the [RFIX](GDX-Template/RFIX.win/) folder with resources, like the icon, and the `.rc` [resource file](GDX-Template/RFIX.win/GDX-Template.RC) which holds all the additional information, like that there is an icon. Most importantly is the `32500 ACNF` resource part of the script.  
Last parameter is the module name, by which name you will need to call your finished add-on from GDL.

**Please note**: The resources situation looks a bit different, if you're developing for MacOS. See the official documentation for more info.


#### More Programming
Since the GDL add-on API was originally written to let users receive external data in GDL we still see the basic structure of an add-on revolving around that functionality. Take a look at the main functions being required:
```
OpenDataFile
InputFromDataFile
OutputToDataFile
CloseDataFile
```
_Input_ i.e. will yield results back to GDL.

The structure of the add-on closely resembles the GDL commands:
```vb
! GDL commands
format = "%c"
channel = OPEN ("DateTime", "", format)         ! invoke the datetime addon
nrvals = INPUT (channel, "", "", str_datetime)  ! read from ›file‹
CLOSE channel                                   ! close it, we are done
```


## Executing GDL Add-Ons
GDL add-ons are invoked when the GDL interpreter sees an `OPEN`, `INPUT`, `OUTPUT`, `CLOSE`, or (equaling to) `INITADDONSCOPE`, `PREPAREFUNCTION`, `CALLFUNCTION`, `CLOSEADDONSCOPE` command respectively.
Also when interpreting a `REQUEST` function which has as first parameter the request name itself, GDL looks after an extension if the request is not implemented in Archicad. For an example see the `DATETIME` [request](https://www.selfgdl.de/diverses/umgebung/request/DATETIME/), which eliminates the seperate GDL tasks of opening and closing a channel, resulting in a rather concise GDL command:

```vb
REQUEST("DATETIME", format, str_datetime)
```
Compare to the example above!


## Compilation
You have programmed all the neat stuff you always wanted? Great!  
In the solution explorer on the right side of Visual Studio you can right click on your project and select "<samp>Build</samp>" right at the top. Now a `.gdx` (and a lot of other files) will be generated inside the specified folder (see the `.vcxproj` file), i.e. "Release".

Copy the compiled `.gdx` file into the Add-Ons folder of Archicad, e.g. (where `XX` is the version number):
```
C:\Program Files\GRAPHISOFT\ARCHICAD XX\Add-Ons\GDL\
```

## How To Use
The easiest way of calling our newly generated add-on in GDL is to just use `REQUEST`, since it handles everything for us. Don't forget to initialize the variable first with the correct type first!

```vb
myval = ""  ! init the variable
r = request("GDXTEMPLATE", "", myval)
```

### More than one
It get's a bit complex when you're yielding more than one result.
You can just `Add` (possible are `AddDouble(1234.567)`, `AddLong(42)` [long = integer], `AddString("A string.")`, `AddNumValue` [???], and `AddDictionary`) more and more data, even of different types.  
There are two ways – let's have a look at the Code, this way it is easier to grok:

Our first option consists of initializing all used variables first and then cramming them into the `REQUEST`, in order.

```vb
first_value = ""
second_value = 0.0

r = request("GDXNAME", "", first_value, second_value)
text2 0, 0, first_value
text2 0, -1, second_value
```

Instead of initializing variables inside the script you could of course use parameters! Those can be written back with `PARAMETERS my_param = my_param` (assuming the type is correct).

The code of the relevant function inside the GDL add-on (shortened to the important pieces). You can see: the only thing that matters is the order of variables you yield.

```cpp
GSErr __GDLEXT_CALL	InputFromDataFile (...)
{
	/* ... */
	values.AddString ("A string, as you might see.");
	values.AddDouble (123.45);
	// Always make sure `nrgotvals` is set to the correct number of values you're yielding·
	*nrgotvals = 2;
	/* ... */
}
```

The second option is to declare an array – which isn't quite the advantage one might think in the first moment: you still can't return an unlimited number of results, because the add-on only writes into pre-populated array cells, meaning you still need to know the precise number of results yielded by the add-on. At least you can shorten the request command this way:

```vb
dim values_to_receive[]
values_to_receive[1] = ""
values_to_receive[2] = 0.0

r = request("GDXNAME", "", values_to_receive)
text2 0, 0, values_to_receive[1]
text2 0,-1, values_to_receive[2]
```

The add-on code stays the same as the in the example above!

**Caveats**:
- Naming of the values in GDL doesn't matter, all you need to adhere to is the _order_ of the variables. `Add`-ing values in the add-on will always be in order, you can't skip items.
- You don't _need_ to declare the GDL variables before using, but you will get a lot of errors thrown at you if you don't. 
- When clicking on the "Check Script" button, no GDL add-on is actually called, meaning you can not use `print` for debugging! (It will just use the values from the initialization.)

---

## Tautological Boilerplate
_All trademarks and copyrights on this repo are the property of their respective owners._  
All code is presented as-is and the author can not be held liable for any damage occuring.
