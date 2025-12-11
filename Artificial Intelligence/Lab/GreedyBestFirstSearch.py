import heapq

# Graph representation with letter nodes
graph = {
    'A': {'B': 1, 'C': 4},
    'B': {'A': 1, 'C': 2, 'D': 5, 'E': 3},
    'C': {'A': 4, 'B': 2, 'F': 6},
    'D': {'B': 5, 'E': 1, 'G': 2},
    'E': {'B': 3, 'D': 1, 'F': 4, 'G': 1},
    'F': {'C': 6, 'E': 4, 'H': 3},
    'G': {'D': 2, 'E': 1, 'H': 2},
    'H': {'F': 3, 'G': 2}
}

# Heuristic values (estimated distance to goal)
# These represent straight-line distances to each node
def get_heuristic_values(goal):
    heuristics = {
        'A': {'A': 0, 'B': 7, 'C': 6, 'D': 8, 'E': 5, 'F': 9, 'G': 4, 'H': 3},
        'B': {'A': 7, 'B': 0, 'C': 3, 'D': 5, 'E': 2, 'F': 8, 'G': 3, 'H': 6},
        'C': {'A': 6, 'B': 3, 'C': 0, 'D': 8, 'E': 5, 'F': 4, 'G': 6, 'H': 7},
        'D': {'A': 8, 'B': 5, 'C': 8, 'D': 0, 'E': 2, 'F': 7, 'G': 1, 'H': 3},
        'E': {'A': 5, 'B': 2, 'C': 5, 'D': 2, 'E': 0, 'F': 4, 'G': 1, 'H': 3},
        'F': {'A': 9, 'B': 8, 'C': 4, 'D': 7, 'E': 4, 'F': 0, 'G': 5, 'H': 2},
        'G': {'A': 4, 'B': 3, 'C': 6, 'D': 1, 'E': 1, 'F': 5, 'G': 0, 'H': 2},
        'H': {'A': 3, 'B': 6, 'C': 7, 'D': 3, 'E': 3, 'F': 2, 'G': 2, 'H': 0}
    }
    return heuristics.get(goal, {})

# Greedy Best-First Search with letter nodes
def greedy_best_first_search(graph, start, goal):
    if start not in graph or goal not in graph:
        return None, "Invalid start or goal node"
    
    visited = set()
    priority_queue = []
    heuristic_values = get_heuristic_values(goal)
    
    # Heap queue with (heuristic, node)
    heapq.heappush(priority_queue, (heuristic_values.get(start, float('inf')), start))
    came_from = {start: None}
    
    print(f"\nSearching from {start} to {goal}...")
    print("Search Progress:")
    
    while priority_queue:
        current_heuristic, current = heapq.heappop(priority_queue)
        
        if current in visited:
            continue
            
        visited.add(current)
        print(f"Visiting node {current} (heuristic: {current_heuristic})")
        
        if current == goal:
            print(f"Goal {goal} reached!")
            break
        
        # Explore neighbors
        for neighbor in graph.get(current, {}):
            if neighbor not in visited:
                neighbor_heuristic = heuristic_values.get(neighbor, float('inf'))
                heapq.heappush(priority_queue, (neighbor_heuristic, neighbor))
                if neighbor not in came_from:
                    came_from[neighbor] = current
    
    # Reconstruct path
    if goal not in came_from:
        return None, f"No path found from {start} to {goal}"
    
    path = []
    node = goal
    while node:
        path.append(node)
        node = came_from.get(node)
    path.reverse()
    
    return path, "Path found successfully"

# Display available nodes
def display_graph():
    print("Available nodes in the graph:")
    print("Nodes:", sorted(graph.keys()))
    print("\nGraph connections:")
    for node, neighbors in graph.items():
        print(f"{node}: {list(neighbors.keys())}")

# Main execution
def main():
    print("=" * 50)
    print("Greedy Best-First Search By Sarfraj Alam")
    print("=" * 50)
    
    display_graph()
    
    print("\n" + "-" * 30)
    
    # Get user input
    while True:
        start = input("\nEnter the source node (A-H): ").strip().upper()
        if start in graph:
            break
        print("Invalid node! Please choose from A, B, C, D, E, F, G, H")
    
    while True:
        goal = input("Enter the destination node (A-H): ").strip().upper()
        if goal in graph:
            break
        print("Invalid node! Please choose from A, B, C, D, E, F, G, H")
    
    # Perform search
    path, message = greedy_best_first_search(graph, start, goal)
    
    # Display results
    print("\n" + "=" * 50)
    print("SEARCH RESULTS")
    print("=" * 50)
    
    if path:
        print(f"Status: {message}")
        print(f"Path found: {' -> '.join(path)}")
        print(f"Number of nodes in path: {len(path)}")
        
        # Calculate total cost
        total_cost = 0
        for i in range(len(path) - 1):
            current_node = path[i]
            next_node = path[i + 1]
            cost = graph[current_node].get(next_node, 0)
            total_cost += cost
            print(f"  {current_node} -> {next_node}: cost = {cost}")
        
        print(f"Total path cost: {total_cost}")
    else:
        print(f"Status: {message}")

# Run the program
if __name__ == "__main__":
    main()
