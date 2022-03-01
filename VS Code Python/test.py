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