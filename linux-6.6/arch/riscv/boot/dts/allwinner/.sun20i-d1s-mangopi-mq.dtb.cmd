savedcmd_arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dtb := gcc -E -Wp,-MMD,arch/riscv/boot/dts/allwinner/.sun20i-d1s-mangopi-mq.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/riscv/boot/dts/allwinner/.sun20i-d1s-mangopi-mq.dtb.dts.tmp arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dts ; ./scripts/dtc/dtc -o arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dtb -b 0 -iarch/riscv/boot/dts/allwinner/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unique_unit_address -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg   -d arch/riscv/boot/dts/allwinner/.sun20i-d1s-mangopi-mq.dtb.d.dtc.tmp arch/riscv/boot/dts/allwinner/.sun20i-d1s-mangopi-mq.dtb.dts.tmp ; cat arch/riscv/boot/dts/allwinner/.sun20i-d1s-mangopi-mq.dtb.d.pre.tmp arch/riscv/boot/dts/allwinner/.sun20i-d1s-mangopi-mq.dtb.d.dtc.tmp > arch/riscv/boot/dts/allwinner/.sun20i-d1s-mangopi-mq.dtb.d

source_arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dtb := arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dts

deps_arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dtb := \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/leds/common.h \
  arch/riscv/boot/dts/allwinner/sun20i-d1s.dtsi \
  arch/riscv/boot/dts/allwinner/sunxi-d1s-t113.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun6i-rtc.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun8i-de2.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun8i-tcon-top.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun20i-d1-ccu.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun20i-d1-r-ccu.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/sun8i-de2.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/sun20i-d1-ccu.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/sun20i-d1-r-ccu.h \
  arch/riscv/boot/dts/allwinner/sun20i-common-regulators.dtsi \

arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dtb: $(deps_arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dtb)

$(deps_arch/riscv/boot/dts/allwinner/sun20i-d1s-mangopi-mq.dtb):
