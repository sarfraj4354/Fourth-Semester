def depth_limited_search(graph, node, target, limit, path=[]): 
    path.append(node) 
 
    if node == target: 
        print("\nGoal found!") 
        print("Path:", " -> ".join(path)) 
        return True 
 
    if limit <= 0: 
        path.pop 
        return False 
 
    for neighbor in graph.get(node, []): 
        if depth_limited_search(graph, neighbor, target, limit - 1, path): 
            return True 
 
    path.pop()                                                           # backtrack if goal not found through this node 
    return False 
graph = { 
    'A': ['B', 'C'], 
    'B': ['D', 'E'], 
    'C': ['F'], 
    'D': [], 
    'E': ['G'], 
    'F': [], 
    'G': [] 
} 
 
                                                                                                         
print(" Depth-Limited Search By Sarfraj Alam") 
start = input("Enter the starting node: ").strip().upper() 
goal = input("Enter the goal node: ").strip().upper() 
try: 
    depth_limit = int(input("Enter the depth limit: ")) 
except ValueError: 
    print("Invalid depth limit. Please enter an integer.") 
    exit() 
 
found = depth_limited_search(graph, start, goal, depth_limit) 
if not found: 
    print(f"\nGoal '{goal}' not found within depth {depth_limit}")
