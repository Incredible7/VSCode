import re

pattern = r'(\w)(?! .*\1)'
s = re.findall(pattern, "eternal.wlop!")
print(s)
