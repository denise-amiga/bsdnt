#include <stdio.h>
#include <stdlib.h>
#include "nn.h"

#define ITER 100000

rand_t state;

int test_add_m(void)
{
   int result = 1;
   long i;
   nn_t a, b, c, r1, r2;
   len_t m, n;
   word_t ci;

   printf("nn_add_m...");

   /* test (a + b) + c = a + (b + c) */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      b = nn_init(m);
      c = nn_init(m);

      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);

      nn_random(a, state, m);
      nn_random(b, state, m);
      nn_random(c, state, m);

      nn_add_m(r1, a, b, m);
      nn_add_m(r1, r1, c, m);

      nn_add_m(r2, b, c, m);
      nn_add_m(r2, r2, a, m);

      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(c);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of addition */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);
      n = randint(100, state);

      a = nn_init(m + n);
      b = nn_init(m + n);

      r1 = nn_init(m + n + 1);
      r2 = nn_init(m + n + 1);

      nn_random(a, state, m + n);
      nn_random(b, state, m + n);
      
      ci = _nn_add_m(r1, a, b, m);
      nn_add_mc(r1 + m, a + m, b + m, n, ci);

      nn_add_m(r2, a, b, m + n);
      
      result = nn_equal_m(r1, r2, m + n + 1);

      if (!result)
      {
         printf("m = %ld, n = %ld\n", m, n);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_add(void)
{
   int result = 1;
   long i;
   nn_t a, b, c, r1, r2;
   len_t m1, m2, m3;
   word_t ci;

   printf("nn_add...");

   /* test a + b + c = a + c + b */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state) + 1;
      m2 = randint(m1, state);
      m3 = randint(m1, state);

      a = nn_init(m1);
      b = nn_init(m2);
      c = nn_init(m3);

      r1 = nn_init(m1 + 1);
      r2 = nn_init(m1 + 1);

      nn_random(a, state, m1);
      nn_random(b, state, m2);
      nn_random(c, state, m3);

      nn_add(r1, a, m1, b, m2);
      nn_add(r1, r1, m1, c, m3);

      nn_add(r2, a, m1, c, m3);
      nn_add(r2, r2, m1, b, m2);

      result = nn_equal_m(r1, r2, m1 + 1);

      if (!result)
      {
         printf("m1 = %ld, m2 = %ld, m3 = %ld\n", m1, m2, m3);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(c);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of addition */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state);
      m2 = randint(100, state);
      m3 = randint(100, state);

      a = nn_init(m1 + m2 + m3);
      b = nn_init(m2 + m3);

      r1 = nn_init(m1 + m2 + m3 + 1);
      r2 = nn_init(m1 + m2 + m3 + 1);

      nn_random(a, state, m1 + m2 + m3);
      nn_random(b, state, m2 + m3);
      
      ci = _nn_add(r1, a, m3, b, m3);
      nn_add_c(r1 + m3, a + m3, m1 + m2, b + m3, m2, ci);

      nn_add(r2, a, m1 + m2 + m3, b, m2 + m3);
      
      result = nn_equal_m(r1, r2, m1 + m2 + m3 + 1);

      if (!result)
      {
         printf("m1 = %ld, m2 = %ld, m3 = %ld\n", m1, m2, m3);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_sub_m(void)
{
   int result = 1;
   long i;
   nn_t a, b, c, r1, r2;
   len_t m, n;
   word_t ci;

   printf("nn_sub_m...");

   /* test (a - b) - c = (a - c) - b */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      b = nn_init(m);
      c = nn_init(m);

      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);

      nn_random(a, state, m);
      nn_random(b, state, m);
      nn_random(c, state, m);

      nn_sub_m(r1, a, b, m);
      nn_sub_m(r1, r1, c, m);

      nn_sub_m(r2, a, c, m);
      nn_sub_m(r2, r2, b, m);

      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(c);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of subtraction */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);
      n = randint(100, state);

      a = nn_init(m + n);
      b = nn_init(m + n);

      r1 = nn_init(m + n + 1);
      r2 = nn_init(m + n + 1);

      nn_random(a, state, m + n);
      nn_random(b, state, m + n);
      
      ci = _nn_sub_m(r1, a, b, m);
      nn_sub_mc(r1 + m, a + m, b + m, n, ci);

      nn_sub_m(r2, a, b, m + n);
      
      result = nn_equal_m(r1, r2, m + n + 1);

      if (!result)
      {
         printf("m = %ld, n = %ld\n", m, n);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test (a + b) - b = a */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      b = nn_init(m);

      r1 = nn_init(m + 1);
      
      nn_random(a, state, m);
      nn_random(b, state, m);
      
      nn_add_m(r1, a, b, m);
      nn_sub_m(r1, r1, b, m);

      result = (nn_equal_m(r1, a, m) && (r1[m] == 0));

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
   }

   /* test a - b = a + (-b) */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      b = nn_init(m);

      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);
      
      nn_random(a, state, m);
      nn_random(b, state, m); 
      
      nn_neg(r1, b, m);
      nn_add_m(r1, r1, a, m);
     
      nn_sub_m(r2, a, b, m);
      
      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_sub(void)
{
   int result = 1;
   long i;
   nn_t a, b, c, r1, r2;
   len_t m1, m2, m3;
   word_t ci;

   printf("nn_sub...");

   /* test a - b - c = a - c - b */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state) + 1;
      m2 = randint(m1, state);
      m3 = randint(m1, state);

      a = nn_init(m1);
      b = nn_init(m2);
      c = nn_init(m3);

      r1 = nn_init(m1 + 1);
      r2 = nn_init(m1 + 1);

      nn_random(a, state, m1);
      nn_random(b, state, m2);
      nn_random(c, state, m3);

      nn_sub(r1, a, m1, b, m2);
      nn_sub(r1, r1, m1, c, m3);

      nn_sub(r2, a, m1, c, m3);
      nn_sub(r2, r2, m1, b, m2);

      result = nn_equal_m(r1, r2, m1 + 1);

      if (!result)
      {
         printf("m1 = %ld, m2 = %ld, m3 = %ld\n", m1, m2, m3);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(c);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of subtraction */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state);
      m2 = randint(100, state);
      m3 = randint(100, state);

      a = nn_init(m1 + m2 + m3);
      b = nn_init(m2 + m3);

      r1 = nn_init(m1 + m2 + m3 + 1);
      r2 = nn_init(m1 + m2 + m3 + 1);

      nn_random(a, state, m1 + m2 + m3);
      nn_random(b, state, m2 + m3);
      
      ci = _nn_sub(r1, a, m3, b, m3);
      nn_sub_c(r1 + m3, a + m3, m1 + m2, b + m3, m2, ci);

      nn_sub(r2, a, m1 + m2 + m3, b, m2 + m3);
      
      result = nn_equal_m(r1, r2, m1 + m2 + m3 + 1);

      if (!result)
      {
         printf("m1 = %ld, m2 = %ld, m3 = %ld\n", m1, m2, m3);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_shl(void)
{
   int result = 1;
   long i;
   nn_t a, r1, r2;
   bits_t sh1, sh2;
   len_t m, n;
   word_t ci;

   printf("nn_shl...");

   /* test (a << sh1) << sh2 = (a << sh2) << sh1 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);

      nn_random(a, state, m);
      sh1 = randint(WORD_BITS, state);
      sh2 = randint(WORD_BITS - sh1, state);
         
      nn_shl(r1, a, m, sh1);
      _nn_shl(r1, r1, m + 1, sh2);

      nn_shl(r2, a, m, sh2);
      _nn_shl(r2, r2, m + 1, sh1);

      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld, sh1 = %ld, sh2 = %ld\n", m, sh1, sh2);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of shl */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);
      n = randint(100, state);

      a = nn_init(m + n);
      
      r1 = nn_init(m + n + 1);
      r2 = nn_init(m + n + 1);

      sh1 = randint(WORD_BITS, state);
      
      nn_random(a, state, m + n);
         
      ci = _nn_shl(r1, a, m, sh1);
      nn_shl_c(r1 + m, a + m, n, sh1, ci);
      
      nn_shl(r2, a, m + n, sh1);

      result = nn_equal_m(r1, r2, m + n + 1);

      if (!result)
      {
         printf("m = %ld, n = %ld\n", m, n);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test a << 1 = a + a */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);

      nn_random(a, state, m);
         
      nn_shl(r1, a, m, 1);
      
      nn_add_m(r2, a, a, m);
      
      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_shr(void)
{
   int result = 1;
   long i;
   nn_t a, r1, r2;
   bits_t sh1, sh2;
   len_t m, n;
   word_t ci;

   printf("nn_shr...");

   /* test (a >> sh1) >> sh2 = (a >> sh2) >> sh1 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m);
      r2 = nn_init(m);

      nn_random(a, state, m);
      sh1 = randint(WORD_BITS, state);
      sh2 = randint(WORD_BITS - sh1, state);
         
      _nn_shr(r1, a, m, sh1);
      _nn_shr(r1, r1, m, sh2);

      _nn_shr(r2, a, m, sh2);
      _nn_shr(r2, r2, m, sh1);

      result = nn_equal_m(r1, r2, m);

      if (!result)
      {
         printf("m = %ld, sh1 = %ld, sh2 = %ld\n", m, sh1, sh2);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of shr */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);
      n = randint(100, state);

      a = nn_init(m + n);
      
      r1 = nn_init(m + n);
      r2 = nn_init(m + n);

      sh1 = randint(WORD_BITS, state);
      
      nn_random(a, state, m + n);
         
      ci = _nn_shr(r1 + n, a + n, m, sh1);
      _nn_shr_c(r1, a, n, sh1, ci);
      
      _nn_shr(r2, a, m + n, sh1);

      result = nn_equal_m(r1, r2, m + n);

      if (!result)
      {
         printf("m = %ld, n = %ld\n", m, n);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test (a << sh1) >> sh1 = a */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m + 1);
      r2 = nn_init(m);

      nn_random(a, state, m);
      sh1 = randint(WORD_BITS, state);
        
      nn_shl(r1, a, m, sh1);
      
      nn_shr(r2, r1, m, sh1);
      
      result = nn_equal_m(a, r2, m);

      if (!result)
      {
         printf("m = %ld, sh1 = %ld\n", m, sh1);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_copy(void)
{
   int result = 1;
   long i;
   nn_t a, r1;
   len_t m;

   printf("nn_copy...");

   /* test copying yields equal integer */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m);
      
      nn_random(a, state, m);
         
      nn_copy(r1, a, m);
      
      result = nn_equal_m(r1, a, m);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(r1);
   }

   return result;
}

int test_equal_m(void)
{
   int result = 1;
   long i, s;
   nn_t a, r1;
   len_t m;

   printf("nn_equal_m...");

   /* test copying and then modifiying yields non-equal integer */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state) + 1;

      a = nn_init(m);
      
      r1 = nn_init(m);
      
      nn_random(a, state, m);
         
      nn_copy(r1, a, m);

      s = randint(m, state);
      a[s] += 1;

      result = !nn_equal_m(r1, a, m);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(r1);
   }

   return result;
}

int test_equal(void)
{
   int result = 1;
   long i;
   nn_t a, b, r1, r2;
   len_t m1, m2;
   
   printf("nn_equal...");

   /* test that equal things compare equal */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state);
 
      r1 = nn_init(m1);
      r2 = nn_init(m1);

      nn_random(r1, state, m1);
      
      nn_copy(r2, r1, m1);

      result = nn_equal(r1, m1, r2, m1);

      if (!result)
      {
         printf("m1 = %ld\n", m1);
      }

      nn_clear(r1);
      nn_clear(r2);
   }

   /* test that not equal lengths compare not equal */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state) + 1;
      m2 = randint(m1, state);

      r1 = nn_init(m1);
      r2 = nn_init(m2);

      do {
         nn_random(r1, state, m1);
      } while (nn_normalise(r1, m1) != m1);
      
      do {
         nn_random(r2, state, m2);
      } while (nn_normalise(r2, m2) != m2);
      
      result = !nn_equal(r1, m1, r2, m2);

      if (!result)
      {
         printf("m1 = %ld, m2 = %ld\n", m1, m2);
      }

      nn_clear(r1);
      nn_clear(r2);
   }

   /* test that not equal values compare not equal */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state) + 1;
      
      r1 = nn_init(m1 + 1);
      a = nn_init(m1);
      b = nn_init(m1);

      do {
         nn_random(a, state, m1);
         nn_random(b, state, m1);
         nn_add_m(r1, a, b, m1);
      } while (r1[m1] || nn_normalise(b, m1) != m1);
      
      result = !nn_equal(r1, m1, a, m1);

      if (!result)
      {
         printf("m1 = %ld, m2 = %ld\n", m1, m2);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
   }

   return result;
}

int test_zero(void)
{
   int result = 1;
   long i;
   nn_t a;
   len_t m;

   printf("nn_zero...");

   /* test zeroing */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      nn_random(a, state, m);
         
      nn_zero(a, m);

      result = (nn_normalise(a, m) == 0);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
   }

   return result;
}

int test_normalise(void)
{
   int result = 1;
   long i, s1, s2;
   nn_t a, r1;
   len_t m;

   printf("nn_normalise...");

   /* test normalising then copying normalised part yields same integer */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state) + 1;

      a = nn_init(m);
      r1 = nn_init(m);
      
      nn_random(a, state, m);
      
      s1 = randint(m, state);       
      nn_zero(a + s1, m - s1);
      s2 = nn_normalise(a, m);

      nn_zero(r1, m);
      nn_copy(r1, a, s2);

      result = ((s1 >= s2) && ((s2 == 0) || (a[s2 - 1] != 0))
             && nn_equal_m(a, r1, m));

      if (!result)
      {
         printf("m = %ld, s1 = %ld, s2 = %ld\n", m, s1, s2);
      }

      nn_clear(a);
      nn_clear(r1);
   }

   return result;
}

int test_mul1(void)
{
   int result = 1;
   long i;
   nn_t a, r1, r2, t1;
   word_t c1, c2, ci;
   len_t m, n;

   printf("nn_mul1...");

   /* test a * (c1 + c2) = a * c1 + a * c2 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      t1 = nn_init(m + 1);
      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);

      nn_random(a, state, m);
   
      do
      {
         c1 = randword(state);
         c2 = randword(state);
      } while (c1 + c2 < c1);

      nn_mul1(t1, a, m, c1);
      nn_mul1(r1, a, m, c2);
      _nn_add_m(r1, r1, t1, m + 1);
      
      nn_mul1(r2, a, m, c1 + c2);

      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld, c1 = %lu, c2 = %lu\n", m, c1, c2);
      }

      nn_clear(a);
      nn_clear(t1);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of mul1 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);
      n = randint(100, state);

      a = nn_init(m + n);
      
      r1 = nn_init(m + n + 1);
      r2 = nn_init(m + n + 1);

      nn_random(a, state, m + n);
   
      c1 = randword(state);

      ci = _nn_mul1(r1, a, m, c1);
      nn_mul1_c(r1 + m, a + m, n, c1, ci);
      
      nn_mul1(r2, a, m + n, c1);
      
      result = nn_equal_m(r1, r2, m + n + 1);

      if (!result)
      {
         printf("m = %ld, n = %ld, c1 = %lu\n", m, n, c1);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_add1(void)
{
   int result = 1;
   long i;
   nn_t a, r1, r2;
   word_t c1, c2, ci;
   len_t m, n;

   printf("nn_add1...");

   /* test a + c1 + c2 = a + c2 + c1 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);

      nn_random(a, state, m);
   
      c1 = randword(state);
      c2 = randword(state);
      
      nn_add1(r1, a, m, c1);
      nn_add1(r1, r1, m, c2);
      
      nn_add1(r2, a, m, c2);
      nn_add1(r2, r2, m, c1);

      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld, c1 = %lu, c2 = %lu\n", m, c1, c2);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of add1 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);
      n = randint(100, state);

      a = nn_init(m + n);
      
      r1 = nn_init(m + n + 1);
      r2 = nn_init(m + n + 1);

      nn_random(a, state, m + n);
   
      c1 = randword(state);

      ci = _nn_add1(r1, a, m, c1);
      nn_add1(r1 + m, a + m, n, ci);
      
      nn_add1(r2, a, m + n, c1);
      
      result = nn_equal_m(r1, r2, m + n + 1);

      if (!result)
      {
         printf("m = %ld, n = %lu, c1 = %lu\n", m, n, c1);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_sub1(void)
{
   int result = 1;
   long i;
   nn_t a, r1, r2;
   word_t c1, c2, ci;
   len_t m, n;

   printf("nn_sub1...");

   /* test a - c1 - c2 = a - c2 - c1 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);

      nn_random(a, state, m);
   
      c1 = randword(state);
      c2 = randword(state);
      
      nn_sub1(r1, a, m, c1);
      nn_sub1(r1, r1, m, c2);
      
      nn_sub1(r2, a, m, c2);
      nn_sub1(r2, r2, m, c1);

      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld, c1 = %lu, c2 = %lu\n", m, c1, c2);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of sub1 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);
      n = randint(100, state);

      a = nn_init(m + n);
      
      r1 = nn_init(m + n + 1);
      r2 = nn_init(m + n + 1);

      nn_random(a, state, m + n);
   
      c1 = randword(state);

      ci = _nn_sub1(r1, a, m, c1);
      nn_sub1(r1 + m, a + m, n, ci);
      
      nn_sub1(r2, a, m + n, c1);
      
      result = nn_equal_m(r1, r2, m + n + 1);

      if (!result)
      {
         printf("m = %ld, n = %lu, c1 = %lu\n", m, n, c1);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test a + c1 - c1 = a */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m + 1);
      a[m] = 0;

      r1 = nn_init(m + 1);
      
      nn_random(a, state, m);
   
      c1 = randword(state);
      
      nn_add1(r1, a, m, c1);
      nn_sub1(r1, r1, m, c1);
      
      result = nn_equal_m(r1, a, m + 1);

      if (!result)
      {
         printf("m = %ld, c1 = %lu\n", m, c1);
      }

      nn_clear(a);
      nn_clear(r1);
   }

   return result;
}

int test_not(void)
{
   int result = 1;
   long i;
   nn_t a, r1;
   len_t m;

   printf("nn_not...");

   /* test not not a = a */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m);
      
      nn_random(a, state, m);
   
      nn_not(r1, a, m);
      nn_not(r1, r1, m);
      
      result = nn_equal_m(r1, a, m);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(r1);
   }

   return result;
}

int test_neg(void)
{
   int result = 1;
   long i;
   nn_t a, r1, r2;
   len_t m, n;
   word_t ci;
   
   printf("nn_neg...");

   /* test neg a = not a + 1 */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);

      a = nn_init(m);
      
      r1 = nn_init(m + 1);
      r2 = nn_init(m + 1);
      
      nn_random(a, state, m);
   
      nn_neg(r1, a, m);

      nn_not(r2, a, m);
      r2[m] = ~ (word_t) 0;
      nn_add1(r2, r2, m, 1);
      
      result = nn_equal_m(r1, r2, m + 1);

      if (!result)
      {
         printf("m = %ld\n", m);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   /* test chaining of neg */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m = randint(100, state);
      n = randint(100, state);

      a = nn_init(m + n);
      
      r1 = nn_init(m + n + 1);
      r2 = nn_init(m + n + 1);
      
      nn_random(a, state, m + n);
   
      nn_neg(r1, a, m + n);
      
      ci = _nn_neg(r2, a, m);
      nn_neg_c(r2 + m, a + m, n, ci);
      
      result = nn_equal_m(r1, r2, m + n + 1);

      if (!result)
      {
         printf("m = %ld, n = %ld\n", m, n);
      }

      nn_clear(a);
      nn_clear(r1);
      nn_clear(r2);
   }

   return result;
}

int test_cmp_m(void)
{
   int result = 1;
   long i;
   nn_t a, b, r1, r2;
   len_t m1;
   
   printf("nn_cmp_m...");

   /* test that equal things compare equal */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state);
 
      r1 = nn_init(m1);
      r2 = nn_init(m1);

      nn_random(r1, state, m1);
      
      nn_copy(r2, r1, m1);

      result = (nn_cmp_m(r1, r2, m1) == 0);

      if (!result)
      {
         printf("m1 = %ld\n", m1);
      }

      nn_clear(r1);
      nn_clear(r2);
   }

   /* test that not equal values compare in the correct way */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state) + 1;
      
      r1 = nn_init(m1 + 1);
      a = nn_init(m1);
      b = nn_init(m1);

      do {
         nn_random(a, state, m1);
         nn_random(b, state, m1);
         nn_add_m(r1, a, b, m1);
      } while (r1[m1] || nn_normalise(b, m1) != m1);
      
      result = (nn_cmp_m(r1, a, m1) > 0 && nn_cmp_m(a, r1, m1) < 0);

      if (!result)
      {
         printf("m1 = %ld\n", m1);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
   }

   return result;
}

int test_cmp(void)
{
   int result = 1;
   long i;
   nn_t a, b, r1, r2;
   len_t m1, m2;
   
   printf("nn_cmp...");

   /* test that equal things compare equal */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state);
 
      r1 = nn_init(m1);
      r2 = nn_init(m1);

      nn_random(r1, state, m1);
      
      nn_copy(r2, r1, m1);

      result = (nn_cmp(r1, m1, r2, m1) == 0);

      if (!result)
      {
         printf("m1 = %ld\n", m1);
      }

      nn_clear(r1);
      nn_clear(r2);
   }

   /* test that not equal lengths compare in the correct way */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state) + 1;
      m2 = randint(m1, state);

      r1 = nn_init(m1);
      r2 = nn_init(m2);

      do {
         nn_random(r1, state, m1);
      } while (nn_normalise(r1, m1) != m1);
      
      do {
         nn_random(r2, state, m2);
      } while (nn_normalise(r2, m2) != m2);
      
      result = (nn_cmp(r1, m1, r2, m2) > 0 && nn_cmp(r2, m2, r1, m1) < 0);

      if (!result)
      {
         printf("m1 = %ld, m2 = %ld\n", m1, m2);
      }

      nn_clear(r1);
      nn_clear(r2);
   }

   /* test that not equal values compare in the correct way */
   for (i = 0; i < ITER && result == 1; i++)
   {
      m1 = randint(100, state) + 1;
      
      r1 = nn_init(m1 + 1);
      a = nn_init(m1);
      b = nn_init(m1);

      do {
         nn_random(a, state, m1);
         nn_random(b, state, m1);
         nn_add_m(r1, a, b, m1);
      } while (r1[m1] || nn_normalise(b, m1) != m1);
      
      result = (nn_cmp(r1, m1, a, m1) > 0 && nn_cmp(a, m1, r1, m1) < 0);

      if (!result)
      {
         printf("m1 = %ld, m2 = %ld\n", m1, m2);
      }

      nn_clear(a);
      nn_clear(b);
      nn_clear(r1);
   }

   return result;
}

#define RUN(xxx) \
   do { \
      if (xxx()) \
      { \
         printf("PASS\n"); \
         pass++; \
      } else \
      { \
         printf("FAIL\n"); \
         fail++; \
      } \
   } while (0)

int main(void)
{
   long pass = 0;
   long fail = 0;
   
   randinit(state);
   
   RUN(test_not);
   RUN(test_neg);
   RUN(test_add1);
   RUN(test_add_m);
   RUN(test_add);
   RUN(test_sub1);
   RUN(test_sub_m);
   RUN(test_sub);
   RUN(test_shl);
   RUN(test_shr);
   RUN(test_copy);
   RUN(test_equal_m);
   RUN(test_equal);
   RUN(test_zero);
   RUN(test_normalise);
   RUN(test_mul1);
   RUN(test_cmp_m);
   RUN(test_cmp);

   printf("%ld of %ld tests pass.\n", pass, pass + fail);

   randclear(state);

   return 0;
}

