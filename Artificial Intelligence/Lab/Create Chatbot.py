"""
smart_chatbot.py
Rule‑based terminal chatbot with simple typo correction.

Features
────────
1. Regex‑pattern intents with multiple random replies
2. Keyword‑based fallback if no intent matches
3. Lightweight spelling helper:
   • Builds a vocabulary from all patterns & keywords
   • Uses difflib.get_close_matches to fix small typos
"""

import re
import random
from difflib import get_close_matches
from typing import List

# ──────────────────────────────
# 1️⃣  Intents dataset
# ──────────────────────────────
INTENTS = {
    "greeting": {
        "patterns": [r"\bhi\b", r"\bhello\b", r"\bhey\b"],
        "responses": [
            "Hello! 👋",
            "Hi there — how can I help?",
            "Hey! What’s up?"
        ],
    },
    "goodbye": {
        "patterns": [r"\bbye\b", r"\bexit\b", r"\bquit\b"],
        "responses": [
            "Goodbye! Have a nice day. 👋",
            "See you later!",
            "Bye‑bye!"
        ],
    },
    "thanks": {
        "patterns": [r"\bthank(?:s| you)?\b"],
        "responses": [
            "You’re welcome!",
            "No problem at all 😊",
            "Happy to help!"
        ],
    },
    "about_bot": {
        "patterns": [r"\byour name\b", r"\bwho (?:are|r) you\b"],
        "responses": [
            "I’m a tiny Python chatbot.",
            "Just some joyful lines of code ✨"
        ],
    },
    "how_are_you": {
        "patterns": [r"\bhow are you\b", r"\bhow’s it going\b"],
        "responses": [
            "I’m doing great, thanks for asking!",
            "Running at full speed 🏃‍♂️💨"
        ],
    },
    "weather": {
        "patterns": [r"\bweather\b", r"\btemperature\b", r"\bforecast\b"],
        "responses": [
            "I’m not connected to a weather service yet, but it looks nice outside!",
            "I can’t fetch live weather right now — maybe bring an umbrella just in case ☂️"
        ],
    },
}

# ──────────────────────────────
# 2️⃣  Keyword fallback replies
# ──────────────────────────────
KEYWORDS = {
    "python": "Python is an amazing language! 🐍",
    "chatbot": "Chatbots are fun, aren’t they?",
    "help": "Sure — tell me what you need help with."
}

# ──────────────────────────────
# 3️⃣  Build vocabulary for typo fix
# ──────────────────────────────
def build_vocab() -> List[str]:
    vocab = set()
    for intent in INTENTS.values():
        for pat in intent["patterns"]:
            vocab.update(re.findall(r"[a-z']+", pat))
    vocab.update(KEYWORDS.keys())
    return sorted(vocab)

VOCAB = build_vocab()

def correct_typos(sentence: str) -> str:
    """
    Replace misspelled words with the closest vocabulary
    match if similarity ≥ 0.8 (difflib ratio).
    """
    tokens = re.findall(r"[a-z']+|[^a-z']+", sentence.lower())
    corrected = []
    for tok in tokens:
        if re.fullmatch(r"[a-z']+", tok):
            match = get_close_matches(tok, VOCAB, n=1, cutoff=0.8)
            corrected.append(match[0] if match else tok)
        else:
            corrected.append(tok)
    return "".join(corrected)

# ──────────────────────────────
# 4️⃣  Core response logic
# ──────────────────────────────
def keyword_fallback(message: str) -> str | None:
    for kw, reply in KEYWORDS.items():
        if kw in message:
            return reply
    return None

def get_response(user_msg: str) -> str:
    clean_msg = correct_typos(user_msg)

    # Intent matching
    for intent in INTENTS.values():
        if any(re.search(pat, clean_msg) for pat in intent["patterns"]):
            return random.choice(intent["responses"])

    # Keyword fallback
    fallback = keyword_fallback(clean_msg)
    if fallback:
        return fallback

    # Default
    return "Sorry, I didn’t quite understand that 🤔"

# ──────────────────────────────
# 5️⃣  Conversation loop
# ──────────────────────────────
def run_chatbot() -> None:
    print("Chatbot: Hi! Type ‘bye’ to quit.")
    while True:
        try:
            user_input = input("You: ").strip()
        except (KeyboardInterrupt, EOFError):
            print("\nChatbot: Bye! 👋")
            break

        if re.fullmatch(r"\s*(bye|exit|quit)\s*", user_input, re.I):
            print("Chatbot:", random.choice(INTENTS["goodbye"]["responses"]))
            break

        print("Chatbot:", get_response(user_input))

# ──────────────────────────────
# 6️⃣  Entry point
# ──────────────────────────────
if __name__ == "__main__":
    run_chatbot()
