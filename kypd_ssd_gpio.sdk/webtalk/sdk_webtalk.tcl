webtalk_init -webtalk_dir C:\\ECE_315\\ece315lab1\\kypd_ssd_gpio.sdk\\webtalk
webtalk_register_client -client project
webtalk_add_data -client project -key date_generated -value "2022-02-10 02:06:07" -context "software_version_and_target_device"
webtalk_add_data -client project -key product_version -value "SDK v2019.1" -context "software_version_and_target_device"
webtalk_add_data -client project -key build_version -value "2019.1" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_platform -value "amd64" -context "software_version_and_target_device"
webtalk_add_data -client project -key registration_id -value "" -context "software_version_and_target_device"
webtalk_add_data -client project -key tool_flow -value "SDK" -context "software_version_and_target_device"
webtalk_add_data -client project -key beta -value "false" -context "software_version_and_target_device"
webtalk_add_data -client project -key route_design -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_family -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_device -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_package -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_speed -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key random_id -value "3qr0vvenq8897fbfe383sr8beo" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_id -value "2019.1_4" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_iteration -value "4" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_name -value "Microsoft Windows 8 or later , 64-bit" -context "user_environment"
webtalk_add_data -client project -key os_release -value "major release  (build 9200)" -context "user_environment"
webtalk_add_data -client project -key cpu_name -value "Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz" -context "user_environment"
webtalk_add_data -client project -key cpu_speed -value "1992 MHz" -context "user_environment"
webtalk_add_data -client project -key total_processors -value "1" -context "user_environment"
webtalk_add_data -client project -key system_ram -value "17.005 GB" -context "user_environment"
webtalk_register_client -client sdk
webtalk_add_data -client sdk -key uid -value "1644448250952" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key isZynq -value "true" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key isZynqMP -value "false" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key Processors -value "2" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key VivadoVersion -value "2019.1" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key Arch -value "zynq" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key Device -value "7z010" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key IsHandoff -value "true" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key os -value "NA" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key apptemplate -value "NA" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key RecordType -value "HWCreation" -context "sdk\\\\hardware/1644448250952"
webtalk_add_data -client sdk -key uid -value "NA" -context "sdk\\\\bsp/1644483967886"
webtalk_add_data -client sdk -key RecordType -value "ToolUsage" -context "sdk\\\\bsp/1644483967886"
webtalk_add_data -client sdk -key BootgenCount -value "0" -context "sdk\\\\bsp/1644483967886"
webtalk_add_data -client sdk -key DebugCount -value "0" -context "sdk\\\\bsp/1644483967886"
webtalk_add_data -client sdk -key PerfCount -value "0" -context "sdk\\\\bsp/1644483967886"
webtalk_add_data -client sdk -key FlashCount -value "0" -context "sdk\\\\bsp/1644483967886"
webtalk_add_data -client sdk -key CrossTriggCount -value "0" -context "sdk\\\\bsp/1644483967886"
webtalk_add_data -client sdk -key QemuDebugCount -value "0" -context "sdk\\\\bsp/1644483967886"
webtalk_transmit -clientid 2829459261 -regid "" -xml C:\\ECE_315\\ece315lab1\\kypd_ssd_gpio.sdk\\webtalk\\usage_statistics_ext_sdk.xml -html C:\\ECE_315\\ece315lab1\\kypd_ssd_gpio.sdk\\webtalk\\usage_statistics_ext_sdk.html -wdm C:\\ECE_315\\ece315lab1\\kypd_ssd_gpio.sdk\\webtalk\\sdk_webtalk.wdm -intro "<H3>SDK Usage Report</H3><BR>"
webtalk_terminate
