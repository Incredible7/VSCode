#include "question/804_Unique_Morse_Code_Words.cpp"
#include "regex"
#include "algm/parse.h"
int main(int argc, char *argv[])
{
    string str = "[[\"[\\\"gin\\\",\\\"zen\\\",\\\"gig\\\",\\\"msg\\\"]\"],[\"[\\\"a\\\"]\"]]";
    vector<vector<string>> arr = parseStringArrArr(str);
    for (int i = 0; i < arr.size(); i++)
    {
      vector<string> args = arr[i];
      Solution *s = new Solution();
      vector<string> arg0 = parseStringArr(args[0]);
      int result=s->uniqueMorseRepresentations(arg0);
      string resultabc =serializeInteger(result);
      cout << "resultabc"+to_string(i)+":" << resultabc <<"resultend"<< endl;
    }
    return 0;
}