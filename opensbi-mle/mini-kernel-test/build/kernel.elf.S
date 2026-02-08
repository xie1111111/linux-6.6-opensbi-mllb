
build/kernel.elf:     file format elf64-littleriscv


Disassembly of section .text:

0000000080200000 <_start>:
    80200000:	00012117          	auipc	sp,0x12
    80200004:	f1810113          	addi	sp,sp,-232 # 80211f18 <z>
    80200008:	cc747057          	vsetivli	zero,8,e8,mf2,ta,ma
    8020000c:	00001097          	auipc	ra,0x1
    80200010:	076080e7          	jalr	118(ra) # 80201082 <main>

0000000080200014 <shutdown>:
    80200014:	1141                	addi	sp,sp,-16
    80200016:	e406                	sd	ra,8(sp)
    80200018:	e022                	sd	s0,0(sp)
    8020001a:	0800                	addi	s0,sp,16
    8020001c:	4501                	li	a0,0
    8020001e:	4581                	li	a1,0
    80200020:	4601                	li	a2,0
    80200022:	48a1                	li	a7,8
    80200024:	00000073          	ecall
    80200028:	0001                	nop
    8020002a:	60a2                	ld	ra,8(sp)
    8020002c:	6402                	ld	s0,0(sp)
    8020002e:	0141                	addi	sp,sp,16
    80200030:	8082                	ret

0000000080200032 <sbi_ecall>:
    80200032:	7159                	addi	sp,sp,-112
    80200034:	f486                	sd	ra,104(sp)
    80200036:	f0a2                	sd	s0,96(sp)
    80200038:	1880                	addi	s0,sp,112
    8020003a:	fcc43023          	sd	a2,-64(s0)
    8020003e:	fad43c23          	sd	a3,-72(s0)
    80200042:	fae43823          	sd	a4,-80(s0)
    80200046:	faf43423          	sd	a5,-88(s0)
    8020004a:	fb043023          	sd	a6,-96(s0)
    8020004e:	f9143c23          	sd	a7,-104(s0)
    80200052:	87aa                	mv	a5,a0
    80200054:	fcf42623          	sw	a5,-52(s0)
    80200058:	87ae                	mv	a5,a1
    8020005a:	fcf42423          	sw	a5,-56(s0)
    8020005e:	fc043503          	ld	a0,-64(s0)
    80200062:	fb843583          	ld	a1,-72(s0)
    80200066:	fb043603          	ld	a2,-80(s0)
    8020006a:	fa843683          	ld	a3,-88(s0)
    8020006e:	fa043703          	ld	a4,-96(s0)
    80200072:	f9843783          	ld	a5,-104(s0)
    80200076:	fc842803          	lw	a6,-56(s0)
    8020007a:	fcc42883          	lw	a7,-52(s0)
    8020007e:	00000073          	ecall
    80200082:	87aa                	mv	a5,a0
    80200084:	fcf43823          	sd	a5,-48(s0)
    80200088:	87ae                	mv	a5,a1
    8020008a:	fcf43c23          	sd	a5,-40(s0)
    8020008e:	fd043783          	ld	a5,-48(s0)
    80200092:	fef43023          	sd	a5,-32(s0)
    80200096:	fd843783          	ld	a5,-40(s0)
    8020009a:	fef43423          	sd	a5,-24(s0)
    8020009e:	fe043703          	ld	a4,-32(s0)
    802000a2:	fe843783          	ld	a5,-24(s0)
    802000a6:	833a                	mv	t1,a4
    802000a8:	83be                	mv	t2,a5
    802000aa:	871a                	mv	a4,t1
    802000ac:	879e                	mv	a5,t2
    802000ae:	853a                	mv	a0,a4
    802000b0:	85be                	mv	a1,a5
    802000b2:	70a6                	ld	ra,104(sp)
    802000b4:	7406                	ld	s0,96(sp)
    802000b6:	6165                	addi	sp,sp,112
    802000b8:	8082                	ret

00000000802000ba <matmul>:
    802000ba:	715d                	addi	sp,sp,-80
    802000bc:	e486                	sd	ra,72(sp)
    802000be:	e0a2                	sd	s0,64(sp)
    802000c0:	fc4a                	sd	s2,56(sp)
    802000c2:	f84e                	sd	s3,48(sp)
    802000c4:	0880                	addi	s0,sp,80
    802000c6:	fca43423          	sd	a0,-56(s0)
    802000ca:	fcb43023          	sd	a1,-64(s0)
    802000ce:	fac43c23          	sd	a2,-72(s0)
    802000d2:	87b6                	mv	a5,a3
    802000d4:	faf42a23          	sw	a5,-76(s0)
    802000d8:	fc843603          	ld	a2,-56(s0)
    802000dc:	fc043683          	ld	a3,-64(s0)
    802000e0:	fb843703          	ld	a4,-72(s0)
    802000e4:	fb442783          	lw	a5,-76(s0)
    802000e8:	4881                	li	a7,0
    802000ea:	4801                	li	a6,0
    802000ec:	4581                	li	a1,0
    802000ee:	004d5537          	lui	a0,0x4d5
    802000f2:	c4550513          	addi	a0,a0,-955 # 4d4c45 <_start-0x7fd2b3bb>
    802000f6:	00000097          	auipc	ra,0x0
    802000fa:	f3c080e7          	jalr	-196(ra) # 80200032 <sbi_ecall>
    802000fe:	872a                	mv	a4,a0
    80200100:	87ae                	mv	a5,a1
    80200102:	fce43823          	sd	a4,-48(s0)
    80200106:	fcf43c23          	sd	a5,-40(s0)
    8020010a:	fd043703          	ld	a4,-48(s0)
    8020010e:	fd843783          	ld	a5,-40(s0)
    80200112:	893a                	mv	s2,a4
    80200114:	89be                	mv	s3,a5
    80200116:	874a                	mv	a4,s2
    80200118:	87ce                	mv	a5,s3
    8020011a:	853a                	mv	a0,a4
    8020011c:	85be                	mv	a1,a5
    8020011e:	60a6                	ld	ra,72(sp)
    80200120:	6406                	ld	s0,64(sp)
    80200122:	7962                	ld	s2,56(sp)
    80200124:	79c2                	ld	s3,48(sp)
    80200126:	6161                	addi	sp,sp,80
    80200128:	8082                	ret

000000008020012a <tensor_add>:
    8020012a:	715d                	addi	sp,sp,-80
    8020012c:	e486                	sd	ra,72(sp)
    8020012e:	e0a2                	sd	s0,64(sp)
    80200130:	fc4a                	sd	s2,56(sp)
    80200132:	f84e                	sd	s3,48(sp)
    80200134:	0880                	addi	s0,sp,80
    80200136:	fca43423          	sd	a0,-56(s0)
    8020013a:	fcb43023          	sd	a1,-64(s0)
    8020013e:	fac43c23          	sd	a2,-72(s0)
    80200142:	87b6                	mv	a5,a3
    80200144:	faf42a23          	sw	a5,-76(s0)
    80200148:	fc843603          	ld	a2,-56(s0)
    8020014c:	fc043683          	ld	a3,-64(s0)
    80200150:	fb843703          	ld	a4,-72(s0)
    80200154:	fb442783          	lw	a5,-76(s0)
    80200158:	4881                	li	a7,0
    8020015a:	4801                	li	a6,0
    8020015c:	45a1                	li	a1,8
    8020015e:	004d5537          	lui	a0,0x4d5
    80200162:	c4550513          	addi	a0,a0,-955 # 4d4c45 <_start-0x7fd2b3bb>
    80200166:	00000097          	auipc	ra,0x0
    8020016a:	ecc080e7          	jalr	-308(ra) # 80200032 <sbi_ecall>
    8020016e:	872a                	mv	a4,a0
    80200170:	87ae                	mv	a5,a1
    80200172:	fce43823          	sd	a4,-48(s0)
    80200176:	fcf43c23          	sd	a5,-40(s0)
    8020017a:	fd043703          	ld	a4,-48(s0)
    8020017e:	fd843783          	ld	a5,-40(s0)
    80200182:	893a                	mv	s2,a4
    80200184:	89be                	mv	s3,a5
    80200186:	874a                	mv	a4,s2
    80200188:	87ce                	mv	a5,s3
    8020018a:	853a                	mv	a0,a4
    8020018c:	85be                	mv	a1,a5
    8020018e:	60a6                	ld	ra,72(sp)
    80200190:	6406                	ld	s0,64(sp)
    80200192:	7962                	ld	s2,56(sp)
    80200194:	79c2                	ld	s3,48(sp)
    80200196:	6161                	addi	sp,sp,80
    80200198:	8082                	ret

000000008020019a <tensor_relu>:
    8020019a:	715d                	addi	sp,sp,-80
    8020019c:	e486                	sd	ra,72(sp)
    8020019e:	e0a2                	sd	s0,64(sp)
    802001a0:	fc4a                	sd	s2,56(sp)
    802001a2:	f84e                	sd	s3,48(sp)
    802001a4:	0880                	addi	s0,sp,80
    802001a6:	fca43423          	sd	a0,-56(s0)
    802001aa:	fcb43023          	sd	a1,-64(s0)
    802001ae:	87b2                	mv	a5,a2
    802001b0:	faf42e23          	sw	a5,-68(s0)
    802001b4:	fc843603          	ld	a2,-56(s0)
    802001b8:	fc043683          	ld	a3,-64(s0)
    802001bc:	fbc42703          	lw	a4,-68(s0)
    802001c0:	4881                	li	a7,0
    802001c2:	4801                	li	a6,0
    802001c4:	4781                	li	a5,0
    802001c6:	458d                	li	a1,3
    802001c8:	004d5537          	lui	a0,0x4d5
    802001cc:	c4550513          	addi	a0,a0,-955 # 4d4c45 <_start-0x7fd2b3bb>
    802001d0:	00000097          	auipc	ra,0x0
    802001d4:	e62080e7          	jalr	-414(ra) # 80200032 <sbi_ecall>
    802001d8:	872a                	mv	a4,a0
    802001da:	87ae                	mv	a5,a1
    802001dc:	fce43823          	sd	a4,-48(s0)
    802001e0:	fcf43c23          	sd	a5,-40(s0)
    802001e4:	fd043703          	ld	a4,-48(s0)
    802001e8:	fd843783          	ld	a5,-40(s0)
    802001ec:	893a                	mv	s2,a4
    802001ee:	89be                	mv	s3,a5
    802001f0:	874a                	mv	a4,s2
    802001f2:	87ce                	mv	a5,s3
    802001f4:	853a                	mv	a0,a4
    802001f6:	85be                	mv	a1,a5
    802001f8:	60a6                	ld	ra,72(sp)
    802001fa:	6406                	ld	s0,64(sp)
    802001fc:	7962                	ld	s2,56(sp)
    802001fe:	79c2                	ld	s3,48(sp)
    80200200:	6161                	addi	sp,sp,80
    80200202:	8082                	ret

0000000080200204 <matmul_rvv>:
    80200204:	7119                	addi	sp,sp,-128
    80200206:	fc86                	sd	ra,120(sp)
    80200208:	f8a2                	sd	s0,112(sp)
    8020020a:	0100                	addi	s0,sp,128
    8020020c:	c22022f3          	csrr	t0,vlenb
    80200210:	00229313          	slli	t1,t0,0x2
    80200214:	9316                	add	t1,t1,t0
    80200216:	40610133          	sub	sp,sp,t1
    8020021a:	c22028f3          	csrr	a7,vlenb
    8020021e:	586d                	li	a6,-5
    80200220:	03180833          	mul	a6,a6,a7
    80200224:	fb880813          	addi	a6,a6,-72
    80200228:	1841                	addi	a6,a6,-16
    8020022a:	9822                	add	a6,a6,s0
    8020022c:	00a83023          	sd	a0,0(a6)
    80200230:	c2202873          	csrr	a6,vlenb
    80200234:	556d                	li	a0,-5
    80200236:	03050533          	mul	a0,a0,a6
    8020023a:	fb050513          	addi	a0,a0,-80
    8020023e:	1541                	addi	a0,a0,-16
    80200240:	9522                	add	a0,a0,s0
    80200242:	e10c                	sd	a1,0(a0)
    80200244:	c2202573          	csrr	a0,vlenb
    80200248:	55ed                	li	a1,-5
    8020024a:	02a585b3          	mul	a1,a1,a0
    8020024e:	fa858593          	addi	a1,a1,-88
    80200252:	15c1                	addi	a1,a1,-16
    80200254:	95a2                	add	a1,a1,s0
    80200256:	e190                	sd	a2,0(a1)
    80200258:	85b6                	mv	a1,a3
    8020025a:	863a                	mv	a2,a4
    8020025c:	86be                	mv	a3,a5
    8020025e:	c2202773          	csrr	a4,vlenb
    80200262:	57ed                	li	a5,-5
    80200264:	02e787b3          	mul	a5,a5,a4
    80200268:	fa478793          	addi	a5,a5,-92
    8020026c:	17c1                	addi	a5,a5,-16
    8020026e:	97a2                	add	a5,a5,s0
    80200270:	872e                	mv	a4,a1
    80200272:	c398                	sw	a4,0(a5)
    80200274:	c2202773          	csrr	a4,vlenb
    80200278:	57ed                	li	a5,-5
    8020027a:	02e787b3          	mul	a5,a5,a4
    8020027e:	fa078793          	addi	a5,a5,-96
    80200282:	17c1                	addi	a5,a5,-16
    80200284:	97a2                	add	a5,a5,s0
    80200286:	8732                	mv	a4,a2
    80200288:	c398                	sw	a4,0(a5)
    8020028a:	c2202773          	csrr	a4,vlenb
    8020028e:	57ed                	li	a5,-5
    80200290:	02e787b3          	mul	a5,a5,a4
    80200294:	f9c78793          	addi	a5,a5,-100
    80200298:	17c1                	addi	a5,a5,-16
    8020029a:	97a2                	add	a5,a5,s0
    8020029c:	8736                	mv	a4,a3
    8020029e:	c398                	sw	a4,0(a5)
    802002a0:	c22027f3          	csrr	a5,vlenb
    802002a4:	40f007b3          	neg	a5,a5
    802002a8:	fd878793          	addi	a5,a5,-40
    802002ac:	17c1                	addi	a5,a5,-16
    802002ae:	97a2                	add	a5,a5,s0
    802002b0:	0c507757          	vsetvli	a4,zero,e8,mf8,ta,ma
    802002b4:	e398                	sd	a4,0(a5)
    802002b6:	fe042623          	sw	zero,-20(s0)
    802002ba:	a675                	j	80200666 <matmul_rvv+0x462>
    802002bc:	fe042423          	sw	zero,-24(s0)
    802002c0:	aeb5                	j	8020063c <matmul_rvv+0x438>
    802002c2:	c2202773          	csrr	a4,vlenb
    802002c6:	57ed                	li	a5,-5
    802002c8:	02e787b3          	mul	a5,a5,a4
    802002cc:	f9c78793          	addi	a5,a5,-100
    802002d0:	17c1                	addi	a5,a5,-16
    802002d2:	97a2                	add	a5,a5,s0
    802002d4:	fec42703          	lw	a4,-20(s0)
    802002d8:	439c                	lw	a5,0(a5)
    802002da:	02f707bb          	mulw	a5,a4,a5
    802002de:	2781                	sext.w	a5,a5
    802002e0:	00379713          	slli	a4,a5,0x3
    802002e4:	c22026f3          	csrr	a3,vlenb
    802002e8:	57ed                	li	a5,-5
    802002ea:	02d787b3          	mul	a5,a5,a3
    802002ee:	fb878793          	addi	a5,a5,-72
    802002f2:	17c1                	addi	a5,a5,-16
    802002f4:	97a2                	add	a5,a5,s0
    802002f6:	639c                	ld	a5,0(a5)
    802002f8:	97ba                	add	a5,a5,a4
    802002fa:	fef43023          	sd	a5,-32(s0)
    802002fe:	fe842783          	lw	a5,-24(s0)
    80200302:	00379713          	slli	a4,a5,0x3
    80200306:	c22026f3          	csrr	a3,vlenb
    8020030a:	57ed                	li	a5,-5
    8020030c:	02d787b3          	mul	a5,a5,a3
    80200310:	fb078793          	addi	a5,a5,-80
    80200314:	17c1                	addi	a5,a5,-16
    80200316:	97a2                	add	a5,a5,s0
    80200318:	639c                	ld	a5,0(a5)
    8020031a:	97ba                	add	a5,a5,a4
    8020031c:	fcf43c23          	sd	a5,-40(s0)
    80200320:	c2202773          	csrr	a4,vlenb
    80200324:	57ed                	li	a5,-5
    80200326:	02e787b3          	mul	a5,a5,a4
    8020032a:	f9c78793          	addi	a5,a5,-100
    8020032e:	17c1                	addi	a5,a5,-16
    80200330:	97a2                	add	a5,a5,s0
    80200332:	439c                	lw	a5,0(a5)
    80200334:	fcf42a23          	sw	a5,-44(s0)
    80200338:	c22027f3          	csrr	a5,vlenb
    8020033c:	40f007b3          	neg	a5,a5
    80200340:	1781                	addi	a5,a5,-32
    80200342:	17c1                	addi	a5,a5,-16
    80200344:	00878733          	add	a4,a5,s0
    80200348:	c22027f3          	csrr	a5,vlenb
    8020034c:	40f007b3          	neg	a5,a5
    80200350:	fd878793          	addi	a5,a5,-40
    80200354:	17c1                	addi	a5,a5,-16
    80200356:	97a2                	add	a5,a5,s0
    80200358:	639c                	ld	a5,0(a5)
    8020035a:	f20007d3          	fmv.d.x	fa5,zero
    8020035e:	0d87f057          	vsetvli	zero,a5,e64,m1,ta,ma
    80200362:	5e07d0d7          	vfmv.v.f	v1,fa5
    80200366:	028700a7          	vs1r.v	v1,(a4)
    8020036a:	c22027f3          	csrr	a5,vlenb
    8020036e:	0786                	slli	a5,a5,0x1
    80200370:	40f007b3          	neg	a5,a5
    80200374:	fd078793          	addi	a5,a5,-48
    80200378:	17c1                	addi	a5,a5,-16
    8020037a:	00878733          	add	a4,a5,s0
    8020037e:	c22027f3          	csrr	a5,vlenb
    80200382:	40f007b3          	neg	a5,a5
    80200386:	fd878793          	addi	a5,a5,-40
    8020038a:	17c1                	addi	a5,a5,-16
    8020038c:	97a2                	add	a5,a5,s0
    8020038e:	639c                	ld	a5,0(a5)
    80200390:	0d87f057          	vsetvli	zero,a5,e64,m1,ta,ma
    80200394:	5e07d0d7          	vfmv.v.f	v1,fa5
    80200398:	028700a7          	vs1r.v	v1,(a4)
    8020039c:	a255                	j	80200540 <matmul_rvv+0x33c>
    8020039e:	fd442683          	lw	a3,-44(s0)
    802003a2:	c2202773          	csrr	a4,vlenb
    802003a6:	00271793          	slli	a5,a4,0x2
    802003aa:	40f707b3          	sub	a5,a4,a5
    802003ae:	fc078793          	addi	a5,a5,-64
    802003b2:	17c1                	addi	a5,a5,-16
    802003b4:	97a2                	add	a5,a5,s0
    802003b6:	0c56f757          	vsetvli	a4,a3,e8,mf8,ta,ma
    802003ba:	e398                	sd	a4,0(a5)
    802003bc:	c22027f3          	csrr	a5,vlenb
    802003c0:	078a                	slli	a5,a5,0x2
    802003c2:	40f007b3          	neg	a5,a5
    802003c6:	fc078793          	addi	a5,a5,-64
    802003ca:	17c1                	addi	a5,a5,-16
    802003cc:	00878733          	add	a4,a5,s0
    802003d0:	fe043603          	ld	a2,-32(s0)
    802003d4:	c22026f3          	csrr	a3,vlenb
    802003d8:	00269793          	slli	a5,a3,0x2
    802003dc:	40f687b3          	sub	a5,a3,a5
    802003e0:	fc078793          	addi	a5,a5,-64
    802003e4:	17c1                	addi	a5,a5,-16
    802003e6:	97a2                	add	a5,a5,s0
    802003e8:	639c                	ld	a5,0(a5)
    802003ea:	0d87f057          	vsetvli	zero,a5,e64,m1,ta,ma
    802003ee:	02067087          	vle64.v	v1,(a2)
    802003f2:	028700a7          	vs1r.v	v1,(a4)
    802003f6:	c2202773          	csrr	a4,vlenb
    802003fa:	57ed                	li	a5,-5
    802003fc:	02e787b3          	mul	a5,a5,a4
    80200400:	fa078793          	addi	a5,a5,-96
    80200404:	17c1                	addi	a5,a5,-16
    80200406:	97a2                	add	a5,a5,s0
    80200408:	439c                	lw	a5,0(a5)
    8020040a:	078e                	slli	a5,a5,0x3
    8020040c:	85be                	mv	a1,a5
    8020040e:	c2202773          	csrr	a4,vlenb
    80200412:	57ed                	li	a5,-5
    80200414:	02e787b3          	mul	a5,a5,a4
    80200418:	fc078793          	addi	a5,a5,-64
    8020041c:	17c1                	addi	a5,a5,-16
    8020041e:	00878733          	add	a4,a5,s0
    80200422:	fd843603          	ld	a2,-40(s0)
    80200426:	c22026f3          	csrr	a3,vlenb
    8020042a:	00269793          	slli	a5,a3,0x2
    8020042e:	40f687b3          	sub	a5,a3,a5
    80200432:	fc078793          	addi	a5,a5,-64
    80200436:	17c1                	addi	a5,a5,-16
    80200438:	97a2                	add	a5,a5,s0
    8020043a:	639c                	ld	a5,0(a5)
    8020043c:	0d87f057          	vsetvli	zero,a5,e64,m1,ta,ma
    80200440:	0ab67087          	vlse64.v	v1,(a2),a1
    80200444:	028700a7          	vs1r.v	v1,(a4)
    80200448:	c22027f3          	csrr	a5,vlenb
    8020044c:	40f007b3          	neg	a5,a5
    80200450:	1781                	addi	a5,a5,-32
    80200452:	17c1                	addi	a5,a5,-16
    80200454:	00878733          	add	a4,a5,s0
    80200458:	c22027f3          	csrr	a5,vlenb
    8020045c:	40f007b3          	neg	a5,a5
    80200460:	1781                	addi	a5,a5,-32
    80200462:	17c1                	addi	a5,a5,-16
    80200464:	00878633          	add	a2,a5,s0
    80200468:	c22027f3          	csrr	a5,vlenb
    8020046c:	078a                	slli	a5,a5,0x2
    8020046e:	40f007b3          	neg	a5,a5
    80200472:	fc078793          	addi	a5,a5,-64
    80200476:	17c1                	addi	a5,a5,-16
    80200478:	00878533          	add	a0,a5,s0
    8020047c:	c22026f3          	csrr	a3,vlenb
    80200480:	57ed                	li	a5,-5
    80200482:	02d787b3          	mul	a5,a5,a3
    80200486:	fc078793          	addi	a5,a5,-64
    8020048a:	17c1                	addi	a5,a5,-16
    8020048c:	008785b3          	add	a1,a5,s0
    80200490:	c22026f3          	csrr	a3,vlenb
    80200494:	00269793          	slli	a5,a3,0x2
    80200498:	40f687b3          	sub	a5,a3,a5
    8020049c:	fc078793          	addi	a5,a5,-64
    802004a0:	17c1                	addi	a5,a5,-16
    802004a2:	97a2                	add	a5,a5,s0
    802004a4:	02857187          	vl1re64.v	v3,(a0)
    802004a8:	0285f107          	vl1re64.v	v2,(a1)
    802004ac:	02867087          	vl1re64.v	v1,(a2)
    802004b0:	639c                	ld	a5,0(a5)
    802004b2:	0987f057          	vsetvli	zero,a5,e64,m1,tu,ma
    802004b6:	b22190d7          	vfmacc.vv	v1,v3,v2
    802004ba:	028700a7          	vs1r.v	v1,(a4)
    802004be:	fd442683          	lw	a3,-44(s0)
    802004c2:	c2202773          	csrr	a4,vlenb
    802004c6:	00271793          	slli	a5,a4,0x2
    802004ca:	40f707b3          	sub	a5,a4,a5
    802004ce:	fc078793          	addi	a5,a5,-64
    802004d2:	17c1                	addi	a5,a5,-16
    802004d4:	97a2                	add	a5,a5,s0
    802004d6:	639c                	ld	a5,0(a5)
    802004d8:	2781                	sext.w	a5,a5
    802004da:	40f687bb          	subw	a5,a3,a5
    802004de:	2781                	sext.w	a5,a5
    802004e0:	fcf42a23          	sw	a5,-44(s0)
    802004e4:	c2202773          	csrr	a4,vlenb
    802004e8:	00271793          	slli	a5,a4,0x2
    802004ec:	40f707b3          	sub	a5,a4,a5
    802004f0:	fc078793          	addi	a5,a5,-64
    802004f4:	17c1                	addi	a5,a5,-16
    802004f6:	97a2                	add	a5,a5,s0
    802004f8:	639c                	ld	a5,0(a5)
    802004fa:	078e                	slli	a5,a5,0x3
    802004fc:	fe043703          	ld	a4,-32(s0)
    80200500:	97ba                	add	a5,a5,a4
    80200502:	fef43023          	sd	a5,-32(s0)
    80200506:	c2202773          	csrr	a4,vlenb
    8020050a:	57ed                	li	a5,-5
    8020050c:	02e787b3          	mul	a5,a5,a4
    80200510:	fa078793          	addi	a5,a5,-96
    80200514:	17c1                	addi	a5,a5,-16
    80200516:	97a2                	add	a5,a5,s0
    80200518:	4394                	lw	a3,0(a5)
    8020051a:	c2202773          	csrr	a4,vlenb
    8020051e:	00271793          	slli	a5,a4,0x2
    80200522:	40f707b3          	sub	a5,a4,a5
    80200526:	fc078793          	addi	a5,a5,-64
    8020052a:	17c1                	addi	a5,a5,-16
    8020052c:	97a2                	add	a5,a5,s0
    8020052e:	639c                	ld	a5,0(a5)
    80200530:	02f687b3          	mul	a5,a3,a5
    80200534:	078e                	slli	a5,a5,0x3
    80200536:	fd843703          	ld	a4,-40(s0)
    8020053a:	97ba                	add	a5,a5,a4
    8020053c:	fcf43c23          	sd	a5,-40(s0)
    80200540:	fd442783          	lw	a5,-44(s0)
    80200544:	2781                	sext.w	a5,a5
    80200546:	e4f04ce3          	bgtz	a5,8020039e <matmul_rvv+0x19a>
    8020054a:	c2202773          	csrr	a4,vlenb
    8020054e:	00271793          	slli	a5,a4,0x2
    80200552:	40f707b3          	sub	a5,a4,a5
    80200556:	fd078793          	addi	a5,a5,-48
    8020055a:	17c1                	addi	a5,a5,-16
    8020055c:	00878733          	add	a4,a5,s0
    80200560:	c22027f3          	csrr	a5,vlenb
    80200564:	40f007b3          	neg	a5,a5
    80200568:	1781                	addi	a5,a5,-32
    8020056a:	17c1                	addi	a5,a5,-16
    8020056c:	00878633          	add	a2,a5,s0
    80200570:	c22027f3          	csrr	a5,vlenb
    80200574:	0786                	slli	a5,a5,0x1
    80200576:	40f007b3          	neg	a5,a5
    8020057a:	fd078793          	addi	a5,a5,-48
    8020057e:	17c1                	addi	a5,a5,-16
    80200580:	008786b3          	add	a3,a5,s0
    80200584:	c22027f3          	csrr	a5,vlenb
    80200588:	40f007b3          	neg	a5,a5
    8020058c:	fd878793          	addi	a5,a5,-40
    80200590:	17c1                	addi	a5,a5,-16
    80200592:	97a2                	add	a5,a5,s0
    80200594:	02867087          	vl1re64.v	v1,(a2)
    80200598:	0286f107          	vl1re64.v	v2,(a3)
    8020059c:	639c                	ld	a5,0(a5)
    8020059e:	0d87f057          	vsetvli	zero,a5,e64,m1,ta,ma
    802005a2:	061110d7          	vfredusum.vs	v1,v1,v2
    802005a6:	028700a7          	vs1r.v	v1,(a4)
    802005aa:	c2202773          	csrr	a4,vlenb
    802005ae:	00271793          	slli	a5,a4,0x2
    802005b2:	40f707b3          	sub	a5,a4,a5
    802005b6:	fc878793          	addi	a5,a5,-56
    802005ba:	17c1                	addi	a5,a5,-16
    802005bc:	00878733          	add	a4,a5,s0
    802005c0:	c22026f3          	csrr	a3,vlenb
    802005c4:	00269793          	slli	a5,a3,0x2
    802005c8:	40f687b3          	sub	a5,a3,a5
    802005cc:	fd078793          	addi	a5,a5,-48
    802005d0:	17c1                	addi	a5,a5,-16
    802005d2:	97a2                	add	a5,a5,s0
    802005d4:	239c                	fld	fa5,0(a5)
    802005d6:	a31c                	fsd	fa5,0(a4)
    802005d8:	c2202773          	csrr	a4,vlenb
    802005dc:	57ed                	li	a5,-5
    802005de:	02e787b3          	mul	a5,a5,a4
    802005e2:	fa078793          	addi	a5,a5,-96
    802005e6:	17c1                	addi	a5,a5,-16
    802005e8:	97a2                	add	a5,a5,s0
    802005ea:	fec42703          	lw	a4,-20(s0)
    802005ee:	439c                	lw	a5,0(a5)
    802005f0:	02f707bb          	mulw	a5,a4,a5
    802005f4:	2781                	sext.w	a5,a5
    802005f6:	fe842703          	lw	a4,-24(s0)
    802005fa:	9fb9                	addw	a5,a5,a4
    802005fc:	2781                	sext.w	a5,a5
    802005fe:	00379713          	slli	a4,a5,0x3
    80200602:	c22026f3          	csrr	a3,vlenb
    80200606:	57ed                	li	a5,-5
    80200608:	02d787b3          	mul	a5,a5,a3
    8020060c:	fa878793          	addi	a5,a5,-88
    80200610:	17c1                	addi	a5,a5,-16
    80200612:	97a2                	add	a5,a5,s0
    80200614:	639c                	ld	a5,0(a5)
    80200616:	00e786b3          	add	a3,a5,a4
    8020061a:	c2202773          	csrr	a4,vlenb
    8020061e:	00271793          	slli	a5,a4,0x2
    80200622:	40f707b3          	sub	a5,a4,a5
    80200626:	fc878793          	addi	a5,a5,-56
    8020062a:	17c1                	addi	a5,a5,-16
    8020062c:	97a2                	add	a5,a5,s0
    8020062e:	239c                	fld	fa5,0(a5)
    80200630:	a29c                	fsd	fa5,0(a3)
    80200632:	fe842783          	lw	a5,-24(s0)
    80200636:	2785                	addiw	a5,a5,1
    80200638:	fef42423          	sw	a5,-24(s0)
    8020063c:	c2202773          	csrr	a4,vlenb
    80200640:	57ed                	li	a5,-5
    80200642:	02e787b3          	mul	a5,a5,a4
    80200646:	fa078793          	addi	a5,a5,-96
    8020064a:	17c1                	addi	a5,a5,-16
    8020064c:	97a2                	add	a5,a5,s0
    8020064e:	fe842703          	lw	a4,-24(s0)
    80200652:	439c                	lw	a5,0(a5)
    80200654:	2701                	sext.w	a4,a4
    80200656:	2781                	sext.w	a5,a5
    80200658:	c6f745e3          	blt	a4,a5,802002c2 <matmul_rvv+0xbe>
    8020065c:	fec42783          	lw	a5,-20(s0)
    80200660:	2785                	addiw	a5,a5,1
    80200662:	fef42623          	sw	a5,-20(s0)
    80200666:	c2202773          	csrr	a4,vlenb
    8020066a:	57ed                	li	a5,-5
    8020066c:	02e787b3          	mul	a5,a5,a4
    80200670:	fa478793          	addi	a5,a5,-92
    80200674:	17c1                	addi	a5,a5,-16
    80200676:	97a2                	add	a5,a5,s0
    80200678:	fec42703          	lw	a4,-20(s0)
    8020067c:	439c                	lw	a5,0(a5)
    8020067e:	2701                	sext.w	a4,a4
    80200680:	2781                	sext.w	a5,a5
    80200682:	c2f74de3          	blt	a4,a5,802002bc <matmul_rvv+0xb8>
    80200686:	0001                	nop
    80200688:	0001                	nop
    8020068a:	c22022f3          	csrr	t0,vlenb
    8020068e:	00229313          	slli	t1,t0,0x2
    80200692:	9316                	add	t1,t1,t0
    80200694:	911a                	add	sp,sp,t1
    80200696:	70e6                	ld	ra,120(sp)
    80200698:	7446                	ld	s0,112(sp)
    8020069a:	6109                	addi	sp,sp,128
    8020069c:	8082                	ret

000000008020069e <putchar>:
    8020069e:	1101                	addi	sp,sp,-32
    802006a0:	ec06                	sd	ra,24(sp)
    802006a2:	e822                	sd	s0,16(sp)
    802006a4:	1000                	addi	s0,sp,32
    802006a6:	87aa                	mv	a5,a0
    802006a8:	fef42623          	sw	a5,-20(s0)
    802006ac:	fec42783          	lw	a5,-20(s0)
    802006b0:	853e                	mv	a0,a5
    802006b2:	4581                	li	a1,0
    802006b4:	4601                	li	a2,0
    802006b6:	4885                	li	a7,1
    802006b8:	00000073          	ecall
    802006bc:	4785                	li	a5,1
    802006be:	853e                	mv	a0,a5
    802006c0:	60e2                	ld	ra,24(sp)
    802006c2:	6442                	ld	s0,16(sp)
    802006c4:	6105                	addi	sp,sp,32
    802006c6:	8082                	ret

00000000802006c8 <puts>:
    802006c8:	1101                	addi	sp,sp,-32
    802006ca:	ec06                	sd	ra,24(sp)
    802006cc:	e822                	sd	s0,16(sp)
    802006ce:	1000                	addi	s0,sp,32
    802006d0:	fea43423          	sd	a0,-24(s0)
    802006d4:	a015                	j	802006f8 <puts+0x30>
    802006d6:	fe843783          	ld	a5,-24(s0)
    802006da:	0007c783          	lbu	a5,0(a5)
    802006de:	2781                	sext.w	a5,a5
    802006e0:	853e                	mv	a0,a5
    802006e2:	00000097          	auipc	ra,0x0
    802006e6:	fbc080e7          	jalr	-68(ra) # 8020069e <putchar>
    802006ea:	87aa                	mv	a5,a0
    802006ec:	873e                	mv	a4,a5
    802006ee:	fe843783          	ld	a5,-24(s0)
    802006f2:	97ba                	add	a5,a5,a4
    802006f4:	fef43423          	sd	a5,-24(s0)
    802006f8:	fe843783          	ld	a5,-24(s0)
    802006fc:	0007c783          	lbu	a5,0(a5)
    80200700:	fbf9                	bnez	a5,802006d6 <puts+0xe>
    80200702:	4785                	li	a5,1
    80200704:	853e                	mv	a0,a5
    80200706:	60e2                	ld	ra,24(sp)
    80200708:	6442                	ld	s0,16(sp)
    8020070a:	6105                	addi	sp,sp,32
    8020070c:	8082                	ret

000000008020070e <clear>:
    8020070e:	1141                	addi	sp,sp,-16
    80200710:	e406                	sd	ra,8(sp)
    80200712:	e022                	sd	s0,0(sp)
    80200714:	0800                	addi	s0,sp,16
    80200716:	00001517          	auipc	a0,0x1
    8020071a:	d0a50513          	addi	a0,a0,-758 # 80201420 <rodata_start+0x2>
    8020071e:	00000097          	auipc	ra,0x0
    80200722:	faa080e7          	jalr	-86(ra) # 802006c8 <puts>
    80200726:	0001                	nop
    80200728:	0001                	nop
    8020072a:	60a2                	ld	ra,8(sp)
    8020072c:	6402                	ld	s0,0(sp)
    8020072e:	0141                	addi	sp,sp,16
    80200730:	8082                	ret

0000000080200732 <itoa>:
    80200732:	7139                	addi	sp,sp,-64
    80200734:	fc06                	sd	ra,56(sp)
    80200736:	f822                	sd	s0,48(sp)
    80200738:	0080                	addi	s0,sp,64
    8020073a:	87aa                	mv	a5,a0
    8020073c:	fcb43023          	sd	a1,-64(s0)
    80200740:	fcf42623          	sw	a5,-52(s0)
    80200744:	fe042623          	sw	zero,-20(s0)
    80200748:	fcc42783          	lw	a5,-52(s0)
    8020074c:	2781                	sext.w	a5,a5
    8020074e:	efd5                	bnez	a5,8020080a <itoa+0xd8>
    80200750:	fec42783          	lw	a5,-20(s0)
    80200754:	0017871b          	addiw	a4,a5,1
    80200758:	fee42623          	sw	a4,-20(s0)
    8020075c:	873e                	mv	a4,a5
    8020075e:	fc043783          	ld	a5,-64(s0)
    80200762:	97ba                	add	a5,a5,a4
    80200764:	03000713          	li	a4,48
    80200768:	00e78023          	sb	a4,0(a5)
    8020076c:	fec42783          	lw	a5,-20(s0)
    80200770:	fc043703          	ld	a4,-64(s0)
    80200774:	97ba                	add	a5,a5,a4
    80200776:	00078023          	sb	zero,0(a5)
    8020077a:	aa31                	j	80200896 <itoa+0x164>
    8020077c:	fcc42783          	lw	a5,-52(s0)
    80200780:	873e                	mv	a4,a5
    80200782:	0007069b          	sext.w	a3,a4
    80200786:	666667b7          	lui	a5,0x66666
    8020078a:	66778793          	addi	a5,a5,1639 # 66666667 <_start-0x19b99999>
    8020078e:	02f687b3          	mul	a5,a3,a5
    80200792:	9381                	srli	a5,a5,0x20
    80200794:	4027d79b          	sraiw	a5,a5,0x2
    80200798:	86be                	mv	a3,a5
    8020079a:	41f7579b          	sraiw	a5,a4,0x1f
    8020079e:	40f687bb          	subw	a5,a3,a5
    802007a2:	86be                	mv	a3,a5
    802007a4:	87b6                	mv	a5,a3
    802007a6:	0027979b          	slliw	a5,a5,0x2
    802007aa:	9fb5                	addw	a5,a5,a3
    802007ac:	0017979b          	slliw	a5,a5,0x1
    802007b0:	40f707bb          	subw	a5,a4,a5
    802007b4:	fcf42e23          	sw	a5,-36(s0)
    802007b8:	fdc42783          	lw	a5,-36(s0)
    802007bc:	0ff7f713          	zext.b	a4,a5
    802007c0:	fec42783          	lw	a5,-20(s0)
    802007c4:	0017869b          	addiw	a3,a5,1
    802007c8:	fed42623          	sw	a3,-20(s0)
    802007cc:	86be                	mv	a3,a5
    802007ce:	fc043783          	ld	a5,-64(s0)
    802007d2:	97b6                	add	a5,a5,a3
    802007d4:	0307071b          	addiw	a4,a4,48
    802007d8:	0ff77713          	zext.b	a4,a4
    802007dc:	00e78023          	sb	a4,0(a5)
    802007e0:	fcc42783          	lw	a5,-52(s0)
    802007e4:	86be                	mv	a3,a5
    802007e6:	0006871b          	sext.w	a4,a3
    802007ea:	666667b7          	lui	a5,0x66666
    802007ee:	66778793          	addi	a5,a5,1639 # 66666667 <_start-0x19b99999>
    802007f2:	02f707b3          	mul	a5,a4,a5
    802007f6:	9381                	srli	a5,a5,0x20
    802007f8:	4027d79b          	sraiw	a5,a5,0x2
    802007fc:	873e                	mv	a4,a5
    802007fe:	41f6d79b          	sraiw	a5,a3,0x1f
    80200802:	40f707bb          	subw	a5,a4,a5
    80200806:	fcf42623          	sw	a5,-52(s0)
    8020080a:	fcc42783          	lw	a5,-52(s0)
    8020080e:	2781                	sext.w	a5,a5
    80200810:	f7b5                	bnez	a5,8020077c <itoa+0x4a>
    80200812:	fec42783          	lw	a5,-20(s0)
    80200816:	fc043703          	ld	a4,-64(s0)
    8020081a:	97ba                	add	a5,a5,a4
    8020081c:	00078023          	sb	zero,0(a5)
    80200820:	fe042423          	sw	zero,-24(s0)
    80200824:	fec42783          	lw	a5,-20(s0)
    80200828:	37fd                	addiw	a5,a5,-1
    8020082a:	fef42223          	sw	a5,-28(s0)
    8020082e:	a899                	j	80200884 <itoa+0x152>
    80200830:	fe842783          	lw	a5,-24(s0)
    80200834:	fc043703          	ld	a4,-64(s0)
    80200838:	97ba                	add	a5,a5,a4
    8020083a:	0007c783          	lbu	a5,0(a5)
    8020083e:	fef401a3          	sb	a5,-29(s0)
    80200842:	fe442783          	lw	a5,-28(s0)
    80200846:	fc043703          	ld	a4,-64(s0)
    8020084a:	973e                	add	a4,a4,a5
    8020084c:	fe842783          	lw	a5,-24(s0)
    80200850:	fc043683          	ld	a3,-64(s0)
    80200854:	97b6                	add	a5,a5,a3
    80200856:	00074703          	lbu	a4,0(a4)
    8020085a:	00e78023          	sb	a4,0(a5)
    8020085e:	fe442783          	lw	a5,-28(s0)
    80200862:	fc043703          	ld	a4,-64(s0)
    80200866:	97ba                	add	a5,a5,a4
    80200868:	fe344703          	lbu	a4,-29(s0)
    8020086c:	00e78023          	sb	a4,0(a5)
    80200870:	fe842783          	lw	a5,-24(s0)
    80200874:	2785                	addiw	a5,a5,1
    80200876:	fef42423          	sw	a5,-24(s0)
    8020087a:	fe442783          	lw	a5,-28(s0)
    8020087e:	37fd                	addiw	a5,a5,-1
    80200880:	fef42223          	sw	a5,-28(s0)
    80200884:	fe842783          	lw	a5,-24(s0)
    80200888:	873e                	mv	a4,a5
    8020088a:	fe442783          	lw	a5,-28(s0)
    8020088e:	2701                	sext.w	a4,a4
    80200890:	2781                	sext.w	a5,a5
    80200892:	f8f74fe3          	blt	a4,a5,80200830 <itoa+0xfe>
    80200896:	0001                	nop
    80200898:	70e2                	ld	ra,56(sp)
    8020089a:	7442                	ld	s0,48(sp)
    8020089c:	6121                	addi	sp,sp,64
    8020089e:	8082                	ret

00000000802008a0 <print_c>:
    802008a0:	7139                	addi	sp,sp,-64
    802008a2:	fc06                	sd	ra,56(sp)
    802008a4:	f822                	sd	s0,48(sp)
    802008a6:	0080                	addi	s0,sp,64
    802008a8:	87aa                	mv	a5,a0
    802008aa:	fcf42623          	sw	a5,-52(s0)
    802008ae:	fd840713          	addi	a4,s0,-40
    802008b2:	fcc42783          	lw	a5,-52(s0)
    802008b6:	85ba                	mv	a1,a4
    802008b8:	853e                	mv	a0,a5
    802008ba:	00000097          	auipc	ra,0x0
    802008be:	e78080e7          	jalr	-392(ra) # 80200732 <itoa>
    802008c2:	fd840793          	addi	a5,s0,-40
    802008c6:	853e                	mv	a0,a5
    802008c8:	00000097          	auipc	ra,0x0
    802008cc:	e00080e7          	jalr	-512(ra) # 802006c8 <puts>
    802008d0:	00001517          	auipc	a0,0x1
    802008d4:	b5850513          	addi	a0,a0,-1192 # 80201428 <rodata_start+0xa>
    802008d8:	00000097          	auipc	ra,0x0
    802008dc:	df0080e7          	jalr	-528(ra) # 802006c8 <puts>
    802008e0:	0001                	nop
    802008e2:	0001                	nop
    802008e4:	70e2                	ld	ra,56(sp)
    802008e6:	7442                	ld	s0,48(sp)
    802008e8:	6121                	addi	sp,sp,64
    802008ea:	8082                	ret

00000000802008ec <print_float16_array>:
    802008ec:	711d                	addi	sp,sp,-96
    802008ee:	ec86                	sd	ra,88(sp)
    802008f0:	e8a2                	sd	s0,80(sp)
    802008f2:	1080                	addi	s0,sp,96
    802008f4:	faa43c23          	sd	a0,-72(s0)
    802008f8:	87ae                	mv	a5,a1
    802008fa:	fac43423          	sd	a2,-88(s0)
    802008fe:	faf42a23          	sw	a5,-76(s0)
    80200902:	fa843503          	ld	a0,-88(s0)
    80200906:	00000097          	auipc	ra,0x0
    8020090a:	dc2080e7          	jalr	-574(ra) # 802006c8 <puts>
    8020090e:	00001517          	auipc	a0,0x1
    80200912:	b2250513          	addi	a0,a0,-1246 # 80201430 <rodata_start+0x12>
    80200916:	00000097          	auipc	ra,0x0
    8020091a:	db2080e7          	jalr	-590(ra) # 802006c8 <puts>
    8020091e:	fe042623          	sw	zero,-20(s0)
    80200922:	a299                	j	80200a68 <print_float16_array+0x17c>
    80200924:	fec42783          	lw	a5,-20(s0)
    80200928:	078a                	slli	a5,a5,0x2
    8020092a:	fb843703          	ld	a4,-72(s0)
    8020092e:	97ba                	add	a5,a5,a4
    80200930:	0007a787          	flw	fa5,0(a5)
    80200934:	fef42227          	fsw	fa5,-28(s0)
    80200938:	fe442787          	flw	fa5,-28(s0)
    8020093c:	c00797d3          	fcvt.w.s	a5,fa5,rtz
    80200940:	fef42423          	sw	a5,-24(s0)
    80200944:	fe842783          	lw	a5,-24(s0)
    80200948:	d007f7d3          	fcvt.s.w	fa5,a5
    8020094c:	fe442707          	flw	fa4,-28(s0)
    80200950:	08f77753          	fsub.s	fa4,fa4,fa5
    80200954:	00001797          	auipc	a5,0x1
    80200958:	cdc78793          	addi	a5,a5,-804 # 80201630 <rodata_start+0x212>
    8020095c:	0007a787          	flw	fa5,0(a5)
    80200960:	10f777d3          	fmul.s	fa5,fa4,fa5
    80200964:	c00797d3          	fcvt.w.s	a5,fa5,rtz
    80200968:	fef42023          	sw	a5,-32(s0)
    8020096c:	fe842783          	lw	a5,-24(s0)
    80200970:	2781                	sext.w	a5,a5
    80200972:	0007de63          	bgez	a5,8020098e <print_float16_array+0xa2>
    80200976:	02d00513          	li	a0,45
    8020097a:	00000097          	auipc	ra,0x0
    8020097e:	d24080e7          	jalr	-732(ra) # 8020069e <putchar>
    80200982:	fe842783          	lw	a5,-24(s0)
    80200986:	40f007bb          	negw	a5,a5
    8020098a:	fef42423          	sw	a5,-24(s0)
    8020098e:	fc840713          	addi	a4,s0,-56
    80200992:	fe842783          	lw	a5,-24(s0)
    80200996:	85ba                	mv	a1,a4
    80200998:	853e                	mv	a0,a5
    8020099a:	00000097          	auipc	ra,0x0
    8020099e:	d98080e7          	jalr	-616(ra) # 80200732 <itoa>
    802009a2:	fc840793          	addi	a5,s0,-56
    802009a6:	853e                	mv	a0,a5
    802009a8:	00000097          	auipc	ra,0x0
    802009ac:	d20080e7          	jalr	-736(ra) # 802006c8 <puts>
    802009b0:	02e00513          	li	a0,46
    802009b4:	00000097          	auipc	ra,0x0
    802009b8:	cea080e7          	jalr	-790(ra) # 8020069e <putchar>
    802009bc:	fe042783          	lw	a5,-32(s0)
    802009c0:	0007871b          	sext.w	a4,a5
    802009c4:	47a5                	li	a5,9
    802009c6:	00e7c863          	blt	a5,a4,802009d6 <print_float16_array+0xea>
    802009ca:	03000513          	li	a0,48
    802009ce:	00000097          	auipc	ra,0x0
    802009d2:	cd0080e7          	jalr	-816(ra) # 8020069e <putchar>
    802009d6:	fc840713          	addi	a4,s0,-56
    802009da:	fe042783          	lw	a5,-32(s0)
    802009de:	85ba                	mv	a1,a4
    802009e0:	853e                	mv	a0,a5
    802009e2:	00000097          	auipc	ra,0x0
    802009e6:	d50080e7          	jalr	-688(ra) # 80200732 <itoa>
    802009ea:	fc840793          	addi	a5,s0,-56
    802009ee:	853e                	mv	a0,a5
    802009f0:	00000097          	auipc	ra,0x0
    802009f4:	cd8080e7          	jalr	-808(ra) # 802006c8 <puts>
    802009f8:	fb442783          	lw	a5,-76(s0)
    802009fc:	37fd                	addiw	a5,a5,-1
    802009fe:	2781                	sext.w	a5,a5
    80200a00:	fec42703          	lw	a4,-20(s0)
    80200a04:	2701                	sext.w	a4,a4
    80200a06:	00f75a63          	bge	a4,a5,80200a1a <print_float16_array+0x12e>
    80200a0a:	00001517          	auipc	a0,0x1
    80200a0e:	a2e50513          	addi	a0,a0,-1490 # 80201438 <rodata_start+0x1a>
    80200a12:	00000097          	auipc	ra,0x0
    80200a16:	cb6080e7          	jalr	-842(ra) # 802006c8 <puts>
    80200a1a:	fec42783          	lw	a5,-20(s0)
    80200a1e:	0007869b          	sext.w	a3,a5
    80200a22:	66666737          	lui	a4,0x66666
    80200a26:	66770713          	addi	a4,a4,1639 # 66666667 <_start-0x19b99999>
    80200a2a:	02e68733          	mul	a4,a3,a4
    80200a2e:	9301                	srli	a4,a4,0x20
    80200a30:	4017571b          	sraiw	a4,a4,0x1
    80200a34:	86ba                	mv	a3,a4
    80200a36:	41f7d71b          	sraiw	a4,a5,0x1f
    80200a3a:	40e6873b          	subw	a4,a3,a4
    80200a3e:	86ba                	mv	a3,a4
    80200a40:	8736                	mv	a4,a3
    80200a42:	0027171b          	slliw	a4,a4,0x2
    80200a46:	9f35                	addw	a4,a4,a3
    80200a48:	9f99                	subw	a5,a5,a4
    80200a4a:	2781                	sext.w	a5,a5
    80200a4c:	eb89                	bnez	a5,80200a5e <print_float16_array+0x172>
    80200a4e:	00001517          	auipc	a0,0x1
    80200a52:	9da50513          	addi	a0,a0,-1574 # 80201428 <rodata_start+0xa>
    80200a56:	00000097          	auipc	ra,0x0
    80200a5a:	c72080e7          	jalr	-910(ra) # 802006c8 <puts>
    80200a5e:	fec42783          	lw	a5,-20(s0)
    80200a62:	2785                	addiw	a5,a5,1
    80200a64:	fef42623          	sw	a5,-20(s0)
    80200a68:	fec42783          	lw	a5,-20(s0)
    80200a6c:	873e                	mv	a4,a5
    80200a6e:	fb442783          	lw	a5,-76(s0)
    80200a72:	2701                	sext.w	a4,a4
    80200a74:	2781                	sext.w	a5,a5
    80200a76:	eaf747e3          	blt	a4,a5,80200924 <print_float16_array+0x38>
    80200a7a:	00001517          	auipc	a0,0x1
    80200a7e:	9c650513          	addi	a0,a0,-1594 # 80201440 <rodata_start+0x22>
    80200a82:	00000097          	auipc	ra,0x0
    80200a86:	c46080e7          	jalr	-954(ra) # 802006c8 <puts>
    80200a8a:	0001                	nop
    80200a8c:	0001                	nop
    80200a8e:	60e6                	ld	ra,88(sp)
    80200a90:	6446                	ld	s0,80(sp)
    80200a92:	6125                	addi	sp,sp,96
    80200a94:	8082                	ret

0000000080200a96 <print_k>:
    80200a96:	7159                	addi	sp,sp,-112
    80200a98:	f486                	sd	ra,104(sp)
    80200a9a:	f0a2                	sd	s0,96(sp)
    80200a9c:	1880                	addi	s0,sp,112
    80200a9e:	faa43423          	sd	a0,-88(s0)
    80200aa2:	87ae                	mv	a5,a1
    80200aa4:	f8c43c23          	sd	a2,-104(s0)
    80200aa8:	faf42223          	sw	a5,-92(s0)
    80200aac:	f9843503          	ld	a0,-104(s0)
    80200ab0:	00000097          	auipc	ra,0x0
    80200ab4:	c18080e7          	jalr	-1000(ra) # 802006c8 <puts>
    80200ab8:	00001517          	auipc	a0,0x1
    80200abc:	97850513          	addi	a0,a0,-1672 # 80201430 <rodata_start+0x12>
    80200ac0:	00000097          	auipc	ra,0x0
    80200ac4:	c08080e7          	jalr	-1016(ra) # 802006c8 <puts>
    80200ac8:	fe042623          	sw	zero,-20(s0)
    80200acc:	a8e1                	j	80200ba4 <print_k+0x10e>
    80200ace:	fec42783          	lw	a5,-20(s0)
    80200ad2:	078e                	slli	a5,a5,0x3
    80200ad4:	fa843703          	ld	a4,-88(s0)
    80200ad8:	97ba                	add	a5,a5,a4
    80200ada:	639c                	ld	a5,0(a5)
    80200adc:	fef43023          	sd	a5,-32(s0)
    80200ae0:	fe043783          	ld	a5,-32(s0)
    80200ae4:	fef42423          	sw	a5,-24(s0)
    80200ae8:	fe842783          	lw	a5,-24(s0)
    80200aec:	2781                	sext.w	a5,a5
    80200aee:	0007de63          	bgez	a5,80200b0a <print_k+0x74>
    80200af2:	02d00513          	li	a0,45
    80200af6:	00000097          	auipc	ra,0x0
    80200afa:	ba8080e7          	jalr	-1112(ra) # 8020069e <putchar>
    80200afe:	fe842783          	lw	a5,-24(s0)
    80200b02:	40f007bb          	negw	a5,a5
    80200b06:	fef42423          	sw	a5,-24(s0)
    80200b0a:	fb840713          	addi	a4,s0,-72
    80200b0e:	fe842783          	lw	a5,-24(s0)
    80200b12:	85ba                	mv	a1,a4
    80200b14:	853e                	mv	a0,a5
    80200b16:	00000097          	auipc	ra,0x0
    80200b1a:	c1c080e7          	jalr	-996(ra) # 80200732 <itoa>
    80200b1e:	fb840793          	addi	a5,s0,-72
    80200b22:	853e                	mv	a0,a5
    80200b24:	00000097          	auipc	ra,0x0
    80200b28:	ba4080e7          	jalr	-1116(ra) # 802006c8 <puts>
    80200b2c:	fa442783          	lw	a5,-92(s0)
    80200b30:	37fd                	addiw	a5,a5,-1
    80200b32:	2781                	sext.w	a5,a5
    80200b34:	fec42703          	lw	a4,-20(s0)
    80200b38:	2701                	sext.w	a4,a4
    80200b3a:	00f75a63          	bge	a4,a5,80200b4e <print_k+0xb8>
    80200b3e:	00001517          	auipc	a0,0x1
    80200b42:	8fa50513          	addi	a0,a0,-1798 # 80201438 <rodata_start+0x1a>
    80200b46:	00000097          	auipc	ra,0x0
    80200b4a:	b82080e7          	jalr	-1150(ra) # 802006c8 <puts>
    80200b4e:	fec42783          	lw	a5,-20(s0)
    80200b52:	0007869b          	sext.w	a3,a5
    80200b56:	66666737          	lui	a4,0x66666
    80200b5a:	66770713          	addi	a4,a4,1639 # 66666667 <_start-0x19b99999>
    80200b5e:	02e68733          	mul	a4,a3,a4
    80200b62:	9301                	srli	a4,a4,0x20
    80200b64:	4017571b          	sraiw	a4,a4,0x1
    80200b68:	86ba                	mv	a3,a4
    80200b6a:	41f7d71b          	sraiw	a4,a5,0x1f
    80200b6e:	40e6873b          	subw	a4,a3,a4
    80200b72:	86ba                	mv	a3,a4
    80200b74:	8736                	mv	a4,a3
    80200b76:	0027171b          	slliw	a4,a4,0x2
    80200b7a:	9f35                	addw	a4,a4,a3
    80200b7c:	9f99                	subw	a5,a5,a4
    80200b7e:	2781                	sext.w	a5,a5
    80200b80:	ef89                	bnez	a5,80200b9a <print_k+0x104>
    80200b82:	fec42783          	lw	a5,-20(s0)
    80200b86:	2781                	sext.w	a5,a5
    80200b88:	cb89                	beqz	a5,80200b9a <print_k+0x104>
    80200b8a:	00001517          	auipc	a0,0x1
    80200b8e:	89e50513          	addi	a0,a0,-1890 # 80201428 <rodata_start+0xa>
    80200b92:	00000097          	auipc	ra,0x0
    80200b96:	b36080e7          	jalr	-1226(ra) # 802006c8 <puts>
    80200b9a:	fec42783          	lw	a5,-20(s0)
    80200b9e:	2785                	addiw	a5,a5,1
    80200ba0:	fef42623          	sw	a5,-20(s0)
    80200ba4:	fec42783          	lw	a5,-20(s0)
    80200ba8:	873e                	mv	a4,a5
    80200baa:	fa442783          	lw	a5,-92(s0)
    80200bae:	2701                	sext.w	a4,a4
    80200bb0:	2781                	sext.w	a5,a5
    80200bb2:	f0f74ee3          	blt	a4,a5,80200ace <print_k+0x38>
    80200bb6:	00001517          	auipc	a0,0x1
    80200bba:	88a50513          	addi	a0,a0,-1910 # 80201440 <rodata_start+0x22>
    80200bbe:	00000097          	auipc	ra,0x0
    80200bc2:	b0a080e7          	jalr	-1270(ra) # 802006c8 <puts>
    80200bc6:	0001                	nop
    80200bc8:	0001                	nop
    80200bca:	70a6                	ld	ra,104(sp)
    80200bcc:	7406                	ld	s0,96(sp)
    80200bce:	6165                	addi	sp,sp,112
    80200bd0:	8082                	ret

0000000080200bd2 <print_tensor_data>:
    80200bd2:	1101                	addi	sp,sp,-32
    80200bd4:	ec06                	sd	ra,24(sp)
    80200bd6:	e822                	sd	s0,16(sp)
    80200bd8:	1000                	addi	s0,sp,32
    80200bda:	fea43423          	sd	a0,-24(s0)
    80200bde:	feb43023          	sd	a1,-32(s0)
    80200be2:	fe843783          	ld	a5,-24(s0)
    80200be6:	639c                	ld	a5,0(a5)
    80200be8:	c385                	beqz	a5,80200c08 <print_tensor_data+0x36>
    80200bea:	fe843783          	ld	a5,-24(s0)
    80200bee:	6398                	ld	a4,0(a5)
    80200bf0:	fe843783          	ld	a5,-24(s0)
    80200bf4:	4f9c                	lw	a5,24(a5)
    80200bf6:	fe043603          	ld	a2,-32(s0)
    80200bfa:	85be                	mv	a1,a5
    80200bfc:	853a                	mv	a0,a4
    80200bfe:	00000097          	auipc	ra,0x0
    80200c02:	e98080e7          	jalr	-360(ra) # 80200a96 <print_k>
    80200c06:	a839                	j	80200c24 <print_tensor_data+0x52>
    80200c08:	fe043503          	ld	a0,-32(s0)
    80200c0c:	00000097          	auipc	ra,0x0
    80200c10:	abc080e7          	jalr	-1348(ra) # 802006c8 <puts>
    80200c14:	00001517          	auipc	a0,0x1
    80200c18:	83450513          	addi	a0,a0,-1996 # 80201448 <rodata_start+0x2a>
    80200c1c:	00000097          	auipc	ra,0x0
    80200c20:	aac080e7          	jalr	-1364(ra) # 802006c8 <puts>
    80200c24:	0001                	nop
    80200c26:	60e2                	ld	ra,24(sp)
    80200c28:	6442                	ld	s0,16(sp)
    80200c2a:	6105                	addi	sp,sp,32
    80200c2c:	8082                	ret

0000000080200c2e <vec_add_rvv>:
    80200c2e:	7139                	addi	sp,sp,-64
    80200c30:	fc06                	sd	ra,56(sp)
    80200c32:	f822                	sd	s0,48(sp)
    80200c34:	0080                	addi	s0,sp,64
    80200c36:	c22022f3          	csrr	t0,vlenb
    80200c3a:	4319                	li	t1,6
    80200c3c:	02530333          	mul	t1,t1,t0
    80200c40:	40610133          	sub	sp,sp,t1
    80200c44:	c2202773          	csrr	a4,vlenb
    80200c48:	57e9                	li	a5,-6
    80200c4a:	02e787b3          	mul	a5,a5,a4
    80200c4e:	17a1                	addi	a5,a5,-24
    80200c50:	17c1                	addi	a5,a5,-16
    80200c52:	97a2                	add	a5,a5,s0
    80200c54:	e388                	sd	a0,0(a5)
    80200c56:	c2202773          	csrr	a4,vlenb
    80200c5a:	57e9                	li	a5,-6
    80200c5c:	02e787b3          	mul	a5,a5,a4
    80200c60:	1781                	addi	a5,a5,-32
    80200c62:	17c1                	addi	a5,a5,-16
    80200c64:	97a2                	add	a5,a5,s0
    80200c66:	e38c                	sd	a1,0(a5)
    80200c68:	c2202773          	csrr	a4,vlenb
    80200c6c:	57e9                	li	a5,-6
    80200c6e:	02e787b3          	mul	a5,a5,a4
    80200c72:	fd878793          	addi	a5,a5,-40
    80200c76:	17c1                	addi	a5,a5,-16
    80200c78:	97a2                	add	a5,a5,s0
    80200c7a:	e390                	sd	a2,0(a5)
    80200c7c:	c2202773          	csrr	a4,vlenb
    80200c80:	57e9                	li	a5,-6
    80200c82:	02e787b3          	mul	a5,a5,a4
    80200c86:	fd078793          	addi	a5,a5,-48
    80200c8a:	17c1                	addi	a5,a5,-16
    80200c8c:	97a2                	add	a5,a5,s0
    80200c8e:	e394                	sd	a3,0(a5)
    80200c90:	aa45                	j	80200e40 <vec_add_rvv+0x212>
    80200c92:	c22027f3          	csrr	a5,vlenb
    80200c96:	0786                	slli	a5,a5,0x1
    80200c98:	40f007b3          	neg	a5,a5
    80200c9c:	17c1                	addi	a5,a5,-16
    80200c9e:	17c1                	addi	a5,a5,-16
    80200ca0:	00878733          	add	a4,a5,s0
    80200ca4:	c22026f3          	csrr	a3,vlenb
    80200ca8:	57e9                	li	a5,-6
    80200caa:	02d787b3          	mul	a5,a5,a3
    80200cae:	1781                	addi	a5,a5,-32
    80200cb0:	17c1                	addi	a5,a5,-16
    80200cb2:	97a2                	add	a5,a5,s0
    80200cb4:	639c                	ld	a5,0(a5)
    80200cb6:	fe843683          	ld	a3,-24(s0)
    80200cba:	0d16f057          	vsetvli	zero,a3,e32,m2,ta,ma
    80200cbe:	0207e107          	vle32.v	v2,(a5)
    80200cc2:	22870127          	vs2r.v	v2,(a4)
    80200cc6:	c22027f3          	csrr	a5,vlenb
    80200cca:	078a                	slli	a5,a5,0x2
    80200ccc:	40f007b3          	neg	a5,a5
    80200cd0:	17c1                	addi	a5,a5,-16
    80200cd2:	17c1                	addi	a5,a5,-16
    80200cd4:	00878733          	add	a4,a5,s0
    80200cd8:	c22026f3          	csrr	a3,vlenb
    80200cdc:	57e9                	li	a5,-6
    80200cde:	02d787b3          	mul	a5,a5,a3
    80200ce2:	fd878793          	addi	a5,a5,-40
    80200ce6:	17c1                	addi	a5,a5,-16
    80200ce8:	97a2                	add	a5,a5,s0
    80200cea:	639c                	ld	a5,0(a5)
    80200cec:	fe843683          	ld	a3,-24(s0)
    80200cf0:	0d16f057          	vsetvli	zero,a3,e32,m2,ta,ma
    80200cf4:	0207e107          	vle32.v	v2,(a5)
    80200cf8:	22870127          	vs2r.v	v2,(a4)
    80200cfc:	c2202773          	csrr	a4,vlenb
    80200d00:	57e9                	li	a5,-6
    80200d02:	02e787b3          	mul	a5,a5,a4
    80200d06:	17c1                	addi	a5,a5,-16
    80200d08:	17c1                	addi	a5,a5,-16
    80200d0a:	00878733          	add	a4,a5,s0
    80200d0e:	c22027f3          	csrr	a5,vlenb
    80200d12:	0786                	slli	a5,a5,0x1
    80200d14:	40f007b3          	neg	a5,a5
    80200d18:	17c1                	addi	a5,a5,-16
    80200d1a:	17c1                	addi	a5,a5,-16
    80200d1c:	008786b3          	add	a3,a5,s0
    80200d20:	c22027f3          	csrr	a5,vlenb
    80200d24:	078a                	slli	a5,a5,0x2
    80200d26:	40f007b3          	neg	a5,a5
    80200d2a:	17c1                	addi	a5,a5,-16
    80200d2c:	17c1                	addi	a5,a5,-16
    80200d2e:	97a2                	add	a5,a5,s0
    80200d30:	2286e207          	vl2re32.v	v4,(a3)
    80200d34:	2287e107          	vl2re32.v	v2,(a5)
    80200d38:	fe843783          	ld	a5,-24(s0)
    80200d3c:	0d17f057          	vsetvli	zero,a5,e32,m2,ta,ma
    80200d40:	02410157          	vadd.vv	v2,v4,v2
    80200d44:	22870127          	vs2r.v	v2,(a4)
    80200d48:	c2202773          	csrr	a4,vlenb
    80200d4c:	57e9                	li	a5,-6
    80200d4e:	02e787b3          	mul	a5,a5,a4
    80200d52:	17a1                	addi	a5,a5,-24
    80200d54:	17c1                	addi	a5,a5,-16
    80200d56:	97a2                	add	a5,a5,s0
    80200d58:	6398                	ld	a4,0(a5)
    80200d5a:	c22026f3          	csrr	a3,vlenb
    80200d5e:	57e9                	li	a5,-6
    80200d60:	02d787b3          	mul	a5,a5,a3
    80200d64:	17c1                	addi	a5,a5,-16
    80200d66:	17c1                	addi	a5,a5,-16
    80200d68:	97a2                	add	a5,a5,s0
    80200d6a:	2287e107          	vl2re32.v	v2,(a5)
    80200d6e:	fe843783          	ld	a5,-24(s0)
    80200d72:	0d17f057          	vsetvli	zero,a5,e32,m2,ta,ma
    80200d76:	02076127          	vse32.v	v2,(a4)
    80200d7a:	c2202773          	csrr	a4,vlenb
    80200d7e:	57e9                	li	a5,-6
    80200d80:	02e787b3          	mul	a5,a5,a4
    80200d84:	fd078793          	addi	a5,a5,-48
    80200d88:	17c1                	addi	a5,a5,-16
    80200d8a:	00878733          	add	a4,a5,s0
    80200d8e:	c22026f3          	csrr	a3,vlenb
    80200d92:	57e9                	li	a5,-6
    80200d94:	02d787b3          	mul	a5,a5,a3
    80200d98:	fd078793          	addi	a5,a5,-48
    80200d9c:	17c1                	addi	a5,a5,-16
    80200d9e:	97a2                	add	a5,a5,s0
    80200da0:	6394                	ld	a3,0(a5)
    80200da2:	fe843783          	ld	a5,-24(s0)
    80200da6:	40f687b3          	sub	a5,a3,a5
    80200daa:	e31c                	sd	a5,0(a4)
    80200dac:	fe843783          	ld	a5,-24(s0)
    80200db0:	00279693          	slli	a3,a5,0x2
    80200db4:	c2202773          	csrr	a4,vlenb
    80200db8:	57e9                	li	a5,-6
    80200dba:	02e787b3          	mul	a5,a5,a4
    80200dbe:	1781                	addi	a5,a5,-32
    80200dc0:	17c1                	addi	a5,a5,-16
    80200dc2:	00878733          	add	a4,a5,s0
    80200dc6:	c2202673          	csrr	a2,vlenb
    80200dca:	57e9                	li	a5,-6
    80200dcc:	02c787b3          	mul	a5,a5,a2
    80200dd0:	1781                	addi	a5,a5,-32
    80200dd2:	17c1                	addi	a5,a5,-16
    80200dd4:	97a2                	add	a5,a5,s0
    80200dd6:	639c                	ld	a5,0(a5)
    80200dd8:	97b6                	add	a5,a5,a3
    80200dda:	e31c                	sd	a5,0(a4)
    80200ddc:	fe843783          	ld	a5,-24(s0)
    80200de0:	00279693          	slli	a3,a5,0x2
    80200de4:	c2202773          	csrr	a4,vlenb
    80200de8:	57e9                	li	a5,-6
    80200dea:	02e787b3          	mul	a5,a5,a4
    80200dee:	fd878793          	addi	a5,a5,-40
    80200df2:	17c1                	addi	a5,a5,-16
    80200df4:	00878733          	add	a4,a5,s0
    80200df8:	c2202673          	csrr	a2,vlenb
    80200dfc:	57e9                	li	a5,-6
    80200dfe:	02c787b3          	mul	a5,a5,a2
    80200e02:	fd878793          	addi	a5,a5,-40
    80200e06:	17c1                	addi	a5,a5,-16
    80200e08:	97a2                	add	a5,a5,s0
    80200e0a:	639c                	ld	a5,0(a5)
    80200e0c:	97b6                	add	a5,a5,a3
    80200e0e:	e31c                	sd	a5,0(a4)
    80200e10:	fe843783          	ld	a5,-24(s0)
    80200e14:	00279693          	slli	a3,a5,0x2
    80200e18:	c2202773          	csrr	a4,vlenb
    80200e1c:	57e9                	li	a5,-6
    80200e1e:	02e787b3          	mul	a5,a5,a4
    80200e22:	17a1                	addi	a5,a5,-24
    80200e24:	17c1                	addi	a5,a5,-16
    80200e26:	00878733          	add	a4,a5,s0
    80200e2a:	c2202673          	csrr	a2,vlenb
    80200e2e:	57e9                	li	a5,-6
    80200e30:	02c787b3          	mul	a5,a5,a2
    80200e34:	17a1                	addi	a5,a5,-24
    80200e36:	17c1                	addi	a5,a5,-16
    80200e38:	97a2                	add	a5,a5,s0
    80200e3a:	639c                	ld	a5,0(a5)
    80200e3c:	97b6                	add	a5,a5,a3
    80200e3e:	e31c                	sd	a5,0(a4)
    80200e40:	c2202773          	csrr	a4,vlenb
    80200e44:	57e9                	li	a5,-6
    80200e46:	02e787b3          	mul	a5,a5,a4
    80200e4a:	fd078793          	addi	a5,a5,-48
    80200e4e:	17c1                	addi	a5,a5,-16
    80200e50:	97a2                	add	a5,a5,s0
    80200e52:	639c                	ld	a5,0(a5)
    80200e54:	0c77f7d7          	vsetvli	a5,a5,e8,mf2,ta,ma
    80200e58:	fef43423          	sd	a5,-24(s0)
    80200e5c:	fe843783          	ld	a5,-24(s0)
    80200e60:	e20799e3          	bnez	a5,80200c92 <vec_add_rvv+0x64>
    80200e64:	0001                	nop
    80200e66:	0001                	nop
    80200e68:	c22022f3          	csrr	t0,vlenb
    80200e6c:	4319                	li	t1,6
    80200e6e:	02530333          	mul	t1,t1,t0
    80200e72:	911a                	add	sp,sp,t1
    80200e74:	70e2                	ld	ra,56(sp)
    80200e76:	7442                	ld	s0,48(sp)
    80200e78:	6121                	addi	sp,sp,64
    80200e7a:	8082                	ret

0000000080200e7c <vec_add_real>:
    80200e7c:	7139                	addi	sp,sp,-64
    80200e7e:	fc06                	sd	ra,56(sp)
    80200e80:	f822                	sd	s0,48(sp)
    80200e82:	0080                	addi	s0,sp,64
    80200e84:	fca43c23          	sd	a0,-40(s0)
    80200e88:	fcb43823          	sd	a1,-48(s0)
    80200e8c:	fcc43423          	sd	a2,-56(s0)
    80200e90:	fcd43023          	sd	a3,-64(s0)
    80200e94:	fe043423          	sd	zero,-24(s0)
    80200e98:	a82d                	j	80200ed2 <vec_add_real+0x56>
    80200e9a:	fe843783          	ld	a5,-24(s0)
    80200e9e:	078a                	slli	a5,a5,0x2
    80200ea0:	fd043703          	ld	a4,-48(s0)
    80200ea4:	97ba                	add	a5,a5,a4
    80200ea6:	4394                	lw	a3,0(a5)
    80200ea8:	fe843783          	ld	a5,-24(s0)
    80200eac:	078a                	slli	a5,a5,0x2
    80200eae:	fc843703          	ld	a4,-56(s0)
    80200eb2:	97ba                	add	a5,a5,a4
    80200eb4:	4398                	lw	a4,0(a5)
    80200eb6:	fe843783          	ld	a5,-24(s0)
    80200eba:	078a                	slli	a5,a5,0x2
    80200ebc:	fd843603          	ld	a2,-40(s0)
    80200ec0:	97b2                	add	a5,a5,a2
    80200ec2:	9f35                	addw	a4,a4,a3
    80200ec4:	2701                	sext.w	a4,a4
    80200ec6:	c398                	sw	a4,0(a5)
    80200ec8:	fe843783          	ld	a5,-24(s0)
    80200ecc:	0785                	addi	a5,a5,1
    80200ece:	fef43423          	sd	a5,-24(s0)
    80200ed2:	fe843703          	ld	a4,-24(s0)
    80200ed6:	fc043783          	ld	a5,-64(s0)
    80200eda:	fcf760e3          	bltu	a4,a5,80200e9a <vec_add_real+0x1e>
    80200ede:	0001                	nop
    80200ee0:	0001                	nop
    80200ee2:	70e2                	ld	ra,56(sp)
    80200ee4:	7442                	ld	s0,48(sp)
    80200ee6:	6121                	addi	sp,sp,64
    80200ee8:	8082                	ret

0000000080200eea <print_vec>:
    80200eea:	7139                	addi	sp,sp,-64
    80200eec:	fc06                	sd	ra,56(sp)
    80200eee:	f822                	sd	s0,48(sp)
    80200ef0:	0080                	addi	s0,sp,64
    80200ef2:	fca43c23          	sd	a0,-40(s0)
    80200ef6:	fcb43823          	sd	a1,-48(s0)
    80200efa:	fcc43423          	sd	a2,-56(s0)
    80200efe:	fc843503          	ld	a0,-56(s0)
    80200f02:	fffff097          	auipc	ra,0xfffff
    80200f06:	7c6080e7          	jalr	1990(ra) # 802006c8 <puts>
    80200f0a:	fe043423          	sd	zero,-24(s0)
    80200f0e:	a831                	j	80200f2a <print_vec+0x40>
    80200f10:	00000517          	auipc	a0,0x0
    80200f14:	54850513          	addi	a0,a0,1352 # 80201458 <rodata_start+0x3a>
    80200f18:	fffff097          	auipc	ra,0xfffff
    80200f1c:	7b0080e7          	jalr	1968(ra) # 802006c8 <puts>
    80200f20:	fe843783          	ld	a5,-24(s0)
    80200f24:	0785                	addi	a5,a5,1
    80200f26:	fef43423          	sd	a5,-24(s0)
    80200f2a:	fe843703          	ld	a4,-24(s0)
    80200f2e:	fd043783          	ld	a5,-48(s0)
    80200f32:	fcf76fe3          	bltu	a4,a5,80200f10 <print_vec+0x26>
    80200f36:	00000517          	auipc	a0,0x0
    80200f3a:	52a50513          	addi	a0,a0,1322 # 80201460 <rodata_start+0x42>
    80200f3e:	fffff097          	auipc	ra,0xfffff
    80200f42:	78a080e7          	jalr	1930(ra) # 802006c8 <puts>
    80200f46:	0001                	nop
    80200f48:	0001                	nop
    80200f4a:	70e2                	ld	ra,56(sp)
    80200f4c:	7442                	ld	s0,48(sp)
    80200f4e:	6121                	addi	sp,sp,64
    80200f50:	8082                	ret

0000000080200f52 <test_main>:
    80200f52:	1101                	addi	sp,sp,-32
    80200f54:	ec06                	sd	ra,24(sp)
    80200f56:	e822                	sd	s0,16(sp)
    80200f58:	1000                	addi	s0,sp,32
    80200f5a:	46a9                	li	a3,10
    80200f5c:	00001617          	auipc	a2,0x1
    80200f60:	f8c60613          	addi	a2,a2,-116 # 80201ee8 <y>
    80200f64:	00001597          	auipc	a1,0x1
    80200f68:	f5c58593          	addi	a1,a1,-164 # 80201ec0 <x>
    80200f6c:	00011517          	auipc	a0,0x11
    80200f70:	fac50513          	addi	a0,a0,-84 # 80211f18 <z>
    80200f74:	00000097          	auipc	ra,0x0
    80200f78:	cba080e7          	jalr	-838(ra) # 80200c2e <vec_add_rvv>
    80200f7c:	46a9                	li	a3,10
    80200f7e:	00001617          	auipc	a2,0x1
    80200f82:	f6a60613          	addi	a2,a2,-150 # 80201ee8 <y>
    80200f86:	00001597          	auipc	a1,0x1
    80200f8a:	f3a58593          	addi	a1,a1,-198 # 80201ec0 <x>
    80200f8e:	00011517          	auipc	a0,0x11
    80200f92:	fb250513          	addi	a0,a0,-78 # 80211f40 <z_real>
    80200f96:	00000097          	auipc	ra,0x0
    80200f9a:	ee6080e7          	jalr	-282(ra) # 80200e7c <vec_add_real>
    80200f9e:	00000617          	auipc	a2,0x0
    80200fa2:	4ca60613          	addi	a2,a2,1226 # 80201468 <rodata_start+0x4a>
    80200fa6:	45a9                	li	a1,10
    80200fa8:	00001517          	auipc	a0,0x1
    80200fac:	f1850513          	addi	a0,a0,-232 # 80201ec0 <x>
    80200fb0:	00000097          	auipc	ra,0x0
    80200fb4:	f3a080e7          	jalr	-198(ra) # 80200eea <print_vec>
    80200fb8:	00000617          	auipc	a2,0x0
    80200fbc:	4b860613          	addi	a2,a2,1208 # 80201470 <rodata_start+0x52>
    80200fc0:	45a9                	li	a1,10
    80200fc2:	00001517          	auipc	a0,0x1
    80200fc6:	f2650513          	addi	a0,a0,-218 # 80201ee8 <y>
    80200fca:	00000097          	auipc	ra,0x0
    80200fce:	f20080e7          	jalr	-224(ra) # 80200eea <print_vec>
    80200fd2:	fe043423          	sd	zero,-24(s0)
    80200fd6:	a0b5                	j	80201042 <test_main+0xf0>
    80200fd8:	00011717          	auipc	a4,0x11
    80200fdc:	f4070713          	addi	a4,a4,-192 # 80211f18 <z>
    80200fe0:	fe843783          	ld	a5,-24(s0)
    80200fe4:	078a                	slli	a5,a5,0x2
    80200fe6:	97ba                	add	a5,a5,a4
    80200fe8:	4398                	lw	a4,0(a5)
    80200fea:	00011697          	auipc	a3,0x11
    80200fee:	f5668693          	addi	a3,a3,-170 # 80211f40 <z_real>
    80200ff2:	fe843783          	ld	a5,-24(s0)
    80200ff6:	078a                	slli	a5,a5,0x2
    80200ff8:	97b6                	add	a5,a5,a3
    80200ffa:	439c                	lw	a5,0(a5)
    80200ffc:	02f70e63          	beq	a4,a5,80201038 <test_main+0xe6>
    80201000:	00000617          	auipc	a2,0x0
    80201004:	47860613          	addi	a2,a2,1144 # 80201478 <rodata_start+0x5a>
    80201008:	45a9                	li	a1,10
    8020100a:	00011517          	auipc	a0,0x11
    8020100e:	f0e50513          	addi	a0,a0,-242 # 80211f18 <z>
    80201012:	00000097          	auipc	ra,0x0
    80201016:	ed8080e7          	jalr	-296(ra) # 80200eea <print_vec>
    8020101a:	00000617          	auipc	a2,0x0
    8020101e:	46660613          	addi	a2,a2,1126 # 80201480 <rodata_start+0x62>
    80201022:	45a9                	li	a1,10
    80201024:	00011517          	auipc	a0,0x11
    80201028:	f1c50513          	addi	a0,a0,-228 # 80211f40 <z_real>
    8020102c:	00000097          	auipc	ra,0x0
    80201030:	ebe080e7          	jalr	-322(ra) # 80200eea <print_vec>
    80201034:	57fd                	li	a5,-1
    80201036:	a089                	j	80201078 <test_main+0x126>
    80201038:	fe843783          	ld	a5,-24(s0)
    8020103c:	0785                	addi	a5,a5,1
    8020103e:	fef43423          	sd	a5,-24(s0)
    80201042:	fe843703          	ld	a4,-24(s0)
    80201046:	47a5                	li	a5,9
    80201048:	f8e7f8e3          	bgeu	a5,a4,80200fd8 <test_main+0x86>
    8020104c:	00000617          	auipc	a2,0x0
    80201050:	42c60613          	addi	a2,a2,1068 # 80201478 <rodata_start+0x5a>
    80201054:	45a9                	li	a1,10
    80201056:	00011517          	auipc	a0,0x11
    8020105a:	ec250513          	addi	a0,a0,-318 # 80211f18 <z>
    8020105e:	00000097          	auipc	ra,0x0
    80201062:	e8c080e7          	jalr	-372(ra) # 80200eea <print_vec>
    80201066:	00000517          	auipc	a0,0x0
    8020106a:	42a50513          	addi	a0,a0,1066 # 80201490 <rodata_start+0x72>
    8020106e:	fffff097          	auipc	ra,0xfffff
    80201072:	65a080e7          	jalr	1626(ra) # 802006c8 <puts>
    80201076:	4781                	li	a5,0
    80201078:	853e                	mv	a0,a5
    8020107a:	60e2                	ld	ra,24(sp)
    8020107c:	6442                	ld	s0,16(sp)
    8020107e:	6105                	addi	sp,sp,32
    80201080:	8082                	ret

0000000080201082 <main>:
    80201082:	7101                	addi	sp,sp,-512
    80201084:	ff86                	sd	ra,504(sp)
    80201086:	fba2                	sd	s0,496(sp)
    80201088:	0400                	addi	s0,sp,512
    8020108a:	87aa                	mv	a5,a0
    8020108c:	872e                	mv	a4,a1
    8020108e:	e0f42623          	sw	a5,-500(s0)
    80201092:	87ba                	mv	a5,a4
    80201094:	e0f42423          	sw	a5,-504(s0)
    80201098:	e0c42783          	lw	a5,-500(s0)
    8020109c:	fef42623          	sw	a5,-20(s0)
    802010a0:	e0842783          	lw	a5,-504(s0)
    802010a4:	fef42423          	sw	a5,-24(s0)
    802010a8:	00000797          	auipc	a5,0x0
    802010ac:	49078793          	addi	a5,a5,1168 # 80201538 <rodata_start+0x11a>
    802010b0:	f7040693          	addi	a3,s0,-144
    802010b4:	863e                	mv	a2,a5
    802010b6:	07800713          	li	a4,120
    802010ba:	0c0777d7          	vsetvli	a5,a4,e8,m1,ta,ma
    802010be:	0c07f057          	vsetvli	zero,a5,e8,m1,ta,ma
    802010c2:	02060087          	vle8.v	v1,(a2)
    802010c6:	0c07f057          	vsetvli	zero,a5,e8,m1,ta,ma
    802010ca:	020680a7          	vse8.v	v1,(a3)
    802010ce:	963e                	add	a2,a2,a5
    802010d0:	96be                	add	a3,a3,a5
    802010d2:	8f1d                	sub	a4,a4,a5
    802010d4:	f37d                	bnez	a4,802010ba <main+0x38>
    802010d6:	0001                	nop
    802010d8:	fec42783          	lw	a5,-20(s0)
    802010dc:	f0040713          	addi	a4,s0,-256
    802010e0:	85ba                	mv	a1,a4
    802010e2:	853e                	mv	a0,a5
    802010e4:	fffff097          	auipc	ra,0xfffff
    802010e8:	64e080e7          	jalr	1614(ra) # 80200732 <itoa>
    802010ec:	00000517          	auipc	a0,0x0
    802010f0:	3bc50513          	addi	a0,a0,956 # 802014a8 <rodata_start+0x8a>
    802010f4:	fffff097          	auipc	ra,0xfffff
    802010f8:	5d4080e7          	jalr	1492(ra) # 802006c8 <puts>
    802010fc:	00000517          	auipc	a0,0x0
    80201100:	3cc50513          	addi	a0,a0,972 # 802014c8 <rodata_start+0xaa>
    80201104:	fffff097          	auipc	ra,0xfffff
    80201108:	5c4080e7          	jalr	1476(ra) # 802006c8 <puts>
    8020110c:	f0040793          	addi	a5,s0,-256
    80201110:	853e                	mv	a0,a5
    80201112:	fffff097          	auipc	ra,0xfffff
    80201116:	5b6080e7          	jalr	1462(ra) # 802006c8 <puts>
    8020111a:	fe842783          	lw	a5,-24(s0)
    8020111e:	0007871b          	sext.w	a4,a5
    80201122:	808007b7          	lui	a5,0x80800
    80201126:	00f71a63          	bne	a4,a5,8020113a <main+0xb8>
    8020112a:	00000517          	auipc	a0,0x0
    8020112e:	3ae50513          	addi	a0,a0,942 # 802014d8 <rodata_start+0xba>
    80201132:	fffff097          	auipc	ra,0xfffff
    80201136:	596080e7          	jalr	1430(ra) # 802006c8 <puts>
    8020113a:	00000517          	auipc	a0,0x0
    8020113e:	3ae50513          	addi	a0,a0,942 # 802014e8 <rodata_start+0xca>
    80201142:	fffff097          	auipc	ra,0xfffff
    80201146:	586080e7          	jalr	1414(ra) # 802006c8 <puts>
    8020114a:	00000097          	auipc	ra,0x0
    8020114e:	e08080e7          	jalr	-504(ra) # 80200f52 <test_main>
    80201152:	f7040793          	addi	a5,s0,-144
    80201156:	ecf43823          	sd	a5,-304(s0)
    8020115a:	4785                	li	a5,1
    8020115c:	ecf42c23          	sw	a5,-296(s0)
    80201160:	4785                	li	a5,1
    80201162:	ecf42e23          	sw	a5,-292(s0)
    80201166:	47bd                	li	a5,15
    80201168:	eef42023          	sw	a5,-288(s0)
    8020116c:	4785                	li	a5,1
    8020116e:	eef42223          	sw	a5,-284(s0)
    80201172:	47bd                	li	a5,15
    80201174:	eef42423          	sw	a5,-280(s0)
    80201178:	00000717          	auipc	a4,0x0
    8020117c:	43870713          	addi	a4,a4,1080 # 802015b0 <rodata_start+0x192>
    80201180:	eb040793          	addi	a5,s0,-336
    80201184:	cd827057          	vsetivli	zero,4,e64,m1,ta,ma
    80201188:	02077087          	vle64.v	v1,(a4)
    8020118c:	cd827057          	vsetivli	zero,4,e64,m1,ta,ma
    80201190:	0207f0a7          	vse64.v	v1,(a5)
    80201194:	00000717          	auipc	a4,0x0
    80201198:	43c70713          	addi	a4,a4,1084 # 802015d0 <rodata_start+0x1b2>
    8020119c:	e9040793          	addi	a5,s0,-368
    802011a0:	cd827057          	vsetivli	zero,4,e64,m1,ta,ma
    802011a4:	02077087          	vle64.v	v1,(a4)
    802011a8:	cd827057          	vsetivli	zero,4,e64,m1,ta,ma
    802011ac:	0207f0a7          	vse64.v	v1,(a5)
    802011b0:	f2040793          	addi	a5,s0,-224
    802011b4:	e6f43823          	sd	a5,-400(s0)
    802011b8:	4785                	li	a5,1
    802011ba:	e6f42c23          	sw	a5,-392(s0)
    802011be:	4785                	li	a5,1
    802011c0:	e6f42e23          	sw	a5,-388(s0)
    802011c4:	47a9                	li	a5,10
    802011c6:	e8f42023          	sw	a5,-384(s0)
    802011ca:	4785                	li	a5,1
    802011cc:	e8f42223          	sw	a5,-380(s0)
    802011d0:	47a9                	li	a5,10
    802011d2:	e8f42423          	sw	a5,-376(s0)
    802011d6:	00000717          	auipc	a4,0x0
    802011da:	41a70713          	addi	a4,a4,1050 # 802015f0 <rodata_start+0x1d2>
    802011de:	e5040793          	addi	a5,s0,-432
    802011e2:	cd827057          	vsetivli	zero,4,e64,m1,ta,ma
    802011e6:	02077087          	vle64.v	v1,(a4)
    802011ea:	cd827057          	vsetivli	zero,4,e64,m1,ta,ma
    802011ee:	0207f0a7          	vse64.v	v1,(a5)
    802011f2:	00000717          	auipc	a4,0x0
    802011f6:	41e70713          	addi	a4,a4,1054 # 80201610 <rodata_start+0x1f2>
    802011fa:	e3040793          	addi	a5,s0,-464
    802011fe:	cd827057          	vsetivli	zero,4,e64,m1,ta,ma
    80201202:	02077087          	vle64.v	v1,(a4)
    80201206:	cd827057          	vsetivli	zero,4,e64,m1,ta,ma
    8020120a:	0207f0a7          	vse64.v	v1,(a5)
    8020120e:	f1840793          	addi	a5,s0,-232
    80201212:	e0f43823          	sd	a5,-496(s0)
    80201216:	4785                	li	a5,1
    80201218:	e0f42c23          	sw	a5,-488(s0)
    8020121c:	4785                	li	a5,1
    8020121e:	e0f42e23          	sw	a5,-484(s0)
    80201222:	4785                	li	a5,1
    80201224:	e2f42023          	sw	a5,-480(s0)
    80201228:	4785                	li	a5,1
    8020122a:	e2f42223          	sw	a5,-476(s0)
    8020122e:	4785                	li	a5,1
    80201230:	e2f42423          	sw	a5,-472(s0)
    80201234:	00000517          	auipc	a0,0x0
    80201238:	2c450513          	addi	a0,a0,708 # 802014f8 <rodata_start+0xda>
    8020123c:	fffff097          	auipc	ra,0xfffff
    80201240:	48c080e7          	jalr	1164(ra) # 802006c8 <puts>
    80201244:	eb040613          	addi	a2,s0,-336
    80201248:	ed040713          	addi	a4,s0,-304
    8020124c:	e7040793          	addi	a5,s0,-400
    80201250:	4685                	li	a3,1
    80201252:	85ba                	mv	a1,a4
    80201254:	853e                	mv	a0,a5
    80201256:	fffff097          	auipc	ra,0xfffff
    8020125a:	e64080e7          	jalr	-412(ra) # 802000ba <matmul>
    8020125e:	872a                	mv	a4,a0
    80201260:	87ae                	mv	a5,a1
    80201262:	eee43823          	sd	a4,-272(s0)
    80201266:	eef43c23          	sd	a5,-264(s0)
    8020126a:	eb040613          	addi	a2,s0,-336
    8020126e:	ed040713          	addi	a4,s0,-304
    80201272:	e7040793          	addi	a5,s0,-400
    80201276:	4685                	li	a3,1
    80201278:	85ba                	mv	a1,a4
    8020127a:	853e                	mv	a0,a5
    8020127c:	fffff097          	auipc	ra,0xfffff
    80201280:	e3e080e7          	jalr	-450(ra) # 802000ba <matmul>
    80201284:	872a                	mv	a4,a0
    80201286:	87ae                	mv	a5,a1
    80201288:	eee43823          	sd	a4,-272(s0)
    8020128c:	eef43c23          	sd	a5,-264(s0)
    80201290:	eb040613          	addi	a2,s0,-336
    80201294:	ed040713          	addi	a4,s0,-304
    80201298:	e7040793          	addi	a5,s0,-400
    8020129c:	4685                	li	a3,1
    8020129e:	85ba                	mv	a1,a4
    802012a0:	853e                	mv	a0,a5
    802012a2:	fffff097          	auipc	ra,0xfffff
    802012a6:	e18080e7          	jalr	-488(ra) # 802000ba <matmul>
    802012aa:	872a                	mv	a4,a0
    802012ac:	87ae                	mv	a5,a1
    802012ae:	eee43823          	sd	a4,-272(s0)
    802012b2:	eef43c23          	sd	a5,-264(s0)
    802012b6:	00000517          	auipc	a0,0x0
    802012ba:	24250513          	addi	a0,a0,578 # 802014f8 <rodata_start+0xda>
    802012be:	fffff097          	auipc	ra,0xfffff
    802012c2:	40a080e7          	jalr	1034(ra) # 802006c8 <puts>
    802012c6:	e7040793          	addi	a5,s0,-400
    802012ca:	00000597          	auipc	a1,0x0
    802012ce:	24e58593          	addi	a1,a1,590 # 80201518 <rodata_start+0xfa>
    802012d2:	853e                	mv	a0,a5
    802012d4:	00000097          	auipc	ra,0x0
    802012d8:	8fe080e7          	jalr	-1794(ra) # 80200bd2 <print_tensor_data>
    802012dc:	ef043703          	ld	a4,-272(s0)
    802012e0:	57fd                	li	a5,-1
    802012e2:	00f71a63          	bne	a4,a5,802012f6 <main+0x274>
    802012e6:	00000517          	auipc	a0,0x0
    802012ea:	23a50513          	addi	a0,a0,570 # 80201520 <rodata_start+0x102>
    802012ee:	fffff097          	auipc	ra,0xfffff
    802012f2:	3da080e7          	jalr	986(ra) # 802006c8 <puts>
    802012f6:	e9040613          	addi	a2,s0,-368
    802012fa:	e7040713          	addi	a4,s0,-400
    802012fe:	e7040793          	addi	a5,s0,-400
    80201302:	4685                	li	a3,1
    80201304:	85ba                	mv	a1,a4
    80201306:	853e                	mv	a0,a5
    80201308:	fffff097          	auipc	ra,0xfffff
    8020130c:	e22080e7          	jalr	-478(ra) # 8020012a <tensor_add>
    80201310:	872a                	mv	a4,a0
    80201312:	87ae                	mv	a5,a1
    80201314:	eee43823          	sd	a4,-272(s0)
    80201318:	eef43c23          	sd	a5,-264(s0)
    8020131c:	ef043703          	ld	a4,-272(s0)
    80201320:	57fd                	li	a5,-1
    80201322:	00f71a63          	bne	a4,a5,80201336 <main+0x2b4>
    80201326:	00000517          	auipc	a0,0x0
    8020132a:	1fa50513          	addi	a0,a0,506 # 80201520 <rodata_start+0x102>
    8020132e:	fffff097          	auipc	ra,0xfffff
    80201332:	39a080e7          	jalr	922(ra) # 802006c8 <puts>
    80201336:	e7040713          	addi	a4,s0,-400
    8020133a:	e7040793          	addi	a5,s0,-400
    8020133e:	4605                	li	a2,1
    80201340:	85ba                	mv	a1,a4
    80201342:	853e                	mv	a0,a5
    80201344:	fffff097          	auipc	ra,0xfffff
    80201348:	e56080e7          	jalr	-426(ra) # 8020019a <tensor_relu>
    8020134c:	872a                	mv	a4,a0
    8020134e:	87ae                	mv	a5,a1
    80201350:	eee43823          	sd	a4,-272(s0)
    80201354:	eef43c23          	sd	a5,-264(s0)
    80201358:	ef043703          	ld	a4,-272(s0)
    8020135c:	57fd                	li	a5,-1
    8020135e:	00f71a63          	bne	a4,a5,80201372 <main+0x2f0>
    80201362:	00000517          	auipc	a0,0x0
    80201366:	1be50513          	addi	a0,a0,446 # 80201520 <rodata_start+0x102>
    8020136a:	fffff097          	auipc	ra,0xfffff
    8020136e:	35e080e7          	jalr	862(ra) # 802006c8 <puts>
    80201372:	e5040613          	addi	a2,s0,-432
    80201376:	e7040713          	addi	a4,s0,-400
    8020137a:	e1040793          	addi	a5,s0,-496
    8020137e:	4685                	li	a3,1
    80201380:	85ba                	mv	a1,a4
    80201382:	853e                	mv	a0,a5
    80201384:	fffff097          	auipc	ra,0xfffff
    80201388:	d36080e7          	jalr	-714(ra) # 802000ba <matmul>
    8020138c:	872a                	mv	a4,a0
    8020138e:	87ae                	mv	a5,a1
    80201390:	eee43823          	sd	a4,-272(s0)
    80201394:	eef43c23          	sd	a5,-264(s0)
    80201398:	ef043703          	ld	a4,-272(s0)
    8020139c:	57fd                	li	a5,-1
    8020139e:	00f71a63          	bne	a4,a5,802013b2 <main+0x330>
    802013a2:	00000517          	auipc	a0,0x0
    802013a6:	17e50513          	addi	a0,a0,382 # 80201520 <rodata_start+0x102>
    802013aa:	fffff097          	auipc	ra,0xfffff
    802013ae:	31e080e7          	jalr	798(ra) # 802006c8 <puts>
    802013b2:	e3040613          	addi	a2,s0,-464
    802013b6:	e1040713          	addi	a4,s0,-496
    802013ba:	e1040793          	addi	a5,s0,-496
    802013be:	4685                	li	a3,1
    802013c0:	85ba                	mv	a1,a4
    802013c2:	853e                	mv	a0,a5
    802013c4:	fffff097          	auipc	ra,0xfffff
    802013c8:	d66080e7          	jalr	-666(ra) # 8020012a <tensor_add>
    802013cc:	872a                	mv	a4,a0
    802013ce:	87ae                	mv	a5,a1
    802013d0:	eee43823          	sd	a4,-272(s0)
    802013d4:	eef43c23          	sd	a5,-264(s0)
    802013d8:	ef043703          	ld	a4,-272(s0)
    802013dc:	57fd                	li	a5,-1
    802013de:	00f71a63          	bne	a4,a5,802013f2 <main+0x370>
    802013e2:	00000517          	auipc	a0,0x0
    802013e6:	13e50513          	addi	a0,a0,318 # 80201520 <rodata_start+0x102>
    802013ea:	fffff097          	auipc	ra,0xfffff
    802013ee:	2de080e7          	jalr	734(ra) # 802006c8 <puts>
    802013f2:	e1040793          	addi	a5,s0,-496
    802013f6:	00000597          	auipc	a1,0x0
    802013fa:	13258593          	addi	a1,a1,306 # 80201528 <rodata_start+0x10a>
    802013fe:	853e                	mv	a0,a5
    80201400:	fffff097          	auipc	ra,0xfffff
    80201404:	7d2080e7          	jalr	2002(ra) # 80200bd2 <print_tensor_data>
    80201408:	fffff097          	auipc	ra,0xfffff
    8020140c:	c0c080e7          	jalr	-1012(ra) # 80200014 <shutdown>
    80201410:	0001                	nop
    80201412:	0001                	nop
    80201414:	70fe                	ld	ra,504(sp)
    80201416:	745e                	ld	s0,496(sp)
    80201418:	20010113          	addi	sp,sp,512
    8020141c:	8082                	ret
