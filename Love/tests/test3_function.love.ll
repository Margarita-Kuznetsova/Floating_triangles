; ModuleID = 'love.module'
source_filename = "love.module"

@.int_string = internal global [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(...)

define void @__print_int(i32 %0) {
  %2 = call i32 (...) @printf([4 x i8]* @.int_string, i32 %0)
  ret void
}

define i32 @love(i32 %0, i32 %1) {
  %g = alloca i32, align 4
  %g1 = load i32, i32* %g, align 4
  %g2 = load i32, i32* %g, align 4
  store i32 %0, i32* %g, align 4
  %h = alloca i32, align 4
  %h3 = load i32, i32* %h, align 4
  %h4 = load i32, i32* %h, align 4
  store i32 %1, i32* %h, align 4
  %g5 = load i32, i32* %g, align 4
  %h6 = load i32, i32* %h, align 4
  %3 = icmp sgt i32 %g5, %h6
  br i1 %3, label %4, label %7

4:                                                ; preds = %2
  %g7 = load i32, i32* %g, align 4
  %g8 = load i32, i32* %g, align 4
  %5 = mul i32 %g8, 3
  %6 = sub i32 %5, 1
  store i32 %6, i32* %g, align 4
  br label %7

7:                                                ; preds = %4, %2
  br label %8

8:                                                ; preds = %10, %7
  %h9 = load i32, i32* %h, align 4
  %9 = icmp sgt i32 %h9, 2
  br i1 %9, label %10, label %12

10:                                               ; preds = %8
  %h10 = load i32, i32* %h, align 4
  %h11 = load i32, i32* %h, align 4
  %11 = sdiv i32 %h11, 2
  store i32 %11, i32* %h, align 4
  br label %8

12:                                               ; preds = %8
  %g12 = load i32, i32* %g, align 4
  call void @__print_int(i32 %g12)
  %h13 = load i32, i32* %h, align 4
  call void @__print_int(i32 %h13)
  %g14 = load i32, i32* %g, align 4
  ret i32 %g14
}

define i32 @main() {
  %tmp1 = alloca i32, align 4
  %tmp11 = load i32, i32* %tmp1, align 4
  %1 = call i32 @love(i32 160, i32 140)
  store i32 %1, i32* %tmp1, align 4
  ret i32 0
}
