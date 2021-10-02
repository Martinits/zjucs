; ModuleID = 'main'
source_filename = "main"

@rec = global { i32, double, i8, i1 } zeroinitializer
@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [5 x i8] c"%lf\0A\00"
@.str.2 = constant [4 x i8] c"%c\0A\00"
@.str.3 = constant [4 x i8] c"%d\0A\00"

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
  store i32 1, i32* getelementptr inbounds ({ i32, double, i8, i1 }, { i32, double, i8, i1 }* @rec, i32 0, i32 0), align 4
  store double 1.100000e+00, double* getelementptr inbounds ({ i32, double, i8, i1 }, { i32, double, i8, i1 }* @rec, i32 0, i32 1), align 8
  store i8 97, i8* getelementptr inbounds ({ i32, double, i8, i1 }, { i32, double, i8, i1 }* @rec, i32 0, i32 2), align 1
  store i1 true, i1* getelementptr inbounds ({ i32, double, i8, i1 }, { i32, double, i8, i1 }* @rec, i32 0, i32 3), align 1
  %rec.ref = load i32, i32* getelementptr inbounds ({ i32, double, i8, i1 }, { i32, double, i8, i1 }* @rec, i32 0, i32 0), align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %rec.ref)
  %rec.ref1 = load double, double* getelementptr inbounds ({ i32, double, i8, i1 }, { i32, double, i8, i1 }* @rec, i32 0, i32 1), align 8
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), double %rec.ref1)
  %rec.ref3 = load i8, i8* getelementptr inbounds ({ i32, double, i8, i1 }, { i32, double, i8, i1 }* @rec, i32 0, i32 2), align 1
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8 %rec.ref3)
  %rec.ref5 = load i1, i1* getelementptr inbounds ({ i32, double, i8, i1 }, { i32, double, i8, i1 }* @rec, i32 0, i32 3), align 1
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i1 %rec.ref5)
  ret void
}
