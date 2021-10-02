; ModuleID = 'main'
source_filename = "main"

@i = global i32 0
@.str = constant [4 x i8] c"%c\0A\00"
@.str.1 = constant [4 x i8] c"%c\0A\00"
@.str.2 = constant [4 x i8] c"%c\0A\00"
@.str.3 = constant [4 x i8] c"%c\0A\00"
@.str.4 = constant [4 x i8] c"%c\0A\00"
@.str.5 = constant [4 x i8] c"%c\0A\00"

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
  store i32 1, i32* @i, align 4
  %Load_id = load i32, i32* @i, align 4
  br label %switch

afterCase:                                        ; preds = %case4, %switch3, %case2, %case
  store i32 2, i32* @i, align 4
  %Load_id9 = load i32, i32* @i, align 4
  br label %switch11

switch:                                           ; preds = %entrypoint
  %equaltmp = icmp eq i32 %Load_id, 1
  br i1 %equaltmp, label %case, label %switch1

case:                                             ; preds = %switch
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8 49)
  br label %afterCase

switch1:                                          ; preds = %switch
  %equaltmp5 = icmp eq i32 %Load_id, 2
  br i1 %equaltmp5, label %case2, label %switch3

case2:                                            ; preds = %switch1
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8 50)
  br label %afterCase

switch3:                                          ; preds = %switch1
  %equaltmp7 = icmp eq i32 %Load_id, 3
  br i1 %equaltmp7, label %case4, label %afterCase

case4:                                            ; preds = %switch3
  %printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8 51)
  br label %afterCase

afterCase10:                                      ; preds = %case16, %switch15, %case14, %case12
  ret void

switch11:                                         ; preds = %afterCase
  %equaltmp17 = icmp eq i32 %Load_id9, 1
  br i1 %equaltmp17, label %case12, label %switch13

case12:                                           ; preds = %switch11
  %printf18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i8 49)
  br label %afterCase10

switch13:                                         ; preds = %switch11
  %equaltmp19 = icmp eq i32 %Load_id9, 2
  br i1 %equaltmp19, label %case14, label %switch15

case14:                                           ; preds = %switch13
  %printf20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i8 50)
  br label %afterCase10

switch15:                                         ; preds = %switch13
  %equaltmp21 = icmp eq i32 %Load_id9, 3
  br i1 %equaltmp21, label %case16, label %afterCase10

case16:                                           ; preds = %switch15
  %printf22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i8 51)
  br label %afterCase10
}
