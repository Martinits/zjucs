; ModuleID = 'main'
source_filename = "main"

@min = constant i32 0
@max = constant i32 10
@a = global [11 x i32] zeroinitializer
@.str = constant [4 x i8] c"%d\0A\00"

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
  %Load_id = load i32, i32* @max, align 4
  %Load_id1 = load i32, i32* @min, align 4
  %Load_id2 = load i32, i32* @min, align 4
  %addtmp = add i32 %Load_id2, 2
  %subtmp = sub i32 %addtmp, %Load_id1
  %"array[idx]" = getelementptr inbounds [11 x i32], [11 x i32]* @a, i32 0, i32 %subtmp
  %Load_id3 = load i32, i32* @max, align 4
  store i32 %Load_id3, i32* %"array[idx]", align 4
  %Load_id4 = load i32, i32* @min, align 4
  %addtmp5 = add i32 %Load_id4, 2
  %subtmp6 = sub i32 %addtmp5, %Load_id1
  %"array[idx]7" = getelementptr inbounds [11 x i32], [11 x i32]* @a, i32 0, i32 %subtmp6
  %"arr[ref]" = load i32, i32* %"array[idx]7", align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %"arr[ref]")
  ret void
}
