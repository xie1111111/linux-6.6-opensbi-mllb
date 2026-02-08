savedcmd_arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dtb := gcc -E -Wp,-MMD,arch/riscv/boot/dts/starfive/.jh7100-beaglev-starlight.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/riscv/boot/dts/starfive/.jh7100-beaglev-starlight.dtb.dts.tmp arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dts ; ./scripts/dtc/dtc -o arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dtb -b 0 -iarch/riscv/boot/dts/starfive/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unique_unit_address -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -@  -d arch/riscv/boot/dts/starfive/.jh7100-beaglev-starlight.dtb.d.dtc.tmp arch/riscv/boot/dts/starfive/.jh7100-beaglev-starlight.dtb.dts.tmp ; cat arch/riscv/boot/dts/starfive/.jh7100-beaglev-starlight.dtb.d.pre.tmp arch/riscv/boot/dts/starfive/.jh7100-beaglev-starlight.dtb.d.dtc.tmp > arch/riscv/boot/dts/starfive/.jh7100-beaglev-starlight.dtb.d

source_arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dtb := arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dts

deps_arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dtb := \
  arch/riscv/boot/dts/starfive/jh7100-common.dtsi \
  arch/riscv/boot/dts/starfive/jh7100.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/starfive-jh7100.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/starfive-jh7100.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/leds/common.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/pinctrl-starfive-jh7100.h \

arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dtb: $(deps_arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dtb)

$(deps_arch/riscv/boot/dts/starfive/jh7100-beaglev-starlight.dtb):
