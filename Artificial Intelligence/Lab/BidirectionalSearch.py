from collections import deque 
def reverse_graph(graph): 
    rev_graph = {node: [] for node in graph} 
    for node, neighbors in graph.items(): 
        for neigh in neighbors: 
            rev_graph.setdefault(neigh, []).append(node) 
    return rev_graph 
 
def bidirectional_search(graph, start, goal): 
    if start == goal: 
        print(f"Start is the same as goal: {start}") 
        return [start] 
    rev_graph = reverse_graph(graph) 
    q_start = deque([(start, [start])]) 
    q_goal = deque([(goal, [goal])]) 
    visited_start = {start: [start]} 
    visited_goal = {goal: [goal]} 
    while q_start and q_goal: 
        node_s, path_s = q_start.popleft() 
        for neighbor in graph.get(node_s, []): 
            if neighbor not in visited_start: 
                visited_start[neighbor] = path_s + [neighbor] 
                q_start.append((neighbor, path_s + [neighbor])) 
                if neighbor in visited_goal: 
                    full_path = visited_start[neighbor] + visited_goal[neighbor][-2::-1] 
                    print(f"\nPath found: {' -> '.join(full_path)}") 
                    return full_path 
 
        node_g, path_g = q_goal.popleft() 
        for neighbor in rev_graph.get(node_g, []): 
            if neighbor not in visited_goal: 
                visited_goal[neighbor] = path_g + [neighbor] 
                q_goal.append((neighbor, path_g + [neighbor])) 
                if neighbor in visited_start: 
                    full_path = visited_start[neighbor] + visited_goal[neighbor][-2::-1] 
                    print(f"\nPath found: {' -> '.join(full_path)}") 
                    return full_path 
    print("\nNo path found between the two nodes.") 
    return None 
graph = { 
    'A': ['B', 'C'], 
    'B': ['D', 'E'], 
    'C': ['F'], 
    'D': [], 
    'E': ['G'], 
    'F': [], 
    'G': ['H'], 
    'H': [] 
} 
print(" Bidirectional Search Algorithm By Sarfraj Alam") 
start = input("Enter start node: ").strip().upper() 
goal = input("Enter goal node: ").strip().upper() 
 
print("\nBidirectional Search by Sarfraj Alam") 
bidirectional_search(graph, start, goal)
