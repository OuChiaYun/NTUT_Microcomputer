cmd_/home/nvidia/Test/demo.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -z noexecstack   --build-id  -T ./scripts/module-common.lds -o /home/nvidia/Test/demo.ko /home/nvidia/Test/demo.o /home/nvidia/Test/demo.mod.o;  true