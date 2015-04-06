

# Project creation #

After you run NIOS II IDE you need to choose your workspace.
To do this select item **Workspace Launcher** from menu **File** and type location of your workspace in dialog box (figure 1).

<img src='http://neek-klondike.googlecode.com/svn/wiki/sw-make-1.png' alt='Creating workspace' height='640' width='800'>

Figure 1 - Creating workspace<br>
<br>
After workspace has been created you need to create new project within this workspace.<br>
To do this choose item <b>Nios II C/C++ Application</b> from submenu <b>New</b> of menu <b>File</b> (figure 2).<br>
In the opened dialog box you should specify:<br>
<ol><li>Name of newly created project.<br>
</li><li>Template <b>Blank Project</b>.<br>
</li><li>Location of file, which contains information about hardware configuration (it is <code>.ptf</code> or <code>.sopcinfo</code> depending on version of the NIOS II IDE).</li></ol>

<img src='http://neek-klondike.googlecode.com/svn/wiki/sw-make-2.png' alt='Creating project' height='640' width='800'>

Figure 2 - Creating project<br>
<br>
<h1>Importing sources</h1>

Now you have a blank project and you need to add files into it.<br>
You can import files by choosing item <b>Import</b> from the project's context menu.<br>
<br>
Next select item <b>File system</b> from the list <b>General</b>.<br>
In the next dialog you should (figure 3):<br>
<ol><li>Browse the top-level directory <b>software</b>, which contains sources.<br>
</li><li>Select directory <b>software</b>:<br>
</li><li>Specify filtered types (to exclude svn files) next way: click <b>Filter types</b>, then select <b>.h</b>, <b>.hpp</b>, <b>.c</b> and <b>.cpp</b>, then enter <b>res</b> in field <b>Other extensions</b> and click <b>Ok</b>.<br>
Also check that option <b>Create selected folders only</b> is selected.</li></ol>

<img src='http://neek-klondike.googlecode.com/svn/wiki/sw-make-3.png' alt='Adding sources' height='640' width='800'>

Figure 3 - Adding sources<br>
<br>
<h1>Settings</h1>

Before building this project require some customization.<br>
First, you should customize system library properties.<br>
To do this, select item <b>System Library Contents</b> from the project's context menu and set next options (figure 4):<br>
<ol><li>Select RTOS <b>MicroC/OS II</b> (we require this OS because we have to concurrently update information on the LCD and poll the touch-screen).<br>
</li><li>Set option <b>Program never exits</b> (follow from the previous).<br>
</li><li>Set option <b>Support C++</b>.</li></ol>

<img src='http://neek-klondike.googlecode.com/svn/wiki/sw-make-4.png' alt='Customizing system library' height='640' width='800'>

Figure 4 - Customizing system library<br>
<br>
Secondly, we should optimize our project because we use video subsystem.<br>
To do this, select item <b>Release</b> from the list <b>Active Build Configuration</b> from the project's context menu (figure 5).<br>
<br>
<img src='http://neek-klondike.googlecode.com/svn/wiki/sw-make-5.png' alt='Customizing active build' height='640' width='800'>

Figure 5 - Customizing active build<br>
<br>
Next select item <b>Properties</b>  from the project's context menu and in the opened dialog select section <b>C/C++ Build</b> (figure 6).<br>
In tab <b>Tool Settings</b> set option <b>Optimization levels</b> to <b>Optimiza most -O3</b> and set option <b>Debug Level</b> to <b>None</b>.<br>
Repeat build configuration for the <code>_syslib</code> project.<br>
<br>
<img src='http://neek-klondike.googlecode.com/svn/wiki/sw-make-6.png' alt='Customizing optimization options' height='640' width='800'>

Figure 6 - Customizing optimization options<br>
<br>
<h1>Build</h1>

Now you ready to build the project.<br>
To perform build select <b>Build All</b> from menu <b>Project</b>.<br>
As result will be generated <b>.elf</b> file in the subfolder <b>Release</b>.