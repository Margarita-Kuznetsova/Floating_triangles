; ModuleID = 'logic.c'
source_filename = "logic.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@data = dso_local local_unnamed_addr global [400 x [200 x i32]] zeroinitializer, align 16
@coord = dso_local local_unnamed_addr global [400 x i32] zeroinitializer, align 16
@calculate.first = internal unnamed_addr global i32 0, align 4

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @init_triangle() local_unnamed_addr #0 {
  call void @llvm.memset.p0i8.i64(i8* noundef nonnull align 16 dereferenceable(320000) bitcast ([400 x [200 x i32]]* @data to i8*), i8 0, i64 320000, i1 false), !tbaa !5
  br label %1

1:                                                ; preds = %1, %0
  %2 = phi i64 [ 0, %0 ], [ %10, %1 ]
  %3 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %2, i64 %2
  store i32 400, i32* %3, align 8, !tbaa !5
  %4 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %2
  %5 = trunc i64 %2 to i32
  store i32 %5, i32* %4, align 8, !tbaa !5
  %6 = or i64 %2, 1
  %7 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %6, i64 %6
  store i32 400, i32* %7, align 4, !tbaa !5
  %8 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %6
  %9 = trunc i64 %6 to i32
  store i32 %9, i32* %8, align 4, !tbaa !5
  %10 = add nuw nsw i64 %2, 2
  %11 = icmp eq i64 %10, 200
  br i1 %11, label %12, label %1, !llvm.loop !9

12:                                               ; preds = %1, %12
  %13 = phi i64 [ %23, %12 ], [ 200, %1 ]
  %14 = sub nuw nsw i64 400, %13
  %15 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %13, i64 %14
  store i32 400, i32* %15, align 8, !tbaa !5
  %16 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %13
  %17 = trunc i64 %14 to i32
  store i32 %17, i32* %16, align 8, !tbaa !5
  %18 = or i64 %13, 1
  %19 = sub nsw i64 399, %13
  %20 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %18, i64 %19
  store i32 400, i32* %20, align 4, !tbaa !5
  %21 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %18
  %22 = trunc i64 %19 to i32
  store i32 %22, i32* %21, align 4, !tbaa !5
  %23 = add nuw nsw i64 %13, 2
  %24 = icmp eq i64 %23, 400
  br i1 %24, label %25, label %12, !llvm.loop !11

25:                                               ; preds = %12, %29
  %26 = phi i64 [ %30, %29 ], [ 0, %12 ]
  %27 = trunc i64 %26 to i32
  br label %32

28:                                               ; preds = %29
  ret void

29:                                               ; preds = %32
  %30 = add nuw nsw i64 %26, 1
  %31 = icmp eq i64 %30, 400
  br i1 %31, label %28, label %25, !llvm.loop !12

32:                                               ; preds = %25, %32
  %33 = phi i64 [ 0, %25 ], [ %37, %32 ]
  %34 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %26, i64 %33
  %35 = load i32, i32* %34, align 4, !tbaa !5
  %36 = trunc i64 %33 to i32
  tail call void @put_pixel(i32 noundef %27, i32 noundef %36, i32 noundef %35) #4
  %37 = add nuw nsw i64 %33, 1
  %38 = icmp eq i64 %37, 200
  br i1 %38, label %29, label %32, !llvm.loop !13
}

declare void @put_pixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @calculate() local_unnamed_addr #0 {
  %1 = load i32, i32* @calculate.first, align 4, !tbaa !5
  %2 = add nsw i32 %1, 1
  %3 = icmp eq i32 %2, 400
  %4 = select i1 %3, i32 0, i32 %2
  store i32 %4, i32* @calculate.first, align 4
  %5 = tail call i32 @save_var(i32 noundef %4, i32 noundef 200, i32 noundef 400) #4
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %6
  store i32 400, i32* %7, align 4, !tbaa !5
  %8 = load i32, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 0), align 16, !tbaa !5
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %9
  store i32 0, i32* %10, align 4, !tbaa !5
  %11 = load i32, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 399), align 4, !tbaa !5
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %12
  store i32 0, i32* %13, align 4, !tbaa !5
  %14 = load i32, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 -1, i64 399), align 4, !tbaa !5
  br label %16

15:                                               ; preds = %16
  store i32 %36, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 399), align 4, !tbaa !5
  br label %40

16:                                               ; preds = %0, %16
  %17 = phi i32 [ %14, %0 ], [ %19, %16 ]
  %18 = phi i64 [ 0, %0 ], [ %20, %16 ]
  %19 = phi i32 [ %5, %0 ], [ %36, %16 ]
  %20 = add nuw nsw i64 %18, 1
  %21 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %20
  %22 = load i32, i32* %21, align 4, !tbaa !5
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %18, i64 %23
  store i32 0, i32* %24, align 4, !tbaa !5
  %25 = sext i32 %17 to i64
  %26 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %18, i64 %25
  store i32 0, i32* %26, align 4, !tbaa !5
  %27 = add nuw nsw i64 %18, 2
  %28 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %27
  %29 = load i32, i32* %28, align 4, !tbaa !5
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %18, i64 %30
  store i32 0, i32* %31, align 4, !tbaa !5
  %32 = tail call i32 @rand() #4
  %33 = srem i32 %32, 3
  %34 = add nsw i32 %33, 1
  %35 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %18
  %36 = load i32, i32* %35, align 4, !tbaa !5
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %18, i64 %37
  store i32 %34, i32* %38, align 4, !tbaa !5
  store i32 %19, i32* %35, align 4, !tbaa !5
  %39 = icmp eq i64 %20, 399
  br i1 %39, label %15, label %16, !llvm.loop !14

40:                                               ; preds = %15, %44
  %41 = phi i64 [ 0, %15 ], [ %45, %44 ]
  %42 = trunc i64 %41 to i32
  br label %47

43:                                               ; preds = %44
  ret void

44:                                               ; preds = %47
  %45 = add nuw nsw i64 %41, 1
  %46 = icmp eq i64 %45, 400
  br i1 %46, label %43, label %40, !llvm.loop !15

47:                                               ; preds = %40, %47
  %48 = phi i64 [ 0, %40 ], [ %52, %47 ]
  %49 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %41, i64 %48
  %50 = load i32, i32* %49, align 4, !tbaa !5
  %51 = trunc i64 %48 to i32
  tail call void @put_pixel(i32 noundef %42, i32 noundef %51, i32 noundef %50) #4
  %52 = add nuw nsw i64 %48, 1
  %53 = icmp eq i64 %52, 200
  br i1 %53, label %44, label %47, !llvm.loop !16
}

declare i32 @save_var(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #2

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #3

attributes #0 = { nounwind sspstrong uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { argmemonly nofree nounwind willreturn writeonly }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{!"clang version 14.0.6"}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = distinct !{!11, !10}
!12 = distinct !{!12, !10}
!13 = distinct !{!13, !10}
!14 = distinct !{!14, !10}
!15 = distinct !{!15, !10}
!16 = distinct !{!16, !10}
