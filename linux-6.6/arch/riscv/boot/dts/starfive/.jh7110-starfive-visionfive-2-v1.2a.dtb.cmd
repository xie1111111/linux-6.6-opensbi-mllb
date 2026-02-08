savedcmd_arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dtb := gcc -E -Wp,-MMD,arch/riscv/boot/dts/starfive/.jh7110-starfive-visionfive-2-v1.2a.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/riscv/boot/dts/starfive/.jh7110-starfive-visionfive-2-v1.2a.dtb.dts.tmp arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dts ; ./scripts/dtc/dtc -o arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dtb -b 0 -iarch/riscv/boot/dts/starfive/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unique_unit_address -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -@  -d arch/riscv/boot/dts/starfive/.jh7110-starfive-visionfive-2-v1.2a.dtb.d.dtc.tmp arch/riscv/boot/dts/starfive/.jh7110-starfive-visionfive-2-v1.2a.dtb.dts.tmp ; cat arch/riscv/boot/dts/starfive/.jh7110-starfive-visionfive-2-v1.2a.dtb.d.pre.tmp arch/riscv/boot/dts/starfive/.jh7110-starfive-visionfive-2-v1.2a.dtb.d.dtc.tmp > arch/riscv/boot/dts/starfive/.jh7110-starfive-visionfive-2-v1.2a.dtb.d

source_arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dtb := arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dts

deps_arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dtb := \
  arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2.dtsi \
  arch/riscv/boot/dts/starfive/jh7110.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/starfive,jh7110-crg.h \
  scripts/dtc/include-prefixes/dt-bindings/power/starfive,jh7110-pmu.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/starfive,jh7110-crg.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \
  arch/riscv/boot/dts/starfive/jh7110-pinfunc.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \

arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dtb: $(deps_arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dtb)

$(deps_arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.2a.dtb):
