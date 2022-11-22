; ModuleID = 'love.module'
source_filename = "love.module"

@.int_string = internal global [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(...)

define void @__print_int(i32 %0) {
  %2 = call i32 (...) @printf([4 x i8]* @.int_string, i32 %0)
  ret void
}

define i32 @main() {
  %z = alloca i32, align 4
  %z1 = load i32, i32* %z, align 4
  store i32 20, i32* %z, align 4
  %z2 = load i32, i32* %z, align 4
  %1 = icmp sgt i32 %z2, 10
  br i1 %1, label %2, label %4

2:                                                ; preds = %0
  %z3 = load i32, i32* %z, align 4
  %z4 = load i32, i32* %z, align 4
  %3 = sub i32 %z4, 1
  store i32 %3, i32* %z, align 4
  br label %4

4:                                                ; preds = %2, %0
  %z5 = load i32, i32* %z, align 4
  call void @__print_int(i32 %z5)
  %y = alloca i32, align 4
  %y6 = load i32, i32* %y, align 4
  store i32 10, i32* %y, align 4
  %y7 = load i32, i32* %y, align 4
  %5 = icmp ne i32 %y7, 5
  br i1 %5, label %6, label %8

6:                                                ; preds = %4
  %y8 = load i32, i32* %y, align 4
  %z9 = load i32, i32* %z, align 4
  %7 = mul i32 %z9, 3
  store i32 %7, i32* %y, align 4
  br label %8

8:                                                ; preds = %6, %4
  %y10 = load i32, i32* %y, align 4
  call void @__print_int(i32 %y10)
  %a = alloca i32, align 4
  %a11 = load i32, i32* %a, align 4
  %z12 = load i32, i32* %z, align 4
  %y13 = load i32, i32* %y, align 4
  %9 = add i32 %z12, %y13
  store i32 %9, i32* %a, align 4
  %a14 = load i32, i32* %a, align 4
  call void @__print_int(i32 %a14)
  %a15 = load i32, i32* %a, align 4
  %10 = icmp slt i32 %a15, 150
  br i1 %10, label %11, label %13

11:                                               ; preds = %8
  %a16 = load i32, i32* %a, align 4
  %a17 = load i32, i32* %a, align 4
  %12 = sdiv i32 %a17, 3
  store i32 %12, i32* %a, align 4
  br label %13

13:                                               ; preds = %11, %8
  %a18 = load i32, i32* %a, align 4
  call void @__print_int(i32 %a18)
  ret i32 0
}
