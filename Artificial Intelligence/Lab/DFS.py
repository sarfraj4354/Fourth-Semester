adj_list = { 
    "a":["b","c"], 
    "b":["d","e"], 
    "c":["f","g"], 
    "d":[], 
    "e":["h","i"], 
    "f":[], 
    "g":["j","k"], 
    "h":[], 
    "i":[], 
    "j":[], 
    "k":[], 
    } 
closedlist={} 
dfs_traversal_output=[] 
for node in adj_list.keys(): 
    closedlist[node]="notvisited" 
def dfs(u): 
    closedlist[u]="visited" 
    dfs_traversal_output.append(u) 
    for v in adj_list[u]: 
        if closedlist[v]!="visited": 
            dfs(v) 
print("Depth-First Search By Sarfraj Alam") 
startnode=input("Enter the node from where you want to traverse: ") 
dfs(startnode) 
print("Traversed sequence of the graph: ",dfs_traversal_output)
