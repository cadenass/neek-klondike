You may deploy preliminary built hardware configuration and application on the NEEK.
To do this you may download files [neek\_niosII\_video\_time\_limited.sof](http://neek-klondike.googlecode.com/files/neek_niosII_video_time_limited.sof) and [klondike.elf](http://neek-klondike.googlecode.com/files/klondike.elf).

Firstly, configure FPGA:
  1. Run **Nios II Command Shell**
  1. Execute next command `nios2-configure-sof neek_niosII_video_time_limited.sof`
  1. You will be prompted to quit, but do not do this if configuration is the time limited.

Secondly, download the application:
  1. Run another instance of **Nios II Command Shell**
  1. Execute next command `nios2-download klondike.elf --go`

Also, if required, you may run `nios2-terminal` before downloading application.
It allows you to see messages about errors, which appears during application executing.