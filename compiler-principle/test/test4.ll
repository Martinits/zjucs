; ModuleID = 'main'
source_filename = "main"

@f = global i32 0
@k = global i32 0
@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [4 x i8] c"%d\0A\00"

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
  store i32 0, i32* @k, align 4
  %0 = call i32 @go(i32* @k, i32 5)
  store i32 %0, i32* @f, align 4
  %Load_id = load i32, i32* @f, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %Load_id)
  %Load_id1 = load i32, i32* @k, align 4
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %Load_id1)
  ret void
}

define internal i32 @go(i32* nonnull %0, i32 %1) {
entrypoint:
  %t = alloca double, align 8
  %fk = alloca i32, align 4
  %go = alloca i32, align 4
  %a = alloca i32, align 4
  %b = getelementptr i32, i32* %0, i32 0
  store i32 %1, i32* %a, align 4
  %Load_id = load i32, i32* %a, align 4
  %gttmp = icmp sgt i32 %Load_id, 0
  %ifCond = icmp ne i1 %gttmp, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entrypoint
  %Load_id1 = load i32, i32* %a, align 4
  %subtmp = sub i32 %Load_id1, 1
  %2 = call i32 @go(i32* %b, i32 %subtmp)
  %Load_id2 = load i32, i32* %a, align 4
  %multmp = mul i32 %Load_id2, %2
  store i32 %multmp, i32* %go, align 4
  br label %merge

else:                                             ; preds = %entrypoint
  store i32 1, i32* %go, align 4
  br label %merge

merge:                                            ; preds = %else, %then
  %Load_id3 = load i32, i32* %go, align 4
  %Load_id4 = load i32, i32* %b, align 4
  %addtmp = add i32 %Load_id4, %Load_id3
  store i32 %addtmp, i32* %b, align 4
  %Load_id5 = load i32, i32* %go, align 4
  %Load_id6 = load i32, i32* @k, align 4
  %addtmp7 = add i32 %Load_id6, %Load_id5
  store i32 %addtmp7, i32* @k, align 4
  %Load_id8 = load i32, i32* %go, align 4
  ret i32 %Load_id8
}
