// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -fclang-abi-compat=latest -target-feature +f32mm -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s
// RUN: %clang_cc1 -fclang-abi-compat=latest -target-feature +f32mm -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - -x c++ %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -fclang-abi-compat=latest -target-feature +f32mm -DSVE_OVERLOADED_FORMS -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s
// RUN: %clang_cc1 -fclang-abi-compat=latest -target-feature +f32mm -DSVE_OVERLOADED_FORMS -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - -x c++ %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s -check-prefix=CPP-CHECK

// REQUIRES: aarch64-registered-target

#include <arm_sve.h>

#ifdef SVE_OVERLOADED_FORMS
// A simple used,unused... macro, long enough to represent any SVE builtin.
#define SVE_ACLE_FUNC(A1, A2_UNUSED, A3, A4_UNUSED) A1##A3
#else
#define SVE_ACLE_FUNC(A1, A2, A3, A4) A1##A2##A3##A4
#endif

// CHECK-LABEL: @test_svmmla_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = tail call <vscale x 4 x float> @llvm.aarch64.sve.fmmla.nxv4f32(<vscale x 4 x float> [[X:%.*]], <vscale x 4 x float> [[Y:%.*]], <vscale x 4 x float> [[Z:%.*]])
// CHECK-NEXT:    ret <vscale x 4 x float> [[TMP0]]
//
// CPP-CHECK-LABEL: @_Z15test_svmmla_f32u13__SVFloat32_tS_S_(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = tail call <vscale x 4 x float> @llvm.aarch64.sve.fmmla.nxv4f32(<vscale x 4 x float> [[X:%.*]], <vscale x 4 x float> [[Y:%.*]], <vscale x 4 x float> [[Z:%.*]])
// CPP-CHECK-NEXT:    ret <vscale x 4 x float> [[TMP0]]
//
svfloat32_t test_svmmla_f32(svfloat32_t x, svfloat32_t y, svfloat32_t z) {
  return SVE_ACLE_FUNC(svmmla,_f32,,)(x, y, z);
}
