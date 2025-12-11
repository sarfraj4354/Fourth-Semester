"""
A simple command‑line chatbot that tolerates user typing mistakes.
---------------------------------------------------------------
* Uses Python's built‑in difflib for fuzzy string matching (no extra dependencies).
* Define intents (keys) with associated responses (values) in the INTENTS dict.
* At runtime, the bot compares the user's message with the intents and returns
  the response for the closest match whose similarity ratio exceeds THRESHOLD.
* If nothing is sufficiently close, the bot falls back to a default reply.

Run: python typo_tolerant_chatbot.py
"""

import difflib
from typing import Dict, Tuple

# ---------------------------- Configuration --------------------------- #

THRESHOLD: float = 0.65  # minimum similarity ratio (0–1) to accept a match
INTENTS: Dict[str, str] = {
    "hello": "Hi there! How can I assist you today?",
    "hi": "Hello! How can I help you?",
    "help": "Sure—tell me what you need help with and I'll do my best!",
    "bye": "Goodbye! Have a great day!",
    "thanks": "You're welcome!",
}
FALLBACK_RESPONSE: str = (
    "I'm sorry, I didn't quite catch that. Could you please rephrase?"
)

# ----------------------------- Functions ------------------------------ #

def find_best_intent(user_input: str) -> Tuple[str, float]:
    """Return the intent with the highest similarity ratio to *user_input*.

    Args:
        user_input: The user's message.

    Returns:
        (best_intent, best_ratio).
        If no intents exist, returns ("", 0.0).
    """
    best_intent = ""
    best_ratio = 0.0

    for intent in INTENTS:
        ratio = difflib.SequenceMatcher(None, user_input.lower(), intent).ratio()
        if ratio > best_ratio:
            best_ratio = ratio
            best_intent = intent
    return best_intent, best_ratio


def get_response(user_input: str) -> str:
    """Return the chatbot's response to *user_input*."""
    intent, ratio = find_best_intent(user_input)
    if ratio >= THRESHOLD:
        return INTENTS[intent]
    return FALLBACK_RESPONSE


# ---------------------------- Main Program ---------------------------- #

if __name__ == "__main__":
    print("🤖  Typo‑Tolerant Chatbot (type 'bye' to exit)\n")
    while True:
        try:
            user_message = input("👤  You: ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\n🤖  Bot: Goodbye! 👋")
            break

        if not user_message:
            continue  # ignore empty input
        response = get_response(user_message)
        print(f"🤖  Bot: {response}")

        if user_message.lower() == "bye":
            break
