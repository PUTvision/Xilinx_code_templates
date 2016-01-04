# Xilinx_code_templates
Collection of simple examples and drivers for peripherals for Xilinx processors (Microblaze and ARM Cortex A9 in Zynq). Languages used: C and C++.

Guide on how to use C++ for bare metal apps on Zynq (Zedboard) can be found here:
http://www.vision.put.poznan.pl/?p=182

Guide on how to write drivers for bare metal Xilinx Zynq (Zedboard) in C and C++ can be found here:
http://www.vision.put.poznan.pl/?p=246

# Desciption

* /app_hello_world/ - simple hello world application for Zedboard
* /app_zynq_ps7_timer/ - example app that uses hardware timer through C and C++ style driver
* /linker_scripts/zynq_ddr_10MB_10MB/ - example linker script for Zedboard with 10 MB sections sizes
* /platform/ - code for cache and UART initializaion (copied from example C project in Xilinx SDK)
* /zynq_ps7_timer/ - C and C++ drivers for Zynq PS timer
