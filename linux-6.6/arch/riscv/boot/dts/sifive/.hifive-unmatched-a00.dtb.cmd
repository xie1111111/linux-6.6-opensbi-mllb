savedcmd_arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dtb := gcc -E -Wp,-MMD,arch/riscv/boot/dts/sifive/.hifive-unmatched-a00.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/riscv/boot/dts/sifive/.hifive-unmatched-a00.dtb.dts.tmp arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dts ; ./scripts/dtc/dtc -o arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dtb -b 0 -iarch/riscv/boot/dts/sifive/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unique_unit_address -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg   -d arch/riscv/boot/dts/sifive/.hifive-unmatched-a00.dtb.d.dtc.tmp arch/riscv/boot/dts/sifive/.hifive-unmatched-a00.dtb.dts.tmp ; cat arch/riscv/boot/dts/sifive/.hifive-unmatched-a00.dtb.d.pre.tmp arch/riscv/boot/dts/sifive/.hifive-unmatched-a00.dtb.d.dtc.tmp > arch/riscv/boot/dts/sifive/.hifive-unmatched-a00.dtb.d

source_arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dtb := arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dts

deps_arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dtb := \
  arch/riscv/boot/dts/sifive/fu740-c000.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/sifive-fu740-prci.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/leds/common.h \
  scripts/dtc/include-prefixes/dt-bindings/pwm/pwm.h \

arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dtb: $(deps_arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dtb)

$(deps_arch/riscv/boot/dts/sifive/hifive-unmatched-a00.dtb):
