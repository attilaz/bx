/*
 * Copyright 2010-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
 */

#ifndef BX_UINT32_T_H_HEADER_GUARD
#define BX_UINT32_T_H_HEADER_GUARD

#include "bx.h"

namespace bx
{
	constexpr uint16_t kHalfFloatZero = UINT16_C(0);
	constexpr uint16_t kHalfFloatHalf = UINT16_C(0x3800);
	constexpr uint16_t kHalfFloatOne  = UINT16_C(0x3c00);
	constexpr uint16_t kHalfFloatTwo  = UINT16_C(0x4000);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_li(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_dec(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_inc(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_not(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_neg(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_ext(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_and(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_andc(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_xor(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_xorl(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_or(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_orc(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_sl(uint32_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_sr(uint32_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC int32_t simd_i32_sr(int32_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_rol(uint32_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_ror(uint32_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_add(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_sub(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_mul(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_div(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_mod(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_cmpeq(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_cmpneq(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_cmplt(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_cmple(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_cmpgt(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_cmpge(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_setnz(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_satadd(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_satsub(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_satmul(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_sels(uint32_t test, uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_selb(uint32_t _mask, uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC  int32_t simd_i32_min(int32_t _a, int32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_i32_max(int32_t _a, int32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_min(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_min(uint32_t _a, uint32_t _b, uint32_t _c);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_max(uint32_t _a, uint32_t _b);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_max(uint32_t _a, uint32_t _b, uint32_t _c);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_clamp(uint32_t _a, uint32_t _min, uint32_t _max);

	///
	BX_CONSTEXPR_FUNC int32_t simd_i32_clamp(int32_t _a, int32_t _min, int32_t _max);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_incwrap(uint32_t _val, uint32_t _min, uint32_t _max);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_decwrap(uint32_t _val, uint32_t _min, uint32_t _max);

	/// Count number of bits set.
	///	????
	template<typename Ty>
	BX_CONSTEXPR_FUNC uint32_t simdXXX_cntbits(Ty _val);

	/// Count number of leading zeros.
	/// ????
	template<typename Ty>
	BX_CONSTEXPR_FUNC uint32_t simdXXX_cntlz(Ty _val);

	/// Count number of trailing zeros.
	/// ???
	template<typename Ty>
	BX_CONSTEXPR_FUNC uint32_t simdXXX_cnttz(Ty _val);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_part1by1(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_part1by2(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_testpow2(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_nextpow2(uint32_t _a);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_li(uint64_t _a);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_dec(uint64_t _a);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_inc(uint64_t _a);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_not(uint64_t _a);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_neg(uint64_t _a);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_ext(uint64_t _a);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_and(uint64_t _a, uint64_t _b);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_andc(uint64_t _a, uint64_t _b);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_xor(uint64_t _a, uint64_t _b);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_xorl(uint64_t _a, uint64_t _b);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_or(uint64_t _a, uint64_t _b);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_orc(uint64_t _a, uint64_t _b);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_sl(uint64_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_sr(uint64_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC int64_t simd_i64_sr(int64_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_rol(uint64_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_ror(uint64_t _a, int32_t _sa);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_add(uint64_t _a, uint64_t _b);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_sub(uint64_t _a, uint64_t _b);

	///
	BX_CONSTEXPR_FUNC uint64_t simd_u64_mul(uint64_t _a, uint64_t _b);

	/// Greatest common divisor.
	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_gcd(uint32_t _a, uint32_t _b);

	/// Least common multiple.
	///
	BX_CONSTEXPR_FUNC uint32_t simd_u32_lcm(uint32_t _a, uint32_t _b);

	/// Align to arbitrary stride.
	///
	BX_CONSTEXPR_FUNC uint32_t strideAlign(uint32_t _offset, uint32_t _stride);

	/// Align to arbitrary stride and Min bytes.
	///
	template<uint32_t Min>
	BX_CONSTEXPR_FUNC uint32_t strideAlign(uint32_t _offset, uint32_t _stride);

	/// Convert float to half-float.
	///
	BX_CONST_FUNC uint16_t halfFromFloat(float _a);

	/// Convert half-float to float.
	///
	BX_CONST_FUNC float halfToFloat(uint16_t _a);

} // namespace bx

#include "inline/uint32_t.inl"

#endif // BX_UINT32_T_H_HEADER_GUARD
