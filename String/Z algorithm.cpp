//1. concat the pattern and target string with a non-existing char, often $ is used
//2. create a z array that find the longest substring that matches the prefix of the pattern)
//3. to find the substring that matches the pattern find the z[i] that equals to the length of the pattern

//here we only demo step 1 and 2
void create_z_arr(string& pattern, string$ word) {
  string s = pattern + word;
  vector<int> z(s.size(),0);
  
  int left=0,right=0, k;
  for (int i=1; i<s.size(); i++) {
    if (i>right) {
      left = right = i;
      
      while (right<n && s[right] == s[right-left]) right++;
      z[i] = right-left;
      right--; //the actual end that matches the prefix
    } else {
      k = i-left;
      if (z[k]<right-i+1) z[i] = z[k];
      else {
        left = i;
        
        while (right<n && s[right] == s[right-left]) right++;
        z[i] = right-left;
        right--;
      }
    }
  }
}




