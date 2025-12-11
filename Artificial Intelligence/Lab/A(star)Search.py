import heapq

# Graph representation with letter nodes and costs
graph = {
    'A': {'B': 2, 'C': 3},
    'B': {'A': 2, 'C': 1, 'D': 4, 'E': 2},
    'C': {'A': 3, 'B': 1, 'F': 5},
    'D': {'B': 4, 'E': 1, 'G': 3},
    'E': {'B': 2, 'D': 1, 'F': 2, 'G': 2},
    'F': {'C': 5, 'E': 2, 'H': 1},
    'G': {'D': 3, 'E': 2, 'H': 2},
    'H': {'F': 1, 'G': 2}
}

# Heuristic function (admissible - never overestimates)
def get_heuristic_values(goal):
    # Straight-line distances to each possible goal
    heuristics = {
        'A': {'A': 0, 'B': 2, 'C': 3, 'D': 6, 'E': 4, 'F': 7, 'G': 6, 'H': 8},
        'B': {'A': 2, 'B': 0, 'C': 1, 'D': 4, 'E': 2, 'F': 5, 'G': 4, 'H': 6},
        'C': {'A': 3, 'B': 1, 'C': 0, 'D': 5, 'E': 3, 'F': 4, 'G': 5, 'H': 5},
        'D': {'A': 6, 'B': 4, 'C': 5, 'D': 0, 'E': 1, 'F': 3, 'G': 2, 'H': 3},
        'E': {'A': 4, 'B': 2, 'C': 3, 'D': 1, 'E': 0, 'F': 2, 'G': 2, 'H': 3},
        'F': {'A': 7, 'B': 5, 'C': 4, 'D': 3, 'E': 2, 'F': 0, 'G': 3, 'H': 1},
        'G': {'A': 6, 'B': 4, 'C': 5, 'D': 2, 'E': 2, 'F': 3, 'G': 0, 'H': 2},
        'H': {'A': 8, 'B': 6, 'C': 5, 'D': 3, 'E': 3, 'F': 1, 'G': 2, 'H': 0}
    }
    return heuristics.get(goal, {})

# A* Search Algorithm
def a_star_search(graph, start, goal):
    if start not in graph or goal not in graph:
        return None, float('inf'), "Invalid start or goal node"
    
    # Priority queue: (f_score, g_score, node)
    open_set = []
    heapq.heappush(open_set, (0, 0, start))
    
    # Track the path
    came_from = {}
    
    # Cost from start to each node
    g_score = {node: float('inf') for node in graph}
    g_score[start] = 0
    
    # Estimated total cost from start to goal through each node
    heuristic_values = get_heuristic_values(goal)
    f_score = {node: float('inf') for node in graph}
    f_score[start] = heuristic_values.get(start, 0)
    
    # Keep track of nodes in open set
    open_set_nodes = {start}
    
    print(f"\nA* Search from {start} to {goal}")
    print("Search Progress:")
    print(f"{'Node':<4} {'g(n)':<6} {'h(n)':<6} {'f(n)':<6} {'Action'}")
    print("-" * 35)
    
    while open_set:
        # Get node with lowest f_score
        current_f, current_g, current = heapq.heappop(open_set)
        open_set_nodes.discard(current)
        
        h_value = heuristic_values.get(current, 0)
        print(f"{current:<4} {current_g:<6} {h_value:<6} {current_f:<6} Exploring")
        
        # Goal reached
        if current == goal:
            print(f"{current:<4} {current_g:<6} {h_value:<6} {current_f:<6} GOAL!")
            break
        
        # Explore neighbors
        for neighbor, cost in graph.get(current, {}).items():
            tentative_g = g_score[current] + cost
            
            # Better path found
            if tentative_g < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g
                h_neighbor = heuristic_values.get(neighbor, 0)
                f_score[neighbor] = tentative_g + h_neighbor
                
                if neighbor not in open_set_nodes:
                    heapq.heappush(open_set, (f_score[neighbor], tentative_g, neighbor))
                    open_set_nodes.add(neighbor)
    
    # Reconstruct path
    if goal not in came_from and start != goal:
        return None, float('inf'), f"No path found from {start} to {goal}"
    
    path = []
    node = goal
    while node in came_from:
        path.append(node)
        node = came_from[node]
    path.append(start)
    path.reverse()
    
    total_cost = g_score[goal]
    return path, total_cost, "Optimal path found"

# Display graph information
def display_graph():
    print("Available nodes in the graph:")
    print("Nodes:", sorted(graph.keys()))
    print("\nGraph connections with costs:")
    for node, neighbors in graph.items():
        connections = [f"{neighbor}({cost})" for neighbor, cost in neighbors.items()]
        print(f"{node}: {', '.join(connections)}")

# Main execution function
def main():
    print("=" * 60)
    print("A* Search Algorithm By Sarfraj Alam")
    print("=" * 60)
    
    display_graph()
    
    print("\n" + "-" * 40)
    
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
    
    # Perform A* search
    path, total_cost, message = a_star_search(graph, start, goal)
    
    # Display results
    print("\n" + "=" * 60)
    print("A* SEARCH RESULTS")
    print("=" * 60)
    
    if path:
        print(f"Status: {message}")
        print(f"Optimal path: {' -> '.join(path)}")
        print(f"Total optimal cost: {total_cost}")
        print(f"Number of nodes in path: {len(path)}")
        
        print("\nDetailed path costs:")
        running_cost = 0
        for i in range(len(path) - 1):
            current_node = path[i]
            next_node = path[i + 1]
            edge_cost = graph[current_node][next_node]
            running_cost += edge_cost
            print(f"  {current_node} -> {next_node}: +{edge_cost} (total: {running_cost})")
    else:
        print(f"Status: {message}")
        print(f"Cost: {total_cost}")

# Run the program
if __name__ == "__main__":
    main()
