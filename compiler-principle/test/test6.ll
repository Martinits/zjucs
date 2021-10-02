; ModuleID = 'main'
source_filename = "main"

@ans = global i32 0
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
  %0 = call i32 @gcd(i32 3, i32 6)
  %1 = call i32 @gcd(i32 9, i32 36)
  %multmp = mul i32 %1, %0
  store i32 %multmp, i32* @ans, align 4
  %Load_id = load i32, i32* @ans, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %Load_id)
  ret void
}

define internal i32 @gcd(i32 %0, i32 %1) {
entrypoint:
  %gcd = alloca i32, align 4
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 %0, i32* %a, align 4
  store i32 %1, i32* %b, align 4
  %Load_id = load i32, i32* %b, align 4
  %equaltmp = icmp eq i32 %Load_id, 0
  %ifCond = icmp ne i1 %equaltmp, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entrypoint
  %Load_id1 = load i32, i32* %a, align 4
  store i32 %Load_id1, i32* %gcd, align 4
  br label %merge

else:                                             ; preds = %entrypoint
  %Load_id2 = load i32, i32* %b, align 4
  %Load_id3 = load i32, i32* %b, align 4
  %Load_id4 = load i32, i32* %a, align 4
  %modtmp = srem i32 %Load_id4, %Load_id3
  %2 = call i32 @gcd(i32 %Load_id2, i32 %modtmp)
  store i32 %2, i32* %gcd, align 4
  br label %merge

merge:                                            ; preds = %else, %then
  %Load_id5 = load i32, i32* %gcd, align 4
  ret i32 %Load_id5
}
