; ModuleID = 'main'
source_filename = "main"

@i = global i32 0
@d = global double 0.000000e+00
@c = global i8 0
@b = global i1 false
@ii = global i32 0
@arr = global [5 x i32] zeroinitializer
@r = global { i32, i32, i8 } zeroinitializer
@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [5 x i8] c"%lf\0A\00"
@.str.2 = constant [4 x i8] c"%c\0A\00"
@.str.3 = constant [4 x i8] c"%d\0A\00"
@.str.4 = constant [4 x i8] c"%d\0A\00"
@.str.5 = constant [4 x i8] c"%d\0A\00"
@.str.6 = constant [4 x i8] c"%d\0A\00"
@.str.7 = constant [4 x i8] c"%d\0A\00"
@.str.8 = constant [4 x i8] c"%c\0A\00"

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
  store i32 4, i32* @i, align 4
  store double 9.890000e+00, double* @d, align 8
  store i8 103, i8* @c, align 1
  store i1 false, i1* @b, align 1
  store i32 45, i32* @ii, align 4
  %Load_id = load i32, i32* @i, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %Load_id)
  %Load_id1 = load double, double* @d, align 8
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), double %Load_id1)
  %Load_id3 = load i8, i8* @c, align 1
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8 %Load_id3)
  %Load_id5 = load i1, i1* @b, align 1
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i1 %Load_id5)
  %Load_id7 = load i32, i32* @ii, align 4
  %printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i32 %Load_id7)
  store i32 0, i32* @i, align 4
  store i32 4, i32* @i, align 4
  br label %cond

cond:                                             ; preds = %loop, %entrypoint
  %Load_id9 = load i32, i32* @i, align 4
  %0 = icmp sle i32 %Load_id9, 8
  %forCond = icmp ne i1 %0, false
  br i1 %forCond, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  %Load_id10 = load i32, i32* @i, align 4
  %subtmp = sub i32 %Load_id10, 4
  %"array[idx]" = getelementptr inbounds [5 x i32], [5 x i32]* @arr, i32 0, i32 %subtmp
  %Load_id11 = load i32, i32* @i, align 4
  store i32 %Load_id11, i32* %"array[idx]", align 4
  %1 = add i32 %Load_id9, 1
  store i32 %1, i32* @i, align 4
  br label %cond

afterLoop:                                        ; preds = %cond
  store i32 4, i32* @i, align 4
  br label %cond12

cond12:                                           ; preds = %loop13, %afterLoop
  %Load_id15 = load i32, i32* @i, align 4
  %2 = icmp sle i32 %Load_id15, 8
  %forCond16 = icmp ne i1 %2, false
  br i1 %forCond16, label %loop13, label %afterLoop14

loop13:                                           ; preds = %cond12
  %Load_id17 = load i32, i32* @i, align 4
  %subtmp18 = sub i32 %Load_id17, 4
  %"array[idx]19" = getelementptr inbounds [5 x i32], [5 x i32]* @arr, i32 0, i32 %subtmp18
  %"arr[ref]" = load i32, i32* %"array[idx]19", align 4
  %printf20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i32 %"arr[ref]")
  %3 = add i32 %Load_id15, 1
  store i32 %3, i32* @i, align 4
  br label %cond12

afterLoop14:                                      ; preds = %cond12
  store i32 1234, i32* getelementptr inbounds ({ i32, i32, i8 }, { i32, i32, i8 }* @r, i32 0, i32 0), align 4
  store i32 2345, i32* getelementptr inbounds ({ i32, i32, i8 }, { i32, i32, i8 }* @r, i32 0, i32 1), align 4
  store i8 99, i8* getelementptr inbounds ({ i32, i32, i8 }, { i32, i32, i8 }* @r, i32 0, i32 2), align 1
  %rec.ref = load i32, i32* getelementptr inbounds ({ i32, i32, i8 }, { i32, i32, i8 }* @r, i32 0, i32 0), align 4
  %printf21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0), i32 %rec.ref)
  %rec.ref22 = load i32, i32* getelementptr inbounds ({ i32, i32, i8 }, { i32, i32, i8 }* @r, i32 0, i32 1), align 4
  %printf23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i32 %rec.ref22)
  %rec.ref24 = load i8, i8* getelementptr inbounds ({ i32, i32, i8 }, { i32, i32, i8 }* @r, i32 0, i32 2), align 1
  %printf25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0), i8 %rec.ref24)
  ret void
}
