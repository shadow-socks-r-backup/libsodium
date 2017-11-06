#ifndef curve25519_ref10_H
#define curve25519_ref10_H

#include <stddef.h>
#include <stdint.h>

/*
 fe means field element.
 Here the field is \Z/(2^255-19).
 */

#define fe crypto_core_curve25519_ref10_fe
#ifdef HAVE_TI_MODE
typedef uint64_t fe[5];
#else
typedef int32_t fe[10];
#endif

#define fe_frombytes crypto_core_curve25519_ref10_fe_frombytes
#define fe_tobytes crypto_core_curve25519_ref10_fe_tobytes
#define fe_copy crypto_core_curve25519_ref10_fe_copy
#define fe_iszero crypto_core_curve25519_ref10_fe_iszero
#define fe_0 crypto_core_curve25519_ref10_fe_0
#define fe_1 crypto_core_curve25519_ref10_fe_1
#define fe_add crypto_core_curve25519_ref10_fe_add
#define fe_sub crypto_core_curve25519_ref10_fe_sub
#define fe_mul crypto_core_curve25519_ref10_fe_mul
#define fe_sq crypto_core_curve25519_ref10_fe_sq
#define fe_invert crypto_core_curve25519_ref10_fe_invert
#define fe_cswap crypto_core_curve25519_fe_cswap
#define fe_scalar_product crypto_core_curve25519_fe_scalar_product

extern void fe_frombytes(fe,const unsigned char *);
extern void fe_tobytes(unsigned char *,const fe);

extern void fe_copy(fe,const fe);
extern int  fe_iszero(const fe);
extern void fe_0(fe);
extern void fe_1(fe);
extern void fe_add(fe,const fe,const fe);
extern void fe_sub(fe,const fe,const fe);
extern void fe_mul(fe,const fe,const fe);
extern void fe_sq(fe,const fe);
extern void fe_invert(fe,const fe);
extern void fe_cswap(fe f, fe g, unsigned int b);
extern void fe_scalar_product(fe h, const fe f, uint32_t n);

/*
 ge means group element.
 *
 Here the group is the set of pairs (x,y) of field elements (see fe.h)
 satisfying -x^2 + y^2 = 1 + d x^2y^2
 where d = -121665/121666.
 *
 Representations:
 ge_p2 (projective): (X:Y:Z) satisfying x=X/Z, y=Y/Z
 ge_p3 (extended): (X:Y:Z:T) satisfying x=X/Z, y=Y/Z, XY=ZT
 ge_p1p1 (completed): ((X:Z),(Y:T)) satisfying x=X/Z, y=Y/T
 ge_precomp (Duif): (y+x,y-x,2dxy)
 */

#define ge_p2 crypto_core_curve25519_ref10_ge_p2
typedef struct {
    fe X;
    fe Y;
    fe Z;
} ge_p2;

#define ge_p3 crypto_core_curve25519_ref10_ge_p3
typedef struct {
    fe X;
    fe Y;
    fe Z;
    fe T;
} ge_p3;

#define ge_p1p1 crypto_core_curve25519_ref10_ge_p1p1
typedef struct {
    fe X;
    fe Y;
    fe Z;
    fe T;
} ge_p1p1;

#define ge_precomp crypto_core_curve25519_ref10_ge_precomp
typedef struct {
    fe yplusx;
    fe yminusx;
    fe xy2d;
} ge_precomp;

#define ge_cached crypto_core_curve25519_ref10_ge_cached
typedef struct {
    fe YplusX;
    fe YminusX;
    fe Z;
    fe T2d;
} ge_cached;

#define ge_frombytes_negate_vartime crypto_core_curve25519_ref10_ge_frombytes_negate_vartime
#define ge_frombytes crypto_core_curve25519_ref10_ge_frombytes
#define ge_tobytes crypto_core_curve25519_ref10_ge_tobytes
#define ge_p3_tobytes crypto_core_curve25519_ref10_ge_p3_tobytes

#define ge_p3_to_cached crypto_core_curve25519_ref10_ge_p3_to_cached
#define ge_p1p1_to_p2 crypto_core_curve25519_ref10_ge_p1p1_to_p2

#define ge_add crypto_core_curve25519_ref10_ge_add
#define ge_scalarmult crypto_core_curve25519_ref10_ge_scalarmult
#define ge_scalarmult_base crypto_core_curve25519_ref10_ge_scalarmult_base
#define ge_double_scalarmult_vartime crypto_core_curve25519_ref10_ge_double_scalarmult_vartime
#define ge_scalarmult_vartime crypto_core_curve25519_ref10_ge_scalarmult_vartime
#define ge_is_canonical crypto_core_curve25519_ref10_ge_is_canonical
#define ge_is_on_curve crypto_core_curve25519_ref10_ge_is_on_curve
#define ge_is_on_main_subgroup crypto_core_curve25519_ref10_ge_is_on_main_subgroup
#define ge_has_small_order crypto_core_curve25519_ref10_ge_has_small_order

extern void ge_tobytes(unsigned char *,const ge_p2 *);
extern void ge_p3_tobytes(unsigned char *,const ge_p3 *);
extern int ge_frombytes(ge_p3 *,const unsigned char *);
extern int ge_frombytes_negate_vartime(ge_p3 *,const unsigned char *);

extern void ge_p3_to_cached(ge_cached *,const ge_p3 *);
extern void ge_p1p1_to_p2(ge_p2 *,const ge_p1p1 *);

extern void ge_add(ge_p1p1 *,const ge_p3 *,const ge_cached *);
extern void ge_scalarmult_base(ge_p3 *,const unsigned char *);
extern void ge_double_scalarmult_vartime(ge_p2 *,const unsigned char *,const ge_p3 *,const unsigned char *);
extern void ge_scalarmult(ge_p3 *,const unsigned char *,const ge_p3 *);
extern void ge_scalarmult_vartime(ge_p3 *,const unsigned char *,const ge_p3 *);
extern int ge_is_canonical(const unsigned char *s);
extern int ge_is_on_curve(const ge_p3 *p);
extern int ge_is_on_main_subgroup(const ge_p3 *p);
extern int ge_has_small_order(const unsigned char s[32]);

/*
 The set of scalars is \Z/l
 where l = 2^252 + 27742317777372353535851937790883648493.
 */

#define sc_reduce crypto_core_curve25519_ref10_sc_reduce
#define sc_muladd crypto_core_curve25519_ref10_sc_muladd
#define sc_is_canonical crypto_core_curve25519_ref10_sc_is_canonical

extern void sc_reduce(unsigned char *);
extern void sc_muladd(unsigned char *,const unsigned char *,const unsigned char *,const unsigned char *);
extern int sc_is_canonical(const unsigned char *s);

#endif
