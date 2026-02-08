savedcmd_arch/riscv/boot/dts/microchip/mpfs-polarberry.dtb := gcc -E -Wp,-MMD,arch/riscv/boot/dts/microchip/.mpfs-polarberry.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/riscv/boot/dts/microchip/.mpfs-polarberry.dtb.dts.tmp arch/riscv/boot/dts/microchip/mpfs-polarberry.dts ; ./scripts/dtc/dtc -o arch/riscv/boot/dts/microchip/mpfs-polarberry.dtb -b 0 -iarch/riscv/boot/dts/microchip/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unique_unit_address -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg   -d arch/riscv/boot/dts/microchip/.mpfs-polarberry.dtb.d.dtc.tmp arch/riscv/boot/dts/microchip/.mpfs-polarberry.dtb.dts.tmp ; cat arch/riscv/boot/dts/microchip/.mpfs-polarberry.dtb.d.pre.tmp arch/riscv/boot/dts/microchip/.mpfs-polarberry.dtb.d.dtc.tmp > arch/riscv/boot/dts/microchip/.mpfs-polarberry.dtb.d

source_arch/riscv/boot/dts/microchip/mpfs-polarberry.dtb := arch/riscv/boot/dts/microchip/mpfs-polarberry.dts

deps_arch/riscv/boot/dts/microchip/mpfs-polarberry.dtb := \
  arch/riscv/boot/dts/microchip/mpfs.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/microchip,mpfs-clock.h \
  arch/riscv/boot/dts/microchip/mpfs-polarberry-fabric.dtsi \

arch/riscv/boot/dts/microchip/mpfs-polarberry.dtb: $(deps_arch/riscv/boot/dts/microchip/mpfs-polarberry.dtb)

$(deps_arch/riscv/boot/dts/microchip/mpfs-polarberry.dtb):
