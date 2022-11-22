; ModuleID = 'pcl.module'
source_filename = "pcl.module"

@.int_string = internal global [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(...)

define void @__print_int(i32 %0) {
  %2 = call i32 (...) @printf([4 x i8]* @.int_string, i32 %0)
  ret void
}

define i32 @foo(i32 %0, i32 %1) {
  %z = alloca i32, align 4
  %z1 = load i32, i32* %z, align 4
  %z2 = load i32, i32* %z, align 4
  store i32 %0, i32* %z, align 4
  %y = alloca i32, align 4
  %y3 = load i32, i32* %y, align 4
  %y4 = load i32, i32* %y, align 4
  store i32 %1, i32* %y, align 4
  %z5 = load i32, i32* %z, align 4
  %y6 = load i32, i32* %y, align 4
  %3 = icmp sgt i32 %z5, %y6
  br i1 %3, label %4, label %6

4:                                                ; preds = %2
  %z7 = load i32, i32* %z, align 4
  %z8 = load i32, i32* %z, align 4
  %5 = add i32 %z8, 1
  store i32 %5, i32* %z, align 4
  br label %6

6:                                                ; preds = %4, %2
  br label %7

7:                                                ; preds = %9, %6
  %y9 = load i32, i32* %y, align 4
  %8 = icmp ne i32 %y9, 2
  br i1 %8, label %9, label %11

9:                                                ; preds = %7
  %y10 = load i32, i32* %y, align 4
  %y11 = load i32, i32* %y, align 4
  %10 = sub i32 %y11, 1
  store i32 %10, i32* %y, align 4
  br label %7

11:                                               ; preds = %7
  %z12 = load i32, i32* %z, align 4
  call void @__print_int(i32 %z12)
  %y13 = load i32, i32* %y, align 4
  call void @__print_int(i32 %y13)
  ret i32 0
}

define i32 @main() {
  %tmp = alloca i32, align 4
  %tmp1 = load i32, i32* %tmp, align 4
  %1 = call i32 @foo(i32 6, i32 4)
  store i32 %1, i32* %tmp, align 4
  ret i32 0
}
