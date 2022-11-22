; ModuleID = 'love.module'
source_filename = "love.module"

@.int_string = internal global [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(...)

define void @__print_int(i32 %0) {
  %2 = call i32 (...) @printf([4 x i8]* @.int_string, i32 %0)
  ret void
}

define i32 @main() {
  %a = alloca i32, align 4
  %a1 = load i32, i32* %a, align 4
  store i32 20, i32* %a, align 4
  br label %1

1:                                                ; preds = %3, %0
  %a2 = load i32, i32* %a, align 4
  %2 = icmp ne i32 %a2, 10
  br i1 %2, label %3, label %5

3:                                                ; preds = %1
  %a3 = load i32, i32* %a, align 4
  %a4 = load i32, i32* %a, align 4
  %4 = sub i32 %a4, 2
  store i32 %4, i32* %a, align 4
  br label %1

5:                                                ; preds = %1
  %a5 = load i32, i32* %a, align 4
  call void @__print_int(i32 %a5)
  %b = alloca i32, align 4
  %b6 = load i32, i32* %b, align 4
  store i32 100, i32* %b, align 4
  br label %6

6:                                                ; preds = %8, %5
  %b7 = load i32, i32* %b, align 4
  %7 = icmp sgt i32 %b7, 10
  br i1 %7, label %8, label %10

8:                                                ; preds = %6
  %b8 = load i32, i32* %b, align 4
  %b9 = load i32, i32* %b, align 4
  %a10 = load i32, i32* %a, align 4
  %9 = sdiv i32 %b9, %a10
  store i32 %9, i32* %b, align 4
  br label %6

10:                                               ; preds = %6
  %b11 = load i32, i32* %b, align 4
  call void @__print_int(i32 %b11)
  %c = alloca i32, align 4
  %c12 = load i32, i32* %c, align 4
  %b13 = load i32, i32* %b, align 4
  %a14 = load i32, i32* %a, align 4
  %11 = sub i32 %b13, %a14
  %12 = add i32 %11, 2
  store i32 %12, i32* %c, align 4
  %c15 = load i32, i32* %c, align 4
  call void @__print_int(i32 %c15)
  br label %13

13:                                               ; preds = %15, %10
  %c16 = load i32, i32* %c, align 4
  %14 = icmp slt i32 %c16, 17
  br i1 %14, label %15, label %17

15:                                               ; preds = %13
  %c17 = load i32, i32* %c, align 4
  %c18 = load i32, i32* %c, align 4
  %c19 = load i32, i32* %c, align 4
  %16 = mul i32 %c18, %c19
  store i32 %16, i32* %c, align 4
  br label %13

17:                                               ; preds = %13
  %c20 = load i32, i32* %c, align 4
  call void @__print_int(i32 %c20)
  ret i32 0
}
