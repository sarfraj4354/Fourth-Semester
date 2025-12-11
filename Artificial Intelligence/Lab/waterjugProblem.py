from collections import deque

def water_jug_bfs(capacityA, capacityB, target):
    # Check if solution is possible
    def gcd(a, b):
        while b:
            a, b = b, a % b
        return a

    if target > max(capacityA, capacityB) or target % gcd(capacityA, capacityB) != 0:
        return "No solution possible"

    visited = set()
    queue = deque()
    queue.append((0, 0, []))  # initial state and empty path

    while queue:
        jugA, jugB, path = queue.popleft()

        if jugA == target or jugB == target:
            return path + [(jugA, jugB)]

        if (jugA, jugB) in visited:
            continue
        visited.add((jugA, jugB))

        next_states = []

        # Fill Jug A
        next_states.append((capacityA, jugB))
        # Fill Jug B
        next_states.append((jugA, capacityB))
        # Empty Jug A
        next_states.append((0, jugB))
        # Empty Jug B
        next_states.append((jugA, 0))

        # Pour A -> B
        pour_to_B = min(jugA, capacityB - jugB)
        next_states.append((jugA - pour_to_B, jugB + pour_to_B))

        # Pour B -> A
        pour_to_A = min(jugB, capacityA - jugA)
        next_states.append((jugA + pour_to_A, jugB - pour_to_A))

        for state in next_states:
            if state not in visited:
                queue.append((state[0], state[1], path + [(jugA, jugB)]))

    return "No solution found"

def main():
    print("Water Jug Problem Solving By Sarfraj Alam")
    capacityA = int(input("Enter capacity of Jug A (liters): "))
    capacityB = int(input("Enter capacity of Jug B (liters): "))
    target = int(input("Enter the target amount to measure (liters): "))

    solution = water_jug_bfs(capacityA, capacityB, target)
    if isinstance(solution, str):
        print(solution)
    else:
        print("\nSteps to measure", target, "liters:")
        for step in solution:
            print(f"Jug A: {step[0]} liters, Jug B: {step[1]} liters")

if __name__ == "__main__":
    main()
