connect -url tcp:127.0.0.1:3121
source C:/ECE_315/ece315lab1/kypd_ssd_gpio.sdk/design_1_wrapper_hw_platform_0/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A" && level==0} -index 1
fpga -file C:/ECE_315/ece315lab1/kypd_ssd_gpio.sdk/design_1_wrapper_hw_platform_0/design_1_wrapper.bit
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
loadhw -hw C:/ECE_315/ece315lab1/kypd_ssd_gpio.sdk/design_1_wrapper_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
dow C:/ECE_315/ece315lab1/kypd_ssd_gpio.sdk/lab1proj2/Debug/lab1proj2.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo Z7 210351AB6E73A"} -index 0
con
