
# Compile

```
cmake -DCMAKE_TOOLCHAIN_FILE=D:\xd\work\software\github\dev_no_ide\toolchain.cmake D:\xd\work\software\github\dev_no_ide -G "MinGW Makefiles" -D "CMAKE_MAKE_PROGRAM:PATH=C:/MinGW/bin/make.exe" 

make
```


```
& C:/Users/xiaod/AppData/Local/Programs/Python/Python39/python.exe d:/xd/work/software/github/dev_no_ide/scripts/kconfig/kconfig.py --handwritten-input-configs Kconfig build\config_out.config build/pre_header.h build/kconfig_out.txt prj.conf

```

# Tool



# Other

```
d:/program files (x86)/arm gnu toolchain arm-none-eabi/12.2 rel1/bin/../lib/gcc/arm-none-eabi/12.2.1/../../../../arm-none-eabi/bin/ld.exe: warning: demo.elf has a LOAD segment with RWX permissions

set_target_properties add -Wl,--no-warn-rwx-segments

```

# Reference
- https://kxygk.github.io/bluepill/
- Kconfig: Zephyr

