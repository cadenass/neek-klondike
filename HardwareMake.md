

# Preparation #
We provide only required files for creating hardware configuration.
But Quartus II generates considerably more files.
Therefore, it is better to put your project in separate folder to isolate automatically generated files.
After creating project's folder, you should copy hardware configuration's files into it.
At last, run Quartus II and then open project file `neek_niosII_video.qpf` from the newly created folder (figure 1).

<img src='http://neek-klondike.googlecode.com/svn/wiki/hw-make-1.png' alt='Opening project' height='640' width='800'>

Figure 1 - Opening project with the Quartus II software<br>
<br>
<h1>Generating SoPC</h1>

First we need to generate files for the our SoPC.<br>
This action is performed by the <b>SoPC Builder</b> utility.<br>
It can be started from menu <b>Tools</b> (figure 2).<br>
<br>
<img src='http://neek-klondike.googlecode.com/svn/wiki/hw-make-2.png' alt='SoPC Builder' height='640' width='800'>

Figure 2 - SoPC Builder<br>
<br>
After opening SoPC Builder you can explore and, if needed, modify system.<br>
When you complete with these tasks you can generate SoPC by clicking button <b>Generate</b> (figure 3).<br>
You will see generation process on the automatically opened tab <b>System generation</b>.<br>
<br>
<img src='http://neek-klondike.googlecode.com/svn/wiki/hw-make-3.png' alt='SoPC generation' height='640' width='800'>

Figure 3 - SoPC generation<br>
<br>
<h1>Compiling project</h1>

After generating SoPC files you can compile project.<br>
Before starting compilation you may want to explore and/or modify top-level design entity.<br>
In this project it represented as the block diagram, which is in the file <code>neek_niosII_video_top.bdf</code>.<br>
<br>
To compile project choose item <b>Start Compilation</b> from menu <b>Processing</b> (figure 4).<br>
<br>
<img src='http://neek-klondike.googlecode.com/svn/wiki/hw-make-4.png' alt='Starting compilation' height='640' width='800'>

Figure 4 - Starting compilation<br>
<br>
When compilation is completed you will see message about 479 warnings, but you may ignore it (figure 5).<br>
Now hardware configuration is ready and you may use it.<br>
Later you will need file <code>neek_niosII_video_time_limited.sof</code> to configure your FPGA and file <code>neek_niosII_video_sopc.ptf</code> (or <code>neek_niosII_video_sopc.sopcinfo</code>) for the NIOS II IDE.<br>
<br>
<blockquote><i>Specified hardware configuration's files has suffix <code>_time_limited</code> because we use Quartus II Web Edition.</i></blockquote>

<img src='http://neek-klondike.googlecode.com/svn/wiki/hw-make-5.png' alt='Compilation completed' height='640' width='800'>

Figure 5 - Compilation completed<br>
<br>
<h1>Probable problems</h1>

If you use Quartus II 10.0 you may see error about DDR SDRAM controller, when you open SoPC builder (figure 6).<br>
You should double click on DDR component and then click <b>Finish</b> button in the opened dialog.<br>
When you do this, error should disappear.<br>
<br>
<img src='http://neek-klondike.googlecode.com/svn/wiki/hw-make-problem-1.png' alt='Error about DDR SDRAM controller' height='640' width='800'>

Figure 6 - Error about DDR SDRAM controller which appeared in Quartus II 10.0 SoPC builder