; ModuleID = 'logic'
source_filename = "logic"

@data = common global [400 x [200 x i32]] zeroinitializer, align 16
@coord = common global [400 x i32] zeroinitializer, align 16
@calculate.first = common global i32 0, align 4

define void @init_triangle() {
  call void @llvm.memset.p0i8.i64(i8* bitcast ([400 x [200 x i32]]* @data to i8*), i8 0, i64 320000, i1 false)
  br label %1

1:                                                ; preds = %1, %0
  %2 = phi i64 [ 0, %0 ], [ %10, %1 ]
  %3 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %2, i64 %2
  store i32 400, i32* %3, align 8
  %4 = getelementptr [400 x i32], [400 x i32]* @coord, i64 0, i64 %2
  %5 = trunc i64 %2 to i32
  store i32 %5, i32* %4, align 8
  %6 = or i64 %2, 1
  %7 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %6, i64 %6
  store i32 400, i32* %7, align 4
  %8 = getelementptr [400 x i32], [400 x i32]* @coord, i64 0, i64 %6
  %9 = trunc i64 %6 to i32
  store i32 %9, i32* %8, align 4
  %10 = add i64 %2, 2
  %11 = icmp eq i64 %10, 200
  br i1 %11, label %12, label %1

12:                                               ; preds = %12, %1
  %13 = phi i64 [ 200, %1 ], [ %23, %12 ]
  %14 = sub i64 400, %13
  %15 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %13, i64 %14
  store i32 400, i32* %15, align 8
  %16 = getelementptr [400 x i32], [400 x i32]* @coord, i64 0, i64 %13
  %17 = trunc i64 %14 to i32
  store i32 %17, i32* %16, align 8
  %18 = or i64 %13, 1
  %19 = sub i64 399, %13
  %20 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %18, i64 %19
  store i32 400, i32* %20, align 4
  %21 = getelementptr [400 x i32], [400 x i32]* @coord, i64 0, i64 %18
  %22 = trunc i64 %19 to i32
  store i32 %22, i32* %21, align 4
  %23 = add i64 %13, 2
  %24 = icmp eq i64 %23, 400
  br i1 %24, label %25, label %12

25:                                               ; preds = %29, %12
  %26 = phi i64 [ 0, %12 ], [ %30, %29 ]
  %27 = trunc i64 %26 to i32
  br label %32

28:                                               ; preds = %29
  ret void

29:                                               ; preds = %32
  %30 = add i64 %26, 1
  %31 = icmp eq i64 %30, 400
  br i1 %31, label %28, label %25

32:                                               ; preds = %32, %25
  %33 = phi i64 [ 0, %25 ], [ %37, %32 ]
  %34 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %26, i64 %33
  %35 = load i32, i32* %34, align 4
  %36 = trunc i64 %33 to i32
  call void @put_pixel(i32 %27, i32 %36, i32 %35)
  %37 = add i64 %33, 1
  %38 = icmp eq i64 %37, 200
  br i1 %38, label %29, label %32
}

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #0

declare void @put_pixel(i32, i32, i32)

define void @calculate() {
  %1 = load i32, i32* @calculate.first, align 4
  %2 = add i32 %1, 1
  %3 = icmp eq i32 %2, 400
  %4 = select i1 %3, i32 0, i32 %2
  store i32 %4, i32* @calculate.first, align 4
  %5 = sdiv i32 %4, 200
  %6 = mul i32 %4, -2
  %7 = add i32 %6, 399
  %8 = mul i32 %7, %5
  %9 = add i32 %8, %4
  %10 = sext i32 %9 to i64
  %11 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %10
  store i32 400, i32* %11, align 4
  %12 = load i32, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 0), align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %13
  store i32 0, i32* %14, align 4
  %15 = load i32, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 399), align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %16
  store i32 0, i32* %17, align 4
  %18 = load i32, i32* getelementptr ([400 x i32], [400 x i32]* @coord, i64 -1, i64 399), align 4
  br label %20

19:                                               ; preds = %20
  br label %44

20:                                               ; preds = %20, %0
  %21 = phi i32 [ %18, %0 ], [ %23, %20 ]
  %22 = phi i64 [ 0, %0 ], [ %24, %20 ]
  %23 = phi i32 [ %9, %0 ], [ %40, %20 ]
  %24 = add i64 %22, 1
  %25 = getelementptr [400 x i32], [400 x i32]* @coord, i64 0, i64 %24
  %26 = load i32, i32* %25, align 4
  %27 = sext i32 %26 to i64
  %28 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %22, i64 %27
  store i32 0, i32* %28, align 4
  %29 = sext i32 %21 to i64
  %30 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %22, i64 %29
  store i32 0, i32* %30, align 4
  %31 = add i64 %22, 2
  %32 = getelementptr [400 x i32], [400 x i32]* @coord, i64 0, i64 %31
  %33 = load i32, i32* %32, align 4
  %34 = sext i32 %33 to i64
  %35 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %22, i64 %34
  store i32 0, i32* %35, align 4
  %36 = call i32 @rand()
  %37 = srem i32 %36, 3
  %38 = add i32 %37, 1
  %39 = getelementptr [400 x i32], [400 x i32]* @coord, i64 0, i64 %22
  %40 = load i32, i32* %39, align 4
  store i32 %40, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 399), align 4
  %41 = sext i32 %40 to i64
  %42 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %22, i64 %41
  store i32 %38, i32* %42, align 4
  store i32 %23, i32* %39, align 4
  %43 = icmp eq i64 %24, 399
  br i1 %43, label %19, label %20

44:                                               ; preds = %48, %19
  %45 = phi i64 [ 0, %19 ], [ %49, %48 ]
  %46 = trunc i64 %45 to i32
  br label %51

47:                                               ; preds = %48
  ret void

48:                                               ; preds = %51
  %49 = add i64 %45, 1
  %50 = icmp eq i64 %49, 400
  br i1 %50, label %47, label %44

51:                                               ; preds = %51, %44
  %52 = phi i64 [ 0, %44 ], [ %56, %51 ]
  %53 = getelementptr [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %45, i64 %52
  %54 = load i32, i32* %53, align 4
  %55 = trunc i64 %52 to i32
  call void @put_pixel(i32 %46, i32 %55, i32 %54)
  %56 = add i64 %52, 1
  %57 = icmp eq i64 %56, 200
  br i1 %57, label %48, label %51
}

declare i32 @rand()

attributes #0 = { argmemonly nofree nounwind willreturn writeonly }
