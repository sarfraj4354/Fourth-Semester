graph={ 
    "a":["b","c","d"], 
    "b":["e","f"], 
    "c":["g","h"], 
    "d":["i"], 
    "e":[], 
    "f":[], 
    "g":[], 
    "h":[], 
    "i":[], 
 
    } 
 
def dfs(node, goal, d_limit, visited, path): 
    if node == goal: 
        return "FOUND", path + [node] 
    elif d_limit == 0: 
        return "NOT_FOUND", visited 
    else: 
        visited.add(node) 
        for child in graph[node]: 
            if child not in visited: 
                result, tv_path = dfs(child, goal, d_limit - 1, visited, path + [node]) 
                if result == "FOUND": 
                    return "FOUND", tv_path 
        return "NOT_FOUND", visited 
 
def iddfs(root, goal): 
    d_limit = 0 
    while True: 
        visited = set() 
        result, tv_path = dfs(root, goal, d_limit, visited, []) 
        print("Depth Limit:", d_limit, "Traversed path:", ' -> '.join(tv_path)) 
        if result == "FOUND": 
            return "Goal node found! Traversed path:" + ' -> '.join(tv_path) 
        elif result == "NOT_FOUND": 
            d_limit += 1 
 
print(" Iterative Deepening Depth First Search By Sarfraj Alam") 
root = input('Enter the start node: ') 
goal = input('Enter the goal node: ') 
result = iddfs(root, goal) 
print(result)
