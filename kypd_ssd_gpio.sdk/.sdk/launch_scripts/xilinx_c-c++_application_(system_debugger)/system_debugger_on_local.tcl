connect -url tcp:127.0.0.1:3121
source /home/macmala/Documents/Courses/ECE315/labs/lab1/kypd_ssd_gpio-20220129T172209Z-001/kypd_ssd_gpio/kypd_ssd_gpio.sdk/design_1_wrapper_hw_platform_0/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A" && level==0} -index 1
fpga -file /home/macmala/Documents/Courses/ECE315/labs/lab1/kypd_ssd_gpio-20220129T172209Z-001/kypd_ssd_gpio/kypd_ssd_gpio.sdk/design_1_wrapper_hw_platform_0/design_1_wrapper.bit
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
loadhw -hw /home/macmala/Documents/Courses/ECE315/labs/lab1/kypd_ssd_gpio-20220129T172209Z-001/kypd_ssd_gpio/kypd_ssd_gpio.sdk/design_1_wrapper_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
dow /home/macmala/Documents/Courses/ECE315/labs/lab1/kypd_ssd_gpio-20220129T172209Z-001/kypd_ssd_gpio/kypd_ssd_gpio.sdk/lab1proj/Debug/lab1proj.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
con
