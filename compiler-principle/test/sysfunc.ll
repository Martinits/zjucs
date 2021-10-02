; ModuleID = 'main'
source_filename = "main"

@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [5 x i8] c"%lf\0A\00"
@.str.2 = constant [4 x i8] c"%c\0A\00"
@.str.3 = constant [4 x i8] c"%d\0A\00"
@.str.4 = constant [4 x i8] c"%d\0A\00"
@.str.5 = constant [4 x i8] c"%d\0A\00"
@.str.6 = constant [4 x i8] c"%d\0A\00"
@.str.7 = constant [4 x i8] c"%c\0A\00"
@.str.8 = constant [4 x i8] c"%d\0A\00"
@.str.9 = constant [4 x i8] c"%c\0A\00"
@.str.10 = constant [4 x i8] c"%d\0A\00"
@.str.11 = constant [5 x i8] c"%lf\0A\00"
@.str.12 = constant [5 x i8] c"%lf\0A\00"
@.str.13 = constant [5 x i8] c"%lf\0A\00"

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
  %abs_i = call i32 @abs_i(i32 -8)
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %abs_i)
  %abs_d = call double @abs_d(double 0x4020E978D4FDF3B6)
  %printf1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), double %abs_d)
  %chr = call i8 @chr(i32 65)
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8 %chr)
  %ord = call i32 @ord(i8 99)
  %printf3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i32 %ord)
  %odd = call i1 @odd(i32 56)
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i1 %odd)
  %odd5 = call i1 @odd(i32 3)
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i1 %odd5)
  %pred_i = call i32 @pred_i(i32 9)
  %printf7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0), i32 %pred_i)
  %pred_c = call i8 @pred_c(i8 103)
  %printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i8 %pred_c)
  %succ_i = call i32 @succ_i(i32 3)
  %printf9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0), i32 %succ_i)
  %succ_c = call i8 @succ_c(i8 100)
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i32 0, i32 0), i8 %succ_c)
  %sqr_i = call i32 @sqr_i(i32 4)
  %printf11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i32 0, i32 0), i32 %sqr_i)
  %sqr_d = call double @sqr_d(double 1.600000e+00)
  %printf12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.11, i32 0, i32 0), double %sqr_d)
  %sqrt_i = call double @sqrt_i(i32 33)
  %printf13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.12, i32 0, i32 0), double %sqrt_i)
  %sqrt_d = call double @sqrt_d(double 4.560000e+00)
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0), double %sqrt_d)
  ret void
}
