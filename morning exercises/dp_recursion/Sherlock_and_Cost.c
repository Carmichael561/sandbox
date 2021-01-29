/*
  consider first A[1] -> 1: A[0] only original
  consider A[1] original: So A[0] can be original or 1
  the same for A[2]
  put it on 1
  put it on original
 */

#define MAX(a, b) ( ((a)<(b)) ? (b) : (a) )
int cost(int n, int* A)
{
    int m1 = abs(A[0] - 1);
    int m2 = MAX( abs(1 - A[1]), abs(A[0] - A[1]) );
    int m1_copy = m1;
    for (int i = 2; i < n; i++)
    {
        m1_copy = m1;
        m1 = MAX( abs(A[i-1] - 1) + m2, m1 );
        m2 = MAX( abs(1 - A[i]) + m1_copy, abs(A[i-1] - A[i]) + m2 );
    }
    return MAX(m1, m2);
}
