; ModuleID = 'main'
source_filename = "main"

@i = global i32 0
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
  store i32 0, i32* @i, align 4
  br label %loop

cond:                                             ; preds = %loop
  %Load_id2 = load i32, i32* @i, align 4
  %gttmp = icmp sgt i32 %Load_id2, 5
  %repeateCond = icmp eq i1 %gttmp, false
  br i1 %repeateCond, label %loop, label %afterLoop

loop:                                             ; preds = %cond, %entrypoint
  %Load_id = load i32, i32* @i, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %Load_id)
  %Load_id1 = load i32, i32* @i, align 4
  %addtmp = add i32 %Load_id1, 1
  store i32 %addtmp, i32* @i, align 4
  br label %cond

afterLoop:                                        ; preds = %cond
  ret void
}
