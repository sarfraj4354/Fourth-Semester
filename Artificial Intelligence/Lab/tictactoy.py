def print_board(board):
    print("\n")
    print(f" {board[0]} | {board[1]} | {board[2]} ")
    print("---|---|---")
    print(f" {board[3]} | {board[4]} | {board[5]} ")
    print("---|---|---")
    print(f" {board[6]} | {board[7]} | {board[8]} ")
    print("\n")

def check_winner(board, player):
    win_combos = [
        (0, 1, 2), (3, 4, 5), (6, 7, 8),  # rows
        (0, 3, 6), (1, 4, 7), (2, 5, 8),  # cols
        (0, 4, 8), (2, 4, 6)              # diagonals
    ]
    for combo in win_combos:
        if all(board[i] == player for i in combo):
            return True
    return False

def is_draw(board):
    return all(cell in ["X", "O"] for cell in board)

def tic_tac_toe():
    board = [str(i) for i in range(1, 10)]  # 1-9 positions
    current_player = "X"
    
    while True:
        print_board(board)
        move = input(f"Player {current_player}, choose a position (1-9): ")

        if not move.isdigit() or int(move) not in range(1, 10):
            print("Invalid input. Choose a number from 1 to 9.")
            continue

        move = int(move) - 1
        if board[move] in ["X", "O"]:
            print("That position is already taken. Choose another.")
            continue

        board[move] = current_player

        if check_winner(board, current_player):
            print_board(board)
            print(f"🎉 Player {current_player} wins!")
            break

        if is_draw(board):
            print_board(board)
            print("It's a draw!")
            break

        current_player = "O" if current_player == "X" else "X"

# Run the game
tic_tac_toe()
