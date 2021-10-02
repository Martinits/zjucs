; ModuleID = 'main'
source_filename = "main"

@b1 = global i1 false
@b2 = global i1 false
@b3 = global i1 false
@c1 = global i8 0
@c2 = global i8 0
@c3 = global i8 0
@i1 = global i32 0
@i2 = global i32 0
@i3 = global i32 0
@r1 = global double 0.000000e+00
@r2 = global double 0.000000e+00
@r3 = global double 0.000000e+00
@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [4 x i8] c"%d\0A\00"
@.str.2 = constant [4 x i8] c"%d\0A\00"
@.str.3 = constant [4 x i8] c"%d\0A\00"
@.str.4 = constant [4 x i8] c"%d\0A\00"
@.str.5 = constant [4 x i8] c"%d\0A\00"
@.str.6 = constant [4 x i8] c"%d\0A\00"
@.str.7 = constant [4 x i8] c"%d\0A\00"
@.str.8 = constant [4 x i8] c"%d\0A\00"
@.str.9 = constant [4 x i8] c"%d\0A\00"
@.str.10 = constant [4 x i8] c"%d\0A\00"
@.str.11 = constant [4 x i8] c"%d\0A\00"
@.str.12 = constant [4 x i8] c"%d\0A\00"
@.str.13 = constant [4 x i8] c"%d\0A\00"
@.str.14 = constant [4 x i8] c"%d\0A\00"
@.str.15 = constant [4 x i8] c"%d\0A\00"
@.str.16 = constant [4 x i8] c"%d\0A\00"
@.str.17 = constant [5 x i8] c"%lf\0A\00"
@.str.18 = constant [5 x i8] c"%lf\0A\00"
@.str.19 = constant [5 x i8] c"%lf\0A\00"
@.str.20 = constant [5 x i8] c"%lf\0A\00"
@.str.21 = constant [5 x i8] c"%lf\0A\00"
@.str.22 = constant [5 x i8] c"%lf\0A\00"
@.str.23 = constant [5 x i8] c"%lf\0A\00"
@.str.24 = constant [4 x i8] c"%d\0A\00"
@.str.25 = constant [4 x i8] c"%d\0A\00"
@.str.26 = constant [4 x i8] c"%d\0A\00"
@.str.27 = constant [4 x i8] c"%d\0A\00"
@.str.28 = constant [4 x i8] c"%d\0A\00"
@.str.29 = constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

declare i32 @abs_i(i32)

declare double @abs_d(double)

declare i8 @chr(i32)

declare i32 @ord(i8)

declare i1 @odd(i32)

declare i32 @pred_i(i32)

declare i8 @pred_c(i8)

declare i32 @succ_i(i32)

declare i8 @succ_c(i8)

declare i32 @sqr_i(i32)

declare double @sqr_d(double)

declare double @sqrt_i(i32)

declare double @sqrt_d(double)

define void @main() {
entrypoint:
  store i1 true, i1* @b1, align 1
  store i1 false, i1* @b2, align 1
  %Load_id = load i1, i1* @b1, align 1
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i1 %Load_id)
  %Load_id1 = load i1, i1* @b2, align 1
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i1 %Load_id1)
  %Load_id3 = load i1, i1* @b2, align 1
  %Load_id4 = load i1, i1* @b1, align 1
  %andtmp = and i1 %Load_id4, %Load_id3
  store i1 %andtmp, i1* @b3, align 1
  %Load_id5 = load i1, i1* @b3, align 1
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i1 %Load_id5)
  %Load_id7 = load i1, i1* @b2, align 1
  %Load_id8 = load i1, i1* @b1, align 1
  %ortmp = or i1 %Load_id8, %Load_id7
  store i1 %ortmp, i1* @b3, align 1
  %Load_id9 = load i1, i1* @b3, align 1
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i1 %Load_id9)
  store i32 13, i32* @i1, align 4
  store i32 10, i32* @i2, align 4
  %Load_id11 = load i32, i32* @i1, align 4
  %printf12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i32 %Load_id11)
  %Load_id13 = load i32, i32* @i2, align 4
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i32 %Load_id13)
  %Load_id15 = load i32, i32* @i2, align 4
  %Load_id16 = load i32, i32* @i1, align 4
  %addtmp = add i32 %Load_id16, %Load_id15
  store i32 %addtmp, i32* @i3, align 4
  %Load_id17 = load i32, i32* @i3, align 4
  %printf18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0), i32 %Load_id17)
  %Load_id19 = load i32, i32* @i2, align 4
  %Load_id20 = load i32, i32* @i1, align 4
  %subtmp = sub i32 %Load_id20, %Load_id19
  store i32 %subtmp, i32* @i3, align 4
  %Load_id21 = load i32, i32* @i3, align 4
  %printf22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i32 %Load_id21)
  %Load_id23 = load i32, i32* @i2, align 4
  %Load_id24 = load i32, i32* @i1, align 4
  %multmp = mul i32 %Load_id24, %Load_id23
  store i32 %multmp, i32* @i3, align 4
  %Load_id25 = load i32, i32* @i3, align 4
  %printf26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0), i32 %Load_id25)
  %Load_id27 = load i32, i32* @i2, align 4
  %Load_id28 = load i32, i32* @i1, align 4
  %divtmp = sdiv i32 %Load_id28, %Load_id27
  store i32 %divtmp, i32* @i3, align 4
  %Load_id29 = load i32, i32* @i3, align 4
  %printf30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i32 0, i32 0), i32 %Load_id29)
  %Load_id31 = load i32, i32* @i2, align 4
  %Load_id32 = load i32, i32* @i1, align 4
  %modtmp = srem i32 %Load_id32, %Load_id31
  store i32 %modtmp, i32* @i3, align 4
  %Load_id33 = load i32, i32* @i3, align 4
  %printf34 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i32 0, i32 0), i32 %Load_id33)
  %Load_id35 = load i32, i32* @i2, align 4
  %Load_id36 = load i32, i32* @i1, align 4
  %gttmp = icmp sgt i32 %Load_id36, %Load_id35
  store i1 %gttmp, i1* @b3, align 1
  %Load_id37 = load i1, i1* @b3, align 1
  %printf38 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0), i1 %Load_id37)
  %Load_id39 = load i32, i32* @i2, align 4
  %Load_id40 = load i32, i32* @i1, align 4
  %getmp = icmp sge i32 %Load_id40, %Load_id39
  store i1 %getmp, i1* @b3, align 1
  %Load_id41 = load i1, i1* @b3, align 1
  %printf42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.12, i32 0, i32 0), i1 %Load_id41)
  %Load_id43 = load i32, i32* @i2, align 4
  %Load_id44 = load i32, i32* @i1, align 4
  %lttmp = icmp slt i32 %Load_id44, %Load_id43
  store i1 %lttmp, i1* @b3, align 1
  %Load_id45 = load i1, i1* @b3, align 1
  %printf46 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.13, i32 0, i32 0), i1 %Load_id45)
  %Load_id47 = load i32, i32* @i2, align 4
  %Load_id48 = load i32, i32* @i1, align 4
  %letmp = icmp sle i32 %Load_id48, %Load_id47
  store i1 %letmp, i1* @b3, align 1
  %Load_id49 = load i1, i1* @b3, align 1
  %printf50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.14, i32 0, i32 0), i1 %Load_id49)
  %Load_id51 = load i32, i32* @i2, align 4
  %Load_id52 = load i32, i32* @i1, align 4
  %equaltmp = icmp eq i32 %Load_id52, %Load_id51
  store i1 %equaltmp, i1* @b3, align 1
  %Load_id53 = load i1, i1* @b3, align 1
  %printf54 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.15, i32 0, i32 0), i1 %Load_id53)
  %Load_id55 = load i32, i32* @i2, align 4
  %Load_id56 = load i32, i32* @i1, align 4
  %uequaltmp = icmp ne i32 %Load_id56, %Load_id55
  store i1 %uequaltmp, i1* @b3, align 1
  %Load_id57 = load i1, i1* @b3, align 1
  %printf58 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.16, i32 0, i32 0), i1 %Load_id57)
  store double 3.150000e+01, double* @r1, align 8
  store double 2.370000e+01, double* @r2, align 8
  %Load_id59 = load double, double* @r1, align 8
  %printf60 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0), double %Load_id59)
  %Load_id61 = load double, double* @r2, align 8
  %printf62 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.18, i32 0, i32 0), double %Load_id61)
  %Load_id63 = load double, double* @r2, align 8
  %Load_id64 = load double, double* @r1, align 8
  %faddtmp = fadd double %Load_id64, %Load_id63
  store double %faddtmp, double* @r3, align 8
  %Load_id65 = load double, double* @r3, align 8
  %printf66 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.19, i32 0, i32 0), double %Load_id65)
  %Load_id67 = load double, double* @r2, align 8
  %Load_id68 = load double, double* @r1, align 8
  %fsubtmp = fsub double %Load_id68, %Load_id67
  store double %fsubtmp, double* @r3, align 8
  %Load_id69 = load double, double* @r3, align 8
  %printf70 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i32 0, i32 0), double %Load_id69)
  %Load_id71 = load double, double* @r2, align 8
  %Load_id72 = load double, double* @r1, align 8
  %fmultmp = fmul double %Load_id72, %Load_id71
  store double %fmultmp, double* @r3, align 8
  %Load_id73 = load double, double* @r3, align 8
  %printf74 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.21, i32 0, i32 0), double %Load_id73)
  %Load_id75 = load double, double* @r2, align 8
  %Load_id76 = load double, double* @r1, align 8
  %fdivtmp = fdiv double %Load_id76, %Load_id75
  store double %fdivtmp, double* @r3, align 8
  %Load_id77 = load double, double* @r3, align 8
  %printf78 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i32 0, i32 0), double %Load_id77)
  %Load_id79 = load double, double* @r2, align 8
  %Load_id80 = load double, double* @r1, align 8
  %fmodtmp = frem double %Load_id80, %Load_id79
  store double %fmodtmp, double* @r3, align 8
  %Load_id81 = load double, double* @r3, align 8
  %printf82 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.23, i32 0, i32 0), double %Load_id81)
  %Load_id83 = load double, double* @r2, align 8
  %Load_id84 = load double, double* @r1, align 8
  %fgttmp = fcmp ogt double %Load_id84, %Load_id83
  store i1 %fgttmp, i1* @b3, align 1
  %Load_id85 = load i1, i1* @b3, align 1
  %printf86 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.24, i32 0, i32 0), i1 %Load_id85)
  %Load_id87 = load double, double* @r2, align 8
  %Load_id88 = load double, double* @r1, align 8
  %fgetmp = fcmp oge double %Load_id88, %Load_id87
  store i1 %fgetmp, i1* @b3, align 1
  %Load_id89 = load i1, i1* @b3, align 1
  %printf90 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.25, i32 0, i32 0), i1 %Load_id89)
  %Load_id91 = load double, double* @r2, align 8
  %Load_id92 = load double, double* @r1, align 8
  %flttmp = fcmp olt double %Load_id92, %Load_id91
  store i1 %flttmp, i1* @b3, align 1
  %Load_id93 = load i1, i1* @b3, align 1
  %printf94 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.26, i32 0, i32 0), i1 %Load_id93)
  %Load_id95 = load double, double* @r2, align 8
  %Load_id96 = load double, double* @r1, align 8
  %fletmp = fcmp ole double %Load_id96, %Load_id95
  store i1 %fletmp, i1* @b3, align 1
  %Load_id97 = load i1, i1* @b3, align 1
  %printf98 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.27, i32 0, i32 0), i1 %Load_id97)
  %Load_id99 = load double, double* @r2, align 8
  %Load_id100 = load double, double* @r1, align 8
  %fequaltmp = fcmp oeq double %Load_id100, %Load_id99
  store i1 %fequaltmp, i1* @b3, align 1
  %Load_id101 = load i1, i1* @b3, align 1
  %printf102 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i32 0, i32 0), i1 %Load_id101)
  %Load_id103 = load double, double* @r2, align 8
  %Load_id104 = load double, double* @r1, align 8
  %fuequaltmp = fcmp one double %Load_id104, %Load_id103
  store i1 %fuequaltmp, i1* @b3, align 1
  %Load_id105 = load i1, i1* @b3, align 1
  %printf106 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.29, i32 0, i32 0), i1 %Load_id105)
  ret void
}
