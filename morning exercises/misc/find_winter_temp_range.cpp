

/*
  1. create pair; first min, second max
  2. iterate thru t and keep local min max
  3. push local min max for every point into pair vector
  4. start new iteration from the end of t
  5. make comparation t[n] with min max inside pair vector for the same position
  6. continue while first t[n] < pair.second[n] and t[n] > pair.first[n]
  7. return n-1
 */
template <class T>
int solution(vector<T> &t)
{
    pair<T, T>
}
