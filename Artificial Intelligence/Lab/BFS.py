import queue 
adj_list = { 
    "a":["b","c"], 
    "b":["d","e","f"], 
    "c":["g","h"], 
    "d":[], 
    "e":["i","j"], 
    "f":[], 
    "g":["k","l"], 
    "h":["m"], 
    "i":[], 
    "j":[], 
    "k":[], 
    "l":[], 
    "m":[], 
    } 
 
visited=[]   # List for visited nodes. 
queue=[]     #Initialize a queue 
bfs_traversal_output=[] 
 
def bfs(visited, graph, node): #function for BFS 
  visited.append(node) 
  queue.append(node) 
  while queue:          # Creating loop to visit each node 
    m = queue.pop(0) 
    bfs_traversal_output.append(m) 
    for neighbour in graph[m]: 
      if neighbour not in visited: 
        visited.append(neighbour) 
        queue.append(neighbour) 
         
  print("The traversing of graph: ",bfs_traversal_output); 
 
print("Breadth-First Search By Sarfraj Alam"); 
startnode=input("Enter the node from where you want to traverse: "); 
bfs(visited,adj_list,startnode) 
