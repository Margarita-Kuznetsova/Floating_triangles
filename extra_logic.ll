; ModuleID = 'love.module'
source_filename = "love.module"


define i32 @save_var(i32 %0, i32 %1, i32 %2) {
  %first = alloca i32, align 4
  %first1 = load i32, i32* %first, align 4
  %first2 = load i32, i32* %first, align 4
  store i32 %0, i32* %first, align 4
  %width = alloca i32, align 4
  %width3 = load i32, i32* %width, align 4
  %width4 = load i32, i32* %width, align 4
  store i32 %1, i32* %width, align 4
  %length = alloca i32, align 4
  %length5 = load i32, i32* %length, align 4
  %length6 = load i32, i32* %length, align 4
  store i32 %2, i32* %length, align 4
  %tmp1 = alloca i32, align 4
  %tmp17 = load i32, i32* %tmp1, align 4
  %length8 = load i32, i32* %length, align 4
  %first9 = load i32, i32* %first, align 4
  %4 = mul i32 2, %first9
  %5 = sub i32 %length8, %4
  %6 = sub i32 %5, 1
  store i32 %6, i32* %tmp1, align 4
  %tmp2 = alloca i32, align 4
  %tmp210 = load i32, i32* %tmp2, align 4
  %first11 = load i32, i32* %first, align 4
  %width12 = load i32, i32* %width, align 4
  %7 = sdiv i32 %first11, %width12
  %tmp113 = load i32, i32* %tmp1, align 4
  %8 = mul i32 %7, %tmp113
  store i32 %8, i32* %tmp2, align 4
  %tmp214 = load i32, i32* %tmp2, align 4
  %first15 = load i32, i32* %first, align 4
  %9 = add i32 %tmp214, %first15
  ret i32 %9
}
