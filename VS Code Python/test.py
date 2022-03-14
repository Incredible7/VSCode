<<<<<<< HEAD
import re

pattern = r'(\w)(?! .*\1)'
s = re.findall(pattern, "eternal.wlop!")
print(s)
=======
def searchPath(gragh, start, end): 
    results = []
    _generatePath(gragh, [start], end, results)
    results.sort(key= lambda x:len(x))
    return results

def _generatePath(gragh, path, end, results):
    current = path[-1]
    if current == end:
        results.append(path)
    else:
        for n in gragh[current]
>>>>>>> 4856bd939adebc47bfaad07aa771f1e43b6613ca
