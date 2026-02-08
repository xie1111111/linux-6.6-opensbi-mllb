savedcmd_arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dtb := gcc -E -Wp,-MMD,arch/riscv/boot/dts/thead/.th1520-lichee-pi-4a.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/riscv/boot/dts/thead/.th1520-lichee-pi-4a.dtb.dts.tmp arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dts ; ./scripts/dtc/dtc -o arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dtb -b 0 -iarch/riscv/boot/dts/thead/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unique_unit_address -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg   -d arch/riscv/boot/dts/thead/.th1520-lichee-pi-4a.dtb.d.dtc.tmp arch/riscv/boot/dts/thead/.th1520-lichee-pi-4a.dtb.dts.tmp ; cat arch/riscv/boot/dts/thead/.th1520-lichee-pi-4a.dtb.d.pre.tmp arch/riscv/boot/dts/thead/.th1520-lichee-pi-4a.dtb.d.dtc.tmp > arch/riscv/boot/dts/thead/.th1520-lichee-pi-4a.dtb.d

source_arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dtb := arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dts

deps_arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dtb := \
  arch/riscv/boot/dts/thead/th1520-lichee-module-4a.dtsi \
  arch/riscv/boot/dts/thead/th1520.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \

arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dtb: $(deps_arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dtb)

$(deps_arch/riscv/boot/dts/thead/th1520-lichee-pi-4a.dtb):
