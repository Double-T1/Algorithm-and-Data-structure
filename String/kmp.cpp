bool kmp(string& pattern, string& s) {
  vector<int> lps(pattern.size(),0)
  for (int i=0, j=1; j<pattern.size();) {
    if (pattern[i] == pattern[j]) lps[j++] = ++i;
    else if (i>0) i = lps[i-1];
    else j++;
  }
  
  int i = 0, j =0;
  while (i<s.size() && j<pattern.size()) {
    if (s[i] == pattern[j]) i++,j++;
    else if (j>0) j = lps[j-1];
    else i++;
  }
  
  if (j == pattern.size()) return true;
  return false;
}
